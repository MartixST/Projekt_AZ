        #include "graph.h"

        int main() {
            string filename = "graph.txt";
            Graph graph(filename);

            graph.findLargestComponent();
            graph.calculateGlobalClusteringCoefficient();

            return 0;
        }