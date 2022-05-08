#include <iostream>
#include <cstdlib>
#include "sampler.h"
#include "DisjointSet.h"

using namespace std;
#define N 10000

Sampler sampler(N);

int main(int argc, char* argv[2]) {

    if(argc != 3){
        cout << "Please enter valid number of arguments." << endl;
        return 1;
    }
    /*
    int rows = stoi(argv[0]);
    int columns = stoi(argv[1]);
    if ((rows < 0 or rows > 50) or ( columns < 0 or columns > 50)){
        cout << "Please enter the rows and columns in the range 0-50." << endl;
        return 2;
    }
    */

    //Sampler
    //    sampler(10);

    for (int i=0;i<10;i++) {
        uint32_t val = sampler.sample();
        cout << val << endl;
    }

    return 0;
}

void generateMaze(uint32_t nR, uint32_t nC){
    int i=0;
    uint32_t maze[50][50];
    for(int r = 0; r < nR; r++){
        for(int c=0; c < nC; c++){
            maze[r][c] = 15;
        }
    }
    uint32_t n = nR*nC;
    DisjointSet dS(n);
    Sampler(4*n);

    while(i < n-1){
        int e = sampler.sample();
        /* while e references an exterior or nonexistent wall
        (r1,c1,dir1) <- decodeCell(e)
         Set (r2,c2) to cell adjacent to (r1,c1) in given direction
        while(dS.find(r1)== dS.find(r2)){
            ds.join(r1,r2);
         }
         i++;
         Remove wall between (r1,c1) and (r2,c2)

    }




}