import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JComponent;
import javax.swing.JFrame;

public class GUI extends JComponent {

	ArrayList<ArrayList<Integer>> drawCoordinates; // gelen kordinatları buraya alıyoruz

	public void paint(Graphics g) {
		int size = drawCoordinates.size()-1;
		//eğer inputlar çok fazla gelirse boyutta bir küçükltme yapmamız lazım.
		//ortak çarpanı input sayısına göre azaltıyoruz.
		int count = 40;
		if(size >= 100 && size <= 999)
			count = 20;
		else if(size >= 1000)
			count = 10;
		//döngü ile teker teker line ları çiziyoruz.
		//başlangıç son ile.
		//javada orijin noktası sol üstte olduğu için y ekseni ters oluyordu.
		//bundan dolayı height dan bizim y mizi çıkartmamız gerekti.
		for(int i=0; i<size;i++)
		{
			g.drawLine(drawCoordinates.get(i).get(0)*count,
					super.getHeight() - drawCoordinates.get(i).get(1)*count,
					drawCoordinates.get(i+1).get(0)*count,
					super.getHeight() - drawCoordinates.get(i+1).get(1)*count);
		}
	}

	public void getPoints(ArrayList<ArrayList<Integer>> c)
	{	//korditanları alıyoruzs
		drawCoordinates = c;
	}
}
