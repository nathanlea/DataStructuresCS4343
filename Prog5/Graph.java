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
    public void Graph() {
        
    }

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
    
    public String longestPath(int s, int t) {
        String path = "";
        if(s==t) {
            return (s+"");
        }
        for(int i=0;i<map.get(s).size();i++) {
            int temp = map.get(s).get(i);
            path = path + temp + longestPath(temp, t);
        }   
        return path;
    }

    public ArrayList<Integer> getEdgesFrom(int u) {
        return map.get(u);
    }

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
