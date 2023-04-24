#include "Segment.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <array>

#define DELTA 0.1

double norm(Coord a) { return dot(a, a); }

double abs(Coord a) { return sqrt(norm(a)); }

double proj(Coord a, Coord b) { return dot(a, b) / abs(b); }

Coord lineLineIntersection(Coord A, Coord B, Coord C, Coord D) {
    // Line AB represented as a1x + b1y = c1
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = a1 * (A.x) + b1 * (A.y);

    // Line CD represented as a2x + b2y = c2
    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2 * (C.x) + b2 * (C.y);

    double det = determinant(a1, a2, b1, b2);

    if (det == 0) {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        std::cerr << "SEGMENTS PARALLELES, OBJET NULL" << std::endl;
        return Coord({__DBL_MAX__, __DBL_MAX__});
    } else {
        double x = (b2 * c1 - b1 * c2) / det;
        double y = (a1 * c2 - a2 * c1) / det;
        return Coord({x, y});
    }
}

Segment vector(Coord A1, Coord A2, Coord B1, Coord B2) { return Segment({B1 - A1, B2 - A2}); }

double cross(Coord a, Coord b) { return a.x * b.y - a.y * b.x; }

double angle(Coord a, Coord b) { return acos(dot(a, b) / abs(a) / abs(b)); }

double dot(Coord a, Coord b) { return a.x * b.x + a.y * b.y; }

double distance(Segment seg) { return distance(seg.a, seg.b); }

double distance(Coord A, Coord B) { return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)); }

double determinant(double a1, double a2, double b1, double b2) { return a1 * b2 - a2 * b1; }

Coord lineLineIntersection(Segment seg1, Segment seg2) { return lineLineIntersection(seg1.a, seg1.b, seg2.a, seg2.b); }

bool onSegment(Coord p, Coord q, Coord r) {
    if (q.x - DELTA <= std::max(p.x, r.x) && q.x + DELTA >= std::min(p.x, r.x) && q.y - DELTA <= std::max(p.y, r.y) &&
        q.y + DELTA >= std::min(p.y, r.y))
        return true;

    return false;
}

int orientation(Coord p, Coord q, Coord r) {
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val <= DELTA && val >= -DELTA)
        return 0; // collinear

    return (val > 0) ? 1 : 2;
}

bool doIntersect(Coord p1, Coord q1, Coord p2, Coord q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1))
        return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1))
        return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2))
        return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2))
        return true;

    return false;
}

bool isOnBothSegments(Coord p, Coord a1, Coord a2, Coord b1, Coord b2) {
    if (onSegment(a1,p, a2) && onSegment(b1,p, b2)) {
        printf("DEBUG: Is on segment \n");
        return true;
    }
    return false;
}
