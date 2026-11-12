// Intervalos - sweep, salas, furar, cobrir, k maquinas
int maxOverlap(const vector<pair<ll, ll>>& iv, bool closed) {
    vector<pair<ll, int>> ev;
    for (auto& [l, r] : iv) {
        ev.push_back({l, closed ? 0 : 1});   // fechado: abre (0) antes de fecha (1)
        ev.push_back({r, closed ? 1 : 0});   // semi-aberto: fecha (0) antes de abre (1)
    }
    sort(ev.begin(), ev.end());
    int cur = 0, best = 0;
    for (auto& [x, t] : ev) {
        bool open = closed ? (t == 0) : (t == 1);
        cur += open ? 1 : -1; best = max(best, cur);
    }
    return best;
}
// {salas, sala[i]}; reaproveita sala livre
pair<int, vector<int>> assignRooms(const vector<pair<ll, ll>>& iv, bool closed = true) {
    int n = iv.size(); vector<int> ord(n), room(n); iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return iv[a] < iv[b]; });
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;   // (fim, sala)
    int cnt = 0;
    for (int i : ord) {
        if (!pq.empty() && (closed ? pq.top().first < iv[i].first : pq.top().first <= iv[i].first)) {
            room[i] = pq.top().second; pq.pop();
        } else room[i] = cnt++;
        pq.push({iv[i].second, room[i]});
    }
    return {cnt, room};
}
// maximo de intervalos disjuntos: ordena por fim
int maxDisjoint(vector<pair<ll, ll>> iv) {
    sort(iv.begin(), iv.end(), [](auto& a, auto& b) { return a.second < b.second; });
    int c = 0; ll last = LLONG_MIN;
    for (auto& [l, r] : iv) if (l > last) c++, last = r;
    return c;
}
// pontos que furam todos os intervalos
vector<ll> minPoints(vector<pair<ll, ll>> iv) {
    sort(iv.begin(), iv.end(), [](auto& a, auto& b) { return a.second < b.second; });
    vector<ll> pts; ll last = LLONG_MIN;
    for (auto& [l, r] : iv) if (l > last) pts.push_back(r), last = r;   // ponto no fim do primeiro nao furado
    return pts;
}
// min intervalos que cobrem [0, L]; -1 se impossivel
int coverMin(vector<pair<ll, ll>> iv, ll L) {
    sort(iv.begin(), iv.end());
    ll reach = 0; int cnt = 0; size_t i = 0;
    while (reach < L) {
        ll best = reach;
        while (i < iv.size() && iv[i].first <= reach) best = max(best, iv[i].second), i++;
        if (best == reach) return -1;      // nenhum avanca
        reach = best; cnt++;
    }
    return cnt;
}
// k maquinas [l,r): usa a livre de maior fim <= l
int kMachines(vector<pair<ll, ll>> iv, int k) {
    sort(iv.begin(), iv.end(), [](auto& a, auto& b) { return a.second < b.second; });
    multiset<ll> m; for (int i = 0; i < k; i++) m.insert(LLONG_MIN);   // fim atual de cada maquina
    int c = 0;
    for (auto& [l, r] : iv) {
        auto it = m.upper_bound(l);          // primeiro com fim > l
        if (it == m.begin()) continue;       // nenhuma livre
        m.erase(prev(it)); m.insert(r); c++;
    }
    return c;
}
/*LATEX_DESC_BEGIN***************************
-> **Intervalos**
Sweep de eventos com empates; salas; min pontos para furar todos; min intervalos
para cobrir [0, L]; max disjuntos; k maquinas. Intervalos (l, r).

Complexidade: O(n log n) cada
Uso:
  int mo = maxOverlap(iv, closed);        // closed = [l,r], senao [l,r)
  auto [k, room] = assignRooms(iv, closed);
  int md = maxDisjoint(iv);
  vector<ll> pts = minPoints(iv);
  int c = coverMin(iv, L);                // -1 se impossivel
  int km = kMachines(iv, k);              // semi-aberto [l,r)

* Sobre o codigo:
  maxOverlap ordena eventos e usa o tipo para desempatar abertura e fechamento.
  assignRooms usa heap de fins e reaproveita sala livre.
  maxDisjoint/minPoints ordenam por fim e avancam gulosamente.
  coverMin varre os intervalos que comecam ate reach e estende o alcance.
  kMachines usa multiset com o fim atual de cada maquina.

* Problemas e reducoes:
  + Maximo simultaneo / minimo de salas: maxOverlap e assignRooms.
  + Furar todos os intervalos com o minimo de pontos: minPoints.
  + Cobrir [0, L] com o minimo de intervalos: coverMin.
  + Escolher o maximo de intervalos disjuntos: maxDisjoint.
  + Atender o maximo de intervalos com k maquinas: kMachines.

Cuidados: errar o empate muda a resposta em 1; coverMin trata reais discretos
  e cobre [0, L] se alcanca >= L.
Catalogo: Arrays e guloso (Intervalos, Empates em sweep, Cobrir [0,L], k maquinas)
Digitacao: 66 linhas | media.
*****************************LATEX_DESC_END*/
