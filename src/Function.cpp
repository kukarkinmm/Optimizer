//
// Created by michael on 20.02.19.
//

#include "Function.h"

Function::Function() : objectiveFunction(std::function<double(const Eigen::VectorXd&)>()),
                       gradient(std::function<Eigen::VectorXd(const Eigen::VectorXd&)>()), functionDomain(Box()) {}

Function::Function(std::function<double(const Eigen::VectorXd &)> func, Box domain)
        : objectiveFunction(std::move(func)),
          gradient([&func=this->objectiveFunction, h=step](const Eigen::VectorXd &p) -> Eigen::VectorXd {
              Eigen::VectorXd result(p.size());
              for (size_t i = 0; i < p.size(); ++i) {
                  Eigen::VectorXd step = Eigen::VectorXd::Zero(p.size());
                  step(i) = h;
                  result(i) = (func(p + step) - func(p - step)) / (2 * h);
              }
              return result;
          }), functionDomain(std::move(domain)) {}

Function::Function(std::function<double(const Eigen::VectorXd &)> func,
                   std::function<Eigen::VectorXd(const Eigen::VectorXd &)> grad, Box domain)
                   : objectiveFunction(std::move(func)), gradient(std::move(grad)), functionDomain(std::move(domain)) {}

Eigen::VectorXd Function::grad(const Eigen::VectorXd &p) const {
    return gradient(p);
}

double Function::operator()(const Eigen::VectorXd &p) const {
    return objectiveFunction(p);
}

const Box& Function::getFunctionDomain() const {
    return functionDomain;
}
