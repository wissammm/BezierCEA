#include "Dump.h"

void writePointsVTK(const std::vector<Coord>& points, const std::filesystem::path& filePath) {
    std::ofstream out{filePath};

    out << "# vtk DataFile Version 2.0\n";
    out << "CGT vtk points output\n";
    out << "ASCII\n";
    out << "DATASET POLYDATA\n";

    out << "POINTS " << points.size() << " float\n";
    for (const auto& point : points)
        out << point.x << ' ' << point.y << " 0\n";

    out << "VERTICES " << points.size() << ' ' << points.size() + 1 << '\n';
    out << points.size();
    for (size_t i = 0, n = points.size(); i < n; ++i)
        out << ' ' << i;
    out << '\n';
}

void writeLinesVTK(const std::vector<Coord>& points, const std::filesystem::path& filePath) {
    std::ofstream out{filePath};

    out << "# vtk DataFile Version 2.0\n";
    out << "CGT vtk points output\n";
    out << "ASCII\n";
    out << "DATASET POLYDATA\n";

    out << "POINTS " << points.size() << " float\n";
    for (const auto& point : points)
        out << point.x << ' ' << point.y << " 0\n";

    out << "LINES 1 " << (points.size() + 1) << "\n";
    out << points.size();
    for (size_t i = 0, n = points.size(); i < n; ++i)
        out << ' ' << i;
    out << "\n";
}

void writeSegmentsVTK(const std::vector<Segment>& segments, const std::filesystem::path& filePath) {
    std::ofstream out{filePath};

    out << "# vtk DataFile Version 2.0\n";
    out << "CGT vtk points output\n";
    out << "ASCII\n";
    out << "DATASET POLYDATA\n";

    out << "POINTS " << segments.size() * 2 << " float\n";
    for (const auto& seg : segments) {
        out << seg.a.x << ' ' << seg.a.y << " 0\n";
        out << seg.b.x << ' ' << seg.b.y << " 0\n";
    }

    out << "LINES " << (segments.size()) << ' ' << 3 * segments.size() << "\n";
   
    for (size_t i = 0; i < (segments.size() * 2) - 1; i += 2) {
        out << 2 << ' ' << i << ' ' << i + 1 << '\n';
    }
    
}