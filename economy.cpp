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
	return random_int(0, vector_size - 1);
}

int random_Action()
{
	return random_int(Actions::A_First, Actions::A_Last);//this function will be used in the future
}

int random_Item()
{
	return random_int(Items::I_First, Items::I_Last - 1);
}

int random_Amount()
{
	return random_int(1, 5);
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
			//inv[i] = 10;
			inv[i] = random_int(6, 15);
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

	void CraftManufactGood()
	{
		inv[Items::I_Money]--;
		inv[Items::I_Material]--;
		inv[Items::I_Labour]--;
		inv[Items::I_Manufact_good]++;
	}

//////////////////////////

	void SellMaterial()
	{
		inv[Items::I_Money] += 5;
		inv[Items::I_Material] -= 1;
	}

	void SellLabour()
	{
		inv[Items::I_Money] += 5;
		inv[Items::I_Labour] -= 1;
	}

	void SellFood()
	{
		inv[Items::I_Money] += 5;
		inv[Items::I_Food] -= 1;
	}

	void SellManufactGood()
	{
		inv[Items::I_Money] += 5;
		inv[Items::I_Manufact_good] -= 1;
	}

//////////////////////////

	void BuyMaterial()
	{
		inv[Items::I_Money] -= 5;
		inv[Items::I_Material] += 1;
	}

	void BuyLabour()
	{
		inv[Items::I_Money] -= 5;
		inv[Items::I_Labour] += 1;
	}

	void BuyFood()
	{
		inv[Items::I_Money] -= 5;
		inv[Items::I_Food] += 1;
	}

	void BuyManufactGood()
	{
		inv[Items::I_Money] -= 5;
		inv[Items::I_Manufact_good] += 1;
	}

//////////////////////////

	void print_inventory()
	{
		cout << "inventory:" << endl;

		for (int i = Items::I_First; i < Items::I_Last; i++)
		{
			cout << "[" << i << "] = " << inv[i] << endl;
		}
		cout << endl;
	}

	int findMin()// here we find item with the least amount
	{
		int min_item = Items::I_First;
		int min_amount = inv[Items::I_First];

		for (int i = Items::I_First; i < Items::I_Last; i++)
		{
			if (inv[i] < min_amount)
			{
				min_item = i;
				min_amount = inv[i];
			}
		}

		return min_item;
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

	int findRichestAgent(int good_type)
	{
		int RichestAgent = 0;
		int maxAmount = Players[0]->inv[good_type];

		for (int i = 0; i < Players.size(); i++)
		{
			if (Players[i]->inv[good_type] > maxAmount)
			{
				RichestAgent = i;
				maxAmount = Players[i]->inv[good_type];
			}
		}
	}

	void Stage_Buy()
	{
		//not implemented right now
	}

	void Stage_Craft()
	{
		//not implemented right now
	}

	void DayCicle()
	{
		//find what every Agent wants

		//Stage_Buy for every Agent

		//Stage_Craft for every Agent
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

	Avito.exchange_good(Avito.Players[0], Items::I_Food, 8, Avito.Players[2], Items::I_Labour, 5);

	Avito.printPlayersInventory();

//////////////////////////////////////////////////////////////////////////////
	cout << "	100000 exchanges test" << endl;
	int size = Avito.Players.size();
	for (int i = 0; i < 100000; i++)
	{

		int A_1 = random_Actor(size);
		int A_2 = random_Actor(size);

		//int i_1 = random_Item();
		//int i_2 = random_Item();
		int i_1 = Avito.Players[A_1]->findMin();
		int i_2 = Avito.Players[A_2]->findMin();

		int am_1 = random_Amount();
		int am_2 = random_Amount();

		if (((Avito.Players[A_1]->inv[i_1] - am_1) > 0) && ((Avito.Players[A_2]->inv[i_2] - am_2) > 0))
		{
			//Avito.exchange_good(Avito.Players[A_1], i_1, am_1, Avito.Players[A_2], i_2, am_2);



		}
	}
	
	Avito.printPlayersInventory();

	return 0;
}
