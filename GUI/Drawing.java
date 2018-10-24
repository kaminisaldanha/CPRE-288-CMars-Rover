package finalProject;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JPanel;

public class Drawing extends JPanel {
	ArrayList<Obstacle> obstacles;
	Roomba roomba;
	int buffer;
	public Drawing(ArrayList<Obstacle> obstacles, Roomba r){
		this.obstacles = obstacles;
		buffer = 24;
		roomba = r;
	}
	public void drawing(){
		repaint();
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		double linearWidth = 0;
		
		g.setColor(Color.GREEN);
		g.drawOval(roomba.getXCoor(), roomba.getYCoor(), 48, 48);
		g.fillOval(roomba.getXCoor(), roomba.getYCoor(), 48, 48);
		
		for (int i = 0; i < obstacles.size(); i++) {
			linearWidth = obstacles.get(i).linearWidth;
			linearWidth = (int)(linearWidth * 1.5);
			if (obstacles.get(i).objectType.equals("small"))
			{
				g.setColor(Color.RED);
				g.drawOval((int)obstacles.get(i).x, (int)obstacles.get(i).y, (int)linearWidth, (int)linearWidth);
				g.fillOval((int)obstacles.get(i).x,(int)obstacles.get(i).y, (int)linearWidth, (int)linearWidth);
			}

			if (obstacles.get(i).objectType.equals("big"))
			{
				g.setColor(Color.BLUE);
				g.drawOval((int)obstacles.get(i).x,(int) obstacles.get(i).y,(int)linearWidth,(int)linearWidth);
				g.fillOval((int)obstacles.get(i).x, (int)obstacles.get(i).y, (int)linearWidth,(int) linearWidth);
			}
			
			if(obstacles.get(i).objectType.equals("short"))
			{
				//width = ;
				g.setColor(Color.MAGENTA);
				g.drawOval((int)obstacles.get(i).x, (int)obstacles.get(i).y, (int)linearWidth, (int)linearWidth);
				g.fillOval((int)obstacles.get(i).x, (int)obstacles.get(i).y, (int)linearWidth, (int)linearWidth);
			}
		}
	}
	
	
}
