namespace InterfaceGraphique
{
    partial class ConfigurationEnLigne
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
            this.label2 = new System.Windows.Forms.Label();
            this.m_ipTextBox = new System.Windows.Forms.TextBox();
            this.m_portTextBox = new System.Windows.Forms.TextBox();
            this.m_saveServerButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.m_imageSentCheckBox = new System.Windows.Forms.CheckBox();
            this.m_imageReceivedCheckBox = new System.Windows.Forms.CheckBox();
            this.m_saveSoundButton = new System.Windows.Forms.Button();
            this.m_messageSentCheckBox = new System.Windows.Forms.CheckBox();
            this.m_messageReceivedCheckBox = new System.Windows.Forms.CheckBox();
            this.m_connectionCheckBox = new System.Windows.Forms.CheckBox();
            this.m_disconnectionCheckBox = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // text1
            // 
            this.text1.AutoSize = true;
            this.text1.Location = new System.Drawing.Point(30, 27);
            this.text1.Name = "text1";
            this.text1.Size = new System.Drawing.Size(27, 24);
            this.text1.TabIndex = 0;
            this.text1.Text = "IP";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(285, 27);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(45, 24);
            this.label2.TabIndex = 1;
            this.label2.Text = "Port";
            // 
            // m_ipTextBox
            // 
            this.m_ipTextBox.Location = new System.Drawing.Point(76, 24);
            this.m_ipTextBox.Name = "m_ipTextBox";
            this.m_ipTextBox.Size = new System.Drawing.Size(185, 27);
            this.m_ipTextBox.TabIndex = 2;
            this.m_ipTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_ipTextBox_KeyPress);
            // 
            // m_portTextBox
            // 
            this.m_portTextBox.Location = new System.Drawing.Point(332, 27);
            this.m_portTextBox.Name = "m_portTextBox";
            this.m_portTextBox.Size = new System.Drawing.Size(114, 27);
            this.m_portTextBox.TabIndex = 3;
            this.m_portTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_portTextBox_KeyPress);
            // 
            // m_saveServerButton
            // 
            this.m_saveServerButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_saveServerButton.Location = new System.Drawing.Point(175, 61);
            this.m_saveServerButton.Name = "m_saveServerButton";
            this.m_saveServerButton.Size = new System.Drawing.Size(114, 32);
            this.m_saveServerButton.TabIndex = 4;
            this.m_saveServerButton.Text = "Enregistrer";
            this.m_saveServerButton.UseVisualStyleBackColor = true;
            this.m_saveServerButton.Click += new System.EventHandler(this.m_saveButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.m_ipTextBox);
            this.groupBox1.Controls.Add(this.text1);
            this.groupBox1.Controls.Add(this.m_saveServerButton);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.m_portTextBox);
            this.groupBox1.Font = new System.Drawing.Font("Sitka Small", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(466, 100);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Serveur";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.m_disconnectionCheckBox);
            this.groupBox2.Controls.Add(this.m_imageSentCheckBox);
            this.groupBox2.Controls.Add(this.m_connectionCheckBox);
            this.groupBox2.Controls.Add(this.m_imageReceivedCheckBox);
            this.groupBox2.Controls.Add(this.m_saveSoundButton);
            this.groupBox2.Controls.Add(this.m_messageSentCheckBox);
            this.groupBox2.Controls.Add(this.m_messageReceivedCheckBox);
            this.groupBox2.Font = new System.Drawing.Font("Sitka Small", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(12, 117);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(466, 147);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Son";
            // 
            // m_imageSentCheckBox
            // 
            this.m_imageSentCheckBox.AutoSize = true;
            this.m_imageSentCheckBox.Location = new System.Drawing.Point(276, 53);
            this.m_imageSentCheckBox.Name = "m_imageSentCheckBox";
            this.m_imageSentCheckBox.Size = new System.Drawing.Size(143, 28);
            this.m_imageSentCheckBox.TabIndex = 0;
            this.m_imageSentCheckBox.Text = "Envoi d\'image";
            this.m_imageSentCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_imageReceivedCheckBox
            // 
            this.m_imageReceivedCheckBox.AutoSize = true;
            this.m_imageReceivedCheckBox.Location = new System.Drawing.Point(20, 53);
            this.m_imageReceivedCheckBox.Name = "m_imageReceivedCheckBox";
            this.m_imageReceivedCheckBox.Size = new System.Drawing.Size(177, 28);
            this.m_imageReceivedCheckBox.TabIndex = 0;
            this.m_imageReceivedCheckBox.Text = "Réception d\'image";
            this.m_imageReceivedCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_saveSoundButton
            // 
            this.m_saveSoundButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_saveSoundButton.Location = new System.Drawing.Point(175, 108);
            this.m_saveSoundButton.Name = "m_saveSoundButton";
            this.m_saveSoundButton.Size = new System.Drawing.Size(114, 32);
            this.m_saveSoundButton.TabIndex = 4;
            this.m_saveSoundButton.Text = "Enregistrer";
            this.m_saveSoundButton.UseVisualStyleBackColor = true;
            this.m_saveSoundButton.Click += new System.EventHandler(this.m_saveSoundButton_Click);
            // 
            // m_messageSentCheckBox
            // 
            this.m_messageSentCheckBox.AutoSize = true;
            this.m_messageSentCheckBox.Location = new System.Drawing.Point(276, 28);
            this.m_messageSentCheckBox.Name = "m_messageSentCheckBox";
            this.m_messageSentCheckBox.Size = new System.Drawing.Size(171, 28);
            this.m_messageSentCheckBox.TabIndex = 0;
            this.m_messageSentCheckBox.Text = "Envoi de message";
            this.m_messageSentCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_messageReceivedCheckBox
            // 
            this.m_messageReceivedCheckBox.AutoSize = true;
            this.m_messageReceivedCheckBox.Location = new System.Drawing.Point(20, 28);
            this.m_messageReceivedCheckBox.Name = "m_messageReceivedCheckBox";
            this.m_messageReceivedCheckBox.Size = new System.Drawing.Size(205, 28);
            this.m_messageReceivedCheckBox.TabIndex = 0;
            this.m_messageReceivedCheckBox.Text = "Réception de message";
            this.m_messageReceivedCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_connectionCheckBox
            // 
            this.m_connectionCheckBox.AutoSize = true;
            this.m_connectionCheckBox.Location = new System.Drawing.Point(20, 78);
            this.m_connectionCheckBox.Name = "m_connectionCheckBox";
            this.m_connectionCheckBox.Size = new System.Drawing.Size(115, 28);
            this.m_connectionCheckBox.TabIndex = 0;
            this.m_connectionCheckBox.Text = "Connexion";
            this.m_connectionCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_disconnectionCheckBox
            // 
            this.m_disconnectionCheckBox.AutoSize = true;
            this.m_disconnectionCheckBox.Location = new System.Drawing.Point(276, 78);
            this.m_disconnectionCheckBox.Name = "m_disconnectionCheckBox";
            this.m_disconnectionCheckBox.Size = new System.Drawing.Size(133, 28);
            this.m_disconnectionCheckBox.TabIndex = 0;
            this.m_disconnectionCheckBox.Text = "Déconnexion";
            this.m_disconnectionCheckBox.UseVisualStyleBackColor = true;
            // 
            // ConfigurationEnLigne
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(495, 276);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "ConfigurationEnLigne";
            this.Text = "Configuration";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label text1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox m_ipTextBox;
        private System.Windows.Forms.TextBox m_portTextBox;
        private System.Windows.Forms.Button m_saveServerButton;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox m_imageSentCheckBox;
        private System.Windows.Forms.CheckBox m_imageReceivedCheckBox;
        private System.Windows.Forms.CheckBox m_messageSentCheckBox;
        private System.Windows.Forms.CheckBox m_messageReceivedCheckBox;
        private System.Windows.Forms.Button m_saveSoundButton;
        private System.Windows.Forms.CheckBox m_disconnectionCheckBox;
        private System.Windows.Forms.CheckBox m_connectionCheckBox;
    }
}