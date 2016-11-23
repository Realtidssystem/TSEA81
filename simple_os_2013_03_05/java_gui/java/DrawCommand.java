import javax.swing.*; 
import java.awt.*; 

/** Performs drawing according to commands */ 
public class DrawCommand extends JPanel
{
    /** Handles command text processing */ 
    private CommandHandler ch; 

    /** A buffer with stored commands */ 
    private String commandBuffer[]; 

    /** Current index in the command buffer */ 
    private int commandIndex; 

    /** Message label for printout */ 
    private MessageLabel messageLabel; 

    /** Flag for controlling drawing */
    private boolean drawEnabled; 

    /** Drawing object for strings */ 
    private DrawString drawString; 

    /** Drawing object for images */ 
    private DrawImage drawImage; 

    /** Constructs a DrawCommand object with a given size of the command 
        buffer, and a given message label */ 
    public DrawCommand(int commandBufferLength, MessageLabel messageLabel)
    {
        ch = new CommandHandler(); 
        commandBuffer = new String[commandBufferLength]; 
        commandIndex = 0; 
        this.messageLabel = messageLabel; 
        drawEnabled = true; 
        drawString = new DrawString(); 
        drawImage = new DrawImage(this); 
        messageLabel.info("Ok"); 
    }

    private boolean isDrawBegin(String commandLine)
    {
        return (ch.getBeforeDelimiter(commandLine).equalsIgnoreCase("draw_begin")); 
    }


    private boolean isDrawEnd(String commandLine)
    {
        return (ch.getBeforeDelimiter(commandLine).equalsIgnoreCase("draw_end")); 
    }

    private boolean commandBufferFull()
    {
        return commandIndex >= commandBuffer.length; 
    }

    private void addCommandLine(String commandLine)
    {
        if (commandIndex < commandBuffer.length)
        {
            commandBuffer[commandIndex] = new String(commandLine); 
            commandIndex++; 
        }
    }

    /** Inserts a new command line in the command buffer, provided the 
        buffer is not full and the command is accepted. General commands 
        are accepted when drawing is not enabled. Drawing is not enabled 
        after the command "draw_begin", and until the command "draw_end" is 
        received. */ 
    public void newCommandLine(String commandLine)
    {
        if (isDrawBegin(commandLine))
        {
            drawEnabled = false; 
            commandIndex = 0; 
        }
        else if (isDrawEnd(commandLine))
        {
            drawEnabled = true; 
            repaint(); 
        }
        else
        {
            if (!drawEnabled)
            {
                if (!commandBufferFull())
                {
                    addCommandLine(commandLine); 
                    messageLabel.info("Ok"); 
                }
                else
                {
                    messageLabel.error("Command buffer full"); 
                }
            }
            else
            {   
                messageLabel.error("draw_begin/draw_end error"); 
            }
        }
    }

    /** Performs drawing, according to the stored commands */ 
    public void drawAll(Graphics g)
    {
        if (drawEnabled)
        {
            for (int i = 0; i < commandIndex; i++)
            {
                String command = ch.getBeforeDelimiter(commandBuffer[i]); 
                if (command.equalsIgnoreCase("draw_string"))
                {
                    drawString.draw(g, ch.getAfterDelimiter(commandBuffer[i])); 
                }
                else if (command.equalsIgnoreCase("draw_image"))
                {
                    drawImage.draw(g, ch.getAfterDelimiter(commandBuffer[i])); 
                }
                else
                {
                    messageLabel.error("Illegal command " + command); 
                }
            }
        }
        else
        {
            messageLabel.info("Nothing to draw"); 
        }
    }

    /** Performs drawing, by calling paintComponent in super class, followed 
        by a call to this.drawAll */ 
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g); 
        drawAll(g); 
    }
}
