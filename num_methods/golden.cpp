#include <iostream>
#include <vector>
#include <functional>

std::vector<double> golden(std::function<double(double)> f, double a, double b, double delta, double eps) {
    const double r1 = (std::sqrt(5) - 1) / 2;
    const double r2 = r1 * r1;
    double h = b - a;
    double ya = f(a);
    double yb = f(b);
    double c = a + r2 * h;
    double d = a + r1 * h;
    double yc = f(c);
    double yd = f(d);
    int k = 1;

    while (std::abs(yb - ya) > eps || h > delta) {
        k++;
        if (yc < yd) {
            b = d;
            yb = yd;
            d = c;
            yd = yc;
            h = b - a;
            c = a + r2 * h;
            yc = f(c);
        }
        else {
            a = c;
            ya = yc;
            c = d;
            yc = yd;
            h = b - a;
            d = a + r1 * h;
            yd = f(d);
        }
    }

    double dp = std::abs(b - a);
    double dy = std::abs(yb - ya);
    double p = a;
    double yp = ya;

    if (yb < ya) {
        p = b;
        yp = yb;
    }

    std::vector<double> S = { p, yp, double(k), dp, dy };

    return S;
}