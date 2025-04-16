
#include "Graph.h"
#include <iostream>
#include <vector>


using namespace std;


//vector "nodes" will collect a set of vertices
//vector "adjList" will collect edges (vector of vectors whose elements are GraphEdge pointers to GraphEdge struct objects)

/*
REMINDERS:
- FILL IN GRAPH::~GRAPH METHODS

*/

// This method is not part of the Graph class / header on purpose
const GraphEdge* findExistingEdge(nodekey_t gnFrom, nodekey_t gnTo, vector<vector<GraphEdge *> > adjList)
{
	if(adjList.size() == 0)
	{
		return nullptr;
	}


	for(size_t rowIDX = 0; rowIDX < adjList.size(); rowIDX++)
	{
		vector<GraphEdge*> row = adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++)
		{
			GraphEdge *cur = row.at(i);

			// It might make sense for there to be an == operator overload in the GraphEdge struct
			// but adding methods to a struct feels so _wrong_ to me!
			if(cur->from == gnFrom && cur->to == gnTo)
			{
				return cur;
			}
		}
	} 

	return nullptr;
}

// This method is not part of the Graph class / header on purpose
// This should probably be a method in the GraphEdge struct
// but adding methods to a struct feels so _wrong_ to me!
string GraphEdgeToString(const GraphEdge* e)
{
	return "((" + to_string(e->from) + ")->(" + to_string(e->to) + ") w:" + to_string(e->weight) + ")";
}





void Graph::AddNode(nodekey_t key)
{

	if(this->IsPresent(key))
	{
		throw invalid_argument("Duplicate node cannot be added: " + to_string(key));
	}


	nodes.push_back(key);
	vector <GraphEdge*> *newRow = new vector<GraphEdge*>; //now each is j a GraphEdge* pointer since we are just adding vertices, not edges yet
	adjList.push_back(*newRow);
	delete newRow; //?
}




const GraphEdge *Graph::AddEdge(nodekey_t gnFrom, nodekey_t gnTo,  unsigned int w)

{
	//check for negatives
	if(static_cast<int>(w) <0){
		throw invalid_argument("Edge weights must be positive numbers.");
		
	}
	// The AddEdge method creates new edges.  It does not and should not update / change
	// the weights of existing edges.  findExistingEdge does not check the weight for this reason
	const GraphEdge* dup = findExistingEdge(gnFrom, gnTo, this->adjList);
	if(dup != nullptr)
	{
		throw invalid_argument("Duplicate edge cannot be added: " + GraphEdgeToString(dup));
	}

	if(!this->IsPresent(gnFrom))
	{
		throw invalid_argument("No such node: " + to_string(gnFrom));
	}

	if(!this->IsPresent(gnTo))
	{
		throw invalid_argument("No such node: " + to_string(gnTo));
	}


	GraphEdge *ge = new GraphEdge;
	//set up from, to, and weight here?
	ge->from = gnFrom;
	ge->to = gnTo;
	ge->weight = w;

	for(size_t i=0; i < nodes.size(); i++){
		if(nodes.at(i) == gnFrom){
			adjList.at(i).push_back(ge);
		}
	}

	// TODO: ^^done aboce 
	// Do stuff here?  IDK what though
	//go thru all adjacent lists to check which one is corresponding to the from
	//vertex of the edge. Then, add the pointer to the edge to the end of the related vector
	//aka for i=0 to nodes.size()
	//if nodes.at(i) = same as from vertex 
	//add pointer ge to the end of the vector adjList.at(i)

	const GraphEdge *response = ge; // this helps the compiler go
	return response;
}


bool Graph::IsPresent(nodekey_t key) const
{
	// TODO:
	// iterate through this->nodes and look for one that matches key
	bool IsPresent = false;
	for(size_t i =0; i<this->nodes.size(); i++){
		if(this-> nodes.at(i) == key){
			IsPresent = true;
		}
	}
	return IsPresent;
	
}




set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t node) const 
{
	size_t idx = 0;
	while(idx < this->nodes.size() && (this->nodes.at(idx) != node))
	{
		idx++;
	}
	if(idx == this->nodes.size()){
		throw invalid_argument("No such node: " + to_string(node));
	}


	// need to redeclare gnFrom?
	set<const GraphEdge*> result = set<const GraphEdge*>();
	// TODO:
	// iterate over this->adjList.at(idx); and find nodes that match the given node
	for(size_t i =0; i < this->adjList.at(idx).size(); i ++){
		//set up the edge?
		const GraphEdge* edge = this->adjList.at(idx).at(i); //need to set up?
		if(edge->from == node){ //should abbrevate to ge->from and use same idea as Add::... or no b/c not given parameters 
			result.insert(edge);
		}
		
	}
	// in their "from" field, put those nodes in result


	return result;
}

 set<nodekey_t> Graph::GetNodes() const 
{
	// TODOL
	// iterate of this->nodes, accumulate into a set<nodekey_t> and return it
	set<nodekey_t> GetNodesReturned;
	for(size_t i =0; i <this->nodes.size(); i++){
		//allowed to use .insert() on a set<...> ? https://cplusplus.com/reference/set/set/insert/
		GetNodesReturned.insert(this->nodes.at(i));
	}
	return GetNodesReturned;
	
}


size_t Graph::Order() const 
{
	return nodes.size();
}

size_t Graph::Size() const 
{
	size_t total = 0;
	for(size_t i = 0; i < adjList.size(); i++){
		vector<GraphEdge*> row = adjList.at(i);
		for(size_t j = 0; j < row.size(); j++){
			total++;
		}
	}

	return total;
}



string Graph::NodesToString() const 
{
	if(nodes.size() == 0)
	{
		return "[]";
	}

	string str = "[";
	for(size_t i = 0; i < (nodes.size() - 1); i++)
	{
		str = str + "(" + to_string(nodes.at(i)) + "), ";
	}

	str = str + "(" + to_string(nodes.at(nodes.size()-1)) + ")]";
	return str;
}

string Graph::EdgesToString() const 
{
	if(this->adjList.size() == 0)
	{
		return "[]";
	}

	size_t count = 0;
	string str = "[";
	for(size_t rowIDX = 0; rowIDX < this->adjList.size(); rowIDX++)
	{
		vector<GraphEdge*> row = this->adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++)
		{
			GraphEdge *cur = row.at(i);
			str = str + GraphEdgeToString(cur);

			if(count < (this->Size() - 1)){
				 str = str + ", ";
			}
			count++;
		}
	} 

	str = str +  "]";
	return str;

}



Graph::~Graph() {
	// TODO:
	// Right now the memory leaks are bad, I need to
	// implement something here to fix it -- valgrind built into remote right?
	//Declared like this: vector<vector<GraphEdge *> > adjList
	for(vector<GraphEdge*>& item: adjList){
		for(GraphEdge* edge:item){
			delete edge; //one by one then
		}

	}
	//there's still vectors but theyre empty so...
	adjList.clear();
}

