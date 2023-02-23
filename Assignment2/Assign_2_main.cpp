/*============================================================
** UTF-8
**
** Assignment 2  (Deadline: 24/02/2023)
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: Load data from .dat file and seperate the input columns
**        : Sort the data ascending/descending by title or course code
**        : Select particular year
**
** Comments: This is a single-file program, BUT COULD USE MULTIPLE .h TO BE MORE CLEAN
**         : .dat file has a structure of:  "double" "int"    "string" terminated by <LF> (0x0A)
**
** Date:  20 February 2023
**
===========================================================*/


//=== includes ===
#include<iostream>
#include<cmath>
#include<string> 
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream> 

//=== defined functions ===

// Ask for path input
// parameters: pointer path
void data_path_ask(std::string *path){
    std::string input;
    std::string data_path;

    // Ask is the courselist is in the same folder (why?: because relative path is used)
    std::cout << "Is courselist.dat file in the folder with the code? [y|n] ";
    std::cin >> input;

    if(input == "y" || input == "Y"){
        // Do nothing, all alright
    }
    else if(input == "n" || input == "N"){
        // Ask to enter the file path. It can be any, validation is done later
        std::cout << "Enter the full path to the file: ";
        std::cin >> data_path;
        path->clear();
        path->append(data_path);
    }
    else{
        // Just exit, don't play with repeating the question
        std::cout << "Incorrect command. Exiting the program";
        exit(0);
    }
}

// Read all data from file
// Example of the entry:  65.6 10071   Mathematics 1
// So each row contains  "double" "int"    "string"
// Each line is terminated by <LF> (0x0A or 10)
std::vector<std::string> load_data(std::string path_to_file){
    std::vector<std::string> data;
    std::string line;
    std::ifstream myfile;

    // Open file
    myfile.open(path_to_file);

    // Check if the file can be opened (correct path OR any existing path), must be .dat extension
    if(myfile.is_open() && path_to_file.find(".dat") != std::string::npos){
        // Read every line and put it into string vector
        while (std::getline(myfile,line))
        {
            data.push_back(line);
        }
        std::cout << "Number of entries in that file is: " << data.size() << std::endl;
        myfile.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
        std::cout << "Run the script again and enter correct file path" << std::endl;
        exit(0);
    }
    return data;
}

// It separates string vector (data line input = data) into 3 vectors (grade, course_id, course_name) 
// Example of the entry:  65.6 10071   Mathematics 1
// So each row contains  "double" "int"    "string"
// Each line is terminated by <LF> (0x0A or 10)
void separate_string(std::vector<std::string> data, std::vector<double> *grade, std::vector<int> *course_id, std::vector<std::string> *course_name){
    std::string temp_str; // temporary variable => i-th element in the data vector 
    std::size_t delim; // first " " substring positon
    std::size_t delim3; // first "   " substring positon

    // Separate line into 3 vectors
    for(int i = 0; i < data.size(); i++){
        temp_str = data[i];
        delim = temp_str.find(" ");
        delim3 = temp_str.find("   ");
        // characters from 0 till the first " "
        grade->push_back(std::stod(temp_str.substr(0, delim))); // 1 space
        // characters from " " till the "   "
        course_id->push_back(std::stoi(temp_str.substr(delim, (delim3-delim)))); // 1 space
        // characters from the end of "   " till the end of the string
        course_name->push_back(temp_str.substr(delim3+3, (temp_str.size()-delim3-3))); // 3 spaces
    }
}

// Calculate mean of the data (double)
double calculate_mean(std::vector<double> ddata){
    double mu{0};
    double temp{0}; // temporary variable

    // Add all items in the vector together
    for(int i = 0; i < ddata.size(); i++){
        temp += ddata[i];
    }
    mu = temp/(ddata.size());

    return mu;
}

// Caclulate standard deviation of the data (double)
double calculate_std(std::vector<double> ddata){
    double sigma{0};
    double temp{0};
    double mu{calculate_mean(ddata)};

    // Add all (x-u)^2
    for(int i = 0; i < ddata.size(); i++){
        temp += std::pow((ddata[i]-mu),2);
    } 
    sigma = std::pow(temp/(ddata.size()-1),0.5);

    return sigma;
}

// sorting algorithim
// order = true => sorting ascending, order = false => sorting descending
// it sorted by ASCII character value, i.e "MP" will be higher than "Ma".
void sort_vector(std::vector<std::string> *vector_input, bool order){
    std::vector <std::string>::iterator vector_begin{vector_input->begin()};
    std::vector <std::string>::iterator vector_end{vector_input->end()};

    // Initially sort all items ascending
    sort(vector_begin, vector_end);
    if(order){
        //sort(vector_begin, vector_end);
    }
    // If not ascending then reverse sorted vector (sort descending)
    else{
        reverse(vector_begin, vector_end);
    }
}

// ask if user want to sort list
// int: 0 = no; 1 = yes, by course id; 2 = yes, by course name
// It validates input aswell
int do_you_want_to_sort(){
    bool validation{true};
    std::string input;

    std::cout << "Do you want to sort the course list? [y|n] " << std::endl;
    std::cin >> input;

    while(validation){
        // *** If YES ***
        if(input == "Y" || input == "y"){
            bool val2{true};
            std::cout << "Do you want to sort it by course id [1] or by course name [2]: [1|2] " << std::endl;
            std::cin >> input;
            while(val2){
                if(input == "1"){
                    validation = false;
                    val2 = false;
                    return 1;
                }
                else if(input == "2"){
                    validation = false;
                    val2 = false;
                    return 2;
                }
                else{
                    std::cout << "SORRY, I do not understand what you want to do" << std::endl;
                    std::cout << "Do you want to sort it by course id [1] or by course name [2]: [1|2] ";
                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> input;
                }
            }
        // *** If NO ***
        }
        else if(input == "N" || input == "n"){
            validation = false;
            return 0;
        }
        // *** Wrong input ***
        else{
            std::cout << "SORRY, I do not understand what you want to do" << std::endl;
            std::cout << "Do you want to sort to list? [y|n] ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> input;
        }
    }
    return 0; // Must be placed here to avoid "warning: control reaches end of non-void function"
}

// Ask user if one wants to sort it ascending (true) or descending (false)
bool ask_how_to_sort(){
    bool validation{true};
    std::string input;

    std::cout << "Do you want to sort it ascending [a] or descending [d]? [a|d] " << std::endl;
    std::cin >> input;
    while(validation){
        if(input == "a" || input == "A"){
            validation = false;
            return true;
        }
        else if(input == "d" || input == "D"){
            validation = false;
            return false;
        }
        else{
            std::cout << "SORRY, I do not understand what you want to do" << std::endl;
            std::cout << "Do you want to sort it ascending [a] or descending [d]? [a|d] ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> input;
        }
    }
    return true; // Must be placed here to avoid "warning: control reaches end of non-void function"
}

// Combines two vectors (<int, string>; <string, int>; <double>) assuming they both have the same length
// **** FUNCTION OVERLOADING
std::vector<std::string> combine_vectors(std::vector<int> v1, std::vector<std::string> v2, std::vector<double> v3){
    std::vector<std::string> fv;
    std::stringstream course;
    for(int i=0; i < v1.size(); i++){
        course << v1[i] << " " << v2[i] << " - Grade: " << v3[i];
        fv.push_back(course.str());
        course.str("");
    }
    return fv;
}
std::vector<std::string> combine_vectors(std::vector<std::string> v1, std::vector<int> v2, std::vector<double> v3){
    std::vector<std::string> fv;
    std::stringstream course;
    for(int i=0; i < v1.size(); i++){
        course << v1[i] << " " << v2[i] << " - Grade: " << v3[i];
        fv.push_back(course.str());
        course.str("");
    }
    return fv;
}
// ****END FUNCTION OVERLOADING

// Find all courses in a given year
std::vector<std::string> select_year(std::vector<std::string> v1, char year){
    std::vector<std::string> fv;
    std::string delim{" "};
    std::string temp_str; // temporary variable => i-th element in the data vector 

    delim += year;
    for(int i = 0; i < v1.size(); i++){
        temp_str = v1[i];
        if(temp_str.at(0) == year){
            fv.push_back(temp_str);
        }
        else if(temp_str.find(delim) == (temp_str.find(" - ")-6)){
            fv.push_back(temp_str);
        }
    }
    return fv;
}

// Ask user if one wants to select specific year
// year = 0: user doesn't want to see a specific year
char ask_to_select_year(){
    char year;
    std::string input;
    bool validation{true};

    std::cout << "Do you want to select a specific year? [y|n] " << std::endl;
    std::cin >> input;
    // *** Outer loop
    while(validation){
        if(input == "y" || input == "Y"){
            std::cout << "Please select a year [1|2|3|4] " << std::endl;
            std::cin >> input;
            // *** Inner loop
            while(true){
                // Switch case does not work on string, I could have just use stoi(input), but it would require additional validation (i.e if user enters "1year")
                if(input == "1"){
                    year = '1';
                    break;
                }
                else if (input == "2"){
                    year = '2';
                    break;
                }
                else if (input == "3"){
                    year = '3';
                    break;
                }
                else if (input == "4"){
                    year = '4';
                    break;
                }
                else{
                        std::cout << "SORRY, I do not understand what you want to do" << std::endl;
                        std::cout << "Please select a year [1|2|3|4] ";
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> input;
                }
                // *** End Inner loop
            }
            validation = false;
        }
        else if(input == "n" || input == "N"){
            year = '0';
            validation = false;
        }
        else{
            std::cout << "SORRY, I do not understand what you want to do" << std::endl;
            std::cout << "Do you want to select a specific year? [y|n] ";
            std::cin.clear();
            std::cin.ignore();
            std::cin >> input;
        }
        // *** End Outer loop
    }

    return year;
}



//=== main ===
int main(){
    // Allocate variables
    std::string path{".\\courselist.dat"};
    std::vector<std::string> data; // All data from the file. Each item = line from the file
    std::vector<double> grade; 
    std::vector<int> course_id; 
    std::vector<std::string> course_name;
    std::vector<std::string> full_course_name; // course id + course name (or name + id)
    int ask_sort;
    bool how_to_sort;

    // As for the path to .dat file
    data_path_ask(&path);

    // Load data and separate into 3 vectors 
    data = load_data(path);
    separate_string(data, &grade, &course_id, &course_name);

    // Clear unused vectors to save memory
    data.clear(); 

    // mean and std
    std::cout << "Mean of the grades: " << calculate_mean(grade) << std::endl;
    std::cout << "Standard deviation of the grades: " << calculate_std(grade) << std::endl;
    std::cout << std::endl; // extra space

    // Ask if user want to sort the data
    // CAREFULL it sorts by ASCII char values: i.e A(65) != a(97). Therefore "MP" will be higher than "Ma" in ascending order.
    ask_sort = do_you_want_to_sort();
    if(ask_sort == 0){
        full_course_name = combine_vectors(course_id, course_name, grade);
        // Do nothing, user doesn't want to sort
    }
    else if(ask_sort == 1){
        // sort by course id
        how_to_sort = ask_how_to_sort();
        full_course_name = combine_vectors(course_id, course_name, grade);
        sort_vector(&full_course_name, how_to_sort);
    }
    else{
        // sort by course name
        how_to_sort = ask_how_to_sort();
        full_course_name = combine_vectors(course_name, course_id, grade);
        sort_vector(&full_course_name, how_to_sort);
    }

    // Clear unused vectors to save memory
    grade.clear(); 
    course_id.clear(); 
    course_name.clear();

    // Show courses
    std::cout << "List of courses: " << std::endl;
    for(int i = 0; i < full_course_name.size(); i++){
        std::cout << full_course_name[i] << std::endl;
    }
    std::cout << std::endl; // extra space

    // Sort by the year
    std::vector<std::string> full_year;
    char year = ask_to_select_year();
    if(year != '0'){
        full_year = select_year(full_course_name,year);
        for(int i = 0; i < full_year.size(); i++){
            std::cout << full_year[i] << std::endl;
        }
        std::cout << std::endl; // extra space
    }

    // Clear vector
    full_course_name.clear();

    // End program
    std::cout << "Enter any key to exit";
    std::cin.ignore();
    std::cin.get();
    return 0;
}