namespace InterfaceGraphique.Forms
{
    partial class CreateProfile
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
            this.label1 = new System.Windows.Forms.Label();
            this.m_loginTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.m_lastNameTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.m_firstNameTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.m_emailTextBox = new System.Windows.Forms.TextBox();
            this.m_adminCheckBox = new System.Windows.Forms.CheckBox();
            this.m_adminLabel = new System.Windows.Forms.Label();
            this.m_adminPasswordTextBox = new System.Windows.Forms.TextBox();
            this.m_choseImageDialog = new System.Windows.Forms.OpenFileDialog();
            this.m_createProfilButton = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.m_password1TextBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.m_password2TextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(22, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 23);
            this.label1.TabIndex = 0;
            this.label1.Text = "Identifiant";
            // 
            // m_loginTextBox
            // 
            this.m_loginTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_loginTextBox.Location = new System.Drawing.Point(26, 28);
            this.m_loginTextBox.Name = "m_loginTextBox";
            this.m_loginTextBox.Size = new System.Drawing.Size(249, 26);
            this.m_loginTextBox.TabIndex = 1;
            this.m_loginTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox1_KeyPress);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(311, 57);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(45, 23);
            this.label2.TabIndex = 2;
            this.label2.Text = "Nom";
            // 
            // m_lastNameTextBox
            // 
            this.m_lastNameTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lastNameTextBox.Location = new System.Drawing.Point(315, 80);
            this.m_lastNameTextBox.Name = "m_lastNameTextBox";
            this.m_lastNameTextBox.Size = new System.Drawing.Size(249, 26);
            this.m_lastNameTextBox.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(22, 57);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(68, 23);
            this.label3.TabIndex = 4;
            this.label3.Text = "Prénom";
            // 
            // m_firstNameTextBox
            // 
            this.m_firstNameTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_firstNameTextBox.Location = new System.Drawing.Point(26, 80);
            this.m_firstNameTextBox.Name = "m_firstNameTextBox";
            this.m_firstNameTextBox.Size = new System.Drawing.Size(249, 26);
            this.m_firstNameTextBox.TabIndex = 2;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(22, 162);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(171, 23);
            this.label4.TabIndex = 6;
            this.label4.Text = "Adresse electronique";
            // 
            // m_emailTextBox
            // 
            this.m_emailTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_emailTextBox.Location = new System.Drawing.Point(26, 186);
            this.m_emailTextBox.Name = "m_emailTextBox";
            this.m_emailTextBox.Size = new System.Drawing.Size(249, 26);
            this.m_emailTextBox.TabIndex = 6;
            this.m_emailTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_emailTextBox_KeyPress);
            // 
            // m_adminCheckBox
            // 
            this.m_adminCheckBox.AutoSize = true;
            this.m_adminCheckBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_adminCheckBox.Location = new System.Drawing.Point(26, 235);
            this.m_adminCheckBox.Name = "m_adminCheckBox";
            this.m_adminCheckBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.m_adminCheckBox.Size = new System.Drawing.Size(208, 27);
            this.m_adminCheckBox.TabIndex = 7;
            this.m_adminCheckBox.Text = "Devenir administrateur";
            this.m_adminCheckBox.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.m_adminCheckBox.UseVisualStyleBackColor = true;
            this.m_adminCheckBox.CheckedChanged += new System.EventHandler(this.m_adminCheckBox_CheckedChanged);
            // 
            // m_adminLabel
            // 
            this.m_adminLabel.AutoSize = true;
            this.m_adminLabel.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_adminLabel.Location = new System.Drawing.Point(311, 214);
            this.m_adminLabel.Name = "m_adminLabel";
            this.m_adminLabel.Size = new System.Drawing.Size(230, 23);
            this.m_adminLabel.TabIndex = 10;
            this.m_adminLabel.Text = "Mot de passe administrateur";
            this.m_adminLabel.Visible = false;
            // 
            // m_adminPasswordTextBox
            // 
            this.m_adminPasswordTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_adminPasswordTextBox.Location = new System.Drawing.Point(315, 239);
            this.m_adminPasswordTextBox.Name = "m_adminPasswordTextBox";
            this.m_adminPasswordTextBox.PasswordChar = '*';
            this.m_adminPasswordTextBox.Size = new System.Drawing.Size(249, 26);
            this.m_adminPasswordTextBox.TabIndex = 8;
            this.m_adminPasswordTextBox.Visible = false;
            // 
            // m_choseImageDialog
            // 
            this.m_choseImageDialog.FileName = "openFileDialog1";
            // 
            // m_createProfilButton
            // 
            this.m_createProfilButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_createProfilButton.Location = new System.Drawing.Point(222, 282);
            this.m_createProfilButton.Name = "m_createProfilButton";
            this.m_createProfilButton.Size = new System.Drawing.Size(108, 35);
            this.m_createProfilButton.TabIndex = 9;
            this.m_createProfilButton.Text = "Envoyer";
            this.m_createProfilButton.UseVisualStyleBackColor = true;
            this.m_createProfilButton.Click += new System.EventHandler(this.m_createProfilButton_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(22, 109);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(111, 23);
            this.label5.TabIndex = 2;
            this.label5.Text = "Mot de passe";
            // 
            // m_password1TextBox
            // 
            this.m_password1TextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_password1TextBox.Location = new System.Drawing.Point(26, 132);
            this.m_password1TextBox.Name = "m_password1TextBox";
            this.m_password1TextBox.PasswordChar = '*';
            this.m_password1TextBox.Size = new System.Drawing.Size(249, 26);
            this.m_password1TextBox.TabIndex = 4;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(311, 109);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(212, 23);
            this.label6.TabIndex = 4;
            this.label6.Text = "Confirmer le mot de passe";
            // 
            // m_password2TextBox
            // 
            this.m_password2TextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_password2TextBox.Location = new System.Drawing.Point(315, 132);
            this.m_password2TextBox.Name = "m_password2TextBox";
            this.m_password2TextBox.PasswordChar = '*';
            this.m_password2TextBox.Size = new System.Drawing.Size(249, 26);
            this.m_password2TextBox.TabIndex = 5;
            // 
            // CreateProfile
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 329);
            this.Controls.Add(this.m_adminPasswordTextBox);
            this.Controls.Add(this.m_adminLabel);
            this.Controls.Add(this.m_adminCheckBox);
            this.Controls.Add(this.m_createProfilButton);
            this.Controls.Add(this.m_emailTextBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.m_password2TextBox);
            this.Controls.Add(this.m_firstNameTextBox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.m_password1TextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.m_lastNameTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.m_loginTextBox);
            this.Controls.Add(this.label1);
            this.Name = "CreateProfile";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Créer un profil";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox m_loginTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox m_lastNameTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox m_firstNameTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox m_emailTextBox;
        private System.Windows.Forms.CheckBox m_adminCheckBox;
        private System.Windows.Forms.Label m_adminLabel;
        private System.Windows.Forms.TextBox m_adminPasswordTextBox;
        private System.Windows.Forms.OpenFileDialog m_choseImageDialog;
        private System.Windows.Forms.Button m_createProfilButton;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox m_password1TextBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox m_password2TextBox;
    }
}