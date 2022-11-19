public class temp{
  public static void main(String[] args){
    double x = 1.5078621164278208;
    double y = -2.44457938628451;
    double z = 1.9294883005424643;
    double[][] planeEquations;
    planeEquations = new double[][]{{6.42,20, 20.69, 0.71}, {4, 5.1, 8, 9}, {6, 7, 10, 11.23}};
    for(int i = 0; i < 3; i++){
      System.out.println(planeEquations[i][0]*x + planeEquations[i][1]*y + planeEquations[i][2]*z - planeEquations[i][3]);
    }
    double[][] planeEquationsTwo;
    planeEquationsTwo = new double[][] {{6.3, 2.1, 9}, {0, 8.4, -1.75}};
    double a = 1.498015873015873;
    double b = -0.20833333333333331;
    for(int i = 0; i < 2; i++){
      System.out.println(planeEquationsTwo[i][0]*a + planeEquationsTwo[i][1]*b - planeEquationsTwo[i][2]);
    }
  }
}
