// Frog 3 com CHT (exemplo completo, standalone)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<ll, ll>
#define pb push_back
//#define endl '\n'

class cht{
public:
    vector<pii>points;
    vector<pii>linhas;
    
    double inter(pii a, pii b){
        return ((double)b.second-(double)a.second)/((double)a.first-(double)b.first);
    }
    
    void add(pii point){
        while(linhas.size()>=2){
            ll n = linhas.size();
            double inter1 = inter(linhas[n-2], linhas[n-1]);
            double inter2 = inter(linhas[n-1], point);
            if(inter1>=inter2)linhas.pop_back();
            else break;
        }
        linhas.pb(point);

    }

    cht(vector<pii>& pontos){
        points = (pontos);
        sort(points.begin(), points.end());
        for(auto ponto : points)add(ponto);
    }

    ll query(ll x){
        if(linhas.size() == 1)return linhas[0].first*x + linhas[0].second;
        ll l = 0, r = (ll)linhas.size()-2;
        ll ans = (ll)linhas.size()-1;
        while(l<=r){
            ll mid = (l+r)/2;
            if(x<inter(linhas[mid],linhas[mid+1])){
                r = mid-1;
                ans = mid;
            }else{
                l = mid+1;
            }
        }
        return linhas[ans].first*x + linhas[ans].second;
    }


};

void solve() {
    
   
    ll n; ll c;
    cin>>n>>c;
    vector<ll>h(n);
    for(auto& x : h)cin>>x;

    vector<ll>dp(n);
    vector<pii>what;
    cht thawan(what);
    dp[1]=0;
    pii ponto_at = {-2*h[0],h[0]*h[0]};

    thawan.add(ponto_at);
    for(int i = 1; i < n; i++){
        dp[i] = c + h[i]*h[i] + thawan.query(h[i]);
        ponto_at = {-2*h[i],dp[i] + h[i]*h[i]};
        thawan.add(ponto_at);
    }

    cout<<dp[n-1]<<endl;

}
    


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll T=1;
    //cin >> T;
    while(T--)solve();
    //cout<<"clash royale"<<endl;
}
/*LATEX_DESC_BEGIN***************************
-> **Frog 3 com convex hull trick (exemplo standalone)**
Resolve dp[i] = c + h[i]^2 + min_j (dp[j] + h[j]^2 - 2*h[i]*h[j]) com CHT.
Programa completo: le n, c e h[0..n-1] e imprime dp[n-1], 0-based.

Complexidade: O(n log n) (insercao O(1) amortizado, consulta binaria).
Uso:
  programa completo; a classe cht tambem pode ser copiada:
  cht hull(vazio); hull.add({m, b}); ll y = hull.query(x);

* Sobre o codigo:
  Cada candidato j vira a reta y = (-2*h[j])*x + (dp[j] + h[j]^2); a query em
  x = h[i] devolve o minimo. inter(a,b) e o x onde duas retas se cruzam;
  add remove retas que nunca serao otimas. query faz busca binaria nas quebras.

* Problemas e reducoes:
  + DP de sapo com custo quadratico (Frog 3).
  + Qualquer dp[i] = min_j (a[j]*x[i] + b[j]) com x monotono ou consulta binaria.
  + Minimizar soma de custos lineares em sequencia.

Cuidados: e standalone (tem main). Inclinacoes sao inseridas em ordem, mas a
  query usa busca binaria, entao tambem funciona fora de ordem. Use ll.
Catalogo: DP (CHT / Li Chao) como exemplo de montagem.
Digitacao: 68 linhas | dificil. Atalho: para o trecho reutilizavel use
  code/ds/cht_monotono.cpp ou code/ds/lichao.cpp.
*****************************LATEX_DESC_END*/
