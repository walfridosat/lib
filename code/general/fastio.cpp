// Fast IO - leitura/escrita manual com buffer
static char ibuf[1 << 16]; static size_t ipos = 0, ilen = 0;
inline int gc() {
    if (ipos == ilen) { ilen = fread(ibuf, 1, sizeof ibuf, stdin); ipos = 0; if (!ilen) return -1; }
    return ibuf[ipos++];
}
inline ll readInt() {
    int c = gc(); while (c != '-' && (c < '0' || c > '9')) c = gc(); // pula lixo
    bool neg = false; if (c == '-') neg = true, c = gc();
    ll x = 0; while (c >= '0' && c <= '9') x = x * 10 + (c - '0'), c = gc();
    return neg ? -x : x;
}
inline string readStr() {
    int c = gc(); while (c != -1 && isspace(c)) c = gc();
    string s; while (c != -1 && !isspace(c)) s += (char)c, c = gc();
    return s;
}
static char obuf[1 << 16]; static size_t opos = 0;
inline void flushOut() { fwrite(obuf, 1, opos, stdout); opos = 0; }
inline void writeChar(char c) { if (opos == sizeof obuf) flushOut(); obuf[opos++] = c; }
inline void writeInt(ll x, char end = '\n') {
    if (x < 0) writeChar('-'), x = -x;      // cuidado: LLONG_MIN nao tratado
    char t[24]; int n = 0; do { t[n++] = '0' + x % 10; x /= 10; } while (x);
    while (n) writeChar(t[--n]);
    if (end) writeChar(end);
}
inline void writeStr(const string& s, char end = '\n') { for (char c : s) writeChar(c); if (end) writeChar(end); }
/*LATEX_DESC_BEGIN***************************
-> **Fast IO** - leitura por fread e escrita em buffer, mais rapido que cin.
Complexidade: O(tamanho da entrada/saida)
Uso: ll x = readInt(); string s = readStr(); writeInt(x); writeChar('\n'); flushOut();
* Sobre o codigo: gc() le de ibuf com fread; writeChar/flushOut escrevem em obuf.
* Problemas e reducoes: + entradas/saidas grandes (mais de 1e6 numeros); + TLE de cin/cout.
Cuidados: nao misturar com cin/scanf/printf; flushOut() antes de sair; em interativo use cin/cout; LLONG_MIN nao e tratado.
Catalogo: Quando nada funciona (TLE vs constante)
Digitacao: 26 linhas | facil.
*****************************LATEX_DESC_END*/
