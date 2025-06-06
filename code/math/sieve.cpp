// Sieve
//
// 
// 
// 1e6
// 
// 

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