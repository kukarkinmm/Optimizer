//
// Created by michael on 20.02.19.
//

#include "Criteria.h"

Criteria::Criteria(const Function &f_) : f(f_) {}

MaxIterations::MaxIterations(size_t max_) : Criteria(Function()), max(max_), i(0) {}

bool MaxIterations::check(const Eigen::VectorXd &) const {
    return i++ < max;
}

Norm::Norm(const Function &f_, double eps_) : Criteria(f_), eps(eps_) {}

bool Norm::check(const Eigen::VectorXd &v) const {
    return f.grad(v).norm() >= eps;
}

Difference::Difference(const Function &f_, double eps_)
        : Criteria(f_), eps(eps_), grad(2) {}

bool Difference::check(const Eigen::VectorXd &v) const {
    Eigen::VectorXd tempGrad = grad;
    if (isFirst) {
        grad = f.grad(v);
        isFirst = false;
        return true;
    }
    grad = f.grad(v);
    return (tempGrad - grad).norm() >= eps;
}

Composition::Composition(const Function &f_, std::vector<std::shared_ptr<Criteria>> crits)
        : Criteria(f_), criterion(std::move(crits)) {}

bool Composition::check(const Eigen::VectorXd &v) const {
    for (const auto &crit : criterion)
        if (crit->check(v))
            return false;
    return true;
}

EmptyCriteria::EmptyCriteria(const Function &f_) : Criteria(f_) {}
