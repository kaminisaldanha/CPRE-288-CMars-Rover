package finalProject;

import java.awt.Color;
import java.math.*;
import java.awt.Graphics;
import javax.swing.JPanel;

public class Roomba extends JPanel {
	private int x, y;
	private String objectType;
	private int linearWidth;

	public Roomba() {
		this.x = 606;
		this.y = 336;
	}
	

	public void updateRoomba(int dist, int angle, boolean direction) {
		dist = dist / 10;
		double angleRad = 0;
		angleRad = (angle * (Math.PI / 180));
		if (direction == true) {
			y -= (int) Math.abs((Math.cos(angleRad * 1.0) * dist*7));
			x += (int) (Math.sin(angleRad * 1.0) * dist*5);
		}
		else {
			y += (int) Math.abs((Math.cos(angleRad * 1.0) * dist*2.5));
			x += (int) (Math.sin(angleRad * 1.0) * dist*2.5);
		}
	}
	
	public int getXCoor() {
		return x;
	}
	
	public int getYCoor() {
		return y;
	}
	
	
	
	
}
