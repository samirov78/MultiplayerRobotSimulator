namespace InterfaceGraphique
{
    partial class Login
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
            this.m_idPasswordLoginLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.m_idPasswordIdTextBox = new System.Windows.Forms.TextBox();
            this.m_idPasswordPasswordTextBox = new System.Windows.Forms.TextBox();
            this.m_idPasswordConnectButton = new System.Windows.Forms.Button();
            this.m_idPasswordImageNameLabel = new System.Windows.Forms.Label();
            this.m_profilePictureBox = new System.Windows.Forms.PictureBox();
            this.m_idPasswordPanel = new System.Windows.Forms.Panel();
            this.m_idPasswordImagePanel = new System.Windows.Forms.Panel();
            this.m_idPasswordImageIdTextBox = new System.Windows.Forms.TextBox();
            this.m_idPasswordImagePasswordTextBox = new System.Windows.Forms.TextBox();
            this.m_idPasswordImageConnectButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.m_idPasswordImageLoginLabel = new System.Windows.Forms.Label();
            this.m_anotherAcountButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.m_profilePictureBox)).BeginInit();
            this.m_idPasswordPanel.SuspendLayout();
            this.m_idPasswordImagePanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_loginLabel
            // 
            this.m_idPasswordLoginLabel.AutoSize = true;
            this.m_idPasswordLoginLabel.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordLoginLabel.Location = new System.Drawing.Point(43, 59);
            this.m_idPasswordLoginLabel.Name = "m_loginLabel";
            this.m_idPasswordLoginLabel.Size = new System.Drawing.Size(92, 23);
            this.m_idPasswordLoginLabel.TabIndex = 0;
            this.m_idPasswordLoginLabel.Text = "Identifiant";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(43, 109);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(111, 23);
            this.label2.TabIndex = 1;
            this.label2.Text = "Mot de passe";
            // 
            // m_idTextBox
            // 
            this.m_idPasswordIdTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordIdTextBox.Location = new System.Drawing.Point(154, 56);
            this.m_idPasswordIdTextBox.Name = "m_idTextBox";
            this.m_idPasswordIdTextBox.Size = new System.Drawing.Size(190, 26);
            this.m_idPasswordIdTextBox.TabIndex = 2;
            this.m_idPasswordIdTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_idTextBox_KeyPress);
            // 
            // m_passwordTextBox
            // 
            this.m_idPasswordPasswordTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordPasswordTextBox.Location = new System.Drawing.Point(154, 106);
            this.m_idPasswordPasswordTextBox.Name = "m_passwordTextBox";
            this.m_idPasswordPasswordTextBox.PasswordChar = '*';
            this.m_idPasswordPasswordTextBox.Size = new System.Drawing.Size(190, 26);
            this.m_idPasswordPasswordTextBox.TabIndex = 3;
            // 
            // m_connectIdPasswordButton
            // 
            this.m_idPasswordConnectButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordConnectButton.Location = new System.Drawing.Point(224, 154);
            this.m_idPasswordConnectButton.Name = "m_connectIdPasswordButton";
            this.m_idPasswordConnectButton.Size = new System.Drawing.Size(120, 30);
            this.m_idPasswordConnectButton.TabIndex = 4;
            this.m_idPasswordConnectButton.Text = "Se connecter";
            this.m_idPasswordConnectButton.UseVisualStyleBackColor = true;
            this.m_idPasswordConnectButton.Click += new System.EventHandler(this.m_idPasswordConnectButton_Click);
            // 
            // m_firstLastNameLabel
            // 
            this.m_idPasswordImageNameLabel.AutoSize = true;
            this.m_idPasswordImageNameLabel.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordImageNameLabel.Location = new System.Drawing.Point(238, 172);
            this.m_idPasswordImageNameLabel.Name = "m_firstLastNameLabel";
            this.m_idPasswordImageNameLabel.Size = new System.Drawing.Size(0, 23);
            this.m_idPasswordImageNameLabel.TabIndex = 0;
            // 
            // m_profilePictureBox
            // 
            this.m_profilePictureBox.Location = new System.Drawing.Point(236, 23);
            this.m_profilePictureBox.Name = "m_profilePictureBox";
            this.m_profilePictureBox.Size = new System.Drawing.Size(151, 142);
            this.m_profilePictureBox.TabIndex = 5;
            this.m_profilePictureBox.TabStop = false;
            this.m_profilePictureBox.Margin = new System.Windows.Forms.Padding(2);
            this.m_profilePictureBox.BackColor = System.Drawing.Color.Gray;
            this.m_profilePictureBox.Click += new System.EventHandler(this.m_profilePictureBox_Click);
            // 
            // m_idPasswordPanel
            // 
            this.m_idPasswordPanel.Controls.Add(this.m_idPasswordLoginLabel);
            this.m_idPasswordPanel.Controls.Add(this.m_idPasswordIdTextBox);
            this.m_idPasswordPanel.Controls.Add(this.m_idPasswordConnectButton);
            this.m_idPasswordPanel.Controls.Add(this.label2);
            this.m_idPasswordPanel.Controls.Add(this.m_idPasswordPasswordTextBox);
            this.m_idPasswordPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_idPasswordPanel.Location = new System.Drawing.Point(0, 0);
            this.m_idPasswordPanel.Name = "m_idPasswordPanel";
            this.m_idPasswordPanel.Size = new System.Drawing.Size(442, 250);
            this.m_idPasswordPanel.TabIndex = 6;
            // 
            // m_idPasswordImagePanel
            // 
            this.m_idPasswordImagePanel.Controls.Add(this.m_idPasswordImageIdTextBox);
            this.m_idPasswordImagePanel.Controls.Add(this.m_profilePictureBox);
            this.m_idPasswordImagePanel.Controls.Add(this.m_idPasswordImageNameLabel);
            this.m_idPasswordImagePanel.Controls.Add(this.m_idPasswordImagePasswordTextBox);
            this.m_idPasswordImagePanel.Controls.Add(this.m_idPasswordImageConnectButton);
            this.m_idPasswordImagePanel.Controls.Add(this.label1);
            this.m_idPasswordImagePanel.Controls.Add(this.m_idPasswordImageLoginLabel);
            this.m_idPasswordImagePanel.Controls.Add(this.m_anotherAcountButton);
            this.m_idPasswordImagePanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_idPasswordImagePanel.Location = new System.Drawing.Point(0, 0);
            this.m_idPasswordImagePanel.Name = "m_idPasswordImagePanel";
            this.m_idPasswordImagePanel.Size = new System.Drawing.Size(442, 250);
            this.m_idPasswordImagePanel.TabIndex = 7;
            // 
            // m_idWithPasswordImageTextBox
            // 
            this.m_idPasswordImageIdTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordImageIdTextBox.Location = new System.Drawing.Point(16, 56);
            this.m_idPasswordImageIdTextBox.Name = "m_idWithPasswordImageTextBox";
            this.m_idPasswordImageIdTextBox.Size = new System.Drawing.Size(190, 26);
            this.m_idPasswordImageIdTextBox.TabIndex = 2;
            this.m_idPasswordImageIdTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_idTextBox_KeyPress);
            // 
            // m_passwordWithIdImageTextBox
            // 
            this.m_idPasswordImagePasswordTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordImagePasswordTextBox.Location = new System.Drawing.Point(16, 110);
            this.m_idPasswordImagePasswordTextBox.Name = "m_passwordWithIdImageTextBox";
            this.m_idPasswordImagePasswordTextBox.PasswordChar = '*';
            this.m_idPasswordImagePasswordTextBox.Size = new System.Drawing.Size(190, 26);
            this.m_idPasswordImagePasswordTextBox.TabIndex = 3;
            // 
            // m_connectIdPasswordImageButton
            // 
            this.m_idPasswordImageConnectButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordImageConnectButton.Location = new System.Drawing.Point(86, 154);
            this.m_idPasswordImageConnectButton.Name = "m_connectIdPasswordImageButton";
            this.m_idPasswordImageConnectButton.Size = new System.Drawing.Size(120, 30);
            this.m_idPasswordImageConnectButton.TabIndex = 4;
            this.m_idPasswordImageConnectButton.Text = "Se connecter";
            this.m_idPasswordImageConnectButton.UseVisualStyleBackColor = true;
            this.m_idPasswordImageConnectButton.Click += new System.EventHandler(this.m_idPasswordImageConnectButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 85);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(111, 23);
            this.label1.TabIndex = 1;
            this.label1.Text = "Mot de passe";
            // 
            // label3
            // 
            this.m_idPasswordImageLoginLabel.AutoSize = true;
            this.m_idPasswordImageLoginLabel.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idPasswordImageLoginLabel.Location = new System.Drawing.Point(12, 31);
            this.m_idPasswordImageLoginLabel.Name = "m_idPasswordImageLoginLabel";
            this.m_idPasswordImageLoginLabel.Size = new System.Drawing.Size(92, 23);
            this.m_idPasswordImageLoginLabel.TabIndex = 0;
            this.m_idPasswordImageLoginLabel.Text = "Identifiant";
            // 
            // m_anotherAcountButton
            // 
            this.m_anotherAcountButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_anotherAcountButton.Location = new System.Drawing.Point(5, 212);
            this.m_anotherAcountButton.Name = "m_anotherAcountButton";
            this.m_anotherAcountButton.Size = new System.Drawing.Size(214, 30);
            this.m_anotherAcountButton.TabIndex = 4;
            this.m_anotherAcountButton.Text = "Choisir un autre compte";
            this.m_anotherAcountButton.UseVisualStyleBackColor = true;
            this.m_anotherAcountButton.Click += new System.EventHandler(this.m_anotherAcountButton_Click);
            // 
            // Login
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(442, 250);
            this.Controls.Add(this.m_idPasswordPanel);
            this.Controls.Add(this.m_idPasswordImagePanel);
            this.Name = "Login";
            this.Text = "Se connecter";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Login_FormClosing);
            this.Load += new System.EventHandler(this.Login_Load);
            ((System.ComponentModel.ISupportInitialize)(this.m_profilePictureBox)).EndInit();
            this.m_idPasswordPanel.ResumeLayout(false);
            this.m_idPasswordPanel.PerformLayout();
            this.m_idPasswordImagePanel.ResumeLayout(false);
            this.m_idPasswordImagePanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label m_idPasswordLoginLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox m_idPasswordIdTextBox;
        private System.Windows.Forms.TextBox m_idPasswordPasswordTextBox;
        private System.Windows.Forms.Button m_idPasswordConnectButton;
        private System.Windows.Forms.Label m_idPasswordImageNameLabel;
        private System.Windows.Forms.PictureBox m_profilePictureBox;
        private System.Windows.Forms.Panel m_idPasswordPanel;
        private System.Windows.Forms.Panel m_idPasswordImagePanel;
        private System.Windows.Forms.Label m_idPasswordImageLoginLabel;
        private System.Windows.Forms.TextBox m_idPasswordImageIdTextBox;
        private System.Windows.Forms.TextBox m_idPasswordImagePasswordTextBox;
        private System.Windows.Forms.Button m_idPasswordImageConnectButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button m_anotherAcountButton;
    }
}