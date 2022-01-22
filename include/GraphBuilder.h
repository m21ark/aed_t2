#ifndef AED_T2_GRAPHBUILDER_H
#define AED_T2_GRAPHBUILDER_H

#include "graph.h"
#include "files_reader.h"
#include "map"
#include "distanceCalc.h"
#include <climits>


class GraphBuilder {

private:

    bool includeM_lines;

    void addNodes();

    void addEdges();

public:
    Graph graph;
    map<string, int> stopToIndex;
    map<int, string> indexToStop;

    Graph buildGraph(bool includeMLines = true) {
        graph = Graph(2487 + 2, true);
        this->includeM_lines = includeMLines;
        addNodes();
        addEdges();
        return graph;
    }

    int nodeGeoDistance(int start, int end);

    static bool file_exists(const string &name);

    list<string> available_1_Lines(const string &code) const;
    list<string> available_0_Lines(const string &code) const;
};


#endif //AED_T2_GRAPHBUILDER_H
