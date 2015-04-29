/**
 * Write a description of class sdasd here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Source
{
    // instance variables - replace the example below with your own
    public static void main(String args[]) {
        //Five points to use for testing
        //1, 4
        //6, 2
        //2, 8
        //3, 9
        //8, 7
        Graph pointField = new Graph();

        Vert _11 = pointField.addVector(1, 1);
        Vert _5  = pointField.addVector(2, 2);
        Vert _2  = pointField.addVector(3, 3);
        Vert _7  = pointField.addVector(4, 4);
        Vert _9  = pointField.addVector(5, 5);
        Vert _8  = pointField.addVector(6, 6);
        Vert _3  = pointField.addVector(7, 7);
        Vert _10 = pointField.addVector(8, 8);
        
        
        _5.neighbors.add(_11);
        _11.neighbors.add(_2);
        _11.neighbors.add(_10);
        _11.neighbors.add(_9);
        _7.neighbors.add(_11);
        _7.neighbors.add(_8);
        _3.neighbors.add(_8);
        _3.neighbors.add(_10);
        _3.neighbors.add(_9);
        
        

        //cout << a->
        //graph* perms[5] = { a, b, c, d, e };

        //permute(10, 10, POINTS);
    }
}
