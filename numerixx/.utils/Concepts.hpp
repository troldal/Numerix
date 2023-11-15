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

#ifndef NUMERIXX_CONCEPTS_HPP
#define NUMERIXX_CONCEPTS_HPP

// ===== Standard Library Includes
#include <complex>

namespace nxx
{

    /**
     * @brief Concept to check if a type is a complex number.
     * @tparam T The type to check.
     */
    template< typename T >
    concept IsComplex = requires(T x) {
                            typename T::value_type;
                            {
                                std::real(x)
                            } -> std::floating_point;
                            {
                                std::imag(x)
                            } -> std::floating_point;
                        };

    /**
     * @brief Concept checking whether a type is a callable function object that returns a floating point type.
     * @tparam FN The type to check.
     */
    template< typename Func >
    concept IsFloatInvocable = requires(Func f) {
                                   requires std::floating_point< std::invoke_result_t< Func, float > >;
                                   requires std::floating_point< std::invoke_result_t< Func, double > >;
                                   requires std::floating_point< std::invoke_result_t< Func, long double > >;
                               };

}    // namespace nxx

namespace nxx::poly {
    template< typename T >
    requires std::floating_point< T > || IsComplex< T >
    class Polynomial;

    template< typename POLY >
    concept IsPolynomial = std::same_as< POLY, Polynomial< typename POLY::value_type > >;
}
#endif    // NUMERIXX_CONCEPTS_HPP
