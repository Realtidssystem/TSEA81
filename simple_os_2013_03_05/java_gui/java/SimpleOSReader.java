/** Reader class for Simple_OS communication */ 
public class SimpleOSReader 
{
    private SimpleOSComm simpleOSComm; 
    private DrawCommand drawCommand; 
    private MessageLabel messageLabel; 
    private boolean isActivated; 
    private ReaderThread readerThread; 

    private ShowCommand showCommand; 
    private SetCommand setCommand; 

    private CommandHandler ch; 

    private final int delayMs = 100; 
    private final double nSecondsTimeOut = 5; 

    private int nEmptyReadsForTimeOut; 
    private int nEmptyReads; 

    /** Constructs a reader object, given a Simple_OS communication object, an object for 
        draw command handling, an object for message printouts, an object for
        show command handling, and an object for set command handling */ 
    public SimpleOSReader(
       SimpleOSComm simpleOSComm, DrawCommand drawCommand, MessageLabel messageLabel, 
       ShowCommand showCommand, SetCommand setCommand)
    {
        this.drawCommand = drawCommand; 
        this.messageLabel = messageLabel; 
        this.simpleOSComm = simpleOSComm; 
	this.showCommand = showCommand; 
	this.setCommand = setCommand; 

        messageLabel.info("Ok"); 
        readerThread = new ReaderThread(this, delayMs); 
        isActivated = false; 

        nEmptyReadsForTimeOut = (int) ( nSecondsTimeOut * 1000 / ((double) delayMs) + 0.5); 
        nEmptyReads = 0; 

        ch = new CommandHandler(); 

        /* set delimiter for command sequences from Simple_OS */ 
        ch.setDelimiter(';'); 
    }

    private boolean simpleOSMessageEmpty(String message)
    {
        return message.equals("__#APP_UI_EMPTY#__"); 
    }

    private boolean simpleOSMessageError(String message)
    {
        return message.equals("__#READ_ERROR#__"); 
    }

    /** Starts reading thread */ 
    public void start()
    {
        isActivated = true; 
        readerThread.start(); 
        messageLabel.info("Ok"); 
    }

    /** Temporarily stops reading thread */ 
    public synchronized void deActivate()
    {
        isActivated = false; 
        messageLabel.note("Reading disabled!"); 
    }

    /** Reactivates reading thread */ 
    public synchronized void reActivate()
    {
        /* assign zero to time out counter */ 
        nEmptyReads = 0; 
        isActivated = true; 
        notify(); 
        messageLabel.info("Ok"); 
    }

    /** Reads a string from Simple_OS, makes the calling thread wait if reading 
        is disabled */ 
    public synchronized void readString()
    {
        String simpleOSMessage; 

        while(!isActivated)
        {
            try
            {
                wait(); 
            } catch (InterruptedException e) {}
        }

        simpleOSMessage = simpleOSComm.readString(); 
        // System.out.println(simpleOSMessage); 
        if (simpleOSMessage == null)
	{
            messageLabel.error("No connection"); 
            simpleOSComm.close(); 
            simpleOSComm.init(); 
	}
        else if (simpleOSMessageError(simpleOSMessage))
        { 
            messageLabel.error("Read error"); 
        }
        else if (simpleOSMessageEmpty(simpleOSMessage))
        {
            nEmptyReads++; 
            /* check for time out */ 
            if (nEmptyReads >= nEmptyReadsForTimeOut)
            {
                messageLabel.note("Read buffer empty"); 
                nEmptyReads = 0; 
            }
        }
        else
        {
	    nEmptyReads = 0; 
            messageLabel.info("Ok"); 
            boolean done; 
            String[] beforeAfter; 

            /* parse command sequence */ 

            beforeAfter = ch.splitFirstDelimiter(simpleOSMessage); 
            done = false; 

            while (!done)
            {
                // System.out.println("bfa_0: " + beforeAfter[0]); 
                // System.out.println("bfa_1: " + beforeAfter[1]); 

                if (ch.isDrawCommand(beforeAfter[0]))
		{
                    drawCommand.newCommandLine(beforeAfter[0]); 
		}
                else if (ch.isShowCommand(beforeAfter[0]))
		{
                    showCommand.newCommand(beforeAfter[0]); 
		}
                else if (ch.isSetCommand(beforeAfter[0]))
		{
                    setCommand.newCommand(beforeAfter[0]); 
		}
 	        else
		{
                    if (beforeAfter[0].length() == 0)
		    {
                        // TODO this should not happen, investigate why
                        // System.err.println("NO LENGTH"); 
		    }
		    else
		    {
                        messageLabel.error("Illegal command"); 
                        System.err.println("Illegal command: " + beforeAfter[0]); 
                        for (int i = 0; i < beforeAfter[0].length(); i++)
                        {
                            System.err.print(beforeAfter[0].codePointAt(i)); 
                            System.err.print(' '); 
                            System.err.print((int) beforeAfter[0].charAt(i)); 
                            System.err.println(); 
                        }
		    }
		}
                if (beforeAfter[1].length() > 0)
                {
                    beforeAfter = ch.splitFirstDelimiter(beforeAfter[1]); 
                }
                else
                {
                    done = true; 
                }
            }
        }
    }
}

