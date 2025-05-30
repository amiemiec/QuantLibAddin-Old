/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2025 André Miemiec

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

#include <qlo/cpibond.hpp>
#include <qlo/flowanalysis.hpp>

#include <ql/time/schedule.hpp>

#include <ql/instruments/bonds/cpibond.hpp>
#include <ql/instruments/bonds/btpitalia.hpp>

#include <ql/currencies/europe.hpp>
#include <ql/utilities/dataformatters.hpp>
#include <ql/indexes/inflationindex.hpp>

using std::vector;
using boost::shared_ptr;

namespace QuantLibAddin {


    CPIBond::CPIBond(const shared_ptr<ObjectHandler::ValueObject>& properties,
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
                    bool permanent)
    : Bond(properties, des, QuantLib::EURCurrency(), permanent)
    {
        
        qlBondObject_ = shared_ptr<QuantLib::CPIBond>(new
                QuantLib::CPIBond(settlementDays,
                faceAmount,
                growthOnly,
                baseCPI,
                observationLag,
                cpiIndex,
                observationInterpolation,
                *schedule,
                coupons,
                accrualDayCounter,
                paymentConvention,
                issueDate,
                paymentCalendar));
        libraryObject_ = qlBondObject_;
        if (description_.empty()) {
            std::ostringstream temp;
            temp << "CPIBonds ";
            temp << QuantLib::io::iso_date(qlBondObject_->maturityDate());
            description_ = temp.str();
        }
        
    }


    BTPItalia::BTPItalia(const shared_ptr<ObjectHandler::ValueObject>& properties,
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
        bool permanent)
        : Bond(properties, des, QuantLib::EURCurrency(), permanent)
    {

        qlBondObject_ = shared_ptr<QuantLib::BTPItalia>(new
            QuantLib::BTPItalia(settlementDays,
                faceAmount,
                observationLag,
                cpiIndex,
                observationInterpolation,
                *schedule,
                coupons,
                accrualDayCounter,
                paymentConvention,
                issueDate,
                paymentCalendar));
        libraryObject_ = qlBondObject_;
        if (description_.empty()) {
            std::ostringstream temp;
            temp << "BTPItalia ";
            temp << QuantLib::io::iso_date(qlBondObject_->maturityDate());
            description_ = temp.str();
        }

    }



}
