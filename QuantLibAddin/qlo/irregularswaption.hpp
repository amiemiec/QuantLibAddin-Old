/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2006 Cristina Duminuco

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

#ifndef qla_irregular_swaption_hpp
#define qla_irregular_swaption_hpp

#include <qlo/baseinstruments.hpp>
#include <ql/experimental/swaptions/irregularswaption.hpp>
#include <ql/pricingengines/swaption/blackswaptionengine.hpp>


namespace QuantLibAddin {
    
    class IrregularSwaption : public Instrument {
      public:
        IrregularSwaption(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                          const boost::shared_ptr<QuantLib::IrregularSwap>& irregularSwap,
                          const boost::shared_ptr<QuantLib::Exercise>& exercise,
                          QuantLib::IrregularSettlement::Type settlementType,
                          bool permanent);

		std::string underlyingSwap() {
            return ObjectHandler::convert2<std::string>(propertyValue("IRREGULARSWAP"));
        }

    };
    
}

#endif
