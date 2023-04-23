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
        _resistivity = res;
        _impedance = complex(_resistivity,0);
    }
    std::string Resistor::GraphicRepresentation(){
        return "-/\\/\\/-"; // will show -/\/\/-, \ is an escape character
    }
    void Resistor::Info(){
        // u03a9 unicode escape for OMEGA
        std::cout << "Resistor: " << _resistivity << "Ω" << std::endl;
    }
    std::string Resistor::CompName(){
        return "Resistor";
    }

    /* Capacitor*/
    Capacitor::Capacitor(double cap){
        _capacitance = cap;
        _impedance = complex(0,-1/(_capacitance*_frequency*2*M_PI));
    }
    std::string Capacitor::GraphicRepresentation(){
        return "--| |--";
    }
    void Capacitor::Info(){
        std::cout << "Capacitor: " << _capacitance << "pF" << std::endl;
    }
    std::string Capacitor::CompName(){
        return "Capacitor";
    }

    /* Inductor */
    Inductor::Inductor(double ind){
        _inductance = ind;
        _impedance = complex(0,_inductance*_frequency*2*M_PI);
    }
    std::string Inductor::GraphicRepresentation(){
        return "--ooo--";
    }
    void Inductor::Info(){
        std::cout << "Inductor: " << _inductance<< "H" << std::endl;
    }
    std::string Inductor::CompName(){
        return "Inductor";
    }
}