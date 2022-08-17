import java.util.Scanner;
public class Q1151B{
  public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    int n, m, temp;
    n = in.nextInt();
    m = in.nextInt();
    int[][] a = new int[n][m];
    int XOR_counter = 0;
    int hasDiffRow = -1;
    int hasDiffCol = -1;
    boolean tempDiffCounter = false;
    int tempDiffVal = -1;
    for(int i = 0; i < n; i++){
      if(hasDiffRow == -1){
        tempDiffCounter = false;
      }
      for(int j = 0; j < m; j++){
        temp = in.nextInt();
        a[i][j] = temp;
        if(j == 0){
          XOR_counter ^= temp;
          tempDiffVal = temp;
        } else if (!tempDiffCounter) {
          if(tempDiffVal != temp){
            tempDiffCounter = true;
            hasDiffRow = i;
            hasDiffCol = j;
          }
        }
      }
    }
    if(XOR_counter != 0){
      System.out.println("TAK");
      for(int i = 0; i < n; i++){
        System.out.print("1");
        if(i != (n-1)){
          System.out.print(" ");
        }
      }
      return;
    }
    if(hasDiffRow == -1){
      System.out.println("NIE");
      return;
    }
    System.out.println("TAK");
    for(int i = 0; i < n; i++){
      if(i != 0){
        System.out.print(" ");
      }
      if(i == hasDiffRow){
        System.out.print(hasDiffCol + 1);
      } else {
        System.out.print("1");
      }
    }
  }
}
