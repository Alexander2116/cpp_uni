/*============================================================
** UTF-8
**
** Assignment 3  (Deadline: 03/03/2023)
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: 
**        : 
**        : 
**
** Classes: galaxy(string, double, double)
**
** Comments: 
**         :
**
** Date:  28 February 2023
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

//=== defined classes ===

class galaxy
{
  private:
    std::string hubble_type; // allow E0-7, S0, SBa 
    double redshift; // 0-10
    double m_tot; // range E7-E12 of solar mass (so variable of size E5 -> ~2^16 <-> ~2^17)
    double stellar_mass_fraction; // f = M/m_tot

    std::vector<galaxy> sattelite_galaxy;
    std::vector<galaxy> empty_val; // empty vector, used only to return if inserted i-th item of sattelite_galaxy is out of size.

    //const solar_mass = 1.989* std::pow(10,30); // kg

  public:
    // *** Constructors ***
    // Default
    galaxy() = default;
    // Parameterized constuctor
    galaxy(std::string hub_type, double red_shift, double mass){
      hubble_type = hub_type;
      redshift = red_shift;
      m_tot = mass; // in units of solar masses

      stellar_mass_fraction = 1/mass; // solar mass / total mass
    }
    // *** Destructor ***
    ~galaxy(){

    }
    // Return hubble_type
    std::string get_hubble_type(){
      return hubble_type;
    }
    
    // Return stellar mass (M_* = f_* x M_tot)
    double stellar_mass() {
      return m_tot * stellar_mass_fraction;
     }
    // Change galaxy's Hubble type
    void change_type(std::string new_type) { 
        hubble_type = new_type;
    }
    // Prototype for function to print out an object's data
    void print_data(){
      std::cout << "Hubble type: " << hubble_type << ";  " << "redshift: " << redshift << ";  " << "total mass: " << m_tot << std::endl;
    };

    // Add satellite galaxy
    // I assume satellite galaxy can be described with the same parameters as a normal galaxy
    void add_satellite_galaxy(std::string hub_type, double red_shift, double mass){
      galaxy sat_gal(hub_type, red_shift, mass);
      sattelite_galaxy.push_back(sat_gal);
    }
    void show_sattelite_galaxies(){
      for(int i = 0; i < sattelite_galaxy.size(); i++){
        std::cout << i << ": ";
        sattelite_galaxy[i].print_data();
      }
    }
    // Find a sattelite galaxy by putting a hubble_type
    galaxy* find_sattelite_galaxy(int i){
      // Linear search
      if(i <= sattelite_galaxy.size()){
        return &sattelite_galaxy[i];
      }
      else{
        // Just to make sure there is only 1 element in this vector
        if(empty_val.empty()){
          empty_val.push_back(galaxy("a",1,1));
        }
        // Could cause memory issues if called multiple times... Please don't use on purpose
        std::cout << "This object is not present" << std::endl;
        return &empty_val[0];
      }
    }

};

//=== defined functions ===


//=== main ===
int main(){
    // Example using default constructor
    galaxy g1("Irr", 2,2);

    std::cout << g1.get_hubble_type() << std::endl;
    // Example using parameterised constructor

    // print out data

    // Get and print out stellar mass

    // Change Hubble type from Irr to S0
    g1.change_type("S0");

    // Add satellite galaxies
    g1.add_satellite_galaxy("S1", 4, pow(10,7));
    g1.add_satellite_galaxy("S2", 5, pow(10,8));
    g1.show_sattelite_galaxies();
    std::cout << "Change type of the 1st (0th) sattelite galaxy." << std::endl;
    // Change satellite galaxy type
    g1.find_sattelite_galaxy(1)->change_type("Irr");
    g1.show_sattelite_galaxies();
  
    // End program
    std::cout << "Enter any key to exit";
    std::cin.ignore();
    std::cin.get();
    return 0;
}