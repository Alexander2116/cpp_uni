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
            vvc current_circuit_objects;
            StringMatrix display_data;
            std::vector<Circuit> _circuits;
            int x_size_window{1};
            int y_size_window{1};
            bool _exit_request{false};
            void EditCir(Circuit* circuit);
            void AddComponent(); // Inside Circuit related
            void EditComponent(); // Inside Circuit related
            Component* CreateComponent();
        public:
            Interface();
            // Interface related functions
            void WelcomeMessage();
            void MainMenu();
            void AddCircuit();
            void EditCircuit();
            void ShowAllComponents();
            void CombineCircuits();

            // Graphics related functions
            void Display();
            void UpdateGraphic();
            void UpdateObjects(vvc add_circuit_objects);
    };

    // Clears terminal. Depending of OS different command is called
    void Clear();

}

#endif /* !CIRCUIT_H */