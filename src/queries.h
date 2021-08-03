#include "data.h"

void query1 (RTree* rtree) {
  cout << "Consulta 1: " << '\n';
  vector<int> ans;
  rtree->same_neighborhood(ans);
  cout << ans.size() << '\n';
   //for (auto e : ans)
    //cout << e << '\n';
}

/* ¿Cuáles son los barrios con mayor cantidad 
    de viajes? Retornar los top 5. (Considerando 
    apenas las coordenadas de partida). */

void query2(RTree* rtree, int n) {
    cout << "Consulta 2: " << '\n';
    vector <pair<int, string>> ans;
    bool exists = rtree->top_pickup(n, ans);
    if (!exists) cout << "No hay esa cantidad de datos.";
    int en = n > ans.size() ? ans.size() : n;
    for (int i = 0; i < en; i++)
      cout << i << ": " << ans[i].second << ", " << ans[i].first << '\n';
}

void query3(RTree* rtree, Point p1, Point p2){
  cout << "Consulta 3: " << '\n';
  int ans = rtree->search_range_neigh(p1, p2);
  cout << ans << '\n';
}