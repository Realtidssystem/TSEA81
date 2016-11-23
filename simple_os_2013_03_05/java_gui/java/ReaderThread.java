/** Performs repeated reading from Simple_OS via shared memory */ 
public class ReaderThread extends Thread
{
    /** The actual reader object */ 
    private SimpleOSReader simpleOSReader; 

    /** Time delay in ms between succesive read attempts */ 
    private int delayMs; 

    /** Constructs a reader thread, given a Simple_OS reader object, and 
        a specified delay between succesive read attempts */ 
    public ReaderThread(SimpleOSReader simpleOSReader, int delayMs)
    {
        this.simpleOSReader = simpleOSReader; 
        this.delayMs = delayMs; 
    }

    /** Performs reading */ 
    public void run()
    {
        while(true)
        {
            simpleOSReader.readString(); 
            try
            {
                sleep(delayMs);
            } catch (InterruptedException e) {}
        }
    }
}
