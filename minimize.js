const minimize = (M) => {
  const n = M.length;
  const m = n === 0 ? 0 : M[0].length;
  const best = Infinity;
  for (let j = 1; j <= m; j++) {
    M[1, j] = taxi[airport, j] + night[1,j];
  }

  for (let k = 2; k <= n; k++) {
    for (let j = 1; j <= m; j++) {
      for (let i = 2; i <= m; i++) {
        if (M[k][j] > M[k - 1][i] + taxi[i][j] + night[k][j]) {
          M[k][j] = M[k - 1][i] + taxi[i][j] + night[k][j];
        }
      }
    }
  }

  for (let j = 1; j <= m; j++) {
    if (best > M[n][j] + taxi[j][airport]) {
      best
    }
  }
}