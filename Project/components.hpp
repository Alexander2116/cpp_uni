#ifndef COMPONENTS_H // include guard
#define COMPONENTS_H

#include "complex.hpp"

namespace myComponents{
    using namespace myComplex;
    
    class Component{
        protected:
            double _frequency = 0;
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
        public:
            Resistor(double resistivity);
            std::string GraphicRepresentation();
            void Info();
            std::string CompName();
    };

    class Capacitor: public Component{
        private:
            double _capacitance;
        public:
            Capacitor(double capacitance);
            std::string GraphicRepresentation();
            void Info();
            std::string CompName();
    };

    class Inductor: public Component{
        private:
            double _inductance;
        public:
            Inductor(double inductance);
            std::string GraphicRepresentation();
            void Info();
            std::string CompName();
    };

    class EmptyComp: public Component{
        public:
            EmptyComp();
            std::string GraphicRepresentation();
            void Info();
            std::string CompName();
    };

    class AC_Source: public Component{
        private:
            double _frequency;
            double _voltage;
            double _current;
        public:
            AC_Source(double vol, double freq, double cur);
            std::string GraphicRepresentation();
            void Info();
    };
    // alternative
    /*
    struct AC_Source : public Component
    {
            double _frequency;
            double _voltage;
            double _current;
            AC_Source(double v, double i, double f);
    };*/
    
}

#endif /* !COMPONENTS_H */