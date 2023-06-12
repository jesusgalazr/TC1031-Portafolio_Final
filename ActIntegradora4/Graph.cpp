#include "Graph.h"

Graph::Graph() {
  adjList.clear();
}

Graph::~Graph() {
  adjList.clear();
}
// O(n)
void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}
//O(n)
void Graph::loadDirWeightedGraph(std::istream & input) {
  std::string line;
  int i = 0;
  while (std::getline(input, line)) {
    if (i == 0) {
      i++;
      continue;
    }
    if (i == 1) {
      std::vector<int> result;
      split(line, result);
      numNodes = result[0];
      numEdges = result[2];
      adjList.resize(numNodes + 1);
      for (int k = 1; k <= numNodes; k++) {
        LinkedList<std::pair<int, int>> tmpList;
        adjList[k] = tmpList;
      }
      i++;
      continue;
    }
    std::vector<int> result;
    split(line, result);
    int nodoU = result[0];
    int nodoV = result[1];
    int weight = result[2];
    adjList[nodoU].addLast(std::make_pair(nodoV, weight));
    i++;
  }
}



//O((V+E) log V
void Graph::dijkstraAlgorithm(int v) {
  // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
  std::vector<int> dist(numNodes+1, INF);
  pq.push(std::make_pair(0, v)); 
  dist[v] = 0;
  while (!pq.empty()) {
    int nodeU = pq.top().second; 
    pq.pop();
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int nodeV = par.first;
      int peso = par.second;
      if (dist[nodeV] > dist[nodeU]+peso) {
        dist[nodeV] = dist[nodeU] + peso;
        pq.push(std::make_pair(dist[nodeV], nodeV));
      }
      ptr = ptr->next;
    }
  }

  std::cout << "\n";
  std::cout << "Short Path" << std::endl;
  for (int i = 1; i <= numNodes; i++) {
    if (dist[i] != INF)
      std::cout << i << "\t" << dist[i] << std::endl;
    else
      std::cout << i << "\tINF" << std::endl;
  }
}

bool Graph::DFSUtil(int v, std::vector<int>& color) {
  for (NodeLinkedList<std::pair<int, int>>* i = adjList[v].getHead(); i != nullptr; i = i->next) {
    int u = i->data.first;
    if (color[u] == -1) {
      color[u] = 1 - color[v];
      if (!DFSUtil(u, color)) {
        return false;
      }
    }
    else if (color[u] == color[v]) {
      return false;
    }
  }
  return true;
}

