import java.io.*;
import java.net.*;

/** Communication with Simple_OS using sockets */ 
public class SimpleOSComm {

    Socket SimpleOSSocket = null;
    BufferedReader fromSimpleOS = null;
    PrintWriter toSimpleOS = null; 

    String hostName = "localhost"; 

    /** Initialisation of communication */ 
    public void init()
    {
	boolean connectionOk = false; 
        int nTries = 0; 

        System.out.println("Initialising communication to Simple_OS");

        while (!connectionOk)
	{ 
            try 
            {
                SimpleOSSocket = new Socket("localhost", 2000); 
                fromSimpleOS = new BufferedReader(
                    new InputStreamReader(SimpleOSSocket.getInputStream()));
                toSimpleOS = new PrintWriter(SimpleOSSocket.getOutputStream(), true); 
                connectionOk = true; 
            }
            catch (Exception e)
	    {
                nTries++; 
                if ((nTries-1) % 10 == 0)
		{
                    int nTriesToPrint = nTries/10 + 1; 
                    System.err.println(
                        "waiting for start of Simple_OS application - n_tries: " + nTriesToPrint); 
		}
                try
                {
                    Thread.sleep(2000);
                } catch (InterruptedException e_sleep) {}
	    }
        }
        System.out.println("Communication link established");
        System.out.println(); 
    }

    /** Reads a string */ 
    public String readString()
    {
        String userInput = "__#APP_UI_EMPTY#__"; 
        // System.out.println("calling in.readLine()"); 
        try 
        {
            userInput = fromSimpleOS.readLine(); 
        }
        catch (Exception e)
	{
            System.err.println("UNKNOWN Exception could not receive from socket"); 
            System.exit(1); 
	}
        // userInput = new String(packet.getData(), 0, packet.getLength());
        // System.out.println("Quote of the Moment: " + userInput);
        return userInput; 
    }

    /** Writes a string */ 
    public int writeString(String message)
    {
        // System.out.println("writeString: " + message); 
        toSimpleOS.print(message + "#"); 
        toSimpleOS.flush(); 
        return 0; 
    }

    public void close()
    {
        try 
	{ 
           toSimpleOS.close(); 
           fromSimpleOS.close(); 
	}
        catch (IOException e)
	{
            System.err.println("IO Exception could not close sockets"); 
            System.exit(1); 
	}
    }
}
