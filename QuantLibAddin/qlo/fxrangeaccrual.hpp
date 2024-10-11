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

#ifndef qla_fxindex_hpp
#define qla_fxindex_hpp

#include <oh/libraryobject.hpp>
#include<qlo/index.hpp>
#include <ql/types.hpp>

namespace QuantLib {
    class Date;
    class Index;
    class EquityIndex;
    class YieldTermStructure;
    class Calendar;
    class Quote;

    template <class T>
    class Handle;
}

namespace QuantLibAddin {

    OH_OBJ_CLASS(EquityIndex,Index);

    class FxIndex : public EquityIndex {
    public:
        FxIndex(const boost::shared_ptr<ObjectHandler::ValueObject>& properties, 
                std::string name,
                QuantLib::Calendar fixingCalendar,
                QuantLib::Handle<QuantLib::YieldTermStructure> domInterest,
                QuantLib::Handle<QuantLib::YieldTermStructure> forInterest,
                QuantLib::Handle<QuantLib::Quote> spot,
                bool permanent);
    };

}

#endif
