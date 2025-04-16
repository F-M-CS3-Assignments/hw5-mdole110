all: 
	g++ -Wall -std=c++11 Graph.cpp GraphTests.cpp -o graph-tests
	g++ -Wall -std=c++11 Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpq-tests
	g++ -Wall -std=c++11 BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp Graph.cpp -o dijkstra

run: 
	./graph-tests
	./bpq-tests
	./dijkstra
try: all run