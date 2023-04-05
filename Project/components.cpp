// components.cpp
#include "components.hpp"

namespace myComponents{
    using namespace myComplex;
    /* Component */
    Component::Component(){
    }
    Component::~Component(){
    }

    /* Resistor */
    Resistor::Resistor(double res): Component(){
        _resistivity = res;
    }
    complex Resistor::Impedance(){
        return complex(_resistivity,0);
    }
    std::string Resistor::GraphicRepresentation(){
        return "-/\\/\\/-";
    }

    /* Capacitor*/
    Capacitor::Capacitor(double cap){
        _capacitance = cap;
    }
    complex Capacitor::Impedance(){
        return complex(0,-1/_capacitance); // complex(0,-(_capacitance*_freq))
    }
    std::string Capacitor::GraphicRepresentation(){
        return "--| |--";
    }

    /* Inductor */
    Inductor::Inductor(double ind){
        _inductance = ind;
    }
    complex Inductor::Impedance(){
        return complex(0,_inductance); // complex(0,_inductance*_freq)
    }
    std::string Inductor::GraphicRepresentation(){
        return "--ooo--";
    }
}