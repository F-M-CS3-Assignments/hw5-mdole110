#include "Dijkstra.h"
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <queue>
#include <vector>
#include <iostream>
//using namespace std 

//EXPLAIN BIG-O NOTATION HERE 
//DEPENDS ON HOW I IMPLEMENTED THE METHODS 
/*
using nodes and edges: 
- each node is processed once so that's O(N)
and there are specific measures in place to make sure they're only processed
once each (visited vector)
- Then, for the edges, you check the edges that go to all neighbors(connected nodes) each time you wanna figure out what node is enxt
therefore, edges are not exclusively visited once, unlike nodes. Instead, it is iterated thru as many times as its neighbors are called so it depends 
how many nodes it is connected to, whether they are traversed, etc. I think this proportional, versatile relationship would be best represented by log(Edges)
- So, I'm not 100p sure but I think the time complexity would be O(Nodes*log(Edges))
*/
int dijkstra(nodekey_t start, nodekey_t end, const Graph *g){
   
    //make sure start and end exist i the graph
    //add code here
    //figure out the difference between two nodes (priority-priority) = cost; keep running cost total; append to list; do all options return min of list 
    //find shortest neighbor always? and go to shortest and then add to cost?
    //;
    //int cost =0;
    //initialize a better prioriry queue (gonna push all nodes to it in path)
    BetterPriorityQueue shortestPathQueue;
    //make the inputted nodekey_t into BPQNode so that it works w the BPQ
    BPQNode startBPQNode;
    startBPQNode.gnode = start;
    startBPQNode.pri = 0;
    shortestPathQueue.push(startBPQNode);https://cplusplus.com/reference/queue/queue/push/
    //bool endREACHED = false; USING WHEN THE SHORTESTPATHQUEUE IS EMPTY INSTEAD 
    //init a vector with all of the costs and nodes
    vector<int> costs(g->Size()+1 , INT_MAX); // now the vector looks like this : [INT_MAX, INT_MAX, INT_MAX, ... for whole graph]
    costs[start] = 0; //can use this syntax now that we made a vector... now it looks like this: [0, INT_MAX, INT_MAX, INT_MAX....]
    //also will need to keep track of the nodes I've visited 
    vector<bool> visitedNode(g->Size()+1, false); //one for every node in graph... init all to false


    //now start node is the only thing in the priority queue 
    //start a loop that can be repreated 
    //while(endREACHED != true){ // if there's no path it gets stuck
    while(shortestPathQueue.empty()!=true){ 
        
       
        //find the neighboring nodes
        //figure out the one closest (shortest cost away) NO ACC..GREEDY
        //instead, find the next node by looking into the queue
        BPQNode curNode = shortestPathQueue.top(); //https://www.tutorialspoint.com/cpp_standard_library/cpp_priority_queue_top.htm#:~:text=The%20C%2B%2B%20std%3A%3Apriority_queue,without%20altering%20the%20queue%20state.
        //just start at first so it's gonna be start first
        //now since we are gonna use it, take it off the queue 
        shortestPathQueue.pop(); //https://www.codecademy.com/resources/docs/cpp/queues/pop#
        //now check to see if the newly popped node is the end 
        nodekey_t currentNodeKey = curNode.gnode; //type change makes it usable in more contexts where it needs to be nodekey_t and not BPQNode object
        //check if you have alr visited the node and if you have skip
        
        
        if(visitedNode[currentNodeKey] == true){
            continue;
        }
        visitedNode[currentNodeKey] = true; //redudent but just making sure it's marked visited when its pulled off the queue
        if(currentNodeKey == end){
            return costs[end]; //this will stop the while loop from continuting to run 
        }
        //now get and visit neighbors
        set<const GraphEdge*> neighbors  = g->GetOutwardEdgesFrom(currentNodeKey); //type needs to match type of g
        //add something to handle if an edge doesnt have any neighvors...aka make sure there;s none then continue
        if(neighbors.empty()){
            continue;
        }
        for(const GraphEdge* edge: neighbors){
            nodekey_t neighborNode = edge->to; //from graph.cpp
            int cost = edge->weight;//from graph.cpp set up
            //compare costs of what it takes to get to the currenet node + edge to neighbor vs the already known lowest cost path to the neighbor ...aka have u found a lower cost pasth
            int CheapestCost = costs[currentNodeKey] + cost; //cost here is the edge to the neighbor 
            if(CheapestCost < costs[neighborNode] ){ //aka path to neighbor thru current not < alr known best path to neighbornode
                costs[neighborNode] = CheapestCost; //set the cost of the neighbor node to tyhe updated cost (cost of path thru the current node...lower cost)
                //now make a BPQNode of the neighbor to push onto the queue 
                BPQNode BPQNeighborNode;
                BPQNeighborNode.gnode = neighborNode;
                BPQNeighborNode.pri = CheapestCost;
                //now add to the queue 
                shortestPathQueue.push(BPQNeighborNode);
                // and say that it was visited 
                //visitedNodes[neighborNode] = currentNodeKey; using if != int_max instead
            }
    }
        
}
//make sure you visited end 
if(costs[end] == INT_MAX){
    cout << "No path exists from start to end node" << endl;
    return -1;
}else{
return costs[end]; //valid bc made sure that end is reachable 
}
}
