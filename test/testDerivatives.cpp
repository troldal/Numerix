//
// Created by Kenneth Balslev on 24/02/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <roots/Roots.hpp>

#include <cmath>
#include <functional>
#include <numbers>
#include <vector>

TEST_CASE("Numerical Derivatives Test", "[derivatives]")
{
    using namespace nxx::deriv;

    std::vector< std::function< double(double) > > functions {
        [](double x) { return std::pow(x, 3) - 2 * x + 5; },
        [](double x) { return 2 * std::pow(x, 2) + 3 * x - 4; },
        [](double x) { return std::sin(x) + std::cos(x); },
        [](double x) { return std::log(x) + 2 * x; },
        [](double x) { return 4 * std::pow(x, 4) - 3 * std::pow(x, 3) + 2 * std::pow(x, 2) - x + 1; },
        [](double x) { return std::exp(x) + 3 * std::pow(x, 2); },
        [](double x) { return std::cos(x * x) - 2 * x; },
        [](double x) { return std::sqrt(x) + 2.0 / x; },
        [](double x) { return 3 * std::pow(x, 3) - 4 * std::pow(x, 2) + 5 * x - 6; },
        [](double x) { return 1.0 / (x + 1); }
    };

    std::vector< double > evals { 2.0, 1.0, std::numbers::pi / 4, std::numbers::e, 0.0, 1.0, std::numbers::pi, 4.0, 2.0, 0.0 };

    std::vector< double > first_derivatives { 10.0, 7.0, 0.0, 2.367879441, -1.0, std::numbers::e + 6, 0.703662284, 0.125, 25.0, -1.0 };

    std::vector< double > second_derivatives {
        12.0, 4.0, -std::sqrt(2), -1.0 / std::pow(std::numbers::e, 2), 4, std::numbers::e + 6, 36.497192117735, 0.03125, 28.0, 2.0
    };

    size_t i = static_cast<size_t>(GENERATE(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));

    // ============================================================================================
    // Computation of 1st order derivatives
    // ============================================================================================

    SECTION("nxx::deriv::central")
    {
        REQUIRE_THAT(*nxx::deriv::central(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_THROWS(nxx::deriv::central([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::central([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::central([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("nxx::deriv::forward")
    {
        REQUIRE_THAT(*nxx::deriv::forward(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_NOTHROW(nxx::deriv::forward([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::forward([](double x){return std::sqrt(x);}, 0.0).has_value() == true);
        REQUIRE(nxx::deriv::forward([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("nxx::deriv::backward")
    {
        REQUIRE_THAT(*nxx::deriv::backward(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_THROWS(nxx::deriv::backward([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::backward([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::backward([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1CentralRichardson")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1CentralRichardson>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order1CentralRichardson>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1CentralRichardson>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order1CentralRichardson>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1Central3Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1Central3Point>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order1Central3Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1Central3Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order1Central3Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1Central5Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1Central5Point>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order1Central5Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1Central5Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order1Central5Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1ForwardRichardson")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1ForwardRichardson>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_NOTHROW(nxx::deriv::derivative<Order1ForwardRichardson>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1ForwardRichardson>([](double x){return std::sqrt(x);}, 0.0).has_value() == true);
        REQUIRE(nxx::deriv::derivative<Order1ForwardRichardson>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1Forward2Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1Forward2Point>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.001));
        REQUIRE_NOTHROW(nxx::deriv::derivative<Order1Forward2Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1Forward2Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == true);
        REQUIRE(nxx::deriv::derivative<Order1Forward2Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1Forward3Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1Forward3Point>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_NOTHROW(nxx::deriv::derivative<Order1Forward3Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1Forward3Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == true);
        REQUIRE(nxx::deriv::derivative<Order1Forward3Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1BackwardRichardson")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1BackwardRichardson>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order1BackwardRichardson>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1BackwardRichardson>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order1BackwardRichardson>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1Backward2Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1Backward2Point>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order1Backward2Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1Backward2Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order1Backward2Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order1Backward3Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order1Backward3Point>(functions[i], evals[i]) - first_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.000001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order1Backward3Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order1Backward3Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order1Backward3Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    // ============================================================================================
    // Computation of 2nd order derivatives
    // ============================================================================================

    SECTION("Order2Central3Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order2Central3Point>(functions[i], evals[i]) - second_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.0001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order2Central3Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order2Central3Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order2Central3Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order2Central5Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order2Central5Point>(functions[i], evals[i]) - second_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.0001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order2Central5Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order2Central5Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order2Central5Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order2Forward3Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order2Forward3Point>(functions[i], evals[i]) - second_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.001));
        REQUIRE_NOTHROW(nxx::deriv::derivative<Order2Forward3Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order2Forward3Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == true);
        REQUIRE(nxx::deriv::derivative<Order2Forward3Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order2Forward4Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order2Forward4Point>(functions[i], evals[i]) - second_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.001));
        REQUIRE_NOTHROW(nxx::deriv::derivative<Order2Forward4Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order2Forward4Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == true);
        REQUIRE(nxx::deriv::derivative<Order2Forward4Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order2Backward3Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order2Backward3Point>(functions[i], evals[i]) - second_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order2Backward3Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order2Backward3Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order2Backward3Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }

    SECTION("Order2Backward4Point")
    {
        REQUIRE_THAT(*nxx::deriv::derivative<Order2Backward4Point>(functions[i], evals[i]) - second_derivatives[i], Catch::Matchers::WithinAbs(0.0, 0.001));
        REQUIRE_THROWS(nxx::deriv::derivative<Order2Backward4Point>([](double x){return std::sqrt(x);}, 0.0).value());
        REQUIRE(nxx::deriv::derivative<Order2Backward4Point>([](double x){return std::sqrt(x);}, 0.0).has_value() == false);
        REQUIRE(nxx::deriv::derivative<Order2Backward4Point>([](double x){return std::sqrt(x);}, 1.0).has_value() == true);
    }
}