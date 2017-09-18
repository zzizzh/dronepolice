#include <convert.h>
#include <Drone112.h>
#include <Command.h>
#include <CommandList.h>
#include <pthread.h>


#define MOVE        0
#define HALT        1
#define GO_HOME     2
#define LAND        3
#define ROTATE      4

#define PIC_HOME    0
#define LIST_STREAM 1
#define APPEND_LIST 2
#define RESET_LIST  3

#define IR_PIN 19

pthread_t p_thread[2];

Drone112 drone = Drone112();

CommandList command_list = CommandList();
// 가지고있는 모든 명령 리스트
Command cur_commnd;           // 현재 수행하고 있는 명령
byte mflag, cflag;
int p_length;                 // 명령 리스트 길이
byte temp_value;
float value1, value2;         // 명령에서 읽을 값

char ssid[] = "JM";           //  연결할 와이파이 이름
char pass[] = "BOMEEJAEMIN";  // 네트워크 보안키
int status = WL_IDLE_STATUS;
IPAddress server(211, 108, 204, 217);  // 연결할 서버 IP주소
WiFiClient client;

bool drone_power = true;      //  드론 on/off
bool sensor_valid = false;    //  센서 유효여부
bool network_valid = false;   //  네트워크 연결여부

void setup() {

	pinMode(IR_PIN, INPUT);         // IR 센서

	while (status != WL_CONNECTED)   // 와이파이 연결
	{
		status = WiFi.begin(ssid, pass);
		delay(1000);
	}
	while (!client.connected())        // 서버에 연결
	{
		if (client.connect(server, 20000))
			network_valid = true;
		delay(1000);

		// 서버로 명령 리스트 요청
		writeInt(1);
		write(0);
	}

	if (command.isEmpty())
	{
		while (!client.available());       // 와이파이 버퍼에 데이터가 있는 동안 계속 command를 읽음
		recvCommand();
	}

	drone.start();

	drone_power = true;

	drone.throttle(160);

	pthread_create(&p_thread[0], NULL, networkSection, NULL);        // 네트워크 & 센서 부분 
	pthread_create(&p_thread[1], NULL, droneSection, drone);        // 드론 구동 부분
}


void recvCommandList()
{
	int read_size = 0;
	if (client.available())
	{
		p_length = readInt();
		mflag = client.read();
		read_size++;

		switch (mflag)
		{
		case PIC_HOME:
			break;
		case LIST_STREAM:
			break;
		case APPEND:
			for (int i = read_size; i <= p_length;)
			{
				c_flag = client.read();
				read_size++;

				switch (cflag)
				{
				case MOVE:
					value1 = readFloat();
					value2 = readFloat();
					command_list.add(Command(cflag, value1, value2));
					read_size += 8;
					break;
				case HALT:
					value1 = readFloat();
					command_list.add(Command(cflag, value1));
					read_size += 4;
					break;
				case GO_HOME:
					command_list.add(Command(cflag));
					break;
				case LAND:
					command_list.add(Command(cflag));
					break;
				case ROTATE:
					value1 = readFloat();
					command_list.add(Command(cflag, value1));
					read_size += 4;
					break;
				}
			}
			break;
		case RESET:
			command_list = CommandList();
			//  서버로 reset 햇다는것을 알려줘야함
			break;
		}
	}
}

void *networkSection()
{

	while (true)
	{


		if (digitalRead(IR_PIN))
		{
			// SIGNAL 사용하면 될듯!
		}
		// getImage()

		if (!client.connected()) // 서버와 연결이 끊겼을 시
		{
			//
		}

		if (drone.getGPSPoint())
	}
}

void *droneSection(Drone112 drone)
{
	while (drone_power)
	{
		while (drone.getGPSPoint() != 0)
		{
			drone.hovering();
		}
		cur_command = command_list.getCommand();

		switch (cur_command.getFlag()
		{
		case MOVE:
			if (drone.checkArrival())
				command.nextCommand();
			else
				drone.goToDestination(cur_command.getValue1(), cur_command.getValue2());
			break;
		}
	}
}
