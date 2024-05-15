#include <iostream>
#include <vector>
#include <functional>
std::vector<double> quadmin(std::function<double(double)> f, double a, double b, double delta, double eps) {
    double p0 = a;
    int maxj = 20;
    int maxk = 30;
    double big = 1e7;
    double err = 1;
    double cond = 0;
    double h = 1;
    int k = 1;

    double f1, p1, p2, pmin, y0, y1, y2, ymin, d, hmin, h0, h1, h2, e0, e1, e2, p, dp, yp, dy;

    if (abs(p0) > 1e4) h = abs(p0) / big;
    while (k < maxk && err > eps && cond != 5) {
        f1 = (f(p0 + eps) - f(p0 - eps)) / 2*eps;
        if (f1 > 0) h = -abs(h);
        p1 = p0 + h;
        p2 = p0 + 2 * h;
        pmin = p0;
        y0 = f(p0);
        y1 = f(p1);
        y2 = f(p2);
        ymin = y0;
        cond = 0;
        int j = 0;
        while (j < maxj && abs(h) > delta && cond == 0) {
            if (y0 <= y1) {
                p2 = p1;
                y2 = y1;
                h = h / 2;
                p1 = p0 + h;
                y1 = f(p1);
            }
            else
                if (y2 < y1) {
                    p1 = p2;
                    y1 = y2;
                    h = 2 * h;
                    p2 = p0 + 2 * h;
                    y2 = f(p2);
                }
                else
                    cond = -1;
            j++;
            if (abs(h) > big || abs(p0) > big) cond = 5;
        }
        if (cond == 5) {
            pmin = p1;
            ymin = f(p1);
        }
        else {
            d = 4 * y1 - 2 * y0 - 2 * y2;
            if (d < 0)
                hmin = h * (4 * y1 - 3 * y0 - y2) / d;
            else {
                hmin = h / 3;
                cond = 4;
            }
            pmin = p0 + hmin;
            ymin = f(pmin);
            h = abs(h);
            h0 = abs(hmin);
            h1 = abs(hmin - h);
            h2 = abs(hmin - 2 * h);

            if (h0 < h) h = h0;
            if (h1 < h) h = h1;
            if (h2 < h) h = h2;
            if (h0 == 0) h = hmin;
            if (h < delta) cond = 1;
            if (abs(h) > big || abs(pmin) > big) cond = 5;
            
            e0 = abs(y0 - ymin);
            e1 = abs(y1 - ymin);
            e2 = abs(y2 - ymin);

            if (e0 != 0 && e0 < err) err = e0;
            if (e1 != 0 && e1 < err) err = e1;
            if (e2 != 0 && e2 < err) err = e2;
            if (e0 != 0 && e1 == 0 && e2 == 0) err = 0;
            if (err < eps) cond = 2;
            p0 = pmin;
            k++;
        }
        if (cond == 2 && h < delta) cond = 3;
    }
    p = p0;
    dp = h;
    yp = f(p);
    dy = err;

    std::vector<double> res = { p, yp, dp, dy, double(k) };

    return res;
}