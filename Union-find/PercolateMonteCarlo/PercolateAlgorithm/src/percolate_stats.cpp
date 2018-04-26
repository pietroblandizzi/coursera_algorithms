 /*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <percolate_stats.h>

#include <stdexcept>
#include <iostream>
#include <numeric>
 
PercolationStats::PercolationStats(int N, int trials) : percolation_(N), results_(trials), n_(N), trials_(trials),
mean_(0.0), stddev_(0.0), c_low_(0.0), c_high_(0.0)
{
    
}
 
double PercolationStats::Mean()
{
   auto sum = std::accumulate(results_.begin(), results_.end(), 0.0);  
   mean_ =  (double)sum/(double)trials_;
   return mean_;
}

double PercolationStats::Stddev()
{
   auto acc = 0.0;
   for(auto r : results_)
   {
       auto tmp = r - mean_;
       acc += (tmp * tmp);
   }
   stddev_ = acc / (double)(trials_-1);
   return stddev_;
}

double PercolationStats::ConfidenceLo()
{
    c_low_ = mean_ - ((1.96 * std::sqrt(stddev_)) /(double)std::sqrt(trials_));
    return c_low_;
}

double PercolationStats::ConfidenceHi()
{
    c_high_ = mean_ + ((1.96 * std::sqrt(stddev_)) /(double)std::sqrt(trials_));
    return c_high_;
}

void PercolationStats::Exec()
{
    for(auto i = 0; i < trials_; ++i)
    {
       results_.at(i) = percolation_.Execute();
    }
    
    std::cout << "Mean: " << Mean() << std::endl;  
    std::cout << "Standard Deviation: " << Stddev() << std::endl;  
    std::cout << "Confidence Low: " << ConfidenceLo() << std::endl;      
    std::cout << "Confidence High: " << ConfidenceHi() << std::endl;     
    
}
