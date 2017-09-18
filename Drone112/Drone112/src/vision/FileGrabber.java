
package vision;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileGrabber
{
    private byte[] buffer;
    
    private static FileGrabber self = null;
    public static FileGrabber getInstance()
    {
        if(self == null) self = new FileGrabber();
        return self;
    }
    
    private FileGrabber() {}
    
    public void grab()
    {
        Path path = Paths.get("cap.png");
        try {  buffer = Files.readAllBytes(path); }
        catch(IOException e) {}
    }
    
    public byte[] getBytes() { return buffer; }
}
