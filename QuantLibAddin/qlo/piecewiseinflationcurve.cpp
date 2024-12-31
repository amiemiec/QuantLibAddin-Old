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

#ifdef HAVE_CONFIG_H
#include <qlo/config.hpp>
#endif

#include <qlo/inflationtermstructures.hpp>
#include <qlo/piecewiseinflationcurve.hpp>
#include <qlo/enumerations/factories/termstructuresfactory.hpp>

#include <ql/termstructures/inflation/inflationhelpers.hpp>
#include <ql/termstructures/inflation/piecewisezeroinflationcurve.hpp>

#include <ql/math/interpolations/backwardflatinterpolation.hpp>
#include <ql/math/interpolations/forwardflatinterpolation.hpp>
#include <ql/math/interpolations/loginterpolation.hpp>


using boost::algorithm::to_upper_copy;
using boost::shared_ptr;
using ObjectHandler::ValueObject;

namespace QuantLibAddin {

    // Constructor

    PiecewiseZeroInflationCurve::PiecewiseZeroInflationCurve(
		    const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Date& referenceDate,
            const QuantLib::Date& baseDate,
            const QuantLib::Frequency& frequency,
            const QuantLib::DayCounter& dayCounter,
            const std::vector<boost::shared_ptr<QuantLib::InflationZeroHelper> > instruments,
            //const std::string& traitsID,
            const std::string& interpolatorID,
            bool permanent)
    : ZeroInflationTermStructure(properties, permanent), traitsID_("ZEROINFLATION"), interpolatorID_(to_upper_copy(interpolatorID))
    {
         std::string traitsID = "ZeroInflation";

		 libraryObject_ = ObjectHandler::Create<boost::shared_ptr<
            QuantLib::ZeroInflationTermStructure> >()(  traitsID,
                                                        interpolatorID,
                                                        referenceDate,
                                                        baseDate,
                                                        frequency,
                                                        instruments, 
                                                        dayCounter);
	
       
         // convert input strings to enumerated datatypes
        
         InterpolatedZeroInflationCurve::Traits traits =
             ObjectHandler::Create<InterpolatedZeroInflationCurve::Traits>()(traitsID);
         InterpolatedZeroInflationCurve::Interpolator interpolator =
             ObjectHandler::Create<InterpolatedZeroInflationCurve::Interpolator>()(interpolatorID);

         pair_ = InterpolatedInflationCurvePair(traits, interpolator);
         

        /*
        libraryObject_ = boost::shared_ptr<QuantLib::ZeroInflationTermStructure>( 
            new QuantLib::PiecewiseZeroInflationCurve<QuantLib::Linear, QuantLib::IterativeBootstrap, QuantLib::ZeroInflationTraits>(referenceDate,
                baseDate,
                frequency,
                dayCounter,
                instruments));
          */
	}

    // Before implementing the member functions it is necessary to provide some logic to wrap
    // the underlying QuantLib template class PiecewiseYieldCurve<Traits, Interpolator>.
    // This logic is placed in namespace Call.

    // TODO 1) This code overlaps somewhat with logic in the Enumeration Registry - consolidate?
    //      2) Generalize this functionality to expose any template class to the Addin interface

    namespace Call2 {

        // A nontemplate abstract base class to hold wrappers for member functions of
        // PiecewiseYieldCurve<Traits, Interpolator>.  A template subclass allows for
        // one concrete instantiation of each combination of Traits / Interpolator.

        class CallerBase2 {
        public:
            virtual const std::vector<QuantLib::Date>& dates(const QuantLib::Extrapolator* extrapolator) const = 0;
            virtual const std::vector<QuantLib::Real>& data(const QuantLib::Extrapolator* extrapolator) const = 0;

            virtual ~CallerBase2() {}
        };

        // Concrete derived class to wrap member functions of PiecewiseYieldCurve<Traits, Interpolator>.
        // Given a pointer to QuantLib::Extrapolator, this class downcasts to
        // PiecewiseYieldCurve<Traits, Interpolator>* and calls the given member function.

        template <class Traits, class Interpolator>
        class Caller2 : public CallerBase2 {

            typedef QuantLib::PiecewiseZeroInflationCurve<Interpolator> CurveClass2;

            const CurveClass2* get(const QuantLib::Extrapolator* extrapolator) const {

                const CurveClass2* ret = dynamic_cast<const CurveClass2*>(extrapolator);
                OH_REQUIRE(ret, "Unable to convert from type " << typeid(extrapolator).name()
                    << " to type " << typeid(CurveClass2).name());
                return ret;
            }


            const std::vector<QuantLib::Date>& dates(const QuantLib::Extrapolator* extrapolator) const {
                return get(extrapolator)->dates();
            }

            const std::vector<QuantLib::Real>& data(const QuantLib::Extrapolator* extrapolator) const {
                return get(extrapolator)->data();
            }

        };

        // Class CallerFactory stores a map of pointers to Caller objects

        class CallerFactory2 {

            // CallerMap - Holds a pointer to Caller for each combination of Traits / Interpolator.
            typedef std::map<InterpolatedInflationCurvePair, CallerBase2*> CallerMap2;
            CallerMap2 callerMap_;

            // Add an entry to the caller map.
            template <class Traits, class Interpolator>
            void init(InterpolatedInflationCurvePair tokenPair) {
                callerMap_[tokenPair] = new Caller2<Traits, Interpolator>;
            }

        public:

            // Constructor - populate the CallerMap.
            CallerFactory2() {

                // Zero Inflation Curves
                init<QuantLib::ZeroInflationTraits, QuantLib::BackwardFlat>(InterpolatedInflationCurvePair(InterpolatedZeroInflationCurve::ZeroInflation, InterpolatedZeroInflationCurve::BackwardFlat));
                init<QuantLib::ZeroInflationTraits, QuantLib::ForwardFlat>(InterpolatedInflationCurvePair(InterpolatedZeroInflationCurve::ZeroInflation, InterpolatedZeroInflationCurve::ForwardFlat));
                init<QuantLib::ZeroInflationTraits, QuantLib::Linear>(InterpolatedInflationCurvePair(InterpolatedZeroInflationCurve::ZeroInflation, InterpolatedZeroInflationCurve::Linear));
                init<QuantLib::ZeroInflationTraits, QuantLib::LogLinear>(InterpolatedInflationCurvePair(InterpolatedZeroInflationCurve::ZeroInflation, InterpolatedZeroInflationCurve::LogLinear));

            }

            // Destructor - deallocate the CallerMap.
            ~CallerFactory2() {
                for (CallerMap2::const_iterator i = callerMap_.begin(); i != callerMap_.end(); ++i)
                    delete i->second;
            }

            // Retrieve the Caller pointer corresponding to a given InterpolatedYieldCurvePair
            const CallerBase2* getCaller(InterpolatedInflationCurvePair tokenPair) const {
                CallerMap2::const_iterator i = callerMap_.find(tokenPair);
                OH_REQUIRE(i != callerMap_.end(), "Unable to retrieve caller for the token pait");
                return i->second;
            }

        };

        // Basic Singleton behavior for the CallerFactory

        const CallerFactory2& callerFactory() {
            static CallerFactory2 callerFactory_;
            return callerFactory_;
        }

    } // namespace Call

    // QuantLibAddin wrappers for member functions of QuantLib class
    // PiecewiseYieldCurve<Traits, Interpolator>. Invocation of the member function is
    // passed off to the CallerFactory which hides the details of the template class.

#define CALL2(FUNC) \
Call2::callerFactory().getCaller(pair_)->FUNC(libraryObject_.get())


    const std::vector<QuantLib::Date>& PiecewiseZeroInflationCurve::dates() const {
        return CALL2(dates);
    }

    const std::vector<QuantLib::Real>& PiecewiseZeroInflationCurve::data() const {
        return CALL2(data);
    }

 
}
