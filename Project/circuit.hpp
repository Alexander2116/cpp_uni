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
            vvc circuit_objects; // whole circuit structure
            complex _impedance; // Thevenin impedance of the circuit
            double _efm;
            static int _id;
            double _frequency{1};
            bool _is_combined = false;
        protected:
            // these functions shouldn't be accessed publicly because they have no self-standing meaning
            complex calc_serial(std::vector<complex> impedancies); // gives impedance for serial components
            std::vector<complex> calc_parallel(vvc circuit_objects_list); // gives impedance for parallel components
        public:
            Circuit(); // not combined in default
            Circuit(Circuit a, Circuit b, bool serial); // allows to create a combined circuit
            ~Circuit();
            void Set_Frequency(double freq);
            double Get_Frequency();
            void Add_serial(Component* new_component);
            void Add_parallel(std::vector<Component*> new_components);
            vvc Get_objects();
            void Update_objects(vvc new_objects);
            double GetEMF();
            complex GetImpedance();
            void SetImpedance(complex impedance); // Used when creating a combined circuit
            double GetPhaseDifference();
            void Info();
    };

}

#endif /* !CIRCUIT_H */