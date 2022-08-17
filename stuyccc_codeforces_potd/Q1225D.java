import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;
public class Q1225D{
  static int MAX_X = 100000;
  public static int[] primeFactoriseReduced(int x, int k){
    // returns two numbers:
    // o[0] = multiple of prime factorisation but w/ all powers greater than k reduced to k
    // o[1] = needed number to "fill" the prime factorisation of x, -1 if greater than limit
    /*
    for(int i = 2; i <= Math.pow(x, 1 / k); i++){
      int toTest = Math.pow(x, k);
      while(x % toTest == 0){
        x /= toTest;
      }
    }
    */
    int[] o = new int[2];
    ArrayList<int[]> temp = new ArrayList<int[]>();
    for(int i = 2; i <= Math.sqrt(x); i++){
      int[] tempArr = null;
      while(x % i == 0){
        if(tempArr == null){
          tempArr = new int[]{i, 0};
        }
        //System.out.println("Dividing " + x + " by " + i);
        x /= i;
        tempArr[1]++;
      }
      if(tempArr != null){
        temp.add(tempArr);
      }
    }
    if(x != 1){
      temp.add(new int[]{x, 1});
    }
    int selfval = 1;
    int complement = 1;
    for(int i = 0; i < temp.size(); i++){
      int[] tempArr = temp.get(i);
      //System.out.println(Arrays.toString(tempArr));
      tempArr[1] = tempArr[1] % k;
      selfval *= Math.pow(tempArr[0], tempArr[1]);
      if(complement != -1 && tempArr[1] != 0){
        complement *= Math.pow(tempArr[0], k - tempArr[1]);
      }
      if(complement > MAX_X){
        complement = -1;
      }
    }
    /*
    for(int i = 0; i < temp.size(); i++){
      System.out.println(Arrays.toString(temp.get(i)));
    }
    */
    o[0] = selfval;
    o[1] = complement;
    return o;
  }
  public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int k = in.nextInt();
    int[] targetData = new int[n];
    int[] selfVals = new int[n];
    HashMap<Integer, Integer> freqMap = new HashMap<Integer, Integer>();
    for(int i = 0; i < n; i++){
      int x = in.nextInt();
      int[] temp = primeFactoriseReduced(x, k);
      //System.out.println("O: " + Arrays.toString(temp));
      selfVals[i] = temp[0];
      targetData[i] = temp[1];
      freqMap.put(temp[0], freqMap.getOrDefault(temp[0], 0) + 1);
    }
    //System.out.println(freqMap);
    long pairCount = 0;
    for(int i = 0; i < n; i++){
      pairCount += freqMap.getOrDefault(targetData[i], 0);
      if(selfVals[i] == targetData[i]){ // subtract self case
        pairCount--;
      }
    }
    System.out.println(pairCount / 2);
  }
}
