#ifndef AED_T2_GRAPHBUILDER_H
#define AED_T2_GRAPHBUILDER_H

#include "graph.h"
#include "files_reader.h"
#include "map"
#include "distanceCalc.h"
#include <climits>


inline bool file_exists(const std::string &name) {
    ifstream f(name.c_str());
    return f.good();
}

list<string> availableLines(const string &code) {
    list<string> l;

    string basicPath = "../dataset/line/line_";
    string format = ".csv";
    if (file_exists(basicPath + code + "_" + "0" + format))
        l.push_back(basicPath + code + "_" + "0" + format);
    if (file_exists(basicPath + code + "_" + "1" + format))
        l.push_back(basicPath + code + "_" + "1" + format);

    return l;
}


class GraphBuilder {


public:
    Graph graph;
    map<string, int> stopToIndex;

    Graph buildGraph() {
        graph = Graph(2487 + 2, true);

        int i = 1;
        for (auto d: StopsReader("../dataset/stops.csv")) {
            graph.addNode(i, d.code);
            stopToIndex.insert(pair<string, int>(d.code, i++));
        }

        for (const auto &l: LinesReader("../dataset/lines.csv")) {
            auto aL = availableLines(l.code);
            while (!aL.empty()) {
                auto first = aL.front();
                aL.pop_front();
                LineStops list;
                ifstream f(first);
                f >> list;
                if (list.stops.empty())
                    continue;
                auto it = ++list.stops.begin();
                for (auto s = list.stops.begin();
                     s != list.stops.end(); s++) { // the circular stuff should be treated differently TODO
                    if (it != list.stops.end()) {
                        auto b = stopToIndex[*s];
                        auto end = stopToIndex[*it];
                        graph.addEdge(b, end, first, INT_MAX);
                    } else
                        break;
                    it++;
                }
            }
        }
        return graph;
    }

};


#endif //AED_T2_GRAPHBUILDER_H
