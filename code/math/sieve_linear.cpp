// Crivo linear (menor fator primo, phi, mu, tau, sigma)
//
// O que faz: em O(N) calcula lp[i] (menor fator primo), lista de primos, phi, mu,
//   tau (numero de divisores) e sigma (soma dos divisores) de todo i <= N.
// Quando usar: Catalogo > Teoria dos numeros (crivo linear para multiplicativas;
//   fatorar muitos numeros <= 1e7 em O(log) com lp).
// Complexidade: O(N) tempo e memoria.
// Uso: sieve_lin(n) com n < NS; fatoracao de x: while(x>1){p=lp[x]; x/=p;}
//   Tudo 1-based (i=1: phi=mu=tau=sigma=1). Para 1e7 troque NS e apague
//   os arrays que nao usa (memoria!).
// Cuidados: sigma em ll (estoura para N muito grande); se so quer lp+primos,
//   apague phi/mu/tau/sigma. Nao confundir com sieve.cpp (crivo simples bool).
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
            // rs = v sem a potencia de lp[v]; tau/sigma multiplicativas
            tau[v] = tau[rs[v]] * (ex[v] + 1);
            sig[v] = sig[rs[v]] * pw[v];
        }
    }
}
