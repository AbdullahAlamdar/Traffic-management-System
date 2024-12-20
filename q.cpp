#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<chrono>
using namespace std;

class ListNode{
    public:
    int dest;
    int weight;
    bool blocked;
    ListNode*next;

    ListNode(int dest, int weight){
        this->dest=dest;
        this->weight=weight;
        this->blocked=false;
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

    void displayVehicleInfo(){
        cout<<"Vehicle id : "<<id<<endl;
        cout<<"Current Location : "<<currentLocation<<endl;
        cout<<"Destination : "<<destination<<endl;
    }

};

class PQNode{
    public:
    int roadId;
    int vehicleDensity;
    int greenTime;
    PQNode*next;

    PQNode(int roadId,int vehicleDensity,int greenTime){
        this->roadId=roadId;
        this->vehicleDensity=vehicleDensity;
        this->greenTime=greenTime;
        next=nullptr;
    }
};
class HashNode{
    public:
    string roadID;
    int vehicleCount;
    HashNode*next;

    HashNode(string roadID,int vehicleCount){
        this->roadID=roadID;
        this->vehicleCount=vehicleCount;
        next=nullptr;
    }
};

class HashTable{
    public:
    static const int tableSize=200;
    HashNode*table[tableSize];

    HashTable(){
        for(int i=0;i<tableSize;i++){
            table[i]=nullptr;
        }
    }

    int hashFunction(string roadId){
        int hash =0;
        for(int i=0;i<roadId.length();i++){
            hash=(hash*31+roadId[i])%tableSize;
        }
        return hash;
    }
    void insert(string roadId, int VehicleCount){
        int index=hashFunction(roadId);

        HashNode*head=table[index];

        while(head!=nullptr){
            if(head->roadID==roadId){
                head->vehicleCount+=VehicleCount;
                return;
            }
            head=head->next;
        }

        // in case of new node
        HashNode*nn=new HashNode(roadId,VehicleCount);
        nn->next=table[index];
        table[index]=nn;
    }

    int getVehicleCount(string roadId){
        int index=hashFunction(roadId);
        HashNode*head=table[index];

        while(head!=nullptr){
            if(head->roadID==roadId){
                return head->vehicleCount;
            }
            head=head->next;
        }
        return 0;
    }

    void identifyCongestedRoads(int threshold){
        cout<<"(Congested roads Vehicle Count > "<<threshold<<" ) "<<endl;
        for(int i=0;i<tableSize;i++){
            HashNode*head=table[i];

            while(head!=nullptr){
                if(head->vehicleCount>threshold){
                    cout<<"Road with ID : ("<<head->roadID<<") is congested ! "<<endl;
                }
                head=head->next;
            }
            
        } 
    }
    void displayCongestionLevelBar(){
        cout<<"Congestion Level (Road ID : | Vehicle Count )"<<endl;
        for(int i=0;i<tableSize;i++){
            HashNode*head=table[i];
            
            while(head!=nullptr){
                cout<<head->roadID<<": ";
                for(int j=0;j<head->vehicleCount;j++){
                    cout<<"| ";
                }
                cout<<" "<<head->vehicleCount<<"Vehicles"<<endl;
                head=head->next;
            }
        }
    }

    void display() {
        cout << "Hash Table (Road ID -> Vehicle Count):" << endl;
        for (int i = 0; i < tableSize; i++) {
            HashNode* head = table[i];
            while (head != nullptr) {
                cout << head->roadID << " -> " << head->vehicleCount << endl;
                head = head->next;
            }
        }
    }
};

class priorityQueue{
    public:
    PQNode*head;

    priorityQueue(){
        head=nullptr;
    }

    void push(int id,int density,int greenTime){
        PQNode*nn=new PQNode(id,density,greenTime);
        if(head==nullptr || head->vehicleDensity<density){
            nn->next=head;
            head=nn;

        }
        else{
            PQNode*temp=head;
            while(temp->next !=nullptr && temp->next->vehicleDensity >=density){
                temp=temp->next;
            }
            nn->next=temp->next;
            temp->next=nn;
        }
    }
    PQNode*pop(){
        if(head==nullptr){
            cout<<"Priority Queue is empty ! "<<endl;
            return nullptr;
        }
        else{
            PQNode*temp=head;
            head=head->next;
            return temp;
        }
    }
    bool isPQEmpty(){
        if(head==nullptr){
            return true;
        }
        return false;
    }
    PQNode* searchAndPop(int routeId){
        PQNode*temp=head;
        while(temp!=nullptr){
            if(temp->roadId==routeId){
                return temp;
            }
        }
        cout<<"Road with route id : "<<routeId<<" Not Found ! "<<endl;
        return nullptr;
    }
    void displayPQ(){
        PQNode*temp=head;
        cout<<"Priority Queue : ";
        while(temp!=nullptr){
            cout<<"(Road id : "<<temp->roadId<<", Density "<<temp->vehicleDensity<<" )"<<endl;
            temp=temp->next;
        }
        cout<<"NULL"<<endl;
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

class trafficSignalManager{
    public:
    priorityQueue pq;
    bool emergencyMode;
    int emergencyPath[100];
    int pathLength;// length for emergency path 

    trafficSignalManager(){
        emergencyMode=false;
        pathLength=0;
    }

    void addroad(int roadId,int density){
        pq.push(roadId,density,30);
    }

    void manageSignals(){
        if(emergencyMode){
            cout<<"Route id : ";
            int id;
            cin>>id;
            PQNode*road=pq.searchAndPop(id);
            if(road){
                cout<<"Green signal , granted (Route id : "<<id<<" )"<<endl;
                emergencyMode=false;
            }
            else{
                cout<<"Can not grant green signal (Route id : "<<id<<" )"<<endl;
            }

        }
        else{
            while (!pq.isPQEmpty()) {
                PQNode* road = pq.pop();
                if (road) {
                    cout << "Granting green signal to Road " << road->roadId;
                    cout<< " with density " << road->vehicleDensity << endl;
                    delete road; // Clean up memory
                }
            }

        }
    }
    void declareRoadEmergency(){
        cout<<"Emergency mode declared ! "<<endl;
        emergencyMode=true;
    }

    void clearPath(int src, int dest) {
        cout << "Clearing path for emergency vehicle from " << src << " to " << dest << endl;
        for (int i = 0; i < pathLength - 1; i++) {
            cout << "Granting green signal for road (" << emergencyPath[i] << " -> " << emergencyPath[i + 1] << ")" << endl;
        }
    }

    void restoreNormalFlow() {
        emergencyMode = false;
        cout << "Restoring normal traffic flow..." << endl;
    }


};

class graph{
    public:
    int vertices;
    list*ListArray;
    vehicle cars[50];
    int vehicleCount;
    //bool blocked;

    graph(int vertices){
        this->vertices=vertices;
        ListArray=new list[vertices];
        vehicleCount=0;
        //this->blocked=false;
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
                if(neighbour->blocked){
                    neighbour=neighbour->next;
                    continue;
                }
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

    void aStarSearch(int src, int dest, trafficSignalManager& tsm) {
            int gScore[vertices]; // Cost from start to the current node
            int fScore[vertices]; // Estimated cost from start to goal via the current node
            int parent[vertices]; // Track the path
            bool visited[vertices] = {false};

            // Initialize scores
            for (int i = 0; i < vertices; i++) {
                gScore[i] = INT8_MAX;
                fScore[i] = INT8_MAX;
                parent[i] = -1;
            }
            gScore[src] = 0;
            fScore[src] = heuristic(src, dest);

            // Priority queue for nodes to explore
            priorityQueue openSet;
            openSet.push(src, fScore[src], 0);

            while (!openSet.isPQEmpty()) {
                PQNode* currentNode = openSet.pop();
                int current = currentNode->roadId;
                delete currentNode;

                if (current == dest) {
                    // Reconstruct path
                    reconstructPath(parent, dest, tsm);
                    return;
                }

                visited[current] = true;

                ListNode* neighbor = ListArray[current].head;
                while (neighbor != nullptr) {
                    int neighborNode = neighbor->dest;
                    int weight = neighbor->weight;

                    if (visited[neighborNode]) {
                        neighbor = neighbor->next;
                        continue;
                    }

                    int tentativeGScore = gScore[current] + weight;

                    if (tentativeGScore < gScore[neighborNode]) {
                        parent[neighborNode] = current;
                        gScore[neighborNode] = tentativeGScore;
                        fScore[neighborNode] = gScore[neighborNode] + heuristic(neighborNode, dest);

                        // Add to priority queue
                        openSet.push(neighborNode, fScore[neighborNode], 0);
                    }

                    neighbor = neighbor->next;
                }
            }

            cout << "No path found from " << src << " to " << dest << endl;
        }

        // Heuristic function (example: straight-line distance)
        int heuristic(int node, int dest) {
            // Replace with actual heuristic calculation
            return abs(node - dest);
        }

    void reconstructPath(int parent[], int dest, trafficSignalManager& tsm) {
        int path[vertices];
        int length = 0;

        for (int v = dest; v != -1; v = parent[v]) {
            path[length++] = v;
        }

        // Reverse the path and store it in trafficSignalManager
        tsm.pathLength = length;
        for (int i = 0; i < length; i++) {
            tsm.emergencyPath[i] = path[length - 1 - i];
        }

        // Display the path
        cout << "Fastest path for emergency vehicle: ";
        for (int i = 0; i < length; i++) {
            cout << tsm.emergencyPath[i];
            if (i < length - 1) cout << " -> ";
        }
        cout << endl;
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
                if(neighbour->blocked){
                    neighbour->next;
                    continue;
                }
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

    void blockRoad(int src, int dest) {
        ListNode* temp = ListArray[src].head;
        while (temp != nullptr) {
            if (temp->dest == dest) {
                temp->blocked = true;
                cout << "Road (" << src << " -> " << dest << ") is now blocked." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Road (" << src << " -> " << dest << ") not found in the graph." << endl;
    }

    void blockIntersection(int intersection) {
        // Block all outgoing roads
        ListNode* temp = ListArray[intersection].head;
        while (temp != nullptr) {
            temp->blocked = true;
            temp = temp->next;
        }

        // Block all incoming roads
        for (int i = 0; i < vertices; i++) {
            ListNode* temp = ListArray[i].head;
            while (temp != nullptr) {
                if (temp->dest == intersection) {
                    temp->blocked = true;
                }
                temp = temp->next;
            }
        }
        cout << "Intersection " << intersection << " is now blocked." << endl;
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

void locateVehicle(string id, int currentLocation, int destination) {
    if (vehicleCount >= 50) {
        cout << "Maximum vehicle limit reached!" << endl;
        return;
    }

    vehicle& v = cars[vehicleCount];
    v.currentLocation = currentLocation;
    v.destination = destination;
    v.id = id;
    v.pathIndex = 0; // Start from the beginning of the path

    // Calculate the shortest path using Dijkstra's Algorithm
    int distance[vertices];
    int parent[vertices];
    bool visited[vertices];

    // Initialize arrays
    for (int i = 0; i < vertices; i++) {
        distance[i] = INT8_MAX;
        parent[i] = -1;
        visited[i] = false;
    }
    distance[currentLocation] = 0;

    // Dijkstra's Algorithm
    for (int count = 0; count < vertices - 1; count++) {
        int minDistance = INT8_MAX, u = -1;
        for (int i = 0; i < vertices; i++) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                u = i;
            }
        }

        if (u == -1) break; // No more reachable nodes
        visited[u] = true;

        ListNode* neighbor = ListArray[u].head;
        while (neighbor != nullptr) {
            int v = neighbor->dest;
            int weight = neighbor->weight;
            if (!visited[v] && distance[u] != INT8_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
            neighbor = neighbor->next;
        }
    }

    // Backtrack to find the shortest path
    int path[vertices];
    int pathLength = 0;
    for (int v = destination; v != -1; v = parent[v]) {
        path[pathLength++] = v;
    }

    // Reverse the path to store it in the vehicle object
    for (int i = 0; i < pathLength; i++) {
        v.shortestPath[i] = path[pathLength - 1 - i];
    }
    v.pathLength = pathLength;

    // Display the shortest path
    cout << "Shortest path for vehicle " << id << ": ";
    for (int i = 0; i < pathLength; i++) {
        cout << v.shortestPath[i];
        if (i < pathLength - 1) cout << " -> ";
    }
    cout << endl;

    vehicleCount++;
}


    void stimulateVehicles() {
    cout << "Simulating vehicle movements" << endl;

    for (int i = 0; i < vehicleCount; i++) {
        vehicle& v = cars[i];

        //  to Check if the vehicle has already reached its destination
        if (v.pathIndex >= v.pathLength - 1) {
            cout << "Vehicle " << v.id << " has already reached its destination: " << v.destination << endl;
        } else {
            // to Move the vehicle to the next location in its path
            v.pathIndex++;
            v.currentLocation = v.shortestPath[v.pathIndex];

            // display the updated status
            cout << "Vehicle " << v.id << " moved to intersection " << v.currentLocation << endl;

            //  to Check if this is the destination
            if (v.currentLocation == v.destination) {
                cout << "Vehicle " << v.id << " has reached its destination: " << v.destination << endl;
            }
        }
    }
    cout << "Simulation step complete." << endl;
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




// function for monitoring system performance
    void monitorPerformance(graph& g, int src, int dest) {
        using namespace std::chrono;
        auto start = high_resolution_clock::now();

        g.DijkstraAlgo(src, dest);

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        cout << "Recalculation completed in " << duration.count() << " ms." << endl;
    }


int main() {
    int vertices;
    cout << "Enter the number of intersections (vertices) in the city graph: ";
    cin >> vertices;

    graph cityGraph(vertices);
    cout << "\nCity Road Network initialized with " << vertices << " intersections.\n";

    int choice;
    do {
        cout << "\n--- Traffic Management System ---\n";
        cout << "1. Load map from file\n";
        cout << "2. Display city road network\n";
        cout << "3. Add a new intersection\n";
        cout << "4. Remove an intersection\n";
        cout << "5. Block a road\n";
        cout << "6. Locate a vehicle and find shortest path\n";
        cout << "7. Simulate vehicle movements\n";
        cout << "8. Update traffic condition\n";
        cout << "9. Manage traffic signals\n";
        cout << "10. Declare and handle emergency\n";
        cout << "11. Monitor congestion levels\n";
        cout << "12. Monitor system performance\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string filename;
                cout << "Enter the file name to load map (e.g., map.csv): ";
                cin >> filename;
                cityGraph.loadMapFromFile(filename);
                cout << "Map loaded successfully!\n";
                break;
            }
            case 2:
                cout << "Displaying City Road Network:\n";
                cityGraph.displayGraph();
                break;
            case 3: {
                int newIntersection;
                cout << "Enter new intersection index: ";
                cin >> newIntersection;
                cityGraph.addNewIntersection(newIntersection);
                break;
            }
            case 4: {
                int intersection;
                cout << "Enter intersection index to remove: ";
                cin >> intersection;
                cityGraph.removeIntersection(intersection);
                break;
            }
            case 5: {
                int src, dest;
                cout << "Enter source and destination to block the road (e.g., 0 1): ";
                cin >> src >> dest;
                cityGraph.blockRoad(src, dest);
                break;
            }
            case 6: {
                string id;
                int src, dest;
                cout << "Enter vehicle ID, source, and destination (e.g., v1 0 4): ";
                cin >> id >> src >> dest;
                cityGraph.locateVehicle(id, src, dest);
                break;
            }
            case 7:
                cout << "Simulating vehicle movements:\n";
                cityGraph.stimulateVehicles();
                break;
            case 8: {
                int src, dest, weight;
                cout << "Enter source, destination, and new weight for the road (e.g., 1 2 15): ";
                cin >> src >> dest >> weight;
                cityGraph.updateTrafficCondition(src, dest, weight);
                break;
            }
            case 9: {
                trafficSignalManager tsm;
                int id, density;
                cout << "Enter road ID and vehicle density (e.g., 1 50): ";
                cin >> id >> density;
                tsm.addroad(id, density);
                cout << "Managing traffic signals:\n";
                tsm.manageSignals();
                break;
            }
            case 10: {
                int src, dest;
                trafficSignalManager tsm;
                cout << "Enter source and destination for emergency path: ";
                cin >> src >> dest;
                tsm.declareRoadEmergency();
                cityGraph.aStarSearch(src, dest, tsm);
                tsm.clearPath(src, dest);
                tsm.restoreNormalFlow();
                break;
            }
            case 11: {
                HashTable hst;
                int threshold, count;
                string roadId;
                cout << "Enter road ID and vehicle count (e.g., 0-4 15): ";
                cin >> roadId >> count;
                hst.insert(roadId, count);
                cout << "Enter congestion threshold: ";
                cin >> threshold;
                hst.identifyCongestedRoads(threshold);
                hst.displayCongestionLevelBar();
                break;
            }
            case 12: {
                int src, dest;
                cout << "Enter source and destination for performance monitoring: ";
                cin >> src >> dest;
                monitorPerformance(cityGraph, src, dest);
                break;
            }
            case 0:
                cout << "Exiting Traffic Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

