#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

double findTotal(char *element);
void removeSpaces(char *line);
int findFirstOccurance(char* s, char el, int start);
bool isThisPrice(char *str);

#define SIZE 100

int main()
{
	char * object = (char*)malloc(sizeof(char)*100);
	double price=0.0;

	printf("Define th object : \n");
	cin >> object;		
	//input olarak objenin ismini alıyoruz.

	//removeSpaces(object);

	printf("obje : %s\n",object);
	//esas fonksiyon burada çağırılıyor.
	price = findTotal(object);

	printf(" price %lf\n", price);


	return 0;
}
//programın ana fonksiyonu. 
//gelen elementin burada parçalayıp
//burada hesaplamalarını yapıyoruz.
double findTotal(char* element)
{
	int start = 0;
	double temp = 0.0, price = 0.0;
	int index = 0;
	int begin = 0;
	int lastPosition = 0;
	char * substr;
	char * obj;
	char ignore;
	int number=0;

	cout<<"what is " << element<< " ? "<< endl;
	cin >> element;
	//girilen objenin elementlerini alıyoruz.

	//removeSpaces(element);

	//recursive in durdurma yeri.
	//girilen değer sayı veya double ise durur.
	if (isThisPrice(element))
		return atof(element);


	while(lastPosition <= strlen(element)) {

		substr = (char*)malloc(sizeof(char)*100);
		obj = (char *)malloc(sizeof(char)*100);

		// + karakterini belirli bir indexten sonra arıyoruz
		index = findFirstOccurance(element,'+',start);
		
		strncpy(substr, element+begin, index - begin);

		lastPosition += strlen(substr) + 1;

		sscanf(substr,"%d%c%s",&number,&ignore,obj);

		temp = findTotal(obj) * number;

		price += temp;

		begin = index+1;
		start = index+1;
	}

	return price;
}

//gelen stringlerin boşluklarını kaldırır.
void removeSpaces(char *line)
{
	int i=0,j=0;
	//girilen inputta içindelki whitespace karakterlerini ignore ediyoruz.
	while(line[i])
	{
		if(line[i] != ' ')
			line[j++] = line[i];
		i++;	
	}
	line[j]= '\0';
}

//gelen stringin içindeki verilen char ı belirli bir indexten başlayıp arıyor.
int findFirstOccurance(char* s, char el, int start){

	int i;

	for(i = start; i < strlen(s); ++i) {
		if (*(s+i) == el)
			return i;
	}

}

//stringin fiyat mı element mi olduğunu anlamak için gerekli fonksiyon.
bool isThisPrice(char *str)
{
	for(int i = 0 ; i < strlen(str); i++ ){

		if(str[i] == '+' || str[i] == '*')
			return false;
	}

	return true;
}
