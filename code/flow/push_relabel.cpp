// Push-relabel (highest label + gap) - fluxo maximo
struct PushRelabel {
    struct Edge { int dest, back; ll f, c; };
    vector<vector<Edge>> g; vector<ll> ec; vector<Edge*> cur;
    vector<vector<int>> hs; vector<int> H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}
    void addEdge(int s, int t, ll cap, ll rcap = 0) {
        if (s == t) return;
        g[s].push_back({t, (int)g[t].size(), 0, cap});
        g[t].push_back({s, (int)g[s].size() - 1, 0, rcap});
    }
    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = g.size(); H[s] = v; ec[t] = 1;
        vector<int> co(2 * v); co[0] = v - 1;
        for (int i = 0; i < v; i++) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);
        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0) // descarrega u
                if (cur[u] == g[u].data() + g[u].size()) {
                    H[u] = 1e9; // relabel
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest] + 1)
                        H[u] = H[e.dest] + 1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v) // gap
                        for (int i = 0; i < v; i++) if (hi < H[i] && H[i] < v)
                            --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= (int)g.size(); }
};
/*LATEX_DESC_BEGIN***************************
-> **Push-relabel (highest label + gap)**
Fluxo maximo s -> t; alternativa ao Dinic em grafos densos ou com
capacidades grandes. 0-indexed.

Complexidade: O(V^2 sqrt E) pior caso; muito rapido na pratica.
Uso:
  PushRelabel pr(n); pr.addEdge(u, v, cap[, rcap]); ll f = pr.calc(s, t);
  pr.leftOfMinCut(v) -> v esta do lado de s no corte minimo (apos calc).

* Sobre o codigo:
  Cada vertice guarda excesso ec[] e altura H[]. Inicializa saturando as
  arestas de s; o vertice ativo de maior altura empurra fluxo para baixo
  (altura do destino + 1) ou e relabelado. O gap (co[H[u]] == 0) sobe para
  V + 1 os vertices inalcancaveis, acelerando o fim.

* Problemas e reducoes:
  + Fluxo maximo / corte minimo: s, t, capacidades; resposta = calc(); lado
    S = leftOfMinCut.
  + Caminhos disjuntos em arestas (Menger): cap 1 em cada aresta; fluxo =
    numero de caminhos.
  + Caminhos disjuntos em vertices: split v_in -> v_out cap 1; arestas
    originais cap INF; fluxo = numero de caminhos.
  + Remover o minimo de vertices para desconectar s de t: split com cap 1
    (ou custo do vertice) e arestas originais INF; o corte da o custo.
  + Project selection / closure: s -> projeto (lucro), maquina -> t (custo),
    dependencia INF; resposta = soma dos lucros - fluxo.
  + Segmentacao binaria: s -> i cap a_i, i -> t cap b_i, i <-> j cap p_ij;
    corte minimo = custo da melhor separacao (A = lado de s).
  + Escolha em cadeia (x_i em 1..k, |x_i - x_j| <= d): cadeia de vertices
    por variavel, arestas INF para tras e INF entre cadeias deslocadas de d;
    cortar a aresta do valor paga o custo.
  + Grid: minimo de celulas bloqueadas para separar dois pontos: split de
    cada celula com cap 1, vizinhos com INF.
  + Densest subgraph: com m = numero de arestas e g fixo, s -> v cap m,
    v -> t cap m + 2g - deg(v), arestas cap 1 nos dois sentidos; o corte do
    lado S vale m*n + 2(g|S| - e(S)), entao compare com m*n e binaria em g.
  + Baseball elimination: s -> jogo cap jogos restantes, jogo -> os 2 times,
    time -> t cap w_max - w_time; eliminado se o fluxo nao satura s.
  + Atribuicao com capacidades: s -> pessoa cap c_p, pessoa -> tarefa cap 1,
    tarefa -> t cap d_t; fluxo = pares.
  + Matching bipartido: s -> L cap 1, L -> R cap 1, R -> t cap 1.
  + Corte minimo global de grafo nao direcionado: fixe s e teste todos os t
    (ou use Gomory-Hu para todos os pares).
  + Minimo de arestas a remover para tornar o grafo desconexo: corte global.

Cuidados: baseado no KACTL. Chamar calc uma unica vez por objeto. Soma de
  varios INF pode estourar ll. 0-indexed.
Catalogo: Grafos (fluxo).
Digitacao: 40 linhas | dificil. Atalho: ok (implementacao ja compacta);
  leftOfMinCut poderia ser escrito como H[a] >= n.
*****************************LATEX_DESC_END*/
