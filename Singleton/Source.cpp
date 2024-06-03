#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Human
{
	//Инициализация в глобале после описания класса
	static Human* instance;//Если статическое поле класс типа инт, мы можем инициализировать ее в классе, в противном случае статическое поле должно инициализироваться за пределами класса.
	string lastName;
	string firstName;
	tm birthDate;
	//SINGLETON'S CTORS ARE ALWAYS PRIVATE
	Human()
	{
		cout << "Ctor Human:\t" << this << endl;
	}
public:
	const std::string& getLastName() const
	{
		//Константный метод не изменяет this
		//Константный метод обязательно должен возвращать константное значение
		return lastName;
	}
	const std::string& getFirstName() const
	{
		return firstName;
	}
	const tm& getBirthDate() const
	{
		return birthDate;
	}
	void setLastName(const std::string& lastName)
	{
		this->lastName = lastName;
	}
	void setFirstName(const std::string& firstName)
	{
		this->firstName = firstName;
	}
	void setBirthDate(int year, int month, int day)
	{
		this->birthDate.tm_mday = day;
		this->birthDate.tm_year = year - 1900;
		this->birthDate.tm_mon = month - 1;
		/*this->birthDate = birthDate;*/
	}
	~Human()
	{
		cout << "Dtor Human:\t" << this << endl;
	}
	static Human& getInstance()
	{
		if (instance == nullptr)//Объект создается только в том случае, если он еще не существует.
		{
			instance = new Human(); 
		}
		return *instance;
	}
	void print() const
	{
		time_t timer;
		time(&timer);
		tm* currentTime = localtime(&timer);
		unsigned int age = currentTime->tm_year - birthDate.tm_year;
		if (currentTime->tm_yday < birthDate.tm_yday)
		{
			age--;
		}
		cout << firstName << " " << lastName << " " << age << endl;
	}
};
Human* Human::instance = nullptr;//Глобальная точка доступа к объекту класса
void main()
{
	setlocale(LC_ALL, "");
	Human main = Human::getInstance();//Создаем экземпляр класса, потому что он еще не существует
	main.setLastName("Vercetti");
	main.setFirstName("Tommy");
	main.setBirthDate(1951, 6, 10);
	main.print();
}