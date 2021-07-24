
namespace WebCamCapture
{
    partial class WebCamCapture
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
            this.Btn_ListarDevices = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.Btn_Start = new System.Windows.Forms.Button();
            this.Btn_Parar = new System.Windows.Forms.Button();
            this.Cbx_ListaWebCams = new System.Windows.Forms.ComboBox();
            this.Pct_SuperficeVideo = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.Pct_SuperficeVideo)).BeginInit();
            this.SuspendLayout();
            // 
            // Btn_ListarDevices
            // 
            this.Btn_ListarDevices.Location = new System.Drawing.Point(467, 29);
            this.Btn_ListarDevices.Name = "Btn_ListarDevices";
            this.Btn_ListarDevices.Size = new System.Drawing.Size(110, 23);
            this.Btn_ListarDevices.TabIndex = 0;
            this.Btn_ListarDevices.Text = "Listar Devices";
            this.Btn_ListarDevices.UseVisualStyleBackColor = true;
            this.Btn_ListarDevices.Click += new System.EventHandler(this.Btn_ListarDevices_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(144, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Dispositivo de Captura:";
            // 
            // Btn_Start
            // 
            this.Btn_Start.Location = new System.Drawing.Point(583, 29);
            this.Btn_Start.Name = "Btn_Start";
            this.Btn_Start.Size = new System.Drawing.Size(110, 23);
            this.Btn_Start.TabIndex = 2;
            this.Btn_Start.Text = "Iniciar";
            this.Btn_Start.UseVisualStyleBackColor = true;
            this.Btn_Start.Click += new System.EventHandler(this.Btn_Start_Click);
            // 
            // Btn_Parar
            // 
            this.Btn_Parar.Location = new System.Drawing.Point(699, 29);
            this.Btn_Parar.Name = "Btn_Parar";
            this.Btn_Parar.Size = new System.Drawing.Size(110, 23);
            this.Btn_Parar.TabIndex = 3;
            this.Btn_Parar.Text = "Parar";
            this.Btn_Parar.UseVisualStyleBackColor = true;
            this.Btn_Parar.Click += new System.EventHandler(this.Btn_Parar_Click);
            // 
            // Cbx_ListaWebCams
            // 
            this.Cbx_ListaWebCams.FormattingEnabled = true;
            this.Cbx_ListaWebCams.Location = new System.Drawing.Point(12, 29);
            this.Cbx_ListaWebCams.Name = "Cbx_ListaWebCams";
            this.Cbx_ListaWebCams.Size = new System.Drawing.Size(449, 25);
            this.Cbx_ListaWebCams.TabIndex = 4;
            // 
            // Pct_SuperficeVideo
            // 
            this.Pct_SuperficeVideo.BackColor = System.Drawing.Color.Black;
            this.Pct_SuperficeVideo.Location = new System.Drawing.Point(12, 60);
            this.Pct_SuperficeVideo.Name = "Pct_SuperficeVideo";
            this.Pct_SuperficeVideo.Size = new System.Drawing.Size(797, 378);
            this.Pct_SuperficeVideo.TabIndex = 5;
            this.Pct_SuperficeVideo.TabStop = false;
            // 
            // WebCamCapture
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(811, 450);
            this.Controls.Add(this.Pct_SuperficeVideo);
            this.Controls.Add(this.Cbx_ListaWebCams);
            this.Controls.Add(this.Btn_Parar);
            this.Controls.Add(this.Btn_Start);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Btn_ListarDevices);
            this.Name = "WebCamCapture";
            this.Text = "WebCam Capture";
            this.Load += new System.EventHandler(this.WebCamCapture_Load);
            ((System.ComponentModel.ISupportInitialize)(this.Pct_SuperficeVideo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Btn_ListarDevices;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Btn_Start;
        private System.Windows.Forms.Button Btn_Parar;
        private System.Windows.Forms.ComboBox Cbx_ListaWebCams;
        private System.Windows.Forms.PictureBox Pct_SuperficeVideo;
    }
}

