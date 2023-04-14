// circuit.cpp

#include "circuit.hpp"

namespace myACCircuit{
    using namespace myComponents;

    Circuit::Circuit(){}

    complex Circuit::calc_serial(std::vector<complex> impedancies){
            complex temp(0,0);
            // Adding parallel
            for(auto imped : impedancies){
                temp += imped;
            }
            return temp;
    } // gives impedance for serial components

    std::vector<complex> Circuit::calc_parallel(std::vector<std::vector<Component*>> circuit_objects_list){
        std::vector<complex> impedance_series;
        for(auto list_of_components : circuit_objects_list){
            complex temp(0,0);
            // Adding parallel
            for(auto component : list_of_components){
                temp += 1/(component->GetImpedance());
            }
            impedance_series.push_back(1/temp);
        }
        return impedance_series;
    } // gives impedance for parallel components

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
    complex Circuit::GetImpedance(){
        return calc_serial(calc_parallel(circuit_objects));
    }

}