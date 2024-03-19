#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
#include "milestone4.h"

/* 
In this main file, we are importing the environment and getting the rows, columns and storing the environment characters 
in a string first and then in 2D char array. The env is initialised as the list of char pointers with row lenght which 
points to char array of column length. We create a pathplanner object in which we initialize the START_SYMBOL and then 
finds the reachable positions in the grid, and returns a list of them. Furthermore, we choose the shortest route through
"getPath", and finally prints the path, where we replace the path with arrows in a particular directions. 
*/ 


// // Read a environment from standard input.
void readEnvStdin(Env env, int rows, int cols, std::string col_input);

// Helper test functions
// void testNode();
// void testNodeList(int row, int col);

void printReachablePositions(Env env, NodeList* reachablePositions);

// // Print out a Environment to standard output with path.
// // To be implemented for Milestone 3
void printPath(Env env, NodeList* solution, int rows, int cols);


int main(int argc, char** argv){

    // // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // // AS YOU GO ALONG.
    // // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;
    

    Env env;                           //double pointer character (char**)

    int row = 0;                       //number of rows of the envrionment
    int col =0;                        //number of columns of the environment
    std::string c;                     //takes the input of the row as a string
    std::string col_input;             //takes all the input of the environment in a string
    while (!std::cin.eof()){
        std::getline(std::cin, c);
        col = c.length();
        col_input.append(c);
        ++row;
    }

    env = make_env(row, col);          //intializes the environment as a 2D array

    // // Load Environment 
    readEnvStdin(env, row, col, col_input);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2

    PathPlanner* pathplanner = new PathPlanner(env, row, col);
    NodeList* reachablePositions = nullptr;


    //We are getting the coordinates of the starting position

    int startx =0;          //row of the start coordinate
    int starty = 0;         //column of the start coordinate
    for (int i=0; i<row; ++i){
       for (int j=0; j<col; ++j){
           if (env[i][j]==SYMBOL_START){
               startx = i;
               starty=j;
           }
       }
    }

    pathplanner->initialPosition(startx, starty);
    
    reachablePositions = pathplanner->getReachableNodes();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();

    //print the path
    printPath(env, solution, row, col);

    for (int i=0; i<row; ++i){
        delete env[i];
    }
    delete env;
    delete pathplanner;
    delete reachablePositions;
    delete solution;

}

void readEnvStdin(Env env, int rows, int cols, std::string col_input){
    /*
    This function stores environment in a 2D array from the string.
    */
    for (int i=0; i != rows; ++i ) {
            for (int j=0; j != cols; ++j ) {
                env[i][j] = col_input[j+(i*cols)];
        }
    }  
}

void printPath(Env env, NodeList* solution, int row, int col) {
    /*
    This function is printing the shortest path with the arrows.
    Checks the position of the next coordinate, then appoints a symbol accordingly.
    */

    for (int i=1; i<solution->getLength()-1; ++i){
        if (solution->get(i+1)->getRow()>solution->get(i)->getRow()){
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = 'v';
        }
        if (solution->get(i+1)->getCol()>solution->get(i)->getCol()){
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = '>';
        }
        if (solution->get(i+1)->getRow()<solution->get(i)->getRow()){
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = '^';
        }
        if (solution->get(i+1)->getCol()<solution->get(i)->getCol()){
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = '<';
        }
    }
    for (int i=0; i < row; ++i ) {
        for (int j=0; j < col; ++j ) {
            std::cout << env[i][j]; 
        }
        if (i!=row-1){
            std::cout << std::endl;
        }
    }
}

/*
This function is to test for the reachable positions for Milestone2.
*/

void printReachablePositions(Env env, NodeList* reachablePositions){
    //TODO
    // for (int i=0; i < reachablePositions->getLength(); ++i){
    //     std::cout << "Node " << i+1 << ": " << reachablePositions->get(i)->getRow()
    //     << ", " << reachablePositions->get(i)->getCol() << ", " << reachablePositions->get(i)->getDistanceToS()
    //     << std::endl;
    // }
}

/*
Below commented code is for testing nodes and nodelists.
*/

// void testNode() {
//     std::cout << "TESTING Node" << std::endl;

//     // Make a Node and print out the contents
//     Node* node = new Node(1, 1, 2);
//     std::cout << node->getRow() << ",";
//     std::cout << node->getCol() << ",";
//     std::cout << node->getDistanceToS() << std::endl;
//     delete node;

//     // Change Node and print again
//     node = new Node(4, 2, 3);
//     std::cout << node->getRow() << ",";
//     std::cout << node->getCol() << ",";
//     std::cout << node->getDistanceToS() << std::endl;
//     delete node;
// }

// void testNodeList(int rows, int cols) {
//     std::cout << "TESTING NodeList" << std::endl;

//     // Make a simple NodeList, should be empty size
//     NodeList* nodeList = new NodeList(rows, cols);
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Add a Node to the NodeList, print size
//     Node* b1 = new Node(1, 1, 1);
//     nodeList->addBack(b1);
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Add second Nodetest
//     Node* b2 = new Node(0, 0, 1);
//     nodeList->addBack(b2);
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Test Get-ith - should be 0,0,1
//     Node* getB = nodeList->get(1);
//     std::cout << getB->getRow() << ",";
//     std::cout << getB->getCol() << ",";
//     std::cout << getB->getDistanceToS() << std::endl;

//     // Print out the NodeList
//     std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
// }
