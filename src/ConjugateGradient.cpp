//
// Created by michael on 20.02.19.
//

#include "ConjugateGradient.h"
#include "Function.h"
#include "LineSearch.h"

std::pair<Eigen::VectorXd, double> ConjugateGradient::optimize(const Eigen::VectorXd &x0) const {
    Eigen::VectorXd x(x0);
    Eigen::VectorXd p = -objectiveFunction.grad(x);
    while (criterion->check(x)) {
        p = objectiveFunction.getFunctionDomain().projectionOnBounds(x, p);
        auto [alpha, arg] = LineSearch(Function([*this, x, p](const Eigen::VectorXd &a) {
                                                    return this->objectiveFunction(x + p * a(0));},
                                                Box({objectiveFunction.getFunctionDomain().highestAlpha(x, p)}))).optimize(Eigen::VectorXd(1));
        Eigen::VectorXd currentGrad = objectiveFunction.grad(x);
        x = x + p * alpha(0);
        Eigen::VectorXd nextGrad = objectiveFunction.grad(x);
        p = -nextGrad + p * betaFunction(currentGrad, nextGrad);
    }
    return std::pair<Eigen::VectorXd, double>(x, objectiveFunction(x));
}

//Fletcher-Reeves algorithm
double ConjugateGradient::betaFunction(const Eigen::VectorXd &currentGrad, const Eigen::VectorXd &nextGrad) const {
    double den = currentGrad.dot(currentGrad);
    if (den < 1e-6)
        return 0;
    return nextGrad.dot(nextGrad) / den;
}

//Polak-Ribiere algorithm
double ConjugateGradient::polakRibiereFunction(const Eigen::VectorXd &currentGrad, const Eigen::VectorXd &nextGrad) const {
    return nextGrad.dot(nextGrad - currentGrad) / currentGrad.dot(currentGrad);
}