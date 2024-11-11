/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2006 Katiuscia Manzoni
 Copyright (C) 2005 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov

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

#include <qlo/cmsrangeaccrual.hpp>

#include <ql/indexes/swapindex.hpp>
#include <ql/timeseries.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/cashflows/cmsrangeaccrualfixed.hpp>
#include <ql/cashflows/conundrumpricer.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/time/date.hpp>

namespace QuantLibAddin {




/*
 CmsRangeAccrualFixedCouponPricer1::CmsRangeAccrualFixedCouponPricer1(
     const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
     QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> swptnVolatility,
     bool permanent) : LibraryObject<QuantLib::CmsRangeAccrualFixedCouponPricer>(properties, permanent)
 {

     libraryObject_ = boost::shared_ptr<QuantLib::CmsRangeAccrualFixedCouponPricer>(new QuantLib::CmsRangeAccrualFixedCouponPricer(swptnVolatility));

 }
 */

 
 CmsRangeAccrualFixedCouponPricer::CmsRangeAccrualFixedCouponPricer(
     const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
     const boost::shared_ptr<QuantLib::CmsCouponPricer>& cmsPricer,
     bool permanent) : LibraryObject<QuantLib::CmsRangeAccrualFixedCouponPricer>(properties, permanent)
 {

     libraryObject_ = boost::shared_ptr<QuantLib::CmsRangeAccrualFixedCouponPricer>(new QuantLib::CmsRangeAccrualFixedCouponPricer(cmsPricer));

 }
 




CmsRangeAccrualFixedCoupon::CmsRangeAccrualFixedCoupon(
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
         const boost::shared_ptr<QuantLib::SwapIndex>& cmsIndex,
         QuantLib::Real lowerTrigger,
         QuantLib::Real upperTrigger,
         // optional FixedRateCoupon
         const QuantLib::Date& refPeriodStart,
         const QuantLib::Date& refPeriodEnd,
         const QuantLib::Date& exCouponDate,
         bool permanent) : LibraryObject<QuantLib::CmsRangeAccrualFixedCoupon>(properties, permanent)
     {
    
        libraryObject_ = boost::shared_ptr<QuantLib::CmsRangeAccrualFixedCoupon>(new QuantLib::CmsRangeAccrualFixedCoupon(
            paymentDate,
            nominal,
            rate,
            dayCounter,
            accrualStartDate,
            accrualEndDate,
            cmsIndex,
            lowerTrigger,
            upperTrigger,
            refPeriodStart,
            refPeriodEnd,
            exCouponDate
        ));
        
     }
 



}