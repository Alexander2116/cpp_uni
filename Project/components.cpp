// components.cpp
#include "components.hpp"

namespace myComponents{

    /* Component */
    Component::Component(){
    }
    Component::~Component(){
    }

    /* Resistor */
    Resistor::Resistor(){}
    double Resistor::Impedance(){}

    /* Capacitor*/
    Capacitor::Capacitor(){}
    double Capacitor::Impedance(){}

    /* Inductor */
    Inductor::Inductor(double ind){
        _inductance = ind;
    }
    double Inductor::Impedance(){}
}