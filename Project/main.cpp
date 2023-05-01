/*============================================================
** UTF-8, Win32
**
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: Simulating of analogue RLC circuit.
**        : Find impedance of the circuit.
**        : Combine circuits 
**
** Comments : 
**
** Date:  15 April 2023
**
===========================================================*/

#include<iostream>
#include "circuit.hpp"
#include "components.hpp"
#include "complex.hpp"
#include "interface.hpp"

using namespace myACCircuit;
using namespace myComplex;
using namespace myComponents;
using namespace myInterface;

int main(){
    Interface inter;
    inter.MainMenu();
    return 0;
}