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
        _frequency = a._frequency;
        b._frequency = _frequency;
        if(serial == true){
            std::cout << 1 << std::endl;
            _impedance = a.GetImpedance() + b.GetImpedance();
            std::cout << 2 << std::endl;
            circuit_objects = a.Get_objects();
            std::cout << 3 << std::endl;
            for(auto c : b.Get_objects()){
                std::cout << 4 << std::endl;
                circuit_objects.push_back(c);
            }
            std::cout << 5 << std::endl;
            // Objects
        }
        else{
            std::cout << 1 << std::endl;
            _impedance = 1/(1/a.GetImpedance() + 1/b.GetImpedance());
            int max_size = 0;
            std::cout << 2 << std::endl;
            for(auto c: a.Get_objects()){
                std::cout << 3 << std::endl;
                if(c.size() > max_size){
                    max_size = c.size();
                }
            }
            std::cout << 4 << std::endl;
            circuit_objects = a.Get_objects();
            // Get circuits to the same x-size
            if(b.Get_objects().size() > a.Get_objects().size()){
                for(int i=0; i < (b.Get_objects().size() - a.Get_objects().size()); i++){
                    std::cout << 5 << std::endl;
                    std::vector<Component*> a;
                    a.push_back(new EmptyComp());
                    circuit_objects.push_back(a);
                }
            }
            // Create space for the added circuit (must be separated by an empty line)
            for(auto c: circuit_objects){
                std::cout << 6 << std::endl;
                for(int i=0; i < (max_size - c.size()+1); i++){
                    std::cout << 7 << std::endl;
                    c.push_back(new EmptyComp());
                }
            }
            // Add b circuit to the circuit_objects
            for(auto c: b.Get_objects()){
                std::cout << 8 << std::endl;
                for(int i=0; i < b.Get_objects().size();i++){
                    std::cout << 9 << std::endl;
                    for(int j=0; j < c.size();j++){
                    std::cout << 10 << std::endl;
                    circuit_objects[i].push_back(c[j]);
                    }
                }
            }
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
    // Adding parallel impadances: 1/Z = 1/Z1 + 1/Z2 + ...
    std::vector<complex> Circuit::calc_parallel(vvc circuit_objects_list){
        std::vector<complex> impedance_series;
        // Read each block
        for(auto list_of_components : circuit_objects_list){
            std::cout << "a" << std::endl;
            complex temp(0,0);
            // Adding parallel
            if(list_of_components.size()>1){
                for(Component* component : list_of_components){
                    std::cout << "b" << std::endl;
                    component->SetFrequency(_frequency);
                    std::cout << "c" << std::endl;
                    // Issue here
                    complex a = component->GetImpedance();
                    std::cout << a << std::endl;
                    temp = temp + a.get_conjugate()*(1/(a.get_modulus())); // t = 1/z1 + 1/z2 +...
                    std::cout << "d" << std::endl;
                }
                std::cout << temp << std::endl;
                std::cout << 1/temp << std::endl;
                impedance_series.push_back(temp.get_conjugate()*(1/temp.get_modulus())); // I = 1/t = 1/(1/z1 + 1/z2 +...)
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
            std::cout << "e" << std::endl;
            // Adding parallel
            for(complex imped : impedancies){
                std::cout << "f" << std::endl;
                std::cout << imped << std::endl;
                temp = temp + imped;
                std::cout << temp << std::endl;
            }
            return temp;
    } // gives impedance for serial components
    // *****************************************
    void Circuit::Set_Frequency(double freq){
        _frequency = freq;
        GetImpedance();
    }

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
        GetImpedance();
        std::cout << "This circuit has " << count << " components with " << _impedance << " impedance and is supplied with " << _frequency << " Hz";
    }
}