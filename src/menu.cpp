#include <iomanip>
#include "../include/menu.h"
#include "../include/GraphBuilder.h"

string trimStr(istream &ios, string str) {
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    return str;
}

bool emptyStream(istream &ios) {
    string bufferContent;
    getline(ios, bufferContent);
    trimStr(ios, bufferContent);
    if (bufferContent.empty())
        return true;
    return false;
}

bool Menu::menuConfirmationPrompt() {
    char confirm;

    cout << "\nConfirm? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
        return true;
    else {
        cout << "Canceled. Press any key to continue...";
        cin.clear();
        cin.ignore(10000, '\n');
        getchar();
    }


    return false;
}


Menu::STATE Menu::criteriaMenu() {
    char userInput;
    string inputError;

    while (true) {
        system(CLEAR);

        if (!inputError.empty())
            cout << inputError;
        inputError = "";

        cout << "========================" << endl;
        cout << "    Minimum Criteria   " << endl;
        cout << "========================" << endl;
        cout << "  1)  Stops " << endl;
        cout << "  2)  Distance" << endl;
        cout << "  3)  Zones" << endl;
        cout << "  4)  Line Changes" << endl;
        cout << "  5)  Go back  " << endl;
        cout << "  0)  Exit" << endl;
        cout << "========================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "Invalid Input!\n";
                continue;
            }

            switch (userInput) {
                case '0':
                    return close;
                case '1':
                    showGeneratedPath(1);
                    return criteria;
                case '2':
                    showGeneratedPath(2);
                    return criteria;
                case '3':
                    showGeneratedPath(3);
                    return criteria;
                case '4':
                    showGeneratedPath(4);
                    return criteria;
                case '5':
                    return location;
                default:
                    cout << "Invalid Input!\n";
                    break;
            }
            continue;

        } else {
            cout << "Invalid Input!\n";
            continue;
        }
    }
}

Menu::STATE Menu::locationMenu() {

    resetMenuVars();

    char userInput;
    string inputError;

    while (true) {
        system(CLEAR);

        if (!inputError.empty())
            cout << inputError;
        inputError = "";


        cout << "===========================" << endl;
        cout << "        Location  " << endl;
        cout << "===========================" << endl;
        cout << "    1)  Stops " << endl;
        cout << "    2)  Coordinates" << endl;
        cout << "    3)  Settings " << endl;
        cout << "    0)  Exit" << endl;
        cout << "===========================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "Invalid Input!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            switch (userInput) {
                case '0':
                    return close;
                case '1':
                    locationStops();
                    return menuConfirmationPrompt() ? criteria : location;
                case '2':
                    locationCords();
                    return menuConfirmationPrompt() ? criteria : location;
                case '3':
                    settingsMenu();
                    return location;
                default:
                    cout << "Invalid Input!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    getchar();
                    break;
            }
            continue;

        } else {
            cout << "Invalid Input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            getchar();
            continue;
        }
    }
}


list<int> Menu::minStops(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex) {

    list<int> path = graph.bfs_path(originIndex, destinyIndex, lines);
    cout << "\nNumber of stops: " << graph.getNode(destinyIndex).dist << endl << endl;

    return path;

}

list<int> Menu::minDistance(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex) {

    graph.dijkstra_distance(originIndex);
    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines);
    cout << "\nDistance: " << graph.getNode(destinyIndex).dist << endl << endl;
    return path;

}


list<int> Menu::minZones(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex) {

    graph.dijkstra_zones(originIndex);
    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines);
    cout << "\nNumber of Zones: " << graph.getNode(destinyIndex).dist << endl << endl;
    return path;

}

list<int> Menu::minSwaps(Graph &graph, vector<pair<Line, bool>> &lines, int originIndex, int destinyIndex) {

    graph.dijkstra_lineSwaps(originIndex);
    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines);
    cout << "\nNumber of minimum line swaps: " << graph.getNode(destinyIndex).dist << endl << endl;
    return path;

}

void Menu::locationStops() {

    //TODO test if they exist
    cout << "\nStarting stop code: ";
    cin >> codeStart;
    cout << "\nDestination stop code: ";
    cin >> codeEnd;

}

void Menu::locationCords() {

    //TODO test if given inputs are valid
    cout << "\nStarting coordinates (latitude, longitude): ";
    cin >> localStart;
    cout << "\nDestination coordinates (latitude, longitude): ";
    cin >> localEnd;
}


void Menu::settingsMenu() {

    askUseMLines();


    askFootDistance();

}

void Menu::start() {

    STATE state = location;

    while (true) {

        system(CLEAR);

        switch (state) {
            case location:
                state = locationMenu();
                break;
            case criteria:
                state = criteriaMenu();
                break;
            case close:
                return;
        }
    }

}

void Menu::resetMenuVars() {
    localStart = {}, localEnd = {};
    codeStart = "", codeEnd = "";
}


void Menu::showGeneratedPath(int pathCriteria) {


    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph(useMLines);
    vector<pair<Line, bool>> lines;
    list<int> path;

    int originIndex, destinyIndex;

    if (!codeStart.empty()) {
        originIndex = model.stopToIndex[codeStart];
        destinyIndex = model.stopToIndex[codeEnd];
    } else {
        originIndex = geoStartNode;
        destinyIndex = geoEndNode;
        graph.addGeoStartEndNode(localStart, localEnd, 500);
    }

    switch (pathCriteria) {
        case 1: // min stops
            path = minStops(graph, lines, originIndex, destinyIndex);
            break;
        case 2: // min distance
            path = minDistance(graph, lines, originIndex, destinyIndex);
            break;
        case 3: // min zones
            path = minZones(graph, lines, originIndex, destinyIndex);
            break;
        case 4: // min lines swaps
            path = minSwaps(graph, lines, originIndex, destinyIndex);
            break;
        default:
            break;
    }


    int i = 0;
    for (int &it: path) {
        cout << setw(8) << model.indexToStop[it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].first.lineDirectionName(lines[i].second) << " " << graph.getNode(it).stop.zone << endl;
        i++;
    }
    getchar();

}

void Menu::askFootDistance() {
    cout << "\n\nPlease provide the distance (in meters) you are\n"
            "willing to travel on foot to reach your destination\n"
            "(Current is " << footDistance << "m)\n";
    cout << "\n > ";

    int n;
    if (cin >> n) {
        footDistance = n;
        cout << "\nFoot distance was set to " << footDistance << " m\n";
    } else {
        cout << "Invalid input!\n";
    }

    cin.clear();
    cin.ignore(10000, '\n');
    getchar();

}

void Menu::askUseMLines() {
    char confirm;

    cout << "\nDo you want to include M lines (Y / N) ? ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
        useMLines = true;
    else {
        useMLines = false;
        cin.clear();
        cin.ignore(10000, '\n');
    }

}




