//****************************************************************************
// Copyright © 2017 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2017-08-06.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <cmath>
#include <iostream>
#include <vector>

namespace SudokuLib
{
    template <typename T>
    void doFactorize(std::vector<T>& factors, T n)
    {
        if (n <= 3)
        {
            factors.push_back(n);
            return;
        }

        while (n % 2 == 0)
        {
            factors.push_back(2);
            n /= 2;
        }

        while (n % 3 == 0)
        {
            factors.push_back(3);
            n /= 3;
        }

        if (n != 1)
        {
            auto max = T(std::ceil(std::sqrt(n)));
            auto inc = 4;
            for (T i = 5; i <= max; i += inc)
            {
                if (n % i == 0)
                {
                    do
                    {
                        factors.push_back(i);
                        n /= i;
                    } while (n % i == 0);
                    if (n == 1)
                        break;
                    max = T(std::ceil(std::sqrt(n)));
                }
                inc ^= 6;
            }
            if (n != 1)
                factors.push_back(n);
        }
    }

    template <typename T,
              typename std::enable_if<std::is_signed<T>::value, int>::type = 0>
    std::vector<T> factorize(T n)
    {
        std::vector<T> factors;
        if (n < -1)
        {
            factors.push_back(-1);
            n = -n;
        }
        doFactorize(factors, n);
        return factors;
    }

    template <typename T,
              typename std::enable_if<std::is_unsigned<T>::value, int>::type = 0>
    std::vector<T> factorize(T n)
    {
        std::vector<T> factors;
        doFactorize(factors, n);
        return factors;
    }

    template <typename T, typename It>
    std::pair<T, T>
    findClosestFactors(T n, std::pair<T, T> bestFactors, T squareRoot,
                       T factor, It firstRemainingFactor,
                       It lastRemainingFactor)
    {
        auto bestDiff = bestFactors.first - bestFactors.second;
        auto otherFactor = n / factor;
        auto maxFactor = std::max(factor, otherFactor);
        auto minFactor = std::min(factor, otherFactor);
        auto diff = maxFactor - minFactor;
        if (diff < bestDiff)
            bestFactors = {maxFactor, minFactor};
        if (factor > squareRoot)
            return bestFactors;
        T newFactor = 0;
        for (auto it = firstRemainingFactor; it != lastRemainingFactor; ++it)
        {
            if (*it != newFactor)
            {
                newFactor = *it;
                bestFactors = findClosestFactors(n, bestFactors,
                                                       squareRoot,
                                                       factor * newFactor,
                                                       it + 1,
                                                       lastRemainingFactor);
            }
        }
        return bestFactors;
    }

    template <typename T>
    std::pair<T, T> findClosestFactors(T n)
    {
        if (n == 0)
            return {0, 0};
        auto m = n >= 0 ? n : -n;
        auto squareRoot = T(std::ceil(std::sqrt(m)));
        if (squareRoot * squareRoot == m)
            return {squareRoot, n / squareRoot};
        auto factors = factorize(m);
        auto result = findClosestFactors(m, {m, 1}, squareRoot,
                                         factors.back(),
                                         factors.rbegin() + 1,
                                         factors.rend());

        if (n > 0)
            return result;
        else
            return {result.first, -result.second};
    }
}
