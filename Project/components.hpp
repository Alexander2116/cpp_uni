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
            double _frequency = 1;
            complex _impedance;
        public:
            Component();
            ~Component();
            virtual complex GetImpedance();
            virtual double GetPhaseDifference();
            virtual double GetImpedanceMagnitude();
            virtual std::string GraphicRepresentation()=0; // Must be specific for each derived component
            virtual void SetFrequency(double frequency);
            virtual double GetFrequency();
            virtual void Info()=0;
            virtual std::string CompName()=0;
    };

    class Resistor: public Component{
        private:
            double _resistivity;
            static int _obj_count;
        public:
            Resistor(double resistivity);
            ~Resistor();
            std::string GraphicRepresentation();
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
            void Info();
            int GetCount();
            std::string CompName();
    };

    class EmptyComp: public Component{
        public:
            EmptyComp();
            std::string GraphicRepresentation();
            void Info();
            std::string CompName();
    };

    
}

#endif /* !COMPONENTS_H */