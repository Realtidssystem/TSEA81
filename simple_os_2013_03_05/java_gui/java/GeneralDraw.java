import java.awt.*; 

/** An abstract class for general drawing. Provides a command handler 
    and a specification for a draw method */ 
public abstract class GeneralDraw
{
    /** Command handler for command text processing */ 
    protected CommandHandler ch; 

    /** Constructor which creates a command handler */ 
    protected GeneralDraw()
    {
        ch = new CommandHandler(); 
    }

    /** Shall perform drawing, according to the given command */ 
    abstract protected void draw(Graphics g, String commandString); 
}
