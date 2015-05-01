/**
 * Write a description of class Main here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class TestingClass
{
    public TestingClass(){
        String test1 = "0, 1, 2, 3, 4, 5";
        String test2 = "0, 1, 2, 3";
        String test3 = "0, 1";
        String test4 = "5, 11, 10";
        String test5 = "5, 11, 2";
        String test6 = "7, 11, 2";
        String verificaiton = "";

        
        //Build the graph
        int s, t;
        Graph g = new Graph();
        g.addVertex(0,1);        g.addVertex(0,2);        g.addVertex(1,2);        g.addVertex(1,3);
        g.addVertex(2,3);        g.addVertex(2,4);        g.addVertex(2,5);        g.addVertex(3,4);
        g.addVertex(3,5);        g.addVertex(4,5);

        //g.toString();

        s=0;t=5;
        String r = s+"";
        System.out.println("Longest Path from: " + s + " to "+  t);
        verificaiton = g.longestPath(s,t, r);
        System.out.print("Returned: " + verificaiton + " Expected: " + test1);
        if(verificaiton.equals(test1)) {                
            System.out.print("\tTest 1 PASSED!");
        }else {
            System.out.print("\tTest 1 FAILED!");
        }
        System.out.println();
        s=0;t=3; r = s+"";
        System.out.println("Longest Path from: " + s + " to "+  t);
        verificaiton = g.longestPath(s,t, r);
        System.out.print("Returned: " + verificaiton + " Expected: " + test2);
        if(verificaiton.equals(test2)) {                
            System.out.print("\tTest 2 PASSED!");
        }else {
            System.out.print("\tTest 2 FAILED!");
        }
        System.out.println();
        s=0;t=1; r = s+"";
        System.out.println("Longest Path from: " + s + " to "+  t);
        verificaiton = g.longestPath(s,t, r);
        System.out.print("Returned: " + verificaiton + " Expected: " + test3);
        if(verificaiton.equals(test3)) {                
            System.out.print("\tTest 3 PASSED!");
        }else {
            System.out.print("\tTest 3 FAILED!");
        }
        System.out.println();

        s = 5;t = 10;         
        Graph g6 = new Graph();        
        g6.addVertex(5,11); g6.addVertex(7,8);g6.addVertex(7,11);g6.addVertex(3,8);
        g6.addVertex(3,10);g6.addVertex(11,2);g6.addVertex(11,9);g6.addVertex(11,10);
        g6.addVertex(8,9);        
        String r6 = s + "";
        System.out.println("Longest Path from: " + s + " to "+  t);
        verificaiton = (g6.longestPath(s,t, r6)).trim();
        System.out.print("Returned: " + verificaiton + " Expected: " + test4);
        if(verificaiton.equals(test4)) {                
            System.out.print("\tTest 4 PASSED!");
        }else {
            System.out.print("\tTest 4 FAILED!");
        }
        System.out.println();
        s=5;t=2;r6 = s+"";
        System.out.println("Longest Path from: " + s + " to "+  t);
        verificaiton = g6.longestPath(s,t, r6);
        System.out.print("Returned: " + verificaiton + " Expected: " + test5);
        if(verificaiton.equals(test5)) {                
            System.out.print("\tTest 5 PASSED!");
        }else {
            System.out.print("\tTest 5 FAILED!");
        }
        System.out.println();
        s=7;t=2;r6 = s+"";
        System.out.println("Longest Path from: " + s + " to "+  t);
        verificaiton = g6.longestPath(s,t, r6);
        System.out.print("Returned: " + verificaiton + " Expected: " + test6);
        if(verificaiton.equals(test6)) {                
            System.out.print("\tTest 6 PASSED!");
        }else {
            System.out.print("\tTest 6 FAILED!");
        }
        System.out.println();
    }

    public static void Main(String[] args) {
        new TestingClass();        
    }
}
