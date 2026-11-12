// Hungarian - atribuicao de custo minimo
ll hungarian(const vector<vector<ll>>& a, vector<int>& ans) {
    int n = a.size(), m = a[0].size(); const ll INF = LLONG_MAX / 4;
    vector<ll> u(n + 1), v(m + 1); vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; i++) {
        p[0] = i; int j0 = 0;
        vector<ll> minv(m + 1, INF); vector<char> used(m + 1, false);
        do {
            used[j0] = true; int i0 = p[j0], j1 = 0; ll delta = INF;
            for (int j = 1; j <= m; j++) if (!used[j]) {
                ll cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                if (minv[j] < delta) delta = minv[j], j1 = j;
            }
            for (int j = 0; j <= m; j++)
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do { int j1 = way[j0]; p[j0] = p[j1]; j0 = j1; } while (j0);
    }
    ans.assign(n, -1);
    for (int j = 1; j <= m; j++) if (p[j]) ans[p[j] - 1] = j - 1;
    return -v[0];
}
/*LATEX_DESC_BEGIN***************************
-> **Hungarian - atribuicao de custo minimo**
Matriz de custos n x m (n <= m); atribui cada linha a uma coluna distinta
minimizando o custo total. Devolve a coluna de cada linha e o valor otimo.
0-indexed.

Complexidade: O(n^2 m).
Uso:
  ll c = hungarian(a, ans); // a n x m (vector<vector<ll>>); ans[i] = coluna
  Maximizar: passe -a. Pares proibidos: custo INF (ex. 1e12) e confira
  c < INF. Exige n <= m (transponha se preciso).

* Sobre o codigo:
  Potenciais u[] (linhas) e v[] (colunas) e matching p[j] por coluna. Para
  cada linha i, Dijkstra na rede de custos reduzidos a[i0-1][j-1] - u[i0] -
  v[j], achando o caminho alternante minimo; way[] guarda o caminho para
  atualizar p[]. O valor otimo e -v[0].

* Problemas e reducoes:
  + Atribuicao de custo minimo n x n: linhas = pessoas, colunas = tarefas,
    a[i][j] = custo; ans[i] = tarefa de i; resposta = c.
  + Atribuicao com lucro: passe -a e negue o resultado; resposta = maior
    lucro total.
  + Pares proibidos / viabilidade: a[i][j] = INF; se c >= INF nao ha
    atribuicao viavel.
  + n <= m (mais tarefas que pessoas): cada linha escolhe uma coluna; as
    colunas nao usadas ficam livres.
  + Matching de peso maximo nao perfeito: acrescente colunas dummy de custo
    0 (n <= m) e maximize com -a; dummy = linha sem par.
  + Atribuicao com capacidades: clone cada pessoa c_p vezes e cada tarefa
    d_t vezes, replicando custos; resolva e agrupe os clones.
  + Transporte unitario (cada cliente recebe 1): linhas = oferta, colunas =
    demanda, custo por unidade; leia ans[i].
  + Par (i, j) forcado: remova a linha i e a coluna j, some a[i][j] ao custo
    do restante.
  + Verificar um custo: compare c com a soma de qualquer outra atribuicao.

Cuidados: exige n <= m (transponha). Custos negativos ok. Para k pares
  exatos use mcmf com k augmentacoes. Use ll e INF grande sem estourar.
  A matriz deve ter ao menos uma coluna.
Catalogo: Grafos (matching maximo ponderado), Otimizacao (problema de
  atribuicao).
Digitacao: 24 linhas | dificil. Atalho: ok (o algoritmo ja e compacto).
*****************************LATEX_DESC_END*/
