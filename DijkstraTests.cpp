
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>

using namespace std;


int DijkstraTest(){
	cout << "Testing Dijkstra Algorithm..." << endl;
	
	// Test 1: graph from assignment
	Graph *g = new Graph();
	
	g->AddNode(1);
	g->AddNode(2);
	g->AddNode(3);
	g->AddNode(4);
	g->AddNode(5);
	g->AddNode(6);
	
	g->AddEdge(1, 2, 7);
	g->AddEdge(2, 1, 7);
	g->AddEdge(1, 3, 9);
	g->AddEdge(3, 1, 9);
	g->AddEdge(1, 6, 14);
	g->AddEdge(6, 1, 14);
	
	g->AddEdge(2, 3, 10);
	g->AddEdge(3, 2, 10);
	g->AddEdge(2, 4, 15);
	g->AddEdge(4, 2, 15);
	
	g->AddEdge(3, 6, 2);
	g->AddEdge(6, 3, 2);
	g->AddEdge(3, 4, 11);
	g->AddEdge(4, 3, 11);
	
	g->AddEdge(6, 5, 9);
	g->AddEdge(5, 6, 9);
	
	g->AddEdge(4, 5, 6);
	g->AddEdge(5, 4, 6);
	
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g->NodesToString() << endl;
	cout << "\tedges: " << g->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start = 1;
	nodekey_t end = 5;

	cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
	
	int ans = dijkstra(start, end, g);
	cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
	assert(ans == 20);

	delete g;
	
	cout << "DONE Testing Dijkstra Algorithm" << endl;
	
	return ans;
}


void MoreDijkstraTests(){
	cout << "Deep Testing Dijkstra Algorithm..." << endl;

	// Your code goes here!
	//add a test for if the end can't be reached 
	cout << "Testing for no valid path between start and end..." << endl;
	Graph *g = new Graph();
	
	g->AddNode(1);
	g->AddNode(2);
	g->AddNode(3);
	g->AddNode(4);
	g->AddNode(5);
	g->AddNode(6);
	
	g->AddEdge(1, 2, 7);
	g->AddEdge(2, 1, 7);
	g->AddEdge(1, 3, 9);
	g->AddEdge(3, 1, 9);
	g->AddEdge(1, 6, 14);
	g->AddEdge(6, 1, 14);
	
	g->AddEdge(2, 3, 10);
	g->AddEdge(3, 2, 10);
	g->AddEdge(2, 4, 15);
	g->AddEdge(4, 2, 15);
	
	g->AddEdge(3, 6, 2);
	g->AddEdge(6, 3, 2);
	g->AddEdge(3, 4, 11);
	g->AddEdge(4, 3, 11);
	
	//no connection between 1 and 5
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g->NodesToString() << endl;
	cout << "\tedges: " << g->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start = 1;
	nodekey_t end = 5;

	cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
	
	int ans = dijkstra(start, end, g);
	cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
	assert(ans == -1);

	delete g;
	cout << "PASSED!!";

	

	//testing for when there's only one node on the graph 
	//will just return 0 because start == end so the cost of the graph from start to end is, technically, 0
	
	cout << "Testing Case with only one node..." << endl;
	
	Graph *g2 = new Graph();
	
	g2->AddNode(1);
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g2->NodesToString() << endl;
	cout << "\tedges: " << g2->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start2 = 1;
	nodekey_t end2 = 1;

	cout << "start: " << to_string(start2) << "  goal: " << to_string(end2) << endl;
	
	int ans2 = dijkstra(start, end, g2);
	cout << "Output from Dijkstra(" << to_string(start2) << ", " << to_string(end2) << ") => " << ans2 << endl;
	assert(ans2 == 0);
	cout << "PASSED!!!" << endl;

	//test a cycle to make sure not revisited 
	
	cout << "Testing a cycle to make sure nodes are not revisited..." << endl;
	Graph *g3 = new Graph();
	
	g3->AddNode(1);
	g3->AddNode(2);
	g3->AddNode(3);
	g3->AddNode(4);

	g3->AddEdge(1, 2, 1);
	g3->AddEdge(2, 3, 1);
	g3->AddEdge(3, 4, 1);
	g3->AddEdge(4, 1, 1);

	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g3->NodesToString() << endl;
	cout << "\tedges: " << g3->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start3 = 1;
	nodekey_t end3 = 3;

	cout << "start: " << to_string(start3) << "  goal: " << to_string(end3) << endl;
	
	int ans3 = dijkstra(start3, end3, g3);
	cout << "Output from Dijkstra(" << to_string(start3) << ", " << to_string(end3) << ") => " << ans3 << endl;
	assert(ans3 == 2);
	cout << "PASSED!!!" << endl;

	

	



	cout << "DONE Deep Testing Dijkstra Algorithm" << endl;
}


int main(){
	
	DijkstraTest(); // this one by itself tests the graph on the assignment
	cout << endl;
	MoreDijkstraTests();
	cout << endl;
	cout << "ALL TESTS PASSED!" << endl;

	return 0;
}
