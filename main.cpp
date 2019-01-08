#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "A_star.h"
using namespace std;

/* This program is used to implement a type of the A* algorithm.
 * The A* algorithm finds a path from the "start" to the "end" in the "maze".
 * The "maze", "start", and "end" can be changed according to the demand. */

int main()
{
      // initialize the map using a 2D matrix. 
      // 1 represents obstacle, 0 represents feasible node
    vector<vector<int>> maze = {
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,1,0,1,0,0,0,0,1},
        {1,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,1,1,1},
        {1,1,1,0,0,0,0,0,1,1,0,1},
        {1,1,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1}
    };
    Astar astar;
    astar.InitAstar(maze);

      // initialize start node and end node
    Node start(1,1);
    Node end(6,10);
      // Use A* to search path
    list<Node *> path = astar.GetPath(start, end, false);
      // Print
    for(auto &p:path)
        cout << '(' << p->x << ',' << p->y << ')' << endl;

    system("pause");
    return 0;
}
