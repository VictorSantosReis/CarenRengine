/*
Copyright 2020 Victor Santos Reis

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


#pragma once
#include "SDK_Base.h"

//Importa os namespaces do SDK BASE do sistema.
using namespace CarenRengine::SDKBase;
using namespace CarenRengine::SDKBase::Enumeracoes;
using namespace CarenRengine::SDKBase::Estruturas;
using namespace CarenRengine::SDKBase::Interfaces;

//Abre o namespace principal
namespace CarenRengine
{
	namespace Windows
	{
		/// <summary>
		/// (IStream) - Interface responsável por representar um IStream que permite que você leia e escreva dados para transmitir objetos. Os objetos de fluxo contêm os dados em 
		/// um objeto de armazenamento estruturado, onde os armazenamentos fornecem a estrutura. Dados simples podem ser escritos diretamente em um fluxo, mas, na maioria das vezes, 
		/// os fluxos são elementos aninhados dentro de um objeto de armazenamento. Eles são semelhantes aos arquivos padrão.
		/// Os métodos nesta interface apresentam os dados do seu objeto como uma sequência contígua de bytes que você pode ler ou escrever. Há também métodos para cometer e reverter
		///  alterações em fluxos que estão abertos no modo transacionado e métodos para restringir o acesso a uma variedade de bytes no fluxo.
		/// </summary>
		[CategoryAttribute("Windows Interface")]
		[Guid("66BE0CDF-F0F1-4260-B64B-CBBAC152B4A4")]
		public interface class ICarenStream : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// O método Clone cria um novo objeto de fluxo com seu próprio ponteiro de busca que faz referência aos mesmos bytes do fluxo original.
			/// O método Clone cria um novo objeto de fluxo para acessar os mesmos bytes, mas usando um ponteiro de busca separado. O novo objeto de fluxo vê os mesmos dados do 
			/// objeto de fluxo de origem. As alterações escritas em um objeto são imediatamente visíveis no outro. O bloqueio de alcance é compartilhado entre os objetos do fluxo.
			/// A configuração inicial do ponteiro de busca na instância de fluxo clonado é a mesma da configuração atual do ponteiro de busca no fluxo original no momento da operação do clone.
			/// </summary>
			/// <param name="Param_Out_CloneInterface">Retorna uma interface (ICarenStream) clonada da interface atual.</param>
			CarenResult Clone([Out] ICarenStream^% Param_Out_CloneInterface);

			/// <summary>
			/// O método Commit garante que quaisquer alterações feitas em um objeto de fluxo aberto no modo transacionado sejam refletidas no armazenamento pai. Se o objeto de fluxo
			/// estiver aberto no modo direto, o ICarenStream::Commit não tiver outro efeito além de direcionar todos os buffers de memória para o objeto de armazenamento de nível 
			/// próximo. A implementação de arquivos compostos COM de fluxos não suporta abertura de fluxos no modo transacionado.
			/// Se o fluxo estiver aberto no modo direto, este método garante que quaisquer buffers de memória tenham sido liberados para o objeto de armazenamento subjacente. 
			/// Isso é muito parecido com uma descarga nos sistemas de arquivos tradicionais.
			/// </summary>
			/// <param name="Param_CommitFlags">Controla como as alterações do objeto de fluxo são cometidas. Consulte a enumeração do STGC para obter uma definição desses valores.</param>
			CarenResult Commit(CA_STGC Param_CommitFlags);

			/// <summary>
			/// O método CopyTo copia um número especificado de bytes do ponteiro de busca atual no fluxo para o ponteiro de busca atual em outro fluxo.
			/// O método CopyTo copia os bytes especificados de um fluxo para outro. Ele também pode ser usado para copiar um fluxo para si mesmo. O ponteiro de busca em cada 
			/// instância de fluxo é ajustado para o número de bytes lidos ou escritos.
			/// </summary>
			/// <param name="Param_StreamDestino">Um ponteiro para o fluxo de destino. O fluxo apontado pelo (Param_StreamDestino) pode ser um novo fluxo ou um clone do fluxo de origem.</param>
			/// <param name="Param_CountBytesCopy">O número de bytes para copiar a partir do fluxo de origem.</param>
			/// <param name="Param_Out_CountBytesReaded">Retorna o número real de bytes lidos a partir do fluxo de origem.</param>
			/// <param name="Param_Out_CountBytesWritten">Retorna o número real de bytes escritos para o fluxo de destino.</param>
			CarenResult CopyTo(
				ICarenStream^ Param_StreamDestino,
				UInt64 Param_CountBytesCopy,
				[Out] UInt64% Param_Out_CountBytesReaded,
				[Out] UInt64% Param_Out_CountBytesWritten);

			/// <summary>
			/// O método LockRegion restringe o acesso a uma faixa especificada de bytes no fluxo. Suportar essa funcionalidade é opcional, uma vez que alguns sistemas de arquivos 
			/// não fornecem. A faixa de byte do fluxo pode ser estendida. Bloquear um intervalo estendido para o fluxo é útil como um método de comunicação entre diferentes instâncias 
			/// do fluxo sem alterar dados que realmente fazem parte do fluxo.
			/// Qualquer região bloqueada com ICarenStream::LockRegion deve ser desbloqueada explicitamente chamando ICarenStream::UnlockRegion com exatamente os mesmos valores para 
			/// os parâmetros Param_Offset, Param_CountBytes e Param_LockType.
			/// </summary>
			/// <param name="Param_Offset">Especifica o byte offset para o início do intervalo.</param>
			/// <param name="Param_CountBytes">Especifica, em bytes, o comprimento da faixa a ser restringida.</param>
			/// <param name="Param_LockType">Especifica as restrições solicitadas ao acessar o intervalo.</param>
			CarenResult LockRegion(
				UInt64 Param_Offset,
				UInt64 Param_CountBytes,
				CA_LOCKTYPE Param_LockType);

			/// <summary>
			/// O método Revert descarta todas as alterações que foram feitas em um fluxo transacionado desde a última chamada ICarenStream::Commit. Em fluxos abertos no modo direto 
			/// e streams usando a implementação de arquivo composto COM do ICarenStream::Revert, este método não tem efeito.
			/// </summary>
			CarenResult Revert();

			/// <summary>
			/// O método Seek altera o ponteiro de busca para um novo local. A nova localização é relativa ao início do fluxo, ao fim do fluxo ou ao ponteiro de busca atual.
			/// </summary>
			/// <param name="Param_Deslocamento">O deslocamento a ser adicionado ao local indicado pelo parâmetro (Param_Origem). Se (Param_Origem) é CA_STREAM_SEEK_SET, isso é 
			/// interpretado como um valor não assinado em vez de um valor assinado.</param>
			/// <param name="Param_Origem">A origem do deslocamento especificado em (Param_Deslocamento). A origem pode ser o início do arquivo(CA_STREAM_SEEK_SET), o ponteiro de 
			/// busca atual(CA_STREAM_SEEK_CUR), ou o final do arquivo(CA_STREAM_SEEK_END).</param>
			/// <param name="Param_Out_NovaPosicao">Retorna a nova posição do ponteiro de busca.</param>
			CarenResult Seek(
				Int64 Param_Deslocamento,
				CA_STREAM_SEEK Param_Origem,
				[Out] UInt64% Param_Out_NovaPosicao);


			/// <summary>
			/// O método SetSize altera o tamanho do objeto de fluxo. O ponteiro de busca não é afetado pela mudança no tamanho do fluxo.
			/// Se o parâmetro (Param_NovoTamanho) for menor do que o fluxo atual, o fluxo será truncado ao tamanho indicado. 
			/// </summary>
			/// <param name="Param_NovoTamanho">Especifica o novo tamanho, em bytes, do fluxo.</param>
			CarenResult SetSize(UInt64 Param_NovoTamanho);

			/// <summary>
			/// O método Stat recupera a estrutura CA_STATSTG para este fluxo.
			/// </summary>
			/// <param name="Param_Out_StaticsStream">Retorna uma estrutura STATSTG onde este método coloca informações sobre este objeto de fluxo.</param>
			/// <param name="Param_Flags">Especifica que este método não retorna alguns dos membros na estrutura STATSTG, salvando assim uma operação de alocação de memória. 
			/// Os valores são retirados da enumeração CA_STATFLAG.</param>
			CarenResult Stat(
				[Out] CA_STATSTG^% Param_Out_StaticsStream,
				CA_STATFLAG Param_Flags);

			/// <summary>
			/// O método UnlockRegion remove a restrição de acesso em uma série de bytes previamente restritos com ICarenStream::LockRegion.
			/// </summary>
			/// <param name="Param_Offset">Especifica o byte offset para o início do intervalo.</param>
			/// <param name="Param_CountBytes">Especifica, em bytes, o comprimento da faixa a ser restringida.</param>
			/// <param name="Param_LockType">Especifica as restrições de acesso previamente colocadas no intervalo.</param>
			CarenResult UnlockRegion(
				UInt64 Param_Offset,
				UInt64 Param_CountBytes,
				CA_LOCKTYPE Param_LockType);
		};

		/// <summary>
	    /// (IPersist) Interface base responsável por fornecer o CLSID(Guid) de um objeto que pode ser armazenado persistentemente no sistema.
	    /// ICarenPersist é a interface base para três outras interfaces: IPersistStorage, ICarenPersistStream e IPersistFile. Cada uma dessas interfaces, portanto, 
	    /// inclui o método GetClassID, e a única dessas três interfaces é implementada em objetos que podem ser serializados em um armazenamento, um fluxo ou um arquivo.
	    /// </summary>
		[CategoryAttribute("Windows Interface")]
		[Guid("634FCBB7-38C4-461B-8333-CBEE80636D36")]
		public interface class ICarenPersist : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera o identificador de classe (CLSID) do objeto.
			/// </summary>
			/// <param name="Param_Out_ClassID">Retorna o CLSID do objeto atual.</param>
			/// <returns></returns>
			CarenResult GetClassID([Out] String^% Param_Out_ClassID);
		};

		/// <summary>
		/// (IPersistStream) Interface responsável permitir a economia e o carregamento de objetos que usam um fluxo serial simples para suas necessidades de armazenamento.
		/// </summary>
		[CategoryAttribute("Windows Interface")]
		[Guid("FFA1A27A-F29B-41B2-A220-E44DA5931F5D")]
		public interface class ICarenPersistStream : ICarenPersist
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}


			//Métodos

			/// <summary>
			/// Recupera o tamanho do fluxo necessário para salvar o objeto.
			/// Este método retorna o tamanho necessário para salvar um objeto. Você pode chamar este método para determinar o tamanho e definir os 
			/// buffers necessários antes de chamar o método ICarenPersistStream::Save.
			/// </summary>
			/// <param name="Param_Out_Size">Retorna o tamanho em bytes do fluxo necessário para salvar este objeto, em bytes.</param>
			/// <returns></returns>
			CarenResult GetSizeMax(UInt64% Param_Out_Size);

			/// <summary>
			/// Determina se um objeto mudou desde que foi salvo pela última vez em seu fluxo.
			/// Este método retorna SS_OK para indicar que o objeto foi alterado. Caso contrário, ele retorna SS_FALSE.
			/// Você deve tratar quaisquer códigos de retorno de erro como uma indicação de que o objeto foi alterado. A menos que este método retorne 
			/// explicitamente SS_FALSE, assuma que o objeto deve ser salvo.
			/// </summary>
			/// <returns></returns>
			CarenResult IsDirty();

			/// <summary>
			/// Inicializa um objeto do fluxo onde ele foi salvo anteriormente.
			/// </summary>
			/// <param name="Param_Fluxo">Um ICarenStream para o fluxo a partir do qual o objeto deve ser carregado.</param>
			/// <returns></returns>
			CarenResult Load(ICarenStream^ Param_Fluxo);

			/// <summary>
			/// Salva um objeto para o fluxo especificado.
			/// </summary>
			/// <param name="Param_Fluxo">Um ICarenStream para o fluxo no qual o objeto deve ser salvo.</param>
			/// <param name="Param_ClearDirty">Indica se o sinalizador sujo deve ser limpo após a conclusão do salvamento.Se TRUE, o sinalizador deve ser apagado. Se FALSE, o 
			/// sinalizador deve ser deixado inalterado.</param>
			/// <returns></returns>
			CarenResult Save(ICarenStream^ Param_Fluxo, Boolean Param_ClearDirty);
		};

		public interface class ICarenInspectable : ICaren
		{

		};

		public interface class ICarenRandomAcessStream : ICarenInspectable
		{

		};

		/// <summary>
		/// (IEnumString) - Interface responsável por enumerar strings. LPWSTR é o tipo que indica um ponteiro para uma sequência de caracteres wide, ou Unicode.
		/// </summary>
		[CategoryAttribute("Windows Interface")]
		[Guid("81EB331C-4725-464C-8A9A-E5B8F5A89EF6")]
		public interface class ICarenEnumString : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Métodos


			/// <summary>
			/// Cria um novo enumerador que contém o mesmo estado de enumeração que o atual. Este método permite gravar um ponto na sequência de enumeração para retornar a esse ponto mais tarde.O interlocutor deve 
			/// liberar este novo enumerador separadamente do primeiro enumerador.
			/// </summary>
			/// <param name="Param_Out_EnumString">Retorna um ponteiro clonado da interface atual.</param>
			CarenResult Clone([Out] ICarenEnumString^% Param_Out_EnumString);

			/// <summary>
			/// Recupera o número especificado de itens na sequência de enumeração.
			/// </summary>
			/// <param name="Param_Quantidade">O número de itens a serem recuperados. Se houver menos do que o número solicitado de itens deixados na sequência, este método recupera os elementos restantes.</param>
			/// <param name="Param_Out_Itens">Retorna uma variedade de itens enumerados.</param>
			/// <param name="Param_Out_QuantidadeRetornada">Retorna o número de itens que foram recuperados. Este parâmetro é sempre menor ou igual ao número de itens solicitados.</param>
			CarenResult Next(
				UInt32 Param_Quantidade,
				[Out] cli::array<String^>^% Param_Out_Itens,
				[Out] UInt32% Param_Out_QuantidadeRetornada);

			/// <summary>
			/// Redefine a sequência de enumeração até o início.
			/// Não há garantia de que o mesmo conjunto de objetos será enumerado após a conclusão da operação de reset. Uma coleção estática é redefinida para o início, mas pode ser muito cara para algumas coleções, 
			/// como arquivos em um diretório, para garantir essa condição.
			/// </summary>
			CarenResult Reset();

			/// <summary>
			/// Ignora um número especificado de itens na sequência de enumeração.
			/// </summary>
			/// <param name="Param_CountSkip">O número de itens a serem ignorados.</param>
			CarenResult Skip(UInt32 Param_CountSkip);
		};

		/// <summary>
		/// (IEnumUnknown) - Interface responsável por enumerar objetos com a interface IUnknown. Pode ser usado para enumerar através dos objetos em um componente contendo 
		/// vários objetos.
		/// </summary>
		[CategoryAttribute("Windows Interface")]
		[Guid("A9957309-C57A-4A73-BA40-F7862771BF4C")]
		public interface class ICarenEnumUnknown : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}

			//Métodos

			/// <summary>
			/// Cria um novo enumerador que contém o mesmo estado de enumeração que o atual. Este método permite gravar um ponto na sequência de enumeração para retornar a esse ponto mais tarde. O interlocutor deve 
			/// liberar este novo enumerador separadamente do primeiro enumerador.
			/// </summary>
			/// <param name="Param_Out_EnumClone">Retorna o ponteiro para o objeto enumerador clonado.</param>
			CarenResult Clone([Out] ICarenEnumUnknown^% Param_Out_EnumClone);

			/// <summary>
			/// Recupera o número especificado de itens na sequência de enumeração.
			/// </summary>
			/// <param name="Param_Quantidade">O número de itens a serem recuperados. Se houver menos do que o número solicitado de itens deixados na sequência, este método recupera os elementos restantes.</param>
			/// <param name="Param_Out_ItensEnumerados">Retorna uma variedade de itens enumerados. O chamador é responsável por liberar as interface depois de sua utilização.</param>
			/// <param name="Param_Out_QuantidadeRetornada">O número de itens que foram recuperados. Este parâmetro é sempre menor ou igual ao número de itens solicitados.</param>
			CarenResult Next(
				UInt32 Param_Quantidade,
				[Out] cli::array<ICaren^>^ Param_Out_ItensEnumerados,
				[Out] UInt32% Param_Out_QuantidadeRetornada);

			/// <summary>
			/// Redefine a sequência de enumeração até o início.
			/// </summary>
			CarenResult Reset();

			/// <summary>
			/// Ignora o número especificado de itens na sequência de enumeração.
			/// </summary>
			/// <param name="Param_QuantidadeSkip">O número de itens a serem ignorados.</param>
			CarenResult Skip(UInt32 Param_QuantidadeSkip);
		};

		/// <summary>
		/// (IPropertyBag2) - Interface responsável por fornecer um objeto com um saco de propriedade no qual o objeto pode salvar suas propriedades persistentemente.
		/// </summary>
		[CategoryAttribute("Windows Interface")]
		[Guid("D0E858B7-EFE8-4E6C-9EA5-536DD603A8AB")]
		public interface class ICarenPropertyBag2 : ICaren
		{
			/// <summary>
			/// Propriedade que define se a classe foi descartada.
			/// </summary>
			property Boolean DisposedClasse
			{
				virtual Boolean get();
			}



			//Métodos

			/// <summary>
			/// (CountProperties) - Obtém o número de propriedades no saco da propriedade.
			/// </summary>
			/// <param name="Param_Out_Quantidade"></param>
			CarenResult ObterQuantidadePropriedades([Out] UInt32% Param_Out_Quantidade);

			/// <summary>
			/// (GetPropertyInfo) - Obtém informações para propriedades em um saco de propriedade sem realmente obter essas propriedades. 
			/// </summary>
			/// <param name="Param_ID"></param>
			/// <param name="Param_Quantidade"></param>
			/// <param name="Param_Out_ArrayPropBags"></param>
			/// <param name="Param_Out_Quantiade"></param>
			CarenResult ObterInfoPropriedades(
				UInt32 Param_ID,
				UInt32 Param_Quantidade,
				[Out] cli::array<Estruturas::CA_PROPBAG2^>^% Param_Out_ArrayPropBags,
				[Out] UInt32% Param_Out_Quantiade);


			/// <summary>
			/// (LoadObject) - Faz com que o saco de propriedade instrua um objeto de propriedade que foi criado anteriormente e inicializado para ler suas propriedades persistentes. 
			/// </summary>
			/// <param name="Param_EnderecoNome"></param>
			/// <param name="Param_Hint"></param>
			/// <param name="Param_UnkObjeto"></param>
			/// <param name="Param_Ref_ErrorLog"></param>
			CarenResult CarregarObjeto(
				String^ Param_EnderecoNome,
				UInt32 Param_Hint,
				ICaren^ Param_UnkObjeto,
				ICaren^% Param_Ref_ErrorLog);

			/// <summary>
			///  (Read) - Faz com que uma ou mais propriedades sejam lidas do saco de propriedade.
			/// </summary>
			/// <param name="Param_Quantidade"></param>
			/// <param name="Param_ArrayPropBagsRequest"></param>
			/// <param name="Param_InterfaceErro"></param>
			/// <param name="Param_Out_VarValue"></param>
			/// <param name="Param_Out_HRESULTArray"></param>
			CarenResult Ler(
				UInt32 Param_Quantidade,
				cli::array<Estruturas::CA_PROPBAG2^>^ Param_ArrayPropBagsRequest,
				ICaren^ Param_InterfaceErro,
				[Out] cli::array<Estruturas::CA_VARIANT^>^% Param_Out_VarValue,
				[Out] cli::array<Int32>^% Param_Out_HRESULTArray);

			/// <summary>
			/// (Write) - Faz com que uma ou mais propriedades sejam salvas no saco da propriedade.
			/// </summary>
			/// <param name="Param_Quantidade"></param>
			/// <param name="Param_ArrayPropBagsRequest"></param>
			/// <param name="Param_VarValue"></param>
			CarenResult Escrever(
				UInt32 Param_Quantidade,
				cli::array<Estruturas::CA_PROPBAG2^>^ Param_ArrayPropBagsRequest,
				cli::array<Estruturas::CA_VARIANT^>^% Param_VarValue);
		};
	}
}