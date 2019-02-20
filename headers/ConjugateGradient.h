//
// Created by michael on 20.02.19.
//

#ifndef OPTIMIZER_CONJUGATEGRADIENT_H
#define OPTIMIZER_CONJUGATEGRADIENT_H

#include "Optimizer.h"
#include "Function.h"
#include "Criteria.h"

class ConjugateGradient : public Optimizer {
    double betaFunction(const Eigen::VectorXd &currentGrad, const Eigen::VectorXd &nextGrad) const;
    double polakRibiereFunction(const Eigen::VectorXd &currentGrad, const Eigen::VectorXd &nextGrad) const;

public:
    ConjugateGradient(const Function& f, std::shared_ptr<Criteria> criterion_)
            : Optimizer(f, std::move(criterion_)) {};
    std::pair<Eigen::VectorXd, double> optimize(const Eigen::VectorXd &x0) const override;
};


#endif //OPTIMIZER_CONJUGATEGRADIENT_H
