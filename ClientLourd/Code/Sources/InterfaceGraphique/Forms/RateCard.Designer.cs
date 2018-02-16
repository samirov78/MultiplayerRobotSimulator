namespace InterfaceGraphique.Forms
{
    partial class RateCard
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
            this.m_cardNameLabel = new System.Windows.Forms.Label();
            this.m_cardScoreLabel = new System.Windows.Forms.Label();
            this.m_rateNumeric = new System.Windows.Forms.NumericUpDown();
            this.m_rateLabel = new System.Windows.Forms.Label();
            this.m_saveButton = new System.Windows.Forms.Button();
            this.m_votesLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_rateNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // m_cardNameLabel
            // 
            this.m_cardNameLabel.AutoSize = true;
            this.m_cardNameLabel.Location = new System.Drawing.Point(23, 21);
            this.m_cardNameLabel.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.m_cardNameLabel.Name = "m_cardNameLabel";
            this.m_cardNameLabel.Size = new System.Drawing.Size(142, 23);
            this.m_cardNameLabel.TabIndex = 0;
            this.m_cardNameLabel.Text = "Nom de la carte :";
            // 
            // m_cardScoreLabel
            // 
            this.m_cardScoreLabel.AutoSize = true;
            this.m_cardScoreLabel.Location = new System.Drawing.Point(23, 111);
            this.m_cardScoreLabel.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.m_cardScoreLabel.Name = "m_cardScoreLabel";
            this.m_cardScoreLabel.Size = new System.Drawing.Size(68, 23);
            this.m_cardScoreLabel.TabIndex = 0;
            this.m_cardScoreLabel.Text = "Score : ";
            // 
            // m_rateNumeric
            // 
            this.m_rateNumeric.Location = new System.Drawing.Point(262, 111);
            this.m_rateNumeric.Margin = new System.Windows.Forms.Padding(5);
            this.m_rateNumeric.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.m_rateNumeric.Name = "m_rateNumeric";
            this.m_rateNumeric.Size = new System.Drawing.Size(46, 26);
            this.m_rateNumeric.TabIndex = 1;
            // 
            // m_rateLabel
            // 
            this.m_rateLabel.AutoSize = true;
            this.m_rateLabel.Location = new System.Drawing.Point(206, 113);
            this.m_rateLabel.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.m_rateLabel.Name = "m_rateLabel";
            this.m_rateLabel.Size = new System.Drawing.Size(46, 23);
            this.m_rateLabel.TabIndex = 2;
            this.m_rateLabel.Text = "Note";
            // 
            // m_saveButton
            // 
            this.m_saveButton.Location = new System.Drawing.Point(183, 153);
            this.m_saveButton.Margin = new System.Windows.Forms.Padding(5);
            this.m_saveButton.Name = "m_saveButton";
            this.m_saveButton.Size = new System.Drawing.Size(125, 41);
            this.m_saveButton.TabIndex = 3;
            this.m_saveButton.Text = "Enregistrer";
            this.m_saveButton.UseVisualStyleBackColor = true;
            this.m_saveButton.Click += new System.EventHandler(this.m_saveButton_Click);
            // 
            // m_votesLabel
            // 
            this.m_votesLabel.AutoSize = true;
            this.m_votesLabel.Location = new System.Drawing.Point(23, 66);
            this.m_votesLabel.Name = "m_votesLabel";
            this.m_votesLabel.Size = new System.Drawing.Size(150, 23);
            this.m_votesLabel.TabIndex = 4;
            this.m_votesLabel.Text = "Nombre de votes :";
            // 
            // RateCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 23F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(335, 206);
            this.Controls.Add(this.m_votesLabel);
            this.Controls.Add(this.m_saveButton);
            this.Controls.Add(this.m_rateLabel);
            this.Controls.Add(this.m_rateNumeric);
            this.Controls.Add(this.m_cardScoreLabel);
            this.Controls.Add(this.m_cardNameLabel);
            this.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(5);
            this.Name = "RateCard";
            this.Text = "Noter la carte en édition";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.RateCard_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.m_rateNumeric)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_cardNameLabel;
        private System.Windows.Forms.Label m_cardScoreLabel;
        private System.Windows.Forms.NumericUpDown m_rateNumeric;
        private System.Windows.Forms.Label m_rateLabel;
        private System.Windows.Forms.Button m_saveButton;
        private System.Windows.Forms.Label m_votesLabel;
    }
}