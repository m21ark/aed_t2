#ifndef AED_T2_DISTANCECALC_H
#define AED_T2_DISTANCECALC_H

#include <cmath>

using namespace std;

static double distanceCalc(double lat1, double lon1, double lat2, double lon2) {

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}


#endif //AED_T2_DISTANCECALC_H