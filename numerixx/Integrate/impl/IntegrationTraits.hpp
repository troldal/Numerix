/*
    888b      88  88        88  88b           d88  88888888888  88888888ba   88  8b        d8  8b        d8
    8888b     88  88        88  888b         d888  88           88      "8b  88   Y8,    ,8P    Y8,    ,8P
    88 `8b    88  88        88  88`8b       d8'88  88           88      ,8P  88    `8b  d8'      `8b  d8'
    88  `8b   88  88        88  88 `8b     d8' 88  88aaaaa      88aaaaaa8P'  88      Y88P          Y88P
    88   `8b  88  88        88  88  `8b   d8'  88  88"""""      88""""88'    88      d88b          d88b
    88    `8b 88  88        88  88   `8b d8'   88  88           88    `8b    88    ,8P  Y8,      ,8P  Y8,
    88     `8888  Y8a.    .a8P  88    `888'    88  88           88     `8b   88   d8'    `8b    d8'    `8b
    88      `888   `"Y8888Y"'   88     `8'     88  88888888888  88      `8b  88  8P        Y8  8P        Y8

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

#ifndef INTEGRATIONTRAITS_HPP
#define INTEGRATIONTRAITS_HPP

// ===== Numerixx Includes
#include <Concepts.hpp>

/**
 * @file IntegrationTraits.hpp
 * @brief Header file defining the IntegrationTraits structure for various integration solvers.
 *
 * This file contains the template specializations of the IntegrationTraits structure for the Trapezoid,
 * Romberg, and Simpson classes. IntegrationTraits is designed to provide type information relevant to
 * the integration process, such as the types of the function, argument, and return value.
 */
namespace nxx::integrate
{
    /**
     * @brief Forward declarations of the integration solver classes.
     *
     * These declarations provide a reference for the IntegrationTraits specializations without needing
     * to include the full definitions of these classes.
     */
    template<IsFloatInvocable FN, IsFloat ARG_T>
    class Trapezoid;
    template<IsFloatInvocable FN, IsFloat ARG_T>
    class Romberg;
    template<IsFloatInvocable FN, IsFloat ARG_T>
    class Simpson;

    namespace detail
    {
        /**
         * @struct IntegrationTraits
         * @brief Primary template for integration traits, to be specialized for each solver.
         *
         * @details This structure template is used to define traits for integration solver classes.
         *          It's specialized for each specific solver class to provide the necessary type information.
         *
         * @tparam FN The type of function to be integrated.
         */
        template<typename FN>
        struct IntegrationTraits;

        /**
         * @brief Specialization of IntegrationTraits for the Trapezoid solver.
         *
         * @tparam FN The type of function to be integrated.
         * @tparam T The type of the argument for the function.
         */
        template<typename FN, typename T>
        struct IntegrationTraits< Trapezoid< FN, T > >
        {
            using FUNCTION_T = FN;                              /**< The type of the function to be integrated. */
            using ARG_T = T;                                    /**< The type of the argument for the function. */
            using RETURN_T = std::invoke_result_t< FN, ARG_T >; /**< The type of the return value of the function. */
        };

        /**
         * @brief Specialization of IntegrationTraits for the Romberg solver.
         *
         * @tparam FN The type of function to be integrated.
         * @tparam T The type of the argument for the function.
         */
        template<typename FN, typename T>
        struct IntegrationTraits< Romberg< FN, T > >
        {
            using FUNCTION_T = FN;                              /**< The type of the function to be integrated. */
            using ARG_T = T;                                    /**< The type of the argument for the function. */
            using RETURN_T = std::invoke_result_t< FN, ARG_T >; /**< The type of the return value of the function. */
        };

        /**
         * @brief Specialization of IntegrationTraits for the Simpson solver.
         *
         * @tparam FN The type of function to be integrated.
         * @tparam T The type of the argument for the function.
         */
        template<typename FN, typename T>
        struct IntegrationTraits< Simpson< FN, T > >
        {
            using FUNCTION_T = FN;                              /**< The type of the function to be integrated. */
            using ARG_T = T;                                    /**< The type of the argument for the function. */
            using RETURN_T = std::invoke_result_t< FN, ARG_T >; /**< The type of the return value of the function. */
        };
    } // namespace detail
}     // namespace nxx::integrate

#endif //INTEGRATIONTRAITS_HPP
