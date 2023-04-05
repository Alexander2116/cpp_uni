// circuit.cpp

#include "circuit.hpp"

namespace myACCircuit{
    using namespace myComponents;

    Circuit::Circuit(){}

    void Circuit::Add_serial(Component* new_component){
        std::vector<Component*> temp;
        temp.push_back(new_component);
        circuit_objects.push_back(temp);
    }
    void Circuit::Add_parallel(std::vector<Component*> new_components){
        circuit_objects.push_back(new_components);
    }
    std::vector<std::vector<Component*>> Circuit::Get_objects(){
        return circuit_objects;
    }

}