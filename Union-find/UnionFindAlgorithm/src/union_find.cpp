/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <union_find.h>

#include <stdexcept>

UnionFind::UnionFind(v_size N) :
    obj_(N), size_obj_(N)
{
    for (v_size i = 0; i < N; ++i) {
        obj_.at(i) = i;
        size_obj_.at(i) = 1;
    }
}

unsigned UnionFind::Root(unsigned i)
{
    if (i >= obj_.size()) {
        throw std::runtime_error("the id is not in a valide range");
    }
    while (i != obj_.at(i)) {
        // path compression
        obj_.at(i) = obj_.at(obj_.at(i));
        i = obj_.at(i);
    }
    return i;
}

bool UnionFind::Connected(unsigned p, unsigned q)
{
    return (Root(p) == Root(q));
}

void UnionFind::Union(unsigned p, unsigned q)
{
    auto i = Root(p);
    auto j = Root(q);

    if (i == j) return;
    // weighting trees
    if (size_obj_.at(i) < size_obj_.at(j)) {
        obj_.at(i) = j;
        size_obj_.at(j) += size_obj_.at(i);
    } else {
        obj_.at(j) = i;
        size_obj_.at(i) += size_obj_.at(j);
    }
}
