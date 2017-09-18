package net;

import java.net.*;
import java.io.*;

public class DroneListener extends Thread
{
    private static final int PORT = 20000;
    private static ServerSocket ss;
    private static boolean on;
    
    public DroneListener() throws IOException
    { ss = new ServerSocket(PORT); }
    
    @Override
    public void run()
    {
        on = true;
        System.out.println("드론 서버 시작");
        
        while(on)
        {
			try { new DroneClient(ss.accept()).start(); }
            catch(SocketException e) {}
            catch(IOException e)
            { System.out.println("클라이언트 소켓 생성 오류"); }
        }
    }
    
    public void setOff() { on = false; }
}
