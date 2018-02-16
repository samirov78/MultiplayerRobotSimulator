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
            this.text1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.m_idTextBox = new System.Windows.Forms.TextBox();
            this.m_passwordTextBox = new System.Windows.Forms.TextBox();
            this.m_connectButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // text1
            // 
            this.text1.AutoSize = true;
            this.text1.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text1.Location = new System.Drawing.Point(26, 28);
            this.text1.Name = "text1";
            this.text1.Size = new System.Drawing.Size(92, 23);
            this.text1.TabIndex = 0;
            this.text1.Text = "Identifiant";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(26, 63);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(111, 23);
            this.label2.TabIndex = 1;
            this.label2.Text = "Mot de passe";
            // 
            // m_idTextBox
            // 
            this.m_idTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_idTextBox.Location = new System.Drawing.Point(143, 25);
            this.m_idTextBox.Name = "m_idTextBox";
            this.m_idTextBox.Size = new System.Drawing.Size(172, 26);
            this.m_idTextBox.TabIndex = 2;
            this.m_idTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_idTextBox_KeyPress);
            // 
            // m_passwordTextBox
            // 
            this.m_passwordTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_passwordTextBox.Location = new System.Drawing.Point(143, 60);
            this.m_passwordTextBox.Name = "m_passwordTextBox";
            this.m_passwordTextBox.Size = new System.Drawing.Size(172, 26);
            this.m_passwordTextBox.TabIndex = 3;
            // 
            // m_connectButton
            // 
            this.m_connectButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_connectButton.Location = new System.Drawing.Point(191, 102);
            this.m_connectButton.Name = "m_connectButton";
            this.m_connectButton.Size = new System.Drawing.Size(124, 30);
            this.m_connectButton.TabIndex = 4;
            this.m_connectButton.Text = "Se connecter";
            this.m_connectButton.UseVisualStyleBackColor = true;
            this.m_connectButton.Click += new System.EventHandler(this.m_connectButton_Click);
            // 
            // Login
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(349, 153);
            this.Controls.Add(this.m_connectButton);
            this.Controls.Add(this.m_passwordTextBox);
            this.Controls.Add(this.m_idTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.text1);
            this.Name = "Login";
            this.Text = "Login";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Login_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label text1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox m_idTextBox;
        private System.Windows.Forms.TextBox m_passwordTextBox;
        private System.Windows.Forms.Button m_connectButton;
    }
}