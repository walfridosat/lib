// Template base - includes, macros, solve e main
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FORI(n) for(ll i = 0; i < (n); i++)
#define FORJ(n) for(ll j = 0; j < (n); j++)
#define endl '\n'
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define pii pair<ll, ll>

void solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    int t = 1;
    while(t--){
        solve();
    }

    return 0;
}
/*LATEX_DESC_BEGIN***************************
-> **Template Base**
Includes, macros (FORI, FORJ, endl, pb, all, pii), solve() vazio e main com fast IO
e um laco de T casos (T = 1 por padrao).

Complexidade: O(1)
Uso:
  cole este arquivo e escreva o corpo em solve();
  descomente cin >> t para T casos.

* Sobre o codigo:
  endl e '\n' (sem flush), entao em interativos use '\n' << flush.

* Problemas e reducoes:
  + Prelude de todos os trechos e ponto de partida quando travar.

Cuidados: evite nomes que colidam com as macros (all, pii) em funcoes da biblioteca.
Catalogo: Como usar quando travar
Digitacao: 19 linhas | facil.
*****************************LATEX_DESC_END*/
