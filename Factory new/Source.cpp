#include <iostream>
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;

//#define MIN_SIZE 50
//#define MAX_SIZE 800
//#define MIN_LINE_WIDTH 1
//#define MAX_LINE_WIDTH 25
//#define MAX_HORIZONTAL_RESOLUTION 800
//#define MAX_VERTICAL_RESOLUTION 600
namespace MyGeometry//CTRL K + S
{
	enum Color
	{
		RED = 0x000000FF,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		GREY = 0x00AAAAAA,
		YELLOW = 0x0000FFFF,
	};
	class Shape
	{
	protected://Нарушение инкапсуляции
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 800;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 25;
		static const int MAX_HORIZONTAL_RESOLUTION = 800;
		static const int MAX_VERTICAL_RESOLUTION = 600;

		unsigned int x;
		unsigned int y;
		unsigned int lineWidth;
		Color color;
	public:

		unsigned int getX() const
		{
			return x;
		}
		unsigned int getY() const
		{
			return y;
		}
		unsigned int getLineWidth() const
		{
			return lineWidth;
		}
		//Минимум 50, максимум 800
		unsigned int setSize(unsigned int size)
		{
			return size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		void setX(unsigned int x)
		{
			this->x = x < MAX_HORIZONTAL_RESOLUTION ? x : MAX_HORIZONTAL_RESOLUTION;
		}
		void setY(unsigned int y)
		{
			this->y = y < MAX_VERTICAL_RESOLUTION ? y : MAX_VERTICAL_RESOLUTION;
		}
		void setLineWidth(unsigned int width)
		{
			if (width < MIN_LINE_WIDTH)
			{
				width = MIN_LINE_WIDTH;
			}
			if (width > MAX_LINE_WIDTH)
			{
				width = MAX_LINE_WIDTH;
			}
			lineWidth = width;
		}
		//ctors
		Shape(unsigned int x, unsigned int y, Color color = GREY, unsigned int lineWidth = 5) : color(color)
		{
			setX(x);
			setY(y);
			setLineWidth(lineWidth);
		}
		virtual ~Shape()
		{

		}
		virtual double getArea() const = 0;
		virtual double getPerimeter() const = 0;
		virtual void draw() const = 0;
		virtual void info() const
		{
			cout << "Area: " << getArea() << endl
				<< "Perimeter: " << getPerimeter() << endl;
			draw();
		}
	};
	class Rectangle : public Shape
	{
		double width;
		double height;
	public:
		double getHeight() const
		{
			return height;
		}
		double getWidth() const
		{
			return width;
		}
		void setWidth(double width)
		{
			this->width = setSize(width);
		}
		void setHeight(double height)
		{
			this->height = setSize(height);
		}
		//ctors
		Rectangle(double width, double height, unsigned int x, unsigned int y, Color color, unsigned int lineWidth) :
			Shape(x, y, color, lineWidth)
		{
			setWidth(width);
			setHeight(height);
		}
		~Rectangle()
		{

		}
		//methods:
		double getArea() const override
		{
			return width * height;
		}
		double getPerimeter() const override
		{
			return (width + height) * 2;
		}
		void draw() const override
		{
			//HWND - handler to Window (Дескриптор окна нужен для того, чтобы обращаться к окну)
			HWND hwnd = GetConsoleWindow(); //Получаем дескриптор окна консоли
			//Для того, чтобы рисовать, нужен контекст устройства (Device context), он есть у каждого окна
			HDC hdc = GetDC(hwnd);
			//hdc - это то, на чем мы будем рисовать.
			//Теперь нужно то, чем мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, lineWidth, color);//Пен рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);//Кисть заливает фигуру
			//Теперь нужно выбрать, чем и на чем мы будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, x, y, x + width, y + height);//Рисуем фигуру с заданными параметрами
			//Удаляем все созданные объекты для того, чтобы освободить ресурсы машины
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);

		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << width << endl;
			cout << "Высота: " << height << endl;
			Shape::info();//Тут тоже происходит рисование, вызывать дроу в мейне на надо
		}
	};
	class Square : public Rectangle
	{
	public:
		Square(double side, unsigned int x, unsigned int y, Color color, unsigned int lineWidth) : Rectangle(side, side, x, y, color, lineWidth)
		{

		}
	};
	class Circle : public Shape
	{
		static const double PI;
		double radius;
	public:
		void setRadius(double radius)
		{
			this->radius = setSize(radius);
		}
		double getRadius() const
		{
			return radius;
		}
		double getArea() const override
		{
			return PI * radius * radius;
		}
		double getPerimeter() const override
		{
			return 2 * PI * radius;
		}
		double getDiameter() const
		{
			return 2 * radius;
		}
		void draw() const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN pen = CreatePen(PS_SOLID, lineWidth, color);
			HBRUSH brush = CreateSolidBrush(color);
			SelectObject(hdc, pen);
			SelectObject(hdc, brush);
			::Ellipse(hdc, x, y, x + getDiameter(), y + getDiameter());
			DeleteObject(pen);
			DeleteObject(brush);
			ReleaseDC(hwnd, hdc);
		}
		Circle(double radius, unsigned int x, unsigned int y, Color color, unsigned int lineWidth) : Shape(x, y, color, lineWidth)
		{
			setRadius(radius);
		}
		~Circle()
		{

		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "radius: " << getRadius() << endl;
			cout << "diameter: " << getDiameter() << endl;
			Shape::info();
		}
	};
	const double Circle::PI = 3.14159;
	class Triangle : public Shape
	{
		//Описать абстрактный класс
		static const double PI;
		double height;
		double base;
	public:
		void setHeight(unsigned int height)
		{
			this->height = setSize(height);
		}
		double getHeight() const
		{
			return height;
		}
		void setBase(double base)
		{
			this->base = setSize(base);
		}
		double getBase() const
		{
			return base;
		}
		//КООРДИНАТЫ ДЛЯ ВЕРХНЕЙ ВЕРШИНЫ
		Triangle(double base, double height, unsigned int x, unsigned int y, Color color, unsigned int lineWidth) : Shape(x, y, color, lineWidth)
		{
			//Конструктор будет работать именно с высотой и основанием, чтобы не было проблем с условием существования треугольника
			setBase(base);
			setHeight(height);	
		}
		double getArea() const override
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
		double getPerimeter() const
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
		void draw() const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN pen = CreatePen(PS_SOLID, lineWidth, color);
			HBRUSH brush = CreateSolidBrush(color);
			SelectObject(hdc,pen);
			SelectObject(hdc, brush);
			POINT vertices[3] = { {x, y}, {x - getLeftSide() * getLeftCos(), y + getLeftSide() * getLeftSin()}, {x + getRightSide() * getRightCos(), y + getRightSide() * getRightSin()}};
			::Polygon(hdc, vertices, 3);
			DeleteObject(pen);
			DeleteObject(brush);
			ReleaseDC(hwnd, hdc);
		}
		void info() const override = 0;
	};
	class IsoscelesTriangle : public Triangle
	{
	public:
		IsoscelesTriangle(double base, double height, unsigned int x, unsigned int y, Color color, unsigned int lineWidth) : Triangle(base, height, x, y, color, lineWidth)
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
	class EqulateralTriangle : public Triangle
	{
	public:
		EqulateralTriangle(double side, unsigned int x, unsigned int y, Color color, unsigned int lineWidth) : Triangle(side, (side * sqrt(3)) / 2.0, x, y, color, lineWidth)
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
		ScaleneTriangle(double base, double leftSide, double height, unsigned int x, unsigned int y, Color color, unsigned int lineWidth) : Triangle(base, height, x, y, color, lineWidth)
		{
			setLeftSide(leftSide);
		}
		void setLeftSide(double left)
		{
			leftSide = setSize(left);
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
	//Если высота равна половине основания в равнобедренном треугольнике, то он прямоугольный. Если левая сторона равна высоте в разностороннем треугольнике, то он прямоугольный.
	//Его можно получить в разных положениях, создавая объекты разных типов, а потому, думаю, еще один класс будет лишним.
	const double Triangle::PI = 3.14159;
}

void main()
{
	setlocale(LC_ALL, "");
	MyGeometry::Square square(100, 420, 100, MyGeometry::Color::GREY, 8);
	square.info();
	MyGeometry::Circle circle(50, 540, 100, MyGeometry::Color::GREEN, 8);
	circle.info();
	MyGeometry::IsoscelesTriangle iTriangle(100, 50, 700, 100, MyGeometry::Color::BLUE, 8);
	iTriangle.info();
	MyGeometry::EqulateralTriangle eTriangle(100, 420, 250, MyGeometry::Color::YELLOW, 8);
	eTriangle.info();
	MyGeometry::ScaleneTriangle sTriangle(200, 100, 100, 600, 300, MyGeometry::Color::RED, 8);
	sTriangle.info();
	//DONE
	//	1. Добавить квадрат;
	//	2. Добавить круг;
	//	3. Добавить иерархию треугольников;
}