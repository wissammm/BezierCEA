#include "BezierElevate.h"
// #include <Eigen/Dense>
// using Eigen::MatrixXd;

Bezier elevate(const Bezier& curve) {
    Bezier retElevate(curve.nbControlPoint() + 1);
    retElevate.controlPoint[0] = curve.controlPoint[0];

    Coord tmpPoint;
    for (size_t i = 1; i < (curve.nbControlPoint() + 1); i++) {
        tmpPoint = (((curve.nbControlPoint() - i) * curve.controlPoint[i]) + (curve.controlPoint[i - 1] * i)) /
                   (curve.nbControlPoint());
        retElevate.controlPoint[i] = tmpPoint;
    }
    retElevate.controlPoint[curve.nbControlPoint()] = curve.controlPoint[curve.degree()];
    return retElevate;
}

// Bezier lower(const Bezier& curve) {

//     size_t k = curve.nbControlPoint();
//     size_t n = k - 1;
//     Bezier  retLower(n);

//     if (k <= 3) {
//         return curve;
//     }

//     MatrixXd        M = MatrixXd::Zero(k, n);
//     Eigen::VectorXd Vx(k);
//     Eigen::VectorXd Vy(k);

//     for (size_t i = 0; i < k; ++i) {
//         if (i == 0)
//             M(i, 0) = 1;
//         else if (i == n)
//             M(i, i - 1) = 1;
//         else {
//             M(i, i - 1) = 1. / k;
//             M(i, i)     = 1. - M(i, i - 1);
//         }

//         Vx(i) = curve.controlPoint[i].x;
//         Vy(i) = curve.controlPoint[i].y;
//     }

//     auto Mt = M.transpose();
//     auto Mc = Mt * M;
//     auto Mi = Mc.inverse();

//     auto V = Mi * Mt;

//     auto nx = V * Vx;
//     auto ny = V * Vy;

//     for (size_t i = 0; i < n; ++i) {
//         printf("nx = %f, ny = %f\n", nx(i), ny(i));
//         retLower.controlPoint[i] = Coord({nx(i), ny(i)});
//     }

//     return retLower;
// }