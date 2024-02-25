#include "graph.h"

Graph::Graph(const string& filename) {
    ifstream file(filename);
    int i, j;
    int max_vertex = 0;

    while (file >> i >> j) {
        max_vertex = max(max_vertex, max(i, j));
    }

    adjacencyList.resize(max_vertex + 1);
    visited.resize(max_vertex + 1, false);

    file.clear();
    file.seekg(0, ios::beg);

    while (file >> i >> j) {
        adjacencyList[i].push_back(j);
        adjacencyList[j].push_back(i);
    }

    file.close();
}

vector<int> Graph::dfs(int node, vector<int>& component) {
    visited[node] = true;
    component.push_back(node);

    for (int i = 0; i < adjacencyList[node].size(); ++i) {
        if (!visited[adjacencyList[node][i]]) {
            dfs(adjacencyList[node][i], component);
        }
    }

    return component;
}

void Graph::findLargestComponent() {
    int largestComponentSize = 0;
    vector<int> largestComponent;

    for (int i = 0; i < adjacencyList.size(); ++i) {
        if (!visited[i]) {
            vector<int> component;
            component = dfs(i, component);
            if (component.size() > largestComponentSize) {
                largestComponentSize = component.size();
                largestComponent = component;
            }
        }
    }

    cout << "Largest component size: " << largestComponentSize << endl;
}

//void Graph::calculateGlobalClusteringCoefficient() {
//    int totalTriangles = 0;
//    int totalTriplets = 0;
//
//    for (int i = 0; i < adjacencyList.size(); ++i) {
//        for (int j = 0; j < adjacencyList[i].size(); ++j) {
//            for (int k = 0; k < adjacencyList[j].size(); ++k) {
//                if (adjacencyList[j][k] == i) {
//                    totalTriangles++;
//                }
//                if (find(adjacencyList[i].begin(), adjacencyList[i].end(), adjacencyList[j][k]) != adjacencyList[i].end()) {
//                    totalTriplets++;
//                }
//            }
//        }
//    }
//
//    double globalClusteringCoefficient = static_cast<double>(totalTriangles) / static_cast<double>(totalTriplets);
//    cout << "Global clustering coefficient: " << globalClusteringCoefficient << endl;
//}

void Graph::calculateGlobalClusteringCoefficient() {
    int totalTriangles = 0;
    int totalTriplets = 0;

    for (int i = 0; i < adjacencyList.size(); ++i) {
        if (visited[i]) {
            int degree = adjacencyList[i].size();
            int localTriangles = 0;
            for (int j = 0; j < degree; ++j) {
                int neighbor = adjacencyList[i][j];
                for (int k = j + 1; k < degree; ++k) {
                    int anotherNeighbor = adjacencyList[i][k];
                    if (find(adjacencyList[neighbor].begin(), adjacencyList[neighbor].end(), anotherNeighbor) != adjacencyList[neighbor].end()) {
                        localTriangles++;
                    }
                }
            }
            totalTriangles += localTriangles / 2;
            totalTriplets += degree * (degree - 1) / 2;
        }
    }

    double globalClusteringCoefficient = static_cast<double>(3 * totalTriangles) / static_cast<double>(totalTriplets);
    cout << "Global clustering coefficient: " << globalClusteringCoefficient << endl;
}