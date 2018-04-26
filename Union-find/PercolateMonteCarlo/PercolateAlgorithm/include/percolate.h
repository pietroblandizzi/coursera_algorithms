/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef PERCOLATE_H_
#define PERCOLATE_H_

#include <vector>
#include <random>

class Percolation
{
public:
    using v_size = std::vector<int>::size_type;

    Percolation (v_size N);  // create n-by-n grid, with all sites blocked
    void Open(int row, int col);  // open site (row, col) if it is not open already
    bool IsOpen(int row, int col);  // is site (row, col) open?
    bool IsFull(int row, int col);  // is site (row, col) full?
    int NumberOfOpenSites();       // number of open sites
    bool Percolates();              // does the system percolate?
    double Execute();

private:
    int Root(int i);
    int GetIndexFromRowColumn(int row, int col);
    bool Connected(int p, int q);
    void Union(int p, int q);
    void ConnectToAdjOpenSites(int row, int col);
    void ResetState();
    std::vector<int> obj_;
    std::vector<unsigned> size_obj_;
    std::vector<int> obj_open_close_;
    int number_open_sites_;
    int n_;
    int fake_root_index_;
    int fake_bottom_index_;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis;
};

#endif // PERCOLATE_H_
