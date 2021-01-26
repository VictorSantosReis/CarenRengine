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
#include "../SDK_Base.h"
#include "../SDK_Caren.h"
#include "../SDK_Windows.h"

//Importa o namespace base.
namespace CarenRengine
{

	/// <summary>
	/// Classe responsável pela conversão da estrutura (PROPVARIANT) entre suas representações NATIVA e GERENCIADA.
	/// </summary>
	public ref class PropVariantManager
	{

		//Construtor & Destruidor da classe.
	public:
		PropVariantManager() {}
		~PropVariantManager() {}


		//Métodos auxiliares.
	private:
		//Cria um Guid a parti de uma determinada String.
		_GUID CreateGuidFromString(String^ Param_DadosGuid);

		//Converte um determinado GUID para uma representação de String gerenciada.
		String^ CreateStringFromGuid(_GUID Param_Guid);

		//Função que copia dados da memoria de um buffer para outro de destino.
		template<typename T>
		errno_t CopiarMemoria(T* Param_BufferDestino, unsigned int Param_SizeBufferDestino, T* Param_BufferOrigem, unsigned int Param_QuantidadeElementos)
		{
			//Realiza a copia da memoria.
			return memcpy_s(Param_BufferDestino, Param_SizeBufferDestino, Param_BufferOrigem, Param_QuantidadeElementos * sizeof(T));
		}

		//(MÉTODO EXPERIMENTAL)
		template<typename TipoArrayNativo, typename TipoArrayGerenciado>
		void CopiarBufferNativoToGerenciado(TipoArrayNativo** Param_Buffer, cli::array<TipoArrayGerenciado>^% Param_BufferGerenciado, UINT32 Param_TamanhoBuffer)
		{
			//Cria um pin para o buffer gerenciado.
			pin_ptr<TipoArrayGerenciado> PinToIndexZeroBuffer = &Param_BufferGerenciado[0];

			//Converte o pinptr para um buffer do tipo de destino.
			TipoArrayNativo* pBufferDestino = reinterpret_cast<TipoArrayNativo*>(PinToIndexZeroBuffer);

			//Verifica se é valido
			if (!ObjetoValido(pBufferDestino))
				throw gcnew NullReferenceException("(CopiarBufferNativoToGerenciado) - Houve uma falha ao criar uma ligação para o buffer de destino gerenciado através do (pin_ptr).");

			//Copia os dados do nativo para o gerenciado.
			std::copy(*Param_Buffer, (*Param_Buffer) + Param_TamanhoBuffer, pBufferDestino);
		}

		//(MÉTODO EXPERIMENTAL)
		template<typename TipoArrayNativo, typename TipoArrayGerenciado>
		void CopiarBufferGerenciadoToNativo(cli::array<TipoArrayGerenciado>^% Param_BufferGerenciado, TipoArrayNativo* Param_BufferDestino, UINT32 Param_TamanhoBuffer)
		{
			//Cria um pin para o buffer gerenciado.
			pin_ptr<TipoArrayGerenciado> PinToIndexZeroBuffer = &Param_BufferGerenciado[0];

			//Converte o pinptr para o buffer de origem.
			TipoArrayNativo* pBufferOrigem = reinterpret_cast<TipoArrayNativo*>(PinToIndexZeroBuffer);

			//Verifica se é valido
			if (!ObjetoValido(pBufferOrigem))
				throw gcnew NullReferenceException("(CopiarBufferGerenciadoToNativo) - Houve uma falha ao criar uma ligação para o buffer de origem gerenciado através do (pin_ptr).");

			//Copia os dados do nativo para o gerenciado.
			std::copy(pBufferOrigem, (pBufferOrigem)+Param_TamanhoBuffer, Param_BufferDestino);
		}

		//Métodos
	public:
		/// <summary>
		/// Método responsável por converter uma estrutura (CA_PROPVARIANT) GERENCIADA em sua representação NATIVA.
		/// Retorna NULO se a conversão não for suportada ou algum valor necessário for invalido.
		/// Chame PropVariantClear quando não for mais utilizar a estrutura.
		/// </summary>
		/// <param name="Param_Estrutura">A estrutura GERENCIADA a ser convertida.</param>
		/// <returns>Retorna um ponteiro para a estrutura nativa PROPVARIANT.</returns>
		PVOID ConverterPropVariantManaged_ToUnmanaged(CA_PROPVARIANT^ Param_Estrutura);

		/// <summary>
		/// Método responsável por converter uma estrutura (PROPVARIANT) NATIVA em sua representação GERENCIADA.
		/// Retorna NULO se a conversão não for suportada ou algum valor necessário for invalido.
		/// </summary>
		/// <param name="Param_Estrutura">A estrutura NATIVA  ser convertida.</param>
		/// <returns></returns>
		CA_PROPVARIANT^ ConverterPropVariantUnmanaged_ToManaged(PROPVARIANT* Param_Estrutura);
	};

}