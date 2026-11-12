"""Gera docs/catalogo.pdf a partir do mapa rapido, do catalogo completo e do indice da lib.

Uso:  python docs/build_pdf.py            (a partir da raiz do repo)
Precisa: python -m pip install markdown ; Chrome ou Edge instalado (impressao headless).
"""
import html, os, re, shutil, subprocess, sys
from pathlib import Path
import markdown

ROOT = Path(__file__).resolve().parent.parent
DOCS = ROOT / "docs"
OUT_HTML = DOCS / "catalogo.html"
OUT_PDF = DOCS / "catalogo.pdf"

CSS = r"""
@page { size: A4; margin: 14mm 13mm 16mm 13mm;
  @bottom-center { content: counter(page); font-size: 8pt; color: #888; } }
:root { --ink:#1b1f24; --mute:#5c6670; --line:#d8dde3; --acc:#1f5fa8; --acc2:#e8f0fa; --warn:#8a5a00; }
* { box-sizing: border-box; }
body { font-family: "Segoe UI", "Noto Sans", "DejaVu Sans", Arial, sans-serif; color: var(--ink);
  font-size: 9.4pt; line-height: 1.38; margin: 0; }
h1, h2, h3 { font-family: "Segoe UI Semibold", "Segoe UI", sans-serif; color: #10243e; }
.cover { height: 260mm; display: flex; flex-direction: column; justify-content: center; padding: 0 12mm;
  page-break-after: always; }
.cover h1 { font-size: 34pt; margin: 0 0 4mm; border: 0; }
.cover .sub { font-size: 13pt; color: var(--mute); }
.cover .meta { margin-top: 18mm; font-size: 9.5pt; color: var(--mute); }
.part { page-break-before: always; }
.part > h1 { font-size: 22pt; border-bottom: 3px solid var(--acc); padding-bottom: 2mm; margin: 0 0 4mm; }
h2 { font-size: 13.5pt; margin: 6mm 0 2mm; padding: 1.2mm 2.5mm; background: var(--acc2);
  border-left: 4px solid var(--acc); break-after: avoid; }
h3 { font-size: 11pt; margin: 4mm 0 1.5mm; break-after: avoid; }
p { margin: 1.2mm 0; }
ul { margin: 1mm 0 2mm; padding-left: 5mm; }
li { margin: 0.6mm 0; break-inside: avoid; }
strong { color: #0d2f57; }
code { font-family: Consolas, "DejaVu Sans Mono", monospace; font-size: 8.6pt; background: #f2f4f7;
  padding: 0 1px; border-radius: 2px; }
table { border-collapse: collapse; width: 100%; margin: 2mm 0 3mm; font-size: 8.3pt; }
th, td { border: 1px solid var(--line); padding: 1mm 1.6mm; vertical-align: top; text-align: left; }
th { background: #eef2f6; }
tr { break-inside: avoid; }
tbody tr:nth-child(even) td { background: #fafbfc; }
blockquote { margin: 2mm 0; padding: 1.5mm 3mm; border-left: 3px solid #d9a300; background: #fff8e5;
  color: var(--warn); font-size: 8.6pt; }
em.stamp { display: block; font-size: 7.5pt; color: #a07a20; font-style: normal; margin: 2mm 0 0.5mm;
  border-top: 1px dashed #e2c98a; padding-top: 0.8mm; }
.toc { columns: 2; column-gap: 8mm; font-size: 9pt; }
.toc a { color: var(--ink); text-decoration: none; }
.toc .p { font-weight: 600; margin-top: 2mm; break-after: avoid; }
.toc div.s { padding-left: 4mm; }
.mapa ul { columns: 2; column-gap: 7mm; }
.mapa p { break-inside: avoid; }
a { color: var(--acc); }
"""

def md(text):
    # Python-Markdown exige linha em branco antes de lista/tabela; o catalogo nem sempre tem.
    out = []
    # sub-listas com 2 espacos -> 4 (Python-Markdown so aninha com 4)
    text = re.sub(r"(?m)^( +)", lambda m: m.group(1) * 2, text)
    for line in text.split("\n"):
        starts_block = re.match(r"\s*([-*]|\d+\.) ", line) or line.startswith("|")
        if starts_block and out and out[-1].strip() and not (
                re.match(r"\s*([-*]|\d+\.) ", out[-1]) or out[-1].startswith("|")):
            out.append("")
        out.append(line)
    return markdown.markdown("\n".join(out), extensions=["tables", "sane_lists"])

def slug(s):
    s = re.sub(r"<[^>]+>", "", s)
    return "s-" + re.sub(r"[^\w]+", "-", s.lower()).strip("-")

def add_ids(h, prefix, toc, part_title):
    def rep(m):
        lvl, inner = m.group(1), m.group(2)
        sid = prefix + slug(inner)
        if lvl == "2":
            toc.append((part_title, re.sub(r"<[^>]+>", "", inner), sid))
        return f'<h{lvl} id="{sid}">{inner}</h{lvl}>'
    return re.sub(r"<h([23])>(.*?)</h\1>", rep, h)

def stamp(h):
    # destaca o carimbo de "nao revisado" das partes geradas por agentes
    return re.sub(r"<p><em>\((adicionado em [^<]*)\)</em></p>", r'<em class="stamp">\1</em>', h)

def lib_index_md():
    idx = DOCS / "lib-index.md"
    return idx.read_text(encoding="utf-8") if idx.exists() else "_Indice da lib ainda nao gerado._"

def main():
    mapa = (DOCS / "mapa-rapido.md").read_text(encoding="utf-8")
    comp = (DOCS / "catalogo-completo.md").read_text(encoding="utf-8")
    # tira o titulo/autor do topo dos md: viram capa e titulo de parte
    mapa = re.sub(r"\A# .*\n", "", mapa)
    comp = re.sub(r"\A# .*\n+(.*@.*\n)?", "", comp)
    toc = []
    parts = [
        ("Mapa rápido", "mapa", md(mapa), "m-"),
        ("Catálogo completo", "comp", stamp(md(comp)), "c-"),
        ("Índice da lib (técnica → arquivo)", "lib", md(lib_index_md()), "l-"),
    ]
    freq = DOCS / "frequencias-cf.md"
    if freq.exists():  # frequencias de tecnicas em CF Div 2/3/4 A-D
        parts.insert(1, ("Frequências em CF (A–D)", "freq",
                         md(re.sub(r"\A# .*\n", "", freq.read_text(encoding="utf-8"))), "f-"))
    body = []
    for title, cls, h, pre in parts:
        h = add_ids(h, pre, toc, title)
        body.append(f'<section class="part {cls}"><h1>{html.escape(title)}</h1>{h}</section>')
    toc_html, last = [], None
    for part, name, sid in toc:
        if part != last:
            toc_html.append(f'<div class="p">{html.escape(part)}</div>'); last = part
        toc_html.append(f'<div class="s"><a href="#{sid}">{html.escape(name)}</a></div>')
    doc = f"""<!doctype html><html lang="pt-br"><head><meta charset="utf-8">
<title>Catálogo de ideias</title><style>{CSS}</style></head><body>
<div class="cover"><h1>Catálogo de ideias</h1>
<div class="sub">Gatilho → ideia → técnica → código, para programação competitiva e ICPC</div>
<div class="meta">Partes: mapa rápido · frequências em CF · catálogo completo · índice da lib<br>
Blocos marcados "adicionado … não revisado" foram gerados automaticamente e ainda não foram conferidos.</div></div>
<section class="part"><h1>Sumário</h1><div class="toc">{''.join(toc_html)}</div></section>
{''.join(body)}</body></html>"""
    OUT_HTML.write_text(doc, encoding="utf-8")
    browser = next((p for p in [
        r"C:\Program Files\Google\Chrome\Application\chrome.exe",
        r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
        shutil.which("google-chrome") or "", shutil.which("chromium") or ""] if p and os.path.exists(p)), None)
    if not browser:
        sys.exit("Chrome/Edge nao encontrado; abra docs/catalogo.html e imprima em PDF.")
    subprocess.run([browser, "--headless=new", "--disable-gpu", "--no-pdf-header-footer",
                    f"--print-to-pdf={OUT_PDF}", OUT_HTML.as_uri()], check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, timeout=180)
    print("ok:", OUT_PDF)

if __name__ == "__main__":
    main()
