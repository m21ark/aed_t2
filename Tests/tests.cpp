#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/distanceCalc.h"
#include "../include/menu.h"
#include "../include/GraphBuilder.h"

using testing::Eq;


TEST(Test_lines_reader, Test_lines_reader) {

    vector<Line> lines = LinesReader("../dataset/lines.csv");

/*    for (const Line &l: lines)
        cout << l << endl;*/

}

TEST(Test_distance_calc, Test_distance_calc) {

    //cout << distanceCalc(41.17567866, -8.614147205, 41.19931569, -8.657616107) << endl;

}


TEST(Test_stops_reader, Test_stops_reader) {

    vector<Stop> stops = StopsReader("../dataset/stops.csv");

/*    for (const Stop &l: stops)
        cout << l << endl;*/

    //cout.precision(10);
    //cout << endl << stops[0].location << endl;

}

TEST(Test_model, Test_model_constructor) {
    GraphBuilder model = GraphBuilder();

    model.buildGraph();

    ASSERT_EQ(model.stopToIndex["1AL2"], 1);
    ASSERT_EQ(model.stopToIndex["ZOID2"], 2487);

}

TEST(Test_bfs, Test_bfs) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    //A melhor combinacao para testar é FRC ALXH1  ou CQ10 PSL1 porque atravessa o porto por comleto (muito longe)
    string origin = "FRC";
    string destiny = "ALXH1";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<Line> lines;

    list<int> path = graph.bfs_path(originIndex, destinyIndex, lines);

    cout << "Number of stops: " << path.size() << endl;

    cout << endl;

    int i = 0;


    if (path.size() != lines.size()) {
        cout << "Path size : " << path.size() << " => ";
        for (auto i: path) cout << model.indexToStop[i] << " ; ";
        cout << endl;
        cout << "Line size : " << lines.size() << " => ";
        for (auto i: lines) cout << i.code << " ; ";
        cout << endl << endl;
    }


    for (auto it = path.begin(); it != path.end(); it++) {

        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].name << endl;

        i++;
    }
}

TEST(Test_bfsPrint, Test_bfsPrint) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();


    //graph.bfsPrint(1);

}

TEST(Test_dijkstra, Test_dijkstra_zones) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = "FRC";
    string destiny = "ALXH1";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<Line> lines;

    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines, 1);

    cout << "\nNumber of stops: " << path.size() << endl;
    int i = 0;
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout <<setw(20)<< lines[i].name << "\t" << graph.getNode(*it).stop.zone << endl;


        i++;
    }

}

TEST(Test_dijkstra, Test_dijkstra_distance) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = "FRC";
    string destiny = "ALXH1";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<Line> lines;

    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines, 2);

    cout << "\nNumber of stops: " << path.size() << endl;
    int i = 0;
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout <<setw(20)<< lines[i].name << endl;
        i++;
    }

}


TEST(Test_dijkstra, Test_dijkstra_swap) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = "STBX2";
    string destiny = "VLC2";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<Line> lines;

    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines, 3);

    cout << "\nNumber of stops: " << path.size() << endl;
    int i = 0;
    for (auto it = path.begin(); it != path.end(); it++) {
        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout <<setw(20)<< lines[i].name << endl;
        i++;
    }

}


TEST(Test_bfs, Test_bfs_walk) {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = "FRC";
    string destiny = "ALXH1";

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    Location start = {41.15195430099009, -8.50037991170946}; //passal
    Location end = {41.18169909813813, -8.600008832034906}; //sjoao

    int radius = 500;

    graph.addGeoStartEndNode(start,end,radius);

    vector<Line> lines;

    list<int> path = graph.bfs_path(2488, 2489, lines);

    cout << "Number of stops: " << path.size() << endl;

    cout << endl;

    int i = 0;


    if (path.size() != lines.size()) {
        cout << "Path size : " << path.size() << " => ";
        for (auto i: path) cout << model.indexToStop[i] << " ; ";
        cout << endl;
        cout << "Line size : " << lines.size() << " => ";
        for (auto i: lines) cout << i.code << " ; ";
        cout << endl << endl;
    }


    for (auto it = path.begin(); it != path.end(); it++) {

        cout << setw(8) << model.indexToStop[*it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].name << endl;

        i++;
    }
}




