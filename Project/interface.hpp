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
            Circuit* _current_circuit; // Used to edit circuit inside EditCir() and AddComponent()
            vvc _current_circuit_objects;
            StringMatrix display_data;
            std::vector<Circuit> _circuits;
            int x_size_window{1};
            int y_size_window{1};
            bool _exit_request{false};
            void EditCir(Circuit* circuit); // Edits given circuit (has interface)
            void AddComponent(); // Inside Circuit related
            void EditComponent(); // Inside Circuit related
            std::vector<Component*> AddSerialComponents();
            Component* CreateComponent();
            void PrintCircuits();
        protected:
            // Interface related functions
            void WelcomeMessage();
            void MainMenu();
            void AddCircuit();
            void EditCircuit();
            void ShowAllCircuits();
            void CombineCircuits();

            // Graphics related functions
            void Display();
            void UpdateGraphic();
            void UpdateObjects(vvc add_circuit_objects);
        public:
            Interface();
    };

    // Clears terminal. Depending of OS different command is called
    void Clear();
    bool AskToTerminate();


}

#endif /* !CIRCUIT_H */