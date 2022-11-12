#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int items = 5;

typedef map<int, int> inventory;//map<item_type, item_amount>

enum Items
{
	I_First = 1,
	I_Money = I_First,
	I_Material,
	I_Labour,
	I_Food,
	I_Manufact_good,
	I_Last
};

enum Actions
{
	A_First = 1,
	A_Craft = A_First,
	A_Exchange,
	A_Sell,
	//other actions will be added
	A_Last
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
	return random_int(Actions::A_First, Actions::A_Last);//this function will be used in the future
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
		for (int i = Items::I_First; i <= Items::I_Last; i++)
		{
			//inv[i] = 0;
			inv[i] = 10;
		}
	}

	void CraftMoney()
	{
		inv[Items::I_Manufact_good]--;
		inv[Items::I_Money]++;
	}

	void CraftMaterial()
	{
		inv[Items::I_Money]--;
		inv[Items::I_Labour]--;
		inv[Items::I_Material]++;
	}

	void CraftLabour()
	{
		inv[Items::I_Food]--;
		inv[Items::I_Manufact_good]--;
		inv[Items::I_Labour]++;
	}

	void CraftFood()
	{
		inv[Items::I_Money]--;
		inv[Items::I_Labour]--;
		inv[Items::I_Food]++;
	}

	void CraftGood()
	{
		inv[Items::I_Money]--;
		inv[Items::I_Material]--;
		inv[Items::I_Labour]--;
		inv[Items::I_Manufact_good]++;
	}

	void print_inventory()
	{
		cout << "inventory:" << endl;

		for (int i = Items::I_First; i < Items::I_Last; i++)
		{
			cout << "[" << i << "] = " << inv[i] << endl;
		}
		cout << endl;
	}

};

Agent* createPlayer()
{
	Agent* A = new Agent;
	return A;
}

void fillMarketPlace(vector<Agent*>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i] = createPlayer();
	}
}

class MarketPlace
{
public:
	vector<Agent*> Players;

	void Initialize(int new_size)
	{
		Players.resize(new_size);
		fillMarketPlace(Players);
	}

	void printPlayersInventory()
	{
		for (int i = 0; i < Players.size(); i++)
		{
			cout << "Player " << i << endl;
			Players[i]->print_inventory();
		}
	}

	void exchange_good(Agent* A1, int good_type_1, int good_amount_1, Agent* A2, int good_type_2, int good_amount_2)
	{
		A1->inv[good_type_2] += good_amount_2;
		A1->inv[good_type_1] -= good_amount_1;
		A2->inv[good_type_1] += good_amount_1;
		A2->inv[good_type_2] -= good_amount_2;
	}
};

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
	/*
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

	exchange_good(AA, Items::I_Material, 5, BB, Items::I_Food, 5);

	cout << "	AA inv:" << endl;
	AA->print_inventory();
	cout << endl;
	cout << "	BB inv:" << endl;
	BB->print_inventory();
	*/

	MarketPlace Avito;

	Avito.Initialize(5);

	Avito.printPlayersInventory();

	cout << "	exchange test 2: " << endl;

	Avito.exchange_good(Avito.Players[0], Items::I_Food, 5, Avito.Players[2], Items::I_Labour, 5);

	Avito.printPlayersInventory();
	
	return 0;
}
