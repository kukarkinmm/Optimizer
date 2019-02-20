//
// Created by michael on 20.02.19.
//

#include "Box.h"

Box::Box(std::vector<std::pair<double, double>> bounds_) : bounds(std::move(bounds_)) {}

bool Box::contains(const Eigen::VectorXd &p) const {
    for (size_t i = 0; i < bounds.size(); ++i)
        if (bounds[i].first < p(i) || bounds[i].second > p(i))
            return false;
    return true;
}

Box Box::operator&&(const Box &rhs) const {
    std::vector<std::pair<double, double>> newBounds(bounds.size());
    for (size_t i = 0; i < bounds.size(); ++i){
        newBounds[i].first = std::max(bounds[i].first, rhs.bounds[i].first);
        newBounds[i].second = std::min(bounds[i].second, rhs.bounds[i].second);
    }
    return Box(newBounds);
}

std::pair<double, double> Box::highestAlpha(const Eigen::VectorXd &x, const Eigen::VectorXd &p) const {
    double alpha = 10e9;
    for (size_t i = 0; i < bounds.size(); ++i) {
        if (p(i) == 0)
            continue;
        double h = (bounds[i].second - x(i)) / p(i);
        if (p(i) < 0)
            h = (bounds[i].first - x(i)) / p(i);
        alpha = std::min(alpha, h);
    }
    return std::make_pair(0, alpha);
}

const std::vector<std::pair<double, double>>& Box::getBounds() const {
    return bounds;
}

Eigen::VectorXd Box::projectionOnBounds(const Eigen::VectorXd &x, const Eigen::VectorXd &p) const {
    assert(x.size() == p.size());
    static double eps = 1e-6;
    Eigen::VectorXd mask(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        if (fabs(x(i) - bounds[i].first) > eps && fabs(x(i) - bounds[i].second) > eps) {
            mask(i) = 1;
        }
    }
    return mask.cwiseProduct(p);
}
