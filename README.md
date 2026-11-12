# Biblioteca de snippets para ICPC

Coleção de trechos de C++17 para maratona de programação, organizada por assunto e com
documentação de quando usar cada técnica.

## Como usar

1. Cole `code/general/template.cpp` no início do arquivo (includes, macros e `main`).
2. Cole o trecho desejado logo abaixo: cada `.cpp` é um fragmento, sem `#include` nem `main`.
3. Para os 9 arquivos de combinatória que dizem `// Requer:`, cole antes
   `code/combinatorics/binom_mod.cpp`.
4. Alguns arquivos são standalone (têm `main` ou `#include` próprio): `general/template.cpp`,
   `general/gen_exemplo.cpp`, `general/interativo.cpp`, `general/rng.cpp`,
   `general/buscaternaria.cpp`, `dp/frog3_cht.cpp`, `ds/ordered_set.cpp`,
   `general/hash_anti.cpp`.

## Onde está o quê

| Arquivo | Conteúdo |
|---|---|
| `docs/lib-index.md` | Índice dos 206 trechos: nome, descrição, seção do catálogo e status |
| `docs/catalogo-completo.md` | Catálogo de técnicas e fórmulas (23 seções) |
| `docs/mapa-rapido.md` | Gatilho → técnica, em uma linha por salto |
| `docs/frequencias-cf.md` | Técnicas mais frequentes em A–D de CF Div. 2/3/4 (351 problemas), por letra e divisão |
| `docs/PLANO_LIB.md` | Convenções, como testar, correções aplicadas e o que falta |
| `docs/AUDITORIA-2026-11-11.md` | Auditoria dos documentos e do código, com achados e status |
| `docs/catalogo.pdf` | Versão impressa do mapa + catálogo + índice |

## Pastas

- `code/algebra`: FFT/NTT, séries formais, Berlekamp–Massey, Lagrange.
- `code/combinatorics`: binomiais, Burnside, Catalan, LGV, partições, árvores rotuladas.
- `code/dp`: mochilas, LIS/LCS, digit DP, intervalo, DAG, otimizações (CHT, D&C, Knuth).
- `code/ds`: BITs, segtrees, sparse tables, DSUs, heaps, CHT, wavelet, treap.
- `code/flow`: matching, fluxo, cortes, custo mínimo, matroides, simplex.
- `code/general`: template, guloso, interativos, compressão, stress test.
- `code/geometry`: primitivas, hull, calipers, círculos, sweep, 3D.
- `code/graph`: BFS/DFS, Dijkstra, SCC, 2-SAT, MST, Euler, árvore de Kruskal.
- `code/math`: crivo, fatoração, CRT, BSGS, floor sum, Miller–Rabin/Pollard.
- `code/string`: hash, KMP/Z, Aho–Corasick, SA/SAM, Manacher, eertree, trie.
- `code/tree`: LCA, HLD, centroide, virtual tree (em construção).

Pastas `code/bits`, `code/games` e `code/primitives` ainda estão vazias; o conteúdo
planejado está nos lotes 1 e 2 de `docs/PLANO_LIB.md`.

## Gerar o PDF

```bash
python docs/build_pdf.py
```

Precisa de `python -m pip install markdown` e Chrome/Edge instalado.

## Status (2026-11-11)

- 206 trechos `.cpp`; todos compilam com `g++ -std=c++17 -O2 -Wall -fsyntax-only` usando
  o prelude do template (0 falhas).
- Testes com brute force/casos conhecidos: LCS bit-parallel, sparse table, subset sum,
  digit DP, trie, LIS, mochila, moedas e frog; e mais 20 arquivos (Dinic, MCMF, Hungarian,
  Hopcroft-Karp, HLD, LCA, SA, SAM, segtree lazy, treap, Li Chao, SCC, 2-SAT, NTT, Pollard,
  Manacher, KMP, Z, wavelet, segtree persistente) contra brute force em milhares de casos.
- Catálogo corrigido e indexado; PDF regerado.
