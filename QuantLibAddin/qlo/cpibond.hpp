/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2025 Andre Miemiec

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

#ifndef qla_cpibond_hpp
#define qla_cpibond_hpp

#include <qlo/bonds.hpp>
#include <qlo/quote.hpp>

#include <ql/types.hpp>
#include <ql/time/businessdayconvention.hpp>
#include <ql/time/frequency.hpp>
#include <ql/indexes/inflationindex.hpp>

namespace QuantLib {
    class CPIBond;
    class BTPItalia;

    template <class T>
    class Handle;
    class Quote;
    class Schedule;

}

namespace QuantLibAddin {


    class CPIBond : public Bond {
      public:
        CPIBond(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& des,
            QuantLib::Natural settlementDays,
            QuantLib::Real faceAmount,
            bool growthOnly,
            QuantLib::Real baseCPI,
            const QuantLib::Period& observationLag,
            boost::shared_ptr<QuantLib::ZeroInflationIndex> cpiIndex,
            QuantLib::CPI::InterpolationType observationInterpolation,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            const std::vector<QuantLib::Rate>& coupons,
            const QuantLib::DayCounter& accrualDayCounter,
            QuantLib::BusinessDayConvention paymentConvention,
            const QuantLib::Date& issueDate,
            const QuantLib::Calendar& paymentCalendar,
            bool permanent);
    };


    class BTPItalia : public Bond {
    public:
        BTPItalia(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& des,
            QuantLib::Natural settlementDays,
            QuantLib::Real faceAmount,
            const QuantLib::Period& observationLag,
            boost::shared_ptr<QuantLib::ZeroInflationIndex> cpiIndex,
            QuantLib::CPI::InterpolationType observationInterpolation,
            const boost::shared_ptr<QuantLib::Schedule>& schedule,
            const std::vector<QuantLib::Rate>& coupons,
            const QuantLib::DayCounter& accrualDayCounter,
            QuantLib::BusinessDayConvention paymentConvention,
            const QuantLib::Date& issueDate,
            const QuantLib::Calendar& paymentCalendar,
            bool permanent);
    };

}

#endif
