/*============================================================
** UTF-8
**
** Assignment 1  (Deadline: 10/02/2023)
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Functions: ask_to_terminate(), get_input(string), get_energy(int, int, int), ask_for_conversion(), main()
**
** Purpose: Enter 3 int values to calculate photon energies of electron transition (Bohr)
**        : Ask for energy conversion J/eV
**        : Validate input
**
** Comments: This is a single-file program
**
** Date:  03 February 2023
**
===========================================================*/


//=== includes ===
#include<iostream>
#include<cmath>
#include<string> 
#include<conio.h>

//=== defined functions ===

// Ask user to terminate program
void ask_to_terminate(){
    // User's input
    std::string _input;

    std::cout << "Detected incorrect input. Do you wish to exit the program? [y/n] ";
    std::cin >> _input;
    if(_input == "Y" || _input == "y"){
        exit(0);
    }
}

// Ask user for input and check if the input is correct (int)
// Argument: string enter_text- text to display when asking for input (what user should enter)
int get_input(std::string enter_text){
    // string _input - requested input must be a from of int (be able to correctly change type from string to int)
    std::string _input;
    // bool _continue - used in the checking loop, if ALL is correct then _continue = false
    bool _continue = true;

    // Ask for the input
    std::cout << enter_text;
    std::cin >> _input;

    // Notice that even if input = 3a4 we get input = 3, which is not what user put in (g++)
    while(std::cin.fail() || _continue){
        // Try to convert input to integer (that's what is requested from the user)
        try{
            // Everything is correct. We got a POSITIVE integer from user (different type is unacceptable, including double xx.0)
            if(std::to_string(std::stoi(_input)) == _input && std::stoi(_input)>0){
                _continue = false;
            }
            // Wrong data type (i.e. the input is not an integer, can be double, string (mix of digits and characters))
            else{
                std::cout << "Input was invalid, enter the POSITIVE value in the correct (integer) format" << std::endl;
                // Ask for program termination 
                ask_to_terminate();
                // Clear and ignore incorrect input (not integer or not positive integer)
                std::cout << enter_text;
                std::cin.clear();
                std::cin.ignore();
                std::cin >> _input;
            }
        }
        // Needed when input cannot be changed to integer (f.e. (int)"aaa" is an error), then run catch
        catch(...){
            std::cout << "Input was invalid, enter the POSITIVE value in the correct (integer) format"<< std::endl;
            // Ask for program termination 
            ask_to_terminate();
            // Clear and ignore incorrect input (not integer or not positive integer)
            std::cout << enter_text;
            std::cin.clear();
            std::cin.ignore();
            std::cin >> _input;
        }
    }

    // Return the correct input
    return std::stoi(_input);
}

// Get energy tranisiton for i->j (ni->nj) for an atom of Z protons
// Arguments: int Z - protons in the atom
//          : int ni - initial orbital
//          : int nj - final orbital
double get_energy(int Z, int ni, int nj){
    return 13.6 * std::pow(Z,2) * (std::pow(nj,-2) - std::pow(ni,-2)); // eV
}

// Ask user for energy conversion from eV to J
bool ask_for_conversion(){
    // User's inpit
    std::string _unit;

    std::cout << "Enter the unit of energy [eV/J]: ";
    std::cin >> _unit;
    // Run the loop untill the correct input ("eV"/"J") is detected
    while(true){
        if(_unit == "J"){
            return true;
        }
        else if(_unit == "eV"){
            return false;
        }
        std::cout << "Incorrect unit" << std::endl;
        ask_to_terminate();
        std::cout << "Enter the correct unit [eV/J]: ";
        std::cin >> _unit;
    }
}


//=== main ===
int main(){

    // eV to J conversion factor
    const double eV_to_J{1.60218e-19};
    // Declrate the unit of the energy
    std::string unit{" eV"};
    // Energy of photon emitted/collected for i->j transition
    double energy;
    // Z - number of protons, ni - initial orbital, nj - final orbital
    int Z, ni, nj;

    // Get data from the user
    Z = get_input("Enter the number of protons in atom (integer): ");
    ni = get_input("Enter the initial orbital (integer): ");
    nj = get_input("Enter the orbital electron is transmitted to (integer): ");

    // Calculate energy from the given inputs
    energy = get_energy(Z, ni, nj);

    // Change (or not) 
    bool st = ask_for_conversion();
    if(st){
        energy *= eV_to_J;
        unit = " J";
    }

    // Output
    std::cout << "Enegy of emitted/absorbed photon in electron transition "<< ni << "->" << nj 
    << " is: " << energy << unit << std::endl;

    std::cout << "Enter any key to exit";
    getch();
    return 0;
}