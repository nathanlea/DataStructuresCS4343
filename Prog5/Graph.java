import java.util.ArrayList;
/**
 * Write a description of class Graph here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Graph
{
    // instance variables - replace the example below with your own
    int u = 5;
    int v = 10;
    ArrayList points;

    /**
     * Constructor for objects of class Graph
     */
    public Graph()
    {
        // initialise instance variables
        points = new ArrayList<Vert>();
    }   
    //Set Vector
    void setNeighbor(Vert a, Vert b) {
        (a.neighbors).add(b);
    }
    Vert getVert(int x, int y) {
        for (int i = 0; i < points.size(); i++) {
            Vert curr = (Vert)points.get(i);
            if (x == curr.u && y == curr.v) {
                return curr;
            }
            else return null;
        }
        return null;
    }
    Vert addVector(int x, int y) {
        Vert newVert =  new Vert(x,y);
        points.add(newVert);
        return newVert;
    }
    void setCoords(int x, int y) {
        //vector* g = new vector();
        u = x;
        v = y;
    }
}
