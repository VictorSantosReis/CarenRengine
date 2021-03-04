
namespace MediaSessionPlaybackTest
{
    partial class MediaSessionPlayback
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
            this.PanelRender = new System.Windows.Forms.Panel();
            this.PanelControlPlayback = new System.Windows.Forms.Panel();
            this.Btn_Stop = new System.Windows.Forms.Button();
            this.Btn_Pause = new System.Windows.Forms.Button();
            this.TrackBarVolume = new System.Windows.Forms.TrackBar();
            this.Btn_Start = new System.Windows.Forms.Button();
            this.Txb_Url = new System.Windows.Forms.TextBox();
            this.Btn_Back = new System.Windows.Forms.Button();
            this.Btn_Advance = new System.Windows.Forms.Button();
            this.PanelRender.SuspendLayout();
            this.PanelControlPlayback.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TrackBarVolume)).BeginInit();
            this.SuspendLayout();
            // 
            // PanelRender
            // 
            this.PanelRender.BackColor = System.Drawing.Color.Black;
            this.PanelRender.Controls.Add(this.PanelControlPlayback);
            this.PanelRender.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PanelRender.Location = new System.Drawing.Point(0, 0);
            this.PanelRender.Name = "PanelRender";
            this.PanelRender.Size = new System.Drawing.Size(1075, 672);
            this.PanelRender.TabIndex = 0;
            this.PanelRender.SizeChanged += new System.EventHandler(this.PanelRender_SizeChanged);
            this.PanelRender.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.PanelRender_MouseDoubleClick);
            // 
            // PanelControlPlayback
            // 
            this.PanelControlPlayback.BackColor = System.Drawing.Color.White;
            this.PanelControlPlayback.Controls.Add(this.Btn_Advance);
            this.PanelControlPlayback.Controls.Add(this.Btn_Back);
            this.PanelControlPlayback.Controls.Add(this.Btn_Stop);
            this.PanelControlPlayback.Controls.Add(this.Btn_Pause);
            this.PanelControlPlayback.Controls.Add(this.TrackBarVolume);
            this.PanelControlPlayback.Controls.Add(this.Btn_Start);
            this.PanelControlPlayback.Controls.Add(this.Txb_Url);
            this.PanelControlPlayback.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.PanelControlPlayback.Location = new System.Drawing.Point(0, 596);
            this.PanelControlPlayback.Name = "PanelControlPlayback";
            this.PanelControlPlayback.Size = new System.Drawing.Size(1075, 76);
            this.PanelControlPlayback.TabIndex = 0;
            // 
            // Btn_Stop
            // 
            this.Btn_Stop.Location = new System.Drawing.Point(178, 42);
            this.Btn_Stop.Name = "Btn_Stop";
            this.Btn_Stop.Size = new System.Drawing.Size(77, 27);
            this.Btn_Stop.TabIndex = 4;
            this.Btn_Stop.Text = "Stop";
            this.Btn_Stop.UseVisualStyleBackColor = true;
            this.Btn_Stop.Click += new System.EventHandler(this.Btn_Stop_Click);
            // 
            // Btn_Pause
            // 
            this.Btn_Pause.Location = new System.Drawing.Point(95, 42);
            this.Btn_Pause.Name = "Btn_Pause";
            this.Btn_Pause.Size = new System.Drawing.Size(77, 27);
            this.Btn_Pause.TabIndex = 3;
            this.Btn_Pause.Text = "Pause";
            this.Btn_Pause.UseVisualStyleBackColor = true;
            this.Btn_Pause.Click += new System.EventHandler(this.Btn_Pause_Click);
            // 
            // TrackBarVolume
            // 
            this.TrackBarVolume.LargeChange = 1;
            this.TrackBarVolume.Location = new System.Drawing.Point(734, 9);
            this.TrackBarVolume.Name = "TrackBarVolume";
            this.TrackBarVolume.Size = new System.Drawing.Size(341, 45);
            this.TrackBarVolume.TabIndex = 2;
            this.TrackBarVolume.TickStyle = System.Windows.Forms.TickStyle.TopLeft;
            this.TrackBarVolume.ValueChanged += new System.EventHandler(this.TrackBarVolume_ValueChanged);
            // 
            // Btn_Start
            // 
            this.Btn_Start.Location = new System.Drawing.Point(12, 42);
            this.Btn_Start.Name = "Btn_Start";
            this.Btn_Start.Size = new System.Drawing.Size(77, 27);
            this.Btn_Start.TabIndex = 1;
            this.Btn_Start.Text = "Start";
            this.Btn_Start.UseVisualStyleBackColor = true;
            this.Btn_Start.Click += new System.EventHandler(this.Btn_Start_Click);
            // 
            // Txb_Url
            // 
            this.Txb_Url.Location = new System.Drawing.Point(12, 9);
            this.Txb_Url.Multiline = true;
            this.Txb_Url.Name = "Txb_Url";
            this.Txb_Url.Size = new System.Drawing.Size(716, 27);
            this.Txb_Url.TabIndex = 0;
            // 
            // Btn_Back
            // 
            this.Btn_Back.Location = new System.Drawing.Point(312, 42);
            this.Btn_Back.Name = "Btn_Back";
            this.Btn_Back.Size = new System.Drawing.Size(77, 27);
            this.Btn_Back.TabIndex = 5;
            this.Btn_Back.Text = "<";
            this.Btn_Back.UseVisualStyleBackColor = true;
            this.Btn_Back.Click += new System.EventHandler(this.Btn_Back_Click);
            // 
            // Btn_Advance
            // 
            this.Btn_Advance.Location = new System.Drawing.Point(395, 42);
            this.Btn_Advance.Name = "Btn_Advance";
            this.Btn_Advance.Size = new System.Drawing.Size(77, 27);
            this.Btn_Advance.TabIndex = 6;
            this.Btn_Advance.Text = ">";
            this.Btn_Advance.UseVisualStyleBackColor = true;
            this.Btn_Advance.Click += new System.EventHandler(this.Btn_Advance_Click);
            // 
            // MediaSessionPlayback
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1075, 672);
            this.Controls.Add(this.PanelRender);
            this.Name = "MediaSessionPlayback";
            this.Text = "Media Session Playback Test";
            this.Load += new System.EventHandler(this.MediaSessionPlayback_Load);
            this.PanelRender.ResumeLayout(false);
            this.PanelControlPlayback.ResumeLayout(false);
            this.PanelControlPlayback.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TrackBarVolume)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel PanelRender;
        private System.Windows.Forms.Panel PanelControlPlayback;
        private System.Windows.Forms.Button Btn_Start;
        private System.Windows.Forms.TextBox Txb_Url;
        private System.Windows.Forms.TrackBar TrackBarVolume;
        private System.Windows.Forms.Button Btn_Stop;
        private System.Windows.Forms.Button Btn_Pause;
        private System.Windows.Forms.Button Btn_Advance;
        private System.Windows.Forms.Button Btn_Back;
    }
}

