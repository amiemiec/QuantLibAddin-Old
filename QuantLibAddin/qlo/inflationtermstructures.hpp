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

#ifndef qla_inflationtermstructures_hpp
#define qla_inflationtermstructures_hpp

#include <qlo/termstructures.hpp>   //ok

#include <ql/time/frequency.hpp>
#include <ql/compounding.hpp>
#include <ql/types.hpp>
#include <ql/math/interpolation.hpp>



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

    
       OH_OBJ_CLASS(ZeroInflationTermStructure,InflationTermStructure);


       class InterpolatedZeroInflationCurve : public ZeroInflationTermStructure {
       public:
           enum Traits {
               ZeroInflation,
               YoYInflation
           };
           enum Interpolator {
               BackwardFlat,
               ForwardFlat,
               Linear,
               LogLinear
           };
           InterpolatedZeroInflationCurve(
               const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
               const QuantLib::Date& referenceDate,
               std::vector<QuantLib::Date> dates,
               const std::vector<QuantLib::Rate>& rates,
               QuantLib::Frequency frequency,
               const QuantLib::DayCounter& dayCounter,
               const std::string& traitsID,
               const std::string& interpolatorID,
               const boost::shared_ptr<QuantLib::Seasonality>& seasonality,
               bool permanent);

           const std::vector<QuantLib::Date>& dates() const;
           const std::vector<QuantLib::Real>& data() const;

       protected:
           const std::string& traitsID_;
           const std::string& interpolatorID_;
       };



       // A pair indicating a combination of Traits / Interpolator.
       typedef std::pair<InterpolatedZeroInflationCurve::Traits, InterpolatedZeroInflationCurve::Interpolator> InterpolatedInflationCurvePair;

       // Stream operator to write a InterpolatedInflationCurvePair to a stream - for logging / error handling.
       std::ostream& operator<<(std::ostream& out,
           InterpolatedInflationCurvePair tokenPair);


}

#endif
