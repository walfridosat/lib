#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
#define pb push_back
#define ppb pop_back
#define endl '\n'
#define all(a) (a).begin(), (a).end()
#define sz(a) ((a).size())
#define pii pair<ll, ll>
#define Merami_THE_ORAL_CIGARETTES_Mou_Ii_kai_RAIN_HD_NC_FC ios_base::sync_with_stdio(false)
#define keep_gambling cin.tie(NULL)
#define FORI(n) for(int i = 0; i < (n); i++)
#define FORJ(n) for(int j = 0; j < (n); j++)
#define SUM(a) accumulate(all(a),0LL) //novo pls beware
#define grid(n,m) vector<vector<ll>>((n), vector<ll>(m))
#define no "NO"
#define yes "YES"
#define iterate(tfg) for(auto it = (tfg).begin();it!=(tfg).end(); it++)
#define makepalao(n) vector<ll>palao(n); FORI(n)cin>>palao[i];
#define DEBUG_MSG(msg) do { \
    cout << "DEBUG: " << msg << std::endl; \
} while(0)
#define print(palao) do { \
    cout << endl; \
    FORI(palao.size()) cout << palao[i] << " "; \
    cout << endl; \
} while(0)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randomInt(int l, int r){return uniform_int_distribution<int>(l, r)(rng);}
vector<ll> permrandom(int n){vector<ll>perm(n);iota(all(perm),1);shuffle(all(perm),rng);return perm;}
vector<ll> arrayrandom(int n, int l = 1, int r = 1e9){vector<ll>arr(n);FORI(n)arr[i]=randomInt(l,r);return arr;}

ll n, m,q, i,j,x, y, z, soma, mj, mi, l,r,nr,u,v ,g, ans,le,ri,mid,op,aim,cost, bsize,nb; pii asd;
string s,s2;
ll a,b,c,d,e,f,h,k;
const ll MAXN = 2e5;
const ll MOD = 1e9+7;
const ll base = randomInt(27,1e3);

const ll max_n = 1e5;
const ll log2_n = 63;

ll rmq[max_n][log2_n];

void build(vector<ll>& a){
    for(ll i =0 ; i < n ;i++){
        rmq[i][0]=a[i];
    }
    for(ll j = 1; (1LL<<j)<=a.size(); j++){
        for(ll i = 0; (i+(1LL<<j)-1)<a.size(); i++){
            if(lookup[i][j-1]<lookup[i+(1<<(j-1))][j-1]){
                lookup[i][j] = lookup[i][j-1];
            }else{
                lookup[i][j] =lookup[i+(1<<(j-1))][j-1];
            }
        }
    }
}

ll query(ll l, ll r){ // 0 based
    ll j = (ll)log2(r-L+1);
    if(lookup[L][j]<=lookup[R-(1<<j)+1][j]){
        return lookup[L][j];
    }
    else{
        return lookup[R - (1 << j) + 1][j];
    }
}


void solve(int asd){
  

    cin>>n;
    vector<ll>a(n);
    for(int i = 0; i < n; i++){
        cin>>a[i];
        rmq[i][0]=a[i];
    }
    build(a);



    
}


int main() {
    Merami_THE_ORAL_CIGARETTES_Mou_Ii_kai_RAIN_HD_NC_FC; keep_gambling;
    //sieve();
    
    int t = 1;
    
    //cin>>t;
   
    
    //print(fib);
    

    
    while(t--){
        solve(t);
    }

    return 0;
}
  