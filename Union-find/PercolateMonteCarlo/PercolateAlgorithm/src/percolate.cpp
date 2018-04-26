/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <percolate.h>

#include <stdexcept>
#include <iostream>

Percolation::Percolation(v_size N) :
    obj_((N * N) + 2), size_obj_((N * N) + 2), obj_open_close_((N * N) + 2),
    number_open_sites_(0), n_(N), fake_root_index_(N * N), fake_bottom_index_((N * N) + 1),
    gen(rd()), dis(0, N - 1)
{
    ResetState();
}

void Percolation::ResetState()
{
    for (v_size i = 0; i < n_* n_ + 2; ++i)
    {
        obj_.at(i) = i;
        size_obj_.at(i) = 1;
        // all the sites are close
        obj_open_close_.at(i) = 0;
    }
    // first row connected to fake root (N*N) and the last to fake and (N*N)+1
    for (v_size i = 0; i < n_; ++i)
    {
        obj_.at(i) = (n_* n_);
        obj_.at((n_ * n_) - i - 1) = (n_ * n_) + 1;
    }
    number_open_sites_ = 0;
}

int Percolation::Root(int i)
{
    if (i >= obj_.size())
    {
        throw std::runtime_error("the id is not in a valide range");
    }
    while (i != obj_.at(i))
    {
        // path compression
        obj_.at(i) = obj_.at(obj_.at(i));
        i = obj_.at(i);
    }
    return i;
}

bool Percolation::Connected(int p, int q)
{
    return (Root(p) == Root(q));
}

void Percolation::Union(int p, int q)
{
    auto i = Root(p);
    auto j = Root(q);

    if (i == j) return;
    // weighting trees
    if (size_obj_.at(i) < size_obj_.at(j))
    {
        obj_.at(i) = j;
        size_obj_.at(j) += size_obj_.at(i);
    } else
    {
        obj_.at(j) = i;
        size_obj_.at(i) += size_obj_.at(j);
    }
}

int Percolation::GetIndexFromRowColumn(int row, int col)
{
    return (row * n_ + col);
}

void Percolation::Open(int row, int col)
{
    if (IsFull(row, col))
    {
        auto i = GetIndexFromRowColumn(row,col);
        obj_open_close_.at(i) = 1;
        number_open_sites_++;
        ConnectToAdjOpenSites(row, col);
    }
}

void Percolation::ConnectToAdjOpenSites(int row, int col)
{
    if (row - 1 >= 0)
    {
        if (IsOpen(row - 1,col))
        {
            Union(GetIndexFromRowColumn(row - 1, col),GetIndexFromRowColumn(row, col));
        }
    }
    if (row + 1 < n_)
    {
        if (IsOpen(row + 1,col))
        {
            Union(GetIndexFromRowColumn(row + 1, col),GetIndexFromRowColumn(row, col));
        }
    }
    if (col - 1 >= 0)
    {
        if (IsOpen(row,col - 1))
        {
            Union(GetIndexFromRowColumn(row, col - 1),GetIndexFromRowColumn(row,col));
        }
    }
    if (col + 1 < n_)
    {
        if (IsOpen(row,col + 1))
        {
            Union(GetIndexFromRowColumn(row,col + 1),GetIndexFromRowColumn(row,col));
        }
    }
}

bool Percolation::IsOpen(int row, int col)
{
    auto i = GetIndexFromRowColumn(row, col);
    return obj_open_close_.at(i) == 1 ? true : false;
}

bool Percolation::IsFull(int row, int col)
{
    return !IsOpen(row,col);
}

int Percolation::NumberOfOpenSites()
{
    return number_open_sites_;
}

bool Percolation::Percolates()
{
    return Connected(fake_root_index_, fake_bottom_index_);
}

double Percolation::Execute()
{
    ResetState();
    int row = 0;
    int col = 0;
    while (!Percolates())
    {
        row = dis(gen);
        col = dis(gen);
        Open(row, col);
    }
    return number_open_sites_ / (double)(n_ * n_);
}
