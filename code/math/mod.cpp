// Aritmetica modular e utilidades de inteiros
//
// O que faz: gcd, lcm, soma/subtracao/multiplicacao mod MOD, exponenciacao e inverso
//            modular (quando o restante do arquivo define); constantes locais.
// Quando usar: Catalogo > Teoria dos numeros e divisores (aritmetica modular).
//            Para binomiais use code/combinatorics/binom_mod.cpp.
// Complexidade: O(log) por exponenciacao/inverso; O(1) nas demais.
// Uso: ajuste MOD (primo) no topo; mod_add/mod_sub/mod_mul, fexp(b, p), mod_inv(a).
// Cuidados: MOD e local deste arquivo (nao redefina em outro trecho colado junto);
//            para multiplicacao de dois ll use __int128 quando MOD ~ 1e9.


const ll MOD = 1000000007; // primo; ajuste conforme o problema

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