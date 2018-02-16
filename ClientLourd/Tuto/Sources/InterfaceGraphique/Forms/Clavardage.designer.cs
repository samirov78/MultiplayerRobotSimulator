namespace InterfaceGraphique
{
    partial class Clavardage
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.m_messageRichTextBox = new System.Windows.Forms.RichTextBox();
            this.m_sendButton = new System.Windows.Forms.Button();
            this.text1 = new System.Windows.Forms.Label();
            this.m_userNameLabel = new System.Windows.Forms.Label();
            this.m_localUserNameLabel = new System.Windows.Forms.Label();
            this.m_effacerButton = new System.Windows.Forms.Button();
            this.m_connectedUsersListBox = new System.Windows.Forms.ListBox();
            this.label2 = new System.Windows.Forms.Label();
            this.m_disconnectedListBox = new System.Windows.Forms.ListBox();
            this.m_sendImageButton = new System.Windows.Forms.Button();
            this.choseImageDialog = new System.Windows.Forms.OpenFileDialog();
            this.m_toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.m_smileButton = new System.Windows.Forms.Button();
            this.m_sadButton = new System.Windows.Forms.Button();
            this.m_celButton = new System.Windows.Forms.Button();
            this.m_tongueButton = new System.Windows.Forms.Button();
            this.m_spleepButton = new System.Windows.Forms.Button();
            this.m_glacesButton = new System.Windows.Forms.Button();
            this.m_winkButton = new System.Windows.Forms.Button();
            this.m_heartButton = new System.Windows.Forms.Button();
            this.m_laughButton = new System.Windows.Forms.Button();
            this.m_bigSmileButton = new System.Windows.Forms.Button();
            this.m_roseButton = new System.Windows.Forms.Button();
            this.m_surpriseButton = new System.Windows.Forms.Button();
            this.m_devilButton = new System.Windows.Forms.Button();
            this.m_emoticonesGroupBox = new System.Windows.Forms.GroupBox();
            this.m_emoticonesGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_messageRichTextBox
            // 
            this.m_messageRichTextBox.HideSelection = false;
            this.m_messageRichTextBox.Location = new System.Drawing.Point(20, 392);
            this.m_messageRichTextBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_messageRichTextBox.Name = "m_messageRichTextBox";
            this.m_messageRichTextBox.Size = new System.Drawing.Size(730, 100);
            this.m_messageRichTextBox.TabIndex = 5;
            this.m_messageRichTextBox.Text = "";
            this.m_messageRichTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.m_messageRichTextBox_KeyDown);
            // 
            // m_sendButton
            // 
            this.m_sendButton.Location = new System.Drawing.Point(668, 503);
            this.m_sendButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_sendButton.Name = "m_sendButton";
            this.m_sendButton.Size = new System.Drawing.Size(82, 40);
            this.m_sendButton.TabIndex = 7;
            this.m_sendButton.Text = "Envoyer";
            this.m_sendButton.UseVisualStyleBackColor = true;
            this.m_sendButton.Click += new System.EventHandler(this.m_sendButton_Click);
            // 
            // text1
            // 
            this.text1.AutoSize = true;
            this.text1.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.text1.Location = new System.Drawing.Point(773, 16);
            this.text1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.text1.Name = "text1";
            this.text1.Size = new System.Drawing.Size(139, 18);
            this.text1.TabIndex = 6;
            this.text1.Text = "Utilisateurs connectés";
            // 
            // m_userNameLabel
            // 
            this.m_userNameLabel.AutoSize = true;
            this.m_userNameLabel.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_userNameLabel.Location = new System.Drawing.Point(20, 7);
            this.m_userNameLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_userNameLabel.Name = "m_userNameLabel";
            this.m_userNameLabel.Size = new System.Drawing.Size(0, 18);
            this.m_userNameLabel.TabIndex = 6;
            this.m_userNameLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // m_localUserNameLabel
            // 
            this.m_localUserNameLabel.AutoSize = true;
            this.m_localUserNameLabel.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_localUserNameLabel.Location = new System.Drawing.Point(20, 367);
            this.m_localUserNameLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_localUserNameLabel.Name = "m_localUserNameLabel";
            this.m_localUserNameLabel.Size = new System.Drawing.Size(0, 18);
            this.m_localUserNameLabel.TabIndex = 6;
            // 
            // m_effacerButton
            // 
            this.m_effacerButton.Location = new System.Drawing.Point(580, 503);
            this.m_effacerButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_effacerButton.Name = "m_effacerButton";
            this.m_effacerButton.Size = new System.Drawing.Size(82, 40);
            this.m_effacerButton.TabIndex = 6;
            this.m_effacerButton.Text = "Effacer";
            this.m_effacerButton.UseVisualStyleBackColor = true;
            this.m_effacerButton.Click += new System.EventHandler(this.m_effacerButton_Click);
            // 
            // m_connectedUsersListBox
            // 
            this.m_connectedUsersListBox.BackColor = System.Drawing.Color.AliceBlue;
            this.m_connectedUsersListBox.FormattingEnabled = true;
            this.m_connectedUsersListBox.ItemHeight = 23;
            this.m_connectedUsersListBox.Location = new System.Drawing.Point(777, 39);
            this.m_connectedUsersListBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_connectedUsersListBox.Name = "m_connectedUsersListBox";
            this.m_connectedUsersListBox.Size = new System.Drawing.Size(199, 211);
            this.m_connectedUsersListBox.Sorted = true;
            this.m_connectedUsersListBox.TabIndex = 9;
            this.m_connectedUsersListBox.TabStop = false;
            this.m_connectedUsersListBox.SelectedIndexChanged += new System.EventHandler(this.m_connectedUsersListBox_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(774, 263);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(156, 18);
            this.label2.TabIndex = 6;
            this.label2.Text = "Déconnectés récemment";
            // 
            // m_disconnectedListBox
            // 
            this.m_disconnectedListBox.BackColor = System.Drawing.Color.AliceBlue;
            this.m_disconnectedListBox.FormattingEnabled = true;
            this.m_disconnectedListBox.ItemHeight = 23;
            this.m_disconnectedListBox.Location = new System.Drawing.Point(778, 285);
            this.m_disconnectedListBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_disconnectedListBox.Name = "m_disconnectedListBox";
            this.m_disconnectedListBox.Size = new System.Drawing.Size(198, 257);
            this.m_disconnectedListBox.Sorted = true;
            this.m_disconnectedListBox.TabIndex = 9;
            this.m_disconnectedListBox.TabStop = false;
            this.m_disconnectedListBox.SelectedIndexChanged += new System.EventHandler(this.m_disconnectedListBox_SelectedIndexChanged);
            // 
            // m_sendImageButton
            // 
            this.m_sendImageButton.Location = new System.Drawing.Point(559, 344);
            this.m_sendImageButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_sendImageButton.Name = "m_sendImageButton";
            this.m_sendImageButton.Size = new System.Drawing.Size(191, 40);
            this.m_sendImageButton.TabIndex = 10;
            this.m_sendImageButton.Text = "Envoyer une image ...";
            this.m_sendImageButton.UseVisualStyleBackColor = true;
            this.m_sendImageButton.Click += new System.EventHandler(this.m_sendImageButton_Click);
            // 
            // choseImageDialog
            // 
            this.choseImageDialog.FileName = "choseImageDialog";
            // 
            // m_toolTip
            // 
            this.m_toolTip.AutoPopDelay = 5000;
            this.m_toolTip.InitialDelay = 500;
            this.m_toolTip.ReshowDelay = 500;
            this.m_toolTip.ShowAlways = true;
            // 
            // m_smileButton
            // 
            this.m_smileButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_smileButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.smile1;
            this.m_smileButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_smileButton.FlatAppearance.BorderSize = 0;
            this.m_smileButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_smileButton.Location = new System.Drawing.Point(3, 11);
            this.m_smileButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_smileButton.Name = "m_smileButton";
            this.m_smileButton.Size = new System.Drawing.Size(40, 40);
            this.m_smileButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_smileButton, ":)");
            this.m_smileButton.UseVisualStyleBackColor = false;
            this.m_smileButton.Click += new System.EventHandler(this.m_smileButton_Click);
            // 
            // m_sadButton
            // 
            this.m_sadButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_sadButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.sad;
            this.m_sadButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_sadButton.FlatAppearance.BorderSize = 0;
            this.m_sadButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_sadButton.Location = new System.Drawing.Point(217, 12);
            this.m_sadButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_sadButton.Name = "m_sadButton";
            this.m_sadButton.Size = new System.Drawing.Size(40, 40);
            this.m_sadButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_sadButton, ":(");
            this.m_sadButton.UseVisualStyleBackColor = false;
            this.m_sadButton.Click += new System.EventHandler(this.m_sadButton_Click);
            // 
            // m_celButton
            // 
            this.m_celButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_celButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.mobile;
            this.m_celButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_celButton.FlatAppearance.BorderSize = 0;
            this.m_celButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_celButton.Location = new System.Drawing.Point(390, 12);
            this.m_celButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_celButton.Name = "m_celButton";
            this.m_celButton.Size = new System.Drawing.Size(40, 40);
            this.m_celButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_celButton, ":C");
            this.m_celButton.UseVisualStyleBackColor = false;
            this.m_celButton.Click += new System.EventHandler(this.m_celButton_Click);
            // 
            // m_tongueButton
            // 
            this.m_tongueButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_tongueButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.tongue;
            this.m_tongueButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_tongueButton.FlatAppearance.BorderSize = 0;
            this.m_tongueButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_tongueButton.Location = new System.Drawing.Point(173, 12);
            this.m_tongueButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_tongueButton.Name = "m_tongueButton";
            this.m_tongueButton.Size = new System.Drawing.Size(40, 40);
            this.m_tongueButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_tongueButton, ":P");
            this.m_tongueButton.UseVisualStyleBackColor = false;
            this.m_tongueButton.Click += new System.EventHandler(this.m_tongueButton_Click);
            // 
            // m_spleepButton
            // 
            this.m_spleepButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_spleepButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.sleep;
            this.m_spleepButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_spleepButton.FlatAppearance.BorderSize = 0;
            this.m_spleepButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_spleepButton.Location = new System.Drawing.Point(504, 12);
            this.m_spleepButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_spleepButton.Name = "m_spleepButton";
            this.m_spleepButton.Size = new System.Drawing.Size(40, 40);
            this.m_spleepButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_spleepButton, ":Z");
            this.m_spleepButton.UseVisualStyleBackColor = false;
            this.m_spleepButton.Click += new System.EventHandler(this.m_spleepButton_Click);
            // 
            // m_glacesButton
            // 
            this.m_glacesButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_glacesButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.glasses;
            this.m_glacesButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_glacesButton.FlatAppearance.BorderSize = 0;
            this.m_glacesButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_glacesButton.Location = new System.Drawing.Point(302, 12);
            this.m_glacesButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_glacesButton.Name = "m_glacesButton";
            this.m_glacesButton.Size = new System.Drawing.Size(40, 40);
            this.m_glacesButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_glacesButton, ":G");
            this.m_glacesButton.UseVisualStyleBackColor = false;
            this.m_glacesButton.Click += new System.EventHandler(this.m_glacesButton_Click);
            // 
            // m_winkButton
            // 
            this.m_winkButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_winkButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.wink;
            this.m_winkButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_winkButton.FlatAppearance.BorderSize = 0;
            this.m_winkButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_winkButton.Location = new System.Drawing.Point(129, 12);
            this.m_winkButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_winkButton.Name = "m_winkButton";
            this.m_winkButton.Size = new System.Drawing.Size(40, 40);
            this.m_winkButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_winkButton, ";)");
            this.m_winkButton.UseVisualStyleBackColor = false;
            this.m_winkButton.Click += new System.EventHandler(this.m_winkButton_Click);
            // 
            // m_heartButton
            // 
            this.m_heartButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_heartButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.love;
            this.m_heartButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_heartButton.FlatAppearance.BorderSize = 0;
            this.m_heartButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_heartButton.Location = new System.Drawing.Point(426, 12);
            this.m_heartButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_heartButton.Name = "m_heartButton";
            this.m_heartButton.Size = new System.Drawing.Size(40, 40);
            this.m_heartButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_heartButton, ":H");
            this.m_heartButton.UseVisualStyleBackColor = false;
            this.m_heartButton.Click += new System.EventHandler(this.m_heartButton_Click);
            // 
            // m_laughButton
            // 
            this.m_laughButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_laughButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.laugh;
            this.m_laughButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_laughButton.FlatAppearance.BorderSize = 0;
            this.m_laughButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_laughButton.Location = new System.Drawing.Point(86, 12);
            this.m_laughButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_laughButton.Name = "m_laughButton";
            this.m_laughButton.Size = new System.Drawing.Size(40, 40);
            this.m_laughButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_laughButton, ":L");
            this.m_laughButton.UseVisualStyleBackColor = false;
            this.m_laughButton.Click += new System.EventHandler(this.m_laughButton_Click);
            // 
            // m_bigSmileButton
            // 
            this.m_bigSmileButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_bigSmileButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.big_smile;
            this.m_bigSmileButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_bigSmileButton.FlatAppearance.BorderSize = 0;
            this.m_bigSmileButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_bigSmileButton.Location = new System.Drawing.Point(44, 11);
            this.m_bigSmileButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_bigSmileButton.Name = "m_bigSmileButton";
            this.m_bigSmileButton.Size = new System.Drawing.Size(40, 40);
            this.m_bigSmileButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_bigSmileButton, ":D");
            this.m_bigSmileButton.UseVisualStyleBackColor = false;
            this.m_bigSmileButton.Click += new System.EventHandler(this.m_bigSmileButton_Click);
            // 
            // m_roseButton
            // 
            this.m_roseButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_roseButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.rose;
            this.m_roseButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_roseButton.FlatAppearance.BorderSize = 0;
            this.m_roseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_roseButton.Location = new System.Drawing.Point(467, 11);
            this.m_roseButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_roseButton.Name = "m_roseButton";
            this.m_roseButton.Size = new System.Drawing.Size(40, 40);
            this.m_roseButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_roseButton, ":R");
            this.m_roseButton.UseVisualStyleBackColor = false;
            this.m_roseButton.Click += new System.EventHandler(this.m_roseButton_Click);
            // 
            // m_surpriseButton
            // 
            this.m_surpriseButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_surpriseButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.shout;
            this.m_surpriseButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_surpriseButton.FlatAppearance.BorderSize = 0;
            this.m_surpriseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_surpriseButton.Location = new System.Drawing.Point(259, 12);
            this.m_surpriseButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_surpriseButton.Name = "m_surpriseButton";
            this.m_surpriseButton.Size = new System.Drawing.Size(40, 40);
            this.m_surpriseButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_surpriseButton, ":O");
            this.m_surpriseButton.UseVisualStyleBackColor = false;
            this.m_surpriseButton.Click += new System.EventHandler(this.m_surpriseButton_Click);
            // 
            // m_devilButton
            // 
            this.m_devilButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_devilButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.devil;
            this.m_devilButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_devilButton.FlatAppearance.BorderSize = 0;
            this.m_devilButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_devilButton.Location = new System.Drawing.Point(346, 12);
            this.m_devilButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_devilButton.Name = "m_devilButton";
            this.m_devilButton.Size = new System.Drawing.Size(40, 40);
            this.m_devilButton.TabIndex = 11;
            this.m_toolTip.SetToolTip(this.m_devilButton, ":V");
            this.m_devilButton.UseVisualStyleBackColor = false;
            this.m_devilButton.Click += new System.EventHandler(this.m_devilButton_Click);
            // 
            // m_emoticonesGroupBox
            // 
            this.m_emoticonesGroupBox.Controls.Add(this.m_smileButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_sadButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_celButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_tongueButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_spleepButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_glacesButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_winkButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_heartButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_laughButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_bigSmileButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_roseButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_surpriseButton);
            this.m_emoticonesGroupBox.Controls.Add(this.m_devilButton);
            this.m_emoticonesGroupBox.Location = new System.Drawing.Point(20, 494);
            this.m_emoticonesGroupBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_emoticonesGroupBox.Name = "m_emoticonesGroupBox";
            this.m_emoticonesGroupBox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_emoticonesGroupBox.Size = new System.Drawing.Size(551, 54);
            this.m_emoticonesGroupBox.TabIndex = 12;
            this.m_emoticonesGroupBox.TabStop = false;
            // 
            // Clavardage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 23F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Menu;
            this.ClientSize = new System.Drawing.Size(990, 566);
            this.Controls.Add(this.m_emoticonesGroupBox);
            this.Controls.Add(this.m_sendImageButton);
            this.Controls.Add(this.m_disconnectedListBox);
            this.Controls.Add(this.m_connectedUsersListBox);
            this.Controls.Add(this.m_effacerButton);
            this.Controls.Add(this.m_localUserNameLabel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.m_userNameLabel);
            this.Controls.Add(this.text1);
            this.Controls.Add(this.m_messageRichTextBox);
            this.Controls.Add(this.m_sendButton);
            this.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "Clavardage";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Clavardage";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Clavardage_FormClosing);
            this.m_emoticonesGroupBox.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        //private System.Windows.Forms.RichTextBox m_messagesRichTextBox;
        private System.Windows.Forms.RichTextBox m_messageRichTextBox;
        private System.Windows.Forms.Button m_sendButton;
        private System.Windows.Forms.Label text1;
        private System.Windows.Forms.Label m_userNameLabel;
        private System.Windows.Forms.Label m_localUserNameLabel;
        private System.Windows.Forms.Button m_effacerButton;
        private System.Windows.Forms.ListBox m_connectedUsersListBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListBox m_disconnectedListBox;
        private System.Windows.Forms.Button m_sendImageButton;
        private System.Windows.Forms.OpenFileDialog choseImageDialog;
        private System.Windows.Forms.Button m_smileButton;
        private System.Windows.Forms.Button m_bigSmileButton;
        private System.Windows.Forms.Button m_laughButton;
        private System.Windows.Forms.Button m_tongueButton;
        private System.Windows.Forms.Button m_surpriseButton;
        private System.Windows.Forms.Button m_winkButton;
        private System.Windows.Forms.Button m_glacesButton;
        private System.Windows.Forms.Button m_devilButton;
        private System.Windows.Forms.Button m_spleepButton;
        private System.Windows.Forms.Button m_heartButton;
        private System.Windows.Forms.Button m_roseButton;
        private System.Windows.Forms.Button m_celButton;
        private System.Windows.Forms.ToolTip m_toolTip;
        private System.Windows.Forms.GroupBox m_emoticonesGroupBox;
        private System.Windows.Forms.Button m_sadButton;
    }
}

