//
// Created by Linus on 14.07.2024.
//
#include "problem.h"

Problem::Problem(int sizeX, int sizeU, int sizeP,
                 std::vector<double> startX, std::vector<double> lbX, std::vector<double> ubX,
                 std::vector<double> lbU, std::vector<double> ubU,
                 std::vector<double> lbP, std::vector<double> ubP,
                 std::unique_ptr<Expression> M, std::unique_ptr<Expression> L,
                 std::vector<std::unique_ptr<Constraint>> F,
                 std::vector<std::unique_ptr<Constraint>> G,
                 std::vector<std::unique_ptr<Constraint>> R,
                 std::vector<std::unique_ptr<Constraint>> A)
        : sizeX(sizeX), sizeU(sizeU), sizeP(sizeP),
          startX(std::move(startX)), lbX(std::move(lbX)), ubX(std::move(ubX)),
          lbU(std::move(lbU)), ubU(std::move(ubU)),
          lbP(std::move(lbP)), ubP(std::move(ubP)),
          M(std::move(M)), L(std::move(L)), F(std::move(F)), G(std::move(G)), R(std::move(R)), A(std::move(A)) {
}
