#ifndef COMPONENTS_H // include guard
#define COMPONENTS_H

#include "complex.hpp"

namespace myComponents{
    using namespace myComplex;
    
    class Component{
        private:
            int test = 0;
        public:
            Component();
            virtual ~Component();
            virtual complex Impedance()=0;
            virtual std::string GraphicRepresentation()=0;
    };

    class Resistor: public Component{
        private:
            double _resistivity;
        public:
            Resistor(double resistivity);
            complex Impedance();
            std::string GraphicRepresentation();
    };

    class Capacitor: public Component{
        private:
            double _capacitance;
        public:
            Capacitor(double capacitance);
            complex Impedance();
            std::string GraphicRepresentation();
    };

    class Inductor: public Component{
        private:
            double _inductance;
        public:
            Inductor(double inductance);
            complex Impedance();
            std::string GraphicRepresentation();
    };

    class AC_Source: public Component{
        private:
            double _frequency;
            double _voltage;
            double _current;
        public:
            AC_Source(double vol, double freq, double cur);
            std::string GraphicRepresentation();
    };
}

#endif /* !COMPONENTS_H */