import javax.swing.*; 

/** Sets parameters, e.g. size of GUI frame, according to commands */ 
public class SetCommand
{
    /** Handles command text processing */ 
    private CommandHandler ch; 

    /** GUI frame */ 
    private JFrame frame; 

    /** Message label for printout */ 
    private MessageLabel messageLabel; 

    /** Default constructor */ 
    public SetCommand(JFrame frame, MessageLabel messageLabel)
    {
        ch = new CommandHandler(); 
	this.frame = frame; 
	this.messageLabel = messageLabel; 
    }

    /** Processes commandLine, and performs actions according to command */ 
    public void newCommand(String commandLine)
    {
        String[] beforeAfter = ch.splitFirstDelimiter(commandLine); 

        String command = beforeAfter[0]; 

	boolean ok = true; 

	int xCoord = 0; 
	int yCoord = 0; 

	if (!command.equals("set_size"))
	{
	    messageLabel.error("Illegal command"); 
	    return; 
	}

        beforeAfter = ch.splitFirstDelimiter(beforeAfter[1]); 

        if (ch.isInt(beforeAfter[0]))
        {
            xCoord = ch.string2Int(beforeAfter[0], 0); 
            if (ch.isInt(beforeAfter[1]))
            {
                yCoord = ch.string2Int(beforeAfter[1], 0); 
            }
            else
            {
                ok = false; 
            }
        }
        else
        {
            ok = false; 
        }

        if (ok)
        {
	    frame.setSize(xCoord, yCoord); 
	    frame.setVisible(true); 
	}
	else
        {   
            messageLabel.error("Illegal command"); 
	}
    }
}
