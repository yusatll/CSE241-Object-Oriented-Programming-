/*
*********************************************
*											*
*		Ahmet Yuşa Telli					*
*		151044092							*
*											*
*											*
*********************************************
*/
/* PROGRAMIN NE YAPTIKLARININ ÖZETİ:
	
programda 3 adet class bulunmakta. 1 ana Game class'ı, 1 Player inner class'ı, 1 Card inner Classı.
başta game classsının objesini oluşturuyoruz ve bu obje üzerinden oyun oynanıyor. 

OYUNDA ŞUNLAR YAPILABİLİYOR:
+random olarak kart üretiyor.6x12 boyutunda.
+boardı boş olarak ekrana bastırıyor. 20x40 boyunda.
+boardın üzerindeki 'o' lara random olarak X ve Y oyuncularını atıyoruz.
+oyuncuların her birine random olarak 3er tane kart dağıtıyoruz.
+oyuncular bu kartlardan istediklerini seçip,isterse döndürebiliyor veya döndürmüyor.
+kartı boarddaki istediği noktaya koyabiliyor.
+kart boarda koyulduktan sonra oyuncuya yeni bir kart veriliyor.
+oyun 2 oyuncudan oluşuyor ve 3x3 lük boardda oynanıyor.
+kartlar sağ, sol, ve 180 derece (tam ters yönde) dönebiliyor.


OYUNDA EKSİK OLAN ŞEYLER:
-OYUNDA SADECE X VE Y HAREKET ETMİYOR. VE KAZANAN KAYBEDEN BELLİ DEĞİL. DİĞER FONKSİYONLAR ÇALIŞIYOR.


*/

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstring>

using namespace std;

/*******************************************************************/
/************************************* GAME CLASS ******************/
/*******************************************************************/
class Game
{
public:
	Game();
	void playGame();
	void initBoard(int size);
	void printBoard(char b[20][40]);
	char board[20][40];
	void emptyBoard(char b[20][40]);
	void randomXY();
	int *findXY(char a);

	void play();

	/*********************************************************************/
	/************************************* PLAYER CLASS ******************/
	/*********************************************************************/
	class Player
	{
	public:
		
		Player();
		void setToken(char newtoken) { token = newtoken;}
		char getToken() {return token;}
		void takeCard();

			/*******************************************************************/
			/************************************* CARD CLASS ******************/
			/*******************************************************************/
			class Card
			{
			public:
				
				Card();
				Card creatCard();
				void printCard(char arr[6][12]);
				Card rotate(int way, Card c);              	 	    //girilen değere göre döndürme
				bool isThere(char arr[4][2], char f);				//daha önceden arrayin içinde o değer var mı onu kontrol ediyor.
				void toempty(char c[6][12]);
				int *findindex(char c[6][12],char t);
				int path(char c[6][12],char in[4][2]);



			public:							//card private
				char card[6][12];
				int cardID;

			};/************************CARD END***************************/

				
	public:
		void setCard1(Card c1) { card1 = c1;}
		void setCard2(Card c2) { card2 = c2;}
		void setCard3(Card c3) { card3 = c3;}
		Card getCard1() { return card1; }		
		Card getCard2() { return card2; }
		Card getCard3() { return card3; }	

	private: 			//player private
		char token;
		Card card1;
		Card card2;
		Card card3;

	};	/*************************PLAYER END********************************/


public:
	void addboard(Game::Player::Card c, int coordinate);	
	Player player1;
	Player player2;
private:
	int size;	
	
};

Game::Game()
{
	printf("Welcome to Tsuro Game!!!\n");
	player1.setToken('X');
	player2.setToken('Y');
}

Game::Player::Player(){}

Game::Player::Card::Card(){}

int main()
{
	int tur=0;
	Game game1;
	int p1card , rotate1 , coordinate =0;
	game1.initBoard(3);		//oyunun boardını initialize ediyoruz.
	game1.randomXY();		//boardda random yerlere X ve Y atıyoruz.
	//game1.play();

	game1.player1.takeCard();		//player 1 için 3 tane kart alıyoruz.
	game1.player2.takeCard(); 		//player 2 için 3 tanee kart alıyoruz.

	cout << "Once Player 1(X) oynayacak sonra Player 2(Y) oynayacak." << endl;
	cout << "Daha sonra kullanıcılar önce kendi kartlarından birini seçecek, sonra kartlarını istiyorsa döndürebilecek. \n";
	cout << "Sonra oyun haritasındaki istediği noktayı 1-9 arası bir sayıyla girerek oraya kartı yerleştirecek.\n";

	game1.printBoard(game1.board);	//boardı ekrana basıyoruz.
	while(tur < 9)
	{		
		cout << "PLAYER 1 IN SIRASI\n";
		cout << "Player 1(X) in kartları : " << endl;
		game1.player1.getCard1().printCard(game1.player1.getCard1().card);		//player 1 in 1.kartı
		game1.player1.getCard2().printCard(game1.player1.getCard2().card);		//player 1 in 2.kartı
		game1.player1.getCard3().printCard(game1.player1.getCard3().card);		//player 1 in 3.kartı

		cout << "Oynamak istediğiniz kartı seçiniz.\n";
		cin >> p1card;
		//girilen kart değeri 1 2 3 den farklı olamaz onu ayarlıyoruz
		while(!(p1card < 4 && p1card > 0))
		{
			cout << "Kart için 1 ,2 ,3 arasında değer girmelisiniz.\n";
			//cin.clear();
			//cin.ignore(256,'\n');
			cin >> p1card;
		}

		cout << "Kartı döndürmek istiyor musunuz? \n(sağ için 1, sol için 2, 180 derece için 3, döndürmek istemiyorsanız 0 giriniz.)\n";
		cin >> rotate1;
		//kartı döndürmek için 0 1 2 giriniz.
		while(!(rotate1 < 4 && rotate1 >= 0))
		{
			cout << "Döndürme işlemi için 0, 1, 2 değerlerinden birini girmelisiniz.\n";
			cin.clear();
			cin.ignore(256,'\n');
			cin >> rotate1;
		}
		if(rotate1 != 0)
		{
			//döndürme yapılacaksa hangi kart dönecek ona uygun fonksiyon çağırılıyor.
			if(p1card == 1)
			{
				game1.player1.setCard1(game1.player1.getCard1().rotate(rotate1,game1.player1.getCard1()));
				game1.player1.getCard1().printCard(game1.player1.getCard1().card);
			}
			else if(p1card == 2){
				game1.player1.setCard2(game1.player1.getCard2().rotate(rotate1,game1.player1.getCard2()));
				game1.player1.getCard2().printCard(game1.player1.getCard2().card);
			}
			else if(p1card == 3){
				game1.player1.setCard3(game1.player1.getCard1().rotate(rotate1,game1.player1.getCard3()));
				game1.player1.getCard3().printCard(game1.player1.getCard3().card);
			}
		}

		cout << "Haritada nereye koymak istersiniz ?\n(1-9 arası sayı giriniz.)\n";
		cin >> coordinate;
		//gelen kart haritada istenen koordinata yerleştiriliyor.
		if(p1card == 1)
			game1.addboard(game1.player1.getCard1(),coordinate);
		else if(p1card == 2)
			game1.addboard(game1.player1.getCard2(),coordinate);
		else if(p1card == 3)
			game1.addboard(game1.player1.getCard3(),coordinate);

		//kullanılan kart yerine yeni bir kart koyuluyor.
		if(p1card == 1)
			game1.player1.setCard1(game1.player1.getCard1().creatCard());
		else if(p1card == 2)
			game1.player1.setCard2(game1.player1.getCard2().creatCard());
		else if(p1card == 3)
			game1.player1.setCard3(game1.player1.getCard3().creatCard());

		game1.printBoard(game1.board);
		/******************************* PLAYER 1 OYANANIŞI SONU****************/
		/******************************* PLAYER 2 OYNANIŞI**********************/

		int p2card, rotate2,coordinate2;
		cout << "PLAYER 2 NIN SIRASI:\n";
		cout << "Player 2(Y) in kartları : " << endl;
		//random gelen kartları ekrana bastırıyoruz.
		game1.player2.getCard1().printCard(game1.player2.getCard1().card);		//player 2 in 1.kartı
		game1.player2.getCard2().printCard(game1.player2.getCard2().card);		//player 2 in 2.kartı
		game1.player2.getCard3().printCard(game1.player2.getCard3().card);		//player 2 in 3.kartı

		cout << "Oynamak istediğiniz kartı seçiniz.\n";
		cin >> p2card;
		//oynanacak kartı seçiyoruz.
		while(!(p2card < 4 && p2card > 0))
		{
			cout << "Kart için 1 ,2 ,3 arasında değer girmelisiniz.\n";
			cin >> p2card;
		}

		cout << "Kartı döndürmek istiyor musunuz? \n(sağ için 1, sol için 2, 180 derece için 3, döndürmek istemiyorsanız 0 giriniz.)\n";
		cin >> rotate2;
		//kartı döndürmek için gerkli sorgulamaları yapıyoruz.
		while(!(rotate2 < 4 && rotate2 >= 0))
		{
			cout << "Döndürme işlemi için 0, 1, 2 ,3 değerlerinden birini girmelisiniz.\n";
			cin >> rotate2;
		}

		if(rotate2 != 0)
		{
			//döndürme işlemi için gerekli fonksiyonları çağırıyoruz.
			if(p2card == 1)
			{
				game1.player2.setCard1(game1.player2.getCard1().rotate(rotate1,game1.player2.getCard1()));
				game1.player2.getCard1().printCard(game1.player2.getCard1().card);
			}
			else if(p2card == 2){
				game1.player2.setCard2(game1.player2.getCard2().rotate(rotate1,game1.player2.getCard2()));
				game1.player2.getCard2().printCard(game1.player2.getCard2().card);
			}
			else if(p2card == 3){
				game1.player2.setCard3(game1.player2.getCard1().rotate(rotate1,game1.player2.getCard3()));
				game1.player2.getCard3().printCard(game1.player2.getCard3().card);
			}
		}

		cout << "Haritada nereye koymak istersiniz ?\n(1-9 arası sayı giriniz.)\n";
		cin >> coordinate2;
		//kartın nereye koyulacağını alıp uygun fonksiyonu çağırıyoruz.
		if(p2card == 1)
			game1.addboard(game1.player2.getCard1(),coordinate2);
		else if(p2card == 2)
			game1.addboard(game1.player2.getCard2(),coordinate2);
		else if(p2card == 3)
			game1.addboard(game1.player2.getCard3(),coordinate2);

		//kart oynandıktan sonra yerine yenisini koyuyoruz.
		if(p2card == 1)
			game1.player1.setCard1(game1.player2.getCard1().creatCard());
		else if(p2card == 2)
			game1.player1.setCard2(game1.player2.getCard2().creatCard());
		else if(p2card == 3)
			game1.player1.setCard3(game1.player2.getCard3().creatCard());
		
		game1.printBoard(game1.board);
		tur++;
	}


}

void Game::play()
{
	//oyun içinde x ve y yi hareket ettirmek için gerekli hesaplamaları yapıyoruz.
	//TO BE CONTINUED...
	int *indexX, *indexY;

	indexX = findXY('X');
	printf("x : %d  %d\n",indexX[0], indexX[1] );

	if(indexX[1] == 0 || indexX[1] == 39)
	{
		if(indexX[1] == 0)
		{
			if(board[indexX[0]][2] != ' ') //sol tarafta bulunan x in yanında sayı varsa:
			{

			}
		}
	}

	indexY = findXY('Y');
	
	printf("x : %d  %d\n",indexX[0], indexX[1] );
	printf("y : %d  %d\n",indexY[0], indexY[1] );
}

int *Game::findXY(char a)
{
	//boardda x ve y yi random attıktan sonra oyun içinde hareket ettirmek için x ve y nin koordinatlarını buluyoruz
	static int in[2];
	int index[][24] = { {0,6},{0,9},{0,18},{0,21},{0,30},{0,33},
						 {3,0},{4,0},{9,0},{10,0},{15,0},{16,0},
						 {3,39},{4,39},{9,39},{10,39},{15,39},{16,39},
						 {19,6},{19,9},{19,18},{19,21},{19,30},{19,33} };

	for (int i = 0; i < 24; ++i)
	{
		if(board[index[i][0]][index[i][1]] == a)
		{
			in[0] = index[i][0];
			in[1] = index[i][1];
		}
	}
	return in;
}

void Game::Player::takeCard()
{
	//oyunculara 3er tane kart veriyoruz.
	card1.creatCard();
	
	card2.creatCard();

	card3.creatCard();

}

void Game::Player::Card::toempty(char c[6][12])
{
	//yeni oluşan kartıların içini boşaltıyoruz.
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 12; ++j)
			c[i][j] = ' ';
}

void Game::emptyBoard(char b[20][40])
{
	//boardı boşlatıyoruz öncelikle
	for (int i = 0; i < 20; ++i)
		for (int j = 0; j < 40; ++j)
			b[i][j] = ' ';
}


Game::Player::Card Game::Player::Card::creatCard()
{
	//random olarak kart oluşturuyoruz.
	//önce 4x2 arrayinin içine random sayılar atıyoruz daha sonra onu card class ının içine atıyoruz.
	char inside[4][2] = { {0,0}, {0,0},{0,0}, {0,0} }  ;
	int r=0, t=1;
	int *index;
	toempty(card);						//önce kartın içine space karakterini atıyoruz sonra yanlışlık çıkmasın
	
	//random kart üretimi
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand((time_t)ts.tv_nsec);


	for (int i = 0; i < 12; ++i)
	{
		//kartın ilk ve son satırlarını önce noktalar atıyoruz.
		card[0][i] = '.';
		card[5][i] = '.';
	}

	//kartın içindeki : ları dolduruyoruz.
	card[1][0] = ':';
	card[1][11] = ':';
	card[4][0] = ':';
	card[4][11] = ':';


	//kartın etrafındaki yerlere sayıları yerleştiriyoruz.
	card[0][4] = '1';
	card[0][7] = '2';
	card[2][11] = '3';
	card[3][11] = '4';
	card[5][7] = '5';
	card[5][4] = '6';
	card[3][0] = '7';
	card[2][0] = '8';

	
	//kartın yolunu çizmek için önce 4x2 bir arraya random sayılar alıyoruz.
	//YOL OLUŞTURMAK İÇİN ÖNCE İLK OLUŞTURDUĞUMUZ 4X2 ARRAYİNİ 2X2 OLARAK DEĞİŞTİRDİM.
	//İÇERİSİNE 1 2 3 VE 8 OLMAYACAK ŞEKİLDE RANDOM SAYILARLA DOLDURDUK.
	//YANİ İÇİNE 4 5 6 7 SAYILARI RASGELE DİZİLİYOR. BUNUN NEDENİ YOL OLUŞTURMAK İÇİN AŞAĞIDAKİ BOŞLUKLARALA YOLU TAMAMLIYORUZ.
	for (int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			
			r = rand() %4 +4;
			r = r + '0';
			if(!(isThere(inside,r)))				//daha önceden kullanılmış sayı var mı ona bakılacak.
				inside[i][j] = r;
			else
				j--;
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		//random oluşturduğumuz 4x2 arrayi kartımızın içine atıyoruz.
		card[i+1][4] = inside[i][0];
		card[i+1][7] = inside[i][1];		
	}
	
	index = findindex(card,'2');

	path(card,inside);

	return *this;
}
int Game::Player::Card::path(char c[6][12],char inside[4][2])
{
	int *index;
	//gelen index değerine göre 

	index = findindex(c,inside[0][0]);	
	c[index[0]][index[1]] = c[0][4];

	index = findindex(c,inside[0][0]);
	c[index[0]][index[1]] = c[0][4];

	index = findindex(c,inside[0][1]);
	c[index[0]][index[1]] = c[0][7];

	index = findindex(c,inside[1][0]);
	c[index[0]][index[1]] = c[2][0];

	index = findindex(c,inside[1][1]);
	c[index[0]][index[1]] = c[2][11];

	//printCard(c);

}

int *Game::Player::Card::findindex(char c[6][12],char t)
{
	//kartın içindeki t değişkenini arıyoruz.
	static int index[2]; 				//array geri döndürmek için static olması gerekli.
	for (int i = 0; i < 12; ++i)
	{
		if(c[0][i] == t)
		{
			index[0]=1;					//bulduğu yerin altındaki yer döndürsün ki ona göre kullanalım.
			index[1] = i;
			return index;
		}
		if(c[5][i] == t)
		{
			index[0] = 4;				//bulduğu yerin bir üstünü döndürecek
			index[1] = i;
			return index;
		}
	}

	if(c[2][0] == t)
	{
		index[0] = 2;
		index[1] = 4;
		return index;
	}
	else if(c[2][11] == t)
	{
		index[0] = 2;
		index[1] = 7;
		return index;
	}
	else if(c[3][0] == t)
	{
		index[0] = 3;
		index[1] = 4;
		return index;
	}
	else if(c[3][11] == t)
	{	
		index[0] = 3;
		index[1] = 7;
		return index;
	}
}

void Game::Player::Card::printCard(char card[6][12])
{
	//gelen kartı ekrana bastırıyoruz
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			cout << card[i][j];
		}
		cout << endl;
	}

}

bool Game::Player::Card::isThere(char arr[4][2], char f)
{
	//arrayin içinde daha önceden f değeri varmı ona bakıyoruz.
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2 ; ++j)
		{
			if(arr[i][j] == f)
				return 1;
			//daha önceden varsa true döner
		}
	}
	return 0;
}

void Game::initBoard(int size)
{
	//oyunda ilk olarak boardı initialize ediyoruz.
	//her satırda ne olması gerekiyorsa onları yerleştiriyoruz.
	char cardWidth[12] = {'-','-','-','-','o','-','-','o','-','-','-','-'};
	char cardHeight[6] = {'|','|','o','o','|','|'};
	int n=0,m=0,i=0,t=0;
	emptyBoard(board);

	for ( i = 0; i < 20; ++i)
	{
		n=0;
		for ( int j = 0; j < 40; ++j)
		{	
			if(i == 0 || i == 19)
			{
				//boardda fazladan olan -- teker teker koyuyoruz
				board[i][0] = '-';
				board[i][1] = '-';				
				board[i][38] = '-';
				board[i][39] = '-';

				for(; n < size; n++)
				{
					for( m = 0; m < 12 ;m++,j++)
					{
						//her kart için üsttarafındaki yer kart sayısına göre yazıoyruz
						//printf("m: %d   j: %d\n", m,j);
						if(i==0)
							board[i][j+2] = cardWidth[m];
						else if(i==19)
							board[i][j+1] = cardWidth[m];
					}
				}
			}
			else
			{
				for(t=0; t<size; t++)
					for( m =0; m < 6; m++,i++)
					{
						board[i][0] = cardHeight[m];
						board[i][39] = cardHeight[m];
					}
			}
		}
	}	
}


void Game::printBoard(char b[20][40])
{
	//boardı ekrana basıyoruz.
	for (int i = 0; i < 20; ++i){
		for (int j = 0; j < 40; ++j){
			printf("%c", b[i][j]);
		}
		printf("\n");
	}	
}

void Game::addboard(Game::Player::Card c,int coordinate)
{
	// gelen kartı belirli koordinattaki boardın üstüne yazıyoruz.
	int m=0,n=0;
	int r=0,b=0;
	
	if(coordinate == 1)
	{
		m=1;
		n=2;
	}
	else if(coordinate == 2)
	{
		m=1;
		n=14;
	}
	else if(coordinate == 3)
	{
		m=1;
		n=26;
	}
	else if(coordinate == 4)
	{
		m=7;
		n=2;
	}
	else if(coordinate == 5)
	{
		m=7;
		n=14;
	}
	else if(coordinate == 6)
	{
		m=7;
		n=26;
	}
	else if(coordinate == 7)
	{
		m=13;
		n=2;
	}
	else if(coordinate == 8)
	{
		m=13;
		n=14;
	}
	else if(coordinate == 9)
	{
		m=13;
		n=26;
	}

	c.printCard(c.card);
	
	for (int i = 0,r=m; i < 6; ++i,r++)
	{
		for (int j = 0,b=n; j < 12; ++j,b++)
		{
			board[r][b] = c.card[i][j];
			
		}
		
	}
	//printBoard(board);
}

Game::Player::Card Game::Player::Card::rotate(int way, Card c)
{
	//way 1 ise sağa doğru döner.
	//way 2 ise sola doğru döner.
	//way 3 ise tam ters döner.
	//way 0 ise dönmez.
	char temp[6][12];
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			temp[i][j] = c.card[i][j];
		}
	}
	
	if(way == 1)
	{
		c.card[2][11] = temp[0][4];
		c.card[3][11] = temp[0][7];
		c.card[5][7] = temp[2][11];
		c.card[5][4] = temp[3][11];
		c.card[3][0] = temp[5][7];
		c.card[2][0] = temp[5][4];
		c.card[0][4] = temp[3][0];
		c.card[0][7] = temp[2][0];

		c.card[2][7] = temp[1][4];
		c.card[3][7] = temp[1][7];
		c.card[1][7] = temp[2][4];
		c.card[4][7] = temp[2][7];
		c.card[1][4] = temp[3][4];
		c.card[4][4] = temp[3][7];
		c.card[2][4] = temp[4][4];
		c.card[3][4] = temp[4][7];
		
	}

	else if(way == 2)
	{
		c.card[3][0] = temp[0][4];
		c.card[2][0] = temp[0][7];
		c.card[0][4] = temp[2][11];
		c.card[0][7] = temp[3][11];
		c.card[2][11] = temp[5][7];
		c.card[3][11] = temp[5][4];
		c.card[5][7] = temp[3][0];
		c.card[5][4] = temp[2][0];

		c.card[3][4] = temp[1][4];
		c.card[2][4] = temp[1][7];
		c.card[4][4] = temp[2][4];
		c.card[1][4] = temp[2][7];
		c.card[4][7] = temp[3][4];
		c.card[1][7] = temp[3][7];
		c.card[3][7] = temp[4][4];
		c.card[2][7] = temp[4][7];
		
	}

	else if( way == 3)
	{

		c.card[3][0] = temp[2][11];
		c.card[2][0] = temp[3][11];
		c.card[0][4] = temp[5][7];
		c.card[0][7] = temp[5][4];
		c.card[2][11] = temp[3][0];
		c.card[3][11] = temp[2][0];
		c.card[5][7] = temp[0][4];
		c.card[5][4] = temp[0][7];

		c.card[3][4] = temp[2][7];
		c.card[2][4] = temp[3][7];
		c.card[4][4] = temp[1][7];
		c.card[1][4] = temp[4][7];
		c.card[4][7] = temp[1][4];
		c.card[1][7] = temp[4][4];
		c.card[3][7] = temp[2][4];
		c.card[2][7] = temp[3][4];

	}

	return c;

}

void Game::randomXY()
{
	//board üzerindeki o ların yerine random olarak x ve y atıyoruz
	int index[][24] = { {0,6},{0,9},{0,18},{0,21},{0,30},{0,33},
						 {3,0},{4,0},{9,0},{10,0},{15,0},{16,0},
						 {3,39},{4,39},{9,39},{10,39},{15,39},{16,39},
						 {19,6},{19,9},{19,18},{19,21},{19,30},{19,33} };
	//boarddaki 'o' ların koordinatlarını bir array içinde tutuyoruz.
	int row=0,col=0;
	srand(time(NULL));

	static int r1,r2;
	r1 = rand() % 24;
	r2 = rand() % 24; 
	 
	row = index[r1][0];
	col = index[r1][1];
	board[row][col] = 'X';
	//x ile y aynı yere koyulmaması için tekrar bir random yaptım
	if(r1 == r2)
		r2 = rand() % 24;

	row = index[r2][0];
	col = index[r2][1];
	board[row][col] = 'Y';
}