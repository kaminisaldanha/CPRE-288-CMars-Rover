package finalProject;

import java.util.ArrayList;
import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Obstacle extends JPanel
{
	ArrayList<Double> coordinates;
	int bumpLeft, bumpRight;
	double  angle, distance, linearWidth;
	int x = 0, y = 0;
	String objectType = "";
	private JFrame frame;
	private Roomba roomba;

	public Obstacle()
	{
	}

	public Obstacle(double dist, double linWidth, double a, JFrame f, Roomba r)
	{
		
		distance = dist;
		angle = a;
		linearWidth = linWidth;
		frame = f;
		roomba = r;
		
		System.out.println("Angle of object: " +a);
	
	}

	public void findObjCoords()
	{
		double angleRad = 0;
		angleRad = ((180-angle) * (Math.PI / 180));
		x = roomba.getXCoor() - (int) ((Math.cos(angleRad * 1.0) * distance)*1.5)+24; // get xcoord
		y = roomba.getYCoor() - (int) ((Math.sin(angleRad * 1.0) * distance)*1.5) - 24; // get ycoord
		repaint();
	}
	
	public boolean objectCheck(int distanceMoved)
	{
		/*
		int IR[] = new int[IRDistAngle.size()];
		boolean xmatch = false;
		boolean ymatch = false;
		int xindex1 = 0, xindex2 = 0;
		int yindex1 = 0, yindex2 = 0;

		// looks for matching x coordinates
		for (int i = 0; i < IR.length - 2; i += 2)
		{
			for (int j = 2; j < IR.length; j += 2)
			{
				if (IR[i] == IR[j] && i != j)
				{
					xmatch = true;
					xindex1 = i; // saves first xindex found
					xindex2 = j; // saves second xindex found
				}
			}
		}

		// looks for matching y coordinates
		for (int i = 1; i < IR.length; i += 2)
		{
			for (int j = 3; j < IR.length; j += 2)
			{
				if (IR[i] == IR[j] && i != j)
				{
					// checks to see if the yindex is one after the xindex of the same objects found
					// above
					if ((yindex1 == xindex1 + 1) && (yindex2 == xindex2 + 1))
					{
						ymatch = true;
					}

				}
			}
		}

		if (xmatch == true && ymatch == true)
		{
			return true;
		}
*/
		return false;
	}

	public void findObjType() {
		if (linearWidth > 8 && linearWidth < 15) {
			objectType = "big";
		}
		if (linearWidth < 8 && linearWidth > 3) {
			objectType = "small";
		}
		if (bumpLeft == 1 || bumpRight == 1) {
			objectType = "short";
		}
	}

}
