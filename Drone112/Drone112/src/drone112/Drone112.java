
package drone112;

import java.awt.EventQueue;

public class Drone112
{

    public static void main(String[] args)
    {

		//EventQueue.invokeLater(() -> new MainFrame().setVisible(true));
    	
        try
        {
            new net.AndroidListener().start(); 
            new net.DroneListener().start(); 
        } catch(Exception e) { e.printStackTrace(); }
        //gcm.GCM.send("APA91bHefOcjHmXHn7PYjw-56OZo9sLJCIaEMwXth5tNXgzbdZu1rN-cswLRhYM3r8VThjS-4hpLDHxdhRG9qvVNfo7w81i6a7lOcuEElb8SJoFCLPaL8EaUBuLI2uzASk0013jpbC1p", "Hello");
    }
    
}
