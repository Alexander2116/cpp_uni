#include "circuit.hpp"
#include "components.hpp"
#include "complex.hpp"
#include "interface.hpp"

using namespace myACCircuit;
using namespace myComplex;
using namespace myComponents;
using namespace myInterface;

int main(){
    Circuit cir;
    
    std::vector<Component*> temp;
    std::vector<Component*> temp2;
    std::vector<Component*> temp3;
    
    temp.push_back(new Resistor(4));
    temp.push_back(new Capacitor(4));
    temp.push_back(new Resistor(4));
    temp2.push_back(new Inductor(4));
    temp2.push_back(new Capacitor(4));
    temp3.push_back(new Capacitor(4));
    temp3.push_back(new Capacitor(4));
    temp3.push_back(new Capacitor(4));
    temp3.push_back(new Capacitor(4));
    cir.Add_parallel(temp);
    cir.Add_parallel(temp2);
    cir.Add_parallel(temp3);

    Interface inter;
    inter.UpdateObjects(cir.Get_objects());
    inter.Display();
    std::getchar();
    return 0;
}