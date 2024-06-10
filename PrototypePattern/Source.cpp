#include <iostream>
#include <string>
#include <map>
#include <memory>
#define delimeter "\n------------------------------------------------\n\n"
using std::cin;
using std::cout;
using std::endl;

class Player
{
public:
	virtual std::unique_ptr<Player> clone() const = 0;
	/*Player(const std::string& name, int id) : name(name), id(id)
	{

	}*/
	virtual ~Player()
	{

	}
	virtual void print() const = 0;
};
class CarPlayer : public Player
{
	std::string name;
	int id;
public:
	CarPlayer(const std::string& name, int id) : name(name), id(id)
	{
		cout << "Car ctor: " << this << endl;
	}
	~CarPlayer()
	{
		cout << "car dtor: " << this << endl;
	}
	void print() const override
	{
		cout << this << ":\t" << name << " " << id << endl;
	}
	std::unique_ptr<Player>clone() const override
	{
		return std::make_unique<CarPlayer>(*this);
	}

};
class BikePlayer : public Player
{
	std::string name;
	int id;
public:
	BikePlayer(const std::string& name, int id) : name(name), id(id)
	{
		cout << "Bike ctor: " << this << endl;
	}
	~BikePlayer()
	{
		cout << "Bike dtor: " << this << endl;
	}
	void print() const override
	{
		cout << this << ":\t" << name << " " << id << endl;
	}
	std::unique_ptr<Player> clone() const override
	{
		return std::make_unique<BikePlayer>(*this);
	}
};
enum PlayerType
{
	CAR, BIKE
};
class PlayerFactory
{
	std::map<PlayerType, Player*> players;
public:
	PlayerFactory()
	{
		players[CAR] = new CarPlayer("BMW", 735);
		players[BIKE] = new BikePlayer("Harley Davidson", 200);
	}
	~PlayerFactory()
	{
		delete players[CAR];
		delete players[BIKE];
	}
	std::unique_ptr<Player> createPlayer(PlayerType type)
	{
		return players[type]->clone();
	}
};
//#define PROBLEM
#define SOLUTION
void main()
{
	setlocale(LC_ALL, "");
#ifdef PROBLEM
	const Player car_player_template("Car player", 100);
	const Player bike_player_template("Bike player", 200);
	car_player_template.print();
	bike_player_template.print();
	Player car_player = car_player_template;
	car_player.print();
	Player bike_player = bike_player_template;
	bike_player.print();
#endif // PROBLEM
	PlayerFactory factory;
	cout << delimeter;
	std::unique_ptr<Player> car_player = factory.createPlayer(CAR);
	car_player->print();

	cout << delimeter;
	std::unique_ptr<Player> bike_player = factory.createPlayer(BIKE);
	bike_player->print();
	cout << delimeter;
	/*delete bike_player;
	delete car_player;
	cout << delimeter;*/
}