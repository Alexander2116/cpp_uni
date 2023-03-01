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
    void change_type(std::string new_type) { }
    // Prototype for function to print out an object's data
    void print_data();

    // Add satellite galaxy
    // I assume satellite galaxy can be described with the same parameters and a normal galaxy
    void add_satellite_galaxy(std::string hub_type, double red_shift, double mass){
      galaxy sat_gal(hub_type, red_shift, mass);
      sattelite_galaxy.push_back(sat_gal);
    }
    void show_satelilite_galaxies(){
      for(int i = 0; i < sattelite_galaxy.size(); i++){
        std::cout << i << ": " << sattelite_galaxy[i].get_hubble_type() << std::endl;
      }
    }
    // Find a sattelite galaxy by putting a hubble_type
    std::vector<galaxy> find_sattelite_galaxy(int i){
      // Linear search
      if(i <= sattelite_galaxy.size()){
        return sattelite_galaxy[i];
      }
      else{
        galaxy no_gal;
        std::cout << "This object is not present" << std::endl;
        return no_gal
      }
    }

};

//=== defined functions ===


//=== main ===
int main(){
  // Example using default constructor
  galaxy g1("test", 2,2);

  g1.add_satellite_galaxy("test1", 2,2);
  g1.add_satellite_galaxy("test2", 2,2);
  g1.show_satelilite_galaxies();
  std::cout << g1.get_hubble_type() << std::endl;
  // Example using parameterised constructor

  // print out data

  // Get and print out stellar mass

  // Change Hubble type from Irr to S0

  // Add satellite galaxies
	
    // End program
    std::cout << "Enter any key to exit";
    std::cin.ignore();
    std::cin.get();
    return 0;
}