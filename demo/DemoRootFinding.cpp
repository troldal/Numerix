// ================================================================================================
// This demo shows how to use the nxx::roots namespace to find the roots of arbitrary functions.
// ================================================================================================

#include "_external.hpp"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <Deriv.hpp>
#include <Roots.hpp>
#include <concepts>

using NXX_FLOAT = double;//boost::multiprecision::cpp_bin_float_50;

// template<>
// struct fmt::formatter< NXX_FLOAT > : fmt::formatter< double >
// {
//     auto format(const NXX_FLOAT& d, fmt::format_context& ctx) const
//     {
//         return fmt::formatter< double >::format(static_cast< double >(d), ctx);
//     }
// };

int main()
{
    using namespace nxx::roots;
    using namespace boost::multiprecision;
    std::cout << std::fixed << std::setprecision(8);
    auto                                        func   = []< nxx::IsFloat VAL_T >(VAL_T x) { return x * x - decltype(x)(5.0); };
    constexpr std::pair< NXX_FLOAT, NXX_FLOAT > bounds = { 0.0, 2.5 };

    // ============================================================================================
    // The nxx::roots namespace contains a number of root-finding algorithms, for finding the roots
    // of arbitrary functions. The algorithms are implemented as objects that can be used to iterate
    // towards a solution. The algorithms are:
    //
    // 1. Ridders
    // 2. Bisection
    // 3. Discrete Newton
    // 4. Newton
    //
    // These algorithms can be used directly, by manually iterating towards a solution, or they can
    // be used indirectly, by using the fsolve() or fdfsolve() functions, which will automatically
    // iterate until a solution is found. The fsolve() function can be used with bracketing methods
    // (Ridders and Bisection), while the fdfsolve() function can be used with non-bracketing methods
    // (Discrete Newton and Newton) that require a derivative of the function.
    //
    // The easiest way to use the algorithms is to use the fsolve() and fdfsolve() functions, which
    // will automatically iterate until a solution is found. The following code shows how to use
    // the fsolve() and fdfsolve() functions to find the roots of the polynomial f(x) = x^2 - 5.
    // (Note that to find the roots of a polynomial, it is better to use the polysolve function
    // from the nxx::poly namespace, which is much faster and more accurate than the root-finding
    // algorithms in the nxx::roots namespace. However, as an example of how to use the root-finding
    // algorithms, it will work just fine.)
    //
    // It should be noted that both the fsolve() and fdfsolve() functions returns a tl::expected
    // object (std::expected when C++23 comes in widespread use), which can either contain a value
    // or an error. The error can be checked by calling the has_value() function, and the value can
    // be retrieved by calling the value() function. The value() function will throw an exception
    // if the expected object does not contain a value. The value can also be retrieved by using
    // the * operator, which will return a reference to the value. If the expected object does not
    // contain a value, the result of using the * operator is undefined.
    // ============================================================================================

    auto terminator = [&](const auto& data) {
        auto [iter, lower, guess, upper] = data;
        auto eval                        = func(guess);

        if (iter == 0) {
            std::cout << "----------------------------------------------------------------------------------\n";
            std::cout << fmt::format("{:>10} | {:>15} | {:>15} | {:>15} | {:>15} ", "#", "Lower", "Guess", "Upper", "Eval") << "\n";
            std::cout << "----------------------------------------------------------------------------------\n";
        }

        std::cout << fmt::format("{:10} | {:15.10f} | {:15.10f} | {:15.10f} | {:15.10f}", iter, lower, guess, upper, eval) << "\n";

        BracketTerminator term;

        if (term(data) && eval >= 0.0) {
            std::cout << "----------------------------------------------------------------------------------\n";
            return true;
        }
        return false;
    };

    std::cout << "\nCompute the root of the polynomial f(x) = x^2 - 5 using bracketing methods:\n";
    std::cout << "Bisection Method:         \n" << fsolve< Bisection >(func, { 0.0, 2.5 }, terminator).result() << std::endl;
    std::cout << "Ridder's Method:          \n" << fsolve< Ridder >(func, bounds, terminator).result() << std::endl;
    std::cout << "Regula Falsi Method:      \n" << fsolve< RegulaFalsi >(func, bounds, terminator).result() << std::endl << std::endl;

    // std::cout << "\nCompute the root of the polynomial f(x) = x^2 - 5 using polishing methods:\n";
    // std::cout << "Newton's Method:          " << *fdfsolve< Newton >(func, nxx::deriv::derivativeOf(func), NXX_FLOAT(1.25)) << std::endl
    // <<
    //     std::endl;

    // Note that the Discrete Newton's Method uses the numerical derivative of the function, while
    // Newton's Method requires a separate function for the derivative.

    // ============================================================================================
    // As mentioned, the fsolve() and fdfsolve() functions return a tl::expected object, which can
    // either contain a value or an error. This is useful if the user wants to check if the
    // algorithm has converged, or if the user wants to check if the algorithm has failed. The
    // following code shows how to use the fsolve() and fdfsolve() functions to find the roots
    // of the function f(x) = log(x) and how to check if the algorithm has failed.
    // ============================================================================================
    // std::cout << "Compute the root of the function f(x) = log(x) using the Bisection method:\n\n";
    // auto print_error = [](auto error) {
    //     std::cout << "Error Description: " << error.what() << std::endl;
    //     std::cout << "Error Type:        " << error.typeAsString() << std::endl;
    //     std::cout << "Last Value:        " << error.value() << std::endl;
    //     std::cout << "Iterations:        " << error.iterations() << std::endl << std::endl;
    // };
    //
    // auto log_func = [](std::floating_point auto x) { return std::log(x); };

    // std::cout << "Initial Bracket:   [5.0, 10.0]\n"; // This bracket does not contain a root
    // auto root = fsolve< Bisection >(log_func, { 5.0, 10.0 });
    // if (!root) print_error(root.error());

    // std::cout << "Initial Bracket:   [-5.0, 10.0]\n"; // The function is undefined at x <= 0
    // root = fsolve< Bisection >(log_func, { -5.0, 10.0 });
    // if (!root) print_error(root.error());

    // std::cout << "Initial Bracket:   [0.1, 200.0]\n";    // This bracket contains a root, but will require many iterations
    // root = fsolve< Bisection >(log_func, { 0.1, 200.0 }, 1.0E-15, 5);
    // if (!root) print_error(root.error());

    // The error object is a subclass of the RootError class, which is a subclass of the std::runtime_error
    // class. This means that the error object can be used in a try-catch block, as shown below.
    // try { throw root.error(); }
    // catch (const RootError& e) { std::cout << "Exception caught: " << e.what() << std::endl << std::endl; }
    // TODO: This doesn't work on clang-cl

    // The error object from the fdfsolve() function works in the same way.
    // std::cout << "Compute the root of the function f(x) = log(x) using the DNewton method:\n\n";
    // std::cout << "Initial Guess = 0.0:\n"; // The function is undefined at x <= 0
    // root = fdfsolve< Newton >(log_func, nxx::deriv::derivativeOf(log_func), 0.0, 1.0E-15);
    // if (!root.has_value()) print_error(root.error());

    // std::cout << "Initial Guess = 1E-3:\n"; // This guess is close to the root, but will require many iterations
    // root = fdfsolve< Newton >(log_func, nxx::deriv::derivativeOf(log_func), 1E-3, 1.0E-15, 5);
    // if (!root.has_value()) print_error(root.error());

    // ============================================================================================
    // If more fine-grained control is needed, the algorithms can be used directly. Both the bracketing
    // solvers and the polishing solvers behaves similarly. The evaluate() member function can be used
    // to evaluate the function at a given point (to check if convergence has been reached), and the
    // iterate() member function can be used to proceed with one iteration. The result() member function
    // can be used to retrieve the current bracketing interval or the current guess, depending on the
    // type of solver. The init() member function can be used to initialize the solver with a bracketing
    // interval or a guess, depending on the type of solver.
    // The following code shows how to use the bracketing solvers and the polishing solvers directly.
    // ============================================================================================

    //
    // // Lambda function for printing the results of the bracketing solvers:
    // auto bracket_root = []< typename SOLVER_T >(SOLVER_T solver) {
    //     //, std::pair< double, double > bounds) {
    //     // Print the header:
    //     std::cout << "----------------------------------------------------------------------------------\n";
    //     std::cout << fmt::format("{:>10} | {:>15} | {:>15} | {:>15} | {:>15} ", "Iter", "Upper", "Lower", "Root", "Error") << std::endl;
    //     std::cout << "----------------------------------------------------------------------------------\n";
    //
    //     // Create variables for the iterations.
    //     std::array< std::pair< NXX_FLOAT, NXX_FLOAT >, 2 > guesses; // Stores the endpoints of the bracketing interval
    //     decltype(guesses.begin())                          min {};     // Stores the endpoint with the smallest absolute value
    //
    //     // Initialize the solver:
    //     // solver.init(bounds);
    //
    //     // Iterate until convergence (or until 100 iterations have been performed):
    //     for (auto i = 0; i <= nxx::iterations<NXX_FLOAT>(); ++i) {
    //         // Retrieve the current bracketing interval, and evaluate the function at the endpoints:
    //         guesses = { std::make_pair(std::get<0>(solver.current()), abs(solver.evaluate(std::get<0>(solver.current())))),
    //                     std::make_pair(std::get<2>(solver.current()), abs(solver.evaluate(std::get<2>(solver.current())))) };
    //
    //         // Find the endpoint which has the smallest error:
    //         min = std::min_element(guesses.begin(), guesses.end(), [](const auto& a, const auto& b) {
    //             return abs(a.second) < abs(b.second);
    //         });
    //
    //         // Print the current iteration:
    //         std::cout << fmt::format("{:10} | {:15.10f} | {:15.10f} | {:15.10f} | {:15.10f} ",
    //                                  i,
    //                                  // Iteration number
    //                                  std::get<0>(solver.current()),
    //                                  // Upper endpoint
    //                                  std::get<2>(solver.current()),
    //                                  // Lower endpoint
    //                                  min->first,                // Root
    //                                  min->second)               // Error
    //             << std::endl;
    //
    //         // Check if convergence has been reached:
    //         if (min->second < nxx::epsilon< typename decltype(solver)::RESULT_T >()) break;
    //
    //         // Perform one iteration:
    //         solver.iterate();
    //     }
    //
    //     // Print the final result:
    //     std::cout << std::fixed << std::setprecision(50) << "CONVERGED! Root found at: " << min->first << "\n";
    //     std::cout << std::fixed << std::setprecision(50) << "Function value at root:   " << solver.evaluate(min->first) << "\n";
    //     std::cout << "----------------------------------------------------------------------------------\n\n";
    // };
    //
    //
    //
    // std::cout << "Manual root-finding using Ridder's method:" << std::endl;
    // bracket_root(Ridder(func, { 0.0, 2.5 }));
    // bracket_root(Ridder(func, bounds));
    //
    // std::cout << "Manual root-finding using the bisection method:" << std::endl;
    // bracket_root(Bisection(func, { 0.0, 2.5 }));
    // bracket_root(Bisection(func, bounds));
    //
    // std::cout << "Manual root-finding using the regula falsi method:" << std::endl;
    // bracket_root(RegulaFalsi(func, { 0.0, 2.5 }));
    // bracket_root(RegulaFalsi(func, bounds));

    // // Lambda function for printing the results of the polishing solvers:
    // auto polish_root = [](auto solver, NXX_FLOAT guess) {
    //     // Print the header:
    //     std::cout << "------------------------------------------------------------------\n";
    //     std::cout << fmt::format("{:>10} | {:>25} | {:>25} ", "Iter", "Root", "Error") << std::endl;
    //     std::cout << "------------------------------------------------------------------\n";
    //
    //     // Initialize the solver:
    //     // solver.init(guess);
    //
    //     // Iterate until convergence (or until 100 iterations have been performed):
    //     for (int i = 0; i <= 100; ++i) {
    //         std::cout << std::fixed << std::setprecision(10);
    //
    //         // Print the current iteration:
    //         std::cout << fmt::format("{:10} | {:25.20f} | {:25.20f} ",
    //                                  i,
    //                                  // Iteration number
    //                                  solver.current(),
    //                                  // Current guess
    //                                  abs(solver.evaluate(solver.current())))    // Error
    //             << std::endl;
    //
    //         // Check if convergence has been reached:
    //         if (abs(solver.evaluate(solver.current())) < nxx::epsilon<NXX_FLOAT>()) break;
    //
    //         // Perform one iteration:
    //         solver.iterate();
    //     }
    //
    //     // Print the final result:
    //     std::cout << std::fixed << std::setprecision(50) << "CONVERGED! Root found at: " << solver.current() << "\n";
    //     std::cout << std::fixed << std::setprecision(50) << "Function value at root:   " << solver.evaluate(solver.current()) << "\n";
    //     std::cout << "------------------------------------------------------------------\n\n";
    // };
    //
    // std::cout << "Manual root-finding using the Newton-Raphson method:" << std::endl;
    // polish_root(Newton(func, nxx::deriv::derivativeOf(func), NXX_FLOAT(1.25)), NXX_FLOAT(1.25));
    //
    // std::cout << "Manual root-finding using the Secant method:" << std::endl;
    // polish_root(Secant(func, nxx::deriv::derivativeOf(func), NXX_FLOAT(1.25)), NXX_FLOAT(1.25));
    //
    // std::cout << "Manual root-finding using the Steffensen method:" << std::endl;
    // polish_root(Steffensen(func, nxx::deriv::derivativeOf(func), NXX_FLOAT(1.25)), NXX_FLOAT(1.25));

    return 0;
}
