/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2024 Andre Miemiec

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

#ifndef qla_fxvolstructure_hpp
#define qla_fxvolstructure_hpp

#include <qlo/termstructures.hpp>
#include <qlo/smilesection.hpp>
#include <ql/time/businessdayconvention.hpp>

#include <ql/termstructures/volatility/equityfx/blackvoltermstructure.hpp>
#include <ql/termstructures/volatility/fx/blackvolsurfacedelta.hpp>
#include <ql/experimental/fx/deltavolquote.hpp>
#include <ql/experimental/fx/blackdeltacalculator.hpp>


namespace QuantLib {
    class Calendar;
    class Matrix;
    class Period;

    class BlackVolatilityTermStructure;
    class BlackVolatilitySurfaceDelta;
}

namespace QuantLibAddin {


    class BlackVolatilitySurfaceDelta : public BlackVolTermStructure {
    public:
        BlackVolatilitySurfaceDelta(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::Date referenceDate,
            const std::vector<QuantLib::Date>& dates,
            const std::vector<QuantLib::Real>& putDeltas,
            const std::vector<QuantLib::Real>& callDeltas,
            bool hasAtm,
            const QuantLib::Matrix& vols,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Calendar& cal,
            const QuantLib::Handle<QuantLib::Quote>& spot,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& domesticTS,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& foreignTS,
            const std::vector<QuantLib::DeltaVolQuote::DeltaType>& dt,
            const std::vector<QuantLib::DeltaVolQuote::AtmType>& at,
            const QuantLib::Period& switchTenor,
            QuantLib::InterpolatedSmileSection::InterpolationMethod interpolationMethod,
            bool flatExtrapolation,
            bool permanent = true);
    };


    class BlackDeltaCalculator : public ObjectHandler::LibraryObject<QuantLib::BlackDeltaCalculator> {
    public:
        BlackDeltaCalculator(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Option::Type& ot,
            const QuantLib::DeltaVolQuote::DeltaType& dt,
            const QuantLib::Real& spot,
            const QuantLib::Real& domesticDF,
            const QuantLib::Real& foreignDF,
            const QuantLib::Real& stdDev,
            bool permanent);
     };

    
}

#endif
