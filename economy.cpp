#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int items = 5;

typedef map<int, int> inventory;//map<item_type, item_amount>

enum Items
{
	First = 1,
	Money = First,
	Material,
	Labour,
	Food,
	Manufact_good,
	Last
};

enum Actions
{
	First = 1,
	Craft = First,
	Exchange,
	Sell,
	//other actions will be added
	Last
};

int random_int(int left_border, int right_border)
{
	return left_border + rand() % (right_border - left_border + 1);
}

int random_Actor(int vector_size)//this function will be used in the future
{
	return random_int(0, vector_size);
}

int random_Action()
{
	return random_int(Actions::First, Actions::Last);//this function will be used in the future
}

class Good
{
public:
	int cost = 0;
	int prod_time = 0;
	
	virtual void print() = 0;
};

/*
class Material : public Good
{
};

class Labour : public Good
{
};

class Food : public Good
{
};

class Manufact_good : public Good
{
};
*/

class Agent
{
public:

	inventory inv;

	Agent()
	{
		for (int i = Items::First; i <= Items::Last; i++)
		{
			//inv[i] = 0;
			inv[i] = 10;
		}
	}

	void CraftMoney()
	{
		inv[Items::Manufact_good]--;
		inv[Items::Money]++;
	}

	void CraftMaterial()
	{
		inv[Items::Money]--;
		inv[Items::Labour]--;
		inv[Items::Material]++;
	}

	void CraftLabour()
	{
		inv[Items::Food]--;
		inv[Items::Manufact_good]--;
		inv[Items::Labour]++;
	}

	void CraftFood()
	{
		inv[Items::Money]--;
		inv[Items::Labour]--;
		inv[Items::Food]++;
	}

	void CraftGood()
	{
		inv[Items::Money]--;
		inv[Items::Material]--;
		inv[Items::Labour]--;
		inv[Items::Manufact_good]++;
	}

	void print_inventory()
	{
		cout << "inventory:" << endl;

		for (int i = Items::First; i < Items::Last; i++)
		{
			cout << "[" << i << "] = " << inv[i] << endl;
		}
	}

};

class MarketPlace
{
public:
	vector<Agent*> Players;

	//void fillPlayers(vector<Agent*> ttt)
	//Agent* createPlayer() ?

	void exchange(Agent* A1, int good_type_1, int good_amount_1, Agent* A2, int good_type_2, int good_amount_2)
	{
		A1->inv[good_type_2] += good_amount_2;
		A1->inv[good_type_1] -= good_amount_1;
		A2->inv[good_type_1] += good_amount_1;
		A2->inv[good_type_2] -= good_amount_2;
	}
};

void exchange_good(Agent* A1, int good_type_1, int good_amount_1, Agent* A2, int good_type_2, int good_amount_2)
{
	A1->inv[good_type_2] += good_amount_2;
	A1->inv[good_type_1] -= good_amount_1;
	A2->inv[good_type_1] += good_amount_1;
	A2->inv[good_type_2] -= good_amount_2;
}

int main(void)
{
/*	cout << "map test:" << endl;

	inventory ttt;

	ttt[1] = 1;
	ttt[2] = 2;
	ttt[3] = 3;
	ttt[4] = 4;
	ttt[5] = 5;


	cout << "map test: " << ttt[1] << endl;

	cout << "\n\n agent test:" << endl;

	Agent human;

	for (int i = 0; i < Items::Last; i++)
	{
		human.inv[i] = 5;
	}

	human.CraftFood();
	human.CraftMaterial();
	human.print_inventory();
	*/

	vector<Agent> Bazar;//must be vector<Agent*> in the future
	Bazar.resize(3);

	cout << "Bazar test:" << endl;
	for (int i = 0; i < Bazar.size(); i++)
	{
		cout << "	Agent <" << i << ">" << endl;
		Bazar[i].print_inventory();
		cout << endl;
	}

	Agent* AA = &Bazar[0];
	Agent* BB = &Bazar[1];

	//exchange_good test

	exchange_good(AA, Items::Material, 5, BB, Items::Food, 5);

	cout << "	AA inv:" << endl;
	AA->print_inventory();
	cout << endl;
	cout << "	BB inv:" << endl;
	BB->print_inventory();

	return 0;
}
