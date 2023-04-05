#include "circuit.hpp"
#include "components.hpp"
#include "complex.hpp"

using namespace myACCircuit;
using namespace myComplex;
using namespace myComponents;

int main(){
    Circuit cir;
    for(int i=0; i<256; i++){
        std::cout<<"*";
    }
    std::getchar();
    return 0;
}