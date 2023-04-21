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
        _current_circuit = circuit;
        while(!_go_back){
            std::cout << "**** Modifying currect circuit ****" << std::endl;
            std::cout << "1: Add component" << std::endl;
            std::cout << "2: Show circuit (graphical representation)" << std::endl;
            std::cout << "3: Show All Components (list)" << std::endl;
            std::cout << "4: Edit components" << std::endl;
            std::cout << "5: Go Back" << std::endl;
            std::cin >> _input;
            //Clear();
            try{
                // Safe, because characters correstponding to 1-5 are system control characters
                switch(_input){
                    // Add component
                    case 1:
                        AddComponent();
                        Clear();
                        break;
                    // Show circuit (graphical representation)
                    case 2:
                        Clear();
                        _current_circuit_objects = _current_circuit->Get_objects();
                        Display();
                        break;
                    // Show All Components (list)
                    case 3:
                        Clear();
                        std::cout << "List of the objects: " << std::endl;
                        try{
                            for(auto c1: _current_circuit->Get_objects()){
                                
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
                        Clear();
                        break;
                    // Go Back
                    case 5:
                        _go_back = true;
                        break;
                }
                //Clear();
            }
            catch(...){}
            std::cin.clear();
            std::cin.ignore();
        }
    }

    void Interface::AddComponent(){
        int _input;
        Component* rlc;
        std::vector<Component*> rlcs;
        std::cout << "**** Add Component to the Circuit ****" << std::endl;
        std::cout << "1: Add serial component to the next block (add one component)" << std::endl;
        std::cout << "2: Add parallel components to the next block (add many components)" << std::endl;
        std::cout << "3: Go Back" << std::endl;
        std::cin >> _input;
        switch(_input){
            // Serial
            case 1:
                rlc = CreateComponent(); 
                if(rlc != nullptr){
                    _current_circuit->Add_serial(rlc);
                }
                else{
                    std::cout << "Component couldn't be added" << std::endl;
                }
                break;
            // Parallel
            case 2:
                rlcs = AddSerialComponents();
                _current_circuit->Add_parallel(rlcs);
                break;
            // Exit
            case 3:
                break;
        }

    }
    // 
    std::vector<Component*> Interface::AddSerialComponents(){
        bool stop = false;
        std::vector<Component*> temp_comp_list;
        Component* temp_comp;
        std::cout << "" << std::endl;
        while(!stop){
            temp_comp = CreateComponent();
            if(temp_comp != NULL){
                temp_comp_list.push_back(temp_comp);
            }
            else{
                std::cout << "Adding the component was unsuccessful" << std::endl;
            }
            std::cout << "Would like like to add another component? [y|n] " << std::endl; 
            // yes return true, so if returns "false" then end the loop
            stop = (AskToTerminate() == false);
            Clear();
        }
        return temp_comp_list;
    }

    void Interface::EditComponent(){
        std::cout << "What component would you like to edit?" << std::endl;
    }

    // Allows to create a component,
    // I could think about better implementation - without returning resistor(0)
    // To work correctly check if not==null
    /// Return: Component if correct, nullptr if incorrect/error/exit
    Component* Interface::CreateComponent(){
        Component* rlc;
        int _input;
        double _value;
        std::cout << "What component would you like to add?" << std::endl;
        std::cout << "1: Resistor" << std::endl;
        std::cout << "2: Capacitor" << std::endl;
        std::cout << "3: Inductor" << std::endl;
        std::cout << "4: Exit" << std::endl;
        std::cin >> _input;
        try{
            switch(_input){
                // Resistor
                case 1:
                    // \u03a9, \u2126, unicode for OMEGA
                    std::cout << "Enter resistance [\u2126]: ";
                    std::cin >> _value;
                    rlc = new Resistor(_value);
                    break;
                // Capacitor
                case 2:
                    std::cout << "Enter capacitance [pF]: ";
                    std::cin >> _value;
                    rlc = new Capacitor(_value);
                    break;
                // Inductor
                case 3:
                    std::cout << "Enter inductance [H]: ";
                    std::cin >> _value;
                    rlc = new Inductor(_value);
                    break;
                // Exit
                case 4: 
                    std::cout << "Going back" << std::endl;
                    return nullptr;

            }
            return rlc;
        }
        catch(...){
            std::cout << "Incorrect item" << std::endl;
            return nullptr;
        }
    }
    
    void Interface::PrintCircuits(){
        for(int i=0; i<_circuits.size(); i++){
            std::cout << i << ": ";
            _circuits[i].Info();
            std::cout << std::endl;
        }
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
            std::cout << "**** Main Menu ****" << std::endl;
            std::cout << "1: Add New Circuit" << std::endl;
            std::cout << "2: Edit Circuit" << std::endl;
            std::cout << "3: Combine Circuits" << std::endl;
            std::cout << "4: Show All Circuits" << std::endl;
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
                        ShowAllCircuits();
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
        Clear();
        std::cout << "**** Add new circuit ****"<< std::endl;
        Circuit new_cir;
        EditCir(&new_cir);
        _circuits.push_back(new_cir);
    }
    void Interface::EditCircuit(){
        int _input;
        bool stop = false;
        Clear();
        std::cout << "**** Available circuits *****" << std::endl;
        PrintCircuits();
        std::cout << std::endl;
        std::cout << "**** Edit Circuit ****" << std::endl;
        while(!stop){
            std::cout << "1: Select circuit to edit" << std::endl;
            std::cout << "2: Exit" << std::endl;

            std::cin >> _input;
            try{
                // Safe, because characters correstponding to 1-5 are system control characters
                switch(_input){
                    case 1:
                        std::cout << "Index of the circuit: ";
                        std::cin >> _input; 
                        EditCir(&_circuits[_input]);
                        break;
                    case 2:
                        stop = true;
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
    void Interface::ShowAllCircuits(){
        Clear();
    }
    void Interface::CombineCircuits(){
        Clear();
    }


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
        std::cout << std::endl;
    }

    // Updates the display matrix
    void Interface::UpdateGraphic(){
        x_size_window = _current_circuit_objects.size();

        for(auto obj : _current_circuit_objects){
            if(obj.size() > y_size_window){
                y_size_window = obj.size();
            }
        }

        display_data = StringMatrix(y_size_window,x_size_window); // y rows and x columns
        // Vector object (circuit_object) index starts with 0
        // Matrix index starts with 1
        for(int i=1; i <= _current_circuit_objects.size(); i++){
            for(int j=1; j <= _current_circuit_objects[i-1].size(); j++){
                display_data(j,i) = _current_circuit_objects[i-1][j-1]->GraphicRepresentation();
            }
        }

    }

    void Interface::UpdateObjects(vvc add_current_circuit_objects){
        _current_circuit_objects = add_current_circuit_objects;
    }

    /*  Outside-Class functions*/

    void Clear(){
        #if defined _WIN32
            system("cls");
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            system("clear");
        #elif defined (__APPLE__)
            system("clear");
        #endif
    }

    // Ask user to provide "y" or "n" 
    // "y" returns true, "n" returns false
    bool AskToTerminate(){
        // User's input
        std::string _input;
        std::cin >> _input;

        // Validate input
        while(true){
            if(_input == "Y" || _input == "y"){
                return true;
            }
            else if(_input == "N" || _input == "n"){
                return false;
            }
            else{
                std::cout << "SORRY, I do not understand what you want to do" << std::endl;
                std::cout << "Enter [y|n] ";
                std::cin.clear();
                std::cin.ignore();
                std::cin >> _input;
            }
        }
    }

}