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

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <qlo/fxvolstructure.hpp>

namespace QuantLibAddin {


    BlackVolatilitySurfaceDelta::BlackVolatilitySurfaceDelta(
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
            bool permanent): BlackVolTermStructure(properties, permanent)
    {
        //QuantLib::Date referenceDate = QuantLib::Settings::instance().evaluationDate();
        QuantLib::DeltaVolQuote::DeltaType front_dt = dt[0];
        QuantLib::DeltaVolQuote::DeltaType rear_dt = dt[1];
        QuantLib::DeltaVolQuote::DeltaType front_atm_dt;
        QuantLib::DeltaVolQuote::DeltaType rear_atm_dt;

        dt[2] != 0 ? front_atm_dt = dt[2]: front_atm_dt = dt[0];
        dt[3] != 0 ? rear_atm_dt = dt[3]: rear_atm_dt = dt[1];

        QuantLib::DeltaVolQuote::AtmType front_at = at[0];
        QuantLib::DeltaVolQuote::AtmType rear_at = at[1];


        libraryObject_ = boost::shared_ptr<QuantLib::Extrapolator>(new
            QuantLib::BlackVolatilitySurfaceDelta(
                referenceDate,
                dates,
                putDeltas,
                callDeltas,
                hasAtm,
                vols,
                dayCounter,
                cal,
                spot,
                domesticTS,
                foreignTS,
                front_dt,
                front_at,
                front_atm_dt,
                switchTenor,
                rear_dt,
                rear_at,
                rear_atm_dt,
                interpolationMethod,
                true
                ));
    };

    BlackDeltaCalculator::BlackDeltaCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Option::Type& ot,
        const QuantLib::DeltaVolQuote::DeltaType& dt,
        const QuantLib::Real& spot,
        const QuantLib::Real& domesticDF,
        const QuantLib::Real& foreignDF,
        const QuantLib::Real& stdDev,
        bool permanent) : LibraryObject<QuantLib::BlackDeltaCalculator>(properties, permanent)
    {
        
        libraryObject_ = boost::shared_ptr<QuantLib::BlackDeltaCalculator>(new
                          QuantLib::BlackDeltaCalculator(ot,dt,spot, domesticDF, foreignDF,stdDev));
        
    };


}
