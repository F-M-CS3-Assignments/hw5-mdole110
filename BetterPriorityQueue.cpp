#include "BetterPriorityQueue.h"
//make sure file name is correct
#include <queue>
#include <vector>
#include <iostream>
#include "Graph.h"


using namespace std;

//made a BetterPriority Queue HEADER FILE ... this is cpp file 
/* DECLARED IN HEADER: 
struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;
*/
	
	bool BPQNode::operator<(const BPQNode &other) const {
		return pri < other.pri;
	}

	bool BPQNode::operator>(const BPQNode &other) const {
		return pri > other.pri;
	}
	
	bool BPQNode::operator==(const BPQNode &other) const {
		return this->gnode == other.gnode;
	}


/*
Declared in header
class BetterPriorityQueue: public std::priority_queue<BPQNode, vector<BPQNode>, 
greater<BPQNode>>::priority_queue{


    //code here
    public:
*/
    bool BetterPriorityQueue::Contains(BPQNode node){
        //code
        /*Extending std::priority_queue provides you access to the protected member
        c which is the vector<BPQNode> containing the items of the queue. You can use this->c 
        to implement the above methods.*/
        bool Contains = false;
        for(size_t i =0; i< this->c.size(); i++){ //iterate thru all elements in the queue
            const BPQNode& item = this->c[i]; //const means dont change it; pass by reference; type is BPQNode; calling it item
            if(item == node){
                Contains = true;//returns true if the given 'node' is in the queue
            }
        }
        return Contains;

        
    }
    bool BetterPriorityQueue::Update(BPQNode node){
        //code
        //craete a vector of BPQNode called items 
        //moving items in this->c vector called c to be safe
        bool UpdatesMade = false;
        vector <BPQNode> items;
        for(size_t i=0; i<this->c.size(); ++i){
            BPQNode& curNode = this->c[i]; //const for dont chnage, BPQNode for object type
            if(curNode == node && node.pri < curNode.pri){
            
                curNode.pri = node.pri;
                
                //NEED TO DEL
                UpdatesMade = true;
            }
            items.push_back(curNode);
        }
    
    
        //c.clear();
        if(UpdatesMade == true){
            c.clear(); //need this->???
            for(int i=0; i<items.size(); i++){
                this->push(items.at(i)); //from hint 
            }
        
        //returns true if changes are made
    }
    return UpdatesMade;
    }

    string BetterPriorityQueue::ToString(){//needs to take in queue? No, just has this->c naturally
        // ex. format: [(1, pri:0), (2, pri:1), ...]
        //follow format on directions ^

        string StringFormnatted = "[";
        //for loop to iterate thru all of c (queue)
        for(size_t i =0; i< this->c.size(); ++i){//for each node in the queue
            StringFormnatted+= "(" + to_string(this->c[i].gnode) + ", pri: " + to_string(this->c[i].pri) + ")";
            //make sure it's not the last element 
            if(i<this->c.size()-1){ //if the number of i's iterated thru is less than the length of the queue
                StringFormnatted+=", "; //aka there's gonna be another one added
            }
        }
        StringFormnatted+="]";
        return StringFormnatted;

    }

    
    string BetterPriorityQueue::BPQNodeToString(BPQNode& node){
        //returns string representation of each item in the queue
        /*BPQNode is a struct; struct is a way to group related members under one name 
        kind of like a class
        */

        // ex. format: [(1, pri:0), (2, pri:1), ...]
        string StructAsString = "(" + to_string(node.gnode) + ", " + to_string(node.pri) + ")";
        return StructAsString;
        //follow format on directions ^

        

    };

    
