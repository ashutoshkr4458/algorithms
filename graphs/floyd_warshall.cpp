for (int i = 1; i <= n; i++) {
  for (int j = 1; j <= n; j++) {
    if (i == j) dist[i][j] = 0;
    else if (adj[i][j]) dist[i][j] = adj[i][j];
    else dist[i][j] = INF;
  }
}

for (int k = 1; k <= n; k++) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
    }
  }
}
