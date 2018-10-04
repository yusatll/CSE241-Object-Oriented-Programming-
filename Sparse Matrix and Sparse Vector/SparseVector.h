#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H


#include <iostream>
#include <vector>
#include <string>

using namespace std;


/*********************************
SPARSE VECTOR CLASSI
OPERATOR OVERLOAD İÇERİR.
************************************/

class SparseVector
{
public:
	SparseVector();
	SparseVector(string file);
	SparseVector(vector<double> v) { vec = v; }
	void openFile();


	//operator+ : Adds two SparseVectors
	//friend SparseVector & operator+(SparseVector& frist, SparseVector& second);
	SparseVector & operator+(SparseVector& second);
	int findIndex(double a, vector<double> b);
	

	//operator- : Subtracts one SparseVector from another
	
	//operator- : Negates elements of a SparseVector
	//Creates another SparseVector object which is element-by-element negative of the operant.
	SparseVector& operator-();
	

	//operator= : Assigns one SparseVector to another
	SparseVector & operator=( SparseVector & object);
	
	//operator<< : Sends contents of a SparseVector to a std::ostream object.	
	//Creates the text representation of a SparseVector and sends it to a std::ostream object. (See
	//Text Representations section for more details)
	friend ostream &operator<<(ostream & output, SparseVector & obj) 
	{
		obj.write(output);
		return output;
	}

	void write(ostream& output);
	


	//function dot : Calculates the dot product(inner product) of two SparseVectors
	//Returns a real number (See Dot Product Section for more details)
	friend double dot(SparseVector & first ,SparseVector & second);


	~SparseVector();
	//vektörü burada tutuyoruz
	vector<double> vec;
	string filename;
};


#endif