/************************
*						*
*	Ahmet Yuşa Telli	*
*		151044092		*
*						*
*************************/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
/*MALLOC KULLANMADAN YAPILMIŞTIR*/
using namespace std;

string trivial(string greeting = "!!!WELCOME!!!");


void welcome(string& withWho, int& size);
void initBoard(int size, char board[20][20]);
int userPlay(char userType, char column, char board[20][20], int size);
bool finish(int size, char board[][20]);/*oyunda boş yer varmı onu kontrol ediyor.*/
void printBoard(int size, char board[20][20]);
int checkColumn(int size, char column, char board[20][20]);
int checkWinner(char userType, char board[][20], int i, int column, int size,int win[4][2]);
int playGame(char user1, char user2, int size, char board[20][20],string withWho);
void toZero(int win[][2],int size);
void print(int win[][2],int size);
void winnerBoard(int win[4][2], char board[20][20], int size);
int computerPlay(char userType, char board[20][20], int size);
int checkThree(int find[3][2],int findO[3][2],char board[20][20],int size, int& x, int& y);

int checkInput(string line, int &size, string &kimde,char board[20][20],string& komut,string& ikili);

int main()
{
	int size;
	char user1,user2;
	char board[20][20];
	string withWho;
	string lastplayer;

	/*deneme*/
	string what = trivial();
	cout << what << endl;

	what = trivial("!!!THE CONNECT FOUR GAME!!!");
	cout << what << endl;

	welcome(withWho,size);

	user1 = 'X';
	user2 = 'O';

	playGame(user1,user2, size, board,withWho);

	return 0;
}

string trivial(string greeting){
	return greeting;
}

int checkInput(string line, int& size, string& kimde, char board[20][20],string& komut,string& ikili)
{
	/*adı belli olan dosyadan bilgileri sırasıyla alır.*/
	ifstream fin;
	ofstream fout;
	char bosluk;/*dosyanın içindeki \n ve space gibi karakterler için kullandım*/

	string strboard;/*ilk önce boardı line olarak string e aldım*/
	string filename,boyut;
	istringstream iss(line);

	iss>> komut;

	iss >> filename;
	const char *file = filename.c_str();


	/*ilk hamlede load falan girilirse kontrol ediyor.*/

	if(komut == "LOAD" || komut == "load")
	{
		cout<<"LOAD : " << endl;
		fin.open(file);

		if(fin.fail())
			cerr << file <<" does not open!!\n";
		//dosyadan al

		/*ilk baştaki size ı aldık.*/
		getline(fin,boyut);
		istringstream (boyut)>>size;
		
		/*size dan sonra gelen \n i aldık boşa.*/

		/*en son kimde kaldığını aldık.*/
		getline(fin,kimde);

		/*pvp veya pvc oyunu*/
		getline(fin,ikili);
		fin.get(bosluk);

		int i=0,j=0,m;
		
		for(m=0;m<size;)
		{
			/*önce file'dan line olarak alıyoruz. sonra line'ı direk 2D array içine
			atıyoruz.*/
			getline(fin,strboard);
			for(j=0;j<size;)
			{
				if(strboard[i] != ' ')
				{
					board[m][j] = strboard[i];
					j++;
					if(j>=size)
						m++;
				}
				i++;
			}
			i=0;
		}

		fin.get(bosluk);
		
		fin.close();
	}	
	else if(komut == "SAVE" || komut == "save")
	{/*gelen değerleri belirtilen isimdeki dosyaya yazıyor.*/
		cout << "SAVE : \n";
		fout.open(file);
		if(fout.fail())
			cerr << file << " does not open!!\n";
		//dosayaya yaz.
		/*dosyada önce size sonra kimde kaldığı ve en son board şeklini yazıyor.*/
		fout << size << endl;
		fout << kimde << endl;
		fout << ikili<<endl;//pvp mi pvc mi?
		int i,j;
		for (i = 0; i < size; ++i)
		{
			for(j=0;j<size;j++)
				fout << " "<< board[i][j];
			fout << endl;	
		}
		cout << "GAME SAVED." <<endl;
		fout.close();
	}

	return 1;

}


void welcome(string& withWho, int& size)
{
	/* bu fonksiyonda kullanıcıdan ön bilgiler alınıyor. bilgisayara karşı
	veya diğer kullanıcıya karşı oynamak istediği öğreniliyor. oynanmak
	istene board'ın genişliği öğreniliyor ve hangi karakter ile oynamak
	istediği öğreniliyor. */
	bool tf=true, tboard = true;
	int number=0;
	char bosluk;
	
	cout << "How long do you want a playground?" << endl
		<< "(4x4, 6x6, ... 20x20) Min: 4x4 \t Max: 20x20 (even number)" << endl;
	cin >> size;

	while(tboard)
	{
		if(size >= 4 && size <= 20 && size % 2 == 0)
			tboard = false;
		else
		{
			cerr << "Please enter again." << size << " is wrong number. " << endl
				<< "Enter an EVEN number greater than 4 and smaller than 20." << endl;
			/* https://stackoverflow.com/questions/5131647/why-would-we-
			call-cin-clear-and-cin-ignore-after-reading-input */
			/* karakter girilince sonsuz döngüye giriyordu.
			bu linkdeki gibi yapınca düzeldi.*/
			cin.clear();
			cin.ignore(1000,'\n');
			cin >> size;
			
		}
	}	

	cout << "Do you want to play with player2 or computer?" << endl
		 << "i) for player2 enter 'P' " << endl << "ii) with computer enter 'C' " << endl;
	cin >> withWho;
	while(tf)
	{
		if( withWho == "p" || withWho == "c" || withWho == "C" || withWho == "P")
			tf = false;
		else
		{
			cerr << "Please choose one." << endl
				 << "i) for player2 enter 'P' " << endl << "ii) with computer enter 'C' " << endl;
			cin >> withWho;	 
		}
	}
}

int playGame(char user1, char user2, int size, char board[20][20], string withWho)
{
	/*oyun burada oynanıyor. oyuncunun hamleleri burada alınıyor. kontrollerin 
	yapılması için fonksiyonlar burada çağırılıyor.*/
	int i=0;
	string column,ikili="pvp";
	string kimde,komut;
	auto chColumn = '\0';
	char bosluk;
	string first = "user1",second = "user2";
	string sirakimde,siradaki="user1";
	bool cont = true,user=true;
	int finished = 1,cmpFinish=0;
	initBoard(size,board);
	
	cin.get(bosluk);/*önceden p veya c girerken enter a basınca \n i burada
			alıyordu. ondan dolayı burada boş bir char alıyorum.*/
	if(withWho == "c" || withWho == "C")
	{
		ikili = "pvc";
		user = false;/*bilgisayarla oynanmak istenirse user2yi devreden çıkartıyoruz*/
		sirakimde = "user1";/*bilgisayara karşı oynarken save için herzaman
		user1 in oyun sırası olur.*/
	}
	
	cout << "Let's start the game!!!" << endl;
	while(finished && !cmpFinish)
	{/************************USER1 OYNANIŞ YERİ******************************/
		while(cont)
		{
			cout << "User 1: (" << user1 << "):";
			
			getline(cin,column);
			if(column.length() != 1)
			{
				
				sirakimde = "user1";
				checkInput(column, size, sirakimde,board,komut,ikili);

				if(komut == "LOAD" || komut == "load")
				{/* load dan sonra user2 mi computer mi oyun ayarlıcak.*/
					if(sirakimde == "user2")
					{
						siradaki = "user2";
						user = true;
					}
					else if(sirakimde == "user1")
					{
						siradaki = "user1";
						if(ikili == "pvp")
							user= true;
						else if(ikili == "pvc")
							user = false;
						
					}
				
					printBoard(size,board);
				}
				else if(komut == "SAVE" || komut == "save")
				{
					if(ikili == "pvp")
						siradaki = "user2";
					else
						siradaki = "computer";
				}
	
				printBoard(size,board);

				
				if(siradaki == "user1")
					getline(cin,column);
				else
					break;
			}

			if (column.length() == 1){
				chColumn = column[0];
				
			}
		
			if(checkColumn(size,chColumn,board) < 0 && siradaki == "user1")
			{
				if(column.length()==1)
					cerr << "!!! Wrong column or Column filled. Please choose another one. !!!" << endl;
				printBoard(size,board);
				
			}
			else
			{
				cont = false;
				if(siradaki == "user1")
					if(userPlay(user1,chColumn,board,size) == 1)
					{/*kazanan varsa 1 döner*/
						finished = 0;
					}
			}

			if(ikili == "pvp")
				siradaki = "user2";
			else if(ikili == "pvc")
				siradaki = "computer"; 
		}
		cont = true;

		if(user)/********************USER2 OYNANIŞ YERİ***********************/
		{/*computer oyundaysa user2 devre dışı kalır*/
			if(finished && siradaki == "user2")
			{
				while(cont)
				{
					cout << "User 2 (" << user2 << "): ";
					getline(cin,column);
					if (column.length() != 1)
					{
						sirakimde = "user2";
						checkInput(column, size, sirakimde,board,komut,ikili);
						
						if(komut == "LOAD" || komut == "load")
						{/*load komutu gelirse siradaki oyuncuyu ve en son kim 
							oynadığına göre oyunun gidişatını ayarlıyor.*/
							if(sirakimde == "user2")
							{
								siradaki = "user2";
								user = true;
							}
							else if(sirakimde == "user1")
							{
								siradaki = "user1";
								if(ikili == "pvp")
									user= true;
								else
									user = false;
								
							}
							printBoard(size,board);
						}
						
					}
					if (column.length() == 1){
						chColumn = column[0];
					}
				
					if((checkColumn(size,chColumn,board) < 0) && (sirakimde == "user2"))
					{
						if(column.length()==1)
							cerr << "!!! Wrong column or Column filled. Please choose another one. !!!" << endl;
						printBoard(size,board);
					}
					else
					{
						cont = false;
						if(siradaki == "user2")
							if(userPlay(user2,chColumn,board,size) == 1)
							{/*kazanan varsa 1 döner*/
								finished = 0;
							}
					}
				}	
				cont = true;
			}

			siradaki = "user1";
		}
		else if(!user && !cmpFinish && finished)
		{/**************COMPUTER OYNANIŞ YERİ **************************/
			cout<< "COMPUTER PLAY :\n";
			if(computerPlay('O',board,size) == 1)
				cmpFinish = 1;
			printBoard(size,board);
			siradaki = "user1";
		}


		if(finished == 0 || cmpFinish == 1)
		{	/*oyunu bitir*/
			return 1;
		}

	}/*END while*/

}


void initBoard(int size, char board[20][20])
{
	/* sadece oyun başında board initial ediliyor ve ekrana düz yazılıyor.*/
	int i=0,j=0;
	for (i = 0; i < size; ++i)
		for (j = 0; j < size; ++j)
			board[i][j] = '.';

	printBoard(size,board);
}

int userPlay(char userType, char column, char board[20][20], int size)
{
	/*user 1 ve user 2 nin oyunu oynadığı yer.*/
	int play=0,tempSize,i;
	bool control = true;
	char tempColumn = column;
	int win[4][2] = { {0,0},{0,0},{0,0},{0,0} };

	if(tempColumn>=97 && tempColumn <= 122)
		play = (int)tempColumn - 97;
	else if(tempColumn >= 65 && tempColumn <= 90)
		play = (int)tempColumn - 65;

	tempSize = size-1;


	if(userType>=97 && userType <= 122)
		userType -= 32;//küçük harfi büyültme
		
	if(checkColumn(size,tempColumn,board) <0)
		return -1;//yanlış column girilirse 

	for(i = tempSize; i >= 0 && control; i--)
	{
		if(board[i][play] == '.')
		{
			control = false;
			board[i][play] = userType;
		}
	}
	i++;
	
	if(checkWinner(userType, board,i,play,size,win) == 1)
	{/*kazanan varsa board'u bas. ve 1 döndür*/
		winnerBoard(win,board,size);
		return 1;
	}
	
	printBoard(size,board);
	return 0;
}

void printBoard(int size, char board[20][20])
{/*sadece board'u ekrana basar.en son halini.*/
	int i=0,j=0;
	char alphabet = 'a';
	for (i = 0; i < size; ++i,++alphabet)
	{
		cout << ' ' << alphabet;
	}
	cout << endl;

	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
			cout << " " << board[i][j];
		cout << endl;
	}
	cout << endl;

}

bool finish(int size, char board[20][20])
{
	/*oyunun bitip bitmediğini kontrol ediyor. doğru dönerse yer bitmiştir.
	yanlış dönerse hala yer kalmış demektir.*/
	
	int j ,k;
	for (j = 0; j < size; ++j)
		if (board[0][j] == '.')
			return false;
		else
			return true;
		
}


int checkColumn(int size, char column, char board[20][20])
{/*column un uygun olup olmadığı ve o sıranın tümünün dolu olup olmadığını kontrol
	ediyor.*/
	int col;
	if(column>=97 && column <= 122)
		col = (int)column - 97;
	else if(column >= 65 && column <= 90)
		col = (int)column - 65;

	if(col > size || board[0][col] != '.')
		return -1;
	else
		return 1;
}

int checkWinner(char userType, char board[20][20], int i, int column, int size,int win[4][2])
{
	/*burada kazananı belirliyoruz. 4 tane userType yanyana veya çapraz gelirse 
	o kişi kazanıcak.*/
	/* userType kulanıcının kullandığı X veya O.
	i : girilen koordinatın x kısmı.*/
	int dortluk =0, wx=0,wy=0;
	int minx, miny, maxx, maxy,x=0,y=0;
	int j=0,k=0,m=0;
	
	minx = i - 3;
	maxx = i + 3;
	miny = column - 3;
	maxy = column + 3;

	toZero(win,4);

	if(column < 3)
		miny = 0;
	if(column+3 > size-1)
		maxy = size-1;
	if(i<3)
		minx = 0;
	if(i+3 > size-1)
		maxx = size-1;

	/*en soldan en sağa 4lü arama: */
	for (j = miny,wx=0,wy=0; j <= maxy ; ++j)
	{
		if(board[i][j] == userType)
		{
			win[wx][wy] = i;
			wy++;
			win[wx][wy] = j;
			wx++;
			wy=0;
			dortluk++;
			/*4lük yer bulunursa diye kontrol için her döngüden sonra if koydum.*/		
			if(dortluk == 4)
				return 1;
		}
	
		else
		{
			dortluk = 0;
			toZero(win,4);
		}
	}

	/*yukarıdan aşağıya 4lü arama: */
	for(k = minx,wx=0,wy=0; k <= maxx ; ++k)
	{
		if(board[k][column] == userType)
		{
			dortluk++;
			win[wx][wy] = k;
			wy++;
			win[wx][wy] = column;
			wx++;
			wy=0;

			if(dortluk == 4)
				return 1;
		}

		else
		{
			dortluk=0;
			toZero(win,4);
		}
	}	
	
	/*sol üstten sağ alta çapraz arama: */
	for(j = miny, k = minx,wx=0,wy=0; j <= maxy || k <= maxx; ++j, ++k)
	{
		if(board[k][j] == userType)
		{
			dortluk++;
			win[wx][wy] = k;
			wy++;
			win[wx][wy] = j;
			wx++;
			wy=0;
			if(dortluk == 4)
				return 1;
		}
		else
		{
			dortluk = 0;
			toZero(win,4);
		}
	}
	
	/*sağ üstten sol alta çapraz arama: */
	for(k = minx, m = maxy,wx=0,wy=0; (k <= maxx || m >= miny) && m>=0 ; ++k, --m)
	{
		if(board[k][m] == userType)
		{	
			dortluk++;
			/*arrayda kazanan yerleri tutuyoruz.*/
			win[wx][wy] = k;
			wy++;
			win[wx][wy] = m;
			wx++;
			wy=0;
			if(dortluk == 4)
				return 1;
		}
		else
		{	
			dortluk = 0;
			toZero(win,4);
		}
	}

	return 0;
}

void toZero(int win[][2], int size)
{/*çözüm arrayini sıfırlamak için fonksiyon yazdım.*/
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < 2; ++j)
			win[i][j] = 0;
}

void print(int win[][2],int size)
{/*çözüm arrayini sıfırlamak için fonksiyon yazdım.*/
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < 2; ++j)
			cout << win[i][j];
		cout << endl;
	}
}

void winnerBoard(int win[4][2], char board[20][20],int size)
{/*kazanan yerin koordinatlarını bir array de tutmuştuk.
	burada o arrayin yerlerini küçütüyoruz.*/
	int x=0,y=0,j=0;
	for (int i = 0; i < 4; ++i)
	{
		x = win[i][j];					
		y = win[i][j+1];
		board[x][y] = board[x][y] +32;
	}
	//cout << "WINNER BOARD : \n";
	if(board[x][y] == 'x')
	{
		cout<<"!!!USER1 WIN!!!\n";
		printBoard(size,board);
	}
	else
		cout<<"!!!USER1 LOSE!!!\n";
	//printBoard(size,board);
}

int computerPlay(char userType, char board[20][20], int size)
{
	/*computer in oyunu oynadığı yer.*/
	int findX[3][2],findO[3][2];
	bool end=true;
	char column,yplay;
	int m,t,g,e,random=0;
	int x=0,y=0,k=0,i=0,j=0;

	for (e = size-1; e >=0; --e)
		for (g = 0; g < size; ++g)
			if(board[e][g] == 'X')
			{
				k++;
				i=e;
				j=g;
			}
	
	if(k == 1)/*ilk el olarak user1 in yanına koyduk.*/
	{
		if(board[i][j+1] == '.' && board[i][j+1] != 'X')
			board[i][j+1] = 'O';
		else
			board[i][j-1] =	'O';
	}	
	else if(k == 2)
	{/*ikinci adım*/
		for(m=0; m < size && end; ++m)
		{/*eğer kullanıcı alttan ikinci satıra x koyarsa : */
			if(board[size-2][m] == 'X')
			{
				if(board[size-1][m] == 'X')
				{/*X'in üstüne X koyarsa ikiliyi boz*/
					board[size-3][m] = 'O';
					end=false;
				}
				else if(board[size-1][m] == 'O')
				{/*O'nun üstüne koyarsa O'nun yanına koy*/
				
					board[size-1][m+1] = 'O';
					end=false;
				}
			}
			else
				if(board[size-1][m] == 'O')
				{
					if(board[size-1][m+1] == '.')
					{
						board[size-1][m+1] = 'O';
						end=false;
					}
					else
						board[size-1][m-2] = 'O';

				}
		}
		end=true;
	}
	else if(k >= 3)
	{	
		if(checkThree(findX,findO,board,size,x,y) == 1)
		{
			yplay = (char)y+97; 
			if(userPlay('O',yplay,board,size) == 1)
				return 1;
		}
		else
		{
			srand(time(NULL));
			random = (rand() % size);
			column = (char)random+97;
			random=0;
			if(userPlay('O',column,board,size) == 1)
				return 1;
			
		}
	}
	return 0;
}


int checkThree(int findX[3][2],int findO[3][2],char board[20][20],int size,int& x,int& y)
{
	/*3 tane x veya 3 tane o kontrolü yapıyor.*/
	int three=0,m=0,t=0,n=0,g=0;
	int j,i,uclu=0;
	bool check =true;
	bool bitir = true;

	toZero(findX,3);
	toZero(findO,3);
	/*sağdan sola 3X kontrolü : */
	for(i=size-1; (i>=0 && check); --i)
	{	/*önce yerleri bulup 3x2lik arrayde koordinatları tuttuk.
	eğer 2tane bulursa içini boşalttık.*/
		for(j=size-1; j>=0;--j)
		{
			if(board[i][j] == 'X')
			{	
				findX[m][t] = i;
				t++;
				findX[m][t] = j;
				m++;
				t=0;
				three++;
				if(three == 3)
					check = false;
			}
			else
			{
				if(check)
				{
					toZero(findX,3);
					three=0;
					m=0;
					t=0;
				}
			}		
		}
	}
	if(!check)
	{
		x=findX[0][0];
		y=findX[2][1]-1;
		return 1;
	}

	/*3 tane O nun yan yana olmasını konrtol et.*/

	for(i=size-1; (i>=0 && bitir); --i)
	{
		for(j=size-1; j>=0;--j)
		{
			if(board[i][j] == 'O')
			{
				findO[n][g] = i;
				g++;
				findO[n][g] = j;
				n++;
				g=0;
				uclu++;
				if(uclu == 3)
					bitir=false;
			}
			if(bitir)
			{
				toZero(findO,3);
				uclu=0;
				n=0;
				g=0;
			}
		}	
	}

	if(!bitir)
	{
		x=findO[0][0];
		y=findO[2][1]-1;
		return 1;
	}


	check = true;
	/*aşağıdan yukarıya 3X kontrolü : */
	/*önce yerleri bulup 3x2lik arrayde koordinatları tuttuk.
	eğer 2tane bulursa içini boşalttık.*/
	m=0;
	t=0;
	for(j=0; j<size && check; ++j)
	{
		for(i=size-1; i>=0; --i)
		{
			if(board[i][j] == 'X')
			{
				findX[m][t] = i;
				t++;
				findX[m][t] = j;
				m++;
				t=0;
				three++;
				if(three == 3)
					check = false;
			}
			else
			{	
				if(check)
				{
					toZero(findX,3);
					three=0;
					m=0;
					t=0;
				}
			}
		}
	}

	if(!check)
	{
		x = findX[2][0] -1;
		y = findX[0][1];
		return 1;
	}

	return 0;
}