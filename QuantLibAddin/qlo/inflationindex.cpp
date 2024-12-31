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

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <qlo/index.hpp>
//#include <qlo/indexes/iborindex.hpp>
#include <qlo/inflationindex.hpp>

#include <ql/timeseries.hpp>
#include <ql/index.hpp>
#include <ql/indexes/inflationindex.hpp>

namespace QuantLib {
    class Region;
    class Period;
    class Currency;
    class Calendar;
    class DayCounter;
    class YieldTermStructure;

    template <class T>
    class Handle;
}



namespace QuantLibAddin {

    /*
    InflationIndex::InflationIndex(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const std::string& familyName,
        const QuantLib::Region& region,
        bool revised,
        const QuantLib::Frequency& frequency,
        const QuantLib::Period& availabilitiyLag,
        const QuantLib::Currency& currency,
        bool permanent):Index(properties, permanent) {
        
        libraryObject_ = boost::shared_ptr<QuantLib::Index>(new
            QuantLib::InflationIndex(familyName, region, revised, frequency, availabilitiyLag, currency));
        
    }
    */

    ZeroInflationIndex::ZeroInflationIndex(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const std::string& familyName,
        /*const boost::shared_ptr<QuantLib::Region>& region,*/
        const QuantLib::Region& region,
        bool revised,
        QuantLib::Frequency frequency,
        const QuantLib::Period& availabilityLag,
        const QuantLib::Currency& currency,
        QuantLib::Handle<QuantLib::ZeroInflationTermStructure> ts,
        bool permanent) : InflationIndex(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::Index>(new
            QuantLib::ZeroInflationIndex(familyName, region, /* *region,*/ revised, frequency, availabilityLag, currency, ts));
    }


}
