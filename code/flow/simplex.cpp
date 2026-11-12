// Simplex - programacao linear (max c.x sujeito a A x <= b, x >= 0)
typedef double SXT;
typedef vector<double> vd;
typedef vector<vd> vvd;
const SXT SX_EPS = 1e-8, SX_INF = 1 / .0;
#define ltj(X) if (s == -1 || make_pair(X[j], N[j]) < make_pair(X[s], N[s])) s = j
struct LPSolver {
    int m, n; vector<int> N, B; vvd D;
    LPSolver(const vvd& A, const vd& b, const vd& c) :
        m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
        for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
        N[n] = -1; D[m + 1][n] = 1;
    }
    void pivot(int r, int s) {
        SXT *a = D[r].data(), inv = 1 / a[s];
        for (int i = 0; i < m + 2; i++) if (i != r && fabs(D[i][s]) > SX_EPS) {
            SXT *b = D[i].data(), inv2 = b[s] * inv;
            for (int j = 0; j < n + 2; j++) b[j] -= a[j] * inv2;
            b[s] = a[s] * inv2;
        }
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv; swap(B[r], N[s]);
    }
    bool simplex(int phase) {
        int x = m + phase - 1;
        for (;;) {
            int s = -1;
            for (int j = 0; j <= n; j++) if (N[j] != -phase) ltj(D[x]);
            if (D[x][s] >= -SX_EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] <= SX_EPS) continue;
                if (r == -1 || make_pair(D[i][n + 1] / D[i][s], B[i]) <
                               make_pair(D[r][n + 1] / D[r][s], B[r])) r = i;
            }
            if (r == -1) return false; // ilimitado
            pivot(r, s);
        }
    }
    SXT solve(vd &x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] < -SX_EPS) { // fase 1: acha base viavel
            pivot(r, n);
            if (!simplex(2) || D[m + 1][n + 1] < -SX_EPS) return -SX_INF;
            for (int i = 0; i < m; i++) if (B[i] == -1) {
                int s = 0;
                for (int j = 1; j <= n; j++) ltj(D[i]);
                pivot(i, s);
            }
        }
        bool ok = simplex(1); x = vd(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return ok ? D[m][n + 1] : SX_INF;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Simplex - programacao linear**
Maximiza c.x sujeito a A x <= b, x >= 0 (double). Tambem resolve o dual,
jogos de soma zero e LP pequeno.

Complexidade: exponencial no pior caso, muito rapido na pratica; desempate
por indice (Bland-like) evita ciclar.
Uso:
  LPSolver lp(A, b, c); vector<double> x; double v = lp.solve(x);
  v = valor otimo (x = solucao); -inf se inviavel; +inf se ilimitado.
  Minimizar: passe -c e negue o resultado.
  >=: multiplique a restricao por -1. Igualdade: duas desigualdades.
  x livre: x = x+ - x- com x+, x- >= 0.

* Sobre o codigo:
  Tableau D com base B e nao-base N. A fase 1 acha uma base viavel se algum
  b[i] < 0 (pivot com a variavel artificial). Depois simplex(1) pivota
  escolhendo a coluna de custo reduzido negativo e a linha pela razao
  minima. solve() le x das variaveis basicas.

* Problemas e reducoes:
  + LP em forma padrao max c.x, A x <= b, x >= 0: base.
  + Minimizacao: use -c e negue o valor; restricoes >=: multiplique por -1.
  + Igualdades: duas desigualdades (<= e >=).
  + Variavel livre: x = x+ - x-.
  + Jogo de soma zero: maximize v com sum_i p_i A_ij >= v e sum p_i = 1,
    p >= 0; o valor do jogo e v e a estrategia e p.
  + Fluxo maximo como LP: variaveis = fluxo por aresta, restricoes de cap e
    conservacao; maximize o fluxo que sai de s.
  + Min-cost flow como LP: minimize sum cost_e f_e com conservacao e caps.
  + Atribuicao como LP: x_ij >= 0, sum_j x_ij = 1, sum_i x_ij <= 1; a
    matriz e totalmente unimodular, entao a solucao e inteira.
  + Minimax / Chebyshev: minimize t com -t <= a_i.x - b_i <= t.
  + Dieta/mistura: minimize custo com restricoes nutricionais >=.
  + Cobertura por vertices (relaxacao): minimize sum x_v com x_u + x_v >= 1
    por aresta.
  + Resolver o dual: as variaveis duais sao os precos-sombra das restricoes.

Cuidados: double com eps = 1e-8; b negativo e tratado na fase 1. A resposta
  inteira so e garantida se o LP for totalmente unimodular. Restricoes
  lineares apenas.
Catalogo: Otimizacao (simplex, dualidade em LP, jogo de soma zero).
Digitacao: 58 linhas | dificil. Atalho: ok (tableau compacto).
*****************************LATEX_DESC_END*/
