//
// Created by michael on 20.02.19.
//

#ifndef OPTIMIZER_OPTIMIZER_H
#define OPTIMIZER_OPTIMIZER_H

#include <functional>
#include <vector>
#include <memory>
#include <Eigen/Core>

#include "Function.h"
#include "Criteria.h"

class Optimizer {
protected:
    Function objectiveFunction;
    std::shared_ptr<Criteria> criterion;

public:
    Optimizer(const Function& f, std::shared_ptr<Criteria> criterion_)
            : objectiveFunction(f), criterion(std::move(criterion_)) {};
    virtual std::pair<Eigen::VectorXd, double> optimize(const Eigen::VectorXd &x0) const = 0;
};

#endif //OPTIMIZER_OPTIMIZER_H
