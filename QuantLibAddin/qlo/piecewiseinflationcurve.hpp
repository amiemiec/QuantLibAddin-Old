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

#ifndef qla_piecewise_inflationcurve_hpp
#define qla_piecewise_inflationcurve_hpp


#include <qlo/inflationtermstructures.hpp>
#include <ql/termstructures/inflation/inflationhelpers.hpp>

namespace QuantLib {

    class DayCounter;
    class Date;

    class InflationTermStructure;

    class PiecwiseZeroInflationCurve;

    typedef BootstrapHelper<ZeroInflationTermStructure> InflationZeroHelper;
}


namespace QuantLibAddin {
    
    //OH_LIB_CLASS(InflationTermStructure, QuantLib::InflationTermStructure);

    	          
	class PiecewiseZeroInflationCurve : public ZeroInflationTermStructure {
      public:
        PiecewiseZeroInflationCurve(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Date& referenceDate,
            const QuantLib::Date& baseDate,
            const QuantLib::Frequency& frequency,
            const QuantLib::DayCounter& dayCounter,
            const std::vector<boost::shared_ptr<QuantLib::InflationZeroHelper> > instruments,
            //const std::string& traitsID,
            const std::string& interpolatorID,
            bool permanent);

            const std::vector<QuantLib::Date>& dates() const;

            const std::vector<QuantLib::Real>& data() const;

        InterpolatedInflationCurvePair interpolatedInflationCurvePair() const {
            return pair_;
        }

    private:
        InterpolatedInflationCurvePair pair_;
        const std::string& traitsID_;
        const std::string& interpolatorID_;

    };

}

#endif
