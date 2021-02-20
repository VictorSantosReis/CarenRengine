﻿
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
            this.Btn_Start = new System.Windows.Forms.Button();
            this.Txb_Url = new System.Windows.Forms.TextBox();
            this.PanelRender.SuspendLayout();
            this.PanelControlPlayback.SuspendLayout();
            this.SuspendLayout();
            // 
            // PanelRender
            // 
            this.PanelRender.BackColor = System.Drawing.Color.Black;
            this.PanelRender.Controls.Add(this.PanelControlPlayback);
            this.PanelRender.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PanelRender.Location = new System.Drawing.Point(0, 0);
            this.PanelRender.Name = "PanelRender";
            this.PanelRender.Size = new System.Drawing.Size(1066, 625);
            this.PanelRender.TabIndex = 0;
            // 
            // PanelControlPlayback
            // 
            this.PanelControlPlayback.BackColor = System.Drawing.Color.White;
            this.PanelControlPlayback.Controls.Add(this.Btn_Start);
            this.PanelControlPlayback.Controls.Add(this.Txb_Url);
            this.PanelControlPlayback.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.PanelControlPlayback.Location = new System.Drawing.Point(0, 576);
            this.PanelControlPlayback.Name = "PanelControlPlayback";
            this.PanelControlPlayback.Size = new System.Drawing.Size(1066, 49);
            this.PanelControlPlayback.TabIndex = 0;
            // 
            // Btn_Start
            // 
            this.Btn_Start.Location = new System.Drawing.Point(735, 10);
            this.Btn_Start.Name = "Btn_Start";
            this.Btn_Start.Size = new System.Drawing.Size(103, 27);
            this.Btn_Start.TabIndex = 1;
            this.Btn_Start.Text = "Start";
            this.Btn_Start.UseVisualStyleBackColor = true;
            this.Btn_Start.Click += new System.EventHandler(this.Btn_Start_Click);
            // 
            // Txb_Url
            // 
            this.Txb_Url.Location = new System.Drawing.Point(13, 10);
            this.Txb_Url.Multiline = true;
            this.Txb_Url.Name = "Txb_Url";
            this.Txb_Url.Size = new System.Drawing.Size(716, 27);
            this.Txb_Url.TabIndex = 0;
            // 
            // MediaSessionPlayback
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1066, 625);
            this.Controls.Add(this.PanelRender);
            this.Name = "MediaSessionPlayback";
            this.Text = "Media Session Playback Test";
            this.Load += new System.EventHandler(this.MediaSessionPlayback_Load);
            this.PanelRender.ResumeLayout(false);
            this.PanelControlPlayback.ResumeLayout(false);
            this.PanelControlPlayback.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel PanelRender;
        private System.Windows.Forms.Panel PanelControlPlayback;
        private System.Windows.Forms.Button Btn_Start;
        private System.Windows.Forms.TextBox Txb_Url;
    }
}

