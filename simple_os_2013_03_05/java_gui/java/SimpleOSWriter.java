/** Class for writing strings to Simple_OS */ 
public class SimpleOSWriter
{
    private SimpleOSComm simpleOSComm; 
    private MessageLabel messageLabel; 

    /** Constructs a writer object, given a Simple_OS communication object and 
        an object for message printouts */ 
    public SimpleOSWriter(SimpleOSComm simpleOSComm, MessageLabel messageLabel)
    {
        this.simpleOSComm = simpleOSComm;       
        this.messageLabel = messageLabel; 
        messageLabel.info("Ok"); 
    }

    private boolean simpleOSMessageFull(int writeReturnValue)
    {
        return writeReturnValue == 1; 
    }

    private boolean simpleOSMessageError(int writeReturnValue)
    {
        return writeReturnValue == -1; 
    }

    /** Writes a string to Simple_OS */ 
    public void writeString(String simpleOSMessage)
    {
        int writeReturnValue;   

        writeReturnValue = simpleOSComm.writeString(simpleOSMessage); 
 
        if (simpleOSMessageError(writeReturnValue))
        {
            messageLabel.error("Write error"); 
        }
        else if (simpleOSMessageFull(writeReturnValue))
        {
            messageLabel.note("Write buffer full"); 
        }
        else
        {
            messageLabel.info("Ok"); 
        }
    }
}

