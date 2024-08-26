#include "chrono/core/ChMatrix.h"
#include <math.h>
#include <stdlib.h>
#include <chrono/functions/ChFunctionConstAcc.h>
#include "AccelerationQuatrature.h"
#include "chrono/core/ChQuadrature.h"

int main()
{

    chrono::ChMatrixNM<double,2,2> matrix1 {{1.5,2.1},{std::sqrt(3),9.444}};
    chrono::ChMatrixNM<double,2,2> matrix2 {{3.6,1.0},{77.223,1.656}};

    chrono::ChMatrixNM<double,2,2> multiplied_result;

    multiplied_result = matrix1 * matrix2;

    for (size_t i = 0; i < 2; i++)
    {
        for (size_t q = 0; q < 2; q++)
        {
            std::cout << multiplied_result(i,q) << "\n\n";
        }
        
    }
    std::cout << "-----------------------------------------------------------" << std::endl;

    std::cout << multiplied_result << std::endl;

    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"  << std::endl;
    chrono::ChRowVectorN<double,25> some_list;
    
    chrono::ChFunctionConstAcc accel;
    accel.SetDuration(10.0);
    accel.SetFirstAccelerationEnd(0.25);
    accel.SetSecondAccelerationStart(0.34);
    accel.SetDisplacement(85);

    double output = accel.GetVal(9.0);

    for (double weird_counter = 0.0; weird_counter < 10.0; weird_counter += .01)
    {
        std::cout << weird_counter << ", " << accel.GetVal(weird_counter) << "\n";
    }

    AccelerationQuatrature a;

    double q_result;

    chrono::ChQuadrature::Integrate1D<double>(q_result,a,0.0,5.0,6);

    std::cout << "The Integration resulted in " << q_result << " So yay for that";

    return 0;
}