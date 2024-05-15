#pragma once
std::vector<double> newton(std::function<double(double)> f,
    std::function<double(double)> df, std::function<double(double)> d2f,
    double p0, double delta, double eps, double max1);