#pragma once

#pragma once
#include <algorithm>    // Needed for the "max" function
#include <cmath>
#include <iostream>
#include <random>


  

// Pricing a European vanilla call option with a Monte Carlo method
template <class T>
T monte_carlo_call_price(const int& num_sims, const T& S, const T& K, const T& r, const T& v, const T& mat) {

    std::random_device rd;

    // Mersenne twister PRNG, initialized with seed from previous random device instance
    std::mt19937 gen(rd());
    std::normal_distribution<float> d(0, 1);;

    T S_adjust = S * exp(mat * (r - 0.5 * v * v));
    T S_cur(0.0);
    T payoff_sum(0.0);
    T sqrt_v2_mat = sqrt(v * v * mat);

    for (int i = 0; i < num_sims; i++) {
        
        double random_gauss = d(gen);
        S_cur = S_adjust * exp(sqrt_v2_mat * random_gauss);
        payoff_sum += max(S_cur - K, 0.0);
    }

    auto result = (payoff_sum / static_cast<double>(num_sims)) * exp(-r * mat);

    return result;
}
