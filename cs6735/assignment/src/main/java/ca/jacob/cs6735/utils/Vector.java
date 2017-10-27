package ca.jacob.cs6735.utils;

public class Vector {
    private Integer[] values;

    public Vector(Integer[] values) {
        this.values = values;
    }

    public Vector() {
        this.values = new Integer[0];
    }

    public void push(Integer value) {
        Integer[] tmp = new Integer[values.length+1];
        System.arraycopy(values, 0, tmp, 0, values.length);
        values = tmp;
    }

    public Integer at(int i) {
        return values[i];
    }
}
