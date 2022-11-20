#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

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

typedef map<int, int> inventory;//map<item_type, item_amount>

typedef map<int, int> Price;//map<item_type, ingredients (to craft)>
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
	return random_int(Actions::A_First, Actions::A_Last - 1);//this function will be used in the future
}

int random_Item()
{
	return random_int(Items::I_First, Items::I_Last - 1);
}

int random_Amount()
{
	return random_int(1, 5);
}

/////////////////////////Agent/////////////////////////////////////

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
			inv[i] = random_int(0, 15);
		}

		inv[Items::I_Money] = 50;
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

	void print_inv()
	{
		for (int i = Items::I_First; i < Items::I_Last; i++)
		{
			cout << "|" << setw(4) << inv[i] << " ";
		}
		cout << endl;
	}

	Items IntToEnum(int item)
	{
		switch (item)
		{
			case I_Money:
			{
				return I_Money;
				break;
			}
			case I_Material:
			{
				return I_Material;
				break;
			}
			case I_Labour:
			{
				return I_Labour;
				break;
			}
			case I_Food:
			{
				return I_Food;
				break;
			}
			case I_Manufact_good:
			{
				return I_Manufact_good;
				break;
			}
			default:
			{
				cout << "something wrong in IntToEnum" << endl;
				return I_Last;
				break;
			}
				
		}
	}

	Items findMin()// here we find item with the least amount
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

		return IntToEnum(min_item);

		//return min_item;
	}
	
	//rework!!!!!!!!!!!
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
	return new Agent;
}

void fillMarketPlace(vector<Agent*>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		vec[i] = createPlayer();
	}
}

//////////////////////////Classes///////////////////////////////////
class Good
{
public:
	int prod_time = 0;
	int cost = 0;

	vector<int> Required_items;

	virtual void print() = 0;

	int HowManyItems(Agent* agent, int item_type) const
	{
		return agent->inv.at(item_type);
	}

	virtual bool IfCraftable(Agent* agent) const = 0;

	virtual void ResourcePayment(Agent* agent)
	{
		for (size_t i = 0; i < Required_items.size(); i++)
		{
			agent->inv[ Required_items[i] ]--;
		}
	}

	virtual void Craft(Agent* agent) = 0;

	virtual void Buy(Agent* agent) = 0;

	virtual bool IfBuyable(Agent* agent) const = 0;

	virtual void Sell(Agent* agent) = 0;

	virtual bool IfSellable(Agent* agent) const = 0;



	//virtual void Buy(Agent*, int item_type, int price) = 0;
};

class Money : public Good
{
public:

	Money()
	{
		Required_items.push_back(I_Manufact_good);
		cost = 0;
	}

	void print()
	{
		cout << "empty cout";
	}

	bool IfCraftable(Agent* agent) const override
	{
		for (size_t i = 0; i < Required_items.size(); i++)
		{
			if (HowManyItems(agent, Required_items[i]) <= 0)
			{
				return false;
			}
		}

		return true;
	}

	void Craft(Agent* agent) override
	{
		ResourcePayment(agent);
		agent->inv[I_Money]++;
	}

	void Buy(Agent* agent) override
	{
		agent->inv[I_Money] -= cost;
		agent->inv[I_Money]++;
	}

	bool IfBuyable(Agent* agent) const override
	{
		if ( (HowManyItems(agent, I_Money) - cost) < 0)
		{
			return false;
		}

		return true;
	}

	void Sell(Agent* agent) override
	{
		agent->inv[I_Money] += cost;
		agent->inv[I_Money]--;
	}

	bool IfSellable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Money) - 1) < 0)
		{
			return false;
		}

		return true;
	}
};

class Material : public Good
{
public:
	Material()
	{
		Required_items.push_back(I_Money);
		Required_items.push_back(I_Labour);
		cost = 5;
	}

	void print()
	{
		cout << "empty cout";
	}

	bool IfCraftable(Agent* agent) const override
	{
		for (size_t i = 0; i < Required_items.size(); i++)
		{
			if (HowManyItems(agent, Required_items[i]) <= 0)
			{
				return false;
			}
		}

		return true;
	}

	void Craft(Agent* agent) override
	{
		ResourcePayment(agent);
		agent->inv[I_Material]++;
	}

	bool IfBuyable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Money) - cost) < 0)
		{
			return false;
		}

		return true;
	}

	void Buy(Agent* agent) override
	{
		agent->inv[I_Money] -= cost;
		agent->inv[I_Material]++;
	}

	void Sell(Agent* agent) override
	{
		agent->inv[I_Money] -= cost;
		agent->inv[I_Material]++;
	}

	bool IfSellable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Material) - 1) < 0)
		{
			return false;
		}

		return true;
	}

};

class Labour : public Good
{
public:
	Labour()
	{
		Required_items.push_back(I_Food);
		Required_items.push_back(I_Manufact_good);
		cost = 5;
	}

	void print()
	{
		cout << "empty cout";
	}

	bool IfCraftable(Agent* agent) const override
	{
		for (size_t i = 0; i < Required_items.size(); i++)
		{
			if (HowManyItems(agent, Required_items[i]) <= 0)
			{
				return false;
			}
		}

		return true;
	}

	void Craft(Agent* agent) override
	{
		ResourcePayment(agent);
		agent->inv[I_Labour]++;
	}

	void Buy(Agent* agent) override
	{
		agent->inv[I_Money] -= cost;
		agent->inv[I_Labour]++;
	}

	bool IfBuyable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Money) - cost) < 0)
		{
			return false;
		}

		return true;
	}

	void Sell(Agent* agent) override
	{
		agent->inv[I_Money] += cost;
		agent->inv[I_Labour]--;
	}

	bool IfSellable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Labour) - 1) < 0)
		{
			return false;
		}

		return true;
	}
};

class Food : public Good
{
public:
	Food()
	{
		Required_items.push_back(I_Money);
		Required_items.push_back(I_Labour);
		cost = 5;
	}

	void print()
	{
		cout << "empty cout";
	}

	bool IfCraftable(Agent* agent) const override
	{
		for (size_t i = 0; i < Required_items.size(); i++)
		{
			if (HowManyItems(agent, Required_items[i]) <= 0)
			{
				return false;
			}
		}

		return true;
	}

	void Craft(Agent* agent) override
	{
		ResourcePayment(agent);
		agent->inv[I_Food]++;
	}

	void Buy(Agent* agent) override
	{
		agent->inv[I_Money] -= cost;
		agent->inv[I_Food]++;
	}

	bool IfBuyable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Money) - cost) < 0)
		{
			return false;
		}

		return true;
	}

	void Sell(Agent* agent) override
	{
		agent->inv[I_Money] += cost;
		agent->inv[I_Food]--;
	}

	bool IfSellable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Food) - 1) < 0)
		{
			return false;
		}

		return true;
	}
};

class Manufact_good : public Good
{
public:
	Manufact_good()
	{
		Required_items.push_back(I_Money);
		Required_items.push_back(I_Material);
		Required_items.push_back(I_Labour);
		cost = 5;
	}

	void print()
	{
		cout << "ttt";
	}

	bool IfCraftable(Agent* agent) const override
	{
		for (size_t i = 0; i < Required_items.size(); i++)
		{
			if (HowManyItems(agent, Required_items[i]) <= 0)
			{
				return false;
			}
		}

		return true;
	}

	void Craft(Agent* agent)
	{
		ResourcePayment(agent);
		agent->inv[Items::I_Manufact_good]++;
	}

	void Buy(Agent* agent) override
	{
		agent->inv[I_Money] -= cost;
		agent->inv[I_Manufact_good]++;
	}

	bool IfBuyable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Money) - cost) < 0)
		{
			return false;
		}

		return true;
	}

	void Sell(Agent* agent) override
	{
		agent->inv[I_Money] += cost;
		agent->inv[I_Manufact_good]--;
	}

	bool IfSellable(Agent* agent) const override
	{
		if ((HowManyItems(agent, I_Manufact_good) - 1) < 0)
		{
			return false;
		}

		return true;
	}
};

//////////////////////GoodType/////////////////////////////////

typedef map<Items, Good*> GoodType;
GoodType GoodTypeList;

///////////////////////////MarketPlace//////////////////////////////////

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
		for (size_t i = 0; i < Players.size(); i++)
		{
			cout << "Player " << i << endl;
			Players[i]->print_inventory();
		}
	}

	void printPlayersInv()
	{
		cout << "  . |  Mo | Ma  |  L  |  F  | Mg |" << endl;

		for (size_t i = 0; i < Players.size(); i++)
		{
			cout << "AG" << i << " ";
			Players[i]->print_inv();
		}
	}

	void exchange_good(Agent* A1, int good_type_1, int good_amount_1, Agent* A2, int good_type_2, int good_amount_2)
	{
		A1->inv[good_type_2] += good_amount_2;
		A1->inv[good_type_1] -= good_amount_1;
		A2->inv[good_type_1] += good_amount_1;
		A2->inv[good_type_2] -= good_amount_2;
	}

	Agent* findRichestAgent(int good_type)
	{
		int RichestAgent = 0;
		int maxAmount = Players[0]->inv[good_type];

		for (size_t i = 0; i < Players.size(); i++)
		{
			if (Players[i]->inv[good_type] > maxAmount)
			{
				RichestAgent = i;
				maxAmount = Players[i]->inv[good_type];
			}
		}

		//return RichestAgent;
		return Players[RichestAgent];
	}

	int findRichestAgentNumber(int good_type)
	{
		int RichestAgent = 0;
		int maxAmount = Players[0]->inv[good_type];

		for (size_t i = 0; i < Players.size(); i++)
		{
			if (Players[i]->inv[good_type] > maxAmount)
			{
				RichestAgent = i;
				maxAmount = Players[i]->inv[good_type];
			}
		}

		return RichestAgent;
	}

	int HowManyAvailable(int item_type)
	{
		int Count = 0;
		for (size_t i = 0; i < Players.size(); i++)
		{
			if (Players[i]->inv[item_type] != 0)
			{
				Count++;
			}
		}

		return Count;
	}

	//void Trade(<Seller>, <Client>, <resource>, <price>)
	/*
	void Trade(Agent* Seller, Agent* Client, int item_type)
	{
		Seller->Sell(item_type, HowManyAvailable(item_type));
		Client->Buy(item_type, HowManyAvailable(item_type));//HERE////////////////////////////////////////////!!!!!!!!!!!!!
	}
	*/

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

////////////////////////////Main////////////////////////////////

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

/////////////////////////Pricelist filling////////////////////////////////////

	Pricelist[I_Money] = 1;
	Pricelist[I_Material] = 5;
	Pricelist[I_Labour] = 5;
	Pricelist[I_Food] = 5;
	Pricelist[I_Manufact_good] = 5;

///////////////////////Every class object for its functions//////////////////////////////////////

	Money Mon;
	Labour Lab;
	Material Mat;
	Food Foo;
	Manufact_good ManG;

	Good* pGoo;

	Money* pMon = &Mon;
	Labour* pLab = &Lab;
	Material* pMat = &Mat;
	Food* pFoo = &Foo;
	Manufact_good* pManG = &ManG;

	//typedef map<Items, Good*> GoodType;//map<item_type, good_type*>
	//GoodType GoodTypeList;

	GoodTypeList[I_Money] = pMon;
	GoodTypeList[I_Labour] = pLab;
	GoodTypeList[I_Material] = pMat;
	GoodTypeList[I_Food] = pFoo;
	GoodTypeList[I_Manufact_good] = pManG;

/////////////////////////////////////////////////////////////

	MarketPlace Avito;

	Avito.Initialize(5);

	//Avito.printPlayersInventory();
	Avito.printPlayersInv();

	/*cout << "	exchange test 2: " << endl;

	Avito.exchange_good(Avito.Players[0], Items::I_Food, 8, Avito.Players[2], Items::I_Labour, 5);
	Avito.printPlayersInventory();
	*/
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

////////////////////////////////CRAFT STAGE///////////////////////////////////
/*
	Avito.printPlayersInv();

	cout << "	Game cycles test STAGE CRAFT" << endl;

	for (int cycle = 0; cycle < 1; cycle++)//in-game cycles
	{
		cout << "cycle " << cycle << endl;
		for (size_t queue = 0; queue < Avito.Players.size(); queue++)//iterate throw Players
		{
			cout << "Agent #" << queue << " turn" << endl;
			
			cout << "Data before craft: " << endl;
			Avito.printPlayersInv();

			Items item = Avito.Players[queue]->findMin();// searching needed resource
			pGoo = GoodTypeList.at(item);

			if (pGoo->IfCraftable(Avito.Players[queue]))
			{
				cout << "----> Agent #" << queue << " crafted " << item << "<---- " << endl;
				pGoo->Craft(Avito.Players[queue]);
			}

			cout << "Data after craft: " << endl;
			Avito.printPlayersInv();
		}
	}

	Avito.printPlayersInventory();
*/
///////////////////////////////PURCHASE STAGE/////////////////////////////////

	cout << "	Game cycles test PURCHASE STAGE (between themselves)" << endl;

	for (int cycle = 0; cycle < 1; cycle++)//in-game cycles
	{
		cout << "cycle " << cycle << endl;
		for (size_t queue = 0; queue < Avito.Players.size(); queue++)//iterate throw Players
		{
			cout << "Agent #" << queue << " turn" << endl;
			
			Items item = Avito.Players[queue]->findMin();// searching needed resource
			pGoo = GoodTypeList.at(item);
			
			Agent* Seller;
			int SellerNum;

			Seller = Avito.findRichestAgent(item);//searching richest agent of needed resource
			SellerNum = Avito.findRichestAgentNumber(item);

			if ((pGoo->IfBuyable(Avito.Players[queue])) && (pGoo->IfSellable(Seller)))
			{
				cout << "Agent #" << queue << " tried to trade with Agent #" << SellerNum << endl << endl;
				cout << "Data before trade: " << endl;
				Avito.printPlayersInv();
				cout << "----> Agent #" << queue << " purchased " << item << "<----" << endl << endl;

				pGoo->Buy(Avito.Players[queue]);
				pGoo->Sell(Seller);

				cout << "Data after trade: " << endl;
				Avito.printPlayersInv();
			}
			else
			{
				cout << "Agent #" << queue << " cannot afford " << item << endl;
			}


			/*
			if (Avito.Players[queue]->IfBuyable(item))//trying to buy it
			{
				cout << "Agent #" << queue << " tried to trade with Agent #" << SellerNum << endl << endl;
				
				cout << "Data before trade: " << endl;
				Avito.printPlayersInv();

				cout << "----> Agent #" << queue << " purchased " << item << "<----"  << endl << endl;
				
				Avito.Trade(Seller, Avito.Players[queue], item);
				
				cout << "Data after trade: " << endl;
				Avito.printPlayersInv();
			}
			else
			{
				cout << "Agent #" << queue << " cannot afford " << item << endl;
			}
			*/
		}
	}

	cout << "	END OF PURCHASE STAGE" << endl;
	
	Avito.printPlayersInv();

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

/*
	cout << "	 TRADE TEST" << endl;
	Avito.Trade(Avito.Players[0], Avito.Players[1], 4);
	Avito.printPlayersInventory();
*/
	return 0;
}
