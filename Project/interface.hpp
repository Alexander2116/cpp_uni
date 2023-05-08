/*============================================================
** UTF-8, Win32
**
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: An iterface for user.
**        : Easy navigation, creation and modification of stored circuits
**
** Classes: Interface()
**
** Comments: 
**
** Date:  15 April 2023
**
===========================================================*/

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
            // *** variables ***
            Circuit* _current_circuit; // Used to edit circuit inside EditCir() and AddComponent()
            // vvc - "vector vector component" - defined in circuit.hpp
            vvc _current_circuit_objects; // temporary, vvc for selected circuit (currently used)
            StringMatrix _display_data; // Matrix for graphics
            std::vector<Circuit> _circuits; // List of all stored circuits
            int _x_size_window{1}; // x size of the display
            int _y_size_window{1}; // y size of the display
            bool _exit_request{false}; // fully exit the program if true
            
            // *** functions ***
            void EditCir(Circuit* circuit); // Edits given circuit (has interface)
            void AddComponent(); // Inside Circuit related - interface to add a component
            void EditComponent(); // Inside Circuit related - interface to edit a component
            std::vector<Component*> AddSerialComponents(); // interface to add a component in series
            Component* CreateComponent(); // Interface to create a component
            void PrintCircuits(); // Prints the list of all saved circuits (index: items in circuit)
        // Protected - shouldn't be able to access as public to avoid misuse
        protected:
            // Interface related functions
            void WelcomeMessage();
            void AddCircuit(); // Option in the main interface
            void EditCircuit(); // Option in the main interface
            void ShowAllCircuits(); // Option in the main interface
            void CombineCircuits(); // Option in the main interface

            // Graphics related functions
            void Display();
            void UpdateGraphic();
            void UpdateObjects(vvc add_circuit_objects);
        public:
            Interface();
            ~Interface();
            void MainMenu(); // Main interface - starting
    };

    // Clears terminal. Depending of OS different command is called
    void Clear();
    bool TakeYNinput();
    void PressAnyButtonToContinue();


}

#endif /* !CIRCUIT_H */