#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/distanceCalc.h"
#include "../include/menu.h"
#include "../include/GraphBuilder.h"


#define geoCQueijo {41.16861948613213, -8.6899475068589}
#define geoFeup {41.17838121987286, -8.599018100763733}
#define geoPassal {41.15203283630788, -8.49986876108789}
#define geoFcup {41.15223552642268, -8.636936732334394}
#define geoFrancelos {41.10191154587645, -8.659713734654174}
#define geoIkea {41.20962241758282, -8.688599177567802}

#define geoStartNode 2488
#define geoEndNode 2489


using testing::Eq;


TEST(Test_bfs, Test_bfs) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    //A melhor combinacao para testar é FRC ALXH1  ou CQ10 PSL1 porque atravessa o porto por comleto (muito longe)
    string origin = "PSL2";
    string destiny = "ASP2";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<pair<Line, bool>> lines;

    list<int> path = graph.bfs_path(originIndex, destinyIndex, lines);

    cout << "Number of stops: " << path.size() << endl;

    cout << endl;

    int i = 0;


    if (path.size() != lines.size()) {
        cout << "Path size : " << path.size() << " => ";
        for (auto i: path) cout << model.indexToStop[i] << " ; ";
        cout << endl;
        cout << "Line size : " << lines.size() << " => ";
        for (auto i: lines) cout << i.first.code << " ; ";
        cout << endl << endl;
    }

    for (auto it = path.begin(); it != path.end(); it++) {

        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].first.name << endl;

        i++;
    }
}

TEST(Test_dijkstra, Test_dijkstra_zones) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph(false);

    string origin = "FRC";
    string destiny = "ALXH1";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    graph.addGeoStartEndNode(geoFeup, geoPassal, 500);
    vector<pair<Line, bool>> lines;

    list<int> path = graph.dijkstra_path(geoStartNode, geoEndNode, lines, 1);

    cout << "\nNumber of stops: " << path.size() << endl;
    int i = 0;
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << setw(20) << lines[i].first.lineDirectionName(lines[i].second) << "\t" << graph.getNode(*it).stop.zone
             << endl;


        i++;
    }

}

