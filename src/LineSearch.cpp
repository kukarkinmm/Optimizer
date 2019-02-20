//
// Created by michael on 20.02.19.
//

#include "LineSearch.h"

LineSearch::LineSearch(const Function &f) : Optimizer(f, std::make_shared<EmptyCriteria>(f)) {}

std::pair<Eigen::VectorXd, double> LineSearch::optimize(const Eigen::VectorXd &x0) const {
    Eigen::VectorXd x(x0.size());
    x(0) = objectiveFunction.getFunctionDomain().getBounds()[0].first;
    double minVal = objectiveFunction(x);
    Eigen::VectorXd minP(x);
    auto h = Eigen::VectorXd::Ones(x.size());
    double s = fabs(objectiveFunction.getFunctionDomain().getBounds()[0].second -
                    objectiveFunction.getFunctionDomain().getBounds()[0].first) / steps;
    x += h * s;
    while (x(0) < objectiveFunction.getFunctionDomain().getBounds()[0].second) {
        double currentVal = objectiveFunction(x);
        if (currentVal < minVal) {
            minVal = currentVal;
            minP = x;
        }
        x += h * s;
    }
    return std::pair<Eigen::VectorXd, double>(minP, minVal);
}
