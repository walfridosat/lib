# Frequências v2 (vocabulário fixo)

Reclassificação manual dos 351 registros (A–D de Div. 2/3/4, 90 contests) num vocabulário fixo de 28 técnicas alinhado às seções do catálogo. Substitui as 43 "famílias" de `frequencias.md`, cujo campo `tecnica` era texto livre (347 valores distintos em 351). Cada problema recebe UMA técnica principal, a que destrava o problema. Dados em `catalogo/editoriais/classificacao.jsonl` (regenere com `python reclassifica.py` naquela pasta).

**Como ler:** a amostra é pequena (cerca de 85 problemas por letra). Diferenças de 1–2 pontos percentuais são ruído; confie na ordem do topo, não em células isoladas.

## Ranking geral

| # | Técnica | Total | % | A | B | C | D | Seção do catálogo |
|---:|---|---:|---:|---:|---:|---:|---:|---|
| 1 | Simulação / implementação direta | 30 | 9% | 20 | 5 | 3 | 2 | — |
| 2 | Guloso (local, mais restrito primeiro, da esquerda) | 23 | 7% | 2 | 5 | 13 | 3 | Arrays e guloso |
| 3 | Só as frequências importam / multiconjunto | 22 | 6% | 4 | 9 | 5 | 4 | Arrays e guloso |
| 4 | Prefixos / diferenças / sufixos | 21 | 6% | — | 5 | 7 | 9 | Arrays e guloso |
| 5 | Extremo decide (máx/mín, pontas, caso extremo) | 18 | 5% | 8 | 7 | 2 | 1 | Reformulações universais (Caso extremo) |
| 6 | Paridade / classes mod 2 | 18 | 5% | 6 | 5 | 3 | 4 | Reformulações universais (Invariante) |
| 7 | Fórmula fechada / telescopia / conta direta | 17 | 5% | 8 | 3 | 4 | 2 | Matemática de olimpíada |
| 8 | Resto, divisibilidade, gcd/lcm | 17 | 5% | 4 | 6 | 7 | — | Teoria dos números e divisores |
| 9 | Bits, xor, potências de 2, bit mais alto | 16 | 5% | 2 | 1 | 5 | 8 | Bits e XOR |
| 10 | Resposta pequena / poucos candidatos / casos | 16 | 5% | 7 | 4 | 3 | 2 | Construtivos e interativos |
| 11 | Construção (padrão, blocos, identidade) | 15 | 4% | 3 | 7 | 1 | 4 | Construtivos e interativos |
| 12 | Run-length / blocos de iguais | 12 | 3% | 1 | 6 | 2 | 3 | Strings, Arrays e guloso |
| 13 | Invariante ou monovariante (soma, mod k, posição relativa) | 12 | 3% | 6 | — | 1 | 5 | Reformulações universais |
| 14 | Grade / geometria | 11 | 3% | — | 3 | 5 | 3 | Geometria |
| 15 | Pombal / cota que a construção atinge | 11 | 3% | 5 | 4 | 1 | 1 | Construtivos e interativos |
| 16 | DP | 10 | 3% | — | 1 | 5 | 4 | DP |
| 17 | Primos e fatoração | 9 | 3% | 2 | 1 | 3 | 3 | Teoria dos números e divisores |
| 18 | Jogos | 9 | 3% | 4 | 3 | 1 | 1 | Teoria dos jogos |
| 19 | Grafos e árvores | 9 | 3% | — | 1 | 2 | 6 | Grafos, Árvores |
| 20 | Trás pra frente / última operação / desfazer | 8 | 2% | 3 | — | 4 | 1 | Reformulações universais (Inverta o tempo) |
| 21 | Ordenar + varredura / two pointers | 8 | 2% | — | 2 | 2 | 4 | Arrays e guloso |
| 22 | Exchange argument / mediana / convexidade | 8 | 2% | 3 | 2 | 1 | 2 | Arrays e guloso |
| 23 | Estrutura simples (pilha, heap, segtree) | 7 | 2% | — | 2 | 1 | 4 | Estruturas de dados e queries |
| 24 | Período, ciclo, estabiliza | 6 | 2% | — | 5 | — | 1 | Cadeias de pulos |
| 25 | Strings (palíndromo, subsequência, espelho) | 5 | 1% | 1 | 2 | 1 | 1 | Strings |
| 26 | Busca binária / ternária na resposta | 5 | 1% | — | — | 3 | 2 | Busca binária e otimização |
| 27 | Interativo / comunicação | 4 | 1% | — | 1 | 1 | 2 | Construtivos e interativos |
| 28 | Contagem / contribuição | 4 | 1% | — | 1 | 2 | 1 | Combinatória, contagem e probabilidade |

## O que tentar primeiro, por letra

Top 6 de cada letra, em % dos problemas daquela letra. É a ordem em que vale testar as ideias quando travar.

| Letra | 1º | 2º | 3º | 4º | 5º | 6º |
|---|---|---|---|---|---|---|
| A (89) | Simulação 22% | Extremo decide 9% | Fórmula fechada 9% | Resposta pequena 8% | Invariante ou monovariante 7% | Paridade 7% |
| B (91) | Só as frequências importam 10% | Extremo decide 8% | Construção 8% | Run-length 7% | Resto, divisibilidade, gcd/lcm 7% | Paridade 5% |
| C (88) | Guloso 15% | Prefixos 8% | Resto, divisibilidade, gcd/lcm 8% | Grade 6% | Só as frequências importam 6% | Bits, xor, potências de 2, bit mais alto 6% |
| D (83) | Prefixos 11% | Bits, xor, potências de 2, bit mais alto 10% | Grafos e árvores 7% | Invariante ou monovariante 6% | Só as frequências importam 5% | Ordenar + varredura 5% |

## Por divisão

| Técnica | Div 4 | Div 3 | Div 2 |
|---|---:|---:|---:|
| Simulação / implementação direta | 24% | 4% | 1% |
| Guloso (local, mais restrito primeiro, da esquerda) | 7% | 8% | 5% |
| Só as frequências importam / multiconjunto | 11% | 7% | 3% |
| Prefixos / diferenças / sufixos | 3% | 8% | 7% |
| Extremo decide (máx/mín, pontas, caso extremo) | 6% | 8% | 3% |
| Paridade / classes mod 2 | 5% | 7% | 4% |
| Fórmula fechada / telescopia / conta direta | 5% | 8% | 3% |
| Resto, divisibilidade, gcd/lcm | 2% | 6% | 6% |
| Bits, xor, potências de 2, bit mais alto | 3% | 4% | 6% |
| Resposta pequena / poucos candidatos / casos | 1% | 6% | 6% |
| Construção (padrão, blocos, identidade) | 4% | 5% | 4% |
| Run-length / blocos de iguais | 4% | 3% | 3% |
| Invariante ou monovariante (soma, mod k, posição relativa) | — | 6% | 4% |
| Grade / geometria | 11% | — | — |
| Pombal / cota que a construção atinge | — | — | 7% |
| DP | — | — | 7% |
| Primos e fatoração | 2% | 2% | 3% |
| Jogos | 1% | 4% | 3% |
| Grafos e árvores | — | 2% | 5% |
| Trás pra frente / última operação / desfazer | 3% | 1% | 3% |
| Ordenar + varredura / two pointers | 3% | 4% | 1% |
| Exchange argument / mediana / convexidade | 1% | 3% | 3% |
| Estrutura simples (pilha, heap, segtree) | 1% | 3% | 2% |
| Período, ciclo, estabiliza | 1% | 2% | 2% |
| Strings (palíndromo, subsequência, espelho) | 3% | — | 1% |
| Busca binária / ternária na resposta | — | 1% | 3% |
| Interativo / comunicação | — | 1% | 2% |
| Contagem / contribuição | — | — | 3% |

(n: Div 4 = 101, Div 3 = 103, Div 2 = 147)

## Leituras

- **A é implementação ou extremo.** Simulação direta é 22% da letra A (quase toda de Div 4) e praticamente some a partir de C. Em Div 2 ela é 1%.
- **Cada letra tem um campeão claro.** B: frequências/multiconjunto. C: guloso (15%, o maior percentual de qualquer célula fora da simulação em A). D: prefixos/diferenças e bits.
- **Pombal/cota e DP só aparecem em Div 2** nesta amostra (7% cada). Resto/gcd e bits já aparecem em Div 3 em taxa parecida. Paridade é transversal (4–7% em todas as divisões).
- **DP, grafos e busca binária só a partir de C.** Em A e B são praticamente zero: se uma A/B parece pedir DP, procure antes a observação.
- **Estruturas de dados são 2%.** Em A–D, se parecer precisar de segtree, quase sempre há uma observação que a dispensa.

## Exemplos por técnica

- **Simulação / implementação direta** (30): CF 2094A, CF 2126A, CF 2132A, CF 2167A, CF 2179B, CF 2231C, CF 2233A, CF 2259A
- **Guloso (local, mais restrito primeiro, da esquerda)** (23): CF 2228C1, CF 2228C2, CF 2231B, CF 2232C1, CF 2252C, CF 2259C, CF 2264B, CF 2277A
- **Só as frequências importam / multiconjunto** (22): CF 2209D, CF 2227B, CF 2230C, CF 2242A, CF 2267B, CF 2275C, CF 2278A, CF 2278B
- **Prefixos / diferenças / sufixos** (21): CF 2248D, CF 2252D, CF 2254D, CF 2258B2, CF 2264D, CF 2266C, CF 2276C, CF 2277D2
- **Extremo decide (máx/mín, pontas, caso extremo)** (18): CF 2185B, CF 2200A, CF 2209B, CF 2218B, CF 2236A, CF 2250A, CF 2258A, CF 2284B
- **Paridade / classes mod 2** (18): CF 2236B, CF 2236D, CF 2244D, CF 2246A, CF 2254C1, CF 2267D, CF 2272B, CF 2280A
- **Fórmula fechada / telescopia / conta direta** (17): CF 2171B, CF 2184A, CF 2184C, CF 2226A, CF 2232D, CF 2257B, CF 2266A, CF 2283A
- **Resto, divisibilidade, gcd/lcm** (17): CF 2226B, CF 2228A, CF 2230B, CF 2238B, CF 2241A, CF 2244C, CF 2267C, CF 2283B
- **Bits, xor, potências de 2, bit mais alto** (16): CF 2234D, CF 2240A, CF 2240B, CF 2246D, CF 2247D1, CF 2260C, CF 2277D1, CF 2283C
- **Resposta pequena / poucos candidatos / casos** (16): CF 2234A, CF 2236C, CF 2247C, CF 2253B, CF 2260A, CF 2264A, CF 2272A, CF 2275A
- **Construção (padrão, blocos, identidade)** (15): CF 2218C, CF 2218D, CF 2231D, CF 2233B, CF 2234B, CF 2241B, CF 2246B, CF 2259D
- **Run-length / blocos de iguais** (12): CF 2220B, CF 2241C, CF 2242C, CF 2244A, CF 2250B, CF 2252B, CF 2254B, CF 2276B
- **Invariante ou monovariante (soma, mod k, posição relativa)** (12): CF 2210D, CF 2238A, CF 2247A, CF 2253D, CF 2256A, CF 2257A, CF 2266D, CF 2278C
- **Grade / geometria** (11): CF 1873C, CF 1926B, CF 1950B, CF 1971C, CF 1985D, CF 2009D, CF 2094C, CF 2148B
- **Pombal / cota que a construção atinge** (11): CF 2217B, CF 2217D, CF 2220A, CF 2247B, CF 2252A, CF 2263B, CF 2276A, CF 2277B
- **DP** (10): CF 2225C, CF 2230D, CF 2238C, CF 2242D, CF 2248C, CF 2258D, CF 2260D, CF 2274B
- **Primos e fatoração** (9): CF 2167D, CF 2195A, CF 2205B, CF 2227C, CF 2238D, CF 2253A, CF 2284C1, CF 2284C2
- **Jogos** (9): CF 2123A, CF 2123D, CF 2171C1, CF 2217A, CF 2228B, CF 2248A, CF 2263A, CF 2266B
- **Grafos e árvores** (9): CF 2195B, CF 2208D1, CF 2208D2, CF 2257C, CF 2272D, CF 2276D, CF 2277C, CF 2283D
- **Trás pra frente / última operação / desfazer** (8): CF 1703C, CF 1742C, CF 1915D, CF 2137A, CF 2205C, CF 2224A, CF 2253C, CF 2274A
- **Ordenar + varredura / two pointers** (8): CF 1791C, CF 1850D, CF 1999C, CF 2121D, CF 2149B, CF 2193D, CF 2248B, CF 2278D
- **Exchange argument / mediana / convexidade** (8): CF 2065D, CF 2149D, CF 2210B, CF 2224B, CF 2232A, CF 2254A, CF 2254C2, CF 2269A
- **Estrutura simples (pilha, heap, segtree)** (7): CF 2126D, CF 2185D, CF 2200C, CF 2205D, CF 2208B, CF 2247D2, CF 2275B
- **Período, ciclo, estabiliza** (6): CF 1692D, CF 2184B, CF 2256B, CF 2259B, CF 2260B, CF 2269B
- **Strings (palíndromo, subsequência, espelho)** (5): CF 1999D, CF 2044B, CF 2065B, CF 2233C, CF 2267A
- **Busca binária / ternária na resposta** (5): CF 2226C, CF 2232C2, CF 2257D, CF 2272C, CF 2275D
- **Interativo / comunicação** (4): CF 2162D, CF 2258C, CF 2280B, CF 2284D
- **Contagem / contribuição** (4): CF 2228D, CF 2246C, CF 2258B1, CF 2264C
