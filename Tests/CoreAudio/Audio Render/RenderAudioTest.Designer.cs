namespace CoreAudio_RenderAudioTest
{
    partial class RenderAudioTest
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
            this.Btn_PlayMusic = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.Txb_UrlMusic = new System.Windows.Forms.TextBox();
            this.TrackVolumeMusic = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.TrackVolumeMusic)).BeginInit();
            this.SuspendLayout();
            // 
            // Btn_PlayMusic
            // 
            this.Btn_PlayMusic.Location = new System.Drawing.Point(358, 61);
            this.Btn_PlayMusic.Name = "Btn_PlayMusic";
            this.Btn_PlayMusic.Size = new System.Drawing.Size(75, 45);
            this.Btn_PlayMusic.TabIndex = 0;
            this.Btn_PlayMusic.Text = "Play";
            this.Btn_PlayMusic.UseVisualStyleBackColor = true;
            this.Btn_PlayMusic.Click += new System.EventHandler(this.Btn_PlayMusic_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(85, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "Url do arquivo:";
            // 
            // Txb_UrlMusic
            // 
            this.Txb_UrlMusic.Location = new System.Drawing.Point(12, 27);
            this.Txb_UrlMusic.Multiline = true;
            this.Txb_UrlMusic.Name = "Txb_UrlMusic";
            this.Txb_UrlMusic.PlaceholderText = "URL ";
            this.Txb_UrlMusic.Size = new System.Drawing.Size(421, 28);
            this.Txb_UrlMusic.TabIndex = 2;
            this.Txb_UrlMusic.Text = "C:\\Users\\Victo\\Music\\Jacob Lee - Ghost.mp3";
            this.Txb_UrlMusic.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // TrackVolumeMusic
            // 
            this.TrackVolumeMusic.Location = new System.Drawing.Point(12, 61);
            this.TrackVolumeMusic.Name = "TrackVolumeMusic";
            this.TrackVolumeMusic.Size = new System.Drawing.Size(340, 45);
            this.TrackVolumeMusic.TabIndex = 3;
            this.TrackVolumeMusic.Value = 5;
            this.TrackVolumeMusic.ValueChanged += new System.EventHandler(this.TrackVolumeMusic_ValueChanged);
            // 
            // RenderAudioTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(445, 113);
            this.Controls.Add(this.TrackVolumeMusic);
            this.Controls.Add(this.Txb_UrlMusic);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Btn_PlayMusic);
            this.Name = "RenderAudioTest";
            this.Text = "Render Audio Test";
            ((System.ComponentModel.ISupportInitialize)(this.TrackVolumeMusic)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Btn_PlayMusic;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Txb_UrlMusic;
        private System.Windows.Forms.TrackBar TrackVolumeMusic;
    }
}

