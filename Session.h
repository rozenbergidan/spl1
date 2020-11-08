#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <queue>
#include <string>
#include "Graph.h"
#include "Agent.h"
#include "json.hpp"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected(); //return -1 if empty
    TreeType getTreeType() const;

    ///our code
    Tree* BFS(int node); //return the BFS tree from g, reducing coupling

    void isolateNode(int node); //isolate the node from its neighbors calls to graph function

    int getNeighborToInfect(int node);// return the node neighbor to getNeighborToInfect, return -1 is all neighbors are infected

    bool isNodeInfected(int node); //return true if node is infected, and false otherwise

    bool isAllActiveOrIsolated(); //return True if all active nodes are isolated

    int getCycleCount() const;

    void addInfected(int node);


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    void fromJSON(const std::string &path);

    int cycleCount;
    //TODO: changed infected to array
    std::vector<bool> infected;
    //bool[] *infected;
    std::queue<int> infectedQueue;


};

#endif