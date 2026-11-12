// IO de __int128 - ler, imprimir e converter
typedef __int128 lll;
string to_str128(lll x) {
    if (x == 0) return "0";
    bool neg = x < 0; if (neg) x = -x;
    string s; while (x > 0) s += char('0' + (int)(x % 10)), x /= 10;
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    return s;
}
lll read128() {
    string s; cin >> s; lll x = 0; bool neg = false;
    for (char c : s) { if (c == '-') neg = true; else x = x * 10 + (c - '0'); }
    return neg ? -x : x;
}
void print128(lll x) { cout << to_str128(x); }
/*LATEX_DESC_BEGIN***************************
-> **IO de __int128** - le e imprime __int128, que cin/cout nao suportam.
Complexidade: O(digitos)
Uso: lll x = read128(); print128(x); cout << to_str128(x);
* Sobre o codigo: to_str128 converte por % 10; read128 le string e acumula.
* Problemas e reducoes: + multiplicar dois ll (1e18) sem overflow; + imprimir o produto.
Cuidados: sem std::abs/to_string; mod com __int128 e lento (~30-60 ns).
Catalogo: Arrays e guloso (cuidado com overflow), Quando nada funciona (Overflow)
Digitacao: 15 linhas | facil.
*****************************LATEX_DESC_END*/
