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
// �������ִ� ��� ��� ����Ʈ
Command cur_commnd;           // ���� �����ϰ� �ִ� ���
byte mflag, cflag;
int p_length;                 // ��� ����Ʈ ����
byte temp_value;
float value1, value2;         // ��ɿ��� ���� ��

char ssid[] = "JM";           //  ������ �������� �̸�
char pass[] = "BOMEEJAEMIN";  // ��Ʈ��ũ ����Ű
int status = WL_IDLE_STATUS;
IPAddress server(211, 108, 204, 217);  // ������ ���� IP�ּ�
WiFiClient client;

bool drone_power = true;      //  ��� on/off
bool sensor_valid = false;    //  ���� ��ȿ����
bool network_valid = false;   //  ��Ʈ��ũ ���Ῡ��

void setup() {

	pinMode(IR_PIN, INPUT);         // IR ����

	while (status != WL_CONNECTED)   // �������� ����
	{
		status = WiFi.begin(ssid, pass);
		delay(1000);
	}
	while (!client.connected())        // ������ ����
	{
		if (client.connect(server, 20000))
			network_valid = true;
		delay(1000);

		// ������ ��� ����Ʈ ��û
		writeInt(1);
		write(0);
	}

	if (command.isEmpty())
	{
		while (!client.available());       // �������� ���ۿ� �����Ͱ� �ִ� ���� ��� command�� ����
		recvCommand();
	}

	drone.start();

	drone_power = true;

	drone.throttle(160);

	pthread_create(&p_thread[0], NULL, networkSection, NULL);        // ��Ʈ��ũ & ���� �κ� 
	pthread_create(&p_thread[1], NULL, droneSection, drone);        // ��� ���� �κ�
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
			//  ������ reset �޴ٴ°��� �˷������
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
			// SIGNAL ����ϸ� �ɵ�!
		}
		// getImage()

		if (!client.connected()) // ������ ������ ������ ��
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
