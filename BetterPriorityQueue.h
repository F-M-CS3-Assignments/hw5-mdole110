//make sure file name is correct
#include <queue>
#include <vector>
#include <iostream>
#include "Graph.h"

using namespace std;

//made a BetterPriority Queue HEADER FILE 
struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;
	
	bool operator<(const BPQNode &other) const;
	

	bool operator>(const BPQNode &other) const; 
	
	bool operator==(const BPQNode &other) const; 
};

class BetterPriorityQueue: public std::priority_queue<BPQNode, vector<BPQNode>, 
greater<BPQNode>>::priority_queue{

    //code here
    public:
    bool Contains(BPQNode node);

        
    
    bool Update(BPQNode node);
        
    string ToString();
    static string BPQNodeToString(BPQNode& node);

    
};