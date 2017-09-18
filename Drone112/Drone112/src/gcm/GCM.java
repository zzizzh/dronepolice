
package gcm;

import com.google.android.gcm.server.*;
import java.util.List;

public class GCM
{
    private static final String APIKEY = "AIzaSyDvi9Psq0lVXP8hiXpzQV7Q1g50zlzwSU8";
    private static final int RETRIES = 5;
    
    public static void send(List<String> list, String value)
    {
        Sender sender = new Sender(APIKEY);
        Message message = new Message.Builder().addData("key", value).build();
        MulticastResult multiResult;

        try
        {
            multiResult = sender.send(message, list, RETRIES);
            
            if (multiResult != null)
            {
                List<Result> resultList = multiResult.getResults();
                
                for (Result result : resultList)
                {
                    System.out.println(result.getMessageId());
                }
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
    public static void send(String regid, String value)
    {
        Sender sender = new Sender(APIKEY);
        Message message = new Message.Builder().addData("msg", value).build();
        Result result;

        try
        {
            result = sender.send(message, regid, RETRIES);
            
            if(result != null) System.out.println(result.getMessageId());
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}
