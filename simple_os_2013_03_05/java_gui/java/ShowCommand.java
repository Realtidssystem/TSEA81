import javax.swing.*; 

/** Displays information according to commands */ 
public class ShowCommand
{
    /** Handles command text processing */ 
    private CommandHandler ch; 

    /** Frame for display of information */ 
    private JFrame frame; 

    /** Message label for printout */ 
    private MessageLabel messageLabel; 

    /** Default constructor */ 
    public ShowCommand(JFrame frame, MessageLabel messageLabel)
    {
        ch = new CommandHandler(); 
	this.frame = frame; 
	this.messageLabel = messageLabel; 
    }

    class displayThread extends Thread
    {
	JFrame frame; 
	String message; 

	public displayThread(JFrame frame, String message)
	{
	    this.frame = frame; 
            this.message = message; 
	}

	public void run()
	{
            JOptionPane.showMessageDialog(frame, message, "Error", JOptionPane.ERROR_MESSAGE); 
	}
    }

    private void displayError(String message)
    {
        new displayThread(frame, message).start(); 
    }

    /** Processes commandLine, and displays information according to command */ 
    public void newCommand(String commandLine)
    {
        String command = ch.getBeforeDelimiter(commandLine); 
        if (command.equals("show_error"))
        {
            displayError(ch.getAfterDelimiter(commandLine)); 
        }
        else 
        {
            messageLabel.error("Illegal command"); 
        }
    }
}
