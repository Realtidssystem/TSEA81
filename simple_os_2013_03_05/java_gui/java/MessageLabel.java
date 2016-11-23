import javax.swing.*; 
import java.awt.*; 
import javax.swing.border.*; 

/** A label for messages, with a border and a title */ 
public class MessageLabel extends JLabel
{
    /** Constructs a message label with a given title */ 
    public MessageLabel(String title)
    {
        Border titledBorder; 
        Border insideBorder; 

        setHorizontalAlignment(SwingConstants.CENTER); 

        titledBorder = BorderFactory.createEtchedBorder(EtchedBorder.LOWERED); 
        insideBorder = BorderFactory.createEmptyBorder(3, 3, 3, 3); 
        titledBorder = BorderFactory.createTitledBorder(
            titledBorder, title, TitledBorder.DEFAULT_JUSTIFICATION, TitledBorder.DEFAULT_POSITION, 
            new Font("SansSerif", Font.PLAIN, 10)); 
        setBorder(BorderFactory.createCompoundBorder(titledBorder, insideBorder)); 
    }

    /** Displays an information message */ 
    public void info(String message)
    {
        setForeground(Color.BLACK); 
        setText(message); 
    }

    /** Displays a note, e.g. a warning message */ 
    public void note(String message)
    {
        setForeground(Color.MAGENTA); 
        setText(message);  
    }

    /** Displays an error message */ 
    public void error(String message)
    {
        setForeground(Color.RED); 
        setText(message);  
    }

    /** Clears the message area */ 
    public void clear()
    {
        setText(""); 
    }
}
