const ll MOD = 1e9 + 7; //WA? Muda o MOD e a base
const ll base = 153; 
// const ll MOD  = 131'807'699; -> Big Prime Number 
//const ll base = 127;         -> Random number larger than the Alphabet

ll expBase[MAXN];

void precalc(){
	expBase[0] = 1;
	for(int i=1; i<MAXN; i++) 
		expBase[i] = (expBase[i-1]*base)%MOD;
}

struct StringHash{
	vector<ll> hsh;

	StringHash(string &s){
		hsh = vector<ll>(s.size()+1, 0);
		for(int i=0; i<s.size(); i++)
			hsh[i+1] = ((hsh[i]*base) % MOD +s[i]) % MOD;
	}
	
	ll gethash(int l, int r){
		return (MOD + hsh[r+1] - (hsh[l]*expBase[r-l+1]) % MOD ) % MOD;
	}
};