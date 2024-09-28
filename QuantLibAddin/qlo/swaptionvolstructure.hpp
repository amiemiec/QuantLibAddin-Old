/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2010 Ferdinando Ametrano
 Copyright (C) 2006 Silvia Frasson
 Copyright (C) 2006 Mario Pucci
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 Copyright (C) 2007 Eric Ehlers

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

#ifndef qla_swaptionvolstructure_hpp
#define qla_swaptionvolstructure_hpp

#include <qlo/termstructures.hpp>
#include <qlo/smilesection.hpp>
#include <ql/time/businessdayconvention.hpp>

namespace QuantLib {
    class Calendar;
    class SwaptionVolatilityCube;
    class SwaptionVolatilityStructure;
    class SwapIndex;
    class Matrix;
    class Period;
    class Quote;
}

namespace QuantLibAddin {

    class ConstantSwaptionVolatility : public SwaptionVolatilityStructure {
      public:
        ConstantSwaptionVolatility(
                        const boost::shared_ptr<ObjectHandler::ValueObject>&,
                        QuantLib::Natural settlementDays,
                        const QuantLib::Calendar& cal,
                        QuantLib::BusinessDayConvention bdc,
                        const QuantLib::Handle<QuantLib::Quote>& vol,
                        const QuantLib::DayCounter& dayCounter,
                        bool permanent);
    };

    class SpreadedSwaptionVolatility : public SwaptionVolatilityStructure {
      public:
        SpreadedSwaptionVolatility(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>& underlyingVolStructure,
            const QuantLib::Handle<QuantLib::Quote>&,
            bool permanent);
    };
        
    class SwaptionVolatilityMatrix : public SwaptionVolatilityDiscrete {
      public:
        SwaptionVolatilityMatrix(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                 const QuantLib::Calendar& calendar,
                                 const QuantLib::BusinessDayConvention bdc,
                                 const std::vector<QuantLib::Period>& optionTenors,
                                 const std::vector<QuantLib::Period>& tenors,
                                 const std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& vols,
                                 const QuantLib::DayCounter& dayCounter,
                                 const bool flatExtrapolation,
                                 const QuantLib::VolatilityType volType,
                                 const std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& shifts,
                                 bool permanent);
        std::vector<long> locate(const QuantLib::Date& d,
                                 const QuantLib::Period& p);
    };
    
    
    
    class InterpolatedSwaptionVolCube : public SwaptionVolatilityStructure {
      public:
        InterpolatedSwaptionVolCube(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>& atmVol,
            const std::vector<QuantLib::Period>& optionTenors,
            const std::vector<QuantLib::Period>& swapTenors,
            const std::vector<QuantLib::Spread>& strikeSpreads,
            const std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& volSpreads,
            const boost::shared_ptr<QuantLib::SwapIndex>& swapIndexBase,
            const boost::shared_ptr<QuantLib::SwapIndex>& shortSwapIndexBase,
            bool vegaWeightedSmileFit,
            bool permanent);
    };

    class SmileSectionByCube : public SmileSection {
      public:
        SmileSectionByCube(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::SwaptionVolatilityCube>& cube,
            const QuantLib::Period& optionTenors,
            const QuantLib::Period& swapTenors,
            bool permanent);
        SmileSectionByCube(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::SwaptionVolatilityCube>& cube,
            const QuantLib::Date& optionDate,
            const QuantLib::Period& swapTenors,
            bool permanent);
    };
    
}

#endif
