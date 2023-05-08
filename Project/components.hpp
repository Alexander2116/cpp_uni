/*============================================================
** UTF-8, Win32
**
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: 
**
** Classes: Component(), Resistor(double), Capacitor(double), Inductor(double), EmptyCom()
**
** Comments: 
**
** Date:  15 April 2023
**
===========================================================*/

#ifndef COMPONENTS_H // include guard
#define COMPONENTS_H

#include "complex.hpp"

namespace myComponents{
    using namespace myComplex;
    
    class Component{
        protected:
            double _frequency = 1; // Frequency, can be changed anytime
            complex _impedance; // current component's impedance
        public:
            Component();
            ~Component();
            virtual complex GetImpedance(); // Return current impedance
            virtual double GetPhaseDifference(); // Return phase difference - impedance's argument
            virtual double GetImpedanceMagnitude(); // Return impedance magnitude - impedance's modulus
            virtual std::string GraphicRepresentation()=0; // Graphics must be specific for each derived component
            virtual void SetFrequency(double frequency)=0; // Sets component's frequency and updates impedance
            virtual double GetFrequency(); // General function to return component's frequency
            virtual void Info()=0; // Provides printed info for each component
            virtual std::string CompName()=0; // Specifies component name
    };

    class Resistor: public Component{
        private:
            double _resistivity;
            static int _obj_count;
        public:
            Resistor(double resistivity);
            ~Resistor();
            std::string GraphicRepresentation();
            void SetFrequency(double frequency);
            void Info();
            int GetCount(); // Return the number of created objects of this type
            std::string CompName();
    };

    class Capacitor: public Component{
        private:
            double _capacitance;
            static int _obj_count;
        public:
            Capacitor(double capacitance);
            ~Capacitor();
            std::string GraphicRepresentation();
            void SetFrequency(double frequency);
            void Info();
            int GetCount();
            std::string CompName();
    };

    class Inductor: public Component{
        private:
            double _inductance;
            static int _obj_count;
        public:
            Inductor(double inductance);
            ~Inductor();
            std::string GraphicRepresentation();
            void SetFrequency(double frequency);
            void Info();
            int GetCount();
            std::string CompName();
    };

    class EmptyComp: public Component{
        public:
            EmptyComp();
            std::string GraphicRepresentation();
            void SetFrequency(double frequency);
            void Info();
            // Doesn't require GetCount() - why would somebody want to know how many blank spaces there are?
            std::string CompName();
    };

    
}

#endif /* !COMPONENTS_H */