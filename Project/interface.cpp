#include "interface.hpp"

namespace myInterface{
    using namespace myComponents;
    using namespace myACCircuit;
    using namespace myComplex;

    Interface::Interface(){
        Clear();
        MainMenu();
    }

    /* Private */
    void Interface::EditCir(Circuit* circuit){
        int _input;
        bool _go_back = false;
        while(!_go_back){
            std::cout << "1: Add component" << std::endl;
            std::cout << "2: Show circuit (graphical representation)" << std::endl;
            std::cout << "3: Show All Components (list)" << std::endl;
            std::cout << "4: Edit components" << std::endl;
            std::cout << "5: Go Back" << std::endl;
            std::cin >> _input;
            try{
                // Safe, because characters correstponding to 1-5 are system control characters
                switch(_input){
                    // Add component
                    case 1:
                        AddComponent();
                        break;
                    // Show circuit (graphical representation)
                    case 2:
                        current_circuit_objects = circuit->Get_objects();
                        Display();
                        break;
                    // Show All Components (list)
                    case 3:
                        try{
                            for(auto c1: circuit->Get_objects()){
                                
                                for(auto c2: c1){
                                    c2->Info();
                                }
                            }
                        }
                        catch(...){std::cout << "Some error occured.";}
                        break;
                    // Edit components
                    case 4:
                        EditComponent();
                        break;
                    // Go Back
                    case 5:
                        // Exit
                        _exit_request = true;
                        break;
                }
                Clear();
            }
            catch(...){}
        }
    }

    void Interface::AddComponent(){
        std::cout << "1: Add serial component to the next block (add one component)" << std::endl;
        std::cout << "2: Add parallel components to the next block (add many components)" << std::endl;
        std::cout << "3: Go Back" << std::endl;
    }
    void Interface::EditComponent(){
        std::cout << "What component would you like to edit?" << std::endl;
    }
    Component* Interface::CreateComponent(){
        Component* rlc;
        int _input;
        double _value;
        std::cout << "What component would you like to add?" << std::endl;
        std::cout << "1: Resistor" << std::endl;
        std::cout << "2: Capacitor" << std::endl;
        std::cout << "3: Inductor" << std::endl;
        std::cin >> _input;
        try{
            switch(_input){
                // Resistor
                case 1:
                    std::cout << "please enter resistance [\u03a9]: ";
                    std::cin >> _value;
                    *rlc = Resistor(_value);
                    break;
                // Capacitor
                case 2:
                    std::cout << "please enter capacitance [pF]: ";
                    std::cin >> _value;
                    *rlc = Capacitor(_value);
                    break;
                // Inductor
                case 3:
                    std::cout << "please enter inductance [H]: ";
                    std::cin >> _value;
                    *rlc = Inductor(_value);
                    break;
            }
            return rlc;
        }catch(...){return rlc;}
    }
    /* Public */
    /*  Interface related functions  */
    void Interface::WelcomeMessage(){
        Clear();
        std::cout << "Hello there," << std::endl;
        std::cout << "Hello there," << std::endl;
    }

    void Interface::MainMenu(){
        int _input;

        WelcomeMessage();
        while(!_exit_request){
            std::cout << "***************" << std::endl;
            std::cout << "1: Add New Circuit" << std::endl;
            std::cout << "2: Edit Circuit" << std::endl;
            std::cout << "3: Combine Circuits" << std::endl;
            std::cout << "4: Show All Components" << std::endl;
            std::cout << "5: Exit Application" << std::endl;

            std::cin >> _input;
            try{
                // Safe, because characters correstponding to 1-5 are system control characters
                switch(_input){
                    case 1:
                        AddCircuit();
                        break;
                    case 2:
                        EditCircuit();
                        break;
                    case 3:
                        CombineCircuits();
                        break;
                    case 4:
                        ShowAllComponents();
                        break;
                    case 5:
                        // Exit
                        _exit_request = true;
                        break;
                }
                Clear();
            }
            catch(...){
                std::cout << "Incorrect input" << std::endl;
            }
            std::cin.clear();
            std::cin.ignore();
        }
    }
    void Interface::AddCircuit(){
        Circuit new_cir;
        EditCir(&new_cir);
        _circuits.push_back(new_cir);
    }
    void Interface::EditCircuit(){}
    void Interface::ShowAllComponents(){}
    void Interface::CombineCircuits(){}


    /*  Graphics related functions  */
    // Display current layout 
    void Interface::Display(){
        UpdateGraphic();

        // Start Frame
        // it is *7 because a component has 7char representation
        for(int i=0; i<x_size_window*7;i++){
            std::cout << "*";
        }
        std::cout << std::endl << std::endl;

        // Fill Frame
        for(int i=1; i <= y_size_window; i++){
            for(int j=1; j <= x_size_window; j++){
                std::cout << display_data(i,j);
            }
            std::cout << std::endl;
        }
        
        // End Frame
        std::cout << std::endl;
        for(int i=0; i<x_size_window*7; i++){
            std::cout << "*";
        }
    }

    // Updates the display matrix
    void Interface::UpdateGraphic(){
        x_size_window = current_circuit_objects.size();

        for(auto obj : current_circuit_objects){
            if(obj.size() > y_size_window){
                y_size_window = obj.size();
            }
        }

        display_data = StringMatrix(y_size_window,x_size_window); // y rows and x columns
        // Vector object (circuit_object) index starts with 0
        // Matrix index starts with 1
        for(int i=1; i <= current_circuit_objects.size(); i++){
            for(int j=1; j <= current_circuit_objects[i-1].size(); j++){
                display_data(j,i) = current_circuit_objects[i-1][j-1]->GraphicRepresentation();
            }
        }

    }

    void Interface::UpdateObjects(vvc add_current_circuit_objects){
        current_circuit_objects = add_current_circuit_objects;
    }


    void Clear(){
        #if defined _WIN32
            system("cls");
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            system("clear");
        #elif defined (__APPLE__)
            system("clear");
        #endif
    }
}