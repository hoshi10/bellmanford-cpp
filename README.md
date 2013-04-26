bellmanford-cpp
================

Summary
-------
This is a C++ implementation of the Bellman-Ford algorithm. Simple interfaces are provided to make it easy to use in any project.

License
-------
This software is released under the MIT license. Refer to **LICENSE.md** for details.

Usage
-----
Add the following to your project:

`#include "bellmanford.h"`

and implement the interface `BellmanFordNode<T>`.

Instantiate `BellmanFordSearch` and:

1. Use `initGraph(<node list>)` to initialise the edge structures required for Bellman-Ford algorithm.

2. Use `search(<source node>)` to begin Bellman-Ford search from the source node.

3. Use `getDistanceMap()` to retrieve the map of distances from the source node to all other nodes in the graph.

Sample
------
Refer to **sample.cpp** for an example of how to use this class.

### Notes

Special thanks to [GeeksforGeeks][1], from which this code was adapted.


[1]: http://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/ "Dynamic Programming | Set 23 (Bellman–Ford Algorithm) - GeeksforGeeks | GeeksforGeeks"