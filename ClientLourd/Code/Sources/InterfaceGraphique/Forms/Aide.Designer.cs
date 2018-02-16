namespace InterfaceGraphique
{
    partial class Aide
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean 
        /// 
        /// any resources being used.
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.help = new System.Windows.Forms.DataGridView();
            this.Actions = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.barreMenus = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.barreOutils = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.raccourcis = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.help)).BeginInit();
            this.SuspendLayout();
            // 
            // help
            // 
            this.help.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCellsExceptHeaders;
            this.help.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.help.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Actions,
            this.barreMenus,
            this.barreOutils,
            this.raccourcis});
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.help.DefaultCellStyle = dataGridViewCellStyle1;
            this.help.Dock = System.Windows.Forms.DockStyle.Fill;
            this.help.Location = new System.Drawing.Point(0, 0);
            this.help.Name = "help";
            this.help.RowTemplate.DefaultCellStyle.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.help.RowTemplate.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.help.Size = new System.Drawing.Size(554, 339);
            this.help.TabIndex = 0;
            this.help.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.help_CellContentClick);
            // 
            // Actions
            // 
            this.Actions.Frozen = true;
            this.Actions.HeaderText = "Actions";
            this.Actions.Name = "Actions";
            this.Actions.ReadOnly = true;
            this.Actions.Width = 215;
            // 
            // barreMenus
            // 
            this.barreMenus.Frozen = true;
            this.barreMenus.HeaderText = "Barre de menus";
            this.barreMenus.Name = "barreMenus";
            this.barreMenus.ReadOnly = true;
            // 
            // barreOutils
            // 
            this.barreOutils.Frozen = true;
            this.barreOutils.HeaderText = "Barre d\'outils";
            this.barreOutils.Name = "barreOutils";
            this.barreOutils.ReadOnly = true;
            // 
            // raccourcis
            // 
            this.raccourcis.Frozen = true;
            this.raccourcis.HeaderText = "Raccourcis";
            this.raccourcis.Name = "raccourcis";
            this.raccourcis.ReadOnly = true;
            // 
            // Aide
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.ClientSize = new System.Drawing.Size(554, 339);
            this.Controls.Add(this.help);
            this.Name = "Aide";
            this.Text = "Aide";
            ((System.ComponentModel.ISupportInitialize)(this.help)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView help;
        private System.Windows.Forms.DataGridViewTextBoxColumn Actions;
        private System.Windows.Forms.DataGridViewTextBoxColumn barreMenus;
        private System.Windows.Forms.DataGridViewTextBoxColumn barreOutils;
        private System.Windows.Forms.DataGridViewTextBoxColumn raccourcis;




    }
}