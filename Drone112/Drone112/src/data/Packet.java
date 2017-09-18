package data;

import java.io.Serializable;

public class Packet implements Serializable
{
	/************************** Packet Flag Specification **************************/
	// 0 : Query for a picture and home location									/
	// 1 : Query for command list and stream										/
	// 2 : Query for command append			data : Command ArrayList				/
	// 3 : Query for command reset			data : Command ArrayList				/
	// 4 : Query for video stream													/
	// 5 : Query for device registration	data : String[2] = {server key, RegId} 	/
	/*******************************************************************************/
	
	private int		flag;
	private Object	data;
	
	public Packet(int flag, Object data)
	{
		setFlag(flag);
		setData(data);
	}
	
	public Packet() {}
	
	public void		setFlag(int flag)		{ this.flag = flag; }
	public void		setData(Object data) 	{ this.data = data; }
	
	public int		getFlag()	{ return flag; }
	public Object	getData()	{ return data; }
}
