namespace InterfaceGraphique.Forms
{
    partial class ChatAdministration
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
            this.m_wordTextBox = new System.Windows.Forms.TextBox();
            this.m_addWordButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.m_inappropriateComboBox = new System.Windows.Forms.ComboBox();
            this.m_deleteWordButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(96, 19);
            this.label1.TabIndex = 0;
            this.label1.Text = "Nouveau mot";
            // 
            // m_wordTextBox
            // 
            this.m_wordTextBox.Location = new System.Drawing.Point(142, 48);
            this.m_wordTextBox.Name = "m_wordTextBox";
            this.m_wordTextBox.Size = new System.Drawing.Size(273, 24);
            this.m_wordTextBox.TabIndex = 1;
            this.m_wordTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_wordTextBox_KeyPress);
            // 
            // m_addWordButton
            // 
            this.m_addWordButton.Location = new System.Drawing.Point(430, 47);
            this.m_addWordButton.Name = "m_addWordButton";
            this.m_addWordButton.Size = new System.Drawing.Size(91, 28);
            this.m_addWordButton.TabIndex = 2;
            this.m_addWordButton.Text = "Ajouter";
            this.m_addWordButton.UseVisualStyleBackColor = true;
            this.m_addWordButton.Click += new System.EventHandler(this.m_addWordButton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 100);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(119, 19);
            this.label2.TabIndex = 3;
            this.label2.Text = "Mots enregistrés";
            // 
            // m_inappropriateComboBox
            // 
            this.m_inappropriateComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_inappropriateComboBox.FormattingEnabled = true;
            this.m_inappropriateComboBox.Location = new System.Drawing.Point(142, 92);
            this.m_inappropriateComboBox.Name = "m_inappropriateComboBox";
            this.m_inappropriateComboBox.Size = new System.Drawing.Size(273, 27);
            this.m_inappropriateComboBox.TabIndex = 4;
            // 
            // m_deleteWordButton
            // 
            this.m_deleteWordButton.Location = new System.Drawing.Point(430, 91);
            this.m_deleteWordButton.Name = "m_deleteWordButton";
            this.m_deleteWordButton.Size = new System.Drawing.Size(91, 28);
            this.m_deleteWordButton.TabIndex = 5;
            this.m_deleteWordButton.Text = "Supprimer";
            this.m_deleteWordButton.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.m_deleteWordButton.UseVisualStyleBackColor = true;
            this.m_deleteWordButton.Click += new System.EventHandler(this.m_deleteWordButton_Click);
            // 
            // ChatAdministration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 19F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(535, 177);
            this.Controls.Add(this.m_deleteWordButton);
            this.Controls.Add(this.m_inappropriateComboBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.m_addWordButton);
            this.Controls.Add(this.m_wordTextBox);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("Sitka Small", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "ChatAdministration";
            this.Text = "Administration de clavardage";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ChatAdministration_FormClosing);
            this.Shown += new System.EventHandler(this.ChatAdministration_Shown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox m_wordTextBox;
        private System.Windows.Forms.Button m_addWordButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox m_inappropriateComboBox;
        private System.Windows.Forms.Button m_deleteWordButton;
    }
}