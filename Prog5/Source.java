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
        //
        //make some vectors 
        //Get 10 random points to find the longest path...
        /*graph* POINTS [10];
        for (int i = 0; i < 10; i++) {
        int r1 = rand();
        int r2 = rand();
        POINTS[i] = new graph(r1, r2);
        }*/

        //Five points to use for testing
        //1, 4
        //6, 2
        //2, 8
        //3, 9
        //8, 7
        Graph pointField = new Graph();

        Vert a = pointField.addVector(1, 1);
        Vert b = pointField.addVector(2, 2);
        Vert c = pointField.addVector(3, 3);
        Vert d = pointField.addVector(4, 4);

        System.out.println("" + a.u);
        System.out.println("" + d.v);

        //cout << a->
        //graph* perms[5] = { a, b, c, d, e };

        //permute(10, 10, POINTS);
    }
}
