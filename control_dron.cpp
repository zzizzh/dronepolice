#include <TinyGPS.h>

#define ERR_GPS_INVALID 1
#define ERR_GPS_NODATA 2


short angle = 0;					// ���� �̵� ����
double pre_lat, pre_lon, lat, lon;	// ����/���� ����,�浵

int PIN_IR = 19;
char flag;

int setval;
int PWM[4] = { 10, 11, 12, 13 };	// ��� 
int r[4] = { 150, 150, 150, 150 };	// ��� ���. ������� throttle, roll, pitch, yaw. 150�� �߸�

int minval = 100;			// �� ��ɺ� �ּ� ���
int maxval = 200;			// �� ��ɺ� �ִ� ���
int d_minival = 0;
int d_maxval = 360;


/*
	��� �õ� �ѱ�
*/
void start()
{
	softAnalogWrite(PWM[0], 150);
	softAnalogWrite(PWM[2], 150);
}

/*
	��� �õ� ����
*/
void terminate()
{
	softAnalogWrite(PWM[0], 100);
	softAnalogWrite(PWM[2], 200);
}

/*
	���� GPS ��ǥ�� ���(����, �浵)
	��ȿ�� ��ǥ�� ���� �Ѵ�....
	Ex>�Ҽ��� �Ʒ� 3��° �ڸ����� 5�̻� ���̳� ��
*/
int getGPSPoint() 
{
	bool newData = false;
	bool valid = false;
	unsigned long chars;
	unsigned short sentences, failed;

	pre_flat = flat;	
	pre_flon = flon;


	char c = GPSSerial.read();

	if (gps.encode(c))
		newData = true;


	if (newData)
		gps.f_get_position(&flat, &flon, &age);

	gps.stats(&chars, &sentences, &failed);

	if (failed == 1)
	{
		flat = pre_flat;
		flon = pre_flon;
		return ERR_GPS_INVALID;
	}
	
	if (chars == 0)
	{
		flat = pre_flat;
		flon = pre_flon;
		return ERR_GPS_NODATA;
	}

	if (newData)
		return 0;
}

/*
	������ GPS ��ǥ���� ���� �̵� ����(��) ���
	����(0��) ����(90��) ����(180��) ����(270��)
*/
short getAngle(double P1_latitude, double P1_longitude, double P2_latitude, double P2_longitude)
{
	double Cur_Lat_radian = P1_latitude * (3.141592 / 180);
	double Cur_Lon_radian = P1_longitude * (3.141592 / 180);

	double Dest_Lat_radian = P2_latitude * (3.141592 / 180);
	double Dest_Lon_radian = P2_longitude * (3.141592 / 180);

	double radian_distance = 0;
	radian_distance = acos(sin(Cur_Lat_radian) * sin(Dest_Lat_radian) + cos(Cur_Lat_radian) * cos(Dest_Lat_radian) * cos(Cur_Lon_radian - Dest_Lon_radian));

	double radian_bearing = acos((sin(Dest_Lat_radian) - sin(Cur_Lat_radian) * cos(radian_distance)) / (cos(Cur_Lat_radian) * sin(radian_distance)));    // acos�� �μ��� �־����� x�� 360�й��� ������ �ƴ� radian(ȣ��)���̴�.   

	double true_bearing = 0;
	if (sin(Dest_Lon_radian - Cur_Lon_radian) < 0)
	{
		true_bearing = radian_bearing * (180 / 3.141592);
		true_bearing = 360 - true_bearing;
	}
	else
	{
		true_bearing = radian_bearing * (180 / 3.141592);
	}

	return (short)true_bearing;
}

/*
	�������� �����ߴ��� Ȯ��
*/
bool checkArrival(double latitude, double longitude)
{
	if (flat == latitude && flon == longtitude)
		return true;

	else
		return false;
}

/*
	������ GPS ��ǥ�� �̵�
*/
void goToDestination(double latitude, double longitude)
{
	short angle_dest;

	angle_dest = getAngle(flat, flon, latitude, longitude);

	angle = getAngle(pre_flat, pre_flon, flat, flon);	
		
	rollDronWithAngle(angle_dest - angle);		// �������� ���� ��ȯ

	throttle (170);
}

/****************************************
*	���� ������ŭ ��� ȸ��(roll)		*
****************************************/
void yaw WithAngle(short angle)
{
	int val;

	
}

/*
	����� ���ڸ����� �����Ű��
*/
void hovering ()
{
	for (int i = 0; i < 4; i++)
		control(PWM[i], 150);
}

/*
	��п� ������ ��� �ֱ�
*/
void control(int PWM[m], int val)
{
	int i;

	if (val < 100)		// �ִ�, �ּҰ��� ��� ���
		val = 100;

	if (val > 200)
		val = 200;

	r[m] = val;
	softAnalogWrite(PWM[m], val);

	return 0;
}
 
void throttle (int val)
{
	control (PWM[0], val);
	r[0] = val;
}

void roll (int val)
{
	control (PWM[1], val);
	r[1] = val;
}

void pitch (int val)
{
	control (PWM[2], val);
	r[2] = val;
}

int yaw (int val)
{
	control (PWM[3], val);
	r[3] = val;
}
