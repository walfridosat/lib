// Hash polinomial de string (prefix hash)
const ll MOD = 1e9 + 7; //WA? Muda o MOD e a base
const ll base = 153; 
// const ll MOD  = 131'807'699; -> Big Prime Number 
//const ll base = 127;         -> Random number larger than the Alphabet

const int MAXN = 1000005; // ajuste ao tamanho maximo das strings

ll expBase[MAXN];

void precalc(){
	expBase[0] = 1;
	for(int i=1; i<MAXN; i++) 
		expBase[i] = (expBase[i-1]*base)%MOD;
}

struct StringHash{
	vector<ll> hsh;

	StringHash(string &s){
		int n = (int)s.size();
		hsh = vector<ll>(n+1, 0);
		for(int i=0; i<n; i++)
			hsh[i+1] = ((hsh[i]*base) % MOD +s[i]) % MOD;
	}
	
	ll gethash(int l, int r){
		return (MOD + hsh[r+1] - (hsh[l]*expBase[r-l+1]) % MOD ) % MOD;
	}
};
/*LATEX_DESC_BEGIN***************************
-> **Hash polinomial de string (prefix hash)**
StringHash(s) monta o hash dos prefixos; gethash(l, r) devolve o hash da
substring s[l..r] inclusiva em O(1).

Complexidade: O(n) para construir, O(1) por consulta; precalc O(MAXN).
Uso:
  precalc(); // uma vez
  StringHash hs(s); ll h = hs.gethash(l, r); // l, r inclusivos
  Comparar substrings, buscar padrao, palindromos com hash reverso.

* Sobre o codigo:
  hsh[i+1] = hsh[i] * base + s[i] (mod MOD); expBase guarda as potencias de
  base. gethash remove o prefixo multiplicando por expBase[r-l+1].

* Problemas e reducoes:
  + Comparar substrings de mesmo tamanho em O(1).
  + Buscar padrao: compare o hash do padrao com janelas do texto.
  + LCP por busca binaria + hash (ou prefira suffix_array + RMQ).
  + Palindromos: hash da string e do reverso.

Cuidados: chame precalc() antes; MOD/base sao globais deste arquivo (nao
  redefina); use dois MODs/base aleatoria contra anti-hash; para LCP prefira
  SA + RMQ. 0-indexed.
Catalogo: Strings (hash).
Digitacao: 23 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/