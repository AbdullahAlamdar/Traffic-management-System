# **Traffic Management System**

## **Overview**
This Traffic Management System is a C++ program designed to simulate and manage a city's traffic flow. It leverages advanced data structures such as graphs, hash tables, and priority queues to implement functionalities like shortest path calculation, traffic signal management, vehicle movement simulation, and congestion monitoring.

---

## **Features**

### **1. Graph Representation**
- **Dynamic Road Network**: Represents the city as a graph with intersections (vertices) and roads (edges).
- **Add/Remove Intersections**: Dynamically add or remove intersections in the network.
- **Block Roads or Intersections**: Temporarily block roads or intersections to simulate roadblocks or accidents.

### **2. Shortest Path Calculation**
- **Dijkstra's Algorithm**: Calculates the shortest path between two intersections.
- **A* Algorithm**: Optimized shortest path calculation using heuristics.
- **Path Reconstruction**: Displays the calculated shortest path for vehicles.

### **3. Vehicle Management**
- **Vehicle Location**: Assign vehicles to specific intersections and their destinations.
- **Shortest Path Assignment**: Assigns the shortest path to vehicles based on their source and destination.
- **Simulation**: Simulates vehicle movement along their assigned paths.

### **4. Traffic Signal Management**
- **Priority Queue**: Manages roads based on vehicle density to optimize traffic signals.
- **Emergency Mode**: Clears paths for emergency vehicles using priority-based signaling.

### **5. Congestion Monitoring**
- **Hash Table**: Tracks vehicle counts on roads for real-time congestion analysis.
- **Congestion Identification**: Identifies congested roads based on a user-defined threshold.
- **Visual Representation**: Displays congestion levels using bar charts.

### **6. File Integration**
- **Load Network**: Reads the road network from a CSV file.
- **Load Vehicles**: Initializes vehicles and their routes from a CSV file.

### **7. Performance Monitoring**
- **Execution Time Measurement**: Measures the time taken to recalculate paths using shortest path algorithms.

---

## **Usage**

### **1. Compilation**
To compile the program, use the following command:
```bash
g++ -o traffic_system main.cpp
 ```
### **1. Execution**
to run the program , run following command:
```bash
./traffic_system
```
### **1. File Requirments**
- **map.csv:** Contains the road network in the format: source,destination,weight.
- **vehicles.csv**: Contains vehicle data in the format: id,source,destination.
- **traffic_signal_timings.csv:** contains traffic signals data indexes
- **emergency_vehicles.csv:** (ID, start, end, priority) from the file. 
- **accidents_or_closures.csv:** Accidents/Closures: Simulate disruptions by dynamically blocking roads as defined in the
file

### **1. Example Output : **
City Road Network
Intersection 0: (1, 10) (2, 15)
Intersection 1: (2, 10) (3, 5)
Intersection 2: (3, 10)

Shortest Paths for Vehicles
Shortest path for vehicle v1: 0 -> 1 -> 3 -> 4

Traffic Signals Information
Managing green signals based on vehicle density

Congestion Levels (represented with bar charts)
- **0-1: | | | | 5 Vehicles**
- **1-3: | | | | | | 10 Vehicles**

Performance Monitoring
Recalculating shortest path took 120 milliseconds.




