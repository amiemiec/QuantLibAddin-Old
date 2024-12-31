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

#include <qlo/indexes/inflation/euhicp.hpp>

#include <ql/indexes/inflation/euhicp.hpp>
#include <ql/utilities/dataparsers.hpp>

#include <boost/algorithm/string/case_conv.hpp>

using ObjectHandler::ValueObject;
using boost::shared_ptr;

namespace QuantLibAddin {

    euhicp::euhicp(const shared_ptr<ValueObject>& properties,
                     const std::string& p_inp,
                     const QuantLib::Handle<QuantLib::ZeroInflationTermStructure>& h,
                     bool permanent)
    : ZeroInflationIndex(properties,"HICP",QuantLib::EURegion(),false,QuantLib::Monthly,QuantLib::Period(1, QuantLib::Months), QuantLib::EURCurrency(),h,permanent)
    {

        libraryObject_ = boost::shared_ptr<QuantLib::ZeroInflationIndex>(new QuantLib::EUHICP(h));
 
    }


}
