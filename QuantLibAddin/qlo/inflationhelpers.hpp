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


#ifndef qla_inflation_helper_hpp
#define qla_inflation_helper_hpp

#include <ql/types.hpp>
#include <ql/time/businessdayconvention.hpp>
#include <ql/time/frequency.hpp>

#include <ql/indexes/inflationindex.hpp>
#include <qlo/inflationtermstructures.hpp>


//AMI++
#include <qlo/swap.hpp>
#include <ql/termstructures/inflation/inflationhelpers.hpp>
//++AMI

namespace QuantLib {

    class InflationTermStructure;
    class ZeroInflationTermStructure;

    template<class TS>
    class BootstrapHelper;

    typedef BootstrapHelper<ZeroInflationTermStructure> InflationZeroHelper;
	
    template<class TS>
    class RelativeDateBootstrapHelper;

    //typedef RelativeDateBootstrapHelper<ZeroInflationTermStructure> RelativeDateInflationHelper;
    
    
    class Quote;
    class Period;
    class Calendar;
    class DayCounter;
    class IborIndex;
    class OvernightIndex;
    class SwapIndex;
    class Schedule;
    class Date;
    class Bond;
    template <class T>
    class Handle;

}

namespace QuantLibAddin {

    class InflationZeroHelper : public ObjectHandler::LibraryObject<QuantLib::InflationZeroHelper> {
    public:
        std::string quoteName() { return quoteName_; }
    protected:
        OH_LIB_CTOR(InflationZeroHelper, QuantLib::InflationZeroHelper);
        std::string quoteName_;
    };

    class ZeroCouponInflationSwapHelper: public InflationZeroHelper{
    public:
        ZeroCouponInflationSwapHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::Quote>& quote,
        const QuantLib::Period& swapObsLag, // lag on swap observation of index
        const QuantLib::Date& maturity,
        QuantLib::Calendar calendar, // index may have null calendar as valid on every day
        QuantLib::BusinessDayConvention paymentConvention,
        QuantLib::DayCounter dayCounter,
        boost::shared_ptr<QuantLib::ZeroInflationIndex> zii,
        QuantLib::CPI::InterpolationType observationInterpolation,
        QuantLib::Handle<QuantLib::YieldTermStructure> nominalTermStructure,
        bool permanent);
    };


    class ZeroCouponInflationSwap : public Swap {
    public:
        ZeroCouponInflationSwap(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::ZeroCouponInflationSwapHelper>& swapRH,
            bool permanent);
    };

}

#endif
