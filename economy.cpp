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
//typedef map<Items, int> inventory;//map<item_type, item_amount>

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

/////////////////////////Agent///////////////////////////

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

//////////////////////////Classes////////////////////////
class Good
{
public:

	virtual Items getResource() const = 0;

	virtual vector<Items> getReqiredItems() = 0;

	void ResourcePayment(Agent* agent)
	{
		vector<Items> RequiredItems;
		RequiredItems = getReqiredItems();

		for (size_t i = 0; i < RequiredItems.size(); i++)
		{
			agent->inv[RequiredItems[i]]--;
		}
	}

	void Craft(Agent* agent)
	{
		ResourcePayment(agent);
		agent->inv[getResource()]++;
	}

	bool IfCraftable(Agent* agent)// const
	{
		vector<Items> RequiredItems;
		RequiredItems = getReqiredItems();

		for (size_t i = 0; i < RequiredItems.size(); i++)
		{
			if (HowManyItems(agent, RequiredItems[i]) <= 0)
			{
				return false;
			}
		}

		return true;
	}

	virtual int getCost() const = 0;

	void Buy(Agent* agent)
	{
		agent->inv[I_Money] -= getCost();
		agent->inv[getResource()]++;
	}

	void Sell(Agent* agent)
	{
		agent->inv[I_Money] += getCost();
		agent->inv[getResource()]--;
	}

////////////////////////////////////////////////////////////////////

	int HowManyItems(Agent* agent, Items item_type) const
	{
		return agent->inv.at(item_type);
	}


	bool IfBuyable(Agent* agent) const
	{
		if ((HowManyItems(agent, I_Money) - getCost()) < 0)
		{
			return false;
		}

		return true;
	}

	bool IfSellable(Agent* agent) const
	{
		return HowManyItems(agent, getResource()) > 0;
	}

	//virtual void Buy(Agent*, int item_type, int price) = 0;
};

class Money : public Good
{
public:
	Items getResource() const override
	{
		return I_Money;
	}

	vector<Items> getReqiredItems() override
	{
		vector<Items> Required;
		Required.push_back(I_Manufact_good);

		return Required;
	}

	int getCost() const override
	{
		return 0;
	}
};

class Material : public Good
{
public:
	vector<Items> getReqiredItems() override
	{
		vector<Items> Required;
		Required.push_back(I_Money);
		Required.push_back(I_Labour);

		return Required;
	}

	Items getResource() const override
	{
		return I_Material;
	}

	int getCost() const override
	{
		return 5;
	}
};

class Labour : public Good
{
public:
	vector<Items> getReqiredItems() override
	{
		vector<Items> Required;
		Required.push_back(I_Food);
		Required.push_back(I_Manufact_good);

		return Required;
	}

	Items getResource() const override
	{
		return I_Labour;
	}

	int getCost() const override
	{
		return 5;
	}
};

class Food : public Good
{
public:
	vector<Items> getReqiredItems() override
	{
		vector<Items> Required;
		Required.push_back(I_Money);
		Required.push_back(I_Labour);

		return Required;
	}

	Items getResource() const override
	{
		return I_Food;
	}

	int getCost() const override
	{
		return 5;
	}
};

class Manufact_good : public Good
{
public:

	vector<Items> getReqiredItems() override
	{
		vector<Items> Required;
		Required.push_back(I_Money);
		Required.push_back(I_Material);
		Required.push_back(I_Labour);

		return Required;
	}

	Items getResource() const override
	{
		return I_Manufact_good;
	}

	int getCost() const override
	{
		return 5;
	}
};

//////////////////////GoodType//////////////////////////

typedef map<Items, Good*> GoodType;
GoodType GoodTypeList;

///////////////////////////MarketPlace//////////////////

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

	void DayCycle()
	{
		//find what every Agent wants

		//Stage_Buy for every Agent

		//Stage_Craft for every Agent
	}


};

////////////////////////////Main//////////////////////////////////////////////////////////////

int main(void)
{
///////////////////////Every class object for its functions////////

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

	//Avito.printPlayersInv();

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
/*
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
		}
	}

	cout << "	END OF PURCHASE STAGE" << endl;
	
	Avito.printPlayersInv();
*/
////////////////////////CRAFT + PURCHASE STAGES IN ONE GAME CYCLE/////////////

	cout << endl << "	START OF THE GAME " << endl << endl;

	for (int cycle = 0; cycle < 50; cycle++)//in-game cycles
	{
		cout << "	CYCLE " << cycle << endl << endl;
		for (size_t queue = 0; queue < Avito.Players.size(); queue++)//iterate throw Players
		{
			///////////////////////CRAFT/////////////////////////////////

			cout << "Agent #" << queue << " craft turn" << endl;

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

			//////////////////////PURCHASE//////////////////////////////////

			cout << "Agent #" << queue << " purchase turn" << endl;

			item = Avito.Players[queue]->findMin();// searching needed resource
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
		}
	}

	cout << endl << "	END OF THE GAME " << endl;

//////////////////////////////////////////////////////////////////////////////
/*
	cout << "	 TRADE TEST" << endl;
	Avito.Trade(Avito.Players[0], Avito.Players[1], 4);
	Avito.printPlayersInventory();
*/

	return 0;
}
