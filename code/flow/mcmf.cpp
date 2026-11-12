// Min-cost max-flow - Dijkstra com potenciais
struct MCMF {
    struct E { int to; ll cap, cost; };
    int n; vector<E> e; vector<vector<int>> g; vector<ll> pot, dist; vector<int> pe;
    vector<ll> costs; // custo marginal por unidade enviada (limitado a 4e6 entradas)
    MCMF(int n) : n(n), g(n) {}
    int add(int u, int v, ll cap, ll cost) {
        e.push_back({v, cap, cost}); g[u].push_back(e.size() - 1);
        e.push_back({u, 0, -cost}); g[v].push_back(e.size() - 1);
        return e.size() - 2;
    }
    pair<ll, ll> run(int s, int t, ll lim = LLONG_MAX) {
        const ll INF = LLONG_MAX / 4;
        // Bellman-Ford para potenciais iniciais (so arestas com cap>0)
        pot.assign(n, INF); pot[s] = 0;
        for (int it = 0; it < n; it++) {
            bool ch = false;
            for (int u = 0; u < n; u++) if (pot[u] < INF)
                for (int id : g[u]) if (e[id].cap > 0 && pot[u] + e[id].cost < pot[e[id].to])
                    pot[e[id].to] = pot[u] + e[id].cost, ch = true;
            if (!ch) break;
        }
        for (int u = 0; u < n; u++) if (pot[u] >= INF) pot[u] = 0; // inalcancaveis
        ll F = 0, C = 0;
        while (F < lim) {
            dist.assign(n, INF); pe.assign(n, -1); dist[s] = 0;
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d > dist[u]) continue;
                for (int id : g[u]) if (e[id].cap > 0) {
                    int v = e[id].to; ll nd = d + e[id].cost + pot[u] - pot[v];
                    if (nd < dist[v]) dist[v] = nd, pe[v] = id, pq.push({nd, v});
                }
            }
            if (dist[t] >= INF) break;
            for (int u = 0; u < n; u++) if (dist[u] < INF) pot[u] += dist[u];
            ll f = lim - F;
            for (int v = t; v != s; v = e[pe[v] ^ 1].to) f = min(f, e[pe[v]].cap);
            for (int v = t; v != s; v = e[pe[v] ^ 1].to) e[pe[v]].cap -= f, e[pe[v] ^ 1].cap += f;
            ll pc = pot[t] - pot[s]; // custo real do caminho (por unidade)
            F += f; C += f * pc;
            for (ll i = 0; i < f && costs.size() < 4000000; i++) costs.push_back(pc);
        }
        return {F, C};
    }
    ll flowOn(int id) { return e[id ^ 1].cap; } // fluxo na aresta direta id
};
/*LATEX_DESC_BEGIN***************************
-> **Min-cost max-flow (Dijkstra + potenciais)**
Fluxo de custo minimo de s a t, com limite opcional de fluxo. Custos
negativos ok desde que nao exista ciclo negativo. 0-indexed.

Complexidade: O(F E log V) (F = augmentacoes); Bellman-Ford inicial O(VE).
Uso:
  MCMF m(n); m.add(u, v, cap, cost); auto [f, c] = m.run(s, t[, maxflow]);
  m.costs -> custo marginal de cada augmentacao (nao-decrescente).
  Fluxo exato k: run(s, t, k) e confira f == k.
  Min cost de fluxo qualquer: pare quando o custo marginal for >= 0.

* Sobre o codigo:
  Potenciais pot[] tornam os custos reduzidos nao-negativos; Bellman-Ford
  acha pot inicial (so arestas com cap > 0) e depois cada Dijkstra acha o
  caminho mais barato no residual. O caminho e saturado, pot atualizado e o
  custo real (pot[t] - pot[s]) entra em costs[]. A convexidade vem dai.

* Problemas e reducoes:
  + Min-cost max-flow: s e t, arestas com cap e cost; resposta (F, C).
  + Fluxo de custo minimo de valor exato k: run(s, t, k); confira f == k.
  + Custo minimo para qualquer quantidade: rode sem limite e pare quando o
    marginal for >= 0 (ou use lim = 1 e olhe costs[]).
  + Atribuicao n x n de custo minimo: s -> linha cap 1, linha -> coluna
    custo, coluna -> t cap 1; fluxo n e custo minimo.
  + k caminhos disjuntos de custo total minimo: arestas com cap 1, MCMF com
    fluxo k; o custo e a soma dos k caminhos.
  + Custo convexo por quantidade: arestas paralelas cap 1 com custos
    f(1)-f(0), f(2)-f(1), ...; o fluxo escolhe as mais baratas primeiro.
  + Maximizar lucro: cost = -lucro; se o fluxo nao precisa ser maximo, pare
    quando o marginal ficar >= 0.
  + Intervalos ponderados com ate k sobrepostos: linha i -> i+1 cap k custo
    0; intervalo [l, r) vira l -> r cap 1 custo -w.
  + Transporte: s -> fornecedor cap oferta, fornecedor -> cliente custo c,
    cliente -> t cap demanda.
  + Carteiro chines dirigido / tornar euleriano com custo minimo: equilibre
    os graus com MCMF (custo = distancia).
  + Atribuicao com capacidades: s -> p cap c_p, p -> tarefa cap 1, tarefa ->
    t cap d_t; fluxo = pares.
  + Matching bipartido de peso maximo: cost = -peso nas arestas; aumente
    enquanto o custo do caminho for < 0.
  + k caminhos com capacidades e custos por aresta: fluxo k nas arestas
    originais com cap e cost.
  + Fluxo com limites inferiores e custo: reduza como em
    flow_lower_bounds.cpp e rode MCMF no grafo reduzido.

Cuidados: custos negativos exigem ausencia de ciclo negativo no grafo
  inicial (Bellman-Ford). cost*flow usa ll. 0-indexed.
Catalogo: Grafos, Otimizacao (min-cost flow, fluxo com custos convexos).
Digitacao: 48 linhas | media. Atalho: o Bellman-Ford inicial pode ser omitido
  se todos os custos forem >= 0; costs[] poderia ser opcional.
*****************************LATEX_DESC_END*/
