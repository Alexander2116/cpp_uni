#ifndef CIRCUIT_H // include guard
#define CIRCUIT_H

#include <vector>
#include "components.hpp"
#include "complex.hpp"

namespace myACCircuit{
    using namespace myComponents;
    using namespace myComplex;

    class Circuit{
        private:
            std::vector<std::vector<Component*>> circuit_objects;
            complex impedance;

        protected:
            // these functions should be accessed publicly because they have no self-standing meaning
            complex calc_serial(std::vector<complex> impedancies); // gives impedance for serial components
            std::vector<complex> calc_parallel(std::vector<std::vector<Component*>> circuit_objects_list); // gives impedance for parallel components
        public:
            Circuit();
            void Add_serial(Component* new_component);
            void Add_parallel(std::vector<Component*> new_components);
            std::vector<std::vector<Component*>> Get_objects();
            double GetEMF();
            complex GetImpedance();
    };

}

#endif /* !CIRCUIT_H */