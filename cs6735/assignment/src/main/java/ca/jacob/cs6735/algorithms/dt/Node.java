package ca.jacob.cs6735.algorithms.dt;

import ca.jacob.cs6735.utils.Matrix;
import ca.jacob.cs6735.utils.Vector;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.*;

import static ca.jacob.cs6735.utils.Matrix.calculateOccurances;
import static ca.jacob.cs6735.utils.Matrix.log2;

public class Node {
  private static final Logger LOG = LoggerFactory.getLogger(Node.class);

  private Double entropy;
  private Matrix x;
  private Vector y;
  private ArrayList<Node> nodes;

  public Node(Integer[][] x, Integer[] y) {
    this.x = new Matrix(x);
    this.y = new Vector(y);
    this.initNodes();
  }

  public void initNodes() {
    this.nodes = new ArrayList<Node>();
  }

  public Double entropy() {
    LOG.info("entropy - starting");
    if(this.entropy != null) return entropy;

    Map<Integer, Integer> classes = calculateOccurances(y);
    LOG.debug("there are {} classes", classes.size());

    double sum = 0;
    for(Integer count : classes.values()) {
      sum += count;
    }
    LOG.debug("sum is " + sum);

    entropy = 0.;
    for(Integer count : classes.values()){
      entropy -= count/sum*log2(count/sum);
    }
    LOG.debug("the entropy is {}", entropy);

    return entropy;
  }

  public void split() {
    LOG.info("split - starting");
    int numOfAttributes = x.colCount();

    for(int j = 0; j < numOfAttributes; j++) {
      Map<Integer, Map<Matrix, Vector>>  split = new HashMap<Integer, Map<Matrix, Vector>>();
      for(int i = 0; j < x.rowCount(); j++) {
        Integer value = x.at(i, j);

        Map<Matrix, Vector> entry = split.get(value);
        if(entry == null) {
          entry = new HashMap<Matrix, Vector>();
          split.put(value, entry);
        }

        Vector v = entry.get(x.row(i));
        if(v == null) {
          Matrix mat = new Matrix();
          v = new Vector();
          mat.pushRow(x.row(i));
          entry.put(mat, v);
        }
        v.push(y.at(i));
      }
    }
  }




}
