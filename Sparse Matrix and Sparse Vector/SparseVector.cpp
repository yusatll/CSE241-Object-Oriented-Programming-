#include "SparseVector.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

SparseVector::SparseVector()
{
	//cout << "Vector Default Constructor.\n";
}



void SparseVector::openFile()
{
	double d = 0.0;
	int i=0;
	char ignore;
	fstream f;
	f.open(filename);
	if(f.is_open())
		cout << filename << " is opened in openFile\n";

	
	while(!f.eof())
	{
		f >> d;
		vec.push_back(d);		//vectore 	ekliyoruz
		f.get(ignore);			//sayılar arasındaki : ları ignore ediyoruz
	}

	if(vec.size() %2 !=0)		//bazı dosyalarda sondaki sayıyı fazladan okuyor. onları çıkartıyoruz.
		vec.pop_back();

/*
	for (i = 0; i < vec.size(); ++i)
		cout << "vec : " << i << "  "<< vec[i] << endl;
*/	

	f.close();
}

SparseVector::SparseVector(string file)
{
	filename = file;
	//cout << "SparseVector string Constructor\n";
	openFile();		//gelen file ismini açıyoruz.
}

SparseVector & SparseVector::operator+(SparseVector& second)
{
	SparseVector total;
	int i=0,j=0,m=0;
	int min = this->vec.size();
	int index=0;
	//iki vektörü toplayıp totala atıyoruz ama kısa vektörü attıktan sonra uzunun kalan verilerini atmamız lazım.

	//gelen vector lerin uzunluklarına göre resize yapıyoruz
	if(this->vec.size() < second.vec.size()){
		//total.vec.resize(second.vec.size());
	}
	else{
		min = second.vec.size();
		//total.vec.resize(this->vec.size());	
	}

		
	//en küçük olan vektor kadar toplamaları gerçekleştiriyoruz
	while ( m<min )
	{
		if(second.vec[i] < this->vec[j])//vektorölerin indexleri aynı değilse ona göre toplama işlemi yapıyoruz
		{
			total.vec.push_back(second.vec[i]); //indexi alıyoruz
			i++;
			total.vec.push_back(second.vec[i]);		//datayı alıyoruz
			i++;
			if(min == second.vec.size())
				m-=2;
		}
		else if(second.vec[i] > this->vec[j])
		{
			total.vec.push_back(this->vec[j]);
			j++;
			total.vec.push_back(this->vec[j]);
			j++;
			if(min == this->vec.size())
				m-=2;
		}
		else if(second.vec[i] == this->vec[j])//aynı indexteki vektörleri topluyoruz
		{
			total.vec.push_back(second.vec[i]);
			//k++;
			j++;
			i++;
			total.vec.push_back(second.vec[i] + this->vec[j]);
			//k++;
			i++;
			j++;
			
		}
		m+=2;
	}

	//uzun vektörde veya kısa vektörde total e atmadığımız vektöreleri atıyoruz
	while(j < this->vec.size() && i < second.vec.size())
	{
		if(second.vec[i] > this->vec[j])
		{
			
			total.vec.push_back(this->vec[j]);
			j++;
			total.vec.push_back(this->vec[j]);
			j++;
			while(i < second.vec.size())
			{
				total.vec.push_back(second.vec[i]);
				i++;
				total.vec.push_back(second.vec[i]);
				i++;
			}
			
		}
		if(second.vec[i] < this->vec[j])
		{
			total.vec.push_back(second.vec[i]);
			i++;
			total.vec.push_back(second.vec[i]);
			i++;
			while(j < this->vec.size())
			{
				total.vec.push_back(this->vec[j]);
				j++;
				total.vec.push_back(this->vec[j]);
				j++;
			}
		}
	}


	*this = total;

	return *this;
	
}

double dot(SparseVector & first ,SparseVector & second)
{
	//indexlerin çarpımlarının toplamını bulup return eder
	double total = 0.0;
	int index;
	int minsize = first.vec.size();

	if(second.vec.size() < minsize)
		minsize = second.vec.size();

	for (int i = 0; i < minsize; i+=2)
	{
		index = first.findIndex(first.vec[i], second.vec);
		if(index >= 0)
		{			
			total = total + (second.vec[index+1] * first.vec[i+1]);
		}
	}
	
	return total;
}


int SparseVector::findIndex(double a, vector<double> b)
{
	//vector içinde gelen a değerinin indexsini bulup döndürüyor.
	//vectorün çift değerleri index tuttuğu için sadece çift değerlere bakılır.
	if(b.size() == 0)
		return -1;
	int i = 0;
	while(i < b.size())
	{
		if(b[i] == a)
			return i;
		else i+=2;
		
	}
	return -1;
}

SparseVector::~SparseVector()
{
	//cout << "Destructor.\n";
	vec.clear();
}

SparseVector& SparseVector::operator-()
{
	//negatife çeevirme fonksiyonu
	for (int i = 1; i < vec.size(); i+=2)
	{
		vec[i] *= (-1);
	}
	return *this;
}

void SparseVector::write(ostream &output)
{
	//file veya ekrana yazdırma fonksiyonunun heelper fonksiyonu
	for (int i = 0; i < vec.size(); i++)
	{
		output << vec[i];
		if(i %2 == 0)
			output << ':';
		else 
			output << ' ';
	}
	output << endl;
}

SparseVector & SparseVector::operator=( SparseVector & object)
{
	//atama operatörünün overloadı
	vec.resize(object.vec.size());

	for (int i = 0; i < object.vec.size(); i++)
		vec[i] = object.vec[i];
	
	return *this;
}