#include "chrono/core/ChQuadrature.h"


class AccelerationQuatrature : public chrono::ChIntegrand1D<double>
{
private:
    /* data */
public:
    AccelerationQuatrature(/* args */);
    ~AccelerationQuatrature();
    void Evaluate(double & result, const double x);
};