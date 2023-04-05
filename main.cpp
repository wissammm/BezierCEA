#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

struct Point
{
    double x;
    double y;
};

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

    Point res;
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

Point computeCasteljau(std::vector<std::vector<Point>> &tmp, double t)
{

    for (int j = 1; j < tmp[0].size(); j++)
    {
        for (int i = 0; i < tmp[0].size() - j; i++)
        {

            Point T;
            T.x = t * tmp[j - 1][i + 1].x + (1 - t) * tmp[j - 1][i].x;
            T.y = t * tmp[j - 1][i + 1].y + (1 - t) * tmp[j - 1][i].y;

            tmp[j][i] = T;
        }
    }

    return tmp[tmp[0].size() - 1][0];
}

void casteljau(const std::vector<Point> &tab, std::vector<Point> &curve, const int nb_points_on_curve)
{
    //: SOURCE: https://fr.wikipedia.org/wiki/Algorithme_de_Casteljau

    std::vector<std::vector<Point>> tmp(tab.size());
    std::vector<Point> ret;

    tmp[0] = tab;

    for (int i = 1; i < tab.size(); i++)
    {
        tmp[i].resize(tab.size() - i);
    }

    for (int i = 0; i <= nb_points_on_curve; i++)
    {
        curve.push_back(computeCasteljau(tmp, static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1.));
    }
}

std::vector<Point> randomPoint(int n, int y, int x)
{
    auto random_points = std::vector<Point>{};
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

    const auto points = randomPoint(10, 50, 50);
    auto curve_castel = std::vector<Point>{};
    auto curve_bez = std::vector<Point>{};
    int nb_points_on_curve = 30;

    clock_t time_req;

    time_req = clock();
    casteljau(points, curve_castel, nb_points_on_curve);
    time_req = clock() - time_req;
    cout << "Casteljau algorithm with " << nb_points_on_curve << " points compute. Time : " << time_req << endl;

    time_req = clock();
    bezier(points,curve_bez,nb_points_on_curve);
    time_req = clock() - time_req;
    cout << "Bezier algorithm with " << nb_points_on_curve << " points compute. Time : " << time_req << endl
         << endl;

    writeLinesVTK(points, "result/lines.vtk");
    writeLinesVTK(curve_castel, "result/curve_castel.vtk");
    writeLinesVTK(curve_castel, "result/curve_bezier.vtk");
}
