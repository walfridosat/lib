// Simulated annealing e hill climbing
//
// O que faz: template de recozimento simulado (maximizar score) com T geometrico e limite de tempo;
//            hill climbing continuo em R^2 com passo decrescente (ponto que minimiza uma funcao).
// Quando usar: "maximize a pontuacao" sem solucao exata, TL 2-10s; geometria continua (Fermat, minimax).
//              Catalogo > Aleatorizacao (Simulated annealing, Hill climbing, Gradiente por perturbacao)
// Complexidade: iteracoes enquanto houver tempo
// Uso: anneal(state, score, mutate, undo, T0, T1, tl): score(state)->double (maior melhor),
//      mutate(state)->void aplica vizinho aleatorio, undo(state)->void desfaz o ultimo mutate.
//      Para delta barato, calcule o score incremental dentro de mutate/undo (troque os lambdas por struct).
//      hillClimb2D(f, x0, y0, step0, tl): minimiza f(x, y).
// Cuidados: usar xorshift/rng rapido no laco interno; deixar ~10% de folga no tempo; T0 na escala dos deltas tipicos
//           (aceita pior com prob exp(delta/T)); funciona melhor com varias reinicializacoes.
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

// minimiza f(x, y) em R^2 por perturbacao com passo que cai pela metade quando nao melhora
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
