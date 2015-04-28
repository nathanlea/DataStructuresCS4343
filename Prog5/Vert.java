import java.util.ArrayList;
/**
 * Write a description of class Vert here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Vert
{
    // instance variables - replace the example below with your own
    public int u;
    public int v;
    public int num_neightbor;
    public ArrayList neighbors;

    /**
     * Constructor for objects of class Vert
     */
    public Vert(int a, int b)
    {
        // initialise instance variables
        u=a;
        v=b;
        neighbors = new ArrayList<Vert>();
    }
}
