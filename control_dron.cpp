#include <TinyGPS.h>

#define ERR_GPS_INVALID 1
#define ERR_GPS_NODATA 2


short angle = 0;					// 현재 이동 방향
double pre_lat, pre_lon, lat, lon;	// 이전/현재 위도,경도

int PIN_IR = 19;
char flag;

int setval;
int PWM[4] = { 10, 11, 12, 13 };	// 드론 
int r[4] = { 150, 150, 150, 150 };	// 드론 명령. 순서대로 throttle, roll, pitch, yaw. 150이 중립

int minval = 100;			// 각 명령별 최소 출력
int maxval = 200;			// 각 명령별 최대 출력
int d_minival = 0;
int d_maxval = 360;


/*
	드론 시동 켜기
*/
void start()
{
	softAnalogWrite(PWM[0], 150);
	softAnalogWrite(PWM[2], 150);
}

/*
	드론 시동 끄기
*/
void terminate()
{
	softAnalogWrite(PWM[0], 100);
	softAnalogWrite(PWM[2], 200);
}

/*
	현재 GPS 좌표값 얻기(위도, 경도)
	유효한 좌표를 얻어야 한다....
	Ex>소수점 아래 3번째 자리수가 5이상 차이날 시
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
	목적지 GPS 좌표값에 대한 이동 방향(각) 얻기
	북쪽(0도) 서쪽(90도) 남쪽(180도) 동쪽(270도)
*/
short getAngle(double P1_latitude, double P1_longitude, double P2_latitude, double P2_longitude)
{
	double Cur_Lat_radian = P1_latitude * (3.141592 / 180);
	double Cur_Lon_radian = P1_longitude * (3.141592 / 180);

	double Dest_Lat_radian = P2_latitude * (3.141592 / 180);
	double Dest_Lon_radian = P2_longitude * (3.141592 / 180);

	double radian_distance = 0;
	radian_distance = acos(sin(Cur_Lat_radian) * sin(Dest_Lat_radian) + cos(Cur_Lat_radian) * cos(Dest_Lat_radian) * cos(Cur_Lon_radian - Dest_Lon_radian));

	double radian_bearing = acos((sin(Dest_Lat_radian) - sin(Cur_Lat_radian) * cos(radian_distance)) / (cos(Cur_Lat_radian) * sin(radian_distance)));    // acos의 인수로 주어지는 x는 360분법의 각도가 아닌 radian(호도)값이다.   

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
	목적지에 도착했는지 확인
*/
bool checkArrival(double latitude, double longitude)
{
	if (flat == latitude && flon == longtitude)
		return true;

	else
		return false;
}

/*
	목적지 GPS 좌표로 이동
*/
void goToDestination(double latitude, double longitude)
{
	short angle_dest;

	angle_dest = getAngle(flat, flon, latitude, longitude);

	angle = getAngle(pre_flat, pre_flon, flat, flon);	
		
	rollDronWithAngle(angle_dest - angle);		// 목적지로 방향 전환

	throttle (170);
}

/****************************************
*	일정 각도만큼 드론 회전(roll)		*
****************************************/
void yaw WithAngle(short angle)
{
	int val;

	
}

/*
	드론을 제자리에서 비행시키기
*/
void hovering ()
{
	for (int i = 0; i < 4; i++)
		control(PWM[i], 150);
}

/*
	드론에 움직임 명령 주기
*/
void control(int PWM[m], int val)
{
	int i;

	if (val < 100)		// 최대, 최소값을 벗어난 경우
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
