/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2012 Ferdinando Ametrano
 Copyright (C) 2006 Cristina Duminuco
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

#ifndef qla_my_pricingengine_hpp
#define qla_my_pricingengine_hpp

#include <oh/libraryobject.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/models.hpp>

namespace QuantLib {
	class TreeSwapEngine;
    class TreeIrregularSwapEngine;
    class TreeIrregularSwaptionEngine;
	class HaganIrregularSwaptionEngine;
	class TreeCallableFixedRateBondEngine;
	class GeneralizedBlackScholesProcess;

	class FdBlackScholesVanillaEngine;
	class FdmSchemeDesc;
	class StochasticProcessArray;


	class BlackVolTermStructure;
	class ForwardVanillaOption;
	class AnalyticEuropeanEngine;
	
	template <class T> 
	class ForwardVanillaEngine;
    
	typedef ForwardVanillaEngine<AnalyticEuropeanEngine> ForwardEngine;
}

namespace QuantLibAddin {


    class TreeVanillaSwapEngine : public PricingEngine 
	{
	  public:
          TreeVanillaSwapEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::ShortRateModel>& model,
			QuantLib::Size timeSteps,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent);
    };

	
	
   class TreeIrregularSwapEngine : public PricingEngine 
	{
	  public:
          TreeIrregularSwapEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::ShortRateModel>& model,
			QuantLib::Size timeSteps,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent);
    };



	class TreeIrregularSwaptionEngine : public PricingEngine 
	{
	  public:
          TreeIrregularSwaptionEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::ShortRateModel>& model,
			QuantLib::Size timeSteps,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent);
    };



	class HaganIrregularSwaptionEngine : public PricingEngine 
	{
	  public:
          HaganIrregularSwaptionEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>& volatilityTS,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent);
    };




	class TreeCallableFixedRateBondEngine : public PricingEngine 
	{
	  public:
          TreeCallableFixedRateBondEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::ShortRateModel>& model,
			QuantLib::Size timeSteps,
			const QuantLib::Handle<QuantLib::YieldTermStructure>& discountCurve,
            bool permanent);
    };

	class MCPathBasketEngine : public PricingEngine {
	public:
		MCPathBasketEngine(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
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
			bool permanent);
	};



	class MCAmericanPathEngine : public PricingEngine {
	public:
		MCAmericanPathEngine(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
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
			bool permanent);
	};


	class FdBlackScholesVanillaEngine : public PricingEngine {
	public:
		FdBlackScholesVanillaEngine(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>& process,
			QuantLib::Size tGrid = 100,
			QuantLib::Size xGrid = 100,
			QuantLib::Size dampingSteps = 0,
			/*const QuantLib::FdmSchemeDesc& schemeDesc = QuantLib::FdmSchemeDesc::Douglas()
			bool localVol = false,
			QuantLib::Real illegalLocalVolOverwrite = -QuantLib::Null<QuantLib::Real>(),*/
			bool permanent = false);
	};

    
	class QuantoForwardVanillaEngine : public PricingEngine
	{
	 public:
		 QuantoForwardVanillaEngine(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>& process,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& foreignRiskFreeTS,
            const QuantLib::Handle<QuantLib::BlackVolTermStructure>& exchangeRateVolatility,
            const QuantLib::Handle<QuantLib::Quote>& correlation,            
			bool permanent);
	};
    

}
#endif
