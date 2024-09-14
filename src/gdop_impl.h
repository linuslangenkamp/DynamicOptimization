#ifndef IPOPT_DO_GDOP_IMPL_H
#define IPOPT_DO_GDOP_IMPL_H

#include <IpTNLP.hpp>

#include "gdop.h"
#include "integrator.h"
#include "mesh.h"
#include "problem.h"
#include "util.h"

using namespace Ipopt;

class GDOP : public TNLP {
public:
    GDOP(const std::shared_ptr<const Problem>& problem, Mesh& mesh, Integrator& rk, InitVars initVars);

    std::shared_ptr<const Problem> problem;
    Mesh mesh;
    Integrator rk;
    InitVars initVars;

    std::vector<double> optimum;  // optimal solution - variables
    double objective{};           // optimal solution - objective
    std::vector<double> x_cb;     // optimal solution (interpolated after refinement)

    std::string exportPath;
    std::string exportHessianPath;
    bool exportHessian = false;
    std::string exportJacobianPath;
    bool exportJacobian = false;

    const int offX = problem->sizeX;
    const int offU = problem->sizeU;
    const int offP = problem->sizeP;
    const int offXU = problem->sizeX + problem->sizeU;                                     // number of vars for one collocation grid point
    const int offXUBlock = (problem->sizeX + problem->sizeU) * rk.steps;                   // number of vars in one interval
    const int offXUTotal = (problem->sizeX + problem->sizeU) * rk.steps * mesh.intervals;  // first parameter variable
    const int numberVars = (problem->sizeX + problem->sizeU) * rk.steps * mesh.intervals + problem->sizeP;

    // block hessians as sparse map: (i,j) -> it, it-th index in COO format, (i,j) var indices
    // note that A, At, C only contain the lower triangle

    /**
    Hessian struct:
    vars   ...     xu    ...    p
      .    A    0   0   0   0   0
      .    0    A   0   0   0   0
     xu    .    .   .   .   .   .
      .    0    0   0   A   0   0
      .    0    0   0   0  At   0
      p    B    ...     B  Bt   C
    **/

    int lengthA = 0;                        // length of one A block
    std::vector<int> rowLengthBlockB = {};  // length of the i-th row of one B block

    // upper left corner of entire hessian: xu - xu block
    std::unordered_map<std::tuple<int, int>, int, n2hash> hessianA{};

    // lower right corner xu - xu block, might be different since M(.), r(.) are evaluated only at the last grid point
    std::unordered_map<std::tuple<int, int>, int, n2hash> hessianAt{};

    // lower left corner of entire hessian: xu-p block
    std::unordered_map<std::tuple<int, int>, int, n2hash> hessianB{};

    // lower right corner xu-p block, might be different since M(.), r(.) are evaluated only at the last grid point
    std::unordered_map<std::tuple<int, int>, int, n2hash> hessianBt{};

    // lower right corner of entire hessian, p-p block
    std::unordered_map<std::tuple<int, int>, int, n2hash> hessianC{};

    bool get_nlp_info(Index& n, Index& m, Index& nnz_jac_g, Index& nnz_h_lag, IndexStyleEnum& index_style) override;

    bool get_bounds_info(Index n, Number* x_l, Number* x_u, Index m, Number* g_l, Number* g_u) override;

    bool get_starting_point(Index n, bool init_x, Number* x, bool init_z, Number* z_L, Number* z_U, Index m, bool init_lambda, Number* lambda) override;

    bool get_scaling_parameters(Number& obj_scaling, bool& use_x_scaling, Index n, Number* x_scaling, bool& use_g_scaling, Index m, Number* g_scaling) override;

    bool eval_f(Index n, const Number* x, bool new_x, Number& obj_value) override;

    bool eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f) override;

    bool eval_g(Index n, const Number* x, bool new_x, Index m, Number* g) override;

    bool eval_jac_g(Index n, const Number* x, bool new_x, Index m, Index nele_jac, Index* iRow, Index* jCol, Number* values) override;

    bool eval_h(Index n, const Number* x, bool new_x, Number obj_factor, Index m, const Number* lambda, bool new_lambda, Index nele_hess, Index* iRow,
                Index* jCol, Number* values) override;

    void finalize_solution(SolverReturn status, Index n, const Number* x, const Number* z_L, const Number* z_U, Index m, const Number* g, const Number* lambda,
                           Number obj_value, const IpoptData* ip_data, IpoptCalculatedQuantities* ip_cq) override;

    void init_jac(Index& nnz_jac_g);

    int init_jac_sparsity(Index* iRow, Index* jCol);

    void get_jac_values(const Number* x, Number* values);

    void updateDenseHessianLFG(const Expression&, std::vector<std::vector<int>>&, std::vector<std::vector<int>>&, std::vector<std::vector<int>>&,
                               std::vector<std::vector<int>>&, std::vector<std::vector<int>>&) const;

    void evalHessianA_B(Number* values, const Number* x, Expression& expr, double factor, int xij, int uij, double tij, int i, int j);

    void evalHessianAt_Bt(Number* values, const Number* x, Expression& expr, double factor, int xij, int uij, double tij);

    void evalHessianC(Number* values, const Number* x, ParamExpression& expr, double factor);

    void updateDenseHessianMR(const Expression&, std::vector<std::vector<int>>&, std::vector<std::vector<int>>&, std::vector<std::vector<int>>&) const;

    static void updateDenseHessianA(const ParamExpression&, std::vector<std::vector<int>>&);

    void createSparseHessian(std::vector<std::vector<int>>&, std::vector<std::vector<int>>&, std::vector<std::vector<int>>&, std::vector<std::vector<int>>&,
                             std::vector<std::vector<int>>&, Index&);

    void init_h(Index& nnz_h_lag);

    void init_h_sparsity(Index* iRow, Index* jCol);

    int get_h_values(const Number* x, Number* values, Number obj_factor, const Number* lambda);

    void exportOptimum(const std::string&) const;
};

#endif  // IPOPT_DO_GDOP_IMPL_H
