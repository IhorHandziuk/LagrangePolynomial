#include <cmath>
#include "LagrangePolynomial.h"
#include <exception>
#include <stdexcept>

bool LagrangePolynomial::addPoint(float x, float y) {
    std::pair<float, float> newPoint = std::pair<float, float>(x, y);
    for (std::pair<float, float> point : points) {
        if (distance(point, newPoint) < eps) {
            return false;
        }
    }
    points.push_back(newPoint);
    return true;
}

bool LagrangePolynomial::removePoint(float x, float y) {
    std::pair<float, float> newPoint = std::pair<float, float>(x, y);
    for (auto it = points.begin(); it != points.end(); it++) {
        if (distance(*it, newPoint) < eps) {
            points.erase(it);
            return true;
        }
    }
    return false;
}

void LagrangePolynomial::removeAllPoints() {
    points.clear();
}

float LagrangePolynomial::getPolynomialAtPoint(float x) {
    if (points.size() < 2) {
        throw std::logic_error("At least 2 points should be present at the set");
    }
    float L = 0;
    float F = 1;
    for (int i = 0; i < points.size(); i++) {
        swapping(i);
        for (int j = 1; j < points.size(); j++) {
            F *= (x - swapPoints[j].first) / (points[i].first - swapPoints[j].first);
        }
        L += points[i].second * F;
        F = 1;
    }
    return L;
}


double LagrangePolynomial::distance(std::pair<float, float> p1, std::pair<float, float> p2) {
    return sqrt(pow((p1.first - p2.first), 2) + pow((p1.first - p2.first), 2));
}

std::vector<float> LagrangePolynomial::getPolynomialCoefficients() {
    if (points.size() < 2) {
        throw std::logic_error("At least 2 points should be present at the set");
    }
    polynomialCoefficients.clear();
    for (int i = 0; i < points.size(); i++) {
        swapping(i);
        for (int j = 1; j < points.size(); j++) {
            rightSideTerms[j] = 1 / (points[i].first - swapPoints[j].first);
            leftSideTerms[j] = (-1) * swapPoints[j].first / (points[i].first - swapPoints[j].first);
        }
        leftSideTerms[0] = points[i].second;
        solve(points.size(), 1, 0);
    }
    return polynomialCoefficients;
}

void LagrangePolynomial::swapping(int k) {
    swapPoints.resize(points.size());
    swapPoints[0].first = points[k].first;
    int l = 1, m = 1;
    while (l <= points.size() - 1) {
        if (l - 1 == k) m++;
        swapPoints[l].first = points[m - 1].first;
        l++;
        m++;
    }
}

void LagrangePolynomial::solve(int len, double mult, int shift) {
    if (len > 1) {
        solve(len - 1, mult * leftSideTerms[len - 1], shift + 1);
        solve(len - 1, mult * rightSideTerms[len - 1], shift);
    } else {
        polynomialCoefficients[shift + 1] += leftSideTerms[0] * mult;
        polynomialCoefficients[shift] += rightSideTerms[0] * mult;
    }
}

vector<pair<float, float>> LagrangePolynomial::getPoints() {
    return points;
}
