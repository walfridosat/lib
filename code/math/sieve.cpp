// Crivo de Eratostenes


const int MAXN = 1000000; // ajuste ao limite do problema

vector<bool> is_prime(MAXN + 1, true);
vector<ll> primes;

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}
/*LATEX_DESC_BEGIN***************************
-> **Crivo de Eratostenes**
Marca is_prime[0..MAXN] e guarda todos os primos em primes.

Complexidade: O(MAXN log log MAXN) tempo; O(MAXN) memoria.
Uso:
  sieve();
  if (is_prime[x]) ...; for (ll p : primes) ...;

* Sobre o codigo:
  Para cada i ainda primo, marca os multiplos a partir de i*i. vector<bool>
  ocupa ~8 MB para 1e6.

* Problemas e reducoes:
  + Listar primos ate 1e6/1e7 -> sieve.
  + Testar primalidade de varios numeros pequenos -> is_prime[x].
  + Fatorar varios numeros por divisao sobre primes -> sieve + loop.
  + Contar primos em um intervalo pequeno -> sieve.
  + Gerar primos para o crivo segmentado -> sieve.

Cuidados: MAXN e local deste arquivo (nao redefina ao colar junto); o crivo
  roda uma vez por execucao; para 1e7 use bitset/char e cuidado com memoria.
Catalogo: Teoria dos numeros e divisores.
Digitacao: 14 linhas | facil.
*****************************LATEX_DESC_END*/
