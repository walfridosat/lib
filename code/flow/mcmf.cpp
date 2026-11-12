// Min-cost max-flow (Dijkstra com potenciais; custos negativos ok se sem ciclo negativo)
//
// O que faz: fluxo de custo minimo de s a t, com limite opcional de fluxo.
// Quando usar: atribuicao, k caminhos disjuntos de custo minimo, escalonamento de intervalos
//   em k maquinas, custo convexo (arestas paralelas), transporte (Catalogo > Grafos,
//   Otimizacao > "Min-cost flow", "Fluxo com custos convexos").
// Complexidade: O(F * E log V) (F = numero de augmentacoes); Bellman-Ford inicial O(VE).
// Uso: MCMF m(n); m.add(u,v,cap,cost); auto [f,c]=m.run(s,t[,maxflow]);
//   m.costs = custo marginal de cada augmentacao (um por caminho, repetido f vezes); e
//   nao-decrescente: custo como funcao do fluxo e convexo (resposta para todo k).
//   Para min-cost de fluxo EXATO k: run(s,t,k) e confira f==k.
// Cuidados: custos negativos: o Bellman-Ford inicial exige ausencia de ciclo negativo.
//   Para min cost de fluxo qualquer: pare quando o custo marginal passar a ser >= 0
//   (use lim=1 repetido, ou olhe costs[]). cost*flow usa ll. 0-indexed.
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
