import javax.swing.*; 
import java.awt.*; 
import java.awt.event.*; 

/** A graphical interface for Simple_OS communication */ 
public class GUISimpleOS implements ActionListener
{
    private JFrame frame; 

    private JMenuItem exitMenuItem; 
    private JMenuItem exitSimpleOSMenuItem; 
    private JMenuItem toggleReadingMenuItem; 
    private JMenuItem sendTextMenuItem; 

    private JMenuItem helpAboutMenuItem; 

    private SimpleOSWriter simpleOSWriter; 

    private SimpleOSReader simpleOSReader; 
    private boolean simpleOSReaderStopped; 

    /** responds to menu item activations */ 
    public void actionPerformed(ActionEvent e) 
    {
        if (e.getSource() == exitMenuItem)
        {
            System.exit(0); 
        }
        else if (e.getSource() == exitSimpleOSMenuItem)
        {
            /* send "exit", assuming Simple_OS program shuts down when receiving this 
               string! */ 
            simpleOSWriter.writeString("exit"); 
        }
        else if (e.getSource() == toggleReadingMenuItem)
        {
            if (simpleOSReaderStopped)
            {
                simpleOSReaderStopped = false; 
                simpleOSReader.reActivate(); 
            }
            else 
            {
                simpleOSReaderStopped = true; 
                simpleOSReader.deActivate(); 
            }
        }
        else if (e.getSource() == sendTextMenuItem)
        {
            String textToSend = JOptionPane.showInputDialog(frame, "Text to send", "Text to Simple_OS", 
                                                            JOptionPane.QUESTION_MESSAGE); 
            if (textToSend != null && textToSend.length() > 0)
            {
                simpleOSWriter.writeString(textToSend); 
            }
        }
        else if (e.getSource() == helpAboutMenuItem)
        {
            JOptionPane.showMessageDialog(frame, 
                "Reads commands from Simple_OS\n Can send text to Simple_OS", 
                "Java/Simple_OS GUI Program 2011-10-04", 
                JOptionPane.INFORMATION_MESSAGE); 
        }
    }

    /** Constructs GUI and performs initializations */ 
    public GUISimpleOS()
    {
        frame = new JFrame("Simple_OS <-> Java"); 

        JPanel messagePanel = new JPanel(); 
        messagePanel.setLayout(new GridLayout(0, 3)); 
        
        MessageLabel commandMessageLabel = new MessageLabel("Command Status"); 
        DrawCommand drawCommand = new DrawCommand(50, commandMessageLabel); 

        MessageLabel readMessageLabel = new MessageLabel("Read Status"); 

	ShowCommand showCommand = new ShowCommand(frame, readMessageLabel); 
	SetCommand setCommand = new SetCommand(frame, readMessageLabel); 

        SimpleOSComm simpleOSComm = new SimpleOSComm(); 
        simpleOSComm.init(); 

        simpleOSReader = new SimpleOSReader(simpleOSComm, drawCommand, readMessageLabel, showCommand, setCommand); 
        simpleOSReaderStopped = false; 

        MessageLabel writeMessageLabel = new MessageLabel("Write Status"); 

        simpleOSWriter = new SimpleOSWriter(simpleOSComm, writeMessageLabel); 

        messagePanel.add(commandMessageLabel); 
        messagePanel.add(readMessageLabel); 
        messagePanel.add(writeMessageLabel); 

        JMenuBar menuBar = new JMenuBar(); 
        frame.setJMenuBar(menuBar); 

        JMenu menu = new JMenu("File");
        menu.setMnemonic(KeyEvent.VK_F);
        menuBar.add(menu);

        sendTextMenuItem = new JMenuItem("Send text to Simple_OS",KeyEvent.VK_E);
        sendTextMenuItem.addActionListener(this); 
        menu.add(sendTextMenuItem); 

        toggleReadingMenuItem = new JMenuItem("Disable/Enable reading"); 
        toggleReadingMenuItem.setMnemonic(KeyEvent.VK_D); 
        toggleReadingMenuItem.addActionListener(this); 
        menu.add(toggleReadingMenuItem); 

        exitSimpleOSMenuItem = new JMenuItem("Exit Simple_OS",KeyEvent.VK_I);
        exitSimpleOSMenuItem.addActionListener(this); 
        menu.add(exitSimpleOSMenuItem); 

        exitMenuItem = new JMenuItem("Exit",KeyEvent.VK_X);
        exitMenuItem.addActionListener(this); 
        menu.add(exitMenuItem); 

        menu = new JMenu("Help");
        menu.setMnemonic(KeyEvent.VK_H);
        menuBar.add(menu);

        helpAboutMenuItem = new JMenuItem("About",KeyEvent.VK_A);
        helpAboutMenuItem.addActionListener(this); 
        menu.add(helpAboutMenuItem); 

        frame.getContentPane().add(drawCommand, BorderLayout.CENTER);
        frame.getContentPane().add(messagePanel, BorderLayout.SOUTH); 

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setLocation(new Point(100, 5)); 
        frame.setSize(new Dimension(750, 500));
        frame.setVisible(true);

        simpleOSReader.start(); 
    }

    public static void main(String[] args)
    {
        GUISimpleOS gso = new GUISimpleOS(); 
    }
}
