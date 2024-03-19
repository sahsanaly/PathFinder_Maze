
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */
   

   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

   // Method for Milestone 2
   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
   NodeList* getReachableNodes();


   // Method for Milestone 3
   // Get the path from the starting position to the given goal co-ordinate
   //    The path should be a DEEP COPY
   NodeList* getPath();


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   

private:
   int rows=0;
   int cols=0;
   NodePtr pNode = nullptr;            //node that needs to be explored
   NodePtr startNode = nullptr;        //start node, S
   NodePtr qNode = nullptr;            //next node
   NodeList* nodeList_O = nullptr;     //Open list
   NodeList* nodeList_C=nullptr;       //Closed List
   NodeList* shortestPath=nullptr;     //List for shortest path
   NodeList* returnList=nullptr;       //return list for shortest path
   Env environment = nullptr;          //char** environment

};

#endif // COSC_ASS_ONE_PATH_PLANNING
