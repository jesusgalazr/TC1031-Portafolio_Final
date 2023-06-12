//Victor Manuel Huerta Loretz A01365532
// Jesús Alonso Galaz Reyes 
//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
// https://stackoverflow.com/questions/18429021/why-is-infinity-0x3f3f3f3f
//https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
//https://www.geeksforgeeks.org/heap-data-structure/
//https://www.geeksforgeeks.org/heap-data-structure/
//https://www.softwaretestinghelp.com/graph-implementation-cpp/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include "MaxHeap.h"

struct Edge {
    std::string originIP;
    std::string destinationIP;
    int weight;
};
//O(1)
struct Node {
    std::string ip;
    int distance;

    Node(const std::string& ip, int distance) : ip(ip), distance(distance) {}

    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

int main() {
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    std::unordered_map<std::string, int> degreeMap;
    MaxHeap maxHeap;
//(O(N))
    std::ifstream file("bitacoraGrafos.txt");
    std::string line;
    std::string originIP;
    int numIPs;

    if (std::getline(file, line)) {
        numIPs = std::stoi(line);
    }

    for (int i = 0; i < numIPs; ++i) {
        if (std::getline(file, line)) {
            degreeMap[line] = 0;
        }
    }
    //O(n)
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Edge edge;
        std::string temp;

        iss >> temp >> temp >> temp;
        iss >> edge.originIP;
        iss >> edge.destinationIP;
        iss >> edge.weight;
        getline(iss, temp);

        edge.originIP = edge.originIP.substr(0, edge.originIP.find(":"));
        edge.destinationIP = edge.destinationIP.substr(0, edge.destinationIP.find(":"));

        adjacencyList[edge.originIP].push_back(edge);
        degreeMap[edge.originIP]++;
    }

    file.close();
//O(M log N)
    std::ofstream output("grados_ips.txt");
    for (auto& pair : degreeMap) {
        output << pair.first << ", " << pair.second << "\n";
        maxHeap.push(std::make_pair(pair.second, pair.first));
    }
    output.close();
//O(N log N)
    std::ofstream output2("mayores_grados_ips.txt");
    for (int i = 0; i < 5 && !maxHeap.empty(); ++i) {
        auto top = maxHeap.top();
        output2 << top.second << ", " << top.first << "\n";
        maxHeap.pop();
    }
    output2.close();

    auto bootMaster = std::max_element(degreeMap.begin(), degreeMap.end(),
                                       [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) -> bool {
                                           return a.second < b.second;
                                       });

    std::cout << "La IP del Boot Master es: " << bootMaster->first << " con " << bootMaster->second << " conexiones de salida.\n";
//O(V + E + V log V)
  //https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
    std::unordered_map<std::string, int> distanceMap;
    std::unordered_map<std::string, std::string> previousMap;

    for (const auto& pair : adjacencyList) {
        const std::string& ip = pair.first;
        distanceMap[ip] = (ip == bootMaster->first) ? 0 : INT_MAX;
    }

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push(Node(bootMaster->first, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        const std::string& currentIP = current.ip;
        int currentDistance = current.distance;

        if (currentDistance > distanceMap[currentIP]) {
            continue;
        }

        for (const Edge& edge : adjacencyList[currentIP]) {
            const std::string& neighborIP = edge.destinationIP;
            int weight = edge.weight;
            int newDistance = currentDistance + weight;

            if (newDistance < distanceMap[neighborIP]) {
                distanceMap[neighborIP] = newDistance;
                previousMap[neighborIP] = currentIP;
                pq.push(Node(neighborIP, newDistance));
            }
        }
    }

    std::ofstream output3("distancia_bootmaster.txt");
    for (const auto& pair : distanceMap) {
        output3 << pair.first << ", " << pair.second << "\n";
    }
    output3.close();
//O(n
//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
    std::ifstream input("distancia_bootmaster.txt");
    std::string ip;
    int shortestDistance = INT_MAX;
    std::string targetIP;

    while (std::getline(input, line)) {
        std::istringstream iss(line);
        iss >> ip;
        int distance;
        if (iss >> distance) {
            if (distance < shortestDistance) {
                shortestDistance = distance;
                targetIP = ip;
            }
        }
    }

    input.close();

    std::cout << "La ip mas probable para el ataque es: " << targetIP << std::endl;

    return 0;
}

