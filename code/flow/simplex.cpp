// Simplex (programacao linear) - estilo KACTL
//
// O que faz: maximiza c.x sujeito a A x <= b, x >= 0.
// Quando usar: LP pequeno (vars/restricoes ate ~100-300), jogos de soma zero, mistura,
//   dieta, max flow pequeno (Catalogo > Otimizacao: "Simplex", "Dualidade em LP",
//   "Jogo de soma zero"). Minimizar: passe -c e negue o resultado.
// Complexidade: exponencial pior caso, muito rapido na pratica. Regra de Bland-like
//   (desempate por indice) evita ciclar.
// Uso: LPSolver lp(A, b, c); vector<double> x; double v = lp.solve(x);
//   v = valor otimo (x recebe a solucao); v = -inf se inviavel; v = +inf se ilimitado.
//   Restricao >=: multiplique por -1. Igualdade: duas desigualdades. x livre: x = x+ - x-.
// Cuidados: double com eps=1e-8; b negativo e tratado (fase 1). Resposta inteira nao e
//   garantida (so se o LP for totalmente unimodular).
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
