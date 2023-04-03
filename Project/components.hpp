#ifndef COMPONENTS_H // include guard
#define COMPONENTS_H

namespace myComponents{

    class Component{

        public:
            Component();
            virtual double Impedance()=0;
            virtual void GraphicRepresentation()=0;
    };

    class Resistor: public Component{

        public:
            Resistor();
            double Impedance();
    };

    class Capacitor: public Component{

        public:
            Capacitor();
            double Impedance();
    };

    class Inductor: public Component{
        private:
            double _inductance;
        public:
            Inductor(double ind);
            double Impedance();
    };

    class AC_Source{
        private:
            double _frequency = 0;
            double _voltage = 0;
            double _current = 0;
        public:
            AC_Source(double vol, double freq, double cur);
    };
}

#endif /* !COMPONENTS_H */