//
// Created by sapko on 11/18/2020.
//
#include "DisjointSet.h"

DisjointSet::DisjointSet(uint32_t n) {
    uint32_t num = n;
    elements = new uint32_t [num];
    rank = new uint32_t [num];

    for(uint32_t i=0; i < n; i++){
        elements[i] = i;
        rank[i] = 0;
    }

}

DisjointSet::~DisjointSet() {
    delete [] elements, rank;
}

uint32_t DisjointSet::find(uint32_t a) {
    if(elements[a] != a){
        elements[a] = find(elements[a]);
    }
    return elements[a];
}

void DisjointSet::join(uint32_t a, uint32_t b) {
    a = find(a);
    b = find(b);
    if(a != b){
        if(rank[a] < rank[b]){
            elements[a] = b;
        }
        else{
            if(rank[a] == rank[b]){
                rank[a] = rank[a] + 1;
            }
            elements[b] = a;
        }
    }
}
