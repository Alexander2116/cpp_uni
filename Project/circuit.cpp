// circuit.cpp

#include "circuit.hpp"

namespace myACCircuit{
    using namespace myComponents;

    // *** Constructors and deconstructor ***
    Circuit::Circuit(){
        _is_combined = false;
        _impedance = complex(0,0);
        _id += 1;
    }

    Circuit::Circuit(Circuit a, Circuit b, bool serial){
        _is_combined = true;
        // New circuit inherits first's circuit frequency
        _frequency = a._frequency;
        b._frequency = _frequency;

        // Connect circuits in serial
        if(serial == true){
            _impedance = a.GetImpedance() + b.GetImpedance();
            _circuit_objects = a.GetObjects();
            for(auto c : b.GetObjects()){
                _circuit_objects.push_back(c);
            }
        }
        // Connect circuits in parallel
        else{
            _impedance = 1/(1/a.GetImpedance() + 1/b.GetImpedance());
            int max_size = 0;
            _circuit_objects = a.GetObjects();

            for(auto c: _circuit_objects){
                if(c.size() > max_size){
                    max_size = c.size();
                }
            }
            // Get circuits to the same x-size
            if(b.GetObjects().size() > a.GetObjects().size()){
                for(int i=0; i < (b.GetObjects().size() - a.GetObjects().size()); i++){
                    std::vector<Component*> a;
                    a.push_back(new EmptyComp());
                    _circuit_objects.push_back(a);
                }
            }
            // Create space for the added circuit (must be separated by an empty line) - y dim
            for(auto &c: _circuit_objects){
                for(int i=0; i <= (max_size - c.size()+1); i++){
                    c.push_back(new EmptyComp());
                }
            }
            // Add b circuit to the circuit_objects
            for(int i=0; i < b.GetObjects().size(); i++){
                for(int j=0; j < b.GetObjects()[i].size(); j++){
                    _circuit_objects[i].push_back(b.GetObjects()[i][j]);
                }
            }
        }
    }

    Circuit::~Circuit(){
        _impedance = complex(0,0);
        _circuit_objects.clear();
        _id -= 1;
    }

    int Circuit::_id{0};

    // *****************************************
    /* Private functions to calculate impedances:
        First: Calculate parallel blokes of components
        Second Calculate serial blokes of impedances 
    */
    // Adding parallel impadances: 1/Z = 1/Z1 + 1/Z2 + ...
    std::vector<complex> Circuit::calc_parallel(vvc circuit_objects_list){
        std::vector<complex> impedance_series;
        // Read each block
        for(auto list_of_components : circuit_objects_list){
            complex temp(0,0);
            // Adding parallel
            if(list_of_components.size()>1){
                for(Component* component : list_of_components){
                    component->SetFrequency(_frequency);
                    complex a = component->GetImpedance();
                    temp = temp + a.get_conjugate()*(1/(a.get_modulus_squared())); // t = 1/z1 + 1/z2 +...
                }
                impedance_series.push_back(temp.get_conjugate()*(1/temp.get_modulus_squared())); // I = 1/t = 1/(1/z1 + 1/z2 +...)
            }
            else{
                list_of_components[0]->SetFrequency(_frequency);
                impedance_series.push_back(list_of_components[0]->GetImpedance());
            }
        }
        return impedance_series;
    } // gives impedance for parallel components
    // Adding serial impadances: Z = Z1 + Z2 + Z3 + ...
    complex Circuit::calc_serial(std::vector<complex> impedancies){
            complex temp(0,0);
            // Adding parallel
            for(complex imped : impedancies){
                temp = temp + imped;
            }
            return temp;
    } // gives impedance for serial components

    // **********  PUBLIC FUNCTIONS *************
    void Circuit::SetFrequency(double freq){
        _frequency = freq;
        // Need to update impadance of the circuit upon changing frequency
        GetImpedance();
    }

    double Circuit::GetFrequency(){
        return _frequency;
    }

    void Circuit::AddSerial(Component* new_component){
        std::vector<Component*> temp;
        new_component->SetFrequency(_frequency);
        temp.push_back(new_component);
        _circuit_objects.push_back(temp);
    }

    void Circuit::AddParallel(std::vector<Component*> new_components){
        for(auto& comp : new_components){
            comp->SetFrequency(_frequency);
        }
        _circuit_objects.push_back(new_components);
    }

    vvc Circuit::GetObjects(){
        return _circuit_objects;
    }

    void Circuit::UpdateObjects(vvc new_obj){
        _circuit_objects = new_obj;
    }


    complex Circuit::GetImpedance(){
        // Just in case if circuit_objects is empty. complex(0,0) should be returned anyway looking at calc_serial() structure
        // Alternatively I could use if(obj != null)
        // if not combined then calculate impedance normally
        if(_is_combined == false){
            try{
                _impedance = calc_serial(calc_parallel(_circuit_objects));
            }
            catch(char const* error_message){
                std::cout << "Impedance couldn't be calculated. Perhaps list of objects is empty" << std::endl;
                std::cout << "Error: " << error_message << std::endl;
                _impedance = complex(0,0);
            }
            return _impedance;
        }
        // If combined then impedance is given at the creation. (special case for parallel adding)
        else{
            return _impedance;
        }
    }

    void Circuit::SetImpedance(complex impedance){
        _impedance = impedance;
    }

    double Circuit::GetPhaseDifference(){
        return _impedance.get_argument();
    }

    void Circuit::Info(){
        int count=0;
        for(auto a: _circuit_objects){
            for(auto b: a){
                // Empty component is not an actual component
                if(b->CompName() != "Empty"){
                    count += 1;
                }
            }
        }
        _impedance = GetImpedance();
        std::cout << "This circuit has " << count << " components with " << _impedance << " impedance and is supplied with " << _frequency << " Hz";
    }
}