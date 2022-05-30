import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class LanternFestival {

    public static int[] lanternFestival(int n, int[][] prefs) {
      if(n % 2 == 0){
        return (new int[]{-1});
      }
      ArrayList<Integer>[] parentreq = (new ArrayList<Integer>())[n]; // list of things that n must be a parent of 
      ArrayList<Integer>[] childreq = (new ArrayList<Integer>())[n]; // list of things that n must be a child of
      int root = -1;
      int[][] tree = new int[n][2];
      ArrayList<Integer> possibleleaves = new ArrayList<Integer>();
      ArrayList<Integer> oneempty = new ArrayList<Integer>();
      ArrayList<Integer> parentless = new ArrayList<Integer>();
      int blankcount = 0;
      for(int i = 0; i < prefs.length; i++){
        int[] pref = prefs[i];
        parentreq[pref[0]].add(pref[1]);
        childreq[pref[1]].add(pref[0]);
      }
      for(int i = 0; i < n; i++){ // process cases where n must be a child of more than 1 thing
        if(childreq[i].size() > 1){
          // IMPOSSIBLE
          return (new int[]{-1});
        }
        if(childreq[i].size() == 0){
          parentless.add(i);
        }
      }
      for(int i = 0; i < n; i++){
        if(parentreq[i].size() > 2){
          // IMPOSSIBLE
          return (new int[]{-1});
        }
        if(parentreq[i].size() == 2){
          tree[i][0] = Math.min(parentreq[i].get(0), parentreq[i].get(1));
          tree[i][1] = Math.max(parentreq[i].get(0), parentreq[i].get(1));
        }
        if(parentreq[i].size() == 1){
          tree[i][0] = parentreq[i].get(0);
          tree[i][1] = -1;
          oneempty.add(i);
          blankcount++;
        }
        if(parentreq[i].size() == 0){
          possibleleaves.add(i);
        }
      }
      if(possibleleaves.size() < ((n + 1) / 2)){
        // IMPOSSIBLE
        return (new int[]{-1});
      }
      while(parentless.size() > 1){
        int curassign = parentless.remove();
        int toassignto = oneempty.remove();
        int curv = tree[toassignto][0];
        tree[toassignto][0] = Math.min(curv, curassign);
        tree[toassignto][1] = Math.max(curv, curassign);
      }
      if(oneempty.size() != 0){
        // IMPOSSIBLE
        return (new int[]{-1});
      }
      root = parentless;
      int[] output = new int[n];
      Deque<Integer> bfs = new ArrayDeque<Integer>();
      bfs.addLast(root);
      for(int i = 0; i < n; i++){
        output[i] = bfs.removeFirst();
        if(output[i]
      }
      return new int[];
    }


    // Do not modify below this line
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.valueOf(reader.readLine());

        for (int i = 0; i < t; i++) {
            String inputNodes = reader.readLine();
            int n = Integer.valueOf(inputNodes);
            String edgeNum = reader.readLine();
            int k = Integer.valueOf(edgeNum);
            int[][] prefs = new int[k][2];
            for (int z = 0; z < k; z++) {
                String inputEdges = reader.readLine();
                String[] inputE = inputEdges.split(" ");
                prefs[z][0] = Integer.valueOf(inputE[0]);
                prefs[z][1] = Integer.valueOf(inputE[1]);
            }

            int [] output = lanternFestival(n, prefs);
            for (Integer e: output) {
                System.out.println(e);
            }

        }
    }
}