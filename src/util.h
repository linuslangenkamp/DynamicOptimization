#ifndef IPOPT_DO_UTIL_H
#define IPOPT_DO_UTIL_H

#include <vector>
#include <cstdlib>
#include <tuple>
#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <set>

template<typename T>
inline int sz(const std::vector<T>& vec) {
    return int(vec.size());
}

struct n2hash {
    std::size_t operator()(const std::tuple<int, int>& v) const {
        auto const [t1, t2] = v;
        auto h1 = std::hash<int>{}(t1);
        auto h2 = std::hash<int>{}(t2);
        return h1 ^ (h2 << 1);
    }
};

inline int fullSum(const std::vector<std::vector<int>>& matrix) {
    int sum = 0;
    for (const auto& row : matrix) {
        for (const auto val : row) {
            sum += val;
        }
    }
    return sum;
}

inline void exportSparsity(const int* iRow, const int* jCol, const int L, const std::tuple<int, int> dim, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    auto const [dimRow, dimCol] = dim;
    outFile << "dimRow" << "," << "dimCol" << "\n";
    outFile << dimRow << "," << dimCol << "\n";

    outFile << "row" << "," << "col" << "\n";
    for (int i = 0; i < L; i++) {
        outFile << iRow[i] << "," << jCol[i] << "\n";
    }
    outFile.close();
}

inline std::string double2Str(double x) {
    std::stringstream strStream;
    strStream << std::fixed << std::setprecision(19) << x;
    return strStream.str();
}

inline double calculateMean(const std::vector<double>& vec) {
    double sum = 0;
    for (double num : vec) {
        sum += num;
    }
    return sum / sz(vec);
}

inline double calculateStdDev(const std::vector<double>& vec, double mean) {
    double sum = 0;
    for (double num : vec) {
        sum += (num - mean) * (num - mean);
    }
    return std::sqrt(sum / sz(vec));
}

#endif //IPOPT_DO_UTIL_H
