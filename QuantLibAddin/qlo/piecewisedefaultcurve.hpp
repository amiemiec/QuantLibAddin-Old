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

#ifndef qla_piecewise_defaultcurve_hpp
#define qla_piecewise_defaultcurve_hpp

//#include <oh/libraryobject.hpp>
//#include <ql/types.hpp>

#include <qlo/defaulttermstructures.hpp>
//#include <qlo/defaultprobabilityhelpers.hpp>
#include <qlo/credit.hpp>

#include <ql/termstructures/credit/piecewisedefaultcurve.hpp>
#include <ql/termstructures/credit/defaultprobabilityhelpers.hpp>

namespace QuantLib {

    class DayCounter;
    class Date;

    class DefaultProabilityTermStructure;

}


namespace QuantLibAddin {

	//OH_LIB_CLASS(DefaultProbabilityTermStructure,QuantLib::DefaultProabilityTermStructure);
    
    
	          
	class PiecewiseDefaultCurve : public DefaultProbabilityTermStructure {
      public:
        PiecewiseDefaultCurve(
		    const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Date& referenceDate,
            const std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> >
                                                                  instruments,
            const QuantLib::DayCounter& dayCounter,
            const std::string& traitsID,
            const std::string& interpolatorID,
            bool permanent);
    };

}

#endif
