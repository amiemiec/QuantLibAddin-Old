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

#include <qlo/seasonality.hpp>

#include <ql/time/date.hpp>
#include <ql/termstructures/inflation/seasonality.hpp>
//#include <ql/termstructures/inflation/interpolatedzeroinflationcurve.hpp>
//#include <ql/termstructures/inflation/interpolatedyoyinflationcurve.hpp>
//#include <ql/math/interpolations/all.hpp>

#include <boost/algorithm/string/case_conv.hpp>

using boost::algorithm::to_upper_copy;

namespace QuantLibAddin {



    MultiplicativePriceSeasonality::MultiplicativePriceSeasonality(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            /*const QuantLib::Date& seasonalityBaseDate,*/
            QuantLib::Frequency frequency,
            const std::vector<QuantLib::Rate>& seasonalityFactors,
            bool permanent) : Seasonality(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::Seasonality>(new
            QuantLib::MultiplicativePriceSeasonality(/*seasonalityBaseDate,*/ frequency, seasonalityFactors));
    };

    
    KerkhofSeasonality::KerkhofSeasonality(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Date& seasonalityBaseDate,
            const std::vector<QuantLib::Rate>& seasonalityFactors,
            bool permanent) : Seasonality(properties, permanent) /*MultiplicativePriceSeasonality(properties, seasonalityBaseDate, QuantLib::Monthly, seasonalityFactors, permanent)*/

    {
        libraryObject_ = boost::shared_ptr<QuantLib::Seasonality>(new
            QuantLib::KerkhofSeasonality(seasonalityBaseDate,seasonalityFactors));
    };
    


}
