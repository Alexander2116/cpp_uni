#include "interface.hpp"

namespace myInterface{
    using namespace myComponents;
    using namespace myACCircuit;
    using namespace myComplex;

    Interface::Interface(){};
    void Interface::Display(){
        Update();

        // Start Frame
        for(int i=0; i<x_size_window;i++){
            std::cout << "*";
        }
        std::cout << std::endl << std::endl;

        // Fill Frame
        for(int i=1; i <= x_size_window; i++){
            for(int j=1; j <= y_size_window; j++){
                std::cout << display_data(i,j);
            }
            std::cout << std::endl;
        }
        
        // End Frame
        std::cout << std::endl << std::endl;
        for(int i=0; i<x_size_window; i++){
            std::cout << "*";
        }
    }
    void Interface::Update(){
        x_size_window = circuit_objects.size();

        for(auto obj : circuit_objects){
            if(obj.size() > y_size_window){
                y_size_window = obj.size();
            }
        }
        display_data = StringMatrix(x_size_window,y_size_window);
        for(int i=1; i <= circuit_objects.size(); i++){
            for(int j=1; j <= circuit_objects[i].size();j++){
                display_data(j,i) = circuit_objects[i][j]->GraphicRepresentation();
            }
        }

    }


}