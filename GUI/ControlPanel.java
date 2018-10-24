package finalProject;

import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.Console;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;

public class ControlPanel extends JPanel
{
	private JButton forward;
	private JButton backward;
	private JButton left;
	private JButton right;
	private JButton scan;
	private JButton songLED;
	private JButton clear;
	//private JButton left90;
//	private JButton right90;
	private SensorData sensorData;
	private double[][] objDataArr;
	private Roomba roomba;
	private JFrame frame;
	public ArrayList<Obstacle> objArrList;

	public ControlPanel(SensorData s, Roomba r, JFrame f, Drawing drawing, ArrayList<Obstacle> obstacles)
	{
		Dimension size = getPreferredSize();
		size.width = 180;
		setPreferredSize(size);
		setBorder(BorderFactory.createTitledBorder("Main Frame"));

		forward = new JButton("Foward");
		backward = new JButton("Backward");
		left = new JButton("Left");
		right = new JButton("Right");
		scan = new JButton("Scan");
		songLED = new JButton("SongLED");
		clear = new JButton("Clear");
//		right90 = new JButton("Right90");

		sensorData = s;
		roomba = r;
		frame = f;
		objDataArr = new double[10][3];
		objArrList = obstacles;

		setLayout(new GridBagLayout());
		GridBagConstraints gc = new GridBagConstraints();

		gc.weightx = 10;
		gc.weighty = 0.5;

		//to turn left
		gc.anchor = GridBagConstraints.NORTH;
		gc.gridx = 0;
		gc.gridy = 0;
		add(left, gc);
		
		//turn left 90 degrees
//		gc.gridx = 0;
//		gc.gridy = 1;
//		add(left90, gc);

		//to turn right
		gc.gridx = 0;
		gc.gridy = 2;
		add(right, gc);

		// turn right 90 degrees
//		gc.gridx = 0;
//		gc.gridy = 3;
//		add(right90, gc);
		
		// for up button
		gc.gridx = 0;
		gc.gridy = 4;
		add(forward, gc);

		// for down button
		gc.gridx = 0;
		gc.gridy = 5;
		add(backward, gc);

		// for song + LED button
		gc.gridx = 0;
		gc.gridy = 6;
		add(songLED, gc);

		// for scan button
		gc.gridx = 0;
		gc.gridy = 7;
		add(scan, gc);

		gc.gridx = 0;
		gc.gridy = 8;
		add(clear, gc);

		scan.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				String dataHere = "";
				dataHere = sensorData.keyboardCommand('r');
				sensorData.translateObjectData(dataHere);
				objDataArr = sensorData.getObjectDataArr();
				if (objDataArr != null)
				{
					Obstacle obs = null;
					for (int i = 0; i < objDataArr.length; i++)
					{
						obs = new Obstacle(objDataArr[i][0], objDataArr[i][1], objDataArr[i][2], frame, r);
						obs.findObjType();
						System.out.println("Object type: " + obs.objectType);
						obs.findObjCoords();
						System.out.println("x is: " + obs.x + " y is: " + obs.y);
						objArrList.add(obs);
						drawing.drawing();
					}
				}
			}
		});

		// up button action
		forward.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				String data = "";
				data = sensorData.keyboardCommand('w');
				sensorData.translateRobotData(data);
				System.out.println(sensorData.getDataString());
				// roomba.updateRoomba(sensorData.getCurDist(), sensorData.getCurAngle(), true);
				// drawing.drawing();
				sensorData.clearCurDist();
			}
		});

		// down button action
		backward.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				String data = "";
				data = sensorData.keyboardCommand('s');
				sensorData.translateRobotData(data);
				System.out.println(sensorData.getDataString());
				// roomba.updateRoomba(sensorData.getCurDist(), sensorData.getCurAngle(),
				// false);
				// drawing.drawing();
				sensorData.clearCurDist();
			}
		});

		// left button action
		left.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				String data = "";
				data = sensorData.keyboardCommand('a');
				sensorData.translateRobotData(data);
				System.out.println(sensorData.getDataString() + "CurAngle: " + sensorData.getCurAngle());
			}
		});


		right.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				String data = "";
				data = sensorData.keyboardCommand('d');
				sensorData.translateRobotData(data);
				System.out.println(sensorData.getDataString() + "CurAngle: " + sensorData.getCurAngle());
			}
		});

		songLED.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				String data = "";
				data = sensorData.keyboardCommand('f');
			}
		});

		clear.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				for (int i = 0; i < objArrList.size(); i++)
				{
					objArrList.remove(i);

				}
				drawing.drawing();
			}
		});
	}
}