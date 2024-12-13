# Bot-detection
This project is a **graph-based system** to ditinguish between a human and bot movements in a 2D maze.
The idea is 
- **Humans follow the shortest path** as natural.
- **Bot avoid traps** ,because they know about them from the code(similar to honey pot mechanism),which make them take a different path.
By tracking path deviations ,the system can detect bots.
--- 

## **Features**
- **Human vs Bot detection**: Differentiates humans and bot based on the path they choose.
- **Dynamic traps**: Traps are hidden from humans but visible to bots.Traps can change to confuse bots.
- **2D maze with graph representation**: The maze is represented as graph, allowing for pathfinding and comparision.


## **How it works **
1. The maze here is stuctured as a graph, with which each node representing a position in maze.
2. Humans follow the natural shortest path.
3. Bots avoids the traps and take an alternative path.
4. If the system finds that the paths are not similar then the user would be identified as a bot.
 


## **How to run**
To run the program, Follow these steps:
```bash
g++ main.cpp -o Bot-detection
./Bot-detection