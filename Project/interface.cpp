#include "interface.hpp"

namespace myInterface{
    using namespace myComponents;
    using namespace myACCircuit;
    using namespace myComplex;

    Interface::Interface(){};

    // Display current layout 
    void Interface::Display(){
        UpdateGraphic();

        // Start Frame
        // it is *7 because a component has 7char representation
        for(int i=0; i<x_size_window*7;i++){
            std::cout << "*";
        }
        std::cout << std::endl << std::endl;

        // Fill Frame
        for(int i=1; i <= y_size_window; i++){
            for(int j=1; j <= x_size_window; j++){
                std::cout << display_data(i,j);
            }
            std::cout << std::endl;
        }
        
        // End Frame
        std::cout << std::endl;
        for(int i=0; i<x_size_window*7; i++){
            std::cout << "*";
        }
    }

    // Updates the display matrix
    void Interface::UpdateGraphic(){
        x_size_window = circuit_objects.size();

        for(auto obj : circuit_objects){
            if(obj.size() > y_size_window){
                y_size_window = obj.size();
            }
        }

        display_data = StringMatrix(y_size_window,x_size_window); // y rows and x columns
        // Vector object (circuit_object) index starts with 0
        // Matrix index starts with 1
        for(int i=1; i <= circuit_objects.size(); i++){
            for(int j=1; j <= circuit_objects[i-1].size(); j++){
                display_data(j,i) = circuit_objects[i-1][j-1]->GraphicRepresentation();
            }
        }

    }

    void Interface::UpdateObjects(vvc add_circuit_objects){
        circuit_objects = add_circuit_objects;
    }


    void Clear(){
        #if defined _WIN32
            system("cls");
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            system("clear");
        #elif defined (__APPLE__)
            system("clear");
        #endif
    }
}