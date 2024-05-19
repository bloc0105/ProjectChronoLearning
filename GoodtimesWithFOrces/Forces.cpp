#include "chrono/physics/ChSystemNSC.h" // Include Chrono NSC physics system
#include "chrono/physics/ChBody.h"      // Include Chrono body
#include <fstream>                      // Include for file I/O
#include <iostream>                     // Include for console I/O

int main() {
    // Create a Chrono shared pointer to a body
    auto the_body = chrono_types::make_shared<chrono::ChBody>();
    // Set the initial position of the body to the origin (0, 0, 0)
    the_body->SetPos(chrono::ChVector3d(0, 0, 0));

    // Set the mass of the body to 1.0
    the_body->SetMass(1.0);

    // Define the simulation timestep
    double timestep = 0.01;

    // Define a constant force to be applied to the body (in the z-direction)
    chrono::ChVector3d the_force(0, 0, 2);

    // Create a Chrono NSC physics system
    auto physics_system = chrono::ChSystemNSC();
    // Set the gravitational acceleration to zero
    physics_system.SetGravitationalAcceleration(0.0);

    // Define the start and stop times for force application
    double force_start_tme = 15.0;
    double force_stop_tme = 16.0;

    // Add the body to the physics system
    physics_system.Add(the_body);

    // Open an output file stream for writing
    std::ofstream stream_out;
    stream_out.open("whatever.csv");

    // Loop over simulation time
    for (double sim_time = 0.0; sim_time <= 20.0; sim_time += timestep) {
        // Apply force if within the specified time interval
        if (sim_time >= force_start_tme && sim_time <= force_stop_tme) {
            the_body->AccumulateForce(the_force, the_body->GetPos(), false);
        }

        // Perform a single timestep in the physics system
        physics_system.DoStepDynamics(timestep);
        
        // Empty accumulators to clear applied forces/momentums
        the_body->EmptyAccumulators();

        // Print simulation time and body position to the console
        std::cout << sim_time << ", " << the_body->GetPos()[2] << std::endl;

        // Write simulation time and body position to the output file
        stream_out << sim_time << ", " << the_body->GetPos()[2] << std::endl;
    }

    // Close the output file stream
    stream_out.close();

    // Return 0 to indicate successful execution
    return 0;
}
