// Crivo linear (multiplicativas)
const int NS = 1000001;
int lp[NS], phi[NS], mu[NS], tau[NS], ex[NS], rs[NS];
ll sig[NS], pw[NS];
vector<int> pr;
void sieve_lin(int n) {
    phi[1] = mu[1] = tau[1] = 1; sig[1] = 1; rs[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!lp[i]) { // i primo
            lp[i] = i; pr.push_back(i);
            phi[i] = i - 1; mu[i] = -1; tau[i] = 2; ex[i] = 1;
            pw[i] = 1 + i; sig[i] = 1 + i; rs[i] = 1;
        }
        for (int p : pr) {
            ll v = (ll)i * p;
            if (p > lp[i] || v > n) break;
            lp[v] = p;
            if (i % p == 0) { // p ja divide i
                phi[v] = phi[i] * p; mu[v] = 0;
                ex[v] = ex[i] + 1; pw[v] = pw[i] * p + 1; rs[v] = rs[i];
            } else {
                phi[v] = phi[i] * (p - 1); mu[v] = -mu[i];
                ex[v] = 1; pw[v] = 1 + p; rs[v] = i;
            }
            // rs = v sem a potencia de lp[v]
            tau[v] = tau[rs[v]] * (ex[v] + 1);
            sig[v] = sig[rs[v]] * pw[v];
        }
    }
}
/*LATEX_DESC_BEGIN***************************
-> **Crivo linear (multiplicativas)**
Em O(N) calcula lp, primos, phi, mu, tau e sigma de todo i <= N.

Complexidade: O(N) tempo e memoria.
Uso:
  sieve_lin(n);                 // n < NS
  while (x > 1) { int p = lp[x]; x /= p; }   // fatorar em O(log)

* Sobre o codigo:
  Cada composto v = i*p e marcado uma vez, com p <= lp[i]. Quando p divide i,
  phi, mu, tau e sigma sao atualizados pelas formulas multiplicativas; rs[v]
  guarda v sem a potencia de lp[v].

* Problemas e reducoes:
  + Fatorar muitos numeros <= 1e7 -> lp.
  + Somatorio de phi/mu/tau/sigma ate N -> arrays prontos.
  + Contar coprimos e mobius para inclusao-exclusao -> phi/mu.
  + Numero de divisores de todos os i -> tau.
  + Soma dos divisores de todos os i -> sig.
  + Base para convolucoes de Dirichlet -> phi, mu.

Cuidados: sigma em ll (estoura para N muito grande); se so quer lp e primos,
  apague phi/mu/tau/sigma; nao confundir com sieve.cpp (crivo simples bool).
Catalogo: Teoria dos numeros.
Digitacao: 29 linhas | media. Atalho: manter so lp/pr e gerar as outras tabelas sob demanda.
*****************************LATEX_DESC_END*/
