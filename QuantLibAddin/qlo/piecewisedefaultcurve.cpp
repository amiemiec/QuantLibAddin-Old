/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2007 Eric Ehlers
 Copyright (C) 2007, 2008, 2009 Ferdinando Ametrano

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

#include <qlo/piecewisedefaultcurve.hpp>
#include <qlo/enumerations/factories/termstructuresfactory.hpp>

#include <ql/termstructures/credit/defaultprobabilityhelpers.hpp>
#include <ql/termstructures/credit/piecewisedefaultcurve.hpp>



namespace QuantLibAddin {

    // Constructor

    PiecewiseDefaultCurve::PiecewiseDefaultCurve(
		    const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Date& referenceDate,
            const std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> >
                                                                  instruments,
            const QuantLib::DayCounter& dayCounter,
            const std::string& traitsID,
            const std::string& interpolatorID,
            bool permanent)
    : DefaultProbabilityTermStructure(properties, permanent)
    {
     
		 libraryObject_ = ObjectHandler::Create<boost::shared_ptr<
            QuantLib::DefaultProbabilityTermStructure> >()(traitsID,
                                                           interpolatorID,
                                                           referenceDate,
														   instruments,
                                                           dayCounter);
	    
	}

 
}
