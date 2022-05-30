import java.io.*;
import java.util.*;
public class Truths2{
  static int[] ExpressionsFalseCount = new int[251]; // 1 indexed
  static int[] ExpressionsTrueCount = new int[251]; // eg. 1|1
  static int[] ExpressionsFalsePCount = new int[251]; // eg. (0%1)
  static int[] ExpressionsTruePCount = new int[251];
  static int[] ExpressionsFalseORInvariantCount = new int[251]; // eg. can't be 0|0, cannot be & with &
  static int[] ExpressionsTrueORInvariantCount = new int[251];
  static final int MOD = 1000000007;
  static void genDPUpTo(int N){
    for(int i = 2; i <= N; i++){
      genDPFor(i);
    }
  }
  static void genDPFor(int N){
    long falseCount = 0;
    long trueCount = 0;
    long falsePCount = 0;
    long truePCount = 0;
    long falseORVCount = 0;
    long trueORVCount = 0;
    // case 1: !x
    falseCount += ExpressionsTruePCount[N-1];
    falseCount %= MOD;
    trueCount += ExpressionsFalsePCount[N-1];
    trueCount %= MOD;
    // note that !(x) also is parentheised
    falsePCount += ExpressionsTruePCount[N-1];
    falsePCount %= MOD;
    truePCount += ExpressionsFalsePCount[N-1];
    truePCount %= MOD;
    // case 2: (x)
    falseCount += ExpressionsFalseCount[N-2];
    falseCount %= MOD;
    falsePCount += ExpressionsFalseCount[N-2];
    falsePCount %= MOD;
    trueCount += ExpressionsTrueCount[N-2];
    trueCount %= MOD;
    truePCount += ExpressionsTrueCount[N-2];
    truePCount %= MOD;
    long dtrueCount = 0;
    long dfalseCount = 0;
    // case 3: (OR INVARIANT x)&(y), y must be parentheised to prevent repetition and make it work
    // for every way to split N:
    for(int xLen = 1; xLen <= (N - 2); xLen++){
      int yLen = N - xLen - 1;
      trueCount += (long)ExpressionsTrueORInvariantCount[xLen] * (long)ExpressionsTruePCount[yLen];
      trueCount %= MOD;
      falseCount += (long)ExpressionsFalseORInvariantCount[xLen] * (long)ExpressionsFalsePCount[yLen];
      falseCount %= MOD;
      falseCount += (long)ExpressionsFalseORInvariantCount[xLen] * (long)ExpressionsTruePCount[yLen];
      falseCount %= MOD;
      falseCount += (long)ExpressionsTrueORInvariantCount[xLen] * (long)ExpressionsFalsePCount[yLen];
      falseCount %= MOD;
    }
    dtrueCount = 0;
    dfalseCount = 0;
    // case 4: x|(OR INVARIANT y)
    for(int xLen = 1; xLen <= (N - 2); xLen++){
      int yLen = N - xLen - 1;
      dtrueCount += (long)ExpressionsTrueCount[xLen] * (long)ExpressionsTrueORInvariantCount[yLen];
      dtrueCount %= MOD;
      dfalseCount += (long)ExpressionsFalseCount[xLen] * (long)ExpressionsFalseORInvariantCount[yLen];
      dfalseCount %= MOD;
      dtrueCount += (long)ExpressionsFalseCount[xLen] * (long)ExpressionsTrueORInvariantCount[yLen];
      dtrueCount %= MOD;
      dtrueCount += (long)ExpressionsTrueCount[xLen] * (long)ExpressionsFalseORInvariantCount[yLen];
      dtrueCount %= MOD;
      trueCount += dtrueCount;
      falseCount += dfalseCount;
      trueORVCount += dtrueCount;
      falseORVCount += dfalseCount;
      trueCount %= MOD;
      falseCount %= MOD;
      trueORVCount %= MOD;
      falseORVCount %= MOD;
    }
    ExpressionsTrueCount[N] = (int)(trueCount % MOD);
    ExpressionsFalseCount[N] = (int)(falseCount % MOD);
    ExpressionsTruePCount[N] = (int)(truePCount % MOD);
    ExpressionsFalsePCount[N] = (int)(falsePCount % MOD);
    long trueORIVCount = trueCount - trueORVCount;
    trueORIVCount += MOD;
    trueORIVCount %= MOD;
    long falseORIVCount = falseCount - falseORVCount;
    falseORIVCount += MOD;
    falseORIVCount %= MOD;
    ExpressionsFalseORInvariantCount[N] = (int)falseORIVCount;
    ExpressionsTrueORInvariantCount[N] = (int)trueORIVCount;
  }
  public static void main(String[] args) throws IOException{
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    String temp = in.readLine();
    int T = Integer.parseInt(temp);
    int maxN = 0;
    int[] NCounts = new int[T];
    ExpressionsFalseCount[1] = 1;
    ExpressionsTrueCount[1] = 1;
    ExpressionsFalsePCount[1] = 1; // just 0 counts as parentheised
    ExpressionsTruePCount[1] = 1;
    ExpressionsFalseORInvariantCount[1] = 1;
    ExpressionsTrueORInvariantCount[1] = 1;
    for(int i = 0; i < T; i++){
      temp = in.readLine();
      int tempN = Integer.parseInt(temp);
      NCounts[i] = tempN;
      if(tempN > maxN){
        maxN = tempN;
      }
    }
    genDPUpTo(maxN);
    // DEBUG:
    System.out.println(Arrays.toString(ExpressionsTrueCount));
    System.out.println(Arrays.toString(ExpressionsFalseCount));
    System.out.println(Arrays.toString(ExpressionsTruePCount));
    System.out.println(Arrays.toString(ExpressionsFalsePCount));
    System.out.println(Arrays.toString(ExpressionsTrueORInvariantCount));
    System.out.println(Arrays.toString(ExpressionsFalseORInvariantCount));
    for(int i = 0; i < T; i++){
      System.out.println(ExpressionsTrueCount[NCounts[i]]);
    }
  }
}
