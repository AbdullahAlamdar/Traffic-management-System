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


    graph(int vertices){
        this->vertices=vertices;
        ListArray=new list[vertices];
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
    }//
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
    cityGraph.DijkstraAlgo(0,4);
}
