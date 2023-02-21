/*============================================================
** UTF-8
**
** Assignment 2  (Deadline: 24/02/2023)
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Functions: 
**          : 
**
** Purpose: 
**        : 
**        : 
**
** Comments: This is a single-file program
**         : .dat file has a structure of:  "double" "int"    "string" terminated by <LF> (0x0A)
**
** Date:  20 February 2023
**
===========================================================*/


//=== includes ===
#include<iostream>
#include<cmath>
#include<string> 
#include<conio.h>
#include<fstream>
#include<vector>

//=== defined functions ===

// Ask for path input
// parameters: pointer path
void data_path_ask(std::string *path){
    std::string input;
    std::string data_path;
    std::cout << "Is courselist.dat file in the folder with the code? [y|n] ";
    std::cin >> input;
    if(input == "y" || input == "Y"){
        // Do nothing, all alright
    }
    else if(input == "n" || input == "N"){
        // Ask to enter the file path
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

    myfile.open(path_to_file);
    if(myfile.is_open()){
        while (std::getline(myfile,line))
        {
            data.push_back(line);
        }
        myfile.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
        std::cout << "Run the script again and enter correct file path" << std::endl;
        exit(0);
    }
    return data;
}

//
void separate_string(std::vector<std::string> data, std::vector<double> *grade, std::vector<int> *course_id, std::vector<std::string> *course_name){
    int items = data.size();
    std::string temp_str;
    for(int i = 0; i < items; i++){
        temp_str = data[i];
        grade->push_back(std::stod(temp_str.substr(0,temp_str.find(" "))));
        course_id->push_back(std::stoi(temp_str.substr(1,temp_str.find(" "))));
        course_name->push_back(temp_str.substr(1,temp_str.find("   ")));
    }
}

//
double calculate_mean(std::vector<double> ddata){
    double mu = 0;
    double temp = 0;

    for(int i = 0; i < ddata.size(); i++){
        temp += ddata[i];
    }
    mu = temp/(ddata.size());

    return mu;
}

//
double calculate_std(std::vector<double> ddata){
    double sigma = 0;
    double temp = 0;
    double mu = calculate_mean(ddata);

    for(int i = 0; i < ddata.size(); i++){
        temp += std::pow((ddata[i]-mu),2);
    } 
    sigma = std::pow(temp/(ddata.size()-1),0.5);

    return sigma;
}

//=== main ===
int main(){
    std::string path = ".\\courselist.dat";
    std::vector<std::string> data;
    std::vector<double> grade; 
    std::vector<int> course_id; 
    std::vector<std::string> course_name;

    data_path_ask(&path);

    data = load_data(path);
    separate_string(data, &grade, &course_id, &course_name);

    std::cout << calculate_mean(grade) << std::endl;
    std::cout << calculate_std(grade) << std::endl;

    for(int i =0; i < grade.size(); i++){
        //std::cout << grade[i] << std::endl;
    }
    std::cout << "Enter any key to exit";
    getch();
    return 0;
}