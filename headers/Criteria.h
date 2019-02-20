//
// Created by michael on 20.02.19.
//

#ifndef OPTIMIZER_CRITERION_H
#define OPTIMIZER_CRITERION_H

#include <vector>
#include <memory>
#include <Eigen/Core>

#include "Function.h"

class Criteria {
protected:
    const Function &f;

public:
    Criteria() = default;
    explicit Criteria(const Function &f_);
    virtual bool check(const Eigen::VectorXd &v) const = 0;
};

class MaxIterations : public Criteria {
    size_t max;
    mutable size_t i;

public:
    MaxIterations(size_t max_);
    bool check(const Eigen::VectorXd &) const override;
};

class Norm : public Criteria {
    double eps;

public:
    Norm(const Function &f_, double eps_);
    bool check(const Eigen::VectorXd &v) const override;
};

class Difference : public Criteria {
    double eps;
    mutable bool isFirst = true;
    mutable Eigen::VectorXd grad;

public:
    Difference(const Function &f_, double eps_);
    bool check(const Eigen::VectorXd &v) const override;
};

class Composition : public Criteria {
    std::vector<std::shared_ptr<Criteria>> criterion;

public:
    Composition(const Function &f_, std::vector<std::shared_ptr<Criteria>> crits);
    bool check(const Eigen::VectorXd &v) const override;
};

class EmptyCriteria : public Criteria {
public:
    explicit EmptyCriteria(const Function &f_);
    bool check([[maybe_unused]] const Eigen::VectorXd &v) const override { return true;}
};

#endif //OPTIMIZER_CRITERION_H
