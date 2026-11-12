// Simulated annealing e hill climbing - otimizacao por perturbacao aleatoria
mt19937_64 rngA(chrono::steady_clock::now().time_since_epoch().count());
double rnd01() { return (rngA() >> 11) * (1.0 / (1ULL << 53)); }

template<class S, class Score, class Mut, class Undo>
void anneal(S& s, Score score, Mut mutate, Undo undo, double T0, double T1, double tl) {
    auto t0 = chrono::steady_clock::now();
    auto el = [&]() { return chrono::duration<double>(chrono::steady_clock::now() - t0).count(); };
    double cur = score(s), best = cur; S bestS = s; double T = T0;
    for (long long it = 0;; it++) {
        if ((it & 255) == 0) {                       // checa tempo e atualiza T raramente
            double e = el(); if (e > tl) break;
            T = T0 * pow(T1 / T0, e / tl);           // decaimento geometrico T0 -> T1
        }
        mutate(s);
        double nw = score(s);
        if (nw >= cur || rnd01() < exp((nw - cur) / T)) {
            cur = nw;
            if (cur > best) best = cur, bestS = s;
        } else undo(s);
    }
    s = bestS;
}

// minimiza f(x,y) com passo que cai quando nao melhora
template<class F> pair<double, double> hillClimb2D(F f, double x, double y, double step, double tl) {
    auto t0 = chrono::steady_clock::now();
    double cur = f(x, y);
    while (chrono::duration<double>(chrono::steady_clock::now() - t0).count() < tl && step > 1e-12) {
        bool imp = false;
        for (int k = 0; k < 30; k++) {              // 30 tentativas aleatorias com o passo atual
            double ang = rnd01() * 2 * acos(-1.0), nx = x + step * cos(ang), ny = y + step * sin(ang);
            double v = f(nx, ny);
            if (v < cur) cur = v, x = nx, y = ny, imp = true;
        }
        if (!imp) step *= 0.5;
    }
    return {x, y};
}
/*LATEX_DESC_BEGIN***************************
-> **Simulated Annealing / Hill Climbing**
Recozimento simulado com temperatura geometrica e limite de tempo (maximiza score),
e hill climbing 2D em R^2 com passo decrescente (minimiza f).

Complexidade: itera enquanto houver tempo; O(1) por iteracao
Uso:
  anneal(s, score, mutate, undo, T0, T1, tl);  // score(s) double, maior melhor
  // mutate(s) aplica vizinho aleatorio; undo(s) desfaz o ultimo mutate
  pair<double,double> p = hillClimb2D(f, x0, y0, step0, tl);

* Sobre o codigo:
  anneal guarda a melhor solucao vista; aceita piora com probabilidade exp(delta/T).
  T cai geometricamente de T0 a T1 durante tl; checa o tempo a cada 256 iteracoes.
  hillClimb2D perturba em 30 direcoes por passo e corta step pela metade se nada melhora.

* Problemas e reducoes:
  + TSP: estado = permutacao das cidades; mutate faz 2-opt (troca duas arestas).
  + Atribuicao/particionamento: estado = vetor de escolhas; score = valor - penalidades.
  + Ponto de Fermat/minimax: hillClimb2D sobre a soma de distancias.

Cuidados: use rng xorshift rapido no laco interno; deixe ~10% de folga no tempo;
  T0 na escala dos deltas tipicos; varias reinicializacoes costumam ajudar.
Catalogo: Aleatorizacao (Simulated annealing, Hill climbing, Gradiente por perturbacao)
Digitacao: 36 linhas | media. Atalho: para score incremental, troque os lambdas por struct.
*****************************LATEX_DESC_END*/
