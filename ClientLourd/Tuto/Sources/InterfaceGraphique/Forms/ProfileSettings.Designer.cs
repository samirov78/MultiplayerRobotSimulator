namespace InterfaceGraphique.Forms
{
    partial class ProfileSettings
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
            this.m_profilPicture = new System.Windows.Forms.PictureBox();
            this.m_choseImageButton = new System.Windows.Forms.Button();
            this.m_adminTextBox = new System.Windows.Forms.TextBox();
            this.m_adminLabel = new System.Windows.Forms.Label();
            this.m_changeImageButton = new System.Windows.Forms.Button();
            this.m_emailTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.m_newPassword1TextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.m_oldPasswordTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.m_changePasswordButton = new System.Windows.Forms.Button();
            this.text1 = new System.Windows.Forms.Label();
            this.m_newPassword2TextBox = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.m_deleteImageButton = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.m_changeEmailButton = new System.Windows.Forms.Button();
            this.m_changeTypeButton = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.m_userRadioButton = new System.Windows.Forms.RadioButton();
            this.m_adminRadioButton = new System.Windows.Forms.RadioButton();
            this.m_choseImageDialog = new System.Windows.Forms.OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.m_profilPicture)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_profilPicture
            // 
            this.m_profilPicture.BackColor = System.Drawing.Color.WhiteSmoke;
            this.m_profilPicture.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_profilPicture.Location = new System.Drawing.Point(18, 32);
            this.m_profilPicture.Name = "m_profilPicture";
            this.m_profilPicture.Size = new System.Drawing.Size(210, 210);
            this.m_profilPicture.TabIndex = 28;
            this.m_profilPicture.TabStop = false;
            // 
            // m_choseImageButton
            // 
            this.m_choseImageButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_choseImageButton.Location = new System.Drawing.Point(18, 252);
            this.m_choseImageButton.Name = "m_choseImageButton";
            this.m_choseImageButton.Size = new System.Drawing.Size(210, 30);
            this.m_choseImageButton.TabIndex = 11;
            this.m_choseImageButton.Text = "Choisir une image ...";
            this.m_choseImageButton.UseVisualStyleBackColor = true;
            this.m_choseImageButton.Click += new System.EventHandler(this.m_choseImageButton_Click);
            // 
            // m_adminTextBox
            // 
            this.m_adminTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_adminTextBox.Location = new System.Drawing.Point(263, 67);
            this.m_adminTextBox.Name = "m_adminTextBox";
            this.m_adminTextBox.Size = new System.Drawing.Size(192, 26);
            this.m_adminTextBox.TabIndex = 9;
            this.m_adminTextBox.Visible = false;
            // 
            // m_adminLabel
            // 
            this.m_adminLabel.AutoSize = true;
            this.m_adminLabel.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_adminLabel.Location = new System.Drawing.Point(16, 67);
            this.m_adminLabel.Name = "m_adminLabel";
            this.m_adminLabel.Size = new System.Drawing.Size(230, 23);
            this.m_adminLabel.TabIndex = 25;
            this.m_adminLabel.Text = "Mot de passe administrateur";
            this.m_adminLabel.Visible = false;
            // 
            // m_changeImageButton
            // 
            this.m_changeImageButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_changeImageButton.Location = new System.Drawing.Point(70, 344);
            this.m_changeImageButton.Name = "m_changeImageButton";
            this.m_changeImageButton.Size = new System.Drawing.Size(108, 30);
            this.m_changeImageButton.TabIndex = 13;
            this.m_changeImageButton.Text = "Envoyer";
            this.m_changeImageButton.UseVisualStyleBackColor = true;
            this.m_changeImageButton.Click += new System.EventHandler(this.m_changeImageButton_Click);
            // 
            // m_emailTextBox
            // 
            this.m_emailTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_emailTextBox.Location = new System.Drawing.Point(93, 35);
            this.m_emailTextBox.Name = "m_emailTextBox";
            this.m_emailTextBox.Size = new System.Drawing.Size(249, 26);
            this.m_emailTextBox.TabIndex = 5;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(17, 35);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(70, 23);
            this.label4.TabIndex = 21;
            this.label4.Text = "Adresse";
            // 
            // m_newPassword1TextBox
            // 
            this.m_newPassword1TextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_newPassword1TextBox.Location = new System.Drawing.Point(207, 70);
            this.m_newPassword1TextBox.Name = "m_newPassword1TextBox";
            this.m_newPassword1TextBox.Size = new System.Drawing.Size(249, 26);
            this.m_newPassword1TextBox.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(6, 70);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(183, 23);
            this.label3.TabIndex = 19;
            this.label3.Text = "Nouveau mot de passe";
            // 
            // m_oldPasswordTextBox
            // 
            this.m_oldPasswordTextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_oldPasswordTextBox.Location = new System.Drawing.Point(207, 31);
            this.m_oldPasswordTextBox.Name = "m_oldPasswordTextBox";
            this.m_oldPasswordTextBox.Size = new System.Drawing.Size(249, 26);
            this.m_oldPasswordTextBox.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(6, 31);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(167, 23);
            this.label2.TabIndex = 17;
            this.label2.Text = "Ancien mot de passe";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.m_changePasswordButton);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.m_oldPasswordTextBox);
            this.groupBox1.Controls.Add(this.text1);
            this.groupBox1.Controls.Add(this.m_newPassword2TextBox);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.m_newPassword1TextBox);
            this.groupBox1.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(12, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(472, 184);
            this.groupBox1.TabIndex = 29;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Mot de passe";
            // 
            // m_changePasswordButton
            // 
            this.m_changePasswordButton.Location = new System.Drawing.Point(348, 138);
            this.m_changePasswordButton.Name = "m_changePasswordButton";
            this.m_changePasswordButton.Size = new System.Drawing.Size(108, 30);
            this.m_changePasswordButton.TabIndex = 4;
            this.m_changePasswordButton.Text = "Envoyer";
            this.m_changePasswordButton.UseVisualStyleBackColor = true;
            this.m_changePasswordButton.Click += new System.EventHandler(this.m_changePasswordButton_Click);
            // 
            // text1
            // 
            this.text1.AutoSize = true;
            this.text1.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text1.Location = new System.Drawing.Point(6, 106);
            this.text1.Name = "text1";
            this.text1.Size = new System.Drawing.Size(88, 23);
            this.text1.TabIndex = 19;
            this.text1.Text = "Confirmer";
            // 
            // m_newPassword2TextBox
            // 
            this.m_newPassword2TextBox.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_newPassword2TextBox.Location = new System.Drawing.Point(207, 106);
            this.m_newPassword2TextBox.Name = "m_newPassword2TextBox";
            this.m_newPassword2TextBox.Size = new System.Drawing.Size(249, 26);
            this.m_newPassword2TextBox.TabIndex = 3;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.m_deleteImageButton);
            this.groupBox2.Controls.Add(this.m_profilPicture);
            this.groupBox2.Controls.Add(this.m_changeImageButton);
            this.groupBox2.Controls.Add(this.m_choseImageButton);
            this.groupBox2.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(490, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(239, 395);
            this.groupBox2.TabIndex = 30;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Image de profil";
            // 
            // m_deleteImageButton
            // 
            this.m_deleteImageButton.Location = new System.Drawing.Point(18, 291);
            this.m_deleteImageButton.Name = "m_deleteImageButton";
            this.m_deleteImageButton.Size = new System.Drawing.Size(210, 30);
            this.m_deleteImageButton.TabIndex = 12;
            this.m_deleteImageButton.Text = "Supprimer l\'image";
            this.m_deleteImageButton.UseVisualStyleBackColor = true;
            this.m_deleteImageButton.Click += new System.EventHandler(this.m_deleteImageButton_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.m_changeEmailButton);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.m_emailTextBox);
            this.groupBox3.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox3.Location = new System.Drawing.Point(12, 193);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(471, 90);
            this.groupBox3.TabIndex = 31;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Adresse électronique";
            // 
            // m_changeEmailButton
            // 
            this.m_changeEmailButton.Location = new System.Drawing.Point(348, 33);
            this.m_changeEmailButton.Name = "m_changeEmailButton";
            this.m_changeEmailButton.Size = new System.Drawing.Size(108, 30);
            this.m_changeEmailButton.TabIndex = 6;
            this.m_changeEmailButton.Text = "Envoyer";
            this.m_changeEmailButton.UseVisualStyleBackColor = true;
            this.m_changeEmailButton.Click += new System.EventHandler(this.m_changeEmailButton_Click);
            // 
            // m_changeTypeButton
            // 
            this.m_changeTypeButton.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_changeTypeButton.Location = new System.Drawing.Point(347, 28);
            this.m_changeTypeButton.Name = "m_changeTypeButton";
            this.m_changeTypeButton.Size = new System.Drawing.Size(108, 30);
            this.m_changeTypeButton.TabIndex = 10;
            this.m_changeTypeButton.Text = "Envoyer";
            this.m_changeTypeButton.UseVisualStyleBackColor = true;
            this.m_changeTypeButton.Click += new System.EventHandler(this.m_changeTypeButton_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.m_userRadioButton);
            this.groupBox4.Controls.Add(this.m_adminRadioButton);
            this.groupBox4.Controls.Add(this.m_adminLabel);
            this.groupBox4.Controls.Add(this.m_changeTypeButton);
            this.groupBox4.Controls.Add(this.m_adminTextBox);
            this.groupBox4.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox4.Location = new System.Drawing.Point(13, 290);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(470, 108);
            this.groupBox4.TabIndex = 32;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Catégorie de profil";
            // 
            // m_userRadioButton
            // 
            this.m_userRadioButton.AutoSize = true;
            this.m_userRadioButton.Location = new System.Drawing.Point(170, 28);
            this.m_userRadioButton.Name = "m_userRadioButton";
            this.m_userRadioButton.Size = new System.Drawing.Size(164, 27);
            this.m_userRadioButton.TabIndex = 8;
            this.m_userRadioButton.TabStop = true;
            this.m_userRadioButton.Text = "Simple utilisateur";
            this.m_userRadioButton.UseVisualStyleBackColor = true;
            // 
            // m_adminRadioButton
            // 
            this.m_adminRadioButton.AutoSize = true;
            this.m_adminRadioButton.Location = new System.Drawing.Point(20, 28);
            this.m_adminRadioButton.Name = "m_adminRadioButton";
            this.m_adminRadioButton.Size = new System.Drawing.Size(135, 27);
            this.m_adminRadioButton.TabIndex = 7;
            this.m_adminRadioButton.TabStop = true;
            this.m_adminRadioButton.Text = "Adminitrateur";
            this.m_adminRadioButton.UseVisualStyleBackColor = true;
            this.m_adminRadioButton.CheckedChanged += new System.EventHandler(this.m_adminRadioButton_CheckedChanged);
            // 
            // ProfileSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(745, 412);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "ProfileSettings";
            this.Text = "Gestion de profil";
            ((System.ComponentModel.ISupportInitialize)(this.m_profilPicture)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox m_profilPicture;
        private System.Windows.Forms.Button m_choseImageButton;
        private System.Windows.Forms.TextBox m_adminTextBox;
        private System.Windows.Forms.Label m_adminLabel;
        private System.Windows.Forms.Button m_changeImageButton;
        private System.Windows.Forms.TextBox m_emailTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox m_newPassword1TextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox m_oldPasswordTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label text1;
        private System.Windows.Forms.TextBox m_newPassword2TextBox;
        private System.Windows.Forms.Button m_changePasswordButton;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button m_changeEmailButton;
        private System.Windows.Forms.Button m_changeTypeButton;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.RadioButton m_userRadioButton;
        private System.Windows.Forms.RadioButton m_adminRadioButton;
        private System.Windows.Forms.Button m_deleteImageButton;
        private System.Windows.Forms.OpenFileDialog m_choseImageDialog;
    }
}