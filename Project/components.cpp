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
    double Resistor::Impedance(){
        return 0;
    }

    /* Capacitor*/
    Capacitor::Capacitor(){}
    double Capacitor::Impedance(){
        return 0;
    }

    /* Inductor */
    Inductor::Inductor(double ind){
        _inductance = ind;
    }
    double Inductor::Impedance(){
        return 0;
    }
}