//Copyright (C) Sorin Draghici <dsorin95@gmail.com>, April 2016
#include<iostream>
using namespace std;

//print the shortest path from source to a vertex
void printPath(int *parent, int vertex)
{
	if (parent[vertex] == -1) //base case: print the source which will have no parent (-1)
	{
		cout << vertex << " ";

		return;
	}

	printPath(parent, parent[vertex]); //recursive case: print the path of the parent of the vertex

	cout << vertex << " ";
}

//print the solution
void printSolution(int *dist, int nVertices, int source, int target, int *parent)
{
	cout << "\n";

	if (target == -1) //print all the distances and paths
	{
		for (int i = 0; i < nVertices; i++)
		{
			if (dist[i] == INT_MAX)
				cout << target << " -> " << i << " not visited\n";
			else
			{
				cout << source << " -> " << i << " minimum distance: " << dist[i] << " path: ";

				printPath(parent, i);

				cout << "\n";
			}
		}
	}
	else //print the distance and path that the user is interested in
	{
		cout << source << " -> " << target << " minumum distance: " << dist[target] << " path: ";

		printPath(parent, target);
	}

	cout << "\n";
}

//calculates the minimum distances between the vertices in a graph
//graph contains the distances from a vertex to another (0 if two vertices are not attached)
void dijkstra(int **graph, int source, int target, int nVertices)
{
	int *distance = new int[nVertices];  //dist[i] is the smallest distance from source to vertex i
	bool *visited = new bool[nVertices]; //visited[i] is true if vertex i has been visited
	int *parent = new int[nVertices];    //Saves the path followed to reach the different vertices. parent[i] is the vertex through which vertex i has been reached

	for (int i = 0; i < nVertices; i++) //initializations
	{
		distance[i] = INT_MAX; //consider infinity as distance to all vertices
		visited[i] = false;    //no vertex has been visited yet
		parent[i] = -1;		   //no vertex has a parent yet
	}

 	distance[source] = 0; //distance from source vertex to himself is 0

	bool cont = true; //cont indicates if the algorithm should continue or not

	for (int i = 0; i < nVertices - 1 && cont; i++) //main loop to check all vertices and save the minimum distance to them
	{
		int current, min = INT_MAX;

		for (int vert = 0; vert < nVertices; vert++) //choose the new closest vertex to the actual current vertex
		{
			if (!visited[vert] && distance[vert] <= min) //find the closest not visited vertex
			{
				min = distance[vert];
				current = vert;
			}
		}

		visited[current] = true;    //mark the choosen vertex as visited
		cont = (current != target); //continue with the algorithm only if the target vertex has not yet been reached

		for (int next = 0; next < nVertices && cont; next++) //update distances from the current vertex to his adjacent vertices
		{
			//tricky part: update the distance to next vertex only if next vertex hasn't been visited before and there is a path to it
			//from current vertex and if the distance to the next vertex passing through the current vertex is less than the previous distance
			if (!visited[next] && graph[current][next] && (distance[current] + graph[current][next] < distance[next]))
			{
				parent[next] = current;
				distance[next] = distance[current] + graph[current][next];
			}
		}
	}

	printSolution(distance, nVertices, source, target, parent);

	delete[] distance, visited, parent;
}

int main()
{
	//ask the user all the needed info
	int nVertices;

	cout << "Amount of vertices: ";
	cin >> nVertices;

	int **graph = new int*[nVertices];

	for (int i = 0; i < nVertices; i++)
		graph[i] = new int[nVertices];

	for (int i = 0; i < nVertices; i++)
	{
		cout << "Input distance from vertex " << i << " to the rest of the vertices (separate distances with a space):\n";

		for (int j = 0; j < nVertices; j++)
			cin >> graph[i][j];
	}

	cout << "Source vertex: ";

	int source;

	cin >> source;

	cout << "Target (use -1 to show all the paths): ";

	int target;

	cin >> target;

	dijkstra(graph, source, target, nVertices); //calculate minimum distances

	for (int i = 0; i < nVertices; i++)
		delete[] graph[i];

	delete[] graph;

	system("pause");

	return 0;
}
