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

typedef map<int, vector<int>> Receipts;//map<item_type, ingredients (to craft)>
Receipts Menu;

typedef map<int, double> Price;//map<item_type, ingredients (to craft)>
Price Pricelist;

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

		inv[Items::I_Money] = 50;
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

	void Craft(int item_type)
	{
		switch (item_type)
		{
		case I_Money:
		{
			CraftMoney();
			break;
		}
		case I_Material:
		{
			CraftMaterial();
			break;
		}
		case I_Labour:
		{
			CraftLabour();
			break;
		}
		case I_Food:
		{
			CraftFood();
			break;
		}
		case I_Manufact_good:
		{
			CraftManufactGood();
			break;
		}
		default:
			break;
		}
	}

//////////////////////////

	void SellMoney()
	{
		//inv[I_Money] += Pricelist[I_Money];
		//inv[I_Money] -= Pricelist[I_Money];
		cout << "";
	}

	void SellMaterial()
	{
		inv[I_Money] += Pricelist[I_Material];
		inv[I_Material]--;
	}

	void SellLabour()
	{
		inv[Items::I_Money] += Pricelist[I_Labour];
		inv[Items::I_Labour]--;
	}

	void SellFood()
	{
		inv[Items::I_Money] += Pricelist[I_Food];
		inv[Items::I_Food]--;
	}

	void SellManufactGood()
	{
		inv[Items::I_Money] += Pricelist[I_Manufact_good];
		inv[Items::I_Manufact_good]--;
	}

	void Sell(int item_type)
	{
		switch (item_type)
		{
		case I_Money:
		{
			SellMoney();
			break;
		}
		case I_Material:
		{
			SellMaterial();
			break;
		}
		case I_Labour:
		{
			SellLabour();
			break;
		}
		case I_Food:
		{
			SellFood();
			break;
		}
		case I_Manufact_good:
		{
			SellManufactGood();
			break;
		}
		default:
			break;
		}
	}

//////////////////////////

	void BuyMoney()
	{
		//inv[I_Money] -= Pricelist[I_Money];
		//inv[I_Money] += Pricelist[I_Money];
		cout << "";
	}

	void BuyMaterial()
	{
		inv[Items::I_Money] -= Pricelist[I_Material];
		inv[Items::I_Material]++;
	}

	void BuyLabour()
	{
		inv[Items::I_Money] -= Pricelist[I_Labour];
		inv[Items::I_Labour]++;
	}

	void BuyFood()
	{
		inv[Items::I_Money] -= Pricelist[I_Food];
		inv[Items::I_Food]++;
	}

	void BuyManufactGood()
	{
		inv[Items::I_Money] -= Pricelist[I_Manufact_good];
		inv[Items::I_Manufact_good]++;
	}

	void Buy(int item_type)
	{
		switch (item_type)
		{
		case I_Money:
		{
			BuyMoney();
			break;
		}
		case I_Material:
		{
			BuyMaterial();
			break;
		}
		case I_Labour:
		{
			BuyLabour();
			break;
		}
		case I_Food:
		{
			BuyFood();
			break;
		}
		case I_Manufact_good:
		{
			BuyManufactGood();
			break;
		}
		default:
			break;
		}
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

	int WhatToCraft()
	{
		return findMin();
	}
	
	int HowMany(int item_type) const
	{
		return inv.at(item_type);
	}

	vector<int> GetIngredients(int item_type) const
	{
		vector<int> ingr;

		ingr = Menu[item_type];

		return ingr;
		//return Menu[item_type];
	}

	bool IfCraftable(int item_type) const
	{
		vector<int> ttt;
		ttt = GetIngredients(item_type);

		for (int i = 0; i < ttt.size(); i++)
		{
			if (HowMany(ttt[i]) <= 0)
			{
				return false;
			}
		}

		return true;
	}

	bool IfBuyable(int item_type) const
	{
		//so if we look on the price, then its just price check (affordable or not)
		if (inv.at(I_Money) < Pricelist[item_type])
		{
			return false;
		}

		return true;
	}

	//bool IfTradeable?? (like barther)

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

	int HowManyAvailable(int item_type)
	{
		int Count = 0;
		for (int i = 0; i < Players.size(); i++)
		{
			if (Players[i]->inv[item_type] != 0)
			{
				Count++;
			}
		}

		return Count;
	}

	//void Trade(<Seller>, <Client>, <resource>)

	//coefficient = 1 / Count;
	//price = base_price / coefficient;

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

/////////////////////////////////////////////////////////////
 
	//typedef map<int, vector<int>> Receipts;
	//Receipts Menu;

	Menu[I_Money] = { I_Manufact_good };//instead of numbers must be elements from enum "Items"
	Menu[I_Material] = {I_Money, I_Labour };
	Menu[I_Labour] = {I_Food, I_Manufact_good };
	Menu[I_Food] = { I_Money, I_Labour };
	Menu[I_Manufact_good] = {I_Money, I_Material, I_Labour };

	//cout << "Menu 2,1 ---> " << Menu[2][1] << endl;

/////////////////////////////////////////////////////////////

	Pricelist[I_Money] = 1;
	Pricelist[I_Material] = 5;
	Pricelist[I_Labour] = 5;
	Pricelist[I_Food] = 5;
	Pricelist[I_Manufact_good] = 5;

/////////////////////////////////////////////////////////////

	MarketPlace Avito;

	Avito.Initialize(5);

	Avito.printPlayersInventory();

	/*cout << "	exchange test 2: " << endl;

	Avito.exchange_good(Avito.Players[0], Items::I_Food, 8, Avito.Players[2], Items::I_Labour, 5);
	*/
	//Avito.printPlayersInventory();

//////////////////////////////////////////////////////////////////////////////
	/*
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
	
	*/

//////////////////////////////////////////////////////////////////////////////
/*	Avito.printPlayersInventory();

	cout << "	Game cycles test STAGE CRAFT" << endl;

	for (int cycle = 0; cycle < 10; cycle++)//in-game cycles
	{
		cout << "cycle " << cycle << endl;
		for (int queue = 0; queue < Avito.Players.size(); queue++)//iterate throw Players
		{
			cout << "Agent #" << queue << " turn" << endl;
			
			cout << "Agent #" << queue << "inventory (before craft): " << endl;
			Avito.Players[queue]->print_inventory();

			int item = Avito.Players[queue]->findMin();// searching needed resource

			if (Avito.Players[queue]->IfCraftable(item))//trying to craft it
			{
				cout << "Agent #" << queue << " crafted " << item << endl;
				Avito.Players[queue]->Craft(item);

				cout << "Agent #" << queue << "inventory (after craft): " << endl;
				Avito.Players[queue]->print_inventory();
			}
		}
	}

	Avito.printPlayersInventory();
*/
//////////////////////////////////////////////////////////////////////////////

	cout << "	Game cycles test PURCHASE STAGE (not between themselves)" << endl;

	for (int cycle = 0; cycle < 10; cycle++)//in-game cycles
	{
		cout << "cycle " << cycle << endl;
		for (int queue = 0; queue < Avito.Players.size(); queue++)//iterate throw Players
		{
			cout << "Agent #" << queue << " turn" << endl;

			cout << "Agent #" << queue << "inventory (before buy): " << endl;
			Avito.Players[queue]->print_inventory();

			int item = Avito.Players[queue]->findMin();// searching needed resource

			if (Avito.Players[queue]->IfBuyable(item))//trying to craft it
			{
				cout << "Agent #" << queue << " purchased " << item << endl;
				Avito.Players[queue]->Buy(item);

				cout << "Agent #" << queue << " inventory (after purchase): " << endl;
				Avito.Players[queue]->print_inventory();
			}
			else
			{
				cout << "Agent #" << queue << " cannot afford " << item << endl;
			}
		}
	}

	cout << "	END OF PURCHASE STAGE" << endl;

	Avito.printPlayersInventory();

//////////////////////////////////////////////////////////////////////////////

	/*
	cout << "	GetIngredients test" << endl;
	vector<int> ingred;
	ingred = Avito.Players[1]->GetIngredients(I_Labour);
	cout << "ingred size = " << ingred.size() << endl;
	cout << "ingred: {" << ingred[0] << ", " << ingred[1] << "}" << endl;
	*/

	/*cout << endl << "	IFCRAFTABLE TEST" << endl;

	Avito.Players[0]->inv[1] = 0;
	Avito.Players[0]->inv[2] = 0;
	Avito.Players[0]->inv[3] = 0;
	Avito.Players[0]->inv[4] = 0;
	Avito.Players[0]->inv[5] = 0;

	Avito.Players[0]->print_inventory();

	if (Avito.Players[0]->IfCraftable(I_Food) == true)
	{
		cout << "we can craft this!" << endl;
	}
	else
	{
		cout << "failure!!!" << endl;
	}
	*/
/*
	cout << endl << "	IFBUYABLE TEST" << endl;

	Avito.Players[0]->inv[1] = 50;
	Avito.Players[0]->inv[2] = 0;
	Avito.Players[0]->inv[3] = 0;
	Avito.Players[0]->inv[4] = 0;
	Avito.Players[0]->inv[5] = 0;

	Avito.Players[0]->print_inventory();

	if (Avito.Players[0]->IfBuyable(I_Food) == true)
	{
		cout << "we can buy this!" << endl;
	}
	else
	{
		cout << "failure!!!" << endl;
	}
*/


	return 0;
}
