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
		for (int i = 1; i <= Items::Last; i++)
		{
			inv[i] = 0;
		}
	}

	void CraftMoney()
	{
		inv[5]--;
		inv[1]++;
	}

	void CraftMaterial()
	{
		inv[1]--;
		inv[3]--;
		inv[2]++;
	}

	void CraftLabour()
	{
		inv[4]--;
		inv[5]--;
		inv[3]++;
	}

	void CraftFood()
	{
		inv[1]--;
		inv[3]--;
		inv[4]++;
	}

	void CraftGood()
	{
		inv[1]--;
		inv[2]--;
		inv[3]--;
		inv[5]++;
	}

	void print_inventory()
	{
		cout << "inventory:" << endl;

		for (int i = 0; i < Items::Last; i++)
		{
			cout << "[" << i << "] = " << inv[i] << endl;
		}
	}
};


int main(void)
{
	cout << "map test:" << endl;

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

	
	/*
	inventory Inv_1;

	Inv_1[1] = 4;
	Inv_1[2] = 4;
	Inv_1[3] = 4;
	Inv_1[4] = 4;
	Inv_1[5] = 4;

	cout << "inventory test:" << endl;
	for (int i = 1; i < 6; i++)
	{
		cout << "item " << i << " = " << Inv_1[i] << endl;
	}

	Inv_1[3]++;
	Inv_1[4] = 3;

	cout << "\n\nmodified inventory:" << endl;
	for (int i = 1; i < 6; i++)
	{
		cout << "item " << i << " = " << Inv_1[i] << endl;
	}

	*/								
	return 0;
}
