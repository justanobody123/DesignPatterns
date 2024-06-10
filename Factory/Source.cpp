﻿#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
#include<ctime>
using namespace std;

//#define MIN_SIZE		50
//#define MAX_SIZE		800
//#define MIN_LINE_WIDTH	1
//#define MAX_LINE_WIDTH	25
//
//#define MAX_HORIZONTAL_RESOLUTION	800
//#define MAX_VERTICAL_RESOLUTION		600

namespace MyGeometry
{
	/*enum Color
	{
		RED = 0x000000FF,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		GREY = 0x00AAAAAA,
		YELLOW = 0x0000FFFF
	};*/
	/*class Color
	{

		int red;
		int green;
		int blue;
	public:
		static const int MIN_COLOR = 0;
		static const int MAX_COLOR = 255;
		int check_color(int value)
		{
			return value < MIN_COLOR ? MIN_COLOR : value > MAX_COLOR ? MAX_COLOR : value;
		}
		void set_red(int value)
		{
			red = check_color(value);
		}
		int get_red() const
		{
			return red;
		}
		int get_green() const
		{
			return green;
		}
		int get_blue() const
		{
			return blue;
		}
		void set_green(int value)
		{
			green = check_color(value);
		}
		void set_blue(int value)
		{
			blue = check_color(value);
		}
		void set_color(int red, int green, int blue)
		{
			set_red(red);
			set_blue(blue);
			set_green(green);
		}
		Color()
		{
			red = 0;
			green = 0;
			blue = 0;
		}
		Color(int red, int green, int blue)
		{
			set_color(red, green, blue);
		}
		~Color()
		{

		}
	};*/
#define SHAPE_TAKE_PARAMETERS unsigned int x, unsigned int y, unsigned int line_width, COLORREF color
#define SHAPE_GIVE_PARAMETERS x, y, line_width, color
	class Shape
	{
	protected:
		unsigned int x;
		unsigned int y;
		unsigned int line_width;
		COLORREF color;
	public:

		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 300;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 25;
		static const int MAX_HORIZONTAL_RESOLUTION = 800;
		static const int MAX_VERTICAL_RESOLUTION = 600;


		unsigned int get_x()const
		{
			return x;
		}
		unsigned int get_y()const
		{
			return y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		unsigned int set_size(unsigned int size)
		{
			return
				size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		void set_color(COLORREF color)
		{
			this->color = color;
		}

		void set_x(unsigned int x)
		{
			this->x = x < MAX_HORIZONTAL_RESOLUTION ? x : MAX_HORIZONTAL_RESOLUTION;
		}
		void set_y(unsigned int y)
		{
			this->y = y < MAX_VERTICAL_RESOLUTION ? y : MAX_VERTICAL_RESOLUTION;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

		//				Constructors:

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_x(x);
			set_y(y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		//				Methods:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		void draw() const
		{
			//HWND - Handler to Window (Дескриптор окна, нужен для того чтобы обращаться в ону)
			HWND hwnd = GetConsoleWindow();	//Получаем дескриптор окна консоли.
			//HWND hwnd = GetDesktopWindow();	//Получаем дескриптор окна консоли.

			//Для того чтобы рисовать, нужен контекст устройства (Device Context), он есть каждого окна
			HDC hdc = GetDC(hwnd);
			//hdc - это то, на чем мы будем рисовать.

			//Теперь нужно то, чем мы будем рисовать:

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//Карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);	//Кисть заливает фигуру

			//Теперь нужно выбрать чем и на чем будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//Тут вызываем оверрайд метод
			drawShape(hdc);

			//Удаляем все созданные объекты для того чтобы освободить ресурсы:

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		virtual void drawShape(HDC& hdc) const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};
	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		void set_width(double width)
		{
			this->width = set_size(width);
		}
		void set_height(double height)
		{
			this->height = set_size(height);
		}

		//				Constructors:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}

		//				Methods:
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void drawShape(HDC& hdc)const override
		{
			::Rectangle(hdc, x, y, x + width, y + height);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << width << endl;
			cout << "Высота: " << height << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Circle : public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void set_radius(double radius)
		{
			this->radius = set_size(radius);
		}
		//				Constructors:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}

		void drawShape(HDC& hdc)const override
		{
			::Ellipse(hdc, x, y, x + get_diameter(), y + get_diameter());
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << get_radius() << endl;
			cout << "Диаметр: " << get_diameter() << endl;
			Shape::info();
		}
	};
	class Triangle : public Shape
	{
		//Описать абстрактный класс
		static const double PI;
		double height;
		double base;
	public:
		void setHeight(unsigned int height)
		{
			this->height = set_size(height);
		}
		double getHeight() const
		{
			return height;
		}
		void setBase(double base)
		{
			this->base = set_size(base);
		}
		double getBase() const
		{
			return base;
		}
		//КООРДИНАТЫ ДЛЯ ВЕРХНЕЙ ВЕРШИНЫ
		Triangle(double base, double height, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
		{
			//Конструктор будет работать именно с высотой и основанием, чтобы не было проблем с условием существования треугольника
			setBase(base);
			setHeight(height);
		}
		double get_area() const override
		{
			return height * base / 2;
		}
		//Актуально для равностороннего и равнобедренного, требуется переопределение для разностороннего
		virtual double getLeftSide() const
		{
			return sqrt(pow(base / 2, 2) + pow(height, 2));
		}
		//Актуально для равностороннего и равнобедренного, требуется переопределение для разностороннего
		virtual double getRightSide() const
		{
			return getLeftSide();
		}
		double get_perimeter() const
		{
			return base + getLeftSide() + getRightSide();
		}
		double getLeftSin() const
		{
			return height / getLeftSide();
		}
		double getRightSin() const
		{
			return height / getRightSide();
		}
		double getLeftAngle() const
		{
			return asin(getLeftSin()) * 180 / PI;
		}
		double getRightAngle() const
		{
			return asin(getRightSin()) * 180 / PI;
		}
		double getTopAngle() const
		{
			return 180 - getLeftAngle() - getRightAngle();
		}
		double getLeftCos() const
		{
			double radians = getLeftAngle() * (PI / 180.0);
			return cos(radians);
		}
		double getRightCos() const
		{
			double radians = getRightAngle() * (PI / 180.0);
			return cos(radians);
		}
		void drawShape(HDC& hdc) const override
		{
			POINT vertices[3] = { {x, y}, {x - getLeftSide() * getLeftCos(), y + getLeftSide() * getLeftSin()}, {x + getRightSide() * getRightCos(), y + getRightSide() * getRightSin()} };
			::Polygon(hdc, vertices, 3);
		}
		void info() const override = 0;
	};
	class IsoscelesTriangle : public Triangle
	{
	public:
		IsoscelesTriangle(double base, double height, SHAPE_TAKE_PARAMETERS) : Triangle(base, height, SHAPE_GIVE_PARAMETERS)
		{

		}
		void info() const override
		{
			cout << typeid(*this).name() << endl
				<< "Основание и верхний угол: " << getBase() << " " << getTopAngle() << "°" << endl
				<< "Левая сторона: " << getLeftSide() << " " << getLeftAngle() << "°" << endl
				<< "Правая сторона: " << getRightSide() << " " << getRightAngle() << "°" << endl;
			Shape::info();
		}
	};
	//По факту, равносторонний треугольник это частный случай равнобедренного. Можно было бы унаследоваться от равнобедренного, но никакой разницы не будет. Иду напрямую, чтобы избежать цепного вызова конструкторов.
	class EquilateralTriangle : public Triangle
	{
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) : Triangle(side, (side * sqrt(3)) / 2.0, SHAPE_GIVE_PARAMETERS)
		{

		}
		void info() const override
		{
			cout << typeid(*this).name() << endl
				<< "Основание и верхний угол: " << getBase() << " " << getTopAngle() << "°" << endl
				<< "Левая сторона: " << getLeftSide() << " " << getLeftAngle() << "°" << endl
				<< "Правая сторона: " << getRightSide() << " " << getRightAngle() << "°" << endl;
			Shape::info();
		}
	};
	class ScaleneTriangle : public Triangle
	{
		double leftSide;
	public:
		ScaleneTriangle(double base, double leftSide, double height, SHAPE_TAKE_PARAMETERS) : Triangle(base, height, SHAPE_GIVE_PARAMETERS)
		{
			setLeftSide(leftSide);
		}
		void setLeftSide(double left)
		{
			leftSide = set_size(left);
			if (leftSide < getHeight())
			{
				cout << "Эта сторона не может быть меньше высоты, проведенной к основанию. leftSide исправлено на " << getHeight() << endl;
				leftSide = getHeight();
			}
		}
		double getLeftSide() const override
		{
			return leftSide;
		}
		double getRightSide() const override
		{
			//Ищем катет основания левого треугольника, вычитаем из основания катет, получаем оставшуюся часть. Ищем по теореме пифагора правую часть
			double theta = sqrt(leftSide * leftSide - getHeight() * getHeight());
			return sqrt(getHeight() * getHeight() + (getBase() - theta) * (getBase() - theta));
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl
				<< "Основание и верхний угол: " << getBase() << " " << getTopAngle() << "°" << endl
				<< "Левая сторона: " << getLeftSide() << " " << getLeftAngle() << "°" << endl
				<< "Правая сторона: " << getRightSide() << " " << getRightAngle() << "°" << endl;
			Shape::info();
		}
	};
	//А вот что делать с прямоугольным — я не знаю. Чаще всего это разносторонний треугольник, но бывают и равнобедренные прямоугольные треугольники.
	//Если высота равна половине основания в равнобедренном треугольнике, то он прямоугольный. Если левая или правая сторона равна высоте в разностороннем треугольнике, то он прямоугольный.
	//Его можно получить в разных положениях, создавая объекты разных типов, а потому, думаю, еще один класс будет лишним.
	const double Triangle::PI = 3.14159;
	//Пришлось вынести енам в подпространство имен, чтобы избежать конфликтов имен
	namespace ShapeTypes
	{
		enum Shapes
		{
			Rectangle, Square, Circle, IsoscelesTriangle, EqulateralTriangle, ScaleneTriangle
		};
	};
	class ShapeFactory {
	public:
		static Shape* createShape(ShapeTypes::Shapes type)
		{
			Shape* shape = nullptr;
#define SHAPE_PARAMETERS rand() % Shape::MAX_HORIZONTAL_RESOLUTION, rand() % Shape::MAX_VERTICAL_RESOLUTION,rand() % Shape::MAX_LINE_WIDTH,RGB(rand(), rand(), rand())
			switch (type)
			{
			case 0:	shape = new Rectangle(rand() % Shape::MAX_SIZE, rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
			case 1: shape = new Square(rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
			case 2: shape = new Circle(rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
			case 3: shape = new IsoscelesTriangle(rand() % Shape::MAX_SIZE, rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
			case 4: shape = new EquilateralTriangle(rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
			case 5: shape = new ScaleneTriangle(rand() % Shape::MAX_SIZE, rand() % Shape::MAX_SIZE, rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
			}
			return shape;
		}
	};
	class ShapeBuilder
	{
	public:
		ShapeBuilder() {}
		Circle* build_circle() {
			return new Circle(100, 400, 400, 8, RGB(255, 255, 255));
		}
		Square* build_square() {
			return new Square(100, 400, 400, 8, RGB(255, 255, 255));
		}
		Rectangle* build_rectangle() {
			return new Rectangle(150, 75, 400, 400, 8, RGB(255, 255, 255));
		}
		IsoscelesTriangle* build_isosceles_triangle() {
			return new IsoscelesTriangle(80, 100, 400, 400, 8, RGB(255, 255, 255));
		}
		EquilateralTriangle* build_equilateral_triangle() {
			return new EquilateralTriangle(100, 400, 400, 8, RGB(255, 255, 255));
		}
		ScaleneTriangle* build_scalene_triangle() {
			return new ScaleneTriangle(80, 120, 60, 400, 400, 8, RGB(255, 255, 255));
		}
		ScaleneTriangle* build_right_triangle()
		{
			return new ScaleneTriangle(60, 100, 100, 400, 400, 8, RGB(255, 255, 255));
		}
	};
}

//#define USING_ENUM_COLOR
//#define USING_COLORREF

void main()
{
	setlocale(LC_ALL, "");
#ifdef USING_ENUM_COLOR
	MyGeometry::Rectangle rect(100, 50, 350, 100, 8, MyGeometry::Color::RED);
	/*cout << "Ширина прямоугольника: " << rect.get_width() << endl;
	cout << "Высота прямоугольника: " << rect.get_height() << endl;
	cout << "Площадь прямоугольника: " << rect.get_area() << endl;
	cout << "Периметр прямоугольника: " << rect.get_perimeter() << endl;
	rect.draw();*/
	rect.info();

	MyGeometry::Square square(44, 550, 100, 5, MyGeometry::Color::GREY);
	square.info();

	MyGeometry::Circle circle(75, 750, 100, 5, MyGeometry::Color::YELLOW);
	circle.info();
#endif // ENUM_COLOR

#ifdef USING_COLORREF
	MyGeometry::Rectangle rect(100, 50, 350, 100, 8, RGB(255, 0, 0));
	/*cout << "Ширина прямоугольника: " << rect.get_width() << endl;
	cout << "Высота прямоугольника: " << rect.get_height() << endl;
	cout << "Площадь прямоугольника: " << rect.get_area() << endl;
	cout << "Периметр прямоугольника: " << rect.get_perimeter() << endl;
	rect.draw();*/
	rect.info();

	MyGeometry::Square square(44, 550, 100, 5, RGB(0, 0, 255));
	square.info();

	MyGeometry::Circle circle(75, 750, 100, 5, RGB(255, 255, 0));
	circle.info();
#endif // USING_COLORREF

	srand(time(NULL));
	const int n = 15;
	MyGeometry::Shape* shape[n]{};
	/*for (int i = 0; i < n; i++)
	{
		shape[i] = MyGeometry::ShapeFactory::createShape(static_cast<MyGeometry::ShapeTypes::Shapes>(rand() % 6));
	}

	for (int i = 0; i < n; i++)
	{
		shape[i]->draw();
		Sleep(500);
	}
	for (int i = 0; i < n; i++)delete[] shape[i];*/
	//Сделала енам, который позволяет управлять фабрикой без магических чисел. Если надо рандомно генерировать объект, то просто приведем инт к енаму с помощью статик каста
	// 
	//Билдер
	MyGeometry::ShapeBuilder builder;
	MyGeometry::Shape* pointer = builder.build_isosceles_triangle();
	pointer->info();
	delete pointer;
}