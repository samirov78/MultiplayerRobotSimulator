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
            this.m_chatPanel = new System.Windows.Forms.Panel();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalCtrlQToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.modeEditionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.premièrePersonneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.profilsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.informationsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tutorielToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripContainer.ContentPanel.SuspendLayout();
            this.toolStripContainer.TopToolStripPanel.SuspendLayout();
            this.toolStripContainer.SuspendLayout();
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
            this.toolStripContainer.ContentPanel.Controls.Add(this.m_chatPanel);
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
            this.scene.Dock = System.Windows.Forms.DockStyle.Fill;
            this.scene.Location = new System.Drawing.Point(0, 0);
            this.scene.MinimumSize = new System.Drawing.Size(100, 100);
            this.scene.Name = "scene";
            this.scene.Size = new System.Drawing.Size(704, 525);
            this.scene.TabIndex = 1;
            this.scene.MouseDown += new System.Windows.Forms.MouseEventHandler(this.scene_MouseDown);
            this.scene.MouseEnter += new System.EventHandler(this.scene_MouseEnter);
            this.scene.MouseMove += new System.Windows.Forms.MouseEventHandler(this.scene_MouseMove);
            this.scene.MouseUp += new System.Windows.Forms.MouseEventHandler(this.scene_MouseUp);
            this.scene.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.scene_MouseWheel);
            this.scene.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.scene_PreviewKeyDown);
            // 
            // m_chatPanel
            // 
            this.m_chatPanel.BackColor = System.Drawing.Color.GhostWhite;
            this.m_chatPanel.Dock = System.Windows.Forms.DockStyle.Right;
            this.m_chatPanel.Location = new System.Drawing.Point(704, 0);
            this.m_chatPanel.Name = "m_chatPanel";
            this.m_chatPanel.Size = new System.Drawing.Size(256, 525);
            this.m_chatPanel.TabIndex = 2;
            // 
            // menuStrip
            // 
            this.menuStrip.Dock = System.Windows.Forms.DockStyle.None;
            this.menuStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.vuesToolStripMenuItem,
            this.profilsToolStripMenuItem,
            this.informationsToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(960, 24);
            this.menuStrip.TabIndex = 2;
            this.menuStrip.Text = "menuStrip";
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
            // informationsToolStripMenuItem
            // 
            this.informationsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tutorielToolStripMenuItem});
            this.informationsToolStripMenuItem.Name = "informationsToolStripMenuItem";
            this.informationsToolStripMenuItem.Size = new System.Drawing.Size(87, 20);
            this.informationsToolStripMenuItem.Text = "Informations";
            // 
            // tutorielToolStripMenuItem
            // 
            this.tutorielToolStripMenuItem.Name = "tutorielToolStripMenuItem";
            this.tutorielToolStripMenuItem.Size = new System.Drawing.Size(115, 22);
            this.tutorielToolStripMenuItem.Text = "Tutoriel";
            this.tutorielToolStripMenuItem.Click += new System.EventHandler(this.tutorielToolStripMenuItem_Click);
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
        private System.Windows.Forms.ToolStripMenuItem informationsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tutorielToolStripMenuItem;
        public System.Windows.Forms.Panel m_chatPanel;
    }
}

