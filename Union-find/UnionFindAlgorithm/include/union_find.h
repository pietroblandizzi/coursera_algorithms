/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include <vector>

class UnionFind
{
public:
    using v_size = std::vector<unsigned>::size_type;

    UnionFind (v_size N);
    bool Connected (unsigned p, unsigned q);
    void Union(unsigned p, unsigned q);

private:
    unsigned Root(unsigned i);
    std::vector<unsigned> obj_;
    std::vector<unsigned> size_obj_;
};


#endif // UNION_FIND_H_
