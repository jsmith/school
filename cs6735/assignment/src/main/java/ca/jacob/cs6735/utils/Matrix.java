package ca.jacob.cs6735.utils;

public class Matrix {
  private Integer[][] values;

  public Matrix(Integer[][] values) {
    this.values = values;
  }

  public Integer[] row(int i) {
    return values[i];
  }

  public Integer[] col(int j) {
    Integer[] col = new Integer[values.length];
    for(int i = 0; i < values.length; i++) {
      col[i] = values[i][j];
    }
    return col;
  }
}
