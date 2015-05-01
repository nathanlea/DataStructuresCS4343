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
    ArrayList<ArrayList<String>> path = new ArrayList<ArrayList<String>>();
    ArrayList<ArrayList<String>> lookup = new ArrayList<ArrayList<String>>();
    public void Graph() {

    }

    public void addVertex(int u, int v) {
        try {
            map.get(u).add(v);
        } catch (Exception e) {
            for(int i=0;i<=u;i++) {
                map.add(new ArrayList<Integer>());
                //path.add(new ArrayList<String>());
            }
            map.get(u).add(v);
        }
    }

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
