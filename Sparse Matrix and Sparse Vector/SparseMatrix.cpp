#include "SparseMatrix.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <cstdio>
using namespace std;

SparseMatrix::SparseMatrix(string file)
{
	//gelen file name i class içindeki stringe atıyoruz
	filename = file;
	openFile();
}

void SparseMatrix::openFile()
{
	ifstream f;
	f.open(filename, ios::in);

	vector<vector<double>> line;
	vector<double> tempd;
	vector<string> linestr;
	string str;
	double d;

	int i=0;

	if(f.is_open())
		cout << filename << " is opened in openFile\n";


	while(getline(f,str))
	{

		while(i<str.size())
		{
			sscanf(str.c_str(),"%lf",&d);
			cout << "d: " << d<<endl;
			tempd.push_back(d);
			i++;
		}

	}


	f.close();
}

void SparseMatrix::write(ostream &output)
{
	//operator << yardımcı fonksiyonu
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = 0; j < vec[i].size(); ++j)
		{
			output << vec[i][j];
		}
		output << endl;
		
	}
}
SparseMatrix & SparseMatrix::operator=(SparseMatrix & object)
{
	//assingment operator overload ı
	vec.resize(object.vec.size());
	for (int i = 0; i < object.vec.size(); ++i)
	{
		for (int j = 0; j < object.vec[i].size(); ++j)
			this->vec[i][j] = object.vec[i][j];
	}
	
	
	return *this;
}

SparseMatrix& SparseMatrix::operator-()
{
	//gelen matrixi eksiye dönüştürmee fonksiyonu
	for (int i = 0; i < this->vec.size(); ++i)
	{
		for (int j = 0; j < this->vec[i].size(); ++j)
		{
			this->vec[i][j] *= -1;
		}
	}
	return *this;
}