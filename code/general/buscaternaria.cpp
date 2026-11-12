// Busca ternaria - minimo de funcao convexa/unimodal em [l, r]
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

ll func(ll x){
    return 2*x*x - 4*x + 2;
}

ld tern_double(ld l, ld r) {
    for(int it=250; it--;){
        ld m1 = l + (r-l)/3, m2 = r - (r-l)/3;
        ld f1 = func(m1), f2 = func(m2);
        if(f1 < f2) r = m2;
        else l = m1;
    }
    //retorna o x que minimiza a funcao
    return l;
}

ll tern_int(ll l, ll r){

    while(r-l>3){
        //ATENCAO
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        if(func(m1)<func(m2)){
            r=m2;
        } else {
            l=m1;
        }
    }

    ll ans = LLONG_MAX;
    for (int i = l; i <= r; i++) {
        ans = min(ans, func(i));
    }

    //retorna o f(x) minimizado
    return ans;
} 
    
/*LATEX_DESC_BEGIN***************************
-> **Busca Ternaria**
tern_double(l, r) devolve o x que minimiza func (convexa/unimodal) em [l, r];
tern_int(l, r) devolve o menor f(x) inteiro. Intervalos fechados.

Complexidade: O(250) no double; O(log(range)) no inteiro
Uso:
  troque func(x) pela sua funcao
  ld x = tern_double(l, r);  // x minimizador
  ll v = tern_int(l, r);     // f(x) minimizado

* Sobre o codigo:
  Compara os pontos m1 e m2 que dividem o intervalo em tres e descarta o lado pior.
  No inteiro, para quando r - l <= 3 e testa todos os candidatos.

* Problemas e reducoes:
  + Minimizar funcao convexa ou unimodal sem derivada.
  + Achar o pico/maximo: use -func(x) ou inverta a comparacao.

Cuidados: so vale se a funcao for convexa/unimodal no intervalo; em empates o
  inteiro pode devolver qualquer minimizador; use long double para precisao.
Catalogo: Busca binaria e otimizacao (Busca ternaria)
Digitacao: 35 linhas | facil. Atalho: tern_int so precisa do laco ate r-l<=3 e do min final.
*****************************LATEX_DESC_END*/
