// Aritmetica modular basica


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
/*LATEX_DESC_BEGIN***************************
-> **Aritmetica modular basica**
gcd, lcm, soma/subtracao/multiplicacao mod MOD, exponenciacao e inverso.

Complexidade: O(log) em fexp/mod_inv; O(1) nas demais.
Uso:
  ll g = gcd(a, b), l = lcm(a, b);
  ll s = mod_add(a, b), d = mod_sub(a, b), p = mod_mul(a, b);
  ll e = fexp(b, p), iv = mod_inv(a);

* Sobre o codigo:
  Versoes simples com MOD constante; fexp e exponenciacao binaria e mod_inv
  usa Fermat (MOD primo).

* Problemas e reducoes:
  + Aritmetica basica mod primo -> funcoes diretas.
  + Inverso modular de a mod primo -> mod_inv.
  + Reduzir expressoes longas mod MOD -> mod_add/mod_sub/mod_mul.
  + lcm sem overflow -> dividir antes de multiplicar.

Cuidados: MOD e local deste arquivo (nao redefina ao colar junto); para
  multiplicar dois ll com MOD ~1e9 use __int128.
Catalogo: Teoria dos numeros e divisores.
Digitacao: 28 linhas | facil. Atalho: mod_add/mod_sub/mod_mul cabem em uma linha cada.
*****************************LATEX_DESC_END*/
