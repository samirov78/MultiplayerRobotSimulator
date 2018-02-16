namespace InterfaceGraphique
{
    partial class Simulation
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
            this.toolStripContainer = new System.Windows.Forms.ToolStripContainer();
            this.scene = new System.Windows.Forms.Panel();
            this.fdroite = new System.Windows.Forms.PictureBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.fhaut = new System.Windows.Forms.PictureBox();
            this.fbas = new System.Windows.Forms.PictureBox();
            this.button13 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.text1 = new System.Windows.Forms.Label();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalCtrlQToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.modeEditionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.premièrePersonneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.profilsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripContainer.ContentPanel.SuspendLayout();
            this.toolStripContainer.TopToolStripPanel.SuspendLayout();
            this.toolStripContainer.SuspendLayout();
            this.scene.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fdroite)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fhaut)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fbas)).BeginInit();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStripContainer
            // 
            // 
            // toolStripContainer.BottomToolStripPanel
            // 
            this.toolStripContainer.BottomToolStripPanel.Enabled = false;
            // 
            // toolStripContainer.ContentPanel
            // 
            this.toolStripContainer.ContentPanel.Controls.Add(this.scene);
            this.toolStripContainer.ContentPanel.Size = new System.Drawing.Size(960, 525);
            this.toolStripContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolStripContainer.LeftToolStripPanelVisible = false;
            this.toolStripContainer.Location = new System.Drawing.Point(0, 0);
            this.toolStripContainer.Name = "toolStripContainer";
            this.toolStripContainer.RightToolStripPanelVisible = false;
            this.toolStripContainer.Size = new System.Drawing.Size(960, 549);
            this.toolStripContainer.TabIndex = 1;
            this.toolStripContainer.TabStop = false;
            this.toolStripContainer.Text = "toolStripContainer";
            // 
            // toolStripContainer.TopToolStripPanel
            // 
            this.toolStripContainer.TopToolStripPanel.Controls.Add(this.menuStrip);
            // 
            // scene
            // 
            this.scene.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.scene.Controls.Add(this.fdroite);
            this.scene.Controls.Add(this.label4);
            this.scene.Controls.Add(this.label3);
            this.scene.Controls.Add(this.label2);
            this.scene.Controls.Add(this.label1);
            this.scene.Controls.Add(this.fhaut);
            this.scene.Controls.Add(this.fbas);
            this.scene.Controls.Add(this.button13);
            this.scene.Controls.Add(this.button12);
            this.scene.Controls.Add(this.button11);
            this.scene.Controls.Add(this.button9);
            this.scene.Controls.Add(this.button8);
            this.scene.Controls.Add(this.button7);
            this.scene.Controls.Add(this.button6);
            this.scene.Controls.Add(this.button5);
            this.scene.Controls.Add(this.button4);
            this.scene.Controls.Add(this.button3);
            this.scene.Controls.Add(this.text1);
            this.scene.Dock = System.Windows.Forms.DockStyle.Fill;
            this.scene.Location = new System.Drawing.Point(0, 0);
            this.scene.MinimumSize = new System.Drawing.Size(100, 100);
            this.scene.Name = "scene";
            this.scene.Size = new System.Drawing.Size(960, 525);
            this.scene.TabIndex = 1;
            this.scene.Paint += new System.Windows.Forms.PaintEventHandler(this.scene_Paint);
            this.scene.MouseDown += new System.Windows.Forms.MouseEventHandler(this.scene_MouseDown);
            this.scene.MouseEnter += new System.EventHandler(this.scene_MouseEnter);
            this.scene.MouseMove += new System.Windows.Forms.MouseEventHandler(this.scene_MouseMove);
            this.scene.MouseUp += new System.Windows.Forms.MouseEventHandler(this.scene_MouseUp);
            this.scene.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.scene_MouseWheel);
            this.scene.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.scene_PreviewKeyDown);
            // 
            // fdroite
            // 
            this.fdroite.Image = global::InterfaceGraphique.Properties.Resources.webmaster_fleches027g;
            this.fdroite.Location = new System.Drawing.Point(216, 241);
            this.fdroite.Name = "fdroite";
            this.fdroite.Size = new System.Drawing.Size(33, 34);
            this.fdroite.TabIndex = 20;
            this.fdroite.TabStop = false;
            this.fdroite.Visible = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(61, 127);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(211, 13);
            this.label4.TabIndex = 19;
            this.label4.Text = "appuyez sur le W pour que le robot avance";
            this.label4.Visible = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(200, 452);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(219, 26);
            this.label3.TabIndex = 18;
            this.label3.Text = "Attention : les autres bouttons ne s\'activeront\r\nsauf si votre robot sera en mode" +
    " manuel";
            this.label3.Visible = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(568, 98);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 17;
            this.label2.Text = "label2";
            this.label2.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(200, 411);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(178, 26);
            this.label1.TabIndex = 16;
            this.label1.Text = "appuyez sur le boutton espace pour\r\nchanger le mode de control du robot";
            this.label1.Visible = false;
            // 
            // fhaut
            // 
            this.fhaut.Image = global::InterfaceGraphique.Properties.Resources.fleche_gif_012__1_;
            this.fhaut.Location = new System.Drawing.Point(253, 363);
            this.fhaut.Name = "fhaut";
            this.fhaut.Size = new System.Drawing.Size(28, 34);
            this.fhaut.TabIndex = 15;
            this.fhaut.TabStop = false;
            this.fhaut.Visible = false;
            // 
            // fbas
            // 
            this.fbas.Image = global::InterfaceGraphique.Properties.Resources.fleche_gif_014;
            this.fbas.Location = new System.Drawing.Point(131, 156);
            this.fbas.Name = "fbas";
            this.fbas.Size = new System.Drawing.Size(28, 33);
            this.fbas.TabIndex = 14;
            this.fbas.TabStop = false;
            this.fbas.Visible = false;
            // 
            // button13
            // 
            this.button13.Enabled = false;
            this.button13.Location = new System.Drawing.Point(188, 313);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(178, 44);
            this.button13.TabIndex = 13;
            this.button13.Text = "Space";
            this.button13.UseVisualStyleBackColor = true;
            this.button13.Visible = false;
            this.button13.Click += new System.EventHandler(this.button13_Click);
            // 
            // button12
            // 
            this.button12.Enabled = false;
            this.button12.Location = new System.Drawing.Point(121, 313);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(70, 44);
            this.button12.TabIndex = 12;
            this.button12.Text = "Alt";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Visible = false;
            // 
            // button11
            // 
            this.button11.Enabled = false;
            this.button11.Location = new System.Drawing.Point(177, 195);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(70, 41);
            this.button11.TabIndex = 11;
            this.button11.Text = "E";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Visible = false;
            // 
            // button9
            // 
            this.button9.Enabled = false;
            this.button9.Location = new System.Drawing.Point(8, 235);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(58, 40);
            this.button9.TabIndex = 9;
            this.button9.Text = "A";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Visible = false;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // button8
            // 
            this.button8.Enabled = false;
            this.button8.Location = new System.Drawing.Point(177, 274);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(70, 41);
            this.button8.TabIndex = 8;
            this.button8.Text = "X";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Visible = false;
            // 
            // button7
            // 
            this.button7.Enabled = false;
            this.button7.Location = new System.Drawing.Point(38, 195);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(73, 41);
            this.button7.TabIndex = 7;
            this.button7.Text = "Q";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Visible = false;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button6
            // 
            this.button6.Enabled = false;
            this.button6.Location = new System.Drawing.Point(64, 235);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(84, 41);
            this.button6.TabIndex = 6;
            this.button6.Text = "S";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Visible = false;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button5
            // 
            this.button5.Enabled = false;
            this.button5.Location = new System.Drawing.Point(110, 195);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(69, 41);
            this.button5.TabIndex = 5;
            this.button5.Text = "W";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Visible = false;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button4
            // 
            this.button4.Enabled = false;
            this.button4.Location = new System.Drawing.Point(145, 235);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(65, 41);
            this.button4.TabIndex = 4;
            this.button4.Text = "D";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Visible = false;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button3
            // 
            this.button3.Enabled = false;
            this.button3.Location = new System.Drawing.Point(110, 274);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(70, 41);
            this.button3.TabIndex = 3;
            this.button3.Text = "Z";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Visible = false;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // text1
            // 
            this.text1.AutoSize = true;
            this.text1.Location = new System.Drawing.Point(3, 75);
            this.text1.Name = "text1";
            this.text1.Size = new System.Drawing.Size(259, 52);
            this.text1.TabIndex = 2;
            this.text1.Text = "bienveune  a ce tutoriel :\r\nceci est votre clavier visuel : utiliser le pour appr" +
    "endre\r\na faire bouger votre robot et changer de mode control\r\n\r\n";
            this.text1.Visible = false;
            this.text1.Click += new System.EventHandler(this.text1_Click);
            // 
            // menuStrip
            // 
            this.menuStrip.Dock = System.Windows.Forms.DockStyle.None;
            this.menuStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.vuesToolStripMenuItem,
            this.profilsToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(960, 24);
            this.menuStrip.TabIndex = 2;
            this.menuStrip.Text = "menuStrip";
            this.menuStrip.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip_ItemClicked);
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuPrincipalCtrlQToolStripMenuItem,
            this.modeEditionToolStripMenuItem});
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.fichierToolStripMenuItem.Text = "Fichier";
            // 
            // menuPrincipalCtrlQToolStripMenuItem
            // 
            this.menuPrincipalCtrlQToolStripMenuItem.Name = "menuPrincipalCtrlQToolStripMenuItem";
            this.menuPrincipalCtrlQToolStripMenuItem.ShortcutKeyDisplayString = "Ctrl-Q";
            this.menuPrincipalCtrlQToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.menuPrincipalCtrlQToolStripMenuItem.Text = "Menu principal";
            this.menuPrincipalCtrlQToolStripMenuItem.Click += new System.EventHandler(this.menuPrincipalCtrlQToolStripMenuItem_Click);
            // 
            // modeEditionToolStripMenuItem
            // 
            this.modeEditionToolStripMenuItem.Name = "modeEditionToolStripMenuItem";
            this.modeEditionToolStripMenuItem.Size = new System.Drawing.Size(194, 22);
            this.modeEditionToolStripMenuItem.Text = "Mode Édition";
            this.modeEditionToolStripMenuItem.Click += new System.EventHandler(this.modeEditionToolStripMenuItem_Click);
            // 
            // vuesToolStripMenuItem
            // 
            this.vuesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueToolStripMenuItem,
            this.orbiteToolStripMenuItem,
            this.premièrePersonneToolStripMenuItem});
            this.vuesToolStripMenuItem.Name = "vuesToolStripMenuItem";
            this.vuesToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.vuesToolStripMenuItem.Text = "Vues";
            this.vuesToolStripMenuItem.Click += new System.EventHandler(this.vuesToolStripMenuItem_Click);
            // 
            // orthographiqueToolStripMenuItem
            // 
            this.orthographiqueToolStripMenuItem.Name = "orthographiqueToolStripMenuItem";
            this.orthographiqueToolStripMenuItem.ShortcutKeyDisplayString = "1";
            this.orthographiqueToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.orthographiqueToolStripMenuItem.Text = "Orthographique";
            this.orthographiqueToolStripMenuItem.Click += new System.EventHandler(this.orthographiqueToolStripMenuItem_Click);
            // 
            // orbiteToolStripMenuItem
            // 
            this.orbiteToolStripMenuItem.Name = "orbiteToolStripMenuItem";
            this.orbiteToolStripMenuItem.ShortcutKeyDisplayString = "2";
            this.orbiteToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.orbiteToolStripMenuItem.Text = "Orbite";
            this.orbiteToolStripMenuItem.Click += new System.EventHandler(this.orbiteToolStripMenuItem_Click);
            // 
            // premièrePersonneToolStripMenuItem
            // 
            this.premièrePersonneToolStripMenuItem.Name = "premièrePersonneToolStripMenuItem";
            this.premièrePersonneToolStripMenuItem.ShortcutKeyDisplayString = "3";
            this.premièrePersonneToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.premièrePersonneToolStripMenuItem.Text = "Première personne";
            this.premièrePersonneToolStripMenuItem.Click += new System.EventHandler(this.premièrePersonneToolStripMenuItem_Click);
            // 
            // profilsToolStripMenuItem
            // 
            this.profilsToolStripMenuItem.Name = "profilsToolStripMenuItem";
            this.profilsToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.profilsToolStripMenuItem.Text = "Profils";
            // 
            // Simulation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CausesValidation = false;
            this.ClientSize = new System.Drawing.Size(960, 549);
            this.Controls.Add(this.toolStripContainer);
            this.KeyPreview = true;
            this.MainMenuStrip = this.menuStrip;
            this.MinimumSize = new System.Drawing.Size(710, 210);
            this.Name = "Simulation";
            this.Text = "Simulation";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Simulation_FormClosing);
            this.Load += new System.EventHandler(this.Simulation_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Simulation_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Simulation_KeyUp);
            this.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.Simulation_PreviewKeyDown);
            this.Resize += new System.EventHandler(this.Simulation_Resize);
            this.toolStripContainer.ContentPanel.ResumeLayout(false);
            this.toolStripContainer.TopToolStripPanel.ResumeLayout(false);
            this.toolStripContainer.TopToolStripPanel.PerformLayout();
            this.toolStripContainer.ResumeLayout(false);
            this.toolStripContainer.PerformLayout();
            this.scene.ResumeLayout(false);
            this.scene.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fdroite)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fhaut)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fbas)).EndInit();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ToolStripContainer toolStripContainer;
        private System.Windows.Forms.Panel scene;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalCtrlQToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem vuesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orbiteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem premièrePersonneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem profilsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem modeEditionToolStripMenuItem;
        public System.Windows.Forms.Label text1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button12;
        public System.Windows.Forms.Button button7;
        private System.Windows.Forms.PictureBox fbas;
        private System.Windows.Forms.PictureBox fhaut;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.PictureBox fdroite;
    }
}

