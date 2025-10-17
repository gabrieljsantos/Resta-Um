Perfeito. Seguindo sua orientação, aqui está o README atualizado com a análise das versões A e B, considerando apenas o que já está implementado e funcional:

---

# Resta Um — Projeto de Programação 2 (C++)

## Descrição

Implementação do jogo de tabuleiro **Resta Um** (peg solitaire) em C++ como projeto da disciplina de Programação 2. O objetivo é reproduzir as regras clássicas, fornecer uma interface em terminal ou gráfica para jogar e demonstrar organização de código, uso de estruturas de dados e testes básicos.

---

## Estrutura atual de pastas

```
/ (raiz)
├─ Gabriel Bispo/           # Versão A do projeto
├─ Gabriel J Santos/        # Versão B do projeto
├─ Eduardo J. S/            # Ainda sem implementações
├─ Template/                # Templates prontos para iniciar projetos
├─ Tutoriais/               # Tutoriais criados com a Raylib
```

---

## Pastas detalhadas

### Pasta `Gabriel Bispo` — Versão A

* Tabuleiro representado como matriz 7x7 (`tabuleiro[TAM][TAM]`).
* Cada célula possui posição em pixels e estado (inválido, vazio ou ocupado).
* Movimentos válidos verificados com regra simples: pulo de duas casas horizontal ou vertical.
* Interface gráfica usando **Raylib**: desenha tabuleiro, peças, seleção do mouse, highlight, botão de reset.
* Registro de recordes em arquivo de texto, exibidos na tela.
* Simples, direta e fácil de manter.

**Observação:** Essa versão é **mais estável** e adequada para iniciar o projeto ou manter como base oficial.

---

### Pasta `Gabriel J Santos` — Versão B

* Tabuleiro representado como **vetores lineares** (`parts[32]` e `empty_place[33]`) com coordenadas cartesianas.
* Transformação de coordenadas para a tela via funções `scaled_to_screen` e `translate_cartesian_to_screen`.
* Seleção da peça pelo mouse com verificação de distância e estado.
* Verificação de possibilidade de movimentos com análise ortogonal de vizinhos (`possibility_of_moving`).
* Desenho do tabuleiro e peças com destaque da seleção.
* Mais genérica e flexível, permite facilmente alterar posições e tamanho do tabuleiro.

**Observação:** Apesar de mais flexível, essa versão é **mais complexa** e verbosa. Funciona corretamente para seleção e indicação de movimentos possíveis, mas algumas funcionalidades avançadas ainda não estão integradas (como reset ou recordes).

---

## Comparação das versões

| Aspecto                | Versão A                            | Versão B                                          |
| ---------------------- | ----------------------------------- | ------------------------------------------------- |
| Estrutura do tabuleiro | Matriz 2D                           | Vetores lineares                                  |
| Flexibilidade          | Menor, tamanho fixo                 | Maior, coordenadas cartesianas                    |
| Movimentos             | Simples, direto                     | Usa vizinhança ortogonal                          |
| Seleção                | Mouse simples, distância até centro | Mouse com cálculo de distância em pixels          |
| Reset/Recordes         | Implementados                       | Não implementados                                 |
| Complexidade           | Baixa, fácil manutenção             | Alta, mais verbosa                                |
| Recomendação           | Base estável para uso               | Experimental/flexível, bom para teste ou expansão |

---

## Regras do jogo

* Tabuleiro inicial com peças ocupando quase todas as posições, exceto um buraco central (configuração clássica).
* Uma peça pode pular sobre uma peça adjacente (horizontal ou vertical) para uma casa vazia imediatamente após a peça pulada; a peça pulada é removida.
* Objetivo: restar apenas 1 peça no tabuleiro (idealmente no centro).
* Jogo termina quando não há movimentos válidos ou quando resta 1 peça.

---

## Funcionalidades implementadas

* Representação do tabuleiro.
* Movimentação válida (checar salto e remoção).
* Interface gráfica (Raylib) para seleção e visualização de peças.
* Validação de movimentos e detecção de fim de jogo.
* Destaque visual da peça selecionada.
* Contador de peças restantes (Versão A).
* Salvamento/carregamento de recordes (Versão A).

---

## Raylib

A **Raylib** é uma biblioteca em **C/C++** voltada para **criação de jogos e aplicações gráficas**.
Oferece recursos para gráficos 2D/3D, sons, entrada de teclado, mouse e janelas, sendo ideal para protótipos rápidos.
Foi desenvolvida para ser leve, multiplataforma e de fácil aprendizado.

---

## Autoria / Participantes

* Cauã Cruz dos Santos
* Gabriel Carvalho Tenório
* Eduardo de Jesus Santos
* Gabriel de Jesus Santos
* Anderson Santos Santana
* Alysson Santos
* Gabriel da Silva Bispo

---

## Referências

* Descrição clássica do jogo **Resta Um / Peg Solitaire**.
* Materiais de apoio da disciplina de **Programação 2**.
* Tutoriais e exemplos da biblioteca **Raylib**.