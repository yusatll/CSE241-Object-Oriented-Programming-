#ifndef TEMPLATE_H
#define TEMPLATE_H


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

namespace CatalogDatabase
{

	template<class T>
	class Catalog
	{
	private:
		vector< vector< string> > database;				//DOSYAYI PARÇALAYIP BURAYA KOYACAĞIZ
		vector< string> lines;							//DOSYAYI İLK OLARAK BURAYA ALIYORUZ
		vector<string> prototype;						//KATEGORENİN TÜRÜNE GÖRE PROTOTİPİNİ OLUŞTURACAĞIZ
		vector<vector<string> > coms;					//

		string catalogName;								//kataloğun türünü kayıt ettiğimiz yer
		string fileName;								//data.txt yi tuttuğumuz yer
		string commandFile;								//commands.txt yi tuttuğumuz yer
		string outputFile;								//output.txt yi tuttuğumuz yer

		string all;										//en son file a yazmak için tüm sonucu bir stringe alıp öyle file a gönderiyoruz
		static int unique;								//exception ların sayısını tutuyoruz.
		ofstream out;		

	public:

		Catalog()
		{
			fileName = "data.txt";
			commandFile = "commands.txt";
			outputFile = "output.txt";

			openFile();									//ilk file ı okuyoruz.
			readCommands();								//commands ları okuyoruz.

			out.open(outputFile, ios_base::out | ios_base::trunc);

 
		}

		Catalog(string file)
		{
			fileName = file;
		}
		Catalog(string s1, string s2)
		{
			fileName = s1;
			commandFile = s2;
		}
		~Catalog()
		{
			out << all;
			out.close();
		}

		void openFile();														//file açıp kapama.
		void searchInside(vector< vector< string> > temp);						//içinde başka aynı title da varmı diye bakılacak
		void parse();															//katalog bilgilerini parse ediyoruz
		void printDatabase();													//database i ekrana bastıyoruz
		void readCommands();													//commadns dekileri alıyoruz
		void parseCommands(string s);											//commands ı parse ediyoruz
		void program();															//commands daki işlemleri yapıyoruz
		void sorting(string type);												//sort işlemi
		void swap(int in1, int in2);								
		void search(string find, string type);			

		vector< vector< string> > getDatabase() { return database; }
		string getCatalog() { return catalogName; }

		void setCatalog(string name) { catalogName = name; }
		void setPrototype();						//KATOLOGUN TÜRÜNE GÖRE PROTOTİPLERİ BELİRLİYORUZ.

	};
}

#endif