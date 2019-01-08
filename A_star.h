#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <math.h>
using namespace std;


const int costH = 10;  // cost of horizontal or vertical move
const int costD = 14;  // cost of diagonal move

struct Node
{
    int x,y;           // coordinates of Nodes
    int F,G,H;         // F=G+H -- evaluation function
    Node *parent;      // coordinates of parent
    Node(int _x,int _y):x(_x),y(_y),F(0),G(0),H(0),parent(NULL){}
    // node initialization
};

/* A* algo class */
class Astar
{
public:
    void InitAstar(vector<vector<int>> &_maze);
    list<Node *> GetPath(Node &startNode,Node &endNode,bool isIgnoreCorner);

private:
    Node *findPath(Node &startNode,Node &endNode,bool isIgnoreCorner);
    vector<Node *> getSurroundNodes(const Node *node,bool isIgnoreCorner) const;
    bool isCanReach(const Node *node,const Node *target,
                    bool isIgnoreCorner) const;
	                // to evaluate whether the node can be used for next step
	                
    Node *isInList(const list<Node *> &list,const Node *node) const;
	// to evaluate whether the node is in openList or closeList
	
    Node *getLeastFNode();
	// return the node with min F from openList

      // to calculate G, H, F
    int calcG(Node *temp_start,Node *node);
    int calcH(Node *node,Node *end);
    int calcF(Node *node);

private:
    vector<vector<int>> maze;
    list<Node *> open_list;
    list<Node *> close_list;
};

