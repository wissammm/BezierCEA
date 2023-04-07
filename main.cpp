#include <chrono>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <ctime>
#include <array>
using namespace std;

// class Timer
// {
// public:
//     Timer(std::string message)
//         : message(std::move(message)), tStart(std::chrono::high_resolution_clock::now())
//     {
//     }

//     ~Timer()
//     {
//         const auto tEnd = std::chrono::high_resolution_clock::now();
//         const auto duration = std::chrono::duration<double, std::milli>(tEnd - tStart).count();
//         cout << message << duration << endl;
//     }

// private:
//     std::string message;
//     std::chrono::steady_clock::time_point tStart;
// };

struct Point
{
    double x;
    double y;
};

struct Segment
{
    Point a;
    Point b;
};

Point subPoint(const Point p1, const Point p2)
{
    return Point({p1.x - p2.x, p1.y - p2.y});
}

Point subPoint(const Point p1, const Point p2, int factor)
{
    return Point({factor * (p1.x - p2.x), factor * (p1.y - p2.y)});
}

using Bezier = std::vector<Point>;
using Buffer = std::vector<std::vector<Point>>;
using Normals = std::vector<Segment>;
using Tangents = std::vector<Segment>;

// Point evaluate(const Bezier& curve, double t)
// {

// }

// Point evaluate(const Bezier& curve, double t, Buffer& buffer)
// {

// }

Bezier derivate(const Bezier &curve)
{

    //: SOURCE: https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-der.html
    //: COMMENT: pas sur que ca marche ...
    Bezier C1 = curve;
    Bezier C2 = curve;
    Bezier retDeriv(curve.size() - 1);

    for (size_t i = 1; i < curve.size(); i++)
    {
        retDeriv[i - 1] = subPoint(curve.at(i - 1),curve.at(i), curve.size() - 1);
    }
    return retDeriv;
}

Point computeTangent(Point deriv_time_t)
{
    //: SOURCE: https://pomax.github.io/bezierinfo/#derivatives
    double m = sqrt(deriv_time_t.x * deriv_time_t.x +
                    deriv_time_t.y * deriv_time_t.y);
    return Point({deriv_time_t.x / m, deriv_time_t.y / m});
}

Point computeNormal(Point tengent)
{
    //: SOURCE: https://pomax.github.io/bezierinfo/#derivatives
    double m = sqrt(tengent.x * tengent.x +
                    tengent.y * tengent.y);

    return Point({-tengent.y / m, tengent.x / m});
}

void writePointsVTK(const std::vector<Point> &points, const std::string &filePath)
{
    std::ofstream out{filePath};

    out << "# vtk DataFile Version 2.0\n";
    out << "CGT vtk points output\n";
    out << "ASCII\n";
    out << "DATASET POLYDATA\n";

    out << "POINTS " << points.size() << " float\n";
    for (const auto &point : points)
        out << point.x << ' ' << point.y << " 0\n";

    out << "VERTICES " << points.size() << ' ' << points.size() + 1 << '\n';
    out << points.size();
    for (size_t i = 0, n = points.size(); i < n; ++i)
        out << ' ' << i;
    out << '\n';
}

void writeLinesVTK(const std::vector<Point> &points, const std::string &filePath)
{
    std::ofstream out{filePath};

    out << "# vtk DataFile Version 2.0\n";
    out << "CGT vtk points output\n";
    out << "ASCII\n";
    out << "DATASET POLYDATA\n";

    out << "POINTS " << points.size() << " float\n";
    for (const auto &point : points)
        out << point.x << ' ' << point.y << " 0\n";

    out << "LINES 1 " << (points.size() + 1) << "\n";
    out << points.size();
    for (size_t i = 0, n = points.size(); i < n; ++i)
        out << ' ' << i;
    out << "\n";
}

void writeSemgentsVTK(const std::vector<Segment> &segments, const std::string &filePath)
{
    std::ofstream out{filePath};

    out << "# vtk DataFile Version 2.0\n";
    out << "CGT vtk points output\n";
    out << "ASCII\n";
    out << "DATASET POLYDATA\n";

    out << "POINTS " << segments.size() *2 << " float\n";
    for (const auto &seg : segments)
    {
        out << seg.a.x << ' ' << seg.a.y << " 0\n";
        out << seg.b.x << ' ' << seg.b.y << " 0\n";
    }

    out << "LINES " << (segments.size()) <<' '<< 3 * segments.size()<< "\n";
    // out << points.size();
    // for (size_t i = 0, n = points.size(); i < n; ++i)
    //     out << ' ' << i;
    for (size_t i = 0; i < (segments.size()*2)-1; i+=2)
    {
        out << 2 << ' '<< i << ' ' << i + 1 << '\n';
    }
    // out << "\n";
}

int binomial(int n, int k)
{
    if (k == 0 || k == n)
        return 1;
    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}

double bernstein(int m, int i, double u)
{
    return binomial(m, i) * pow(u, i) * pow((1 - u), m - i);
}

Point computeBezier(const std::vector<Point> &tab, double t)
{

    Point res{0., 0.};
    for (int i = 0; i < tab.size(); i++)
    {
        res.x += bernstein(tab.size() - 1, i, t) * tab[i].x;
        res.y += bernstein(tab.size() - 1, i, t) * tab[i].y;
    }
    return res;
}

void bezier(const std::vector<Point> &tab, std::vector<Point> &curve, const int nb_points_on_curve)
{
    for (int i = 0; i <= nb_points_on_curve; i++)
    {
        curve.push_back(computeBezier(tab, static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1.));
    }
}

Point computeCasteljau(Buffer &tmp, double t)
{
    const auto n = tmp[0].size();
    for (size_t j = 1; j < n; ++j)
    {
        for (size_t i = 0; i < n - j; ++i)
        {
            const auto &A = tmp[j - 1][i + 1];
            const auto &B = tmp[j - 1][i];
            auto &C = tmp[j][i];

            C.x = t * (A.x - B.x) + B.x;
            C.y = t * (A.y - B.y) + B.y;
        }
    }

    return tmp[n - 1][0];
}

Buffer createBuffer(const Bezier &tab)
{
    Buffer tmp(tab.size());
    tmp[0] = tab;

    for (int i = 1; i < tab.size(); i++)
    {
        tmp[i].resize(tab.size() - i);
    }
    return tmp;
}

void casteljau(const Bezier &tab, std::vector<Point> &curve, const int nb_points_on_curve)
{
    //: SOURCE: https://fr.wikipedia.org/wiki/Algorithme_de_Casteljau

    Buffer bufferCurve = createBuffer(tab);

    for (int i = 0; i <= nb_points_on_curve; i++)
    {
        curve.push_back(computeCasteljau(bufferCurve, static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1.));
    }
}

void normalsAndTangents(const Bezier &tab, std::vector<Point> &curve, const int nb_points_on_curve,
                        Tangents &tangents, Normals &normals, double factor)
{

    Buffer bufferCurve = createBuffer(tab);
    Bezier deriv = derivate(tab);
    Buffer bufferDeriv = createBuffer(deriv);

    for (int i = 0; i <= nb_points_on_curve; i++)
    {
        double time = static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1.;

        Point curvePoint = computeCasteljau(bufferCurve, time);

        curve.push_back(curvePoint);
        Point deriv_point = computeCasteljau(bufferDeriv, time);
        Point tangent = computeTangent(deriv_point);
        Point normal = computeNormal(tangent);

        tangents.push_back(Segment({subPoint(tangent, curvePoint, factor), curvePoint}));
        normals.push_back(Segment({subPoint(normal, curvePoint, factor), curvePoint}));
    }
}

std::array<Bezier, 2> decompose(const Bezier &curve, double t)
{
    // ... TODO
    uint16_t curve_size = curve.size();
    Buffer tmp(curve_size);

    tmp[0] = curve;

    for (int i = 1; i < curve_size; ++i)
    {
        tmp[i].resize(curve_size - i);
    }
    computeCasteljau(tmp, t);

    //: SOURCE: https://www.youtube.com/watch?v=lPJo1jayLdc
    Bezier part1, part2(curve_size);

    for (uint16_t i = 0; i < curve_size; ++i)
    {
        part1.push_back(tmp[i][0]);
        part2[curve_size - i - 1] = (tmp[i][curve_size - i - 1]);
    }
    std::array<Bezier, 2> ret = {part1, part2};
    return ret;
}

Bezier randomPoint(int n, int y, int x)
{
    Bezier random_points;
    for (int i = 0; i < n; i++)
    {

        random_points.push_back(Point({static_cast<double>(rand() % x),
                                       static_cast<double>(rand() % y)}));
    }
    return random_points;
}

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    const auto points = randomPoint(5, 50, 50);

    Bezier curve_castel;
    Bezier curve_bez;
    int nb_points_on_curve = 20;

    // {
    //     // auto timer = Timer{ "Casteljau algorithm with " + std::to_string(nb_points_on_curve) + " points compute. Time : " };
    //     for (int i = 0; i < 100; ++i)
    //         casteljau(points, curve_castel, nb_points_on_curve);
    //     writeLinesVTK(curve_castel, "result/curve_castel.vtk");
    // }

    // {
    //     // auto timer = Timer{ "Bezier algorithm with " + std::to_string(nb_points_on_curve) + " points compute. Time : " };
    //     for (int i = 0; i < 100; ++i)
    //         bezier(points, curve_bez, nb_points_on_curve);
    //     writeLinesVTK(curve_bez, "result/curve_bezier.vtk");
    // }

    // {
    //     std::cout << "Hello, before decompose!\n";
    //     Bezier a, b;
    //     auto arrayDecompose = decompose(points, 0.5);
    //     a = arrayDecompose[0];
    //     b = arrayDecompose[1];

    //     auto a_curve = std::vector<Point>{};
    //     auto b_curve = std::vector<Point>{};

    //     casteljau(a, a_curve, 30);
    //     casteljau(b, b_curve, 30);
    //     writeLinesVTK(a_curve, "result/a_curve.vtk");
    //     writeLinesVTK(b_curve, "result/b_curve.vtk");
    //     writeLinesVTK(a, "result/a_point.vtk");
    //     writeLinesVTK(b, "result/b_point.vtk");
    // }

    // {
    //     Bezier derivOf = derivate(points);
    //     auto curv_deriv = std::vector<Point>{};
    //     casteljau(derivOf, curv_deriv, nb_points_on_curve);
    //     writeLinesVTK(curv_deriv, "result/curv_deriv.vtk");
    //     writeLinesVTK(derivOf, "result/point_deriv.vtk");
    // }

    // {
    //     // auto timer = Timer{ "Casteljau algorithm with " + std::to_string(nb_points_on_curve) + " points compute. Time : " };

        // casteljau(points, curve_castel, nb_points_on_curve);
        // writeLinesVTK(curve_castel, "result/curve_castel.vtk");
    // }

    {
        auto curv_normals = std::vector<Point>{};
        Tangents tangents;
        Normals normals;
        normalsAndTangents(points,curv_normals,nb_points_on_curve,tangents,normals,0.2);
        writeSemgentsVTK(normals,"result/normals.vtk");
        writeLinesVTK(curv_normals, "result/curv_normals.vtk");
    }

    writeLinesVTK(points, "result/lines.vtk");
}