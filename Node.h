
#ifndef COSC_ASS_ONE_NODE
#define COSC_ASS_ONE_NODE

#include "Types.h"

class Node {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // get row-co-ordinate
   int getRow();

   // get Column-co-ordinate
   int getCol();

   // getters and setters for distance to source
   int getDistanceToS();
   void setDistanceToS(int distanceToS);


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   
   // Constructor/Destructor
   Node(int row, int col, int distanceToS);
//    Node(Node& other);
   ~Node();
    
    
private:
    int row;
    int col;
    int distanceToS;
    

};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef Node** NodePtrPtr;       //pointer to the pointer to a node
typedef Node* NodePtr;           //pointer to a node

#endif // COSC_ASS_ONE_NODE
