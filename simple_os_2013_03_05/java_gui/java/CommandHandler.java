/** Command text processing */ 
public class CommandHandler
{
    private char delimiter = ':'; 

    /** Sets a delimiter */ 
    public void setDelimiter(char delimiter)
    {
        this.delimiter = delimiter; 
    }

    /** Returns string before delimiter */ 
    public String getBeforeDelimiter(String string)
    {
        int delimIndex = string.indexOf(delimiter); 
        if (delimIndex > 0)
        {
            return string.substring(0, delimIndex); 
        }
        else
        {
            return string; 
        }
    }

    /** Returns string after delimiter, or the empty string */ 
    public String getAfterDelimiter(String string)
    {
        int delimIndex = string.indexOf(delimiter); 
        if (delimIndex > 0)
        {
            return string.substring(delimIndex + 1, string.length()); 
        }
        else
        {
            return ""; 
        }
    }

    /** Returns an array of two strings, before and after the delimiter */ 
    public String[] splitFirstDelimiter(String string)
    {
        String[] returnString = new String[2]; 
        returnString[0] = getBeforeDelimiter(string); 
        returnString[1] = getAfterDelimiter(string); 
        return returnString; 
    }

    /** Returns true if string represents an integer, false otherwise */ 
    public boolean isInt(String string)
    {
        boolean ok = true; 
        int intValue;
        try 
        {
            intValue = Integer.parseInt(string.substring(2, string.length()), 16); 
            // intValue = Integer.parseInt(string, 16); 
        }
        catch (NumberFormatException e) 
        {
            System.err.println("ERROR: could not parse " + string); 
            intValue = 0; 
            ok = false; 
        }
        return ok; 
    }

    /** Converts string to integer and returns the integer value found. If this is not possible, 
        errorValue is returned */
    public int string2Int(String string, int errorValue)
    {
        boolean ok = true; 
        int intValue;
        try 
        {
            intValue = Integer.parseInt(string.substring(2, string.length()), 16); 
            // intValue = Integer.parseInt(string, 16); 
        }
        catch (NumberFormatException e) 
        {
            System.err.println("ERROR: could not parse " + string); 
            intValue = 0; 
            ok = false; 
        }
        if (ok)
        {
            return intValue; 
        }
        else
        {
            return errorValue; 
        }
    }

    /** Returns true if command starts with "draw_" */ 
    public boolean isDrawCommand(String command)
    {
	return command.startsWith("draw_"); 
    }

    /** Returns true if command starts with "show_" */ 
    public boolean isShowCommand(String command)
    {
	return command.startsWith("show_"); 
    }

    /** Returns true if command starts with "set_" */ 
    public boolean isSetCommand(String command)
    {
	return command.startsWith("set_"); 
    }
}

