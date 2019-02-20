//
// Created by michael on 20.02.19.
//

#ifndef OPTIMIZER_LINEARSEARCH_H
#define OPTIMIZER_LINEARSEARCH_H

#include "Optimizer.h"
#include "Function.h"

class LineSearch : Optimizer {
    double steps = 1000;

public:
    LineSearch(const Function& f);
    std::pair<Eigen::VectorXd, double> optimize(const Eigen::VectorXd &x0) const override;
};


#endif //OPTIMIZER_LINEARSEARCH_H
