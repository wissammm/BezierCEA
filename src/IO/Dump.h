#pragma once

#include "Bezier/Bezier.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

void writeLinesVTK(const std::vector<Coord>& points, const std::filesystem::path& filePath);
void writePointsVTK(const std::vector<Coord>& points, const std::filesystem::path& filePath);
void writeSegmentsVTK(const std::vector<Segment>& segments, const std::filesystem::path& filePath);