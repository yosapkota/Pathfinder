//
// Created by sapko on 11/18/2020.
//

#ifndef MAIN_CPP_DISJOINTSET_H
#define MAIN_CPP_DISJOINTSET_H

#include <cstdint>
using namespace std;

class DisjointSet{

public:
    DisjointSet(uint32_t n);
    ~DisjointSet();
    uint32_t find(uint32_t);
    void join(uint32_t, uint32_t);

private:
    uint32_t
        *elements, *rank;
};

#endif //MAIN_CPP_DISJOINTSET_H
