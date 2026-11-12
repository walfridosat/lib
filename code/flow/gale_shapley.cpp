// Gale-Shapley - casamento estavel
vector<int> galeShapley(const vector<vector<int>>& pm, const vector<vector<int>>& pw) {
    int n = pm.size();
    vector<vector<int>> rk(n, vector<int>(n)); // rk[j][i] = posicao do homem i para a mulher j
    for (int j = 0; j < n; j++) for (int k = 0; k < n; k++) rk[j][pw[j][k]] = k;
    vector<int> nxt(n, 0), wife(n, -1), husb(n, -1); queue<int> q;
    for (int i = 0; i < n; i++) q.push(i);
    while (!q.empty()) {
        int m = q.front(); q.pop();
        int w = pm[m][nxt[m]++];
        if (husb[w] < 0) husb[w] = m, wife[m] = w;
        else if (rk[w][m] < rk[w][husb[w]]) { // ela prefere m: o antigo volta a fila
            int old = husb[w]; wife[old] = -1; q.push(old);
            husb[w] = m; wife[m] = w;
        } else q.push(m);
    }
    return wife;
}
/*LATEX_DESC_BEGIN***************************
-> **Gale-Shapley - casamento estavel**
n homens e n mulheres com listas de preferencia completas; devolve o casamento
estavel otimo para quem propoe. 0-indexed.

Complexidade: O(n^2).
Uso:
  auto w = galeShapley(pm, pw);
  pm[i] = mulheres de i por preferencia (melhor primeiro);
  pw[j] = homens de j por preferencia; w[i] = mulher casada com o homem i.

* Sobre o codigo:
  rk[j][i] guarda a posicao do homem i na lista da mulher j. Uma fila de homens
  livres: cada um propoe a proxima mulher; se ela esta livre aceita, senao
  troca se preferir o novo e o antigo volta a fila. Cada par e proposto no
  maximo uma vez.

* Problemas e reducoes:
  + Casamento estavel completo: n homens, n mulheres, listas completas;
    arestas = pares possiveis, ordem = preferencia; resposta w[].
  + Hospitais/residentes com capacidade: clone cada hospital em c vagas com a
    mesma lista; residentes escolhem vagas.
  + Escolas/alunos com cotas: mesma clonagem de cada escola em c slots.
  + Otimo para quem propoe: cada homem recebe a melhor parceira entre todos os
    casamentos estaveis.
  + Pessimo para quem recebe: cada mulher recebe o pior parceiro estavel.
  + Rode com os lados trocados (pm = pw e pw = pm) para obter o otimo das
    mulheres.
  + Preferencias com empates: desempate arbitrariamente; o resultado e
    fracamente estavel nas preferencias originais.
  + Verificacao: dado w[], confira que nao existe par (i, j) que se prefira
    mutuamente a seus pares atuais (nenhum blocking pair).

Cuidados: listas completas e do mesmo tamanho n. Capacidade > 1: clone o
  hospital em varias vagas com a mesma lista. 0-indexed.
Catalogo: Grafos (emparelhamento, casamento estavel).
Digitacao: 17 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
