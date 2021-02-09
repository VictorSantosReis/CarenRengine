using System;

//Importa os namespaces base.
using CarenRengine;
using CarenRengine.SDKBase;
using CarenRengine.SDKBase.Constantes;
using CarenRengine.SDKBase.Enumeracoes;
using CarenRengine.SDKBase.Estruturas;
using CarenRengine.SDKBase.GUIDs;

//API de codigos de resultado.S
using CarenRengine.CarenCodesStatus;

//Importa o SDK da Media Foundation
using CarenRengine.MediaFoundation;



namespace Transcode_Dll
{
    /// <summary>
    /// Classe responsável por demonstrar o funcionamento da API de transcodificação da Media Foundation.
    /// </summary>
    public class MFTTranscodeApi
    {
        #region Estruturas
        private struct MyTranscodeInfo
        {
            /// <summary>
            /// Interface para o encodificador escolhido pelo usuário.
            /// </summary>
            public ICarenMFMediaSink Encoder { get; set; }

            /// <summary>
            /// Interface para o escritor responsável por escrever as amostras de entradas para o Encodificador escrever no arquivo final.
            /// </summary>
            public ICarenMFSinkWriter Escritor { get; set; }

            /// <summary>
            /// Interface para o tipo da midia de entrada a ser convertida.
            /// </summary>
            public ICarenMFMediaType TypeInput { get; set; }

            /// <summary>
            /// Estrutura que contém informações para o arquivo de áudio de entrada.
            /// </summary>
            public CA_WAVEFORMATEXEXTENSIBLE InputWavFormat { get; set; }

            /// <summary>
            /// String para url do arquivo de saida transcodificado.
            /// </summary>
            public String UrlArquivoFinal { get; set; }
        }
        #endregion

        #region Variaveis
        private MyTranscodeInfo myTranscodeApi = new MyTranscodeInfo();
        MediaFoundationFunctions MFTFuncs = new MediaFoundationFunctions();
        #endregion



        #region Construtores
        /// <summary>
        /// Inicializa a classe de transcodificação passando a URL para o arquivo de saida transcodificado.
        /// </summary>
        /// <param name="Param_UrlArquivoAudioSaida">A url para o arquivo transcodificado. O sistema seleciona o encodificador com base no mimetype/extensão do arquivo.</param>
        /// <param name="Param_AudioFormatoEntrada">Estrutura que contém as informações do tipo de áudio de entrada a ser convertido.</param>
        public MFTTranscodeApi(String Param_UrlArquivoAudioSaida, CA_WAVEFORMATEXEXTENSIBLE Param_AudioFormatoEntrada) 
        {
            //Define os dados na estrutura.
            myTranscodeApi.UrlArquivoFinal = Param_UrlArquivoAudioSaida;
            myTranscodeApi.InputWavFormat = Param_AudioFormatoEntrada;

            //Inicializa a classe de tipo de mídia que vai conter as informações do tipo de dados de entrada.
            myTranscodeApi.TypeInput = new CarenMFMediaType(false);

            //Chama o método para converter a estrutura Wav em uma interface de tipo de midia.
            MFTFuncs._MFInitMediaTypeFromWaveFormatEx(ref Param_AudioFormatoEntrada, myTranscodeApi.InputWavFormat.TamanhoEstrutura, myTranscodeApi.TypeInput);

            //Verifica se não houve falha
            if (myTranscodeApi.TypeInput.StatusPonteiro().StatusCode != ResultCode.SS_OK)
            {
                //Chama uma exeção.
                throw new Exception("Ocorreu uma falha ao converter a estrutura (CA_WAVEFORMATEXEXTENSIBLE) em uma interface de tipo de midia!");
            }

            //Chama o método para criar o escritor com base na url de saida.
            myTranscodeApi.Escritor = new CarenMFSinkWriter(myTranscodeApi.UrlArquivoFinal, null, null);
        }

        /// <summary>
        /// Inicializa a classe de transcodificação passando diretamente o Encodificador que vai processar os dados de entrada para gerar o arquivo
        /// de saida.
        /// </summary>
        /// <param name="Param_EncoderSaida">Uma interface ICarenMFMediaSink para o Sink/Encoder do tipo de áudio de saida. Consulte os métodos das class MediaFoundationFunctions para obter
        /// um encodificador.</param>
        /// <param name="Param_AudioFormatoEntrada">Estrutura que contém as informações do tipo de áudio de entrada a ser convertido.</param>
        public MFTTranscodeApi(ICarenMFMediaSink Param_EncoderSaida, CA_WAVEFORMATEXEXTENSIBLE Param_AudioFormatoEntrada) 
        {
            //Define os dados na estrutura.
            myTranscodeApi.Encoder = Param_EncoderSaida;
            myTranscodeApi.InputWavFormat = Param_AudioFormatoEntrada;

            //Inicializa a classe de tipo de mídia que vai conter as informações do tipo de dados de entrada.
            myTranscodeApi.TypeInput = new CarenMFMediaType(false);

            //Chama o método para converter a estrutura Wav em uma interface de tipo de midia.
            MFTFuncs._MFInitMediaTypeFromWaveFormatEx(ref Param_AudioFormatoEntrada, myTranscodeApi.InputWavFormat.TamanhoEstrutura, myTranscodeApi.TypeInput);

            //Verifica se não houve falha
            if (myTranscodeApi.TypeInput.StatusPonteiro().StatusCode != ResultCode.SS_OK)
            {
                //Chama uma exeção.
                throw new Exception("Ocorreu uma falha ao converter a estrutura (CA_WAVEFORMATEXEXTENSIBLE) em uma interface de tipo de midia!");
            }

            //Chama o método para criar o escritor com base na url de saida.
            myTranscodeApi.Escritor = new CarenMFSinkWriter(Param_EncoderSaida, null);

            //Adiciona referencia.
            Param_EncoderSaida.AdicionarReferencia();
        }
        #endregion
    }
}
