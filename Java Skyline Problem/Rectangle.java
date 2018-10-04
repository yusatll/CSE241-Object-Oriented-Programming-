public class Rectangle
{	//verilen inputlara göre rectangele class objesini oluşturuyoruz.
	private int width;
	private int height;
	private int start;
	private int end;

	public int getWidth() { return width; }
	public int getHeight() { return height; }
	public int getStart() { return start; }
	public int getEnd() { return end; }

	public void setHeight(int height) { this.height = height; }
	public void setStart(int start) { this.start = start; }
	public void setWidth(int width) { this.width = width; }

	public Rectangle(int w, int h ,int s)
	{
		this.width = w;
		this.height = h;
		this.start = s;
		this.end = start + width;
	}
	public Rectangle() {
		this.end = start + width;
	}
	public Rectangle(Rectangle r)
	{
		this.end = start + width;
	}
	public void printRec()
	{
		System.out.print(width +" " +height +" " + start +" " + end);
	}
}
