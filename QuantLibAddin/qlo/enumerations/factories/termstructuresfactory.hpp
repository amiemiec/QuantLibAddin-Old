/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2006, 2007 Eric Ehlers
 Copyright (C) 2016 Stefano Fondi

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef qla_termstructuresfactory_hpp
#define qla_termstructuresfactory_hpp

#include <oh/enumerations/typefactory.hpp>
#include <ql/types.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/math/interpolations/mixedinterpolation.hpp>
//++AMI
#include <ql/termstructures/defaulttermstructure.hpp>
//AMI++
//++AMI
#include <ql/termstructures/inflationtermstructure.hpp>
#include <ql/termstructures/inflation/interpolatedzeroinflationcurve.hpp>
//AMI++


namespace QuantLib {
    class Calendar;
    class Quote;
    class DayCounter;
    class YieldTermStructure;

    template<class TS>
    class BootstrapHelper;

    typedef BootstrapHelper<YieldTermStructure> RateHelper;

    //++AMI
    class DefaultProbabilityTermStructure;
    typedef BootstrapHelper<DefaultProbabilityTermStructure> DefaultProbabilityHelper;
    //AMI++

    //++AMI
    class ZeroInflationTermStructure;
    typedef BootstrapHelper<ZeroInflationTermStructure> InflationZeroHelper;
    //AMI++

}

namespace ObjectHandler {

    typedef boost::shared_ptr<QuantLib::YieldTermStructure>(*YieldTermStructureConstructor)(
            QuantLib::Natural nDays,
            const QuantLib::Calendar& calendar,
            const std::vector<boost::shared_ptr<QuantLib::RateHelper> >& rh,
            const QuantLib::DayCounter& dayCounter,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
            const std::vector<QuantLib::Date>& jumpDates,
            const QuantLib::MixedInterpolation::Behavior behavior,
            const QuantLib::Size n);

    template<>
    class Create<boost::shared_ptr<QuantLib::YieldTermStructure> > :
        private RegistryManager<QuantLib::YieldTermStructure,
                                EnumPairRegistry> {
    public:
        boost::shared_ptr<QuantLib::YieldTermStructure> operator() (
                const std::string& traitsID,
                const std::string& interpolatorID,
                QuantLib::Natural nDays,
                const QuantLib::Calendar& calendar,
                const std::vector<boost::shared_ptr<QuantLib::RateHelper> >& rh,
                const QuantLib::DayCounter& dayCounter,
                const std::vector<QuantLib::Handle<QuantLib::Quote> >& jumps,
                const std::vector<QuantLib::Date>& jumpDates,
                const QuantLib::MixedInterpolation::Behavior behavior,
                const QuantLib::Size n) {
            KeyPair key(traitsID, interpolatorID);
            YieldTermStructureConstructor yieldTermStructureConstructor =
                reinterpret_cast<YieldTermStructureConstructor>(getType(key));
            return yieldTermStructureConstructor(nDays, calendar,
                                                 rh, dayCounter,
                                                 jumps, jumpDates,
                                                 behavior, n);
        }
        using RegistryManager<QuantLib::YieldTermStructure,
                              EnumPairRegistry>::registerType;
    };


    //AMI++
    typedef boost::shared_ptr<QuantLib::DefaultProbabilityTermStructure>(*DefaultProbabilityTermStructureConstructor)(
        const QuantLib::Date& referenceDate,
        const std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> >& instruments,
        const QuantLib::DayCounter& dayCounter);


    template<>
    class Create<boost::shared_ptr<QuantLib::DefaultProbabilityTermStructure> > :
        private RegistryManager<QuantLib::DefaultProbabilityTermStructure,
        EnumPairRegistry> {
    public:
        boost::shared_ptr<QuantLib::DefaultProbabilityTermStructure> operator() (
            const std::string& traitsID,
            const std::string& interpolatorID,
            const QuantLib::Date& referenceDate,
            const std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> >& instruments,
            const QuantLib::DayCounter& dayCounter) {
            KeyPair key(traitsID, interpolatorID);
            DefaultProbabilityTermStructureConstructor defaultProbabilityTermStructureConstructor =
                reinterpret_cast<DefaultProbabilityTermStructureConstructor>(getType(key));

            return defaultProbabilityTermStructureConstructor(referenceDate,
                instruments,
                dayCounter);
        }
        using RegistryManager<QuantLib::DefaultProbabilityTermStructure,
            EnumPairRegistry>::registerType;
    };
    //++AMI


    //AMI++
    typedef boost::shared_ptr<QuantLib::ZeroInflationTermStructure>(*ZeroInflationTermStructureConstructor)(
        const QuantLib::Date& referenceDate,
        const QuantLib::Date& baseDate,
        const QuantLib::Frequency& frequency,
        const std::vector<boost::shared_ptr<QuantLib::InflationZeroHelper> >& instruments,
        const QuantLib::DayCounter& dayCounter);


    template<>
    class Create<boost::shared_ptr<QuantLib::ZeroInflationTermStructure> > :
        private RegistryManager<QuantLib::ZeroInflationTermStructure,
        EnumPairRegistry> {
    public:
        boost::shared_ptr<QuantLib::ZeroInflationTermStructure> operator() (
            const std::string& traitsID,
            const std::string& interpolatorID,
            const QuantLib::Date& referenceDate,
            const QuantLib::Date& baseDate,
            const QuantLib::Frequency frequency,
            const std::vector<boost::shared_ptr<QuantLib::InflationZeroHelper> >& instruments,
            const QuantLib::DayCounter& dayCounter) {
            KeyPair key(traitsID, interpolatorID);
            ZeroInflationTermStructureConstructor zeroInflationTermStructureConstructor =
                reinterpret_cast<ZeroInflationTermStructureConstructor>(getType(key));

            return zeroInflationTermStructureConstructor(referenceDate,
                baseDate,
                frequency,
                instruments,
                dayCounter);
        }
        using RegistryManager<QuantLib::ZeroInflationTermStructure,
            EnumPairRegistry>::registerType;
    };
    //++AMI



 }

#endif
