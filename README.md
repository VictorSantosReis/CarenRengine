# CarenRengine
Projeto tem como objetivo implementar algumas APIs nativas do Windows relacionadas a Mídia e Gráficos tanto 2D como 3D.
CarenRengine vai permitir o desenvolvimento de aplicativos **3D**, **2D**, **Mídia(Áudio e Vídeo)** em linguagens gerenciadas como 
o **C#(CSharp)**, com quase **TODAS** as **interfaces nativas** disponiveis no **C++** com a menor penalidade de desempenho possível que eu conseguir. 


# Motivação
O mundo de bibliotecas do .NET disponível atualmente, ao que se refere a aplicativos Win32 Desktop especificamente, não possui bibliotecas
avançadas para **gráficos(2D, 3D) e mídia(Áudio, Vídeo)** que possibilitem o desenvolivmento de um aplicativo, digamos, Renderizador de Vídeo(Player de Video)
de forma avançada(nas suas entranhas), o que temos é um componente de mídia(**MediaElement**) para renderizar com controles predefinidos.

Acredito que o Windows carece muito de uma biblioteca gerenciada para essas áreas que estão sendo muito mais exploradas hoje em dia.
Desenvolver um aplicativo em **C++**, pelo menos para mim é muito chato e entendiante devido a sintaxe da linguagem. 
**Já ouço alguns amantes do C++ me criticarem aqui(Risos).**

Gosto e muito do CSharp, todas as suas funcionalidades e praticidade aglomerada com as varias funções voltadas para codificação no Visual Studio
deixa muito agradável de programar na linguagem, ainda mais com o novo **.NET 5** ([.NET](https://github.com/dotnet/core)) que está fundindo
**.Net Core 3.1** em apenas uma única plataforma de desenvolvimento.


# Linguagem & Plataforma
O projeto é baseado na linguagem **C++ Gerenciado** ou **C++/CLR** como é comumente chamado. A plataforma .NET utilizada para compilar é a **.NET Core 3.1** que será
atualizada mais tarde para o **.NET 5** em seu lançamento oficial ainda este ano(2020).

No momento, não tenho interesse e nem motivo em suportar a plataforma NetFramework. Com a introdução do **.NET Core** e a vinda do **.NET 5** o desempenho
foi melhorado e muito, algo que não se pode ignorar. A utilização das intruções disponíveis pelo processador na biblioteca do **.NET** foi um ponto muito
importante para seu desempenho. Você pode dar um Google para encontrar essas informações de forma bem fácil.

![NetCore](https://github.com/VictorSantosReis/CarenRengine/tree/master/Imagens/NetCoreLogoNovo100x100.jpg)


# Arquitetura
Atualmente, CarenRengine suporta apenas o modelo de **[1 via]** de desenvolvimento. Significa que o usuário envia comandos para a API processar, mais o contrário
não é possível até o momento. Um modelo **[2 vias]** gerenciado é necessário em algumas interfaces que permitem que o usuário sobrescreva para poder personalizar
uma entrada ou saida de dados. Um caso simples de interface seria a [IMFTransform](https://docs.microsoft.com/en-us/windows/win32/api/mftransform/nn-mftransform-imftransform)
da API **Microsoft Media Foundation** que permite o usuário criar um decodificador personalizado para um tipo. Apesar desse recurso de implementar sua própria interface gerenciada não está diponível, ainda é possível criar uma implementação em código nativo e passar um ponteiro para a interface de destino.

* **A seguinte imagem demonstra a arquitetura básica do projeto e suas APIs:**

![Arquitetura](https://github.com/VictorSantosReis/CarenRengine/tree/master/Imagens/CarenRengineAPIs.jpg)

'*' **Pode ou não ser incluido futuramente!**

**CarenRengine** é uma biblioteca baseada 99% em interfaces. **ICaren** é a interface base e comum a todas as outras disponíveis pela biblioteca, assemelhando-se a interface nativa **IUnkown** que a maioria das interfaces do Windows derivam.

Chamar os métodos nativos das interfaces é um processo muito simples e familiar a qualquer outra chamada para um método no C#. Todos os métodos implementados pela biblioteca
segue a regra de manter a ordem original dos parametros nos métodos da interface, ou seja, replicar um exemplo disponível no site da Microsoft para determinada API não será uma tarefa muito diferente.

* **Aqui está um exemplo simples de uma chamada para o método nativo (**BeginDraw**) presente na interface (**ID2D1RenderTarget**) da API Direct2D:**

![FuncChamada](https://github.com/VictorSantosReis/CarenRengine/tree/master/Imagens/CarenRengine_ChamadaDeMetodo.jpg)

Todos os tipos(**Enum**, **Estrutura**, **GUIDs**) tem sua correspondência gerenciada pela biblioteca. O **namespace SDKBase** contém todas as **estruturas**, **enumeraçôes**, **GUIDs** que podem ser utilizado pelas APIs e que você ira utilizar nos métodos. Seguindo um padrão comum, todos os tipos gerenciados tem um **CA_** no inicio de seu nome. Então, se um parametro nativo exige a seguinte estrutura (**D2D1_COLOR_F**), sua represenção gerenciada seria **CA_D2D1_COLOR_F**.


# APIs
As **Urls** a seguir levam diretamente para o site de desenvolvedor da Microsoft para a API especificada. Devo mencionar, nem todas as
interfaces podem está disponível atualmente, mais tardar estarei desenvolvendo um **Roadmap** completo para o projeto.

* [Media Foundation](https://docs.microsoft.com/en-us/windows/win32/medfound/microsoft-media-foundation-sdk) - Principal API para Leitura/Reprodução/Gravação de Áudio e Vídeo.
* [Core Audio](https://docs.microsoft.com/en-us/windows/win32/CoreAudio/core-audio-apis-in-windows-vista) - Este Core é responsável por 4 APIs: MMDevice, WASAPI, EndpointVolume e DeviceTopology API.
* [Windows Imaging Component](https://docs.microsoft.com/en-us/windows/win32/wic/-wic-about-windows-imaging-codec) - API responsável por trabalhar com imagens e seus metadados. Tem forte integração com o Direct2D.
* [DXGI](https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/dx-graphics-dxgi-overviews) - O Microsoft DirectX Graphics Infrastructure (DXGI) gerencia tarefas de baixo nível que podem ser independentes do tempo de execução dos gráficos Direct3D. O DXGI fornece uma estrutura comum para várias versões do Direct3D.
* [Direct2D](https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-portal) - API gráfica 2D acelerada por hardware com alta performance e renderização de alta qualidade para geometrias 2D, Bitmaps e textos.
* [Direct3D 11](https://docs.microsoft.com/en-us/windows/win32/direct3d11/atoc-dx-graphics-direct3d-11) - API gráfica 3D utilizada para renderização de gráficos 3D / 2D para aplicativos e jogos.


# Documentação
A documentação das APIs nativas podem ser acessadas nos links dispostos acima, você pode estudar por eles para enteder como funciona e apenas fazer algumas adaptações para o código gerenciado com o mesmo esquema.
A documentação referente a como CarenRengine funciona ainda será publicada aqui ou em um site especifico(muita coisa para uma pessoa só 😬).


# Como começar
Para começar a desenvolver com está biblioteca você vai precisar:
* SDK do .Net Core 3.1 - https://dotnet.microsoft.com/download/dotnet-core/3.1
* Windows 10 x86 ou x64 - Build 1809 ou superior - https://www.microsoft.com/pt-br/software-download/windows10
* Visual Studio (16.7) ou superior - https://visualstudio.microsoft.com/pt-br/downloads/


# Pacotes Nuget
Como o Nuget Packge não suporta de forma oficial as montagens em **C++/CLI**, decidir não fazer neste momento porque precisaria criar um pacote para cada montagem(x86 e x64) e isso seria bastante irritante. Essa é um questão que vou pensar em uma solução mais para frente já que a biblioteca será portada com o tempo para o **WInRT**.

**Neste caso então, baixe o projeto ou faça um fork, compile para a arquitetura de destino de sua preferência e comece a utilizar fazendo uma referência a seu DLL gerado.**


# O que esperar do Futuro?
Inicio do proximo ano pretendo lançar a primeira versão da biblioteca com todas as APIs do **Roadmap** e mais tardar para o meio do ano estarei já iniciando a grande migração da bibliteca para o WinRT C++(**Windows Runtime Component**) que já está suportando em versão Preview, a possibilidade de usar o componente tanto em aplicativos Win32 Desktop como o UWP graças aos projetos [WinUI3.0](https://github.com/microsoft/microsoft-ui-xaml) e o [CsWinRT](https://github.com/microsoft/CsWinRT) em versão preview ainda.

Não recomendo utilizar a biblioteca neste momento para produção. Muitas coisas seram modificadas até o lançamento da primeira versão estável. Algumas coisas criticas que logo seram modificadas é a forma de criação atual das classes seram modificadas para usar o (**new NomeClasse**) em vez de **NomeClass.CriarInstancia([Out] NomeClasse)**


# Contribuição
Note, eu trabalho atualmente sozinho neste projeto a cerca de uns 3 anos, atualmente estou focado em terminar todas as bibliotecas para depois realizar testes, verificar bugs e percas de desempenho. Tenho alguns projetos de testes já em andamento, mais não estou muito focado nesta questão.
Fique a vontade mesmo assim para clicar em **Criar um novo erro** e eu estarei adicionando a um marrco para poder está sanando o bug e realizando os devidos testes eventualmente.


# Codificação
Eu não possuo um conhecimento necessário para criar uma grande codificação, sou programador apenas como **Hobby**, curto bastante programar em meu tempo livre.
Com o tempo o código pode ser melhorado quando apenas focar no desempenho e na limpeza, mais sinta-se a vontade para expor uma melhor maneira de criar a codificação
de alguma parte do projeto.


# Licença
**APACHE 2.0**
