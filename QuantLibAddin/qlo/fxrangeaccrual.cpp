/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
* 
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

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <qlo/fxrangeaccrual.hpp>

#include <ql/indexes/fxindex.hpp>
#include <ql/timeseries.hpp>
#include <ql/indexes/equityindex.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/cashflows/fxrangeaccrualfixed.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/time/date.hpp>

namespace QuantLibAddin {



 FxIndex::FxIndex(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                  std::string name,
                  QuantLib::Calendar fixingCalendar,
                  QuantLib::Handle<QuantLib::YieldTermStructure> domInterest,
                  QuantLib::Handle<QuantLib::YieldTermStructure> forInterest,
                  QuantLib::Handle<QuantLib::Quote> spot,
                  bool permanent): EquityIndex(properties, permanent) {


    libraryObject_ = boost::shared_ptr<QuantLib::FxIndex>(new QuantLib::FxIndex(name,
                                                                    fixingCalendar,
                                                                    domInterest,
                                                                    forInterest,
                                                                    spot));
    
    
}



 FxRangeAccrualFixedCouponPricer::FxRangeAccrualFixedCouponPricer(
     const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
     QuantLib::Handle<QuantLib::BlackVolTermStructure> fxVolatility,
     bool permanent) : LibraryObject<QuantLib::FxRangeAccrualFixedCouponPricer>(properties, permanent)
 {

     libraryObject_ = boost::shared_ptr<QuantLib::FxRangeAccrualFixedCouponPricer>(new QuantLib::FxRangeAccrualFixedCouponPricer(fxVolatility));

 }



FxRangeAccrualFixedCoupon::FxRangeAccrualFixedCoupon(
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
         const boost::shared_ptr<QuantLib::FxIndex>& fxIndex,
         QuantLib::Real lowerTrigger,
         QuantLib::Real upperTrigger,
         QuantLib::Natural lookback,
         // optional FixedRateCoupon
         const QuantLib::Date& refPeriodStart,
         const QuantLib::Date& refPeriodEnd,
         const QuantLib::Date& exCouponDate,
         bool permanent) : LibraryObject<QuantLib::FxRangeAccrualFixedCoupon>(properties, permanent)
     {
    
        libraryObject_ = boost::shared_ptr<QuantLib::FxRangeAccrualFixedCoupon>(new QuantLib::FxRangeAccrualFixedCoupon(
            paymentDate,
            nominal,
            rate,
            dayCounter,
            accrualStartDate,
            accrualEndDate,
            fxIndex,
            lowerTrigger,
            upperTrigger,
            lookback,
            refPeriodStart,
            refPeriodEnd,
            exCouponDate
        ));
        
     }
 
    FxRangeAccrualLeg::FxRangeAccrualLeg(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        QuantLib::BusinessDayConvention paymentConvention,
        const QuantLib::DayCounter& paymentDayCounter,
        const std::vector<QuantLib::Real>& nominals,
        const boost::shared_ptr<QuantLib::Schedule>& schedule,
        const std::vector<QuantLib::Rate>& fixedRates,
        const boost::shared_ptr<QuantLib::FxIndex>& index,
        const std::vector<QuantLib::Natural>& fixingDays,
        const std::vector<QuantLib::Rate>& lowerTriggers,
        const std::vector<QuantLib::Rate>& upperTriggers,
        const std::vector<QuantLib::Natural>& observationsShifters,
        const boost::shared_ptr<QuantLib::FxRangeAccrualFixedCouponPricer>& pricer,
        bool permanent) : Leg(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::Leg>(new QuantLib::Leg(QuantLib::FxRangeAccrualLeg(*schedule, index, pricer)
            .withNotionals(nominals)
            .withPaymentAdjustment(paymentConvention)
            .withPaymentDayCounter(paymentDayCounter)
            .withFixedRates(fixedRates)
            .withFixingDays(fixingDays)
            .withLowerTriggers(lowerTriggers)
            .withUpperTriggers(upperTriggers)
            .withObservationShifters(observationsShifters)));
    }



}