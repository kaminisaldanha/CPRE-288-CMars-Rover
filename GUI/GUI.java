package finalProject;

import javax.swing.JButton;

// A Java program for a Client

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.io.*;
import java.net.UnknownHostException;
import java.util.ArrayList;

public class GUI extends JFrame
{
	public GUI()
	{

		// Set JFrame size to :
		// Width : 1440 pixels
		// Height : 900 pixels
		setSize(1440, 900);

		// Set JFrame default close operation
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// Make JFrame visible
		setVisible(true);
	}	

	public void paint(Graphics g)
	{
		// Override paint method in superclass
		super.paint(g);

		// Get current JFrame width
		int frameWidth = getSize().width;

		// Get current JFrame height
		int frameHeight = getSize().height;

		int temp = 0;

		// Draw vertical grid line with spacing between each line equal to 10 pixels
		while (temp < frameWidth)
		{
			temp = temp + 10;
			g.drawLine(temp, 0, temp, frameHeight);
		}

		temp = 0;

		// Draw horizontal grid line with spacing between each line equal to 10 pixels
		while (temp < frameHeight)
		{
			temp = temp + 10;
			g.drawLine(0, temp, frameWidth, temp);
		}
	}

	public static void main(String[] args) throws UnknownHostException, IOException
	{

		ArrayList<Obstacle>objArrList = new ArrayList<Obstacle>();
		
		JFrame frame = new JFrame();
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(1440, 720);
		Container c = new Container();
		c = frame.getContentPane();
		Roomba r = new Roomba();
		SensorData data = new SensorData();
		
	
		Drawing drawing = new Drawing(objArrList, r);
		ControlPanel controlPanel = new ControlPanel(data, r, frame, drawing, objArrList);
		c.add(controlPanel, BorderLayout.WEST);
		frame.add(drawing);
		drawing.drawing();
		
	
	}

}
