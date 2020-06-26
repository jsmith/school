/**
 * Input: "73 -> 67 -> 65 -> 91 -> 98 -> 122 -> 124 -> 153 -> 183 -> 37 -> 21 -> 14"
 * Output: 295
 */
const count = (s) => {
  const l = s.split(" -> ").map((v) => parseInt(v));
  return l.map((_, i) => i === 0 ? 0 : Math.abs(l[i - 1] - l[i])).reduce((a, v) => a + v);
}

let test = (l, c) => {
  const s = new Set(l);
  const result = []
  while (s.size !== 0) {
    let min = null;
    for (const v of s) {
      if (min === null || Math.abs(v - c) < Math.abs(min - c)) {
        min = v;
      }
    }

    if (min === null) {
      throw Error("DLSJDKLDJFLJk")
    }

    c = min;
    s.delete(min);
    result.push(min);
  }

  return result.join(" -> ");
}