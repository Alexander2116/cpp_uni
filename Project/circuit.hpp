#ifndef CIRCUIT_H // include guard
#define CIRCUIT_H

#include <vector>
#include "components.cpp"

namespace AC_Circuit{
    using namespace myComponents;

    class Circuit{
        private:
            std::vector<std::vector<Component*>> circuit_objects;
            Component a;
        public:
            Circuit();
            void Add_serial();
            void Add_parallel();
    };

}

#endif /* !CIRCUIT_H */