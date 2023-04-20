#include "Segment.h"
#include <algorithm>
#include <cmath>

double distance(Segment seg) {return distance(seg.a,seg.b);}

double distance(Coord A, Coord B) { return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)); }

double determinant(Coord a1, Coord a2, Coord b1, Coord b2) {
    return (b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x);
}

Coord getIntersectionPoint(Coord a1, Coord a2, Coord b1, Coord b2) {
    double ua           = determinant(a1, a2, b1, b2) / determinant(a2, a1, b1, b2);
    Coord  intersection = a1 + ua * (a2 - a1);
    return intersection;
}

Coord getIntersectionPoint(Segment seg1, Segment seg2) { return getIntersectionPoint(seg1.a, seg1.b, seg2.a, seg2.b); }

bool isOnSegment(Coord p, Coord a, Coord b) {
    if (p.x <= fmax(a.x, b.x) && p.x >= fmin(a.x, b.x) && p.y <= fmax(a.y, b.y) && p.y >= fmin(a.y, b.y)) {
        return true;
    }
    return false;
}

bool isOnBothSegments(Coord p, Coord a1, Coord a2, Coord b1, Coord b2) {
    if (isOnSegment(p, a1, a2) && isOnSegment(p, b1, b2)) {
        return true;
    }
    return false;
}

int orientation(Coord p, Coord q, Coord r) {
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0; // collinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool doIntersect(Coord p1, Coord q1, Coord p2, Coord q2) {
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && isOnSegment(p1, p2, q1))
        return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && isOnSegment(p1, q2, q1))
        return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && isOnSegment(p2, p1, q2))
        return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && isOnSegment(p2, q1, q2))
        return true;

    return false; // Doesn't fall in any of the above cases
}