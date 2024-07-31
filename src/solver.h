#ifndef IPOPT_DO_SOLVER_H
#define IPOPT_DO_SOLVER_H

#include "gdop.h"

enum class LinearSolver {
    MUMPS,
    MA27,
    MA57,
    MA77,
    MA86,
    MA97,
    PARDISO
};

enum class MeshAlgorithm {
    NONE,
    BASIC,
    L2_BOUNDARY_NORM
};

class Solver {
public:
    Solver(const SmartPtr<GDOP>& gdop, int maxMeshIterations, LinearSolver linearSolver, MeshAlgorithm meshAlgorithm);

    SmartPtr<GDOP> gdop;
    LinearSolver linearSolver;
    MeshAlgorithm meshAlgorithm;
    int meshIteration = 0;
    const int maxMeshIterations;
    double tolerance = 1e-14;
    std::vector<double> cbValues;           // starting values after refinement

    // important methods
    int solve();
    std::vector<int> detect();
    void refine(std::vector<int>&);
    void finalizeOptimization();

    // detection methods
    std::vector<int> basicStrategy(double) const;
    std::vector<int> l2BoundaryNorm() const;

    // additional / optional flags, printouts, ...
    std::vector<double> objectiveHistory;   // history of objectives in refinement process
    std::string exportOptimumPath;
    int initialIntervals;
    std::chrono::_V2::system_clock::time_point solveStartTime;
    void postOptimization();
    bool exportOptimum = false;
    void printObjectiveHistory();
    void printMeshStats();
    void setExportOptimumPath(const std::string&);
    void initSolvingProcess();
    void setTolerance(double d);
};

#endif //IPOPT_DO_SOLVER_H
