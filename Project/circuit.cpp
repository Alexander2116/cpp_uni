// circuit.cpp

#include "circuit.hpp"

namespace myACCircuit{
    using namespace myComponents;

    Circuit::Circuit(){
        _is_combined = false;
        _impedance = complex(0,0);
    }

    Circuit::Circuit(Circuit a, Circuit b, bool serial){
        _is_combined = true;
        if(serial == true){
            _impedance = a.GetImpedance() + b.GetImpedance();
            // Objects
        }
        else{
            _impedance = 1/(1/a.GetImpedance() + 1/b.GetImpedance());
            // Objects
        }
    }

    Circuit::~Circuit(){
        _impedance = complex(0,0);
        circuit_objects.clear();
    }

    int Circuit::_id{0};

    // *****************************************
    /* Private functions to calculate impedances:
        First: Calculate parallel blokes of components
        Second Calculate serial blokes of impedances 
    */
   void Circuit::Set_Frequency(double freq){
        _frequency = freq;
   }

    // Adding parallel impadances: 1/Z = 1/Z1 + 1/Z2 + ...
    std::vector<complex> Circuit::calc_parallel(vvc circuit_objects_list){
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
    // Adding serial impadances: Z = Z1 + Z2 + Z3 + ...
    complex Circuit::calc_serial(std::vector<complex> impedancies){
            complex temp(0,0);
            // Adding parallel
            for(auto imped : impedancies){
                temp += imped;
            }
            return temp;
    } // gives impedance for serial components
    // *****************************************

    void Circuit::Add_serial(Component* new_component){
        std::vector<Component*> temp;
        new_component->SetFrequency(_frequency);
        temp.push_back(new_component);
        circuit_objects.push_back(temp);
    }
    void Circuit::Add_parallel(std::vector<Component*> new_components){
        for(auto& comp : new_components){
            comp->SetFrequency(_frequency);
        }
        circuit_objects.push_back(new_components);
    }
    vvc Circuit::Get_objects(){
        return circuit_objects;
    }
    double Circuit::GetEMF(){
        return _efm;
    }
    complex Circuit::GetImpedance(){
        // Just in case if circuit_objects is empty. complex(0,0) should be returned anyway looking at calc_serial() structure
        // Alternatively I could use if(obj != null)
        if(!_is_combined){
            try{
                _impedance = calc_serial(calc_parallel(circuit_objects));
            }
            catch(...){
                std::cout << "Impedance couldn't be calculated. Perhaps list of objects is empty" << std::endl;
                _impedance = complex(0,0);
            }
            return _impedance;
        }
        else{
            return _impedance;
        }
    }

    double Circuit::GetPhaseDifference(){
        return _impedance.get_argument();
    }

    void Circuit::Info(){
        int count=0;
        for(auto a: circuit_objects){
            for(auto b: a){
                // Empty component is not an actual component
                if(b->CompName() != "Empty"){
                    count += 1;
                }
            }
        }
        std::cout << "This circuit has " << count << " components";
    }
}