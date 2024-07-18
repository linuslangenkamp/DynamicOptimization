#include <iostream>
#include <memory>
#include <IpIpoptApplication.hpp>
#include "test_nlp.h"
#include "integrator.h"
#include "expression.h"
#include "constraint.h"
#include "mesh.h"
#include "problem.h"
#include "constants.h"
#include "gdop.h"
#include <IpSolveStatistics.hpp>
#include <IpTimingStatistics.hpp>
#include <IpIpoptData.hpp>
#include <iomanip>

using namespace Ipopt;

class Mayer : public Expression {
public:
    static std::unique_ptr<Mayer> create() {
        Adjacency adj{
                {0, 1},
                {},
                {}
        };
        return std::unique_ptr<Mayer>(new Mayer(std::move(adj)));
    }

    double eval(const double *x, const double *u, const double *p, double t) override {
        return x[0] * (0.23 + x[1] * x[1]);
    }

    std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
        return {std::vector<double>{0.23 + x[1] * x[1], 2 * x[1] * x[0]}, {}, {}};
    }
private:
    Mayer(Adjacency adj) : Expression(std::move(adj)) {
    }
};

class Lagrange : public Expression {
public:
    static std::unique_ptr<Lagrange> create() {
        Adjacency adj{
                {0},
                {0},
                {}
        };
        return std::unique_ptr<Lagrange>(new Lagrange(std::move(adj)));
    }

    double eval(const double *x, const double *u, const double *p, double t) override {
        return 0.5 * (x[0]*x[0] + u[0]*u[0]);
    }

    std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
        return {std::vector<double>{x[0]}, {u[0]}, {}};
    }
private:
    Lagrange(Adjacency adj) : Expression(std::move(adj)) {
    }
};

class F0 : public Expression {
public:
    static std::unique_ptr<F0> create() {
        Adjacency adj{
                {0},
                {0},
                {}
        };
        return std::unique_ptr<F0>(new F0(std::move(adj)));
    }

    double eval(const double *x, const double *u, const double *p, double t) override {
        return -x[0]*x[0]*x[0] + u[0];
    }

    std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
        return {std::vector<double>{-3*x[0]*x[0]}, {1}, {}};
    }
private:
    F0(Adjacency adj) : Expression(std::move(adj)) {
    }
};

class R0 : public Constraint {
public:
    static std::unique_ptr<R0> create() {
        Adjacency adj{
                {0},
                {},
                {}
        };
        return std::unique_ptr<R0>(new R0(std::move(adj), 0, 0));
    }

    double eval(const double *x, const double *u, const double *p, double t) override {
        return 1.5 - x[0];
    }

    std::array<std::vector<double>, 3> evalDiff(const double *x, const double *u, const double *p, double t) override {
        return {std::vector<double>{-1}, {}, {}};
    }
private:
    R0(Adjacency adj, double lb, double ub) : Constraint(std::move(adj), lb, ub) {
    }
};

int main() {
    Integrator rk = Integrator::radauIIA(IntegratorSteps::Steps3);
    Mesh mesh = Mesh::createEquidistantMesh(6000, 100);

    std::vector<std::unique_ptr<Expression>> F;
    F.push_back(F0::create());

    std::vector<std::unique_ptr<Constraint>> R;
    R.push_back(R0::create());

    Problem problem(
            1, 1, 0,
            {1},
            {MIN_DOUBLE}, {MAX_DOUBLE},
            {-10}, {10},
            {}, {},
            {},
            Lagrange::create(),
            std::move(F),
            {},
            std::move(R),
            {}
    );
    GDOP gdop(std::move(problem), mesh, rk, InitVars::CONST);
    SmartPtr<GDOP> DOP = &gdop;

    SmartPtr<IpoptApplication> app = IpoptApplicationFactory();
    app->Options()->SetNumericValue("tol", 1e-12);
    app->Options()->SetStringValue("hessian_approximation", "limited-memory");
    //app->Options()->SetStringValue("jacobian_approximation", "finite-difference-values");
    app->Options()->SetStringValue("mu_strategy", "adaptive");
    app->Options()->SetIntegerValue("print_level", 5);
    app->Options()->SetStringValue("timing_statistics", "yes");
    app->Options()->SetStringValue("output_file", "ipopt.out");

    ApplicationReturnStatus status;
    status = app->Initialize();
    if( status != Solve_Succeeded )
    {
        std::cout << std::endl << std::endl << "*** Error during initialization!" << std::endl;
        return (int) status;
    }

    status = app->OptimizeTNLP(DOP);

    return (int) status;
}
