import java.awt.*; 

/** Performs drawing of strings */ 
public class DrawString extends GeneralDraw
{
    /** Performs drawing of a string, according to commandString, which 
        specifies coordinates and the string to draw */ 
    public void draw(Graphics g, String commandString)
    {
        int xCoord = 0; 
        int yCoord = 0; 
        String stringToDraw = "Initial Value"; 

        boolean ok = true; 

        String[] beforeAfter = ch.splitFirstDelimiter(commandString); 
        if (ch.isInt(beforeAfter[0]))
        {
            xCoord = ch.string2Int(beforeAfter[0], 0); 
            beforeAfter = ch.splitFirstDelimiter(beforeAfter[1]); 
            if (ch.isInt(beforeAfter[0]))
            {
                yCoord = ch.string2Int(beforeAfter[0], 0); 
                stringToDraw = beforeAfter[1]; 
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
            g.drawString(stringToDraw, xCoord, yCoord); 
        }
        else
        {
            g.drawString("DrawString: Parse Error", 10, 30); 
        }
    }
}
