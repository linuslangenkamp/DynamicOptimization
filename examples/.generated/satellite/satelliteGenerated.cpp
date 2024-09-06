
// CODEGEN FOR MODEL "satellite"

// includes
#define _USE_MATH_DEFINES
#include "satelliteGeneratedParams.h"
#include <cmath>
#include <string>
#include "constants.h"
#include <problem.h>
#include "integrator.h"
#include "mesh.h"
#include "gdop.h"
#include "solver.h"


// runtime parameters and global constants


// mayer term
class Mayersatellite : public Expression {
public:
	static std::unique_ptr<Mayersatellite> create() {
		Adjacency adj{{0, 1, 2, 3, 4, 5, 6}, {}, {}};
		AdjacencyDiff adjDiff{{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}, {}, {}, {}, {}, {}};
		return std::unique_ptr<Mayersatellite>(new Mayersatellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return pow(x[4], 2) + pow(x[5], 2) + pow(x[6], 2) + pow(-0.70106 + x[0], 2) + pow(-0.56098 + x[2], 2) + pow(-0.43047 + x[3], 2) + pow(-0.0923 + x[1], 2);
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{2*(-0.70106 + x[0]), 2*(-0.0923 + x[1]), 2*(-0.56098 + x[2]), 2*(-0.43047 + x[3]), 2*x[4], 2*x[5], 2*x[6]}, {}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{2, 2, 2, 2, 2, 2, 2}, {}, {}, {}, {}, {}};
	}
private:
	Mayersatellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


// lagrange term
class Lagrangesatellite : public Expression {
public:
	static std::unique_ptr<Lagrangesatellite> create() {
		Adjacency adj{{}, {0, 1, 2}, {}};
		AdjacencyDiff adjDiff{{}, {}, {{0, 0}, {1, 1}, {2, 2}}, {}, {}, {}};
		return std::unique_ptr<Lagrangesatellite>(new Lagrangesatellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return 0.5*(pow(u[0], 2) + pow(u[1], 2) + pow(u[2], 2));
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{}, {1.0*u[0], 1.0*u[1], 1.0*u[2]}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{}, {}, {1.0, 1.0, 1.0}, {}, {}, {}};
	}
private:
	Lagrangesatellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


// dynamic constraints
class F0satellite : public Expression {
public:
	static std::unique_ptr<F0satellite> create() {
		Adjacency adj{{1, 2, 3, 4, 5, 6}, {}, {}};
		AdjacencyDiff adjDiff{{{4, 3}, {5, 2}, {6, 1}}, {}, {}, {}, {}, {}};
		return std::unique_ptr<F0satellite>(new F0satellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return 0.5*(x[3]*x[4] - x[5]*x[2] + x[6]*x[1]);
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{0.5*x[6], -0.5*x[5], 0.5*x[4], 0.5*x[3], -0.5*x[2], 0.5*x[1]}, {}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{0.5, -0.5, 0.5}, {}, {}, {}, {}, {}};
	}
private:
	F0satellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


class F1satellite : public Expression {
public:
	static std::unique_ptr<F1satellite> create() {
		Adjacency adj{{0, 2, 3, 4, 5, 6}, {}, {}};
		AdjacencyDiff adjDiff{{{4, 2}, {5, 3}, {6, 0}}, {}, {}, {}, {}, {}};
		return std::unique_ptr<F1satellite>(new F1satellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return 0.5*(-x[0]*x[6] + x[3]*x[5] + x[4]*x[2]);
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{-0.5*x[6], 0.5*x[4], 0.5*x[5], 0.5*x[2], 0.5*x[3], -0.5*x[0]}, {}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{0.5, 0.5, -0.5}, {}, {}, {}, {}, {}};
	}
private:
	F1satellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


class F2satellite : public Expression {
public:
	static std::unique_ptr<F2satellite> create() {
		Adjacency adj{{0, 1, 3, 4, 5, 6}, {}, {}};
		AdjacencyDiff adjDiff{{{4, 1}, {5, 0}, {6, 3}}, {}, {}, {}, {}, {}};
		return std::unique_ptr<F2satellite>(new F2satellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return 0.5*(x[0]*x[5] + x[3]*x[6] - x[4]*x[1]);
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{0.5*x[5], -0.5*x[4], 0.5*x[6], -0.5*x[1], 0.5*x[0], 0.5*x[3]}, {}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{-0.5, 0.5, 0.5}, {}, {}, {}, {}, {}};
	}
private:
	F2satellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


class F3satellite : public Expression {
public:
	static std::unique_ptr<F3satellite> create() {
		Adjacency adj{{0, 1, 2, 4, 5, 6}, {}, {}};
		AdjacencyDiff adjDiff{{{4, 0}, {5, 1}, {6, 2}}, {}, {}, {}, {}, {}};
		return std::unique_ptr<F3satellite>(new F3satellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return -0.5*(x[0]*x[4] + x[5]*x[1] + x[6]*x[2]);
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{-0.5*x[4], -0.5*x[5], -0.5*x[6], -0.5*x[0], -0.5*x[1], -0.5*x[2]}, {}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{-0.5, -0.5, -0.5}, {}, {}, {}, {}, {}};
	}
private:
	F3satellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


class F4satellite : public Expression {
public:
	static std::unique_ptr<F4satellite> create() {
		Adjacency adj{{5, 6}, {0}, {}};
		AdjacencyDiff adjDiff{{{6, 5}}, {}, {}, {}, {}, {}};
		return std::unique_ptr<F4satellite>(new F4satellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return (1.0/1000000.0)*(550*u[0] - 83334*x[6]*x[5]);
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{(-41667.0/500000.0)*x[6], (-41667.0/500000.0)*x[5]}, {11.0/20000.0}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{-41667.0/500000.0}, {}, {}, {}, {}, {}};
	}
private:
	F4satellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


class F5satellite : public Expression {
public:
	static std::unique_ptr<F5satellite> create() {
		Adjacency adj{{4, 6}, {1}, {}};
		AdjacencyDiff adjDiff{{{6, 4}}, {}, {}, {}, {}, {}};
		return std::unique_ptr<F5satellite>(new F5satellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return (1.0/833333.0)*(50*u[1] - 83333*x[6]*x[4]);
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{(-83333.0/833333.0)*x[6], (-83333.0/833333.0)*x[4]}, {50.0/833333.0}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{-83333.0/833333.0}, {}, {}, {}, {}, {}};
	}
private:
	F5satellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


class F6satellite : public Expression {
public:
	static std::unique_ptr<F6satellite> create() {
		Adjacency adj{{4, 5}, {2}, {}};
		AdjacencyDiff adjDiff{{{5, 4}}, {}, {}, {}, {}, {}};
		return std::unique_ptr<F6satellite>(new F6satellite(std::move(adj), std::move(adjDiff)));
	}

	double eval(const double *x, const double *u, const double *p, double t) override {
		return (1.0/916667.0)*(550*u[2] + 166667*x[5]*x[4]);
	}

	std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{(166667.0/916667.0)*x[5], (166667.0/916667.0)*x[4]}, {550.0/916667.0}, {}};
	}

	std::array<std::vector<double>, 6> evalDiff2(const double *x, const double *u, const double *p, double t) override {
		return {std::vector<double>{166667.0/916667.0}, {}, {}, {}, {}, {}};
	}
private:
	F6satellite(Adjacency adj, AdjacencyDiff adjDiff) : Expression(std::move(adj), std::move(adjDiff)) {}
};


std::vector<double> uInitialGuess(double t) {
	 return {0, 0, 0};
};

Problem createProblem_satellite() {

    std::vector<std::unique_ptr<Expression>> F;
    F.push_back(F0satellite::create());
    F.push_back(F1satellite::create());
    F.push_back(F2satellite::create());
    F.push_back(F3satellite::create());
    F.push_back(F4satellite::create());
    F.push_back(F5satellite::create());
    F.push_back(F6satellite::create());
    
    std::vector<std::unique_ptr<Constraint>> G;
    
    
    std::vector<std::unique_ptr<Constraint>> R;
    
    
    std::vector<std::unique_ptr<ParamConstraint>> A;
    

    Problem problem(
            7, 3, 0,  // #vars
            {0, 0, 0, 1, 0.01, 0.005, 0.001},  // x0
            {MINUS_INFINITY, MINUS_INFINITY, MINUS_INFINITY, MINUS_INFINITY, MINUS_INFINITY, MINUS_INFINITY, MINUS_INFINITY},  // lb x
            {PLUS_INFINITY, PLUS_INFINITY, PLUS_INFINITY, PLUS_INFINITY, PLUS_INFINITY, PLUS_INFINITY, PLUS_INFINITY},  // ub x
            &uInitialGuess,  // u0 initial guesses for optimization
            {MINUS_INFINITY, MINUS_INFINITY, MINUS_INFINITY},  // lb u
            {PLUS_INFINITY, PLUS_INFINITY, PLUS_INFINITY},  // ub u
            {},  // p0 initial guesses for optimization
            {},  // lb p
            {},  // ub p
            Mayersatellite::create(),
            Lagrangesatellite::create(),
            std::move(F),
            std::move(G),
            std::move(R),
            std::move(A),
            "satellite");
            
    #ifdef INITIAL_STATES_PATH
    problem.initialStatesPath = INITIAL_STATES_PATH "/initialValues.csv";
    #endif
    
    return problem;
};

int main() {
    auto problem = std::make_shared<const Problem>(createProblem_satellite());
    InitVars initVars = INIT_VARS;
    Integrator rk = Integrator::radauIIA(RADAU_INTEGRATOR);
    Mesh mesh = Mesh::createEquidistantMesh(INTERVALS, FINAL_TIME);
    LinearSolver linearSolver = LINEAR_SOLVER;
    MeshAlgorithm meshAlgorithm = MESH_ALGORITHM;
    int meshIterations = MESH_ITERATIONS;

    Solver solver = Solver(create_gdop(problem, mesh, rk, initVars), meshIterations, linearSolver, meshAlgorithm);

    // set solver flags
    #ifdef EXPORT_OPTIMUM_PATH
    solver.setExportOptimumPath(EXPORT_OPTIMUM_PATH);
    #endif
    
    #ifdef EXPORT_HESSIAN_PATH
    solver.setExportHessianPath(EXPORT_HESSIAN_PATH);
    #endif
    
    #ifdef EXPORT_JACOBIAN_PATH
    solver.setExportJacobianPath(EXPORT_JACOBIAN_PATH);
    #endif
    
    #ifdef TOLERANCE
    solver.setTolerance(TOLERANCE);
    #endif
    
    // set solver mesh parameters
    #ifdef LEVEL
    solver.setMeshParameter("level", LEVEL);
    #endif
    
    #ifdef C_TOL
    solver.setMeshParameter("ctol", C_TOL);
    #endif
    
    #ifdef SIGMA
    solver.setMeshParameter("sigma", SIGMA);
    #endif
    
    // optimize
    int status = solver.solve();
    return status;
}        
        