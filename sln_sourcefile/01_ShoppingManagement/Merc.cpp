#include "Merc.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


Merc::Merc(const char *name, int price, int sale)
{
	strcpy_s(mercName, name);
	mercPrice = price;
	mercSale = sale;
}

Merc::~Merc()
{
}

Merc& Merc::operator=(const Merc & m)
{
	mercSale = m.mercSale;
	mercPrice = m.mercPrice;
	strcpy_s(mercName, m.mercName);

	return *this;
}


void Merc::Show()
{
	cout << setw(15) << mercName << setw(20) << mercPrice << setw(15) << mercSale << endl;
}

void Merc::Print(ofstream &out)
{
	out << mercName << '\t' << mercPrice << '\t' << mercSale << '\n';
}

void Merc::setMerc(const char *name, int price, int sale)
{
	strcpy_s(mercName, name);
	mercPrice = price;
	mercSale = sale;
}

void Merc::setPrice(int price)
{
	mercPrice = price;
}

void Merc::setSale(int changeNum)
{
	mercSale += changeNum;
}

void Merc::saveMerc(ofstream & out)
{
	out << mercName << '\t' << mercPrice << '\t' << mercSale << '\n';
}
