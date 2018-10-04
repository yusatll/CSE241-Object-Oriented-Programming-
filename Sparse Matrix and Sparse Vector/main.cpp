#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SparseVector.h"
#include "SparseMatrix.h"

/***************
SparseVector tam çalışıyor.
SparseMatrix dosyadan okuma yok. Bİrkaç tane operator overloadlar var.>*/

using namespace std;

int main()
{
	string s,s2;
	/*
	ofstream outfile;
	ifstream inputfile,inputfile2;
	outfile.open("output.txt", ios::out | ios::trunc );
	inputfile.open("input.txt");
	//trunc : 	If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one.	
	
	ifstream openmatrix;
	openmatrix.open("m.txt");
	*/
	
/*
	SparseVector sv("input.txt");
	SparseVector y1("yusa.txt");

	ofstream couttofile;
	couttofile.open("output.txt", ios::out | ios::trunc );
	cout << "sv objesinin vec:\n";
	cout << sv; 			//sv ojesinin içindeki vec basar
	cout << endl;

	cout << "y1 objesinin vec:\n";
	cout << y1; 			//sv ojesinin içindeki vec basar
	cout << endl;

	vector<double> v = {2,15.6, 4,22.4, 7,12.9, 20,18.5};
	
	//couttofile << sv;

	sv = y1 + sv;

*/

	SparseMatrix sm("m1.txt");


	//Creating a SparseVector from file
	//SparseVector a1("a1.txt");
	//outfile<<"a1"<<endl<<a1<<endl;
	

	//Binary operations and assignment
	//a1 = a1 + a1;
	//outfile<<"a1"<<endl<<a1<<endl;
	

	//Creating SparseMatrix from file
	//SparseMatrix m1("m1.txt");
	//SparseMatrix m2("m2.txt");
	
	//outfile<<"m2"<<endl<<m2<<endl;
	
	//Transpose
	//outfile<<m2.transpose()<<endl;
	
	//Dot product
	//outfile<<dot(a1,a1)<<endl;


	

	return 0;
}