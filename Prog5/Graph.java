import java.util.*;
/**
 * Write a description of class Graph here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Graph
{
    ArrayList<ArrayList<Integer>> map = new ArrayList<ArrayList<Integer>>();
    ArrayList<ArrayList<String>> lookup = new ArrayList<ArrayList<String>>();
    public void Graph() {

    }

    /****************************************************************
     * FUNCTION: addVertex
     * ARGUMENTS: int, int
     * 
     * DESCRIPTION:
     * Takes a u, starting point, and a v, ending points. and adds 
     * the connection between the new vertx and adds into the 
     * 2D array to examplify a connection between the two nodes
     * 
     * RUNTIME: O(1)
     * Assuming the inilization of the arrayList is a trivial constant task
     * and not part of the overall algorithm as it only has to be ran the
     * first time, the function only adds one thing to an arrayList making
     * the runtime O(1)
     ***************************************************************/

    public void addVertex(int u, int v) {
        try {
            map.get(u).add(v);
        } catch (Exception e) {
            for(int i=0;i<=u;i++) {
                map.add(new ArrayList<Integer>());
            }
            map.get(u).add(v);
        }
    }

    /****************************************************************
     * FUNCTION: longestPath
     * ARGUMENTS: int, int, String
     * RETURNS: String
     * 
     * DESCRIPTION:
     * Taks the starting point, s, and the ending point, t, and finds
     * all the possible connections from s and adds all these connections
     * to the lookUp table to enable top down memoization from the table
     * if a similar problem is called earlier the problem as already been solved
     * and if can just pull it from the table and not have to solve the problem
     * 
     * RUNTIME: Theta(lg(n))
     * Worst case would be everything is connected to one central element in 
     * a web type fasion which then the longest path would be any of the elements but 
     * the code will still run through adding all of the elements adding the to
     * the path, making the run time O(n)
     * Thats a terrible DAG so in the average case, lets say everything is evenly connected together
     * making the max distance to any point the same as a tree, and thus the max elements that
     * would have to be ran through would be theta(lg(n)).
     * 
     ***************************************************************/
    public String longestPath(int s, int t, String r) {
        ArrayList<Integer> h = map.get(s);
        int i = 0;
        String back = r;
        if(lookUp(s,t) != null) {
            r = lookUp(s,t);
            if(r.charAt(r.length()-1)-48==t) {
                return r;
            } else return longestPath(r.charAt(r.length()-1)-48,t, r);
        }
        else {
            while(h.size() > i) {
                if(h.get(i) == t) {
                    addPath(s, t, (r + ", " + t ));
                    return (r + ", " + t );
                }
                else {
                    r += ", "+ Integer.toString(h.get(i));
                    int temp = h.get(i);
                    addPath(s,temp,r);
                    longestPath(h.get(i), t, r);
                    r = back;
                    i++;
                }
            }
            return lookUp(s,t);
        }
    }

    /****************************************************************
     * FUNCTION: addPath
     * ARGUMENTS: int, int, String
     * 
     * DESCRIPTION:
     * Helper method to longestPath, adds the path that longestPath 
     * found to the lookup table in the correct location
     * Also if not initialized yet the method also initialized the
     * correct number of new String/ArrayLists
     * 
     * RUNTIME: O(1)
     * Assuming if the functions are initilized, as that only has to be done once
     * the function runs straight through only adding a String to an array
     ***************************************************************/
    public void addPath(int s, int t, String r) {
        int a = r.charAt(0)-48;
        int b = r.charAt(r.length()-1)-48;
        if(r.length()<1) return;
        try {
            if(lookup.get(a).get(b).length() < r.length()) {
                lookup.get(a).set(b,r);
            } else {
                return;
            }            
        }catch(Exception e) {
            for(int i=0;i<=a;i++) {
                lookup.add(new ArrayList<String>());
            }
            for(int i=0;i<=t;i++) {
                lookup.get(a).add(new String());
            }
            lookup.get(a).set(b,r);
        }
    }

    /****************************************************************
     * FUNCTION: lookUP
     * ARGUMENTS: int, int
     * 
     * DESCRIPTION:
     * Takes a u, starting point, and a v, ending points and locates
     * a path that has been found and return that path if it exist
     * 
     * RUNTIME: Theta(n)
     * With the assumption above that everything is evenly spead apart, 
     * the average case. Would give the max number of connected paths
     * from the starting element, 2^(lg(n)), thus making the average run time
     * of the lookup table n.
     ***************************************************************/
    public String lookUp(int s, int t) {
        try {
            ArrayList<String> h = lookup.get(s);
            for(int i =0;i<h.size();i++){
                String[] possPath = h.get(i).split(", ");
                if(possPath.length>1) { 
                    if(Integer.parseInt(possPath[0].trim()) == s) {
                        if(Integer.parseInt(possPath[possPath.length-1].trim()) == t) {
                            String ret = "";
                            for(int j = 0; j<possPath.length;j++) {
                                ret += possPath[j];
                                if(!(j+2>possPath.length)) ret+= ", ";
                            }
                            return ret;
                        }
                    }
                }
            }
            return null;
        }catch(Exception e) {
            return null;
        }
    }

    /****************************************************************
     * FUNCTION: toString
     * ARGUMENTS: 
     * RETURN: String
     * 
     * DESCRIPTION:
     * Draws to 2D array showing the connections between the vertices
     ***************************************************************/
    public String toString() {
        for(int i = 0, x = 0 ; i < map.size(); x++) {
            if(x == i) {                
                for(int j = 0,y = 0 ; j < map.get(i).size(); y++){
                    if(y==map.get(i).get(j)) {
                        System.out.print(" 1 ");
                        j++;
                    } else {
                        System.out.print(" 0 ");
                    }
                }
                System.out.println("");
                i++;
            }

            else {
                System.out.println("X");
            }
        }
        return "";
    }
}
