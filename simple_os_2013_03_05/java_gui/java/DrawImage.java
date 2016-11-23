import java.awt.*; 
import java.awt.image.*; 

/** Performs drawing of images */ 
public class DrawImage extends GeneralDraw
{
    private ImageNames imageNames; 
    private ImageObserver io; 

    /** Constructor where an image observer is required */ 
    public DrawImage(ImageObserver io)
    {
        this.io = io; 
        imageNames = new ImageNames(25); 
    }

    /** Performs drawing of an image, according to commandString, which 
        specifies an image filename and coordinates */ 
    public void draw(Graphics g, String commandString)
    {
        String fileName; 
        int xCoord = 0; 
        int yCoord = 0; 

        boolean ok = true; 

        String[] beforeAfter = ch.splitFirstDelimiter(commandString); 
        fileName = beforeAfter[0]; 
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
            boolean done = false; 
            int nDraws = 0; 
            boolean drawResult; 

	    String newFileName = "../images/" + fileName + ".gif"; 
  	    Image image = imageNames.getImage(newFileName); 
	    if (image == null)
	    {
		g.drawString(newFileName + " NOT FOUND", xCoord, yCoord); 
		return; 
	    }
            
            /* iterate until image probably is loaded, however not for too long  */ 
            while (!done)
            {
                drawResult = g.drawImage(image, xCoord, yCoord, io); 
                nDraws++; 
                done = drawResult || nDraws > 5; 
                if (!done)
                {
                    try {
                        Thread.sleep(200); 
                    } catch (InterruptedException e) {}
                }
            }
        }
        else
        {
            g.drawString("DrawImage: Parse Error", 10, 40); 
        }
    }
}
