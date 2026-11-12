// Crivo de Eratostenes
//
// O que faz: marca is_prime[0..MAXN] e guarda todos os primos em primes.
// Quando usar: Catalogo > Teoria dos numeros e divisores (crivo). Para fatoracao
//            multipla use o menor fator (crivo linear); para 10^9+ use Miller-Rabin.
// Complexidade: O(MAXN log log MAXN) tempo e O(MAXN) memoria.
// Uso: sieve(); depois consulte is_prime[x] ou itere primes.
// Cuidados: MAXN e local deste arquivo (nao redefina ao colar junto); o crivo roda
//            uma vez por execucao; 1e6 ~ 8 MB com vector<bool>.


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