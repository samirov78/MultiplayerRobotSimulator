namespace InterfaceGraphique
{
    partial class EnregistrerDistant
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
            this.m_cardNameTextBox = new System.Windows.Forms.TextBox();
            this.m_saveButton = new System.Windows.Forms.Button();
            this.m_publicRadioButton = new System.Windows.Forms.RadioButton();
            this.m_privateRadioButton = new System.Windows.Forms.RadioButton();
            this.m_passwordTextBox = new System.Windows.Forms.TextBox();
            this.m_passwordLabel = new System.Windows.Forms.Label();
            this.m_onLigneCheckBox = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(28, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(131, 23);
            this.label1.TabIndex = 0;
            this.label1.Text = "Nom de la carte";
            // 
            // m_cardNameTextBox
            // 
            this.m_cardNameTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_cardNameTextBox.Location = new System.Drawing.Point(160, 35);
            this.m_cardNameTextBox.Name = "m_cardNameTextBox";
            this.m_cardNameTextBox.Size = new System.Drawing.Size(205, 26);
            this.m_cardNameTextBox.TabIndex = 1;
            this.m_cardNameTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_cardNameTextBox_KeyPress);
            // 
            // m_saveButton
            // 
            this.m_saveButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_saveButton.Location = new System.Drawing.Point(257, 156);
            this.m_saveButton.Name = "m_saveButton";
            this.m_saveButton.Size = new System.Drawing.Size(108, 29);
            this.m_saveButton.TabIndex = 2;
            this.m_saveButton.Text = "Enregistrer";
            this.m_saveButton.UseVisualStyleBackColor = true;
            this.m_saveButton.Click += new System.EventHandler(this.m_saveButton_Click);
            // 
            // m_publicRadioButton
            // 
            this.m_publicRadioButton.AutoSize = true;
            this.m_publicRadioButton.Checked = true;
            this.m_publicRadioButton.Font = new System.Drawing.Font("Sitka Text", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_publicRadioButton.Location = new System.Drawing.Point(175, 102);
            this.m_publicRadioButton.Name = "m_publicRadioButton";
            this.m_publicRadioButton.Size = new System.Drawing.Size(72, 25);
            this.m_publicRadioButton.TabIndex = 3;
            this.m_publicRadioButton.TabStop = true;
            this.m_publicRadioButton.Text = "Public";
            this.m_publicRadioButton.UseVisualStyleBackColor = true;
            this.m_publicRadioButton.CheckedChanged += new System.EventHandler(this.m_publicRadioButton_CheckedChanged);
            // 
            // m_privateRadioButton
            // 
            this.m_privateRadioButton.AutoSize = true;
            this.m_privateRadioButton.Font = new System.Drawing.Font("Sitka Text", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_privateRadioButton.Location = new System.Drawing.Point(32, 102);
            this.m_privateRadioButton.Name = "m_privateRadioButton";
            this.m_privateRadioButton.Size = new System.Drawing.Size(73, 25);
            this.m_privateRadioButton.TabIndex = 4;
            this.m_privateRadioButton.TabStop = true;
            this.m_privateRadioButton.Text = "Privée";
            this.m_privateRadioButton.UseVisualStyleBackColor = true;
            this.m_privateRadioButton.CheckedChanged += new System.EventHandler(this.m_privateRadioButton_CheckedChanged);
            // 
            // m_passwordTextBox
            // 
            this.m_passwordTextBox.Font = new System.Drawing.Font("Sitka Text", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_passwordTextBox.Location = new System.Drawing.Point(32, 156);
            this.m_passwordTextBox.Name = "m_passwordTextBox";
            this.m_passwordTextBox.PasswordChar = '*';
            this.m_passwordTextBox.Size = new System.Drawing.Size(204, 26);
            this.m_passwordTextBox.TabIndex = 5;
            this.m_passwordTextBox.Visible = false;
            // 
            // m_passwordLabel
            // 
            this.m_passwordLabel.AutoSize = true;
            this.m_passwordLabel.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_passwordLabel.Location = new System.Drawing.Point(28, 130);
            this.m_passwordLabel.Name = "m_passwordLabel";
            this.m_passwordLabel.Size = new System.Drawing.Size(111, 23);
            this.m_passwordLabel.TabIndex = 0;
            this.m_passwordLabel.Text = "Mot de passe";
            this.m_passwordLabel.Visible = false;
            // 
            // m_onLigneCheckBox
            // 
            this.m_onLigneCheckBox.AutoSize = true;
            this.m_onLigneCheckBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_onLigneCheckBox.Location = new System.Drawing.Point(32, 71);
            this.m_onLigneCheckBox.Name = "m_onLigneCheckBox";
            this.m_onLigneCheckBox.Size = new System.Drawing.Size(190, 27);
            this.m_onLigneCheckBox.TabIndex = 6;
            this.m_onLigneCheckBox.Text = "Avec édition en ligne";
            this.m_onLigneCheckBox.UseVisualStyleBackColor = true;
            // 
            // EnregistrerDistant
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(398, 196);
            this.Controls.Add(this.m_onLigneCheckBox);
            this.Controls.Add(this.m_passwordTextBox);
            this.Controls.Add(this.m_privateRadioButton);
            this.Controls.Add(this.m_publicRadioButton);
            this.Controls.Add(this.m_saveButton);
            this.Controls.Add(this.m_cardNameTextBox);
            this.Controls.Add(this.m_passwordLabel);
            this.Controls.Add(this.label1);
            this.Name = "EnregistrerDistant";
            this.Text = "Enregistrer dans le serveur";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox m_cardNameTextBox;
        private System.Windows.Forms.Button m_saveButton;
        private System.Windows.Forms.RadioButton m_publicRadioButton;
        private System.Windows.Forms.RadioButton m_privateRadioButton;
        private System.Windows.Forms.TextBox m_passwordTextBox;
        private System.Windows.Forms.Label m_passwordLabel;
        private System.Windows.Forms.CheckBox m_onLigneCheckBox;
    }
}