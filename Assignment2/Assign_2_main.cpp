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
        std::cout << "Unable to open file";
    }
    return data;
}

//
void separate_string(std::vector<std::string> data, std::vector<double> *grade, std::vector<int> *course_id, std::vector<std::string> *course_name){
    int _items = data.size();
    std::string temp_str;
    for(int i =0; i < _items; i++){
        temp_str = data[i];
        grade->push_back(std::stod(temp_str.substr(0,temp_str.find(" "))));
        course_id->push_back(std::stoi(temp_str.substr(1,temp_str.find(" "))));
        course_name->push_back(temp_str.substr(1,temp_str.find("   ")));
    }
}

//=== main ===
int main(){
    std::string path = ".\\courselist.dat";
    std::vector<std::string> data;
    std::vector<double> grade; 
    std::vector<int> course_id; 
    std::vector<std::string> course_name;

    data = load_data(path);
    separate_string(data, &grade, &course_id, &course_name);

    for(int i =0; i < grade.size(); i++){
        std::cout << grade[i] << std::endl;
    }
    std::cout << "Enter any key to exit";
    getch();
    return 0;
}