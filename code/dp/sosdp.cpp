#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define int long long
#define endl '\n'

#define pii pair<ll,ll>
#define pb push_back

const ll MAXN = 21;
ll F[1<<MAXN]; //guarda a resposta pra uma submask
ll dp[MAXN][1<<MAXN];

ll gen_submask(int b , int curmask) {
    if(b < 0) {
        return F[curmask];
    }

    if(dp[b][curmask] != -1) return dp[b][curmask];

    ll ans = 0;
    if(curmask&(1ll << b)) {  
        ans += gen_submask(b-1 , curmask); //transicao pra o bit ligado
        ans += gen_submask(b-1 , curmask ^ (1ll << b)); //transicao pra o bit desligado
    }
    else {
        ans += gen_submask(b-1 , curmask); //transicao pra o bit desligado
    }
    return dp[b][curmask] = ans;
}

