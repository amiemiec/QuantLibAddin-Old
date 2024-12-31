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


#ifndef qla_inflation_seasonality_hpp
#define qla_inflation_seasonality_hpp

#include <qlo/termstructures.hpp>

#include <ql/time/frequency.hpp>
#include <ql/compounding.hpp>
#include <ql/types.hpp>

namespace QuantLib {
    class Calendar;
    class DayCounter;
    class Date;
    class Quote;
    class Seasonality;

    template<class TS>
    class BootstrapHelper;

    typedef BootstrapHelper<InflationTermStructure> InflationHelper;

    template <class T>
    class Handle;
}

namespace QuantLibAddin {
     
    OH_LIB_CLASS(Seasonality,QuantLib::Seasonality);


    class MultiplicativePriceSeasonality: public Seasonality {
    public:
        MultiplicativePriceSeasonality( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                        const QuantLib::Date& seasonalityBaseDate,
                                        QuantLib::Frequency frequency,
                                        const std::vector<QuantLib::Rate>& seasonalityFactors,
                                        bool permanent);
    };

    
    class KerkhofSeasonality: public Seasonality/*MultiplicativePriceSeasonality*/ {
    public:
        KerkhofSeasonality( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                            const QuantLib::Date& seasonalityBaseDate,
                            const std::vector<QuantLib::Rate>& seasonalityFactors,
                            bool permanent);
        
    };



}

#endif
