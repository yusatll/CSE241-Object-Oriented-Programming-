import javax.swing.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Skylines {

	ArrayList<ArrayList<Integer>> coordinates;      //TÜM KOORDİNATLAR BURDA TUTULCAK. BUNUN GRAFİĞİ ÇİZİLCEK.

	public void showGUI() {
		GUI graph = new GUI();	//yeni bir GUI class objesi oluşturuyoruz
		graph.getPoints(coordinates); 	//kordinatları tuttuğumuz 2d arrayi alıyoruz.

		JFrame window = new JFrame();		//jframe ile grafik çizilecek onun objesi lazım
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);	
		window.setBounds(30, 30, 1200, 700);	//pencerenin boyutları

		window.getContentPane().add(graph);
		window.setVisible(true);

	}


	public void run() {
		File file = new File("data.txt");
		ArrayList<ArrayList<Integer>> list = new ArrayList<ArrayList<Integer>>();	//dosyadan direk buraya okuncak değerler

		ArrayList<Rectangle> rectangles = new ArrayList<Rectangle>();
		//dosyadan okuman kısmı
		Scanner sc = null;	
		try {
			sc = new Scanner(file);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		int i = 0,j=-1;

		while (sc.hasNextLine())
		{
			if (i % 3 == 0)
			{
				list.add(new ArrayList<>());
				j++;
			}
			list.get(j).add(sc.nextInt());

			i++;
		}

		//rectangle class içine atıyoruz değerleri.
		int h =0;
		while(h < i/3 )
		{
			rectangles.add(new Rectangle(list.get(h).get(0),list.get(h).get(1),list.get(h).get(2)));
			h++;
		}
		skyLines(rectangles);
		//printRecangles(rectangles);
		//printArrayList(list);
	}

	//skyline problemini çözen fonksiyon.
	public void skyLines(ArrayList<Rectangle> rec)
	{
		coordinates = new ArrayList<ArrayList<Integer>>();
		int currentPos , currentHeight=0,lastSize,currentEnd=0;
		int beforeHeight=0;
		int firstStart=0,x=0;
		boolean flag = true;
		lastSize = findLastEnd(rec);
		for(currentPos = 0; currentPos < lastSize+1; currentPos++,x++)
		{
			for(int i=0; i < rec.size(); i++)
			{
				if(currentPos == rec.get(i).getStart() )            //dikdörtgenin başlangıç noktasındaysak
				{
					if(flag)                                        //ilk satırdaki elemanları almak için ve if e girmek için gerekli
					{
						firstStart = currentPos;
						flag = false;                               //ilk giriş için istisna bir durum
					}
					if(currentHeight < rec.get(i).getHeight() && currentPos>=firstStart)
					{
						addToArray(currentPos,currentHeight,coordinates);			//aynı olan varmı diye kontrol edicek fonksiyon.
						//System.out.println("x1 : " + currentPos + " y1 : " + currentHeight + " end : " + currentEnd);
						beforeHeight = findThisRecH(currentPos,rec);
						//beforeHeight = currentHeight;
						currentHeight = rec.get(i).getHeight();		//bulunan koordinatları alıyoruz
						currentEnd = rec.get(i).getEnd();
						addToArray(currentPos,currentHeight,coordinates);
						//System.out.println("x2 : " + currentPos + " y2 : " + currentHeight + " end : " + currentEnd);
					}
				}
				if(currentPos == rec.get(i).getEnd() )              //yani sonuna gelinmişse. düşüş olacak
				{                                                   //end şuanki konumdan düşük yükseklikte ise girmeyecek
					if(currentHeight <= rec.get(i).getHeight() || currentPos == lastSize)
					{                                               //şuanki h sonuna geldiğimiz yerden küçükse yapılca
						if(currentPos != lastSize)
						{
							//System.out.println("cur h: " + currentHeight);
							if(beforeHeight > currentHeight)
							{                                       //burda bir düşüş var.
								beforeHeight = findThisRecH(currentPos, rec);
							}
							addToArray(currentPos,currentHeight,coordinates);
							//System.out.println("x3 : " + currentPos + " y3 : " + currentHeight + " end : " + currentEnd);
							beforeHeight = findThisRecH(currentPos, rec);
							addToArray(currentPos,beforeHeight,coordinates);
							//System.out.println("x4 : " + currentPos + " y4 : " + beforeHeight + " end : " + currentEnd);
							currentHeight = beforeHeight;
						}
						else
						{
							int lastH = findThisRecH(currentPos, rec);	//şuanki bulunduğumuz pozisyondaki yüksekliği alıyoruz
							addToArray(currentPos,lastH,coordinates);
							//.out.println("x3 : " + currentPos + " y3 : " + lastH + " end : " + currentEnd);
							addToArray(currentPos,0,coordinates);
							//System.out.println("x4 : " + currentPos + " y4 : " + 0 + " end : " + currentEnd);
						}
					}
				}
			}
		}
		//System.out.println("Coordinates : ");
		printArray(coordinates);
	}

	public void printArray(ArrayList<ArrayList<Integer>> output)
	{	//bulunan kordinatları düzgün bir şekilde bastıyıroyuz
		int a;
		for(List<Integer> num : output)
		{
			a=0;
			System.out.print("(");
			for(Integer ss : num)
			{
				System.out.print(ss);
				if(a==0)
				{
					System.out.print(", ");
					a++;
				}
			}
			System.out.print("), ");
		}
	}

	public void addToArray(int x, int y, ArrayList<ArrayList<Integer>> output)
	{                                     //daha önceden aynı koordinat gelmiş mi diye kontrol ediyoruz

		int found = -1,i;                   //found default olarak  -1 dedik bulunmama durumu için
		for(i = 0; i < output.size(); i++)
		{
			if(output.get(i).get(0) == x && output.get(i).get(1) == y)
				found = i;                 //aynısından varsa ekleme yapılmayacak
		}
		if(found == -1) {
			output.add(new ArrayList<>());
			output.get(output.size()-1).add(x);
			output.get(output.size()-1).add(y);
		}
	}

	public static int findThisRecH(int pos, ArrayList<Rectangle> rec)
	{
		//şuan hangi dikdörtgenin üzerindeyiz onu buluyoruz. 
		// başlangıç ve bitişine göre
		int max=0;
		for(int i = 0; i < rec.size(); i++)
		{
			if(pos >= rec.get(i).getStart() && pos <= rec.get(i).getEnd())
			{
				max = rec.get(i).getHeight();
				if(max < rec.get(i).getHeight())
					max = rec.get(i).getHeight();
			}
		}
		return max;
	}

	public int findLastEnd(ArrayList<Rectangle> r)
	{	
		int last = r.get(0).getEnd();
		for(int i = 0; i < r.size();i++)
		{
			if(last < r.get(i).getEnd() )
				last = r.get(i).getEnd();
		}

		return last;
	}

	public void printArrayList(ArrayList<ArrayList<Integer>> list)
	{	//2d arraylistesini direk bastırmak için yardımcı fonk
		for (ArrayList<Integer> elem : list ) {
			for(Integer num : elem)
				System.out.print(num + " ");
			System.out.println();
		}
	}

	public void printRecangles(ArrayList<Rectangle> rec)
	{	//rectangel classını ekrana bastırmak için gerekli fonk
		System.out.println("Rectangles: ");
		for(int a= 0; a < rec.size() ; a++)
		{
			rec.get(a).printRec();
			System.out.println();
		}
	}
}
