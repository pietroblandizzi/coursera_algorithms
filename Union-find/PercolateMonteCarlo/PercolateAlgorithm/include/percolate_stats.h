/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef PERCOLATE_STATS_H_
#define PERCOLATE_STATS_H_

#include <vector>
#include <random>

#include "percolate.h"

class PercolationStats
{
public:


    PercolationStats (int N, int trials);
    double Mean();                        // sample mean of percolation threshold
    double Stddev();                        // sample standard deviation of percolation threshold
    double ConfidenceLo();                  // low  endpoint of 95% confidence interval
    double ConfidenceHi();                  // high endpoint of 95% confidence interval
    void Exec();

private:
    Percolation percolation_;
    std::vector<double> results_;
    int n_;
    int trials_;
    double mean_;
    double stddev_;
    double c_low_;
    double c_high_;
};

#endif // PERCOLATE_STATS_H_

