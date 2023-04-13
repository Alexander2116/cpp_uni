#ifndef COMPONENTS_H // include guard
#define COMPONENTS_H

#include "complex.hpp"

namespace myComponents{
    using namespace myComplex;
    
    class Component{
        protected:
            double frequency = 0;
        public:
            Component();
            ~Component();
            virtual complex GetImpedance()=0;
            virtual double GetPhaseDifference()=0;
            virtual double GetImpedanceMagnitude()=0;
            virtual std::string GraphicRepresentation()=0;
            virtual double SetFrequency()=0;
            virtual double GetFrequency()=0;
    };

    class Resistor: public Component{
        private:
            double _resistivity;
        public:
            Resistor(double resistivity);
            complex GetImpedance();
            double GetPhaseDifference();
            double GetImpedanceMagnitude();
            std::string GraphicRepresentation();
            double SetFrequency();
            double GetFrequency();
    };

    class Capacitor: public Component{
        private:
            double _capacitance;
        public:
            Capacitor(double capacitance);
            complex GetImpedance();
            double GetPhaseDifference();
            double GetImpedanceMagnitude();
            std::string GraphicRepresentation();
            double SetFrequency();
            double GetFrequency();
    };

    class Inductor: public Component{
        private:
            double _inductance;
        public:
            Inductor(double inductance);
            complex GetImpedance();
            double GetPhaseDifference();
            double GetImpedanceMagnitude();
            std::string GraphicRepresentation();
            double SetFrequency();
            double GetFrequency();
    };

    class AC_Source: public Component{
        private:
            double _frequency;
            double _voltage;
            double _current;
        public:
            AC_Source(double vol, double freq, double cur);
            complex GetImpedance();
            double GetPhaseDifference();
            double GetImpedanceMagnitude();
            std::string GraphicRepresentation();
            double SetFrequency();
            double GetFrequency();
    };
}

#endif /* !COMPONENTS_H */