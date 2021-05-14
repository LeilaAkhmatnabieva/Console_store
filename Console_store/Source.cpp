#include<iostream>
#include<string>
#include<stdio.h>

using namespace std;

class Product;
class Human;
class Sofa;
class Lamp;
class Oven;

class Human
{
public:
	Human()
	{
		this->Name = "User name";
		this->balance = 200000;
		this->Purchases = 0;
	}


	void Print(Human* human)
	{
		cout << "\n" << "Name: " << human->Name << "\n" << "Balans: " << human->balance << "\n" << "Amount of prev. purchases: " << human->Purchases << endl << endl;
	}

	void setName(string Name) { this->Name = Name; }
	void setBalance(int balance) { this->balance = balance; }
	void setPurchases(int Purchases) { this->Purchases = Purchases; }

	string getName() { return this->Name; }
	int getBalance() { return this->balance; }
	int getPurchases() { return this->Purchases; }


	double GetDiscountPrice(int price)
	{
		if ((this->Purchases) < 50000) { return (price); }
		if ((this->Purchases) < 100000) { return price * 0.9; }
		if ((this->Purchases) < 150000) { return price * 0.8; }
		else { return price * 0.7; }
	}

private:
	string Name;
	int balance;
	int Purchases;
	int Discount; //%
};

class Product
{
private:
	int Code;
	static int id;
public:
	Product()
	{
		Code = id;
		id++;
	}

	int GetID() { return this->id; }

	void Print(Human* human)
	{
		printf("%15s\t%15s\t%10d\t%17.1f\t%10d\n", this->Name.c_str(), this->color.c_str(), this->price, (human->GetDiscountPrice(this->price)), this->Code);
	}

	void PrintLine() { cout << "------------------------------------------------" << endl; }

	int GetPrice() { return price; }

	int getMinPrice(Product* product)
	{
		int MinPrice = (*product).GetPrice();
		for (int i = 1; i < (*product).GetID(); i++)
		{
			product++;
			if (MinPrice > (*product).GetPrice())
				MinPrice = (*product).GetPrice();
		}
		return MinPrice;
	}

protected:
	int price;
	string Name;
	string color;
	double length;
	double width;
	double height;


};
int Product::id = 0;

class Sofa : public Product
{
public:
	Sofa(string Name, int price, string color, double length, double width, double height, bool isFold)
	{
		this->Name = Name;
		this->price = price;
		this->color = color;
		this->length = length;
		this->width = width;
		this->height = height;
		this->isFold = isFold;
		Print();
	}

	void Print()
	{
		cout << "Name: Sofa " << this->Name << endl << "Color: " << this->color << endl << "Size: " << this->height << "x" << this->length << "x" << this->width << endl << "Folding sofa: " << this->isFold << endl << "Price: " << this->price << endl << endl;		PrintLine();
	}
private:
	bool isFold;

};

class Lamp : public Product
{
private:
	int power;
public:
	Lamp(string Name, int price, string color, double length, double width, double height, int power)
	{
		this->Name = Name;
		this->price = price;
		this->color = color;
		this->length = length;
		this->width = width;
		this->height = height;
		this->power = power;
		Print();
	}

	void Print()
	{
		cout << "Name: Lamp " << this->Name << endl << "Color: " << this->color << endl << "Soze: " << this->height << "x" << this->length << "x" << this->width << endl << "Power: " << this->power << endl << "Price: " << this->price << endl << endl;
		PrintLine();
	}
};

class Oven : public Product
{
public:
	Oven(string Name, int price, string color, double length, double width, double height, int voltage, int weight)
	{
		this->Name = Name;
		this->price = price;
		this->color = color;
		this->length = length;
		this->width = width;
		this->height = height;
		this->voltage = voltage;
		this->weight = weight;
		Print();
	}

	void Print()
	{
		cout << "Name: Oven " << this->Name << endl << "Color: " << this->color << endl << "Size: " << this->height << "x" << this->length << "x" << this->width << endl << "Votage: " << this->voltage << "Weight: " << this->weight << endl << "Price: " << this->price << endl << endl;
		PrintLine();
	}
private:
	int voltage;
	int weight;
};

class Purchase : public Human
{
public:
	void Buy(Product* prod)
	{
		int DiscPrice = GetDiscountPrice(prod->GetPrice());
		if (DiscPrice > getBalance())
		{
			cout << "Insufficient funds" << endl;
		}
		else
		{
			setBalance(getBalance() - DiscPrice);
			setPurchases(getPurchases() + DiscPrice);// didnt work????
		}
	}
};



int main()
{
	setlocale(LC_ALL, "ru");

	Purchase human;
	string value;
	cout << "Enter your name:" << endl;
	//cin >> value;
	//human.setName(value);
	human.setName("Leila");
	human.Print(&human);

	Oven Gorlig("Gorlig", 14999, "black", 59.4, 56, 58.9, 220, 26);
	Oven Anratta("Anratta", 32999, "black", 59.5, 55, 59.5, 220, 30);
	Lamp Ringsta("Ringsta", 2199, "white/brass", 56, 33, 29, 13);
	Lamp Evedal("Evedal", 15999, "marble/grey", 34, 52, 28, 13);
	Sofa Friheten("Friheten", 23999, "dark-grey", 88, 230, 151, true);
	Sofa Landskrona("Landskrona", 49999, "dark-grey", 164, 89, 78, false);

	Product* product = new Product[Landskrona.GetID()]{ Gorlig, Anratta, Ringsta, Evedal, Friheten, Landskrona };
	int Code;
	int MinPrice = product->getMinPrice(&product[0]);
	while (human.GetDiscountPrice(MinPrice) < human.getBalance())
	{
		printf("\n%15s\t%15s\t%10s\t%17s\t%10s\n", "Name", "Color", "Price", "Sale price", "Product code");
		for (int i = 0; i < Landskrona.GetID(); i++)
		{
			product[i].Print(&human);
		}
		human.Print(&human);
		cout << "Enter the product code you want to buy:" << endl;
		cin >> Code;

		while (((product->GetID()) <= Code) | (Code < 0))
		{
			cout << "This product does not exist! Re-enter the code:" << endl;
			cin >> Code;
		}
		human.Buy(&(product[Code]));
		product->PrintLine();
	}

	cout << "Insufficient funds." << endl;



	delete[] product;

	return 0;
}