import java.util.*;
public class Donuts{
  static Deque<Integer> DFSStack = new ArrayDeque<Integer>();
  static ArrayList<HashSet<Integer>> adj = new ArrayList<HashSet<Integer>>();
  static ArrayList<HashSet<Integer>> adjToppings = new ArrayList<HashSet<Integer>>();
  static int[] toppingMapping = null;
  static int maxTopping = 1; // toppings count + 1
  public static void DFSHandler(){
    while(DFSStack.peek() != null){
      //System.out.println(DFSStack);
      DFS();
    }
  }
  public static void DFS(){
    try{
      int curCheck = DFSStack.remove();
      if(toppingMapping[curCheck] != 0){ // already assigned
        return;
      }
      for(int i = 1; i < maxTopping; i++){
        if(!adjToppings.get(curCheck).contains(i)){
          toppingMapping[curCheck] = i;
          break;
        }
      }
      if(toppingMapping[curCheck] == 0){ // add new topping
        toppingMapping[curCheck] = maxTopping;
        maxTopping++;
      }
      for(int adjDonut : adj.get(curCheck)){
        adjToppings.get(adjDonut).add(toppingMapping[curCheck]);
        if(toppingMapping[adjDonut] == 0){
          //System.out.println("Added " + adjDonut + " to BFS Queue");
          DFSStack.addFirst(adjDonut);
        }
      }
    } catch (NoSuchElementException e){
      return;
    }
  }
  public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    HashMap<String, Integer> mapping = new HashMap<String, Integer>();
    int n = in.nextInt();
    int[] outputTypeArr = new int[n];
    String first = null;
    String prev = null;
    int curNumber = 0;
    for(int i = 0; i < n; i++){
      String temp = in.next();
      if(first == null){
        first = temp;
      }
      if(!mapping.containsKey(temp)){
        mapping.put(temp, curNumber);
        adj.add(new HashSet<Integer>());
        adjToppings.add(new HashSet<Integer>());
        curNumber++;
      }
      outputTypeArr[i] = mapping.get(temp);
      if(prev != null){
        adj.get(mapping.get(temp)).add(mapping.get(prev));
        adj.get(mapping.get(prev)).add(mapping.get(temp));
      }
      prev = temp;
    }
    adj.get(mapping.get(prev)).add(mapping.get(first));
    adj.get(mapping.get(first)).add(mapping.get(prev));
    //System.out.println(mapping);
    //System.out.println(adj);
    toppingMapping = new int[adj.size()];
    DFSStack.add(0);
    DFSHandler();
    //System.out.println(Arrays.toString(toppingMapping));
    System.out.println(maxTopping - 1);
    for(int i = 0; i < n; i++){
      if(i != 0){
        System.out.print(" ");
      }
      System.out.print(toppingMapping[outputTypeArr[i]]);
    }
  }
}
