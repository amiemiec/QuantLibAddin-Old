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

#ifndef qla_cmsrangeaccrual_hpp
#define qla_cmsrangeaccrual_hpp

#include <oh/libraryobject.hpp>
#include<qlo/index.hpp>
#include <ql/types.hpp>

#include <qlo/leg.hpp>
#include <ql/time/businessdayconvention.hpp>

namespace QuantLib {
    class Date;
    class Index;
    class SwapIndex;
    class Schedule;
    class YieldTermStructure;
    class Calendar;
    class Quote;
    class SwaptionVolatilityStructure;
    class CmsRangeAccrualFixedCouponPricer;
    class CmsRangeAccrualFixedCoupon;
    class CmsCouponPricer;
    class DayCounter;
    class Date;

    template <class T>
    class Handle;
}

namespace QuantLibAddin {

/*
    class CmsRangeAccrualFixedCouponPricer1: public ObjectHandler::LibraryObject<QuantLib::CmsRangeAccrualFixedCouponPricer> {
    public:
        CmsRangeAccrualFixedCouponPricer1(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> swptnVolatility,
        bool permanent);
    };
    */
    
    class CmsRangeAccrualFixedCouponPricer : public ObjectHandler::LibraryObject<QuantLib::CmsRangeAccrualFixedCouponPricer> {
    public:
        CmsRangeAccrualFixedCouponPricer(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::CmsCouponPricer>& cmsPricer,
            bool permanent);
    };
    



    class CmsRangeAccrualFixedCoupon : public ObjectHandler::LibraryObject<QuantLib::CmsRangeAccrualFixedCoupon> {
    public:
        CmsRangeAccrualFixedCoupon(
            // FixedRateCoupon
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Date& paymentDate,
            QuantLib::Real nominal,
            QuantLib::Real rate,
            const QuantLib::DayCounter& dayCounter,
            const QuantLib::Date& accrualStartDate,
            const QuantLib::Date& accrualEndDate,
            // RA feature
            // calculate observation schedule from coupon
            const boost::shared_ptr<QuantLib::SwapIndex>& swapIndex,
            QuantLib::Real lowerTrigger,
            QuantLib::Real upperTrigger,
            QuantLib::Natural lockout,
            // optional FixedRateCoupon
            const QuantLib::Date& refPeriodStart,
            const QuantLib::Date& refPeriodEnd,
            const QuantLib::Date& exCouponDate,
            bool permanent);
    };


    class CmsRangeAccrualLeg : public Leg {
    public:
        CmsRangeAccrualLeg(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::BusinessDayConvention paymentConvention,
            const QuantLib::DayCounter& paymentDayCounter,
            const std::vector<QuantLib::Real>& nominals,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            const std::vector<QuantLib::Rate>& fixedRates,
            const boost::shared_ptr<QuantLib::SwapIndex>& index,
            const std::vector<QuantLib::Natural>& fixingDays,
            const std::vector<QuantLib::Rate>& lowerTriggers,
            const std::vector<QuantLib::Rate>& upperTriggers,
            const std::vector<QuantLib::Natural>& observationsLockouts,
            const boost::shared_ptr<QuantLib::CmsRangeAccrualFixedCouponPricer>& pricer,
            bool permanent);
    };


}

#endif
