namespace InterfaceGraphique
{
    partial class OpenCard
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.m_flowLayout = new System.Windows.Forms.FlowLayoutPanel();
            this.SuspendLayout();
            // 
            // m_flowLayout
            // 
            this.m_flowLayout.AutoScroll = true;
            this.m_flowLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_flowLayout.Location = new System.Drawing.Point(0, 0);
            this.m_flowLayout.Name = "m_flowLayout";
            this.m_flowLayout.Size = new System.Drawing.Size(760, 400);
            this.m_flowLayout.TabIndex = 0;
            // 
            // OpenCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(760, 400);
            this.Controls.Add(this.m_flowLayout);
            this.Name = "OpenCard";
            this.Text = "Ouvrir une carte en ligne";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.OpenCard_FormClosing);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel m_flowLayout;
    }
}