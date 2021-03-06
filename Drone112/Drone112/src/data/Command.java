package data;

import java.io.Serializable;

public class Command implements Serializable
{
	/*********** Command Flag Specification ************/
	// 0 : Move		value1, value2 : location			/
	// 1 : Halt		value1 : halt duration (second)		/
	// 2 : Go Home										/
	// 3 : Land											/
	// 4 : Rotate	value1 : degree (North)				/
	/***************************************************/
	
	private long	id;
	private int		flag;
	private float	value1;
	private float	value2;
	
	public Command(int flag, float value1, float value2)
	{
		this();
		setFlag(flag);
		setValue1(value1);
		setValue2(value2);
	}

	public Command() { setId(); }
	
	private void 	setId() 				{ id = java.lang.System.currentTimeMillis(); }
	public void 	setFlag(int flag) 		{ this.flag = flag; }
	public void 	setValue1(float value1)	{ this.value1 = value1; }
	public void		setValue2(float value2)	{ this.value2 = value2; }
	
	public long		getId()		{ return id; }
	public int		getFlag()	{ return flag; }
	public float	getValue1()	{ return value1; }
	public float	getValue2()	{ return value2; }
}
