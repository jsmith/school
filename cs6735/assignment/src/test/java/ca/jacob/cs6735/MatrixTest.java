package ca.jacob.cs6735;

import ca.jacob.cs6735.utils.Matrix;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertArrayEquals;

public class MatrixTest {
    private ca.jacob.cs6735.utils.Matrix matrix;

    @Before
    public void setup() {
        matrix = new ca.jacob.cs6735.utils.Matrix(new Integer[][]{{1, 2, 3}, {1, 2, 3}});
    }

    @Test
    public void testRow() {
        assertArrayEquals(new Integer[]{1, 2, 3}, matrix.row(0));
    }

    @Test
    public void testCol() {
        assertArrayEquals(new Integer[]{2, 2}, matrix.col(1));
    }
}
