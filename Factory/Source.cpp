#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <vector>
#define MAX_LENGTH 10
#define MIN_LENGTH 1
#define CONSOLE_WIDTH 120
#define CONSOLE_HEIGHT 30
#define PI 3.14159
using std::cout;
using std::cin;
using std::endl;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };//инициализируем передаваемыми значениями объект координат
	SetConsoleCursorPosition(hStdOut, myCoords);
}
class Figure
{
protected:
	double area;
	double perimeter;
	int x; 
	int y;
	virtual void setArea() = 0;
	virtual void setPerimeter() = 0;
public:
	virtual void printInfo() const = 0;
	virtual void printFigure() const = 0;
	virtual void setPosition(int x, int y) = 0;
	const double& getPerimeter() const
	{
		return perimeter;
	}
	const double& getArea() const
	{
		return area;
	}
};
class MyRectangle : public Figure
{
protected:
	int width;
	int height;
	double diagonal;
	int x;
	int y;
	void setDiagonal()
	{
		diagonal = sqrt(width * width + height * height);
	}
	void setArea() override
	{
		area = width * height;
	}
	void setPerimeter() override
	{
		perimeter = (width + height) * 2;
	}
	void setHeight(int value)
	{
		height = value < MIN_LENGTH ? MIN_LENGTH :
			value > MAX_LENGTH ? MAX_LENGTH :
			value;
	}
	void setWidth(int value)
	{
		width = value < MIN_LENGTH ? MIN_LENGTH :
			value > MAX_LENGTH ? MAX_LENGTH :
			value;
	}
public:
	MyRectangle()
	{
		setSize(MIN_LENGTH + rand() % (MAX_LENGTH - MIN_LENGTH + 1), MIN_LENGTH + rand() % (MAX_LENGTH - MIN_LENGTH + 1));
		setPosition(rand() % (CONSOLE_WIDTH - width), rand() % (CONSOLE_HEIGHT - height));
	}
	MyRectangle(int width, int height, int x, int y)
	{
		setSize(width, height);
		setPosition(x, y);
	}
	void setSize(int width, int height)
	{
		setWidth(width);
		setHeight(height);
		setPerimeter();
		setArea();
		setDiagonal();
	}
	const int& getWidth() const
	{
		return width;
	}	
	const int& getHeight() const
	{
		return height;
	}
	const double& getDiagonal() const
	{
		return diagonal;
	}
	void setPosition(int x, int y) override
	{
		this->x = x < 0 ? 0 :
			x > CONSOLE_WIDTH - width ? CONSOLE_WIDTH - width :
			x;
		this->y = y < 0 ? 0 :
			y > CONSOLE_HEIGHT - height ? CONSOLE_HEIGHT - height :
			y;
	}
	void printInfo() const override
	{
		cout << "Rectangle:" << endl
			<< "width = " << width << endl
			<< "height = " << height << endl
			<< "diagonal = " << diagonal << endl
			<< "area = " << area << endl
			<< "perimeter = " << perimeter << endl << endl;
	}
	void printFigure() const override
	{
		for (size_t i = 0; i < height; i++)
		{
			setCursor(x, y + i);
			for (size_t j = 0; j < width; j++)
			{
				cout << "*";
			}
			cout << endl;
		}
	}
};
class Square : public MyRectangle
{
public:
	Square()
	{
		setSize(MIN_LENGTH + rand() % (MAX_LENGTH - MIN_LENGTH + 1));
		setPosition(rand() % (CONSOLE_WIDTH - width), rand() % (CONSOLE_HEIGHT - width));
	}
	Square(int side, int x, int y)
	{
		setSize(side);
		setPosition(x, y);
	}
	void setSize(int side)
	{
		setWidth(side);
		setHeight(side);
		setPerimeter();
		setArea();
		setDiagonal();
	}
	void printInfo() const override
	{
		cout << "Square:" << endl
			<< "side = " << width << endl
			<< "diagonal = " << diagonal << endl
			<< "area = " << area << endl
			<< "perimeter = " << perimeter << endl << endl;
	}
	void printFigure() const override
	{
		for (size_t i = 0; i < width; i++)
		{
			setCursor(x, y + i);
			for (size_t j = 0; j < width; j++)
			{
				cout << "-";
			}
			cout << endl;
		}
	}
};
class Circle : public Figure
{
	double radius;
	double diameter;
	int x;
	int y;
	void setPerimeter() override
	{
		perimeter = 2 + PI + radius;
	}
	void setDiameter()
	{
		diameter = 2 * radius;
	}
	void setArea() override
	{
		area = PI * radius * radius;
	}
public:
	void setRadius(int value)
	{
		radius = value;
		setPerimeter();
		setDiameter();
		setArea();
	}
	const double& getRadius() const
	{
		return radius;
	}
	const double& getDiameter() const
	{
		return diameter;
	}
	void setPosition(int x, int y) override
	{
		this->x = x < 0 ? 0 :
			x > CONSOLE_WIDTH - 20 ? CONSOLE_WIDTH - 20 :
			x;
		this->y = y < 0 ? 0 :
			y > CONSOLE_HEIGHT ? CONSOLE_HEIGHT :
			y;
	}
	Circle()
	{
		setRadius(MIN_LENGTH + rand() % (MAX_LENGTH - MIN_LENGTH + 1));
		setPosition(rand() % (CONSOLE_WIDTH - 20), rand() % CONSOLE_HEIGHT);
	}
	Circle(double radius, int x, int y)
	{
		setRadius(radius);
		setPosition(x, y);
	}
	void printInfo() const override
	{
		cout << "Circle:" << endl
			<< "radius = " << radius << endl
			<< "diameter = " << diameter << endl
			<< "area = " << area << endl
			<< "perimeter = " << perimeter << endl << endl;
	}
	void printFigure() const override
	{
		setCursor(x, y);
		cout << "Это круг, честно\n";
	}
};
class Triangle : public Figure
{
	//Будем полагать, что треугольник прямоугольный и равнобедренный
	int height;
	//Было бы проще надобавлять всяких медиан и биссектрис, если бы треугольник не пришлось рисовать в консоли, 
	// потому что в таком случае у него было бы три точных стороны
	void setArea() override
	{
		area = height * height / 2;
	}
	void setPerimeter() override
	{
		double thirdSide = sqrt(height * height + height * height);
		perimeter = thirdSide + height * 2;
	}
public:
	void printInfo() const override
	{
		cout << "Triangle:" << endl
			<< "height = " << height << endl
			<< "area = " << area << endl
			<< "perimeter = " << perimeter << endl << endl;
	}
	void printFigure() const override
	{
		for (size_t i = 0; i < height; i++)
		{
			setCursor(x, y + i);
			for (size_t j = 0; j < i + 1; j++)
			{
				cout << "+";
			}
			cout << endl;
		}
	}
	void setHeight(int value)
	{
		height = value < MIN_LENGTH ? MIN_LENGTH :
			value > MAX_LENGTH ? MAX_LENGTH :
			value;
		setArea();
		setPerimeter();
	}
	const int& getHeight() const
	{
		return height;
	}
	void setPosition(int x, int y) override
	{
		this->x = x < 0 ? 0 :
			x > CONSOLE_WIDTH - height ? CONSOLE_WIDTH - height :
			x;
		this->y = y < 0 ? 0 :
			y > CONSOLE_HEIGHT - height ? CONSOLE_HEIGHT - height :
			y;
	}
	Triangle()
	{
		setHeight(MIN_LENGTH + rand() % (MAX_LENGTH - MIN_LENGTH + 1));
		setPosition(rand() % (CONSOLE_WIDTH - height), rand() % (CONSOLE_HEIGHT - height));
	}
	Triangle(int height, int x, int y)
	{
		setHeight(height);
		setPosition(x, y);
	}
};
//TODO:
//В проекте 'Factory' реализовать иерархию геометрических фигур :
//Квадрат, Прямоугольник, Крут, треугольник.......
//для каждой фигуры нужно вывести ее первичные свойства, например,
//длина сторон, радиус ........и вторичные свойства : диагональ,
//площадь, периметр....
//Так же каждую фигуру нужно нарисовать.
//
//Необходимо сгенерировать все эти фигуры в случайном порядке со случайными свойствами.
void main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	/*system("mode con: cols=120 lines=30");*/
	std::vector<Figure*> factory{ new MyRectangle(), new Square(), new Circle(), new Triangle()};
	for (size_t i = 0; i < factory.size(); i++)
	{
		factory[i]->printFigure();
	}
	
}