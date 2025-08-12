# PathFinder Maze

Grid‑based pathfinding that computes the **shortest path** through a maze. Early milestones operate on a fixed **20×20** grid; Milestone 4 supports an **expandable grid** of arbitrary size.

##  Highlights
- `Node`, `NodeList` and `PathPlanner` abstractions for search
- Deterministic output with sample tests in `/Tests_sample`
- Milestones 1–3: fixed grid
- Milestone 4: dynamic grid sizing

##  Structure
PathFinder_Maze/
├── main.cpp
├── Node.{h,cpp}
├── NodeList.{h,cpp}
├── PathPlanner.{h,cpp}
├── Types.h
├── Tests_sample/
└── README.md

## Build & Run
### Build
##### bash:
  g++ -std=c++17 -O2 -o pathfinder main.cpp Node.cpp NodeList.cpp PathPlanner.cpp
  
 ### Run
  `./pathfinder`  if the program reads from bundled inputs,
  
  OR 
  
  `./pathfinder < path/to/maze.txt > output.txt` if your implementation expects a file
 
