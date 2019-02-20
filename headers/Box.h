//
// Created by michael on 20.02.19.
//

#ifndef OPTIMIZER_BOX_H
#define OPTIMIZER_BOX_H

#include <algorithm>
#include <vector>
#include <Eigen/Core>

class Box {
    std::vector<std::pair<double, double>> bounds;

public:
    Box() = default;
    explicit Box(std::vector<std::pair<double, double>> bounds_);

    bool contains(const Eigen::VectorXd &p) const;
    Box operator&&(const Box &rhs) const;
    std::pair<double, double> highestAlpha(const Eigen::VectorXd &x, const Eigen::VectorXd &p) const;
    const std::vector<std::pair<double, double>>& getBounds() const;
    Eigen::VectorXd projectionOnBounds(const Eigen::VectorXd &x, const Eigen::VectorXd &p) const;
};

#endif //OPTIMIZER_BOX_H
