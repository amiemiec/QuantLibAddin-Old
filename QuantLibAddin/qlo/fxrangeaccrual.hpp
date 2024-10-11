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

#ifndef qla_fxindex_hpp
#define qla_fxindex_hpp

#include <oh/libraryobject.hpp>
#include<qlo/index.hpp>
#include <ql/types.hpp>

namespace QuantLib {
    class Date;
    class Index;
    class EquityIndex;
    class FxIndex;
    class YieldTermStructure;
    class Calendar;
    class Quote;
    class BlackVolTermStructure;
    class FxRangeAccrualFixedCouponPricer;
    class FxRangeAccrualFixedCoupon;
    class DayCounter;
    class Date;

    template <class T>
    class Handle;
}

namespace QuantLibAddin {

    OH_OBJ_CLASS(EquityIndex,Index);

    class FxIndex : public EquityIndex {
    public:
        FxIndex(const boost::shared_ptr<ObjectHandler::ValueObject>& properties, 
                std::string name,
                QuantLib::Calendar fixingCalendar,
                QuantLib::Handle<QuantLib::YieldTermStructure> domInterest,
                QuantLib::Handle<QuantLib::YieldTermStructure> forInterest,
                QuantLib::Handle<QuantLib::Quote> spot,
                bool permanent);
    };



    class FxRangeAccrualFixedCouponPricer: public ObjectHandler::LibraryObject<QuantLib::FxRangeAccrualFixedCouponPricer> {
    public:
        FxRangeAccrualFixedCouponPricer(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        QuantLib::Handle<QuantLib::BlackVolTermStructure> fxVolatility,
        bool permanent);
    };

    class FxRangeAccrualFixedCoupon : public ObjectHandler::LibraryObject<QuantLib::FxRangeAccrualFixedCoupon> {
    public:
        FxRangeAccrualFixedCoupon(
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
            // optional FixedRateCoupon
            const QuantLib::Date& refPeriodStart,
            const QuantLib::Date& refPeriodEnd,
            const QuantLib::Date& exCouponDate,
            bool permanent);
    };


}

#endif
