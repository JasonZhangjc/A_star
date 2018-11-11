#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "A_star.h"
using namespace std;

void Astar::InitAstar(vector<vector<int>> &_maze)
{
    maze=_maze;
}

int Astar::calcG(Node *temp_start,Node *node)
{
    int extraG=(abs(node->x - temp_start->x) + abs(node->y - temp_start->y)) == 1 ? costH : costD;
    int parentG=node->parent==NULL ? 0 : node->parent->G;
	                    // parent of initial node should be empty
    return parentG + extraG;
}

int Astar::calcH(Node *node,Node *end)
{
    return sqrt((double)(end->x - node->x) * (double)(end->x - node->x)
			   +(double)(end->y - node->y) * (double)(end->y - node->y)) * costH;
	                    // use Euclidean distance to calculate H
}

int Astar::calcF(Node *node)
{
    return node->G + node->H;
}

Node *Astar::getLeastFNode()
{
    if(!openList.empty())
    {
        auto resNode=openList.front();
        for(auto &node:openList)
            if(node->F < resNode->F)
                resNode=node;
        return resNode;
    }
    return NULL;
}

Node *Astar::findPath(Node &startNode,Node &endNode,bool isIgnoreCorner)
{
    openList.push_back(new Node(startNode.x,startNode.y));
	                    // put the source node in and open a new node
    while(!openList.empty())
    {
        auto curNode=getLeastFNode();     // find the node with min F
        openList.remove(curNode);         // delete current node from openList
        closeList.push_back(curNode);     // put current node into closeList

        // find a feasible cell from the 8 cells
        auto surroundNodes=getSurroundNodes(curNode,isIgnoreCorner);
        for(auto &target:surroundNodes)
        {
            // for a node, if it's not in openList, put it into openList,
			// and set current node as its parent, calculate F,G,H
            if(!isInList(openList,target))
            {
                target->parent=curNode;

                target->G=calcG(curNode,target);
                target->H=calcH(target,&endNode);
                target->F=calcF(target);

                openList.push_back(target);
            }

			// for a node, if it's in openList, calculate G,
			// if the G is greater than before, do nothing,
			// otherwise set current node as its parent and update G,F
            else
            {
                int tempG=calcG(curNode,target);
                if(tempG<target->G)
                {
                    target->parent=curNode;

                    target->G=tempG;
                    target->F=calcF(target);
                }
            }
            Node *resNode=isInList(openList,&endNode);
            if(resNode)
                return resNode; // return resNode instead of endNode, because of the deep copy
        }
    }

    return NULL;
}

list<Node *> Astar::GetPath(Node &startNode,Node &endNode,bool isIgnoreCorner)
{
    Node *result=findPath(startNode,endNode,isIgnoreCorner);
    std::list<Node *> path;

    //return path, if path is not found, return empty list
    while(result)
    {
        path.push_front(result);
        result=result->parent;
    }
    return path;
}

Node *Astar::isInList(const list<Node *> &list,const Node *node) const
{
    // evaluate whether the node is in the list. (only comparing coordinates)
    for(auto p:list)
        if(p->x==node->x&&p->y==node->y)
            return p;
    return NULL;
}

bool Astar::isCanReach(const Node *node,const Node *target,bool isIgnoreCorner) const
{
	// if the node is the same as the current node,
	// or exceeds the map,
	// or is an obstacle,
	// or is in closeList,
	// return false.
    if(target->x<0||target->x>maze.size()-1
        ||target->y<0&&target->y>maze[0].size()-1
        ||maze[target->x][target->y]==1
        ||target->x==node->x&&target->y==node->y
        ||isInList(closeList,target))
        return false;
    else
    {
        if(abs(node->x-target->x) + abs(node->y-target->y)==1)
            return true;
        else
        {
            // if it's diagonal, consider the blocking situations
            if(maze[node->x][target->y]==0&&maze[target->x][node->y]==0)
                return true;
            else
                return isIgnoreCorner;
        }
    }
}

vector<Node *> Astar::getSurroundNodes(const Node *node,bool isIgnoreCorner) const
{
    vector<Node *> surroundNodes;

    for(int x=node->x-1;x<=node->x+1;x++)
        for(int y=node->y-1;y<=node->y+1;y++)
            if(isCanReach(node,new Node(x,y),isIgnoreCorner))
                surroundNodes.push_back(new Node(x,y));

    return surroundNodes;
}
