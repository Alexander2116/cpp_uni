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
            virtual double GetPhaseDifference()=0;
            virtual double GetImpedanceMagnitude();
            virtual std::string GraphicRepresentation()=0; // Must be specific for each derived component
            virtual void SetFrequency(double frequency);
            virtual double GetFrequency();
            virtual void Info()=0;
    };

    class Resistor: public Component{
        private:
            double _resistivity;
        public:
            Resistor(double resistivity);
            double GetPhaseDifference();
            std::string GraphicRepresentation();
            void Info();
    };

    class Capacitor: public Component{
        private:
            double _capacitance;
        public:
            Capacitor(double capacitance);
            double GetPhaseDifference();
            std::string GraphicRepresentation();
            void Info();
    };

    class Inductor: public Component{
        private:
            double _inductance;
        public:
            Inductor(double inductance);
            double GetPhaseDifference();
            std::string GraphicRepresentation();
            void Info();
    };

    class AC_Source: public Component{
        private:
            double _frequency;
            double _voltage;
            double _current;
        public:
            AC_Source(double vol, double freq, double cur);
            double GetPhaseDifference();
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