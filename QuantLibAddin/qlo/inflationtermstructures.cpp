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

#ifdef HAVE_CONFIG_H
#include <qlo/config.hpp>
#endif

//#include <qlo/yieldtermstructures.hpp>
#include <qlo/inflationtermstructures.hpp>
#include <qlo/inflationhelpers.hpp>

#include <ql/time/date.hpp>
#include <ql/termstructures/inflation/seasonality.hpp>
#include <ql/termstructures/inflation/interpolatedzeroinflationcurve.hpp>
#include <ql/termstructures/inflation/interpolatedyoyinflationcurve.hpp>
#include <ql/termstructures/inflation/seasonality.hpp>

#include <ql/math/interpolations/all.hpp>

#include <boost/algorithm/string/case_conv.hpp>

using boost::algorithm::to_upper_copy;
using boost::shared_ptr;
using ObjectHandler::ValueObject;



namespace QuantLibAddin {


    InterpolatedZeroInflationCurve::InterpolatedZeroInflationCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Date& referenceDate,
        std::vector<QuantLib::Date> dates,
        const std::vector<QuantLib::Rate>& rates,
        QuantLib::Frequency frequency,
        const QuantLib::DayCounter& dayCounter,
        const std::string& traitsID,
        const std::string& interpolatorID,
        const boost::shared_ptr<QuantLib::Seasonality>& seasonality,
        bool permanent) :ZeroInflationTermStructure(properties, permanent), interpolatorID_(boost::algorithm::to_upper_copy(interpolatorID)), traitsID_(boost::algorithm::to_upper_copy(traitsID)) {

        if (traitsID_ == "ZEROINFLATION") {
            if (interpolatorID_ == "BACKWARDFLAT") {
                libraryObject_ = shared_ptr<QuantLib::Extrapolator>(new
                    QuantLib::InterpolatedZeroInflationCurve<QuantLib::BackwardFlat>( referenceDate,
                                                                            dates,
                                                                            rates,
                                                                            frequency,
                                                                            dayCounter,
                                                                            seasonality));
            }
            else if (interpolatorID_ == "FORWARDFLAT") {
                libraryObject_ = shared_ptr<QuantLib::Extrapolator>(new
                    QuantLib::InterpolatedZeroInflationCurve<QuantLib::ForwardFlat>(referenceDate,
                        dates,
                        rates,
                        frequency,
                        dayCounter,
                        seasonality));
            }
            else if (interpolatorID_ == "LINEAR") {
                libraryObject_ = shared_ptr<QuantLib::Extrapolator>(new
                    QuantLib::InterpolatedZeroInflationCurve<QuantLib::Linear>(referenceDate,
                        dates,
                        rates,
                        frequency,
                        dayCounter,
                        seasonality));
            }
            else if (interpolatorID_ == "LOGLINEAR") {
                libraryObject_ = shared_ptr<QuantLib::Extrapolator>(new
                    QuantLib::InterpolatedZeroInflationCurve<QuantLib::LogLinear>(referenceDate,
                        dates,
                        rates,
                        frequency,
                        dayCounter,
                        seasonality));
            }
            else {
                QL_FAIL("unknown interpolatorID: " << interpolatorID_);
            }
        }
        else if (traitsID_ == "YOY") {
            QL_FAIL("YoY not implemented yet");
        }
        else {
            QL_FAIL("not implemented yet");
        }
    
    };




#define RESOLVE_TEMPLATE(NAME) \
        if (traitsID_=="ZERO") { \
            if (interpolatorID_=="BACKWARDFLAT") { \
                return boost::dynamic_pointer_cast<QuantLib::InterpolatedZeroInflationCurve<QuantLib::BackwardFlat> > (libraryObject_)->NAME(); \
            } else if (interpolatorID_=="FORWARDFLAT") { \
                return boost::dynamic_pointer_cast<QuantLib::InterpolatedZeroInflationCurve<QuantLib::ForwardFlat> >(libraryObject_)->NAME(); \
            } else if (interpolatorID_=="LINEAR") { \
                return boost::dynamic_pointer_cast<QuantLib::InterpolatedZeroInflationCurve<QuantLib::Linear> >(libraryObject_)->NAME(); \
            } else if (interpolatorID_=="LOGLINEAR") { \
                return boost::dynamic_pointer_cast<QuantLib::InterpolatedZeroInflationCurve<QuantLib::LogLinear> > (libraryObject_)->NAME(); \
            } else \
                QL_FAIL("unknown interpolatorID: " << interpolatorID_); \
        } else if (traitsID_=="YoY") { \
                QL_FAIL("unknown interpolatorID: " << interpolatorID_); \
        } else \
            QL_FAIL("unknown traitsID: " << traitsID_);

  


    const std::vector<QuantLib::Date>& InterpolatedZeroInflationCurve::dates() const {
        RESOLVE_TEMPLATE(dates)
    }

    const std::vector<QuantLib::Real>& InterpolatedZeroInflationCurve::data() const {
        RESOLVE_TEMPLATE(data)
    }





}
