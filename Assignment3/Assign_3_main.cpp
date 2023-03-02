/*============================================================
** UTF-8
**
** Assignment 3  (Deadline: 03/03/2023)
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: Demonstrate usefullness of the classes
**        : Create a "galaxy" class
**
** Classes: galaxy(string, double, double, double)
**
** Comments: I'm happy I'm not doing astro
**
** Date:  2 March 2023
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
    std::string hubble_type{""}; // allow E0-7, S0, SBa 
    double redshift{0.0}; // 0-10
    double m_tot{0.0}; // range E7-E12 of solar mass (so variable of size E5 -> ~2^16 <-> ~2^17)
    double stellar_mass_fraction{0.0}; // f = M/m_tot

    std::vector<galaxy> sattelite_galaxy;
    std::vector<galaxy> empty_val; // empty vector, used only to return if inserted i-th item of sattelite_galaxy is out of size.

    //const solar_mass = 1.989* std::pow(10,30); // kg

  public:
    galaxy() = default;
    // Parameterized constuctor
    galaxy(std::string hub_type, double red_shift, double mass, double s_m_frac){
      hubble_type = hub_type;
      redshift = red_shift;
      m_tot = mass; // in units of solar masses
      stellar_mass_fraction = s_m_frac; // stellar mass / total mass
    }

    // Destructor
    ~galaxy(){
      hubble_type.erase();
      redshift = (double)NULL;
      m_tot  = (double)NULL;
      stellar_mass_fraction  = (double)NULL;
      sattelite_galaxy.clear();
      empty_val.clear();
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
    // Change galaxy's redshift
    void change_redshift(double red) { 
        redshift = red;
    }
    // Change galaxy's mass
    void change_type(double m) { 
        m_tot = m;
    }
        // Change galaxy's mass
    void change_stellar_fraction(double frac) { 
        stellar_mass_fraction = frac;
    }
    // Prototype for function to print out an object's data
    void print_data(){
      std::cout << "Hubble type: " << hubble_type << ";  " << "redshift: " << redshift << ";  " << "total mass: " << m_tot << std::endl;
    };

    // Add satellite galaxy
    // I assume satellite galaxy can be described with the same parameters as a normal galaxy
    void add_satellite_galaxy(std::string hub_type, double red_shift, double mass, double s_m_frac){
      galaxy sat_gal(hub_type, red_shift, mass, s_m_frac);
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
      if(i <= sattelite_galaxy.size()){
        return &sattelite_galaxy[i];
      }
      else{
        // Just to make sure there is only 1 element in this vector
        if(empty_val.empty()){
          empty_val.push_back(galaxy("a",1,1,1));
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
    galaxy gdef;
    gdef.print_data();
    // Should be create a empty object. 
    gdef.change_type("Irr-test");
    gdef.print_data();
    std::cout << std::endl;
    // Deconstuctor (expect empty hubble type)
    gdef.~galaxy();
    gdef.print_data();
    std::cout << std::endl;
    // Example using parameterised constructor
    galaxy g1("Irr", 2,pow(10,10),0.05);
    // print out data
    g1.print_data();
    // Get and print out stellar mass
    std::cout << "Stellar mass: " << g1.stellar_mass() << std::endl;
    // Change Hubble type from Irr to S0
    g1.change_type("S0");
    g1.print_data();

    // Add satellite galaxies
    g1.add_satellite_galaxy("S1", 4, pow(10,7),0.01);
    g1.add_satellite_galaxy("S2", 5, pow(10,8),0.02);
    g1.show_sattelite_galaxies();

    // Change satellite galaxy type
    std::cout << "Change type of the 2nd sattelite galaxy." << std::endl;
    g1.find_sattelite_galaxy(1)->change_type("Irr");
    g1.show_sattelite_galaxies();
  
    // End program
    std::cout << std::endl << "Program exit. Enter any key to exit ";
    std::cin.ignore();
    std::cin.get();
    return 0;
}