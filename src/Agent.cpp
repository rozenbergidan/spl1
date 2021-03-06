//
// Created by spl211 on 02/11/2020.
//

#include "../include/Agent.h"

using namespace std;

//---------------------------------------Agent---------------------------------------------------------------
Agent::Agent(){}

///========Rule of 3
Agent::~Agent(){};
//---------------------------------------ContactTracer---------------------------------------------------------------
ContactTracer::ContactTracer() : Agent() {};

///========Rule of 5


ContactTracer *ContactTracer::clone() const {
    ContactTracer *output = new ContactTracer();
    return output;
}

void ContactTracer::act(Session &session) {
    int node = session.dequeueInfected();
    if (node != -1) {
        Tree *tree = session.BFS(node);
        int nodeToDelete = tree->traceTree();
        session.isolateNode(nodeToDelete);
        delete tree;
    }
}

//---------------------------------------Virus---------------------------------------------------------------
Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd), isActive(false) {}

///========Rule of 5
//Virus::Virus(const Virus &other) :Agent(), nodeInd(other.nodeInd),isActive(other.isActive){
//
//}
//Virus::~Virus() {
//
//}
//const Virus & Virus::operator=(const Virus &other) {
//    nodeInd=other.nodeInd;
//    isActive=other.isActive;
//    return *this;
//}
Virus *Virus::clone() const {
    Virus *output = new Virus(nodeInd);
    if(isActive) output->isActive = true;
    return output;
}
void Virus::act(Session &session) {
    if (!isActive) {
        isActive = true;
        session.enqueueInfected(nodeInd);
        session.infectNode(nodeInd);
    }
    int nodeToInfect = session.getNeighborToInfect(nodeInd);
    if (nodeToInfect != -1) {
        Virus *newVirus = new Virus(nodeToInfect);
        session.addAgent(*newVirus);
        session.infectNode(nodeToInfect);
        delete newVirus;
    }
}

bool Virus::getActive() const {return isActive;}


