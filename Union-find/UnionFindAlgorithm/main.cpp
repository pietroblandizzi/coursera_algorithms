/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "union_find.h"

#include <iostream>


int main(int argc, char **argv)
{

    UnionFind union_find(10);
    union_find.Union(4,3);
    union_find.Union(3,8);
    union_find.Union(6,5);
    union_find.Union(9,4);
    union_find.Union(2,1);

    std::cout << union_find.Connected(0,7) << std::endl;
    union_find.Union(8,9);
    union_find.Union(5,0);
    union_find.Union(7,2);
    union_find.Union(6,1);
    union_find.Union(1,0);

    std::cout << union_find.Connected(0,7) << std::endl;
    std::cout << union_find.Connected(8,9) << std::endl;

    return 0;
}
