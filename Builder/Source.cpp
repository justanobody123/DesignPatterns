#include <iostream>
#include <string>
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;
#define delimeter "\n--------------------------------------------\n\n"
class Computer
{
	std::string type;
	std::string mb;
	std::string cpu;
	std::string ram;
	std::string disk;
	std::string gpu;
	std::string psu;
	std::string cooler;
	std::string chassis;
	bool on;
public:
	void set_mb(const std::string& mb)
	{
		this->mb = mb;
	}
	void set_type(const std::string& type)
	{
		this->type = type;
	}
	void set_cpu(const std::string& cpu)
	{
		this->cpu = cpu;
	}
	void set_ram(const std::string& ram)
	{
		this->ram = ram;
	}
	void set_disk(const std::string& disk)
	{
		this->disk = disk;
	}
	void set_gpu(const std::string& gpu)
	{
		this->gpu = gpu;
	}
	void set_psu(const std::string& psu)
	{
		this->psu = psu;
	}
	void set_cooler(const std::string& cooler)
	{
		this->cooler = cooler;
	}
	void set_chassis(const std::string& chassis)
	{
		this->chassis = chassis;
	}
	Computer()
	{
		on = false;
		cout << "Default assembly:\t" << this << endl;
	}
	Computer(const std::string& type,
		const std::string& mb,
		const std::string& cpu,
		const std::string& ram,
		const std::string& disk,
		const std::string& gpu,
		const std::string& psu,
		const std::string& cooler,
		const std::string& chassis
	)
	{
		set_type(type);
		set_mb(mb);
		set_cpu(cpu);
		set_ram(ram);
		set_disk(disk);
		set_gpu(gpu);
		set_psu(psu);
		set_cooler(cooler);
		set_chassis(chassis);
		on = false;
		cout << "Assembly DONE\t" << this << endl;
	}
	~Computer()
	{
		cout << "Disassembled\t" << this << endl;
	}
	void power_button()
	{
		//Ыныдуе(ЭсдыЭ)ж
		on = !on;
		if (on)
		{
			cout << "Загрузка Windows. Пожалуйста, подождите..." << endl;
			Sleep(500);
			cout << "Ваш рабочий стол " << endl;
			Sleep(500);
			info();
		}
		else
		{
			cout << "Завершение работы системы" << endl;
			Sleep(500);
			cout << "Не забудьте выдернуть меня из розетки" << endl;
		}
	}
	void info() const
	{
		cout << "Свойства системы:" << endl <<
			type << endl <<
			mb << endl <<
			cpu << endl <<
			ram << endl <<
			disk << endl <<
			gpu << endl <<
			cooler << endl <<
			chassis << endl;
	}

};
class ComputerBuilder
{
protected:
	Computer* computer;
public:
	ComputerBuilder()
	{
		this->computer = new Computer();
	}
	virtual ~ComputerBuilder()
	{
		delete this->computer;
	}
	Computer* get_computer()
	{
		return computer;
	}
	virtual void set_type() = 0;
	virtual void set_mb() = 0;
	virtual void set_cpu() = 0;
	virtual void set_ram() = 0;
	virtual void set_disk() = 0;
	virtual void set_gpu() = 0;
	virtual void set_psu() = 0;
	virtual void set_cooler() = 0;
	virtual void set_chassis() = 0;

};
class OfficeComputerBuilder : public ComputerBuilder
{
public:
	void set_type() override
	{
		computer->set_type("Офисный компьютер");
	}
	void set_mb() override
	{
		computer->set_mb("MSI H610 MicroATX");
	}
	void set_cpu() override
	{
		computer->set_cpu("Intel Celeron G6900");
	}
	void set_ram() override
	{
		computer->set_ram("Silicon power 8 GB DDR-4");
	}
	void set_disk() override
	{
		computer->set_disk("Kingston A400 240 GB");
	}
	void set_gpu() override
	{
		computer->set_gpu("Intel HD Graphics");
	}
	void set_psu() override
	{
		computer->set_psu("Chieftec 500W");
	}
	void set_cooler() override
	{
		computer->set_cooler("Stock Intel cooler");
	}
	void set_chassis() override
	{
		computer->set_chassis("DeepCool MiniTower");
	}
};
class DeveloperComputerBuilder : public ComputerBuilder
{
public:
	void set_type() override
	{
		computer->set_type("Компьютер разработчика");
	}
	void set_mb() override
	{
		computer->set_mb("ASUS ROG MAXIMUS Z790 DARK HERO");
	}
	void set_cpu() override
	{
		computer->set_cpu("Intel Core i9-12900K BOX");
	}
	void set_ram() override
	{
		computer->set_ram("Corsair Dominator 64 GB DDR-5");
	}
	void set_disk() override
	{
		computer->set_disk("Samsung 970 Pro M2 4000 GB");
	}
	void set_gpu() override
	{
		computer->set_gpu("GeForce 4900Ti");
	}
	void set_psu() override
	{
		computer->set_psu("Seasonic 1600W");
	}
	void set_cooler() override
	{
		computer->set_cooler("Zalman CNPS-20 X");
	}
	void set_chassis() override
	{
		computer->set_chassis("Thermaltake Divider 550 TG Ultra");
	}
};
class SysAdmin
{
	ComputerBuilder* builder;
public:
	SysAdmin() :builder(nullptr)
	{
	}
	void assebly_computer(ComputerBuilder* builder)
	{
		this->builder = builder;
		builder->set_type();
		builder->set_mb();
		builder->set_cpu();
		builder->set_ram();
		builder->set_disk();
		builder->set_gpu();
		builder->set_psu();
		builder->set_cooler();
		builder->set_chassis();
	}
	void turn_on_the_computer()
	{
		cout << delimeter;
		if (builder)
		{
			builder->get_computer()->power_button();
		}
		else
		{
			cout << "Средства на сборку компьютера не были выделены" << endl;
		}
		cout << delimeter;
		
	}
};
//#define PROBLEM
#define SOLUTION
void main()
{
	setlocale(LC_ALL, "");
#ifdef PROBLEM
	Computer cheap_computer(
		"Бюджетный компьютер",
		"MSI H610 MicroATX",
		"Intel Celeron G6900",
		"Silicon power 8 GB DDR-4",
		"Kingston A400 240 GB",
		"Intel HD Graphics",
		"Chieftec 500W",
		"Stock Intel cooler",
		"DeepCool MiniTower");
	cout << delimeter;
	cheap_computer.power_button();
	cout << delimeter;
	Computer game_dev
	(
		"Компьютер разработчика",
		"ASUS ROG MAXIMUS Z790 DARK HERO",
		"Intel Core i9-12900K BOX",
		"Corsair Dominator 64 GB DDR-5",
		"Samsung 970 Pro M2 4000 GB",
		"GeForce 4900Ti",
		"Seasonic 1600W",
		"Zalman CNPS-20 X",
		"Thermaltake Divider 550 TG Ultra"
	);
	cout << delimeter;
	game_dev.power_button();
	cout << delimeter;
#endif // PROBLEM

#ifdef SOLUTION 
	SysAdmin nice_guy;

	OfficeComputerBuilder computer_for_director;
	nice_guy.assebly_computer(&computer_for_director);
	nice_guy.turn_on_the_computer();

	DeveloperComputerBuilder computer_for_developer;
	nice_guy.assebly_computer(&computer_for_developer);
	nice_guy.turn_on_the_computer();
#endif // SOLUTION 

}