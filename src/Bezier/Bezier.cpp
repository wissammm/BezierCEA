#include "Bezier.h"


int binomial(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}

double bernstein(int m, int i, double u) { return binomial(m, i) * pow(u, i) * pow((1 - u), m - i); }


Bezier elevate(const Bezier& curve) {
    Bezier retElevate(curve.size() + 1);
    retElevate[0] = curve[0];

    Coord tmpPoint;
    for (size_t i = 1; i < (curve.size() + 1); i++) {
        tmpPoint      = (((curve.size() - i) * curve[i]) + (curve[i - 1] * i)) / (curve.size());
        retElevate[i] = tmpPoint;
    }
    retElevate[curve.size()] = curve[curve.size() - 1];
    return retElevate;
}


Bezier lower(const Bezier& curve) {

    size_t k = curve.size();
    size_t n = k - 1;
    Bezier retLower(n);

    if (k <= 3) {
        return curve;
    }

    MatrixXd        M = MatrixXd::Zero(k, n);
    Eigen::VectorXd Vx(k);
    Eigen::VectorXd Vy(k);

    for (size_t i = 0; i < k; ++i) {
        if (i == 0)
            M(i, 0) = 1;
        else if (i == n)
            M(i, i - 1) = 1;
        else {
            M(i, i - 1) = 1. / k;
            M(i, i)     = 1. - M(i, i - 1);
        }

        Vx(i) = curve[i].x;
        Vy(i) = curve[i].y;
    }

    auto Mt = M.transpose();
    auto Mc = Mt * M;
    auto Mi = Mc.inverse();

    auto V = Mi * Mt;

    auto nx = V * Vx;
    auto ny = V * Vy;

    for (size_t i = 0; i < n; ++i) {
        printf("nx = %f, ny = %f\n", nx(i), ny(i));
        retLower[i] = Coord({nx(i), ny(i)});
    }

    return retLower;
}

Bezier derivate(const Bezier& curve) {

    //: SOURCE: https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-der.html
    //: COMMENT: pas sur que ca marche ...
    Bezier retDeriv(curve.size() - 1);

    for (size_t i = 1; i < curve.size(); i++) {
        retDeriv[i - 1] = (curve[i - 1] - curve[i]) * static_cast<double>(curve.size() - 1);
    }
    return retDeriv;
}

Coord computeTangent(Coord deriv_time_t) {
    //: SOURCE: https://pomax.github.io/bezierinfo/#derivatives
    double m = sqrt(deriv_time_t.x * deriv_time_t.x + deriv_time_t.y * deriv_time_t.y);
    return Coord({deriv_time_t.x / m, deriv_time_t.y / m});
}

Coord computeNormal(Coord tengent) {
    //: SOURCE: https://pomax.github.io/bezierinfo/#derivatives
    double m = sqrt(tengent.x * tengent.x + tengent.y * tengent.y);

    return Coord({-tengent.y / m, tengent.x / m});
}


Coord evalBezier(const Bezier& bezier, double t) {
    const auto n = bezier.size() - 1;

    Coord res{0., 0.};
    for (int i = 0; i <= n; i++) {
        res.x += bernstein(static_cast<int>(n), i, t) * bezier[i].x;
        res.y += bernstein(static_cast<int>(n), i, t) * bezier[i].y;
    }
    return res;
}

std::vector<Coord> bezier(const std::vector<Coord>& tab, size_t nb_points_on_curve) {
    auto curve = std::vector<Coord>();
    curve.reserve(nb_points_on_curve);
    for (size_t i = 0; i <= nb_points_on_curve; i++) {
        curve.push_back(evalBezier(tab, static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1.));
    }
    return curve;
}

Coord evalCasteljau(const Bezier& bezier, double t, Buffer& buffer) {
    //: SOURCE: https://fr.wikipedia.org/wiki/Algorithme_de_Casteljau
    const auto n = bezier.size() - 1;

    buffer[0] = bezier;
    for (size_t j = 1; j <= n; ++j) {
        for (size_t i = 0; i <= n - j; ++i) {
            const auto& A = buffer[j - 1][i + 1];
            const auto& B = buffer[j - 1][i];
            auto&       C = buffer[j][i];

            C.x = t * (A.x - B.x) + B.x;
            C.y = t * (A.y - B.y) + B.y;
        }
    }

    return buffer[n][0];
}

Buffer createBuffer(size_t degree) {
    Buffer buffer(degree + 1);
    for (size_t i = 0; i <= degree; i++) {
        buffer[i].resize(degree + 1 - i);
    }
    return buffer;
}

std::vector<Coord> casteljau(const Bezier& bezier, size_t nb_points_on_curve) {
    Buffer bufferCurve = createBuffer(bezier.size() - 1);

    auto curve = std::vector<Coord>();
    curve.reserve(nb_points_on_curve);
    for (size_t i = 0; i <= nb_points_on_curve; i++) {
        curve.push_back(
            evalCasteljau(bezier, static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1., bufferCurve));
    }
    return curve;
}



CurveNormalsAndTangents normalsAndTangents(const Bezier& bezier, size_t nb_points_on_curve, double factor) {

    Buffer buffer = createBuffer(bezier.size() - 1);
    Bezier deriv  = derivate(bezier);

    auto result = CurveNormalsAndTangents{};
    for (int i = 0; i <= nb_points_on_curve; i++) {
        const double time = static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1.;

        const Coord curvePoint = evalCasteljau(bezier, time, buffer);
        result.curve.push_back(curvePoint);

        const Coord deriv_point = evalCasteljau(deriv, time, buffer);
        const Coord tangent     = computeTangent(deriv_point);
        const Coord normal      = computeNormal(tangent);

        result.tangents.push_back(Segment({curvePoint, curvePoint + tangent * factor}));
        result.normals.push_back(Segment({curvePoint, curvePoint + normal * factor}));
    }
    return result;
}

std::array<Bezier, 2> decompose(const Bezier& curve, double t) {
    // ... TODO
    size_t curve_size = curve.size();

    auto buffer = createBuffer(curve.size() - 1);

    evalCasteljau(curve, t, buffer);

    //: SOURCE: https://www.youtube.com/watch?v=lPJo1jayLdc
    Bezier part1, part2(curve_size);

    for (size_t i = 0; i < curve_size; ++i) {
        part1.push_back(buffer[i][0]);
        part2[curve_size - i - 1] = (buffer[i][curve_size - i - 1]);
    }
    std::array<Bezier, 2> ret = {part1, part2};
    return ret;
}

Bezier randomPoint(int n, int y, int x) {
    Bezier random_points;
    for (int i = 0; i < n; i++) {

        random_points.push_back(Coord({static_cast<double>(rand() % x), static_cast<double>(rand() % y)}));
    }
    return random_points;
}
