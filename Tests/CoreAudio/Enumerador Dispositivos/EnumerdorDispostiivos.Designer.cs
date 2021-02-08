
namespace CoreAudio_EnumeradorDispositivos
{
    partial class EnumerdorDispostiivos
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
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.Btn_EnumRenderAudio = new System.Windows.Forms.Button();
            this.Btn_EnumCaptureAudio = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(12, 33);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(306, 23);
            this.comboBox1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(181, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "Dispositivos Renderização Audio:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 86);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(169, 15);
            this.label2.TabIndex = 3;
            this.label2.Text = "Dispositivos de Captura Áudio:";
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(12, 107);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(306, 23);
            this.comboBox2.TabIndex = 2;
            // 
            // Btn_EnumRenderAudio
            // 
            this.Btn_EnumRenderAudio.Location = new System.Drawing.Point(334, 33);
            this.Btn_EnumRenderAudio.Name = "Btn_EnumRenderAudio";
            this.Btn_EnumRenderAudio.Size = new System.Drawing.Size(146, 23);
            this.Btn_EnumRenderAudio.TabIndex = 4;
            this.Btn_EnumRenderAudio.Text = "Enumerar Dispositivos";
            this.Btn_EnumRenderAudio.UseVisualStyleBackColor = true;
            this.Btn_EnumRenderAudio.Click += new System.EventHandler(this.Btn_EnumRenderAudio_Click);
            // 
            // Btn_EnumCaptureAudio
            // 
            this.Btn_EnumCaptureAudio.Location = new System.Drawing.Point(334, 107);
            this.Btn_EnumCaptureAudio.Name = "Btn_EnumCaptureAudio";
            this.Btn_EnumCaptureAudio.Size = new System.Drawing.Size(146, 23);
            this.Btn_EnumCaptureAudio.TabIndex = 5;
            this.Btn_EnumCaptureAudio.Text = "Enumerar Dispositivos";
            this.Btn_EnumCaptureAudio.UseVisualStyleBackColor = true;
            this.Btn_EnumCaptureAudio.Click += new System.EventHandler(this.Btn_EnumCaptureAudio_Click);
            // 
            // EnumerdorDispostiivos
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(508, 146);
            this.Controls.Add(this.Btn_EnumCaptureAudio);
            this.Controls.Add(this.Btn_EnumRenderAudio);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBox1);
            this.Name = "EnumerdorDispostiivos";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.EnumerdorDispostiivos_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Button Btn_EnumRenderAudio;
        private System.Windows.Forms.Button Btn_EnumCaptureAudio;
    }
}

