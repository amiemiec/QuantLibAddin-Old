/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2024 André Miemiec

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


#include <qlo/qladdindefines.hpp>
#include <qlo/inflationhelpers.hpp>
#include <ql/termstructures/inflation/inflationhelpers.hpp>


namespace QuantLibAddin {


    ZeroCouponInflationSwapHelper::ZeroCouponInflationSwapHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::Quote>& quote,
        const QuantLib::Natural spot,
        const QuantLib::Period& swapObsLag, // lag on swap observation of index
        const QuantLib::Period& swapTerm,
        QuantLib::Calendar calendar, // index may have null calendar as valid on every day
        QuantLib::BusinessDayConvention paymentConvention,
        QuantLib::DayCounter dayCounter,
        boost::shared_ptr<QuantLib::ZeroInflationIndex> zii,
        QuantLib::CPI::InterpolationType observationInterpolation,
        QuantLib::Handle<QuantLib::YieldTermStructure> nominalTermStructure,
        bool permanent) : InflationZeroHelper(properties, permanent) 
    {
        //QL_FAIL(!(observationInterpolation == QuantLib::CPI::Flat), "Not validated");
        
        libraryObject_ = boost::shared_ptr<QuantLib::InflationZeroHelper>(new
            QuantLib::ZeroCouponInflationSwapHelper(
                quote,
                spot,
                swapObsLag, // lag on swap observation of index
                swapTerm,
                calendar, // index may have null calendar as valid on every day
                paymentConvention,
                dayCounter,
                zii,
                observationInterpolation,
                nominalTermStructure));
        
    }

    ZeroCouponInflationSwap::ZeroCouponInflationSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::ZeroCouponInflationSwapHelper>& swapRH,
        bool permanent) : Swap(properties, permanent)
    {
        libraryObject_ = swapRH->swap();
    }


}
