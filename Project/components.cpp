// components.cpp

#include "components.hpp"
#define _USE_MATH_DEFINES

namespace myComponents{
    using namespace myComplex;
    /* Component */
    Component::Component(){
    }
    Component::~Component(){
    }
    void Component::SetFrequency(double frequency){
        _frequency = frequency;
    }
    double Component::GetFrequency(){
        return _frequency;
    }
    complex Component::GetImpedance(){
        return _impedance;
    }
    double Component::GetPhaseDifference(){
        return _impedance.get_argument();
    }
    double Component::GetImpedanceMagnitude(){
        return _impedance.get_modulus();
    }

    /* Resistor */
    Resistor::Resistor(double res): Component(){
        ++_obj_count;
        _resistivity = res;
        _impedance = complex(_resistivity,0);
    }
    std::string Resistor::GraphicRepresentation(){
        return "-/\\/\\/-"; // will show -/\/\/-, \ is an escape character
    }
    void Resistor::Info(){
        // u03a9 unicode escape for OMEGA - it doesn't work on windows correctly, but is fine in the debugger 
        std::cout << "Resistor: " << _resistivity << " ohm" << std::endl;
    }
    int Resistor::GetCount(){
        return _obj_count;
    }
    std::string Resistor::CompName(){
        return "Resistor";
    }
    Resistor::~Resistor(){
        --_obj_count;
    }
    int Resistor::_obj_count{0};

    /* Capacitor*/
    Capacitor::Capacitor(double cap){
        ++_obj_count;
        _capacitance = cap;
        _impedance = complex(0,-1/(_capacitance*_frequency*2*M_PI));
    }
    std::string Capacitor::GraphicRepresentation(){
        return "--| |--";
    }
    void Capacitor::Info(){
        std::cout << "Capacitor: " << _capacitance << " pF" << std::endl;
    }
    int Capacitor::GetCount(){
        return _obj_count;
    }
    std::string Capacitor::CompName(){
        return "Capacitor";
    }
    Capacitor::~Capacitor(){
        --_obj_count;
    }
    int Capacitor::_obj_count{0};

    /* Inductor */
    Inductor::Inductor(double ind){
        ++_obj_count;
        _inductance = ind;
        _impedance = complex(0,_inductance*_frequency*2*M_PI);
    }
    std::string Inductor::GraphicRepresentation(){
        return "--ooo--";
    }
    void Inductor::Info(){
        std::cout << "Inductor: " << _inductance<< " H" << std::endl;
    }
    int Inductor::GetCount(){
        return _obj_count;
    }
    std::string Inductor::CompName(){
        return "Inductor";
    }
    Inductor::~Inductor(){
        --_obj_count;
    }
    int Inductor::_obj_count{0};

    /* Empty */
    EmptyComp::EmptyComp(){}
    std::string EmptyComp::GraphicRepresentation(){
        return "       "; // 7 spaces
    }
    void EmptyComp::Info(){}
    std::string EmptyComp::CompName(){
        return "Empty";
    }
}