// interface.cpp

#include "interface.hpp"

namespace myInterface{
    using namespace myComponents;
    using namespace myACCircuit;
    using namespace myComplex;

    /**** Constructor & deconstructor ****/
    Interface::Interface(){
        Clear();
        //MainMenu();
    }
    Interface::~Interface(){
        _current_circuit = nullptr;
        _current_circuit_objects.clear(); 
        _display_data.~StringMatrix(); 
        _circuits.clear();
    }

    /**** Private ****/
    void Interface::EditCir(Circuit* circuit){
        int _input;
        double _freq;
        bool _go_back = false;
        _current_circuit = circuit;
        while(!_go_back){
            _current_circuit->Info();
            std::cout << std::endl;
            std::cout << std::endl << "**** Modifying currect circuit ****" << std::endl;
            std::cout << "1: Change circuit frequency connection" << std::endl;
            std::cout << "2: Add component" << std::endl;
            std::cout << "3: Show circuit (graphical representation)" << std::endl;
            std::cout << "4: Show All Components (list)" << std::endl;
            std::cout << "5: Edit components" << std::endl;
            std::cout << "6: Go Back" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            std::cin >> _input;
            //Clear();
            try{
                // Safe, because characters correstponding to 1-5 are system control characters
                switch(_input){
                    case 1:
                        std::cout << "Enter the frequency supply source for the circuit [Hz]: ";
                        std::cin >> _freq;
                        try{
                            if(_freq <= 0){
                                std::cout << "Frequency cannot be negative nor 0" << std::endl;
                            }
                            else{
                                // Updates impedance automatically
                                _current_circuit->SetFrequency(_freq);
                                Clear();
                            }
                        }
                        catch(char const* error_message){
                            Clear();
                            std::cout << "Couldn't set the frequency" << std::endl;
                            std::cout << "Error: " << error_message << std::endl;
                        }
                        break;
                    // Add component
                    case 2:
                        AddComponent();
                        Clear();
                        break;
                    // Show circuit (graphical representation)
                    case 3:
                        Clear();
                        _current_circuit_objects = _current_circuit->GetObjects();
                        if(_current_circuit_objects.size()>0){
                            Display();
                        }
                        break;
                    // Show All Components (list)
                    case 4:
                        Clear();
                        std::cout << "List of the objects: " << std::endl;
                        try{
                            for(auto c1: _current_circuit->GetObjects()){
                                for(auto c2: c1){
                                    c2->Info();
                                }
                            }
                        }
                        catch(char const* error_message){
                            std::cout << "Error: " << error_message << std::endl;
                        }
                        std::cout << std::endl;
                        break;
                    // Edit components
                    case 5:
                        EditComponent();
                        Clear();
                        break;
                    // Go Back
                    case 6:
                        _go_back = true;
                        break;
                    default:
                        Clear();
                        break;
                }
                //Clear();
            }
            catch(char const* error_message){
                std::cout << "Error: " << error_message << std::endl;
            }
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
        std::cin.clear();
        std::cin.ignore();
        std::cin >> _input;
        switch(_input){
            // Serial
            case 1:
                rlc = CreateComponent(); 
                if(rlc != nullptr){
                    _current_circuit->AddSerial(rlc);
                }
                else{
                    std::cout << "Component couldn't be added" << std::endl;
                }
                break;
            // Parallel
            case 2:
                rlcs = AddSerialComponents();
                _current_circuit->AddParallel(rlcs);
                break;
            // Exit
            case 3:
                break;
            default:
                std::cout << "Non-existing option. Go back." << std::endl;
                break;
        }

    }

    void Interface::EditComponent(){
        int idx_i, idx_j;
        std::cout << "What component would you like to edit?" << std::endl;
        vvc obj = _current_circuit->GetObjects();
        
        for(int i=0; i < obj.size();i++){
            for(int j=0; j < obj[i].size();j++){
                std::cout << i << " " << j << " :";
                obj[i][j]->Info();
            }
            std::cout << std::endl;
        }
        std::cout << "Enter [i] [j] index to select the component [i j]: ";
        try{
            std::cin >> idx_i >> idx_j;
            if(idx_i < obj.size()){
                if(idx_j < obj[idx_i].size()){
                    Component* rlc;
                    int _input;
                    double _value;

                    std::cout << "Select what you would like to do with this component: ";
                    obj[idx_i][idx_j]->Info();
                    std::cout << "1: Replace to new Resistor" << std::endl;
                    std::cout << "2: Replace to new Capacitor" << std::endl;
                    std::cout << "3: Replace to new Inductor" << std::endl;
                    std::cout << "4: Remove" << std::endl;
                    std::cout << "Any character: Go back" << std::endl;
                    std::cin >> _input;
                    switch(_input){
                        // Resistor
                        case 1:
                            // \u03a9, \u2126, unicode for OMEGA - doesn't work properly on Windows
                            std::cout << "Enter resistance [Ohm]: ";
                            std::cin >> _value;
                            _current_circuit_objects[idx_i][idx_j] = new Resistor(_value);
                            break;
                        // Capacitor
                        case 2:
                            std::cout << "Enter capacitance [pF]: ";
                            std::cin >> _value;
                            obj[idx_i][idx_j] = new Capacitor(_value);
                            break;
                        // Inductor
                        case 3:
                            std::cout << "Enter inductance [H]: ";
                            std::cin >> _value;
                            obj[idx_i][idx_j] = new Inductor(_value);
                            break;
                        // Remove
                        case 4: 
                            // Check if works
                            obj[idx_i].erase(obj[idx_i].begin() + idx_j);
                            break;
                        // Exit
                        case 5: 
                            std::cout << "Going back" << std::endl;
                            break;
                    } // switch end
                    _current_circuit->UpdateObjects(obj);

                } // inner if
            } // outer if
        } //try
        catch(char const* error_message){
                std::cout << "Error: " << error_message << std::endl;
        }

    }

    // Interface to create a block of components to add them in series
    // Returns the created block of components 
    std::vector<Component*> Interface::AddSerialComponents(){
        bool stop = false;
        std::vector<Component*> temp_comp_list;
        Component* temp_comp;
        std::cout << std::endl;
        while(!stop){
            temp_comp = CreateComponent();
            if(temp_comp != NULL){
                temp_comp_list.push_back(temp_comp);
            }
            else{
                std::cout << "Adding the component was unsuccessful" << std::endl;
            }
            std::cout << "Would like like to add another component? [y|n] " << std::endl; 
            // 'yes' return true, so if returns "false" then end the loop
            std::cin.clear();
            std::cin.ignore();
            stop = (TakeYNinput() == false);
            //Clear();
        }
        return temp_comp_list;
    }

    // Allows to create a component,
    // I could think about better implementation - without returning resistor(0)
    // To work correctly check if not==null
    /// Return: Component if correct, nullptr if incorrect/error/exit
    Component* Interface::CreateComponent(){
        Component* rlc;
        int _input;
        double _value;
        double _freq = _current_circuit->GetFrequency();
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
                    // \u03a9, \u2126, unicode for OMEGA - doesn't work properly on Windows
                    std::cout << "Enter resistance [Ohm]: ";
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
                default:
                    std::cout << "Non-existing option. Go back" << std::endl;
                    return nullptr;

            }
            rlc->SetFrequency(_freq);
            return rlc;
        }
        catch(char const* error_message){
            std::cout << "Incorrect item" << std::endl;
            std::cout << "Error: " << error_message << std::endl;
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
    
    /**** Protected ****/
    /*  Interface related functions  */
    void Interface::WelcomeMessage(){
        Clear();
        std::cout << "Hello there," << std::endl;
        std::cout << "this program is used to simulate RCL circuits and calculate their impedances for given frequency." << std::endl <<
        "You can create a new circuit by adding a resistor, capacitor or inductor to each block." << std::endl <<
        "'A block' is a part of the circuit. Each block must have at least one element." << std::endl <<
        "Each circuit can be edited. Available circuits have unique index." << std::endl <<
        "Graphical elements are: " << std::endl <<
        "-/\\/\\/-  Resistor" << std::endl <<
        "--| |--  Capacitor" << std::endl <<
        "--ooo--  Inductor" << std::endl << std::endl;
    }

    void Interface::AddCircuit(){
        Clear();
        std::cout << "**** Add new circuit ****"<< std::endl;
        Circuit new_cir;
        
        EditCir(&new_cir);
        if(new_cir.GetObjects().size()>0){
            _circuits.push_back(new_cir);
        }
    }

    void Interface::EditCircuit(){
        int _input;
        int _idx;
        bool stop = false;
        Clear();
        while(!stop){
            std::cout << "**** Available circuits *****" << std::endl;
            PrintCircuits();
            std::cout << std::endl;
            std::cout << "**** Edit Circuit ****" << std::endl;
            std::cout << "1: Select circuit to edit" << std::endl;
            std::cout << "2: Exit" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            std::cin >> _input;
            try{
                // Safe, because characters corresponding to 1-5 are system control characters
                switch(_input){
                    case 1:
                        std::cout << "Index of the circuit: ";
                        std::cin >> _idx;
                        if(_idx < _circuits.size() && _idx >= 0){
                            EditCir(&_circuits[_idx]);
                            Clear();
                        }
                        else{
                            Clear();
                            std::cout << "This circuit doesn't exist" << std::endl << std::endl;
                        }
                        break;
                    case 2:
                        stop = true;
                        break;
                    default:
                        Clear();
                }
            }
            catch(char const* error_message){
                Clear();
                std::cout << "Incorrect input" << std::endl;
                std::cout << "Error: " << error_message << std::endl;
            }

        }
    }

    void Interface::ShowAllCircuits(){
        Clear();
        std::cout << "**** Available circuits *****" << std::endl;
        PrintCircuits();
        std::cout << std::endl;
        //std::cout << "Press any button to go back "; // Function below provides the message 
        PressAnyButtonToContinue();
    }

    void Interface::CombineCircuits(){
        int c1, c2;
        bool series;
        Clear();
        std::cout << "**** Available circuits *****" << std::endl;
        PrintCircuits();
        std::cout << "What two circuits would you like to combine? [i j]" << std::endl;
        std::cin >> c1 >> c2;
        if(c1 < _circuits.size() && c2 < _circuits.size() && c1 >= 0 && c2 >= 0){
            std::cout << "Do you want to connect it in series [y] or parallel [n]?: " << std::endl; 
            series = TakeYNinput();
            _circuits.push_back(Circuit(_circuits[c1], _circuits[c2], series));
        }
        else{
            std::cout << "Given circuit doesn't exist" << std::endl;
        }
        PressAnyButtonToContinue();
    }


    /*  Graphics related functions  */
    // Display current layout 
    void Interface::Display(){
        UpdateGraphic();

        // Start Frame
        // it is *7 because a component has 7char representation
        for(int i=0; i<_x_size_window*7; i++){
            std::cout << "*";
        }
        std::cout << std::endl << std::endl;

        // Fill Frame
        for(int i=1; i <= _y_size_window; i++){
            for(int j=1; j <= _x_size_window; j++){
                std::cout << _display_data(i,j);
            }
            std::cout << std::endl;
        }
        
        // End Frame
        std::cout << std::endl;
        for(int i=0; i<_x_size_window*7; i++){
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    // Updates the display matrix
    void Interface::UpdateGraphic(){
        _x_size_window = _current_circuit_objects.size();

        for(auto obj : _current_circuit_objects){
            if(obj.size() > _y_size_window){
                _y_size_window = obj.size();
            }
        }

        _display_data = StringMatrix(_y_size_window,_x_size_window); // y rows and x columns
        // Vector object (circuit_object) index starts with 0
        // Matrix index starts with 1
        for(int i=1; i <= _current_circuit_objects.size(); i++){
            for(int j=1; j <= _current_circuit_objects[i-1].size(); j++){
                _display_data(j,i) = _current_circuit_objects[i-1][j-1]->GraphicRepresentation();
            }
        }

    }

    void Interface::SetObjects(vvc add_current_circuit_objects){
        _current_circuit_objects = add_current_circuit_objects;
    }

    /**** Public ****/
    void Interface::MainMenu(){
        int _input;

        while(!_exit_request){
            WelcomeMessage();
            std::cout << "**** Main Menu ****" << std::endl;
            std::cout << "1: Add New Circuit" << std::endl;
            std::cout << "2: Edit Circuit" << std::endl;
            std::cout << "3: Show All Circuits" << std::endl;
            std::cout << "4: Combine Circuits" << std::endl;
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
                        ShowAllCircuits();
                        break;
                    case 4:
                        // Exit
                        CombineCircuits();
                        break;
                    case 5:
                        // Exit
                        _exit_request = true;
                        break;
                }
                Clear();
            }
            catch(char const* error_message){
                std::cout << "Incorrect input" << std::endl;
                std::cout << "Error: " << error_message << std::endl;
            }
            std::cin.clear();
            std::cin.ignore();
        }
    }
    

    /**** Outside-Class functions ****/

    void Clear(){
        #if defined _WIN32
            system("cls");
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            system("clear");
        #elif defined (__APPLE__)
            system("clear");
        #endif
    }

    // Ask user to provide "y" or "n", Take Y/N input
    // "y" returns true, "n" returns false
    bool TakeYNinput(){
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


    void PressAnyButtonToContinue(){
        #if defined _WIN32
            system("pause");
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            system("read");
        #elif defined (__APPLE__)
            system("read");
        #endif
    }
}