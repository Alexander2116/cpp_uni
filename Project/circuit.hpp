/*============================================================
** UTF-8, Win32
**
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: 
**
** Classes: Circuit: Circuit(), Circuit(Circuit, Circuit, bool)
**
** Comments: 
**
** Date:  15 April 2023
**
===========================================================*/

#ifndef CIRCUIT_H // include guard
#define CIRCUIT_H

#include <vector>
#include "components.hpp"
#include "complex.hpp"

namespace myACCircuit{
    using namespace myComponents;
    using namespace myComplex;
    typedef std::vector<std::vector<Component*>> vvc; // vvc - vector vector component

    class Circuit{
        private:
            vvc _circuit_objects; // whole circuit structure
            complex _impedance; // Thevenin impedance of the circuit
            static int _id;
            double _frequency{1};
            bool _is_combined = false;
            // these functions shouldn't be accessed publicly because they have no self-standing meaning
            std::vector<complex> calc_parallel(vvc circuit_objects_list); // gives impedance for parallel components
            complex calc_serial(std::vector<complex> impedancies); // gives impedance for serial components
        
        public:
            Circuit(); // not combined in default
            Circuit(Circuit a, Circuit b, bool serial); // allows to create a combined circuit
            ~Circuit();
            void SetFrequency(double freq);
            double GetFrequency();
            void AddSerial(Component* new_component); // Add a single component in the next block
            void AddParallel(std::vector<Component*> new_components); // Add a set of components in the next block
            vvc GetObjects(); // Returns stored objects (_circuit_objects)
            void UpdateObjects(vvc new_objects); // updates _circuit_objects
            complex GetImpedance(); // returns _impedance
            void SetImpedance(complex impedance); // Used when creating a combined circuit
            double GetPhaseDifference(); // Gets the phase difference of the current impedance (does not update impedance beforehand)
            void Info();
    };

}

#endif /* !CIRCUIT_H */