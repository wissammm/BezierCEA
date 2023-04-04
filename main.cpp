#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

struct Point
{
    float x;
    float y;
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

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    const auto points = std::vector<Point>{{0., 0.}, {1., 0.}, {2., 1.}};
    writeLinesVTK(points, "C:/Temp/lines.vtk");
}

int binomial(int n, int k)
{
    if (k == 0 || k == n)
        return 1;
    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}

Point bezier(std::vector<Point> *tab, int nb_points, float t)
{
    Point res;
    res.x = 0.f;
    res.y = 0.f;
    //: COMMENT:Wissam: Optimisable si on utilise un itérateur et non un for
    for (int i = 0; i < nb_points; i++)
    {
        res.x += binomial(nb_points, i) * (float)(pow((double)(1 - t), (double)(nb_points - i)) * pow((double)t, (double)i)) * tab->at(i).x;
        res.y += binomial(nb_points, i) * (float)(pow((double)(1 - t), (double)(nb_points - i)) * pow((double)t, (double)i)) * tab->at(i).y;
    }
    return res;
}

Point casteljau(std::vector<Point> &tab, int nb_points, float t)
{
    //:SOURCE: https://fr.wikipedia.org/wiki/Algorithme_de_Casteljau
    Point res;
    res.x = 0.f;
    res.y = 0.f;
    std::vector<std::vector<Point>> tmp(nb_points);

    for (int i = 0; i < nb_points; i++)
    {
        tmp[i].resize(nb_points - i);
    }

    for (int j = 1; j < nb_points; j++)
    {
        for (int i = 0; i < nb_points - j; i++)
        {
            Point act;
            // act.x = t* 0;
        }
    }
    return {};
}