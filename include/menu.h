#ifndef AED_T2_MENU_H
#define AED_T2_MENU_H


#include <iostream>
#include <vector>
#include <string>
#include "files_reader.h"
#include "graph.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


#define geoCQueijo {41.16861948613213, -8.6899475068589}
#define geoFeup {41.17838121987286, -8.599018100763733}
#define geoPassal {41.15203283630788, -8.49986876108789}
#define geoFcup {41.15223552642268, -8.636936732334394}
#define geoFrancelos {41.10191154587645, -8.659713734654174}
#define geoIkea {41.20962241758282, -8.688599177567802}
#define geoAliados {41.14843076280013, -8.610857716992687}
#define geoBomSucesso {41.15576823832895, -8.629961857769722}
#define geoPalBolsa {41.14073588624748, -8.615741317702945}
#define geoGaiaShopping {41.117352653497626, -8.621390956976255}
#define geoNorteShopping {41.17921590595752, -8.652310502100645}
#define geoCordoaria {41.14546314938763, -8.616957405759472}
#define geoAlfena {41.24468890867462, -8.52083368770199}
#define geoCampanha {41.14885301366697, -8.585581573539976}
#define geoSouto {41.136360363397294, -8.530595914787796}
#define geoStartNode 2488
#define geoEndNode 2489

using namespace std;


class Menu {

private:

    Location localStart, localEnd;
    string codeStart, codeEnd;
    int footDistance = 500;
    bool useMLines = true;


    enum STATE {
        location, criteria, close
    };

    static bool menuConfirmationPrompt();


public:

    STATE locationMenu();

    STATE criteriaMenu();

    void start();

    static list<int> minStops(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex);

    static list<int> minDistance(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex);

    static list<int> minZones(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex);

    static list<int> minSwaps(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex);

    void askLocationStops();

    void askLocationCords();

    void settingsMenu();

    void resetMenuVars();

    void showGeneratedPath(int pathCriteria);

    void askFootDistance();

    void askUseMLines();

    bool processStoredCords(const string &input, Location &location);
};

string trimStr(istream &ios, string str);

bool emptyStream(istream &ios);

#endif