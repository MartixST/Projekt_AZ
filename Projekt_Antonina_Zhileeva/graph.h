#pragma once

#include <unordered_map>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

class Graph {
public:
    Graph(const string& filename);
    void findLargestComponent();
    void calculateGlobalClusteringCoefficient();

private:
    vector<vector<int>> adjacencyList;
    vector<bool> visited;
    vector<int> dfs(int node, vector<int>& component);
};