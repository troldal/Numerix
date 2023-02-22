/*
    888b      88  88        88  88b           d88  88888888888  88888888ba   88  8b        d8
    8888b     88  88        88  888b         d888  88           88      "8b  88   Y8,    ,8P
    88 `8b    88  88        88  88`8b       d8'88  88           88      ,8P  88    `8b  d8'
    88  `8b   88  88        88  88 `8b     d8' 88  88aaaaa      88aaaaaa8P'  88      Y88P
    88   `8b  88  88        88  88  `8b   d8'  88  88"""""      88""""88'    88      d88b
    88    `8b 88  88        88  88   `8b d8'   88  88           88    `8b    88    ,8P  Y8,
    88     `8888  Y8a.    .a8P  88    `888'    88  88           88     `8b   88   d8'    `8b
    88      `888   `"Y8888Y"'   88     `8'     88  88888888888  88      `8b  88  8P        Y8

    Copyright © 2022 Kenneth Troldal Balslev

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the “Software”), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is furnished
    to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef PCPROPS_DIFFERENTIATION_HPP
#define PCPROPS_DIFFERENTIATION_HPP

#include <cassert>
#include <cmath>
#include <functional>
#include <limits>

namespace nxx::deriv
{

    /**
     * @brief Contains private implementations methods for computing function derivatives.
     */
    namespace impl
    {

        // ====================================================================
        // Central finite difference formulas
        // ====================================================================

        /**
         * @brief Compute the 1st order derivative of the provided function, using a 3-point centered finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto central3PointOrder1(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (function(val + stepsize) - function(val - stepsize)) / (2 * stepsize);
        }

        /**
         * @brief Compute the 1st order derivative of the provided function, using a 5-point centered finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto central5PointOrder1(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (-function(val + 2 * stepsize) + 8 * function(val + stepsize) - 8 * function(val - stepsize) +
                    function(val - 2 * stepsize)) /
                   (12 * stepsize);
        }

        /**
         * @brief Compute the 2nd order derivative of the provided function, using a 3-point centered finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto central3PointOrder2(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (function(val + stepsize) - 2 * function(val) + function(val - stepsize)) / std::pow(stepsize, 2);
        }

        /**
         * @brief Compute the 2nd order derivative of the provided function, using a 5-point centered finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto central5PointOrder2(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (-function(val + 2 * stepsize) + 16 * function(val + stepsize) - 30 * function(val) + 16 * function(val - stepsize) -
                    function(val - 2 * stepsize)) /
                   (12 * std::pow(stepsize, 2));
        }

        // ====================================================================
        // Forward finite difference formulas
        // ====================================================================

        /**
         * @brief Compute the 1st order derivative of the provided function, using a 2-point forward finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto forward2PointOrder1(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (function(val + stepsize) - function(val)) / stepsize;
        }

        /**
         * @brief Compute the 1st order derivative of the provided function, using a 3-point forward finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto forward3PointOrder1(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (-function(val + 2 * stepsize) + 4 * function(val + stepsize) - 3 * function(val)) / (2 * stepsize);
        }

        /**
         * @brief Compute the 2nd order derivative of the provided function, using a 3-point forward finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto forward3PointOrder2(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (function(val + 2 * stepsize) - 2 * function(val + stepsize) + function(val)) / std::pow(stepsize, 2);
        }

        /**
         * @brief Compute the 2nd order derivative of the provided function, using a 4-point forward finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto forward4PointOrder2(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (-function(val + 3 * stepsize) + 4 * function(val + 2 * stepsize) - 5 * function(val + stepsize) + 2 * function(val)) /
                   std::pow(stepsize, 2);
        }

        // ====================================================================
        // Backward finite difference formulas
        // ====================================================================

        /**
         * @brief Compute the 1st order derivative of the provided function, using a 2-point backward finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto backward2PointOrder1(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (function(val) - function(val - stepsize)) / stepsize;
        }

        /**
         * @brief Compute the 1st order derivative of the provided function, using a 3-point backward finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::is_invocable_v<Fn, double>
        inline auto backward3PointOrder1(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (3 * function(val) - 4 * function(val - stepsize) + function(val - 2 * stepsize)) / (2 * stepsize);
        }

        /**
         * @brief Compute the 2nd order derivative of the provided function, using a 3-point backward finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto backward3PointOrder2(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (function(val) - 2 * function(val - stepsize) + function(val - 2 * stepsize)) / std::pow(stepsize, 2);
        }

        /**
         * @brief Compute the 2nd order derivative of the provided function, using a 4-point backward finite divided-difference formula.
         * @details See chapter 23 in "Numerical Methods for Engineers", 8th Edition by Steven C. Chapra, for details.
         * @tparam Fn The type of the function. Can be any callable object, e.g. a lambda.
         * @param function The function for which to compute the derivative.
         * @param val The value at which to compute the derivative.
         * @param stepsize The step size to use when using the divided-difference formula.
         * @return The approximated derivative. The type is the same as the return type of the provided function.
         * @note This function is not intended to be used directly. Instead, use the Derivative class, or one of the convenience functions.
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto backward4PointOrder2(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize)
            -> decltype(function(0.0))
        {
            return (2 * function(val) - 5 * function(val - stepsize) + 4 * function(val - 2 * stepsize) - function(val - 3 * stepsize)) /
                   std::pow(stepsize, 2);
        }

        // ====================================================================
        // Robust Derivatives
        // ====================================================================

        /**
         * @brief
         * @tparam Fn
         * @param function
         * @param val
         * @param stepsize
         * @return
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto derivOrder1(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize) -> decltype(function(0.0))
        {
            using RT = decltype(function(0.0));

            RT result;

            result = impl::central5PointOrder1(function, val, stepsize);
            if (!std::isnan(result)) return result;

            result = impl::central3PointOrder1(function, val, stepsize);
            if (!std::isnan(result)) return result;

            result = impl::backward3PointOrder1(function, val, stepsize);
            if (!std::isnan(result)) return result;

            result = impl::backward2PointOrder1(function, val, stepsize);
            if (!std::isnan(result)) return result;

            result = impl::forward3PointOrder1(function, val, stepsize);
            if (!std::isnan(result)) return result;

            return impl::forward2PointOrder1(function, val, stepsize);
        }

        /**
         * @brief
         * @tparam Fn
         * @param function
         * @param val
         * @param stepsize
         * @return
         */
        template<typename Fn>
            requires std::invocable<Fn, double>
        inline auto derivOrder2(Fn function, decltype(function(0.0)) val, decltype(function(0.0)) stepsize) -> decltype(function(0.0))
        {
            using RT = decltype(function(0.0));

            RT result;

            result = impl::central5PointOrder2(function, val, stepsize);
            if (!std::isnan(result)) return result;

            result = impl::central3PointOrder2(function, val, stepsize);
            if (!std::isnan(result)) return result;

            result = impl::backward4PointOrder2(function, val, stepsize);
            if (!std::isnan(result)) return result;

            result = impl::backward3PointOrder2(function, val, stepsize);
            if (!std::isnan(result)) return result;

            result = impl::forward4PointOrder2(function, val, stepsize);
            if (!std::isnan(result)) return result;

            return impl::forward3PointOrder2(function, val, stepsize);
        }
    }    // namespace impl

    /**
     * @brief
     * @tparam Fn
     */
    template<typename Fn>
        requires std::invocable<Fn, double>
    class Derivative final
    {
        Fn m_func;

        using RT = decltype(m_func(0.0));

    public:
        /**
         * @brief
         * @param function
         */
        explicit Derivative(Fn function) : m_func(function) {}

        /**
         * @brief
         * @param val
         * @param order
         * @return
         */
        RT operator()(RT val, int order = 1)
        {
            assert(order >= 1 && order <= 2);

            auto h = std::cbrt(std::numeric_limits<RT>::epsilon());
            switch (order) {
                case 1:
                    return impl::derivOrder1(m_func, val, h);
                case 2:
                    return impl::derivOrder2(m_func, val, h);
                default:
                    return impl::derivOrder1(m_func, val, h);
            }
        }
    };

    /**
     * @brief
     * @tparam Fn
     * @param function
     * @param val
     * @param order
     * @return
     */
    template<typename Fn>
        requires std::invocable<Fn, double>
    inline auto central(Fn function, decltype(function(0.0)) val, int order = 1) -> decltype(function(0.0))
    {
        assert(order >= 1 && order <= 2);

        using RT = decltype(function(0.0));
        auto h   = std::cbrt(std::numeric_limits<RT>::epsilon());

        RT result;

        if (order == 1) {
            result = impl::central5PointOrder1(function, val, h);
            if (!std::isnan(result)) return result;
            return impl::central3PointOrder1(function, val, h);
        }

        if (order == 2) {
            result = impl::central5PointOrder2(function, val, h);
            if (!std::isnan(result)) return result;
            return impl::central3PointOrder2(function, val, h);
        }

        return std::nan("0");
    }

    /**
     * @brief
     * @tparam Fn
     * @param function
     * @param val
     * @param order
     * @return
     */
    template<typename Fn>
        requires std::invocable<Fn, double>
    inline auto forward(Fn function, decltype(function(0.0)) val, int order = 1) -> decltype(function(0.0))
    {
        assert(order >= 1 && order <= 2);

        using RT = decltype(function(0.0));
        auto h   = std::cbrt(std::numeric_limits<RT>::epsilon());

        RT result;

        if (order == 1) {
            result = impl::forward3PointOrder1(function, val, h);
            if (!std::isnan(result)) return result;
            return impl::forward2PointOrder1(function, val, h);
        }

        if (order == 2) {
            result = impl::forward4PointOrder2(function, val, h);
            if (!std::isnan(result)) return result;
            return impl::forward3PointOrder2(function, val, h);
        }

        return std::nan("0");
    }

    /**
     * @brief
     * @tparam Fn
     * @param function
     * @param val
     * @param order
     * @return
     */
    template<typename Fn>
        requires std::invocable<Fn, double>
    inline auto backward(Fn function, decltype(function(0.0)) val, int order = 1) -> decltype(function(0.0))
    {
        assert(order >= 1 && order <= 2);

        using RT = decltype(function(0.0));
        auto h   = std::cbrt(std::numeric_limits<RT>::epsilon());

        RT result;

        if (order == 1) {
            result = impl::backward3PointOrder1(function, val, h);
            if (!std::isnan(result)) return result;
            return impl::backward2PointOrder1(function, val, h);
        }

        if (order == 2) {
            result = impl::backward4PointOrder2(function, val, h);
            if (!std::isnan(result)) return result;
            return impl::backward3PointOrder2(function, val, h);
        }

        return std::nan("0");
    }

}    // namespace numerix::deriv

#endif    // PCPROPS_DIFFERENTIATION_HPP
