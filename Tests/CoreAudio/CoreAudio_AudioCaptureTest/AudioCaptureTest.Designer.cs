
namespace CoreAudio_AudioCaptureTest
{
    partial class AudioCaptureTest
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.Cbx_ListCaptureAudioDevices = new System.Windows.Forms.ComboBox();
            this.Btn_StartCapture = new System.Windows.Forms.Button();
            this.Label2 = new System.Windows.Forms.Label();
            this.Txb_UrlOutputFile = new System.Windows.Forms.TextBox();
            this.Btn_StopCapture = new System.Windows.Forms.Button();
            this.Btn_ListarDispositivos = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 4);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(148, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "Dispositivo Captura Áudio:";
            // 
            // Cbx_ListCaptureAudioDevices
            // 
            this.Cbx_ListCaptureAudioDevices.FormattingEnabled = true;
            this.Cbx_ListCaptureAudioDevices.Location = new System.Drawing.Point(12, 22);
            this.Cbx_ListCaptureAudioDevices.Name = "Cbx_ListCaptureAudioDevices";
            this.Cbx_ListCaptureAudioDevices.Size = new System.Drawing.Size(418, 23);
            this.Cbx_ListCaptureAudioDevices.TabIndex = 2;
            // 
            // Btn_StartCapture
            // 
            this.Btn_StartCapture.Location = new System.Drawing.Point(12, 159);
            this.Btn_StartCapture.Name = "Btn_StartCapture";
            this.Btn_StartCapture.Size = new System.Drawing.Size(94, 35);
            this.Btn_StartCapture.TabIndex = 3;
            this.Btn_StartCapture.Text = "Capturar";
            this.Btn_StartCapture.UseVisualStyleBackColor = true;
            this.Btn_StartCapture.Click += new System.EventHandler(this.Btn_StartCapture_Click);
            // 
            // Label2
            // 
            this.Label2.AutoSize = true;
            this.Label2.Location = new System.Drawing.Point(13, 91);
            this.Label2.Name = "Label2";
            this.Label2.Size = new System.Drawing.Size(98, 15);
            this.Label2.TabIndex = 5;
            this.Label2.Text = "Arquivo de saida:";
            // 
            // Txb_UrlOutputFile
            // 
            this.Txb_UrlOutputFile.Location = new System.Drawing.Point(13, 109);
            this.Txb_UrlOutputFile.Multiline = true;
            this.Txb_UrlOutputFile.Name = "Txb_UrlOutputFile";
            this.Txb_UrlOutputFile.PlaceholderText = "URL DA PASTA DE SAIDA";
            this.Txb_UrlOutputFile.Size = new System.Drawing.Size(417, 44);
            this.Txb_UrlOutputFile.TabIndex = 6;
            this.Txb_UrlOutputFile.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Btn_StopCapture
            // 
            this.Btn_StopCapture.Location = new System.Drawing.Point(112, 159);
            this.Btn_StopCapture.Name = "Btn_StopCapture";
            this.Btn_StopCapture.Size = new System.Drawing.Size(94, 35);
            this.Btn_StopCapture.TabIndex = 7;
            this.Btn_StopCapture.Text = "Parar";
            this.Btn_StopCapture.UseVisualStyleBackColor = true;
            this.Btn_StopCapture.Click += new System.EventHandler(this.Btn_StopCapture_Click);
            // 
            // Btn_ListarDispositivos
            // 
            this.Btn_ListarDispositivos.Location = new System.Drawing.Point(313, 51);
            this.Btn_ListarDispositivos.Name = "Btn_ListarDispositivos";
            this.Btn_ListarDispositivos.Size = new System.Drawing.Size(117, 35);
            this.Btn_ListarDispositivos.TabIndex = 8;
            this.Btn_ListarDispositivos.Text = "Listar Dispositivos";
            this.Btn_ListarDispositivos.UseVisualStyleBackColor = true;
            this.Btn_ListarDispositivos.Click += new System.EventHandler(this.Btn_ListarDispositivos_Click);
            // 
            // AudioCaptureTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(442, 206);
            this.Controls.Add(this.Btn_ListarDispositivos);
            this.Controls.Add(this.Btn_StopCapture);
            this.Controls.Add(this.Txb_UrlOutputFile);
            this.Controls.Add(this.Label2);
            this.Controls.Add(this.Btn_StartCapture);
            this.Controls.Add(this.Cbx_ListCaptureAudioDevices);
            this.Controls.Add(this.label1);
            this.Name = "AudioCaptureTest";
            this.Text = "Audio Capture Test";
            this.Load += new System.EventHandler(this.AudioCaptureTest_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox Cbx_ListCaptureAudioDevices;
        private System.Windows.Forms.Button Btn_StartCapture;
        private System.Windows.Forms.Label Label2;
        private System.Windows.Forms.TextBox Txb_UrlOutputFile;
        private System.Windows.Forms.Button Btn_StopCapture;
        private System.Windows.Forms.Button Btn_ListarDispositivos;
    }
}

