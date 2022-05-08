#include <iostream>
#include "pathfinder.h"
#include "sampler.h"
#include "DisjointSetForest.h"
#include "stack.h"



using namespace std;

uint32_t encode(uint32_t row,uint32_t col,uint32_t dir,
                uint32_t nR,uint32_t nC) {
    uint32_t e = (dir * nR + row) * nC + col;
    return e;

}

void decode(uint32_t val,uint32_t &row,uint32_t &col,uint32_t &dir,
            uint32_t nR,uint32_t nC) {
        col = val % nC;
        val /= nC;
        row = val % nR;
        dir = val / nR;
}

void generateMaze(uint8_t maze[][MAX_COLS],int32_t nR,int32_t nC) {
    Sampler
        sampler(2*nR*nC-nR-nC);
    DisjointSetForest
        dsf(nR*nC);
    uint32_t
        nRemoved = 0,
        r,c,
        r2,c2,
        w1,w2,
        cell1,cell2;

    for(uint32_t r =0; r < nR; r++){
        for(uint32_t c =0; c < nC; c++){
            maze[r][c] = 15;
        }
    }
    // loop until nR * nC - 1 walls removed
    while (nRemoved < nR * nC - 1) {

        // get wall at random
        int32_t
            w = sampler.sample();

        // if it is a right wall...
        if (w < nR * (nC - 1)) {

            // calculate r,c,r2,c2,w1,w2
            w1 = WALL_RIGHT;
            w2 = WALL_LEFT;
            r = w / (nC-1);
            c = w % (nC-1);
            r2 = r;
            c2 = c +1;

            // encode cell1 and cell2
            cell1 = encode(r,c,0,nR,nC);
            cell2 = encode(r2,c2,0,nR,nC);

        } else {        // ... else it's a down wall

            // adjust w
                w -= nR * (nC-1);
                w1 = WALL_DOWN;
                w2 = WALL_UP;
            // calculate r,c,r2,c2,w1,w2
                r = w % (nR-1);
                c = w / (nR-1);
                r2 = r + 1;
                c2 = c;
            // encode cell1 and cell2
                cell1 = encode(r,c,0,nR, nC);
                cell2 = encode(r2,c2,0,nR,nC);
        }

        // if cell1 and cell2 are not connected...
        if (dsf.dsfFind(cell1) != dsf.dsfFind(cell2)) {

            // connect them
            dsf.dsfUnion(cell1,cell2);

            // remove w1 from r,c
            maze[r][c] &= ~w1;

            // remove w2 from r2,c2
            maze[r2][c2] &= ~w2;

            // increment removed count
            nRemoved++;
        }

    // end loop
    }

    // all done
}

void solveMaze(uint8_t maze[][MAX_COLS],int32_t nR,int32_t nC) {

    // s.push(encode(0,0,0,nR,nC))
    Stack<uint32_t> S;
    S.push(encode(0, 0, 0, nR, nC));

    // mark maze[0][0] as VISITED
    maze[0][0] |= VISITED;

    // loop forever
    while (true) {
        // decode top of stack into r,c,d
        uint32_t
                r, c, d;
        decode(S.peek(), r, c, d, nR, nC);

        //cout << "d after decoding :" << d << endl;

        // if r,c is (nR-1),(nC-1) then break
        if ((r == nR - 1) and (c == nC - 1)) {
            break;
        }
        // if d == 4, you're at a dead end
        if (d == 4) {
            // mark maze[r][c] as a DEAD_END
            maze[r][c] |= DEAD_END;
            // s.pop()
            S.pop();
        }
            // else
        else {
            int32_t r2, c2;
            int dR[4] = {-1, 0, 1, 0};
            int dC[4] = {0, 1, 0, -1};
            // calculate r2,c2 as neighbor in direction d
            r2 = r + dR[d];
            c2 = c + dC[d];
            //cout << dR[d] << endl;
            // replace top of stack with encode(r,c,d+1,nR,nC)
            S.pop();
            S.push(encode(r, c, d + 1, nR, nC));

            //cout << "r, r2 and c2: " << r << " " << r2 << " " << c2 << endl;

            // if no wall exists in direction d AND...
            // ... maze[r2][c2] is NOT VISITED then...

            int wall = 1 << d;
            //(maze[r2][c2] == (maze[r2][c2] | DEAD_END))
            if ( (maze[r][c] & wall) == 0 and (maze[r2][c2] & VISITED) == 0) {
                // s.push(encode(r2,c2,0,nR,nC))
                S.push(encode(r2, c2, 0, nR, nC));
                // mark maze[r2][c2] as VISITED
                maze[r2][c2] |= VISITED;
            }
            // end if

            // end if again
        }
            // end loop
    }
            // all done

    }

    int main(int argc, char *argv[]) {
        int32_t
                nR, nC;
        uint8_t
                maze[MAX_ROWS][MAX_COLS];

        if (argc != 3) {
            cout << "Usage: " << argv[0] << " numrows numcols" << endl;
            return 1;
        }

        nR = strtol(argv[1], nullptr, 10);
        nC = strtol(argv[2], nullptr, 10);

        // verify that 0 < nR,nC <= 50

       if((nR <= 0 or nR > 50) or (nC <= 0 or nC > 50)){
            cout << "Enter the valid range." << endl;
            return 2;
        }

        //==============================================
        // this is just some test stuff
        //
        /*
        Sampler
                sampler(nR);

        cout << nC << endl;
        for (int i = 0; i < nR; i++) {
            uint32_t val = sampler.sample();
            std::cout << val << std::endl;
        }

        //==============================================
        //
        */

        // call maze generator
        generateMaze(maze, nR, nC);

        // call maze solver
       solveMaze(maze, nR, nC);

        // call Dr. Bob's output function
        printMaze(maze, nR, nC);


        return 0;
    }