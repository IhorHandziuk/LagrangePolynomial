#ifndef LAGRANGEPOLYNOMIAL_H
#define LAGRANGEPOLYNOMIAL_H

#include <vector>

using std::vector;
using std::pair;


class LagrangePolynomial {

public:

    bool addPoint(float x, float y);

    bool removePoint(float x, float y);

    void removeAllPoints();

    float getPolynomialAtPoint(float x);

    vector<float> getPolynomialCoefficients();

    vector<pair<float, float>> getPoints();

private:
    vector<pair<float, float>> points;
    vector<float> polynomialCoefficients;

    vector<pair<float, float>> swapPoints;
    vector<float> leftSideTerms;
    vector<float> rightSideTerms;
    float eps = 0.1;

    double distance(pair<float, float> p1, pair<float, float> p2);

    void swapping(int k);

    void solve(int len, double mult, int shift);
};


#endif //LAGRANGEPOLYNOMIAL_H
