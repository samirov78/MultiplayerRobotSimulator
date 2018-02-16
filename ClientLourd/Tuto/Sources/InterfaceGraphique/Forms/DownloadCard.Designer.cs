namespace InterfaceGraphique
{
    partial class DownloadCard
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
            this.text1 = new System.Windows.Forms.Label();
            this.m_cardNameTextBox = new System.Windows.Forms.TextBox();
            this.m_downloadButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // text1
            // 
            this.text1.AutoSize = true;
            this.text1.Location = new System.Drawing.Point(34, 42);
            this.text1.Name = "text1";
            this.text1.Size = new System.Drawing.Size(82, 13);
            this.text1.TabIndex = 0;
            this.text1.Text = "Nom de la carte";
            // 
            // m_cardNameTextBox
            // 
            this.m_cardNameTextBox.Location = new System.Drawing.Point(135, 39);
            this.m_cardNameTextBox.Name = "m_cardNameTextBox";
            this.m_cardNameTextBox.Size = new System.Drawing.Size(191, 20);
            this.m_cardNameTextBox.TabIndex = 1;
            // 
            // m_downloadButton
            // 
            this.m_downloadButton.Location = new System.Drawing.Point(246, 89);
            this.m_downloadButton.Name = "m_downloadButton";
            this.m_downloadButton.Size = new System.Drawing.Size(79, 23);
            this.m_downloadButton.TabIndex = 2;
            this.m_downloadButton.Text = "Télécharger";
            this.m_downloadButton.UseVisualStyleBackColor = true;
            this.m_downloadButton.Click += new System.EventHandler(this.m_downloadButton_Click);
            // 
            // DownloadCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(338, 146);
            this.Controls.Add(this.m_downloadButton);
            this.Controls.Add(this.m_cardNameTextBox);
            this.Controls.Add(this.text1);
            this.Name = "DownloadCard";
            this.Text = "DownloadCard";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label text1;
        private System.Windows.Forms.TextBox m_cardNameTextBox;
        private System.Windows.Forms.Button m_downloadButton;
    }
}