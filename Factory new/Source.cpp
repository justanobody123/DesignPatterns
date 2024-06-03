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
			/*for (size_t i = 0; i < height; i++)
			{
				for (size_t j = 0; j < width; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}*/
			//HWND - handler to Window (Дескриптор окна нужен для того, чтобы обращаться к окну)
			HWND hwnd = GetConsoleWindow(); //Получаем дескриптор окна консоли
			this;
			//Для того, чтобы рисовать, нужен контекст устройства (Device context), он есть у каждого окна
			HDC hdc = GetDC(hwnd);
			//hdc - это то, на чем мы будем рисовать.
			//Теперь нужно то, чем мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, lineWidth, color);//Пен рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);//Кисть заливает фигуру
			//Теперь нужно выбрать, чем и на чем мы будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, x, y, x + width, y + height);
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
			Shape::info();
		}
	};
}
void main()
{
	setlocale(LC_ALL, "");
	MyGeometry::Rectangle rect(100, 50, 100, 200, MyGeometry::Color::RED, 8);
	rect.info();
	rect.draw();
	//TODO
	//1. Добавить квадрат;
	// 2. Добавить круг;
	// 3. Добавить иерархию треугольников
	//
}