#ifndef CIRCUIT_H // include guard
#define CIRCUIT_H

#include <vector>
#include "components.hpp"

namespace myACCircuit{
    using namespace myComponents;

    class Circuit{
        private:
            std::vector<std::vector<Component*>> circuit_objects;
        public:
            Circuit();
            void Add_serial(Component* new_component);
            void Add_parallel(std::vector<Component*> new_components);
            std::vector<std::vector<Component*>> Get_objects();
    };

}

#endif /* !CIRCUIT_H */