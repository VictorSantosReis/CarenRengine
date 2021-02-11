using System;
using System.IO;

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

//Importa o SDK do Windows.
using CarenRengine.Windows;

namespace Transcode_Dll
{
    /// <summary>
    /// Classe responsável por demonstrar o funcionamento da API de transcodificação da Media Foundation.
    /// </summary>
    public class MFTTranscodeApi : IDisposable
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
            /// Interface que contém os atributos do SinkWriter.
            /// </summary>
            public ICarenMFAttributes AtributosEscritor { get; set; }

            /// <summary>
            /// Interface que vai conter o tipo de dados de áudio no fluxo encodificado.
            /// </summary>
            public ICarenMFMediaType TypeOutputStreamAudioMPEG4 { get; set; }

            /// <summary>
            /// Interface para o tipo da midia de entrada a ser convertida.
            /// </summary>
            public ICarenMFMediaType TypeInput { get; set; }

            /// <summary>
            /// Interface que contém o ponteiro para o fluxo que vai receber os dados convertidos.
            /// </summary>
            public ICarenStream StreamToFile { get; set; }

            /// <summary>
            /// O fluxo da Media Foundation que encapsula o ICarenStream que será gerenciado pelo encodificador.
            /// </summary>
            public ICarenMFByteStream MFByteStream { get; set; }

            /// <summary>
            /// Estrutura que contém informações para o arquivo de áudio de entrada.
            /// </summary>
            public CA_WAVEFORMATEXEXTENSIBLE InputWavFormat { get; set; }
        }
        #endregion

        #region Enumeracoes
        public enum AudioEncoders
        {
            /// <summary>
            /// Os dados de entrada seram codificados para um arquivo ou fluxo MP3
            /// </summary>
            MP3 = 1,

            /// <summary>
            /// Os dados de entrada seram codificados para um arquivo ou fluxo AAC
            /// </summary>
            AAC
        }
        #endregion

        #region Variaveis
        private MyTranscodeInfo myTranscodeApi = new MyTranscodeInfo();
        MediaFoundationFunctions MFTFuncs = new MediaFoundationFunctions();
        #endregion



        #region Construtores
        /// <summary>
        /// Inicializa a classe de transcodificação passando diretamente o Encodificador que vai processar os dados de entrada para gerar o arquivo
        /// de saida.
        /// </summary>
        /// <param name="Param_EncoderSaida">Uma interface ICarenMFMediaSink para o Sink/Encoder do tipo de áudio de saida. Consulte os métodos das class MediaFoundationFunctions para obter
        /// um encodificador.</param>
        /// <param name="Param_AudioFormatoEntrada">Estrutura que contém as informações do tipo de áudio de entrada a ser convertido.</param>
        public MFTTranscodeApi(AudioEncoders Param_AudioEncoderOutput, String Param_UrlOutputFile, CA_WAVEFORMATEXEXTENSIBLE Param_AudioFormatoEntrada)
        {
            //Variavel que vai conter os resultados das operações.
            CarenResult Resultado = new(ResultCode.ER_FAIL, false);

            //Converte a estrutura com o formato de áudio de entrada em uma interface ICarenMFMediaType.
            Resultado = MFTFuncs._MFInitMediaTypeFromWaveFormatEx(ref Param_AudioFormatoEntrada, Param_AudioFormatoEntrada.TamanhoEstrutura, myTranscodeApi.TypeInput = new CarenMFMediaType(false));

            //Verifica se não houve erro.
            if(Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Ocorreu uma falha..

                //Chama uma exceção.
                throw new Exception($"Ocorreu uma falha ao tentar converter a estrutura (CA_WAVEFORMATEXEXTENSIBLE). Code({Resultado.StatusCode.ToString()}) - Mensagem de erro > " + Resultado.ObterMensagem(Resultado.HResult));
            }

            //Chama a função para deletar o arquivo se já existir.
            File.Delete(Param_UrlOutputFile);

            //Cria o fluxo para o arquivo de saida a receber os dados codificados.
            myTranscodeApi.StreamToFile = new CarenStream(Param_UrlOutputFile, CA_STGMs.CA_STGM_READWRITE, CA_FILE_ATTRIBUTES.CA_FILE_ATTRIBUTE_NORMAL, true);

            //Cria o fluxo da Media Foundation com base no fluxo criado anteriormente.
            myTranscodeApi.MFByteStream = new CarenMFByteStream(myTranscodeApi.StreamToFile);

            //Verifica qual o tipo do encodificador selecionado pelo usuário e cria.
            switch (Param_AudioEncoderOutput)
            {
                case AudioEncoders.MP3:
                    {
                        //Chama o método para criar o dissipador de mídia escolhido pelo usuário.
                        Resultado = MFTFuncs._MFCreateMP3MediaSink(myTranscodeApi.MFByteStream, myTranscodeApi.Encoder = new CarenMFMediaSink());

                        //Verifica se não houve erro.
                        if (Resultado.StatusCode != ResultCode.SS_OK)
                        {
                            //Ocorreu uma falha..

                            //Chama uma exceção.
                            throw new Exception($"Ocorreu uma falha ao tentar criado o encodificador de dados. Code({Resultado.StatusCode.ToString()}) - Mensagem de erro > " + Resultado.ObterMensagem(Resultado.HResult));
                        }

                        //Chama o método para criar o escritor com o encodificador inicializado.
                        myTranscodeApi.Escritor = new CarenMFSinkWriter(myTranscodeApi.Encoder, null);

                        //Define o tipo de mídia de entrada.
                        Resultado = myTranscodeApi.Escritor.SetInputMediaType(0, myTranscodeApi.TypeInput, null);

                        //Verifica se não houve erro.
                        if (Resultado.StatusCode != ResultCode.SS_OK)
                        {
                            //Ocorreu uma falha..

                            //Chama uma exceção.
                            throw new Exception($"Ocorreu uma falha ao definir o tipo de mídia de entrada. Code({Resultado.StatusCode.ToString()}) - Mensagem de erro > " + Resultado.ObterMensagem(Resultado.HResult));
                        }
                    }
                    break;
                case AudioEncoders.AAC:
                    {
                        //Cria a interface do tipo de mídia que vai conter no arquivo.
                        myTranscodeApi.TypeOutputStreamAudioMPEG4 = new CarenMFMediaType(true);

                        //Define os atributos para o tipo encodificado.
                        myTranscodeApi.TypeOutputStreamAudioMPEG4.SetGUID(GUIDs_MF_MEDIATYPE_ATTRIBUTES.MF_MT_MAJOR_TYPE, GUIDs_MFAttributes_MAJOR_TYPES.MFMediaType_Audio);
                        myTranscodeApi.TypeOutputStreamAudioMPEG4.SetGUID(GUIDs_MF_MEDIATYPE_ATTRIBUTES.MF_MT_SUBTYPE, GUIDs_MF_AUDIO_SUBTYPES.MFAudioFormat_AAC);
                        myTranscodeApi.TypeOutputStreamAudioMPEG4.SetUINT32(GUIDs_MF_MEDIATYPE_ATTRIBUTES.MF_MT_AUDIO_BITS_PER_SAMPLE, Param_AudioFormatoEntrada.Format.wBitsPerSample);
                        myTranscodeApi.TypeOutputStreamAudioMPEG4.SetUINT32(GUIDs_MF_MEDIATYPE_ATTRIBUTES.MF_MT_AUDIO_SAMPLES_PER_SECOND, Param_AudioFormatoEntrada.Format.nSamplesPerSec);
                        myTranscodeApi.TypeOutputStreamAudioMPEG4.SetUINT32(GUIDs_MF_MEDIATYPE_ATTRIBUTES.MF_MT_AUDIO_NUM_CHANNELS, Param_AudioFormatoEntrada.Format.nChannels);
                        myTranscodeApi.TypeOutputStreamAudioMPEG4.SetUINT32(GUIDs_MF_MEDIATYPE_ATTRIBUTES.MF_MT_AUDIO_AVG_BYTES_PER_SECOND, 12000);
                        myTranscodeApi.TypeOutputStreamAudioMPEG4.SetUINT32(GUIDs_MF_MEDIATYPE_ATTRIBUTES.MF_MT_AAC_PAYLOAD_TYPE, 0);
                        myTranscodeApi.TypeOutputStreamAudioMPEG4.SetUINT32(GUIDs_MF_MEDIATYPE_ATTRIBUTES.MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION, (uint)CA_AUDIO_AAC_PROFILE_LEVEL_INDICATION.PerfilAAC_L2); //Perfil AAC
                        
                        //Chama o método para criar o dissipador de mídia escolhido pelo usuário.
                        Resultado = MFTFuncs._MFCreateMPEG4MediaSink(myTranscodeApi.MFByteStream, null, myTranscodeApi.TypeOutputStreamAudioMPEG4, myTranscodeApi.Encoder = new CarenMFMediaSink());

                        //Verifica se não houve erro.
                        if (Resultado.StatusCode != ResultCode.SS_OK)
                        {
                            //Ocorreu uma falha..

                            //Chama uma exceção.
                            throw new Exception($"Ocorreu uma falha ao tentar criado o encodificador de dados. Code({Resultado.StatusCode.ToString()}) - Mensagem de erro > " + Resultado.ObterMensagem(Resultado.HResult));
                        }

                        //Cria os atributos para o escritor.
                        myTranscodeApi.AtributosEscritor = new CarenMFAttributes(2);

                        //Define os atributos.
                        myTranscodeApi.AtributosEscritor.SetUINT32(GUIDs_MFAtributos_SinkWriter.MF_READWRITE_DISABLE_CONVERTERS, 0); //0 - HABILITA CONVERSOES.
                        myTranscodeApi.AtributosEscritor.SetGUID(GUIDs_MFAtributos_SinkWriter.MF_TRANSCODE_CONTAINERTYPE, GUIDs_MFTranscodeContainerType.TranscodeContainerType_MPEG4); //Container.

                        //Chama o método para criar o escritor com o encodificador inicializado.
                        myTranscodeApi.Escritor = new CarenMFSinkWriter(myTranscodeApi.Encoder, myTranscodeApi.AtributosEscritor);

                        //Define o tipo de mídia de entrada.
                        Resultado = myTranscodeApi.Escritor.SetInputMediaType(0, myTranscodeApi.TypeInput, null);

                        //Verifica se não houve erro.
                        if (Resultado.StatusCode != ResultCode.SS_OK)
                        {
                            //Ocorreu uma falha..

                            //Chama uma exceção.
                            throw new Exception($"Ocorreu uma falha ao definir o tipo de mídia de entrada. Code({Resultado.StatusCode.ToString()}) - Mensagem de erro > " + Resultado.ObterMensagem(Resultado.HResult));
                        }
                    }
                    break;

                default:
                    throw new Exception("Nenhum encodificador disponivel para o tipo de audio de saida escolhido.");
            }

        }
        #endregion

        #region Métodos
        /// <summary>
        /// Método responsável por inicializar o escritor de dados.
        /// </summary>
        /// <returns></returns>
        public CarenResult Inicializar()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new(ResultCode.ER_FAIL, false);

            //Chama o método para iniciar o escritor de amostras.
            Resultado = myTranscodeApi.Escritor.BeginWriting();

            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Chama o método para finalizar todas as operações.
        /// </summary>
        /// <returns></returns>
        public CarenResult Finalizar()
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new(ResultCode.ER_FAIL, false);

            //Chama o método para finalizar o escritor de dados e concluir todas as operações necessárias no arquivo final.
            Resultado = myTranscodeApi.Escritor._Finalize();

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Chama uma exceção.
                throw new Exception($"Não foi possivel finalizar o escritor de dados. Code({Resultado.StatusCode.ToString()}) - Mensagem de erro > " + Resultado.ObterMensagem(Resultado.HResult));
            }

            //Desliga o Media Sink(Encoder).
            Resultado = myTranscodeApi.Encoder.Shutdown();

            //Verifica se não houve erro
            if (Resultado.StatusCode != ResultCode.SS_OK)
            {
                //Chama uma exceção.
                throw new Exception($"Ocorreu uma falha ao tentar desligar o Media Sink responsável pela encodificação. Code({Resultado.StatusCode.ToString()}) - Mensagem de erro > " + Resultado.ObterMensagem(Resultado.HResult));
            }

            //Retorna o resultado.
            return Resultado;
        }

        /// <summary>
        /// Envia uma amostra descompactada de dados para ser encodificada.
        /// </summary>
        /// <param name="Param_AmostraDados">A interface para a amostra de mídia. A interface deve conter no mínimo os atributos base de cada codec.</param>
        /// <returns></returns>
        public CarenResult EnviarAmostrar(ICarenMFSample Param_AmostraDados)
        {
            //Variavel a ser retornada.
            CarenResult Resultado = new(ResultCode.ER_FAIL, false);

            //Chama o método para iniciar o escritor de amostras.
            Resultado = myTranscodeApi.Escritor.WriteSample(0, Param_AmostraDados);

            //Retorna o resultado.
            return Resultado;
        }

        public void Dispose()
        {
            //Libera as interfaces utilizadas pela classe.
            SafeReleaseInterface(myTranscodeApi.TypeOutputStreamAudioMPEG4);
            SafeReleaseInterface(myTranscodeApi.Encoder);
            SafeReleaseInterface(myTranscodeApi.AtributosEscritor);
            SafeReleaseInterface(myTranscodeApi.Escritor);
            SafeReleaseInterface(myTranscodeApi.TypeInput);
            SafeReleaseInterface(myTranscodeApi.MFByteStream);
            SafeReleaseInterface(myTranscodeApi.StreamToFile);
            MFTFuncs = null;
            myTranscodeApi.InputWavFormat = null;

            //Chama o GC.
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
        }
        #endregion

        #region Utilidades
        public void SafeReleaseInterface(ICaren Param_Base)
        {
            //Verifica se a interface é valida.
            if (Param_Base is not null)
            {
                //Verifica se é valido e libera o ponteiro.
                if (Param_Base.StatusPonteiro().StatusCode == ResultCode.SS_OK)
                    Param_Base.LiberarReferencia();

                //Chama o finalizador.
                Param_Base.Finalizar();
            }
        }
        #endregion

    }
}
