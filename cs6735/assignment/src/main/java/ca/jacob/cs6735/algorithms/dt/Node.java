package ca.jacob.cs6735.algorithms.dt;

import java.lang.Math;
import java.util.Map;
import java.util.HashMap;
import java.util.logging.Logger;

public class Node {
  private static final Logger LOG = Logger.getLogger(Node.class.getName());

  private Double entropy;
  private Integer[][] x;
  private Integer[] y;
  private Node[] nodes;

  public Node(Integer[][] x, Integer[] y) {
    this.x = x;
    this.y = y;
  }

  /**
   * The method returns the entropy of the node
   * @return The entropy of the node
   */
  public Double entropy() {
    LOG.info("entropy - starting");
    if(this.entropy != null) return entropy;

    Map<Integer, Integer> classes = calculateOccurances(y);
    LOG.fine("there are " + classes.size() + " classes");

    entropy = 0.;
    for(Integer count : classes.values()){
      entropy -= count*log2(count);
    }
    LOG.fine("the entropy is " + entropy);

    return entropy;
  }

  public void split() {
    LOG.info("split - starting");
    int numOfAttributes = x[0].length;
    Double[] entropies = new Double[numOfAttributes];
    for(int i = 0; i < numOfAttributes; i++) {
      Map<Integer, Integer> splitInfo = calculateOccurances(x[i]);
    }


  }

  private Double log2(int value) {
    return Math.log(value) / Math.log(2);
  }

  private Map<Integer, Integer> calculateOccurances(Integer[] values) {
    Map<Integer, Integer> map = new HashMap<Integer, Integer>();
    for(Integer value : values) {
      Integer count = map.get(value);
      if(count == null) {
        count = 0;
      } else {
        count++;
      }
      map.replace(value, count);
    }
    return map;
  }
}
