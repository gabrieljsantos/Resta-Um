# Como instalar e configurar as dependências e fazer o projeto “rodar”

Primeiro ponto: infelizmente, é necessário que todos os envolvidos no projeto estejam com as máquinas e seus ambientes de desenvolvimento **totalmente alinhados** — todo mundo usando a **mesma versão de tudo**.
E um conselho meu (Gabriel J. S.): que **todos baixem dos mesmos links**.
Sabemos que computadores, quando resolvem não funcionar, usam “magia” para fazer isso da pior forma possível.

Dito isso, vamos começar pela IDE.

---

## Code::Blocks

Você deve instalar o **Code::Blocks** na versão **20.03**.
Sabemos que existem versões mais recentes, mas, por enquanto, essa é a que funciona corretamente com a **Raylib** — e o que precisamos é que **rode sem erro**, mesmo sendo uma versão mais antiga.

---

### Onde encontrar o Code::Blocks versão 20.03?

Nesta [página do SourceForge](https://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows) é possível baixar a versão **20.03** do Code::Blocks.

> Atenção: escolha o instalador `codeblocks-20.03mingw-setup.exe`.

Durante a instalação, você pode trocar o diretório padrão de
`C:\Program Files\CodeBlocks`
para algo como
`C:\Program Files\CodeBlocks20.03`.

Motivo: isso evita conflito caso você queira manter uma versão mais recente do Code::Blocks instalada.
Claro que você também pode desinstalar a versão anterior ou simplesmente sobrescrever.
(Detalhe: eu **não sobrescrevi** e funcionou aqui — mas não garanto que sempre funcione.)

Em resumo: considere os riscos e confusões de ter duas versões diferentes do mesmo software na mesma máquina.

---

## Como abrir o projeto no Code::Blocks

Procure pelo arquivo chamado `projeto.cbp` que está na raiz do repositório e abra-o com o **Code::Blocks 20.03**.

Perfeito — o texto está ótimo na ideia e na explicação, só tem vários errinhos de digitação e concordância.
Aqui está a **versão revisada**, clara e padronizada, mantendo o mesmo tom descontraído e didático:

---

## `C:\MinGW` vs `C:\Program Files\CodeBlocks{...}\MinGW`

Se você já instalou o compilador **MinGW** na sua máquina, provavelmente possui a pasta `C:\MinGW`.
Mesmo instalando o **Code::Blocks 20.03**, ele pode acabar sendo configurado automaticamente para usar esse compilador externo — e o problema é que **a Raylib não está incluída nessa versão do MinGW**.
Por isso, é **necessário mudar o compilador externo para o interno do Code::Blocks 20.03**.

Para fazer isso:

1. Vá em **Settings → Compiler**.
2. Será aberta uma nova janela com várias abas; clique na aba **Toolchain executables**.
3. Procure a seção chamada **Compiler’s installation directory**.
4. Se o caminho estiver errado, você verá algo como `C:\MinGW` ou outro endereço qualquer (que é o compilador externo).
5. Clique nas reticências `...` e navegue até a pasta `MinGW` que fica dentro da pasta onde o **Code::Blocks 20.03** foi instalado.

   * Exemplo: `C:\Program Files\CodeBlocks20.03\MinGW`
6. Selecione a pasta e clique em **OK**.

Depois disso, para executar ▶️, faça primeiro:

* Tente fazer um **Build ⚙️**.
* Se não funcionar, tente um **Rebuild 🔁**.
* E, se mesmo assim nada acontecer, **feche o Code::Blocks e abra novamente**.


---