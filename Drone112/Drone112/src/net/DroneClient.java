
package net;

import java.net.*;
import java.util.Scanner;
import java.io.*;

public class DroneClient extends Thread
{
	private Socket cs;
	private DataInputStream is;
	private DataOutputStream os;
	private Scanner input;

	public DroneClient(Socket cs) throws IOException
	{
		this.cs = cs;
		is = new DataInputStream(cs.getInputStream());
		os = new DataOutputStream(cs.getOutputStream());
	}

	@Override
	public void run()
	{
		input = new Scanner(System.in);
		System.out.println("드론 접속");
		try
		{
			while(true)
			{

				System.out.println("start drone : 6");
				System.out.print("input : ");

				byte cflag = input.nextByte();
				os.write(cflag);
				
				if(cflag != 6 && cflag != 7)
				{
					int setval = input.nextInt();
					os.writeInt(setval);
				}

			}
		}

		catch(Exception e)
		{
			System.out.println("받을 때 오류");
			e.printStackTrace();
		}

		try { cs.close(); } catch(Exception e) {}
	}
}
