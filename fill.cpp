#include "GridFill.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{

	int x = 0, y = 0;
	Fill fill;
	string infile;
	string outfile = "";
	int choice = 0;

	for (int i = 1; i < argc; i++)
	{
		try {
			if (!string(argv[i]).compare("-help"))
			{
				cout << "\nUSAGE:\n" <<
					"Fills a selected zone with black color\n" <<
					"Usage: fill [-param] [arg] [-param] [arg]\n";
				system("pause");
				return 0;
			}
			if (!string(argv[i]).compare("-input"))
			{
				++i;
				if (i >= argc) throw "Not enough arguments\n";
				infile = argv[i];
				try {
					std::fstream fin;
					fin.open(infile, std::ifstream::in);
					if (fin.fail())throw std::ifstream::failure("File does not exist");
					fin >> fill;
					fin.close();
				}
				catch (std::ifstream::failure e) {
					std::cerr << "Exception opening file\n" << e.what() << '\n';
					system("pause");
					return 0;
				}
			}
			else if (!string(argv[i]).compare("-output"))
			{
				i++;
				if (i >= argc) throw "Not enough arguments\n";
				outfile = argv[i];
				
			}
			else if (!string(argv[i]).compare("-i"))
			{
				++i;
				if (i >= argc) throw "Not enough arguments\n";
				x = std::atoi(argv[i]);
			}
			else if (!string(argv[i]).compare("-j"))
			{
				++i;
				if (i >= argc) throw "Not enough arguments\n";
				y = std::atoi(argv[i]);
			}
			else if (!string(argv[i]).compare("-queue"))
			{
				choice = 0;
			}
			else if (!string(argv[i]).compare("-stack"))
			{
				choice = 1;
			}
			else if (!string(argv[i]).compare("-recursive"))
			{
				choice = 2;
			}
			else
			{
				std::cerr << "Unknown argument\n";
				system("pause");
				return 0;
			}
		}
		catch (char* error) {
			std::cerr << error;
			system("pause");
			return 0;
		}
	}
	
	switch (choice)
	{
		case 1: 
		{
			fill.fillStack(x, y);
			break; 
		}
		case 2: 
		{ 
			fill.fillRecursive(x, y);
			break; 
		}
		default:
		{ 
			fill.fillQueue(x, y);
			break; 
		}
	}
	if (outfile != "")
	{
		try {
			std::fstream fout;
			fout.open(outfile, std::ofstream::out);
			fout << fill;
			fout.close();
		}
		catch (std::ifstream::failure e) {
			std::cerr << "Exception writing to file\n";
			system("pause");
			return 0;
		}
	}
	else
		cout << fill;

	//Some testing
	Fill f(5, 5);
	f.fillRecursive(2, 2);
	cout << "\nRecursive:\n"; f.printCanvas();
	Fill f1(5, 5);
	f1.fillQueue(2, 2);
	cout << "Queue:\n"; f1.printCanvas();
	Fill f2(5, 5);
	f2.fillStack(2, 2);
	cout << "Stack:\n"; f2.printCanvas();
	Fill f3(5, 5);
	f3.fillStackInefficient(2, 2);
	cout << "StackInefficient:\n"; f3.printCanvas();
	system("pause");
	return 0;
}
