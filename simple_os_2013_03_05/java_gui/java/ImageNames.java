import java.awt.*; 
import java.awt.image.*; 
import java.io.*; 

/** Stores names and images, can deliver an image given a name */ 
public class ImageNames
{
    private int nameIndex; 

    private Image[] images; 
    private String[] names; 

    /** Constructor where the maximum number of stored images (and names) is specified */ 
    public ImageNames(int maxNImages) 
    {
        images = new Image[maxNImages]; 
        names = new String[maxNImages]; 
        for (int i = 0; i < names.length; i++)
        {
            names[i] = new String(""); 
        }
        nameIndex = 0; 
    }

    /** Returns an image, corresponding to the file "name". Images are loaded 
        on demand, i.e. the first time they are requested */ 
    public Image getImage(String name)
    {
        int i = 0; 
        boolean found = false; 
        Image image = null; 

        while (i < nameIndex && !found)
        {
            if (name.length() > 0 && name.equals(names[i]))
            {   
                found = true; 
                image = images[i]; 
            }
            i++; 
        }

        if (!found)
        {
	    try
            {
                FileInputStream fileStream = new FileInputStream(name); 
	    } catch (FileNotFoundException e)
	    {
		return null; 
	    }
            names[nameIndex] = new String(name); 
            image = Toolkit.getDefaultToolkit().getImage(name); 
            /** store image for future reference */ 
            images[nameIndex] = image; 
            nameIndex++; 
        }

        return image; 
    }
}
