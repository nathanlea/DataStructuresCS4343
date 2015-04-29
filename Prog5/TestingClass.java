/**
 * Write a description of class Main here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class TestingClass
{
    public TestingClass(){
        //Build the graph
        Graph g = new Graph();
        g.addVertex(0,1);
        g.addVertex(0,2);
        g.addVertex(1,2);
        g.addVertex(1,3);
        g.addVertex(2,3);
        g.addVertex(2,4);
        g.addVertex(2,5);
        g.addVertex(3,4);
        g.addVertex(3,5);
        g.addVertex(4,5);
        
        g.toString();
        
        System.out.println(g.longestPath(0,5));
    }
    
    public static void Main(String args[]) {
       new TestingClass();        
    }
}
