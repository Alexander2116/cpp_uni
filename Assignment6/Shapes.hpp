/*============================================================
** UTF-8, Win32
**
** Assignment 5  (Deadline: 21/04/2023)
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: 
**
** Classes: Shape2D, Rectangle, Square, Ellipse, Circle
**		  : Shape3D, Cuboid, Cube, Ellipsoid, Sphere
**		  : Prism
**
** Comments : Formulas for area/volume: https://byjus.com/maths/area-of-shapes/
**			:							https://byjus.com/maths/3d-shapes/
**
** Date:  31 March 2023
**
===========================================================*/
#ifndef SHAPES_H // include guard
#define SHAPES_H

//=== includes ===
#include<iostream>
#include<cmath>

namespace myShapes{
	//=== defined classes ===
	// ** 2D Shapes **
	class Shape2D {
		protected:
			double ar; // area
			std::string shape_name;
			static int n_objects; 
		public:
			// I didn't find a need to create a purely virtual function
			Shape2D(std::string shape_type);
			virtual ~Shape2D();
			virtual double GetArea(); // return area
			virtual void Info(); // general info about this shape: type + area
			virtual void NumberShapeInfo(); // general info about the total number of shapes
	};
	//int Shape2D::n_objects{0};

	class Rectangle : public Shape2D{
		private:
			static int count;
		public:
			Rectangle(double a_side_length, double b_side_length);
			~Rectangle();
			void CountInfo(); // only how many objects of this specific shape exist
	};

	class Square : public Shape2D{
		private:
			static int count;
		public:
			Square(double side_length); 
			~Square();
			void CountInfo();
	};

	class Ellipse : public Shape2D{
		private:
			static int count;
		public:
			// a = 1/2 minor axis, b = 1/2 major axis
			Ellipse(double minor_axis, double major_axis); 
			~Ellipse();
			void CountInfo();
	};

	class Circle : public Shape2D{
		private:
			static int count;
		public:
			Circle(double radius);
			~Circle();
			void CountInfo();
	};

	// ** 3D Shapes **
	class Shape3D {
		protected:
			double vol; // volume
			std::string shape_name;
			static int n_objects;
		public:
			Shape3D(std::string shape_type);
			virtual ~Shape3D();
			virtual double GetVolume(); // return area
			virtual void ShapeInfo(); // general info about the current shape
	};

	class Cuboid : public Shape3D{
		private:
			static int count;
		public:
			Cuboid(double hight, double length, double width);
			~Cuboid();
			void Info();
	};
	class Cube : public Shape3D{
		private:
			static int count;
		public:
			Cube(double a);
			~Cube();
			void Info();
	};
	class Ellipsoid : public Shape3D{
		private:
			static int count;
		public:
			Ellipsoid(double a, double b, double c);
			~Ellipsoid();
			void Info();
	};
	class Sphere : public Shape3D{
		private:
			static int count;
		public:
			Sphere(double radius);
			~Sphere();
			void Info();
	};
}
#endif /* !SHAPES_H */