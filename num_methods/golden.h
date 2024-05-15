#pragma once
std::vector<double> golden(std::function<double(double)> f, double a, double b, double delta, double eps);