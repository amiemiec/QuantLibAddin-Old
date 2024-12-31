/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2024 Andre Miemiec
 
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

#ifndef qla_inflationindex_hpp
#define qla_inflationindex_hpp

#include <oh/libraryobject.hpp>

#include <ql/types.hpp>
#include <qlo/index.hpp>
#include <ql/index.hpp>
#include <ql/indexes/region.hpp>
#include <ql/time/businessdayconvention.hpp>
#include <ql/termstructures/inflation/interpolatedzeroinflationcurve.hpp>


namespace QuantLib {
    class Region;
    class Period;
    class Currency;
    class Calendar;
    class DayCounter;
    class YieldTermStructure;
    class IborIndex;
    class Quote;


    template <class T>
    class Handle;
}

namespace QuantLibAddin {



    class Region : public ObjectHandler::LibraryObject<QuantLib::Region> {
    public:
        OH_LIB_CTOR(Region, QuantLib::Region);
    };


    /*
    class InflationIndex : public Index {
      public:
          InflationIndex( const boost::shared_ptr<ObjectHandler::ValueObject>& properties, 
                          const std::string& familyName,
                          const QuantLib::Region& region,
                          bool revised,
                          const QuantLib::Frequency& frequency,
                          const QuantLib::Period& availabilitiyLag,
                          const QuantLib::Currency& currency,
                          bool permanent);
    };
    */

    OH_OBJ_CLASS(InflationIndex, Index);


    class ZeroInflationIndex : public InflationIndex {
    public:
        ZeroInflationIndex(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::string& familyName,
            /*const boost::shared_ptr<QuantLib::Region>& region,*/
            const QuantLib::Region& region,
            bool revised,
            QuantLib::Frequency frequency,
            const QuantLib::Period& availabilityLag,
            const QuantLib::Currency& currency,
            QuantLib::Handle<QuantLib::ZeroInflationTermStructure> ts = {},
            bool permanent = false);
    };


}

#endif
