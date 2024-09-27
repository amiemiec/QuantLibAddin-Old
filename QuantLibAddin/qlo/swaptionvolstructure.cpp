/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2006 Silvia Frasson
 Copyright (C) 2006 Mario Pucci
 Copyright (C) 2006, 2007 Giorgio Facchinetti

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

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <qlo/swaptionvolstructure.hpp>

#include <ql/termstructures/volatility/swaption/swaptionconstantvol.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolcube.hpp>
#include <ql/termstructures/volatility/swaption/interpolatedswaptionvolatilitycube.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolmatrix.hpp>
#include <ql/termstructures/volatility/swaption/spreadedswaptionvol.hpp>
#include <ql/math/optimization/endcriteria.hpp>
#include <ql/time/calendars/nullcalendar.hpp>

namespace QuantLibAddin {

    ConstantSwaptionVolatility::ConstantSwaptionVolatility(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        QuantLib::Natural settlementDays,
        const QuantLib::Calendar& cal,
        QuantLib::BusinessDayConvention bdc,
        const QuantLib::Handle<QuantLib::Quote>& vol,
        const QuantLib::DayCounter& dayCounter,
        bool permanent)
    : SwaptionVolatilityStructure(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::Extrapolator>(new
            QuantLib::ConstantSwaptionVolatility(settlementDays,
                                                 cal,
                                                 bdc,
                                                 vol,
                                                 dayCounter));
    }

    SpreadedSwaptionVolatility::SpreadedSwaptionVolatility(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>& underlyingVolStructure,
            const QuantLib::Handle<QuantLib::Quote>& spread,
            bool permanent)
    : SwaptionVolatilityStructure(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::Extrapolator>(new
            QuantLib::SpreadedSwaptionVolatility(underlyingVolStructure,
                                                 spread));
    }

    SwaptionVolatilityMatrix::SwaptionVolatilityMatrix(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Calendar& calendar,
            const QuantLib::BusinessDayConvention bdc,
            const std::vector<QuantLib::Period>& optionTenors,
            const std::vector<QuantLib::Period>& swapTenors,
            const std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& vols,
            const QuantLib::DayCounter& dayCounter,
            bool permanent)
    : SwaptionVolatilityDiscrete(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::Extrapolator>(new
            QuantLib::SwaptionVolatilityMatrix(calendar,
                                               bdc,
                                               optionTenors,
                                               swapTenors,
                                               vols,
                                               dayCounter));
    }

    std::vector<long> SwaptionVolatilityMatrix::locate(
                                                const QuantLib::Date& d,
                                                const QuantLib::Period& p) {
        std::pair<QuantLib::Size, QuantLib::Size> indexes =
            boost::dynamic_pointer_cast<QuantLib::SwaptionVolatilityMatrix>(
                libraryObject_)->locate(d,p);
        std::vector<long> result(2);
        result[0]=indexes.first;
        result[1]=indexes.second;
        return result;
    }

    InterpolatedSwaptionVolCube::InterpolatedSwaptionVolCube(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>& atmVol,
        const std::vector<QuantLib::Period>& optionTenors,
        const std::vector<QuantLib::Period>& swapTenors,
        const std::vector<QuantLib::Spread>& strikeSpreads,
        const std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& volSpreads,
        const boost::shared_ptr<QuantLib::SwapIndex>& swapIndexBase,
        const boost::shared_ptr<QuantLib::SwapIndex>& shortSwapIndexBase,
        bool vegaWeightedSmileFit,
        bool permanent) : SwaptionVolatilityStructure(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::Extrapolator>(new
            QuantLib::InterpolatedSwaptionVolatilityCube(atmVol,
                                       optionTenors,
                                       swapTenors,
                                       strikeSpreads,
                                       volSpreads,
                                       swapIndexBase,
                                       shortSwapIndexBase,
                                       vegaWeightedSmileFit));
    }


    SmileSectionByCube::SmileSectionByCube(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::SwaptionVolatilityCube>& cube,
            const QuantLib::Period& optionTenor,
            const QuantLib::Period& swapTenors,
            bool permanent) : SmileSection(properties, permanent) {
             libraryObject_ = cube->smileSection(optionTenor,swapTenors);
    }

    SmileSectionByCube::SmileSectionByCube(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::SwaptionVolatilityCube>& cube,
            const QuantLib::Date& optionDate,
            const QuantLib::Period& swapTenors,
            bool permanent) : SmileSection(properties, permanent) {
             libraryObject_ = cube->smileSection(optionDate,swapTenors);
    }

}
