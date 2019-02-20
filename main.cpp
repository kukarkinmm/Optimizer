#include <iostream>
#include <cmath>

#include "ConjugateGradient.h"

int main() {
    Function foo([](Eigen::VectorXd v) {
        return std::sin(v[0]) * std::cos(v[0]) - std::pow(v[0], 5) + std::exp(v[1]);
    }, Box(std::vector<std::pair<double, double>>({{-2, 2}, {-1, 3}})));
    ConjugateGradient optimizer(foo, std::make_shared<MaxIterations>(100));
    Eigen::VectorXd x(2);
    x(0) = 1;
    x(1) = 0;
    std::pair<Eigen::VectorXd, double> res = optimizer.optimize(x);
    std::cout << res.first << "\n" << res.second << "\n";
    return 0;
}