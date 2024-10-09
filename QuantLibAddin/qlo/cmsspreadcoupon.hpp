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

#ifndef qla_cmsspreadcoupon_hpp
#define qla_cmsspreadcoupon_hpp

#include <qlo/leg.hpp>

#include <ql/time/businessdayconvention.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <qlo/couponvectors.hpp>
#include <qlo/indexes/interestrateindex.hpp>


namespace QuantLib {
    class Schedule;
    class IborIndex;
    class DayCounter;
    class SwapIndex;
    class SwapSpreadIndex;
    class OptionletVolatilityStructure;

    template <class T>
    class Handle;
}

namespace QuantLibAddin {


    class SwapSpreadIndex : public InterestRateIndex {
    public:
        SwapSpreadIndex::SwapSpreadIndex(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& familyName,
            const boost::shared_ptr<QuantLib::SwapIndex>& swapIndex1,
            const boost::shared_ptr<QuantLib::SwapIndex>& swapIndex2,
            QuantLib::Real gearing1,
            QuantLib::Real gearing2,
            bool permanent);
    protected:
        OH_OBJ_CTOR(SwapSpreadIndex, InterestRateIndex);
    };




    class CmsSpreadLeg : public Leg {
    public:
        CmsSpreadLeg(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::BusinessDayConvention paymentConvention,
            const std::vector<QuantLib::Real>& nominals,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            const std::vector<QuantLib::Natural>& fixingDays,
            bool isInArrears,
            const QuantLib::DayCounter& paymentDayCounter,
            const std::vector<QuantLib::Rate>& floors,
            const std::vector<QuantLib::Real>& gearings,
            const boost::shared_ptr<QuantLib::SwapSpreadIndex>& index,
            const std::vector<QuantLib::Spread>& spreads,
            const std::vector<QuantLib::Rate>& caps,
            bool permanent);
    };



    class LogNormalCmsSpreadPricer : public FloatingRateCouponPricer {
    public:
        LogNormalCmsSpreadPricer(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::CmsCouponPricer>& cmsPricer,
            const QuantLib::Handle<QuantLib::Quote>& correlation,
            QuantLib::Handle<QuantLib::YieldTermStructure> couponDiscountCurve,
            QuantLib::Size integrationPoints,
            const QuantLib::VolatilityType volType,
            QuantLib::Real shift1,
            QuantLib::Real shift2,
            bool permanent);
    };


    
    


}

#endif
