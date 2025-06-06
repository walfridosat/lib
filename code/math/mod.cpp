// Aritmetica modular
//
// 
// 
// 
// 
// 

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

ll mod_add(ll a, ll b) {
    return (a % MOD + b % MOD) % MOD;
}

ll mod_sub(ll a, ll b) {
    return ((a % MOD - b % MOD) + MOD) % MOD;
}

ll mod_mul(ll a, ll b) {
    return (a % MOD * b % MOD) % MOD;
}

ll fexp(ll b, ll p){
	ll ans = 1;

	while(p){
		if(p&1) ans = (ans*b) % MOD;
		b = b * b % MOD;
		p >>= 1;
	}

	return ans % MOD;
}

ll mod_inv(ll a) {
    return fexp(a, MOD - 2);
}