/**
 * GDOPT - General Dynamic Optimizer
 * Copyright (C) 2024  Linus Langenkamp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef GDOPT_MESH_H
#define GDOPT_MESH_H

#include <utility>
#include <vector>

class Mesh {
public:
    Mesh(int intervals, double tf, std::vector<double> grid, std::vector<double> deltaT)
        : intervals(intervals), tf(tf), grid(std::move(grid)), deltaT(std::move(deltaT)) {
    }

    int intervals;
    double tf;
    std::vector<double> grid;
    std::vector<double> deltaT;

    static Mesh createEquidistantMesh(int intervals, double tf);
    void update(std::vector<int>& markedIntervals);
};

#endif  // GDOPT_MESH_H
