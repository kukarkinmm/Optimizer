//
// Created by michael on 20.02.19.
//

#ifndef OPTIMIZER_FUNCTION_H
#define OPTIMIZER_FUNCTION_H

#include <functional>
#include <Eigen/Core>

#include "Box.h"

class Function {
protected:
    std::function<double(const Eigen::VectorXd&)> objectiveFunction;
    std::function<Eigen::VectorXd(const Eigen::VectorXd&)> gradient;
    Box functionDomain;

    constexpr static double step = 0.005;

public:
    Function();
    Function(std::function<double(const Eigen::VectorXd &)> func, Box domain);
    Function(std::function<double(const Eigen::VectorXd &)> func, std::function<Eigen::VectorXd(const Eigen::VectorXd &)> grad, Box domain);

    const Box& getFunctionDomain() const;
    virtual Eigen::VectorXd grad(const Eigen::VectorXd &p) const;
    virtual double operator()(const Eigen::VectorXd &p) const;
};


#endif //OPTIMIZER_FUNCTION_H