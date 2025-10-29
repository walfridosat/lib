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
