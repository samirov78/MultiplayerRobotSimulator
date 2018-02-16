namespace InterfaceGraphique
{
    partial class MenuPrincipale
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MenuPrincipale));
            this.bSimulation = new System.Windows.Forms.Button();
            this.bConfiguration = new System.Windows.Forms.Button();
            this.bEditeur = new System.Windows.Forms.Button();
            this.bQuitter = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.m_chatButton = new System.Windows.Forms.Button();
            this.m_connectionButton = new System.Windows.Forms.Button();
            this.m_nameLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // bSimulation
            // 
            this.bSimulation.BackColor = System.Drawing.Color.MidnightBlue;
            this.bSimulation.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bSimulation.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.bSimulation.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.bSimulation.Font = new System.Drawing.Font("Segoe Print", 16.125F);
            this.bSimulation.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.bSimulation.Location = new System.Drawing.Point(274, 79);
            this.bSimulation.Name = "bSimulation";
            this.bSimulation.Size = new System.Drawing.Size(221, 50);
            this.bSimulation.TabIndex = 0;
            this.bSimulation.Text = "Simulation";
            this.bSimulation.UseVisualStyleBackColor = false;
            this.bSimulation.Click += new System.EventHandler(this.bSimulation_Click);
            // 
            // bConfiguration
            // 
            this.bConfiguration.BackColor = System.Drawing.Color.MidnightBlue;
            this.bConfiguration.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bConfiguration.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.bConfiguration.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.bConfiguration.Font = new System.Drawing.Font("Segoe Print", 16.125F);
            this.bConfiguration.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.bConfiguration.Location = new System.Drawing.Point(274, 149);
            this.bConfiguration.Name = "bConfiguration";
            this.bConfiguration.Size = new System.Drawing.Size(221, 50);
            this.bConfiguration.TabIndex = 0;
            this.bConfiguration.Text = "Configuration";
            this.bConfiguration.UseVisualStyleBackColor = false;
            this.bConfiguration.Click += new System.EventHandler(this.bConfiguration_Click);
            // 
            // bEditeur
            // 
            this.bEditeur.BackColor = System.Drawing.Color.MidnightBlue;
            this.bEditeur.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bEditeur.FlatAppearance.BorderColor = System.Drawing.Color.DarkGreen;
            this.bEditeur.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.bEditeur.Font = new System.Drawing.Font("Segoe Print", 16.125F);
            this.bEditeur.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.bEditeur.Location = new System.Drawing.Point(274, 219);
            this.bEditeur.Name = "bEditeur";
            this.bEditeur.Size = new System.Drawing.Size(221, 50);
            this.bEditeur.TabIndex = 0;
            this.bEditeur.Text = "Editeur";
            this.bEditeur.UseVisualStyleBackColor = false;
            this.bEditeur.Click += new System.EventHandler(this.bEditeur_Click);
            // 
            // bQuitter
            // 
            this.bQuitter.BackColor = System.Drawing.Color.MidnightBlue;
            this.bQuitter.Cursor = System.Windows.Forms.Cursors.Hand;
            this.bQuitter.FlatAppearance.BorderColor = System.Drawing.Color.DarkGreen;
            this.bQuitter.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.bQuitter.Font = new System.Drawing.Font("Segoe Print", 16.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bQuitter.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.bQuitter.Location = new System.Drawing.Point(36, 219);
            this.bQuitter.Name = "bQuitter";
            this.bQuitter.Size = new System.Drawing.Size(221, 50);
            this.bQuitter.TabIndex = 0;
            this.bQuitter.Text = "Quitter";
            this.bQuitter.UseVisualStyleBackColor = false;
            this.bQuitter.Click += new System.EventHandler(this.bQuitter_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog";
            // 
            // m_chatButton
            // 
            this.m_chatButton.BackColor = System.Drawing.Color.MidnightBlue;
            this.m_chatButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.m_chatButton.FlatAppearance.BorderColor = System.Drawing.Color.DarkGreen;
            this.m_chatButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.m_chatButton.Font = new System.Drawing.Font("Segoe Print", 16.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_chatButton.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.m_chatButton.Location = new System.Drawing.Point(36, 149);
            this.m_chatButton.Name = "m_chatButton";
            this.m_chatButton.Size = new System.Drawing.Size(221, 50);
            this.m_chatButton.TabIndex = 0;
            this.m_chatButton.Text = "Clavardage";
            this.m_chatButton.UseVisualStyleBackColor = false;
            this.m_chatButton.Click += new System.EventHandler(this.m_chatButton_Click);
            // 
            // m_connectionButton
            // 
            this.m_connectionButton.BackColor = System.Drawing.Color.MidnightBlue;
            this.m_connectionButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.m_connectionButton.FlatAppearance.BorderColor = System.Drawing.Color.DarkGreen;
            this.m_connectionButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.m_connectionButton.Font = new System.Drawing.Font("Segoe Print", 16.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_connectionButton.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.m_connectionButton.Location = new System.Drawing.Point(36, 79);
            this.m_connectionButton.Name = "m_connectionButton";
            this.m_connectionButton.Size = new System.Drawing.Size(221, 50);
            this.m_connectionButton.TabIndex = 0;
            this.m_connectionButton.Text = "Connexion";
            this.m_connectionButton.UseVisualStyleBackColor = false;
            this.m_connectionButton.Click += new System.EventHandler(this.m_connectionButton_Click);
            // 
            // m_nameLabel
            // 
            this.m_nameLabel.AutoSize = true;
            this.m_nameLabel.BackColor = System.Drawing.Color.Transparent;
            this.m_nameLabel.Font = new System.Drawing.Font("Segoe Print", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_nameLabel.ForeColor = System.Drawing.Color.DarkSlateBlue;
            this.m_nameLabel.Location = new System.Drawing.Point(195, 315);
            this.m_nameLabel.Name = "m_nameLabel";
            this.m_nameLabel.Size = new System.Drawing.Size(0, 47);
            this.m_nameLabel.TabIndex = 1;
            // 
            // MenuPrincipale
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Menu;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.ClientSize = new System.Drawing.Size(534, 367);
            this.Controls.Add(this.m_nameLabel);
            this.Controls.Add(this.m_connectionButton);
            this.Controls.Add(this.m_chatButton);
            this.Controls.Add(this.bQuitter);
            this.Controls.Add(this.bEditeur);
            this.Controls.Add(this.bConfiguration);
            this.Controls.Add(this.bSimulation);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MenuPrincipale";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "INF2990-11 Simulateur de robot ";
            this.Load += new System.EventHandler(this.MenuPrincipale_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bSimulation;
        private System.Windows.Forms.Button bConfiguration;
        private System.Windows.Forms.Button bEditeur;
        private System.Windows.Forms.Button bQuitter;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Button m_chatButton;
        private System.Windows.Forms.Button m_connectionButton;
        private System.Windows.Forms.Label m_nameLabel;
    }
}