/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2007, 2012 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers

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

#include <qlo/pricingengines_misc.hpp>

#include <qlo/swaption.hpp>
#include <qlo/enumerations/factories/pricingenginesfactory.hpp>

#include <ql/pricingengines/swap/treeswapengine.hpp>
#include <ql/experimental/swaptions/treeirregularswapengine.hpp>
#include <ql/experimental/swaptions/treeirregularswaptionengine.hpp>
#include <ql/experimental/swaptions/haganirregularswaptionengine.hpp>
#include <ql/experimental/callablebonds/treecallablebondengine.hpp>

#include <ql/experimental/mcbasket/mcpathbasketengine.hpp>
#include <ql/experimental/mcbasket/mcamericanpathengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/instruments/forwardvanillaoption.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/quanto/quantoengine.hpp>
#include <ql/pricingengines/forward/forwardengine.hpp>


namespace QuantLibAddin {

	
	TreeVanillaSwapEngine::TreeVanillaSwapEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::ShortRateModel>& model,
            QuantLib::Size timeSteps,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
			QuantLib::TreeVanillaSwapEngine(model,timeSteps,discountCurve));
    }


	
	TreeIrregularSwapEngine::TreeIrregularSwapEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::ShortRateModel>& model,
            QuantLib::Size timeSteps,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
			QuantLib::TreeIrregularSwapEngine(model,timeSteps,discountCurve));
    }




	TreeIrregularSwaptionEngine::TreeIrregularSwaptionEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::ShortRateModel>& model,
            QuantLib::Size timeSteps,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
			QuantLib::TreeIrregularSwaptionEngine(model,timeSteps,discountCurve));
    }
	


	HaganIrregularSwaptionEngine::HaganIrregularSwaptionEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>& volatilityTS,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent) : PricingEngine(properties, permanent)
	{
		libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
			QuantLib::HaganIrregularSwaptionEngine(volatilityTS,discountCurve));
    }





	TreeCallableFixedRateBondEngine::TreeCallableFixedRateBondEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::ShortRateModel>& model,
            QuantLib::Size timeSteps,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
			QuantLib::TreeCallableFixedRateBondEngine(model,timeSteps,discountCurve));
    }


    MCPathBasketEngine::MCPathBasketEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::StochasticProcessArray>& processArray,
        bool isQuasiRng,
        QuantLib::Size timeSteps,
        QuantLib::Size timeStepsPerYear,
        bool brownianBridge,
        bool antitheticVariate,
        bool controlVariate,
        QuantLib::Size requiredSamples,
        QuantLib::Real requiredTolerance,
        QuantLib::Size maxSamples,
        QuantLib::BigNatural seed,
        bool permanent)
        : PricingEngine(properties, permanent)
    {
        if (isQuasiRng) {
            libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(
                QuantLib::MakeMCPathBasketEngine<QuantLib::LowDiscrepancy>(processArray)
                .withSteps(timeSteps)
                //.withStepsPerYear(timeStepsPerYear)
                .withBrownianBridge(brownianBridge)
                .withAntitheticVariate(antitheticVariate)
                .withControlVariate(controlVariate)
                .withSamples(requiredSamples)
                //.withAbsoluteTolerance(requiredTolerance)
                .withMaxSamples(maxSamples)
                .withSeed(seed));
        }
        else {
            libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(
                QuantLib::MakeMCPathBasketEngine<QuantLib::PseudoRandom>(processArray)
                .withSteps(timeSteps)
                //.withStepsPerYear(timeStepsPerYear)
                .withBrownianBridge(brownianBridge)
                .withAntitheticVariate(antitheticVariate)
                .withControlVariate(controlVariate)
                .withSamples(requiredSamples)
                //.withAbsoluteTolerance(requiredTolerance)
                .withMaxSamples(maxSamples)
                .withSeed(seed));
        }



    }



    MCAmericanPathEngine::MCAmericanPathEngine(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::StochasticProcessArray>& processArray,
        QuantLib::Size timeSteps,
        QuantLib::Size timeStepsPerYear,
        bool brownianBridge,
        bool antitheticVariate,
        bool controlVariate,
        QuantLib::Size requiredSamples,
        QuantLib::Real requiredTolerance,
        QuantLib::Size maxSamples,
        QuantLib::BigNatural seed,
        QuantLib::Size nCalibrationSamples,
        bool permanent) : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(
            QuantLib::MakeMCAmericanPathEngine<QuantLib::PseudoRandom>(processArray)
            .withSteps(timeSteps)
            //.withStepsPerYear(timeStepsPerYear)
            .withBrownianBridge(brownianBridge)
            .withAntitheticVariate(antitheticVariate)
            .withControlVariate(controlVariate)
            .withSamples(requiredSamples)
            //.withAbsoluteTolerance(requiredTolerance)
            .withMaxSamples(maxSamples)
            .withSeed(seed)
            .withCalibrationSamples(nCalibrationSamples));
    }






    FdBlackScholesVanillaEngine::FdBlackScholesVanillaEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>& process,
        QuantLib::Size tGrid,
        QuantLib::Size xGrid,
        QuantLib::Size dampingSteps,
        /*const QuantLib::FdmSchemeDesc& schemeDesc,
        bool localVol,
        QuantLib::Real illegalLocalVolOverwrite,*/
        bool permanent)
        : PricingEngine(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::FdBlackScholesVanillaEngine(process,
                tGrid, xGrid, dampingSteps/*,schemeDesc,
                localVol, illegalLocalVolOverwrite*/));

    }



   

	QuantoForwardVanillaEngine::QuantoForwardVanillaEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>& process,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& foreignRiskFreeTS,
            const QuantLib::Handle<QuantLib::BlackVolTermStructure>& exchangeRateVolatility,
            const QuantLib::Handle<QuantLib::Quote>& correlation,            
			bool permanent) 
	: PricingEngine(properties, permanent)
    {
    
		libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(
             new QuantLib::QuantoEngine<QuantLib::ForwardVanillaOption,
			                            QuantLib::ForwardEngine >(
                                                 process, foreignRiskFreeTS, exchangeRateVolatility,correlation));

		 
	}



}

