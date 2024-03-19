
#include "NodeList.h"
#include <iostream>



NodeList::NodeList(){
    this->length = 0;

    this->nodes = new NodePtr[length]; //node pointer array of length 'length'
}


NodeList::~NodeList(){
   
}

NodeList::NodeList(NodeList& other){
    // TODO
    this->length = other.length;
    this->nodes = new NodePtr[length];
}


int NodeList::getLength(){
    return this->length;
   
}


NodePtr NodeList::get(int i){
    return nodes[i];
   
}

void NodeList::addBack(NodePtr newNode){
    
    /*deletes the node pointer list, makes another one of length+1
    and adds the new node to it*/

    NodePtrPtr temp = new NodePtr[length];
    if (length >0){
        for (int i=0; i<length; ++i){
            temp[i] = nodes[i];
        }
    }
    delete nodes;
    nodes = new NodePtr[length+1];
    for (int i=0; i<length; ++i){
        nodes[i] = temp[i];
    }
    delete[] temp;
    nodes[length] = newNode;
    ++length;
    
}


bool NodeList::containsNode(NodePtr node){

    //checks if the node matches any node in the list
    bool boolean = false;
    for (int i =0; i<length; ++i) {
        if (node->getRow()==nodes[i]->getRow() && (node)->getCol()==nodes[i]->getCol()) {
            boolean = true;
        }
    }
    return boolean;
}

void NodeList::clear(){
    //deletes all the nodes and then deletes the list
    for (int i=0; i<getLength(); ++i ){
       delete nodes[i];
    }
    delete[] nodes;
}