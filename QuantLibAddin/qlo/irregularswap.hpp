/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Aurelien Chanudet

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

#ifndef qla_irregularswap_hpp
#define qla_irregularswap_hpp

#include <qlo/swap.hpp>
#include <ql/experimental/swaptions/irregularswap.hpp>





namespace QuantLibAddin {

	class Leg;

    class IrregularSwap : public Swap {
    public:
        IrregularSwap(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::IrregularSwap::Type type,
			const QuantLib::Leg& fixLeg,
			const QuantLib::Leg& floatLeg,
            bool permanent);

        std::vector<std::vector<ObjectHandler::property_t> > fixedLegAnalysis();
        std::vector<std::vector<ObjectHandler::property_t> > floatingLegAnalysis();
    };

}

#endif
