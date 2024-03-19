
#include "PathPlanner.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols){

    this->rows = rows;
    this->cols=cols;

    //declare the environment as double pointer array of characters
    if (rows >= 0 && cols >= 0) {
        environment = new char*[rows];
        for (int i = 0; i != rows; ++i) {
            environment[i] = new char[cols];
        }
    }
    //initalizes the values to the environment
    for (int i=0; i != rows; ++i ) {
        for (int j=0; j != cols; ++j ) {
            environment[i][j] = env[i][j];
        }
    }

    //Open list and its deep copies
    nodeList_O = new NodeList();
    nodeList_C = new NodeList(*nodeList_O);
    shortestPath = new NodeList(*nodeList_O);
    returnList = new NodeList(*nodeList_O);



}

PathPlanner::~PathPlanner(){

    for (int i=0; i<rows; ++i){
        delete environment[i];
    }
    delete environment;
    qNode = nullptr;
    delete qNode;
    delete startNode;
    delete nodeList_C;
    shortestPath->clear();
    returnList->clear();
    nodeList_O->clear();

   
}

void PathPlanner::initialPosition(int row, int col){

    startNode = new Node(row, col, 0);
    
    nodeList_O->addBack(startNode);

    pNode = startNode;

    startNode = nullptr;
}

NodeList* PathPlanner::getReachableNodes(){
    
    for (int i=0; i<nodeList_O->getLength(); ++i){
        
        /*checks if the surronding node, in all directions, is either empty or goal, then adds to the 
        open list if it hasn't been added already*/

        if (pNode->getCol()%cols!=0){
            if (environment[pNode->getRow()][pNode->getCol()+LEFT] == SYMBOL_EMPTY || 
            environment[pNode->getRow()][pNode->getCol()+LEFT] == SYMBOL_GOAL){
                NodePtr qNode = new Node(pNode->getRow(), pNode->getCol()+LEFT, pNode->getDistanceToS()+1);
                if (nodeList_O->containsNode(qNode) == false){
                    nodeList_O->addBack(qNode);
                }
                else {
                    delete qNode;
                }
            }
        }
        
        if (pNode->getRow()<rows-1){
            if (environment[pNode->getRow()+DOWN][pNode->getCol()] == SYMBOL_EMPTY || 
            environment[pNode->getRow()+DOWN][pNode->getCol()] == SYMBOL_GOAL){
                NodePtr qNode = new Node(pNode->getRow()+DOWN, pNode->getCol(), pNode->getDistanceToS()+1);
                if (nodeList_O->containsNode(qNode) == false){
                    nodeList_O->addBack(qNode);
                }
                else {
                    delete qNode;
                }
            }
        }

        if (((pNode->getCol()+1)%cols)!=0){
            if (environment[pNode->getRow()][pNode->getCol()+RIGHT] == SYMBOL_EMPTY || 
            environment[pNode->getRow()][pNode->getCol()+RIGHT] == SYMBOL_GOAL){
                NodePtr qNode = new Node(pNode->getRow(), pNode->getCol()+RIGHT, pNode->getDistanceToS()+1);
                if (nodeList_O->containsNode(qNode) ==false){
                    nodeList_O->addBack(qNode);
                }
                else {
                    delete qNode;
                }
            }
        }

        if (pNode->getRow()>0){
            if (environment[pNode->getRow()+UP][pNode->getCol()] == SYMBOL_EMPTY || 
            environment[pNode->getRow()+UP][pNode->getCol()] == SYMBOL_GOAL){
                NodePtr qNode = new Node(pNode->getRow()+UP, pNode->getCol(), pNode->getDistanceToS()+1);
                if (nodeList_O->containsNode(qNode)==false){
                    nodeList_O->addBack(qNode);
                }
                else {
                    delete qNode;   //deletes the q-node if doesnt add in the openlist
                }
            }
        }
        
        
        //adds the pnode to the closed once it's been explored
        nodeList_C->addBack(pNode);

        //the next node in the openlist becomes the pnode if it's not in the closed list already
        for (int i=nodeList_O->getLength()-1; i>=0; --i){
            if (nodeList_C->containsNode(nodeList_O->get(i))==false) {
                pNode =  nodeList_O->get(i);
            }
        }
    }

    //returns the reachable nodes
    return nodeList_O;  
   
}

NodeList* PathPlanner::getPath(){

    int goalx =0;       //row of the goal
    int goaly =0;       //column of the goal
    NodePtr tempNode;   //temporary node pointer 

    for (int i=0; i<rows; ++i){
       for (int j=0; j<cols; ++j){
           if (environment[i][j]==SYMBOL_GOAL){
               goalx = i;
               goaly=j;
           }
       }
    }

    //adds the goal node to the shortest path list
    for (int i=0; i<nodeList_O->getLength();++i){
        if (nodeList_O->get(i)->getRow() == goalx && nodeList_O->get(i)->getCol() == goaly){
            qNode = new Node(nodeList_O->get(i)->getRow(), nodeList_O->get(i)->getCol(), nodeList_O->get(i)->getDistanceToS());
            shortestPath->addBack(qNode);
        }
    }

    /*
    checks if the distance of a node in the openlist is less than the goal node (or a previous node) and its coordinate position
    is adjacent to that node, then it adds to the shortest path list.
    */
    for (int i=nodeList_O->getLength()-1; i>=0 && qNode->getDistanceToS()>0 ;--i) {
        for (int j=nodeList_O->getLength()-1; j>=0 && qNode->getDistanceToS()>=1 ;--j) {
            if (qNode->getDistanceToS() - nodeList_O->get(j)->getDistanceToS() == 1) {
            if ((qNode->getRow() - nodeList_O->get(j)->getRow() == 1  && qNode->getCol() - nodeList_O->get(j)->getCol() == 0)
                || (qNode->getRow() - nodeList_O->get(j)->getRow() == 0 && qNode->getCol() - nodeList_O->get(j)->getCol() == 1)
                || (qNode->getRow() - nodeList_O->get(j)->getRow() == -1 && qNode->getCol() - nodeList_O->get(j)->getCol() == 0)
                || (qNode->getRow() - nodeList_O->get(j)->getRow() == 0 && qNode->getCol()-nodeList_O->get(j)->getCol() == -1)){
                    tempNode = new Node(nodeList_O->get(j)->getRow(), nodeList_O->get(j)->getCol(), nodeList_O->get(j)->getDistanceToS());
                    shortestPath->addBack(tempNode);
                    qNode = tempNode;
                    tempNode = nullptr;
                    delete tempNode;
                }
            }
        }
    }

    //reverse the shortest path list to start from S and ends at G
    for (int i=shortestPath->getLength()-1; i>=0; --i){
        tempNode = new Node(shortestPath->get(i)->getRow(), shortestPath->get(i)->getCol(), shortestPath->get(i)->getDistanceToS());
        returnList->addBack(tempNode);
        tempNode = nullptr;
        delete tempNode;
    }

    return returnList;
    
}
