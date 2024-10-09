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

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif

#include <qlo/cmsspreadcoupon.hpp>

#include <ql/cashflows/simplecashflow.hpp>
#include <ql/cashflows/cashflows.hpp>
#include <ql/experimental/coupons/swapspreadindex.hpp>
#include <ql/experimental/coupons/cmsspreadcoupon.hpp>
#include <ql/experimental/coupons/lognormalcmsspreadpricer.hpp>


using ObjectHandler::LibraryObject;
using ObjectHandler::ValueObject;
using QuantLib::earlier_than;
using QuantLib::CashFlow;
using boost::shared_ptr;
using std::vector;


namespace QuantLib{
    class SwapSpreadIndex;

}

namespace QuantLibAddin {

    SwapSpreadIndex::SwapSpreadIndex(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const std::string& familyName,
        const boost::shared_ptr<QuantLib::SwapIndex>& swapIndex1,
        const boost::shared_ptr<QuantLib::SwapIndex>& swapIndex2,
        QuantLib::Real gearing1,
        QuantLib::Real gearing2,
        bool permanent)
        : InterestRateIndex(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::SwapSpreadIndex>(new
            QuantLib::SwapSpreadIndex(familyName,
                swapIndex1,
                swapIndex2,
                gearing1,
                gearing2));
    }



    CmsSpreadLeg::CmsSpreadLeg(const shared_ptr<ValueObject>& properties,
        QuantLib::BusinessDayConvention paymentConvention,
        const vector<QuantLib::Real>& nominals,
        const shared_ptr<QuantLib::Schedule>& schedule,
        const vector<QuantLib::Natural>& fixingDays,
        bool isInArrears,
        const QuantLib::DayCounter& paymentDayCounter,
        const vector<QuantLib::Rate>& floors,
        const vector<QuantLib::Real>& gearings,
        const shared_ptr<QuantLib::SwapSpreadIndex>& index,
        const vector<QuantLib::Spread>& spreads,
        const vector<QuantLib::Rate>& caps,
        bool permanent)
        : Leg(properties, permanent)
    {
        int dim_v_nominals = nominals.size();
        int dim_v_gearings = gearings.size();
        int dim_v_caps = caps.size();
        int dim_v_floors = floors.size();
        int dim_v_spreads = spreads.size();

        int dim_v_max = std::max(std::max(std::max(std::max(dim_v_caps, dim_v_floors), dim_v_spreads), dim_v_gearings),dim_v_nominals);

        vector<QuantLib::Real> nominals_; nominals_.resize(dim_v_max);
        vector<QuantLib::Real> gearings_; gearings_.resize(dim_v_max);
        vector<QuantLib::Rate> caps_; caps_.resize(dim_v_max);
        vector<QuantLib::Rate> floors_; floors_.resize(dim_v_max);
        vector<QuantLib::Spread> spreads_; spreads_.resize(dim_v_max);
        

        //Step 1: Pimp the dimension of the vectors 
        if (dim_v_caps == 1)     { caps_.assign(dim_v_max, caps.at(0)); }
        if (dim_v_floors == 1)   { floors_.assign(dim_v_max, floors.at(0)); }
        if (dim_v_gearings == 1) { gearings_.assign(dim_v_max, gearings.at(0)); }
        if (dim_v_spreads == 1)  { spreads_.assign(dim_v_max, spreads.at(0)); }
        if (dim_v_nominals == 1) { nominals_.assign(dim_v_max, nominals.at(0)); }

        //Step 2: Rescale the Parameters such that gearing becomes 1.0 ans spread becomes 0.0
        for (int i = 0; i < dim_v_max; i++) {
            caps_[i]   = (caps_[i]-spreads_[i])/gearings_[i];     
            floors_[i] = (floors_[i]-spreads_[i])/gearings_[i];
            nominals_[i] *= gearings_[i];
            spreads_[i] /= gearings[i];   
            gearings_[i] = 1.0;
        }


        libraryObject_ = shared_ptr<QuantLib::Leg>(new
            QuantLib::Leg(QuantLib::CmsSpreadLeg(*schedule, index)
                .withNotionals(nominals)
                .withPaymentDayCounter(paymentDayCounter)
                .withPaymentAdjustment(paymentConvention)
                .withFixingDays(fixingDays)
                .withGearings(gearings)
                .withSpreads(spreads)
                .withCaps(caps)
                .withFloors(floors)
                .inArrears(isInArrears)));
    }




    LogNormalCmsSpreadPricer::LogNormalCmsSpreadPricer(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::CmsCouponPricer>& cmsPricer,
        const QuantLib::Handle<QuantLib::Quote>& correlation,
        QuantLib::Handle<QuantLib::YieldTermStructure> couponDiscountCurve,
        QuantLib::Size integrationPoints,
        const QuantLib::VolatilityType volType,
        QuantLib::Real shift1,
        QuantLib::Real shift2,
        bool permanent): FloatingRateCouponPricer(properties, permanent)
    {

        libraryObject_ =  shared_ptr<QuantLib::LognormalCmsSpreadPricer>(new
             QuantLib::LognormalCmsSpreadPricer(cmsPricer, 
                                                correlation, 
                                                couponDiscountCurve, 
                                                integrationPoints, 
                                                volType, 
                                                shift1, 
                                                shift2));
    }


     
}