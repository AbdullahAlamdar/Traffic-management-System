#include<iostream>
#include<fstream>
#include<istream>
#include<string>
using namespace std;

class ListNode{
    public:
    int dest;
    int weight;
    ListNode*next;

    ListNode(int dest, int weight){
        this->dest=dest;
        this->weight=weight;
        next=nullptr;
    }

};

struct vehicle{
    string id;
    int currentLocation;
    int destination;
    int shortestPath[100];
    int pathLength;
    int pathIndex;

};

class list{
    public:
    ListNode*head;

    list(){
        head=nullptr;
    }
    void addNode(int dest, int weight){
        ListNode*nn=new ListNode(dest,weight);
        if(head==nullptr){
            head=nn;
        }
        else{
            ListNode*temp=head;
            while(temp->next!=nullptr){
                temp=temp->next;
            }
            temp->next=nn;
        }
    }

};

class graph{
    public:
    int vertices;
    list*ListArray;
    vehicle cars[50];
    int vehicleCount;

    graph(int vertices){
        this->vertices=vertices;
        ListArray=new list[vertices];
        vehicleCount=0;
    }

    void addEdge(int src,int dest, int weight){
        ListArray[src].addNode(dest,weight);
    }
    void addNewIntersection(int new_intersection){
        if(new_intersection<0){
            cout<<"New vertex can not be less than zero"<<endl;
            return;
        }
        else{
            if(new_intersection>=vertices){
                cout<<"Resizing graph ! "<<endl;

                int newSize=new_intersection+1;
                list*updatedArray=new list[newSize];

                for(int i=0;i<vertices;i++){
                    updatedArray[i]=ListArray[i];
                } 

                delete[] ListArray;
                ListArray=updatedArray;
                vertices=newSize;

                cout<<"New vertex "<<new_intersection<<" Added dynamically ! "<<endl;
            }
        }
    }

    void removeIntersection(int vertex){
        if(vertex<vertices){
            ListArray[vertex].head=nullptr;
            cout<<"Vertex "<<vertex<<" deleted dynamically ! "<<endl;
        }
        else{
            cout<<"Invalid index enterd "<<endl;
        }
    }


    void printPath(int vertex, int parent[]) {
        if (parent[vertex] == -1) {
            cout << vertex;
            return;
        }
        printPath(parent[vertex], parent);
        cout << " -> " << vertex;
    }

    void DijkstraAlgo(int src,int dest){
        // arrays 
        int distance[vertices];
        int parent[vertices];
        bool visited[vertices];

        // initial values

        for(int i=0;i<vertices;i++){
            distance[i]=INT8_MAX; // infinite
            parent[i]=-1;    // no parent
            visited[i]=false; // not visited yet
        }

        // initializing the source to source dist
        distance[src]=0;

        // main algo loop
        for(int count=0;count<vertices-1;count++){
            // for finding the vertex with min distance that has not yet been visited 
            int minDistance=INT8_MAX;// infinite
            int u=-1;
            // 2nd loop 
            for(int i=0;i<vertices;i++){
                if(!visited[i] && distance[i]<minDistance){
                    minDistance=distance[i];
                    u=i;
                }
            }

            visited[u]=true;

            //for updating the distances of neighbouring vertices
            ListNode*neighbour=ListArray[u].head;
            while(neighbour!=nullptr){
                int v=neighbour->dest;
                int weight=neighbour->weight;

                // for updating the distance if a shorter path is find
                if (!visited[v] && distance[u] != INT8_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
            neighbour = neighbour->next;
            }
        }
            if (distance[dest] == INT8_MAX) {
                cout << "No path exists from " << src << " to " << dest << endl;
            } else {
                cout << "Shortest path distance: " << distance[dest] << endl;
                cout << "Path: ";
                printPath(dest, parent);
                cout << endl;
            } 
    }

    int calculatePathLength(int src, int dest){
        // arrays 
        int distance[vertices];
        int parent[vertices];
        bool visited[vertices];

        // initial values

        for(int i=0;i<vertices;i++){
            distance[i]=INT8_MAX; // infinite
            parent[i]=-1;    // no parent
            visited[i]=false; // not visited yet
        }

        // initializing the source to source dist
        distance[src]=0;

        // main algo loop
        for(int count=0;count<vertices-1;count++){
            // for finding the vertex with min distance that has not yet been visited 
            int minDistance=INT8_MAX;// infinite
            int u=-1;
            // 2nd loop 
            for(int i=0;i<vertices;i++){
                if(!visited[i] && distance[i]<minDistance){
                    minDistance=distance[i];
                    u=i;
                }
            }

            visited[u]=true;

            //for updating the distances of neighbouring vertices
            ListNode*neighbour=ListArray[u].head;
            while(neighbour!=nullptr){
                int v=neighbour->dest;
                int weight=neighbour->weight;

                // for updating the distance if a shorter path is find
                if (!visited[v] && distance[u] != INT8_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
            neighbour = neighbour->next;
            }
            return distance[dest];
        }
    }

    void updateTrafficCondition(int src,int dest,int newWeight){
        // will traverse the arrayList to find the source array of the list and then update the weight of respected edge
        ListNode*temp=ListArray[src].head;

        while(temp!=nullptr){
            if(temp->dest==dest){
                temp->weight=newWeight;
                cout<<"Traffic updated for edge ("<<src<<" -> "<<dest<<" ) "<<" with "<<newWeight<<endl;
                return;
            }
            temp=temp->next;
        }
        cout<<"Entered edge ("<<src<<" -> "<<dest<<" ) , not found ! "<<endl; 
    }

    void locateVehicle(string id, int currentLocation,int destination){
        cars[vehicleCount].currentLocation=currentLocation;
        cars[vehicleCount].destination=destination;
        cars[vehicleCount].id=id;
        cars[vehicleCount].pathLength=calculatePathLength(currentLocation,destination);
        cout<<"Shortest Path for vehicle "<<cars[vehicleCount].id;
        graph::DijkstraAlgo(currentLocation,destination);
        vehicleCount++;
    }


    void displayGraph(){
        for(int i=0;i<vertices;i++){
            cout<<"Intersection "<<i+1<<" : ";
            ListNode*temp=ListArray[i].head;
            while(temp!=nullptr){
                cout<<"("<<temp->dest<<" , "<<temp->weight<<")";
                temp=temp->next;
            }
            cout<<endl;
        }
    }
    void loadMapFromFile(const string&filename){
        ifstream file(filename);
        
        string line;
        int src,dest,weight;
        while(getline(file,line)){
            int pos1 = line.find(',');
            int pos2 = line.find(',', pos1 + 1);



            src=stoi( line.substr(0,pos1));
            dest=stoi(line.substr(pos1+1,pos2-pos1-1));
            weight=stoi(line.substr(pos2+1));
            addEdge(src,dest,weight);
        }
        file.close();
    }

    void LoadVehiclesFromFile(const string& filename){
        ifstream file(filename);

        string line;
        string V_id;
        int startVertex,endVertex;
        while(getline(file,line)){
            int pos1=line.find(',');
            int pos2=line.find(',',pos1+1);

            V_id=line.substr(0,pos1);
            startVertex=stoi(line.substr(pos1+1,pos2-pos1-1));
            endVertex=stoi(line.substr(pos2+1));
            locateVehicle(V_id,startVertex,endVertex);
        }
        file.close();
    }
};
int main(){
    int vertices=5;
    graph cityGraph(vertices);

    //loading the dataset
    cityGraph.loadMapFromFile("map.csv");
//    cityGraph.addEdge(0,1,5);
//    cityGraph.addEdge(0,2,15);
//    cityGraph.addEdge(1,2,10);
//    cityGraph.addEdge(1,3,9);
//    cityGraph.addEdge(2,3,7);
//    cityGraph.addEdge(3,4,3);

    //displaying the map
    cout<<"City Road Network : "<<endl;
    cityGraph.displayGraph();
    //cityGraph.removeIntersection(0);
    cout<<endl;
    cout<<endl;
    // cityGraph.displayGraph();
    // cout<<endl;
    // cout<<endl;
    //cityGraph.LoadVehiclesFromFile("vehicles.csv");
    cityGraph.locateVehicle("v1",0,4);
   // cityGraph.locateVehicle("v2",1,3);
   // cityGraph.locateVehicle("v3",0,2);
}
