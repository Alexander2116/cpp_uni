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

        protected:
            // these functions shouldn't be accessed publicly because they have no self-standing meaning
            complex calc_serial(std::vector<complex> impedancies); // gives impedance for serial components
            std::vector<complex> calc_parallel(vvc circuit_objects_list); // gives impedance for parallel components
        public:
            Circuit();
            ~Circuit();
            void Add_serial(Component* new_component);
            void Add_parallel(std::vector<Component*> new_components);
            vvc Get_objects();
            double GetEMF();
            complex GetImpedance();
            double GetPhaseDifference();
    };

}

#endif /* !CIRCUIT_H */