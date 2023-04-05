#ifndef INTERFACE_H // include guard
#define INTERFACE_H

#include <vector>
#include "components.hpp"
#include "circuit.hpp"
#include "complex.hpp"
#include "matrix.hpp"

namespace myInterface{
    using namespace myComponents;
    using namespace myACCircuit;
    using namespace myComplex;
    using namespace myMatrix;


    class Interface{
        private:
            std::vector<std::vector<Component*>> circuit_objects;
            int x_size_window;
            int y_size_window;
        public:
            Interface();
            void Display();
            void Update();
    };

}

#endif /* !CIRCUIT_H */