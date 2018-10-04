#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <vector>

using namespace std;

/*************************
Sparse Matrix Classı
Operatör overload içerir.

FOSYADAN OKUMA İŞLEMİNİ YAPAMADIM. DİĞER YAPTIĞIM OPERATÖR OVERLOADLAR ÇALIŞIYOR.
*/


class SparseMatrix
{
public:
	SparseMatrix(){ }
	SparseMatrix(string file);
	//SparseMatrix(vector<double> v) { vec = v; }

	void openFile();

	//operator+ : Adds two matrices
	
	//operator- : Subtracts one matrix from another
	SparseMatrix& operator-();

	//operator- : Negates elements of a matrix
	
	//operator= : Assigns one matrix to another
	SparseMatrix & operator=(SparseMatrix & obj);


	//operator<< : Sends contents of a SparseMatrix to a std::ostream object.
	friend ostream &operator<<(ostream & output, SparseMatrix & obj) 
	{
		obj.write(output);
		return output;
	}

	void write(ostream& output);
	
	//operator* : Multiplies two matrices (Regular matrix multiplication)
	
	//function transpose : Returns the transpose of a matrix
	//∗ Creates another SparseMatrix which is the transpose of the original object.

	vector<vector<double>> vec;
	string filename;

	//~SparseMatrix();
	
};


#endif