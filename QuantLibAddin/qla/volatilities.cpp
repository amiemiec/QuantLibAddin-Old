
/*
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qla/config.hpp>
#endif
#include <qla/volatilities.hpp>
#include <qla/generalutils.hpp>
#include <qla/typefactory.hpp>

namespace QuantLibAddin {

    BlackConstantVol::BlackConstantVol(
            const long &settlementDateLong,
            const double &volatility,
            const std::string &dayCounterID) {

        QuantLib::Date settlementDate(settlementDateLong);
        QuantLib::DayCounter dayCounter =
            Create<QuantLib::DayCounter>()(dayCounterID);
        blackVolTermStructure_ = boost::shared_ptr<QuantLib::BlackVolTermStructure> (
            new QuantLib::BlackConstantVol(
                settlementDate,
                volatility,
                dayCounter));
    }

    BlackVarianceSurface::BlackVarianceSurface(
            const long &settlementDate,
            const std::vector < long > &dates,
            const std::vector < double > &strikes,
            const std::vector < std::vector < double > > &vols,
            const std::string &dayCounterID) {

        QuantLib::Date settlementDateQL(settlementDate);
        const std::vector<QuantLib::Date> datesQL = 
            longVectorToDateVector(dates);
        QuantLib::Matrix volsQL =
            vectorVectorToMatrix(vols);
        QuantLib::DayCounter dayCounter =
            Create<QuantLib::DayCounter>()(dayCounterID);

        blackVolTermStructure_ = boost::shared_ptr<QuantLib::BlackVolTermStructure> (
            new QuantLib::BlackVarianceSurface(
                settlementDateQL,
                datesQL,
                strikes,
                volsQL,
                dayCounter));
    }


}

