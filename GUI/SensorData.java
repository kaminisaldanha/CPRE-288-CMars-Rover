package finalProject;

import java.awt.GridBagConstraints;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.swing.event.EventListenerList;
import javax.swing.JButton;
import javax.swing.JPanel;

import java.util.ArrayList;
import java.util.Scanner;

public class SensorData extends JPanel
{

	private EventListenerList listenerList = new EventListenerList();
	private JButton up, down, left, right, scan, LED, song;
	private int bLeft, bRight, cLeft, cRight, cFrontLeft, cFrontRight, boundaryLeft, boundaryRight, boundaryFLeft,
			boundaryFRight;
	private DataOutputStream output;
	private DataInputStream input;
	private GridBagConstraints gc;
	public String dataString;
	private int curDist;
	private int curAngle;
	private double[][] objectDataArr;
	public Socket socket;

	public SensorData() throws UnknownHostException, IOException
	{
		/*
		socket = new Socket("192.168.1.1", 288);
		System.out.println("CONNECTED\n");
		output = new DataOutputStream(socket.getOutputStream());
		input = new DataInputStream(socket.getInputStream());*/

		dataString = "";
		objectDataArr = null;
		curDist = 0;
		curAngle = 0;

	}

	public String keyboardCommand(char letter)
	{
		String temp = "";
		char read = 'a';
		try
		{
			output.write(letter);
		} catch (IOException e1)
		{
			e1.printStackTrace();
		}
		while (read != '}')
		{
			try
			{
				read = (char) input.read();
			} catch (IOException e1)
			{
				e1.printStackTrace();
			}
			temp = temp + read;
		}
		temp = temp.replace(temp.substring(temp.length() - 1), "");
		dataString = temp;
		return temp;
	}

	public void translateObjectData(String data)
	{
		double[][] arrData;
		Scanner scanner = new Scanner(data);
		int objNum, location;
		double dist, size;
		String objLine;
		objNum = scanner.nextInt();
		arrData = new double[objNum][3];
		for (int i = 0; i < objNum; i++)
		{
			dist = scanner.nextFloat();
			size = scanner.nextFloat();
			location = scanner.nextInt();
			arrData[i][0] = dist;
			arrData[i][1] = size;
			arrData[i][2] = location;

		}
		scanner.close();
		objectDataArr = arrData;

	}

	public void translateRobotData(String info)
	{
		Scanner scanner = new Scanner(info);
		String dataLine = "";
		int data;
		while (scanner.hasNext())
		{
			dataLine = scanner.nextLine();
			Scanner scanner2 = new Scanner(dataLine);
			scanner2.useDelimiter("\\D");
			char[] negCheck = new char[dataLine.length()];
			boolean sign = false;
			negCheck = dataLine.toCharArray();
			ArrayList<Character> negCheckList = new ArrayList<Character>();

			for (int i = 0; i < negCheck.length; i++)
			{
				negCheckList.add(negCheck[i]);
			}

			for (int i = 0; i < dataLine.length(); i++)
			{
				if (negCheck[i] == '-')
				{
					sign = true;
					negCheckList.remove(i);
				}
			}
			dataLine = "";
			for (int i = 0; i < negCheckList.size(); i++)
			{
				dataLine = dataLine + negCheckList.get(i);
			}
			scanner2.close();
			scanner2 = new Scanner(dataLine);

			if (dataLine.contains("Dist Moved "))
			{
				scanner2.next();
				scanner2.next();
				data = scanner2.nextInt();
				curDist = data;
				if (sign == true)
				{
					curDist *= -1;
					sign = false;
				}

			}

			else if (dataLine.contains("Angle Moved "))
			{
				scanner2.next();
				scanner2.next();
				data = scanner2.nextInt();
				if (sign == false)
				{
					data = data * -1;
				}

				if (sign == true)
				{
					sign = false;
				}
				curAngle += data *2;
			}
/*
			else
			{
				Scanner scanner3 = new Scanner(dataLine);

				bLeft = scanner3.nextInt();
				bRight = scanner3.nextInt();
				cLeft = scanner3.nextInt();
				cRight = scanner3.nextInt();
				cFrontLeft = scanner3.nextInt();
				cFrontRight = scanner3.nextInt();
				boundaryLeft = scanner3.nextInt();
				boundaryRight = scanner3.nextInt();
				boundaryFLeft = scanner3.nextInt();
				boundaryFRight = scanner3.nextInt();

			}
*/
		}
		

		scanner.close();
	}
	/*
	public int getbLeft() {
		return bLeft;
	}
	
	public int getbRight() {
		return bRight;
	}
	
	public int getcLeft() {
		return cLeft;
	}
	
	public int getcRight() {
		return cRight;
	}
	
	public int getcFrontLeft() {
		return cFrontLeft;
	}
	
	public int getcFrontRight() {
		return cFrontRight;
	}
	
	public int getboundaryLeft() {
		return boundaryLeft;
	}
	
	public int getboundaryRight() {
		return boundaryRight;
	}
	
	public int getboundaryFLeft() {
		return boundaryFLeft;
	}
	
	public int getboundaryFRight() {
		return boundaryFRight;
	}
*/
	public String getDataString()
	{
		return dataString;
	}

	public double[][] getObjectDataArr()
	{
		return objectDataArr;
	}

	public int getCurDist()
	{
		return curDist;
	}

	public int getCurAngle()
	{
		return curAngle;
	}

	public void clearCurDist()
	{
		curDist = 0;
	}

	public void clearCurAngle()
	{
		curAngle = 0;
	}

}
