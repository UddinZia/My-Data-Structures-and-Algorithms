
/***************************
** File: graph.h
** Author: Evan Cyr, Zia Uddin
** Date: 5/08/2022
** Section: 511
** Email: zia19@tamu.edu, ecry20@tamu.edu
**
** This file contains the class definition for a graph using an adjaceny matrix implementation. 
** contains defintions for Prim's and Dijkstra's algorithms. Dijkstra's algorithm was approached  
** recursively while Prim's algorithm was approaced using a nested for loop.
*
***************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using std::endl; using std::cout; using std::vector;


class Graph {
private:
    // TODO(student): implement graph

    //Variables for Dijkstra's algorithm
    //Struct for holding the data for dTable
    struct dNode
    {
        //integer for holding the node's vertex ID
        size_t vertex = SIZE_MAX;
        //integer for holding the previous node's index value in dTable
        size_t previous = SIZE_MAX;
        //double for the distance of the vertex from dMain vertex
        double distance = INFINITY;
        //boolean for if the node has been visited
        bool visited = false;
    };
    //Vector of dNodes for the vertexs, integer to hold the size of dTable, and the main vertex for Dijkstra
    std::vector<dNode> dTable;
    size_t dSize = 0;
    size_t dMain;

    //Vector of vectors to hold the graph implementation
    std::vector<std::vector<double>> arr;
    //Integers to hold the amount of vertexs, edges, size, and capacity of arr
    size_t vertexs;
    size_t edges;
    size_t size;
    size_t capacity;
    
    //Name: dijkstraRec()
    //Precondition: dijkstra() has been called
    //Postcondition: dTable will have the dNode distances updated for every vector in the graph
    void dijkstraRec(size_t source_id){

        //Check to see if it is a valid source_id or if the current id has already been visited
        if(source_id > capacity || dTable[source_id].visited){
            
            //Loop thorugh dTable to check to see if any of the nodes haven't been visited
            for(size_t i = 0; i < dSize; i++){
                
                //If a node hasn't been visited, recall the function on that node
                if(dTable[i].visited == false){
                    dijkstraRec(i);
                }
            }
            return;
        }

        
        //Create variables to hold the smallest weight and ID of that weight
        double minWeight = INFINITY;
        double minID = INFINITY;

        //Loop through dTable
        for(size_t i = 0; i < dSize; i++){

            //Check to see if there is an edge between the current index of dTable and the source_id index
            if(contains_edge(dTable[source_id].vertex,dTable[i].vertex)){
                
                //Check to see if there already is a distance at the current dNode
                if(dTable[i].distance == INFINITY){
                    
                    //If there isn't, set the previous vertex to source and update the distance with the cost of source to i + distance already at source
                    dTable[i].distance = dTable[source_id].distance + cost(dTable[source_id].vertex,dTable[i].vertex);
                    dTable[i].previous = source_id;

                    //If the distance is smaller than minWeight, set minWeight to the distance and id to i
                    if(dTable[i].distance < minWeight){
                        minWeight = dTable[i].distance;
                        minID = i;
                    }
                }
                else{
                    
                    //If there is, check to see if the cost of source to i + distance is less than the current distance
                    double costs = dTable[source_id].distance + cost(dTable[source_id].vertex,dTable[i].vertex);
                    if(dTable[source_id].distance + cost(dTable[source_id].vertex,dTable[i].vertex) < dTable[i].distance){

                        //If it is, set the current distance to that, previous ertx to source
                        dTable[i].distance = costs;
                        dTable[i].previous = source_id;

                        //If the distance is smaller than minWeight, set minWeight to the distance and id to i
                        if(dTable[i].distance < minWeight){
                            minWeight = dTable[i].distance;
                            minID = i;
                        }
                    }
                }
            }
        }
        
        //Set the current vertex visited to true and call the function on minID
        dTable[source_id].visited = true;
        dijkstraRec(minID);
    }

    //Name: 
    //Precondition: 
    //Postcondition: 
    
    //Name: printPath()
    //Precondition: print_shortest_path() has been called
    //Postcondition: The shortest path calculated from dijkstra's algorithm will be printed out
    void printPath(size_t index, std::ostream& os=std::cout) const{

        //Check to see if index is valid or if the current index is main index of the algorithm, if so return
        if(index > dTable.size() || dTable[index].vertex == dMain){
            return;
        }

        //Call printPath on the previous vertex of the current one
        printPath(dTable[index].previous, os);

        //Print out an arrow followed by the current vertex
        os << " --> " << dTable[index].vertex;
    };

    vector<double> mst; // creates minimum spanning tree
    vector<vector<double>> undirected; // creates undirected graph representation

    /*
    * creates undirected version of directed graph, used for prim's algorithim
    */
    vector<vector<double>> create_undirectected()
    {
        // create new copy of adjacency matrix 
        vector<vector<double>> undirected_graph(arr);
        
        // make directed graph undirected: edge has weight going both ways
        for (size_t i = 1; i < size; i++)
        {
            for (size_t j = 1; j < size; j++)
            {
                if (undirected_graph[i][j] != INFINITY)
                {
                    undirected_graph[j][i] = undirected_graph[i][j];
                }
            }
        }
       return undirected_graph;
    }

public:
    // Task 1

    //Constructor
    Graph(){    
        arr.push_back(std::vector<double>{}); // initialize arr to be vector of vector 
        arr[0].push_back(INFINITY); // initialize all values to inf, meaning no edges currently exist
        size = 1;
        capacity = 1;
        vertexs = 0;
        edges = 0;
    }
    
    //Copy Constructor
    Graph(const Graph& other)
    {
        arr = other.arr;
        vertexs = other.vertexs;
        edges = other.edges;
        size = other.size;
        capacity = other.capacity;
        undirected = other.undirected;
        
    }
    
    //Assignment copy
    Graph& operator=(const Graph& other)
    {
        arr = other.arr;
        vertexs = other.vertexs;
        edges = other.edges;
        size = other.size;
        capacity = other.capacity;
        undirected = other.undirected;

        return *this;
    }

    //Deconstructor
    ~Graph(){
        size = 0;
        capacity = 0;
        vertexs = 0;
        edges = 0;
    }
    
    //Name: vertex_count()
    //Precondition: none
    //Postcondition: Will return vertexs variable
    size_t vertex_count() const{return vertexs;}

    //Name: edge_count()
    //Precondition: none
    //Postcondition: Will return edges variable
    size_t edge_count() const{return edges;}

    /*
    * finds the vertex in the graph, returns true if successful or false if unsucessful
    */
    bool contains_vertex(size_t id) const
    {
        //Loop though arr
        for (size_t i = 0; i < size; i++)
        {   
            //If the current index's value is equal to id, return true
            if (arr[i][0] == id)
                return true;
        }
        //If not found return false
        return false;
    }
    /*
    *  returns true if edge exist b/w two verticies and false otherwise
    */
    bool contains_edge(size_t src, size_t dest) const
    {
        //Loop through the first vector in arr
        for (size_t i = 0; i < size; i++)
        {
            //Check to see if arr[0][i] is equal to the src vertex
            if (src == arr[0][i]) 
            {
               //Loop through the first element of every vector in arr
               for (size_t j = 0; j < size; j++)
               {
                   //Check to see if arr[j][0] is equal to the dest vertex
                   if (dest == arr[j][0]) 
                   {
                       if (arr[j][i] != INFINITY) // returns true if edge is not infinity meaning it exists
                       {
                           return true;
                       }
                       return false;
                   }
               }
           }
        }
        return false;
    }
    /*
    * returns the weight of an edge between two verticies
    */
    double cost(size_t src, size_t dest) const{
        
        //Loop through the first vector in arr
        for (size_t i = 0; i < size; i++)
        {
            //Check to see if arr[0][i] is equal to the src vertex
            if (src == arr[0][i])
            {
                //Loop through the first element of every vector in arr
                for (size_t j = 0; j < size; j++)
                {
                    //Check to see if arr[j][0] is equal to the dest vertex
                    if (dest == arr[j][0])
                    {
                       if (arr[j][i] != INFINITY) // returns [j][i] which is the weight/cost in the graph if not INF
                       {
                           return arr[j][i];
                       }
                       else
                       {
                           return INFINITY;
                       }
                   }
               }
           }
        }
        return INFINITY;
    }

    /*
    * adds vertex to graph, returns true on success and false otherwise
    */
    bool add_vertex(size_t id)
    {
        if(contains_vertex(id)){ // if id already exists return false
            return false;
        }

        arr.push_back(std::vector<double>{});
        size++; 
        capacity = size;
        for(size_t i = 0; i < size; i++){ // create new row for vertex
            arr[i].resize(size,INFINITY);
        }
        arr[0][size-1] = id; // add vertex to  graph
        arr[size-1][0] = id;
        arr[size-1][size-1] = INFINITY;
        vertexs++; 
        return true;
    }
    /*
    * adds a weight for 2 verticies if it equals infinity creating an edge. otherwise if an edge exists, returns false 
    */
    bool add_edge(size_t src, size_t dest, double weight=1)
    {
          for (size_t i = 0; i < size; i++)
          {
           if (src == arr[0][i])
           {
               for (size_t j = 0; j < size; j++)
               {
                   if (dest == arr[j][0])
                   {
                       if (arr[j][i] != INFINITY)
                       {
                           return false;
                       }
                       else
                       {
                            arr[j][i] = weight;
                            edges++;
                            return true;
                       }
                   }
               }
           }
        }
        return false;   
    }
    
    /*
    * removes vertex, returns true on success and false otherwise.
    */
    bool remove_vertex(size_t id)
    {
        if(!contains_vertex(id)){ // if vertex does not exists
            return false;
        }

        // remove vertex by assigning vertex to become INF 
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i][0] == id)
            {
                arr[i][0] = INFINITY;
                arr[0][i] = INFINITY;
                for (size_t j = 0; j < size; j++){
                    arr[i][j] = INFINITY;
                    arr[j][i] = INFINITY;
                }
                vertexs--;
                return true;
            }
        }
        return false;
    }

    /*
    *  removes edge if it exists and returns true, returns false otherwise
    *  replaces existing edge with INF
    */
    bool remove_edge(size_t src, size_t dest)
    {
        for (size_t i = 0; i < size; i++)
        {
            if (src == arr[0][i])
            {
                for (size_t j = 0; j < size; j++)
                {
                    if (dest == arr[j][0])
                    {
                      if (arr[i][j] == INFINITY) 
                       {
                           return false;
                       }
                       else
                       {
                            arr[i][j] = INFINITY;
                            edges--;
                            return true;
                       }
                    }
                }
            }
        }
        return false;
    }

    // Task 2
   
    /*
    * prim algorithim function constructs a mst of the graph. graph is converted to undirected graph 
    * in order for algorithim to function
    */
    void prim(size_t source_id)
    {
        if(source_id >= capacity){
            return;
        }
        undirected = create_undirectected(); // create new undirected graph 
        size_t index = indexOf(source_id); // returns index of the vertex in the graph

       
        vector<bool> visited(capacity,false); // vector keeps track of visited verticies 
        visited[index] = true;

        mst.resize(capacity,INFINITY); // the minimum spanning tree
        mst[0] = source_id;
        size_t l = 1; // index variable for adding to mst
        size_t min; 
        size_t minIndex; // keeps track of index of vertex with min edge
        size_t c; // column variable

        for (size_t r = index; r < size; r++)
        {
                min = SIZE_MAX;
                visited[r] = true; 
                if (l < size)
                {
                    for (c = 1; c < size; c++) 
                    {
                        
                        if (min > undirected[r][c] && undirected[r][c] != INFINITY && !visited[c]) // if edge exists and is less than current min value and has not been visited
                        {
                            min = undirected[r][c];  // update min value while looping through row 
                            mst[l] = undirected[0][c]; // add vertex to mst 
                            minIndex = c;
                        }
                    }
                    l++;
                    r = minIndex-1; // set r to go to next row where minimum edge was found
                }
                else
                {
                    break;
                }
        }
    }

    /*
    * returns true if id is in path made by prim algorithim
    */
    bool is_path(size_t id) const
    {

       if(mst.size() == 0){
           return false;
       } 
       for (size_t i = 0; i < size; i++) 
       {
           if(mst[i] == id)
           {
               return true;
           }
       }
        return false;
    }

    void print_path(size_t dest_id, std::ostream& os=std::cout) const
    {
        if (!is_path(dest_id))
        {
            cout << "<no path>\n";
            return;
        }
        

        for (size_t i = 0; i < capacity-1; i++)
        {
            if (mst[i] != dest_id)
            {
                cout << mst[i] << " --> ";
            }   
            else
            {
                cout << dest_id << endl;
                break;
            }
        }
    }

    // Task 3

    //Name: djikstra()
    //Precondition: source_id is valid meaning it's smaller than the size of arr
    //Postcondition: the vector dTable will be filled with nodes containing the distance of the vertexs to the passed in vertex
    void dijkstra(size_t source_id){

        //Check to see whther or not source_id is valid, if not return
        if(source_id >= arr.max_size()){
            return;
        }

        //Update dMain variable with the source_id
        dMain = source_id;

        //Resize dTable to the amount of vertices and set the dSize to that value
        dTable.resize(vertexs, dNode{});
        dSize = vertexs;

        //Integer to hold the current index of the source_id vertex
        size_t tableID = SIZE_MAX;

        //Integer to hold the index of dTable during iteration through the loop
        size_t j = 0;

        //Loop through the first vector in arr
        for(size_t i = 1; i < capacity; i++){
            //Check to see if the value is infinity
            if(arr[0][i] != INFINITY){

                //If not, set the current index of dTable's vertex to equal the index of the current arr value 
                dTable[j].vertex = arr[0][i];

                //If the current is the source id, set its distance to 0 and tabelID to current index of dTable
                if(arr[0][i] == source_id){
                    dTable[j].distance = 0;
                    tableID = j;
                }

                //increment j
                j++;
            }
        }

        //Call dijkstraRec on the tableID
        dijkstraRec(tableID);
    };

    //Name: distance()
    //Precondition: dijkstra() has been called
    //Postcondition: Will return the distance from the dMain vertex to the id vertex
    double distance(size_t id) const{

        //Loop through dTable and return the value of dNode distance for the passed in id
        for(size_t i = 0; i < dSize; i++){
            if(dTable[i].vertex == id){
                return dTable[i].distance;
            }
        }
        return INFINITY;
    };

    //Name: print_shortest_path()
    //Precondition: dijkstra() has been called
    //Postcondition: The shortest path from dMain vertex to dest_id vertex will be printed to the console
    void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const{

        //Check to see if dest_id is valid, if not return
        if(dest_id >= capacity){
            return;
        }
        
        //Check to see if path exists, if not print nopath
        double dist = distance(dest_id);
        if(dist == INFINITY){
            os << "<nopath>\n";
            return;
        }

        //Print out the main vertex
        os << dMain;

        //Loop through dMain, if the current id is dest_id call printPath on the current id
        for(size_t i = 0; i < dSize; i++){
            if(dTable[i].vertex == dest_id){
                
                printPath(i, os);
                break;
            }
        }
        //Print out the distance
        os << " distance: " << dist << std::endl;
        return; 
    };
    
    //Name: print_table()
    //Precondition: None
    //Postcondition: Prints out arr
    void print_table()
    {
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                std::cout << arr[i][j] << " ";
            }
            std::cout << endl;
        }
        std::cout << endl;
        
    }

    //Name: print_d()
    //Precondition: NOne
    //Postcondition: prints out dTable
    void print_d(){
        for(size_t i = 0; i < dSize; i++){
            std::cout << dTable[i].vertex << ": " << dTable[i].distance << " " << dTable[i].visited << " " << dTable[i].previous << std::endl;
        }
    }

    // returns index of a virtex in graph
    size_t indexOf(double virtex) const
    {
        for (size_t i = 0; i < size; i++)
        {
            if (arr[0][i] == virtex)
                return i;
        }
        return -1;
    }
};

#endif  // GRAPH_H
