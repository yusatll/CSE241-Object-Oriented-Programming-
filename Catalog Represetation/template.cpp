#include <iostream>
#include "template.h"

using namespace std;


namespace CatalogDatabase
{
	template<class T>
	int Catalog<T>::unique = 0;		//unique ilk değerini atadık

	template<class T>
	void Catalog<T>::openFile()
	{
		//data txt dosyasını okuyup parse eden fonksiyona gönderiyor.
		ifstream datafile(fileName);
		string str;

		getline(datafile,catalogName);			//catalog türünü ilk satırdan alıyoruz
		setPrototype();							//katalog türüne göre prototipi belirliyoruz
		
		//cout << "Catalog Read: " << catalogName << "\n";
		all +=  "Catalog Read: " + catalogName + "\n";		//katalog türünü kayıt ediyoruz

		while(getline(datafile,str))
		{
			lines.push_back(str);				//geri kalan satırları alıyoruz
		}

		parse();				//satırları işlenebilecek hale getiriyoruz.
	}



	template<class T>
	void Catalog<T>::readCommands()
	{
		//commands txt yi okuyup gerekli yere gönderiyor.
		ifstream comFile(commandFile);		

		string str;

		while(getline(comFile,str))
		{
			parseCommands(str);
		}
		program();		//işlemleri ayırt etme yeri
	}
	
	template<class T>
	void Catalog<T>::parseCommands(string s)
	{
		//command ları işlemek için parse ediyoruz
		string del = " ";
		size_t pos=0;
		int i=0;
		vector<string> t;

		while((pos = s.find(del)) != string::npos)
		{
			string str = s.substr(0,pos);
			
			t.push_back(i%2==1 ? str.substr(1,str.length()-2):str);
			//cout << t << endl;
			s.erase(0, pos + del.length());
			i++;
		}
		t.push_back(i%2==1 ? s.substr(1,s.length()-2):s);
		
		coms.push_back(t);				//coms vektöründe tutuyoruz.

		
	}

	template<class T>
	void Catalog<T>::program()
	{
		//gelen komutlara göre önce komutları ekrana bastırıp sonra gerekli fonksiyonları çağırıyoruz.
		for (int i = 0; i < coms.size(); ++i)
		{
			if(coms[i][0] == "search"){
				for(int y =0; y< coms[i].size(); y++){
					//önce ekrana bastıyoruz
					//cout << coms[i][y] << " ";
					if(y%2!=0)
						all += "\"" + coms[i][y] + "\" ";
					else
						all += coms[i][y] + " ";
				}
				//cout << endl;
				all += "\n";
				//sonra gerekli fonksiyona gönderiyoruz
				search(coms[i][1],coms[i][3]);
				//search yapan fonk
			}
			else if(coms[i][0] == "sort"){
				for(int y =0; y< coms[i].size(); y++){
					//cout << coms[i][y] << " ";
					if(y%2!=0)
						all += "\"" + coms[i][y] + "\" ";
					else
						all += coms[i][y] + " ";
				}
				//cout << endl;
				all += "\n";
				sorting(coms[i][1]);
				//sort yapan fonk coms[i][1] gönder
			}
		}
			
	}


	template<class T>
	void Catalog<T>::search(string find, string type)
	{
		//find ı type içinde arayıp yerlerini değiştiriyoruz.
		int index,flag = -1;
		for (index = 0; index < prototype.size(); ++index)
		{
			if(prototype[index] == type){
				flag = 1;
				break;
			}
			else {
				flag = -1;
			}
		}

		try
		{
			if(flag == -1){
				throw flag;
			}
		}
		catch(int f)
		{
			//cout << "Exception: command is wrong\n";
			all += "Exception: command is wrong\n";
			//yanlış bir tip gelirse exceeption throw edilir.
			return;
		}
		

		for(int i = 0; i < database.size(); i++)
		{
 			if(database[i][index].find(find) != string::npos)
			{	//bulunan değerler işlenir
				for(int j = 0; j < database[i].size() ; j++){
					all += "\"" + database[i][j] + "\" ";
					//cout << "\"" << database[i][j] <<"\" " << " " ;
				}
				//cout << endl;
				all += "\n";
			}

		}

	}



	template<class T>
	void Catalog<T>::sorting(string type)
	{
		//gelen type a göre sıralama yapılır.
		int i, j,index;
		int n = database.size();
		for (index = 0; index < prototype.size(); ++index)
		{
			if(prototype[index] == type)
				break;
		}

		//cout << "prototype: " << prototype[index]  << endl;
  		
   		for (i = 0; i < n-1; i++)  
		    for (j = 0; j < n-i-1; j++) 
			   	if (database[j][index] > database[j+1][index])
					swap(j, j+1);

		printDatabase();
	}

	template<class T>
	void Catalog<T>::swap(int in1, int in2)
	{
		//sort için gerekli swap fonksiyonu
		string temp;

		for (int i = 0; i < database[0].size(); i++)
		{
			temp = database[in1][i];
			database[in1][i] = database[in2][i];
			database[in2][i] = temp;
		}
	}

	template<class T>
	void Catalog<T>::setPrototype()
	{
		//katalog türüne göre prototipi belirliyoruz
		if(catalogName == "movie")			//<title> <director> <year> <genre> <starring>
			prototype = {"title", "director", "year", "genre", "starring"};
		else if(catalogName == "book")		//<title> <authors> <year> <tags>
			prototype = {"title", "authors", "year", "tags"};
		else if(catalogName == "music")		//<title> <artists> <year> <genre>
			prototype = {"title", "artists", "year", "genre"}; 
	}


	template<class T>
	void Catalog<T>::parse() 
	{
		//data txt deki verileri kategorilerine göre ayırıyoruz
		vector<string> tmp;
		vector<vector<string>> tempdata;
		
		for (int i = 0, j = 0, t = 0; i < lines.size(); ++i) 
		{
			int counter =0;
			istringstream ss(lines[i]);
			string token;

			while (getline(ss, token, '"')) 
			{
				counter ++;
				if (j % 2 != 0) 
				{

					tmp.push_back(token);
					t++;
				}
				j++;
			}
			tempdata.push_back(tmp);
			
			//eğer eksik kategori gelirse exception throw edilecek.
 			try
			{
				vector<string> th = tempdata[i];
				if(catalogName == "movie"){
					if(counter != 10){
						throw th;
					}
				}
				else{
					if(counter != 8){
						throw th;
					}
				}
			}
			catch(vector<string> t)
			{
				//cout << "Exception: missing field\n";
				all += "Exception: missing field\n";
				//cout << "counter : " << c << endl;
				for (int y = 0; y< t.size(); y++){
					all += "\"" + t[y] + "\" ";
					//cout << "\"" << t[y] << "\" ";
				}
				all += "\n";
				//cout << endl;
				tempdata.pop_back();
				unique++; 			//exception da unique sayısı artıcak

			}
			tmp.clear();

		}
		
		searchInside(tempdata);
		//printDatabase();

	}


	template<class T>
	void Catalog<T>::searchInside(vector<vector<string>> v)
	{
		//aynı title olanları ayıklıyoruz. onları almıyoruz
		int i =0;
		string find;
		for (int i = 0; i < v.size(); ++i)
		{
			find = v[i][0];
			for(int j = i; j < v.size(); j++)
			{
				try
				{
					if(find == v[j][0] && i != j)		//aynı olanlar varsa duplicate olacak.
					{
						vector<string> th = v[j];
						v.erase(v.begin()+j);
						throw (th);
					}
				
				}
				catch(vector<string> t)
				{
					all += "Exception: duplicate entry\n";
					//cout << "Exception: duplicate entry\n";
					for (int i = 0; i < t.size(); ++i)
					{
						//cout << "\""<< t[i] <<"\" ";
						all += "\"" + t[i] + "\" "; 
					}
					all += "\n";
					//cout << endl;
					unique++;
				}
				
			}
			
		}
		
		
		//cout << unique << " unique entries" << endl;
		string uni = to_string(unique);
		all += uni + " unique entries" + "\n";	
		//all += unique + " unique entries" + "\n";
		database = v;

	}


	template<class T>
	void Catalog<T>::printDatabase() 
	{
		//databese i print ediyoruz
		for (vector<string> line : database) {
			for (string data : line){
				all += "\"" + data + "\" ";
				//cout << "\"" << data << "\" ";
			}
			//cout << "\n";
			all += "\n";
		}

	}


}