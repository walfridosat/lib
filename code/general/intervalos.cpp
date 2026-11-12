// Intervalos: sweep de eventos, salas, furar, cobrir, k maquinas
//
// O que faz: maxima sobreposicao (com tratamento de empates), atribuicao de salas, minimo de pontos para furar todos,
//            minimo de intervalos para cobrir [0, L], max disjuntos, k maquinas (maximo atendido).
// Quando usar: "quantos ao mesmo tempo", "minimo de salas", "cobrir segmento", "escolher max intervalos".
//              Catalogo > Arrays e guloso (Intervalos, Empates em sweep, Cobrir [0,L], k maquinas)
// Complexidade: O(n log n)
// Uso: intervalos como pair<ll,ll> (l, r). closed=true: [l, r] fechado (abertura antes do fechamento no mesmo ponto);
//      closed=false: [l, r) (fechamento antes).
//      maxOverlap(iv, closed); assignRooms(iv) -> sala de cada intervalo (0-based) e numero de salas (semi-aberto/fechado: closed);
//      maxDisjoint(iv) (fechados, tocar nas pontas conta como sobrepor); minPoints(iv) -> pontos que furam todos;
//      coverMin(iv, L) -> minimo de intervalos que cobrem [0, L] (-1 se impossivel);
//      kMachines(iv, k) -> maximo de intervalos atendidos (semi-abertos [l, r)).
// Cuidados: errar o empate muda a resposta em 1; coverMin trabalha com reais discretos: cobre [0, L] se alcanca >= L.
int maxOverlap(const vector<pair<ll, ll>>& iv, bool closed) {
    vector<pair<ll, int>> ev;
    for (auto& [l, r] : iv) {
        ev.push_back({l, closed ? 0 : 1});   // tipo: menor processa primeiro; fechado: +1 (0) antes de -1 (1)
        ev.push_back({r, closed ? 1 : 0});   // semi-aberto: -1 (0) antes de +1 (1)
    }
    sort(ev.begin(), ev.end());
    int cur = 0, best = 0;
    for (auto& [x, t] : ev) {
        bool open = closed ? (t == 0) : (t == 1);
        cur += open ? 1 : -1; best = max(best, cur);
    }
    return best;
}
// retorna {numero de salas, sala[i]}; reaproveita sala cujo fim < inicio (fechado) ou <= inicio (semi-aberto)
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
// maximo de intervalos fechados dois a dois disjuntos: ordena por fim
int maxDisjoint(vector<pair<ll, ll>> iv) {
    sort(iv.begin(), iv.end(), [](auto& a, auto& b) { return a.second < b.second; });
    int c = 0; ll last = LLONG_MIN;
    for (auto& [l, r] : iv) if (l > last) c++, last = r;
    return c;
}
// minimo de pontos que furam todos os intervalos fechados; devolve os pontos
vector<ll> minPoints(vector<pair<ll, ll>> iv) {
    sort(iv.begin(), iv.end(), [](auto& a, auto& b) { return a.second < b.second; });
    vector<ll> pts; ll last = LLONG_MIN;
    for (auto& [l, r] : iv) if (l > last) pts.push_back(r), last = r;   // ponto no fim do primeiro nao furado
    return pts;
}
// minimo de intervalos [l, r] cuja uniao cobre o segmento [0, L] (continuo); -1 se impossivel
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
// k maquinas, intervalos semi-abertos [l, r): maximo atendido. Ordena por fim; usa a maquina livre com maior fim <= l.
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
