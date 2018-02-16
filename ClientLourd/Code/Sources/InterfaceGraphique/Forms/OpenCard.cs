using Commun;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class OpenCard : Form
    {
        private delegate void AddCardCallBack(string xml, string name, string password, string score);

        public OpenCard()
        {
            InitializeComponent();
            Program.SDispatcher.EditionConnectionM.CardPlusReceived += AddCard;
        }

        void AddCard(string xml, string name, string password , string score)
        {
            if (InvokeRequired)
            {
                Invoke(new AddCardCallBack(AddCard),xml, name, password, score);
            }
            else
            {
                Panel panel = new Panel();
                PictureBox pictureBox = new PictureBox();
                Label nameLabel = new Label();
                Label statusLabel = new Label();
                Label scoreLabel = new Label();
                ComboBox comboBox = new ComboBox();
                /*this.m_flowLayout.SuspendLayout();
                panel.SuspendLayout();
                ((System.ComponentModel.ISupportInitialize)(pictureBox)).BeginInit();
                this.SuspendLayout();*/
                //
                m_flowLayout.Controls.Add(panel);
                //
                panel.Controls.Add(nameLabel);
                panel.Controls.Add(statusLabel);
                panel.Controls.Add(scoreLabel);
                panel.Controls.Add(pictureBox);
                panel.Controls.Add(comboBox);
                panel.Font = new System.Drawing.Font("Sitka Small", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                //////panel.Location = new System.Drawing.Point(300, 3);
                //panel.Name = "panel1";
                panel.Size = new Size(184, 193);
                panel.TabIndex = 0;
                // 
                pictureBox.Location = new Point(15, 28);
                pictureBox.SizeMode = PictureBoxSizeMode.Zoom;
                pictureBox.BackColor = Color.Black;
                //pictureBox.Name = "pictureBox1";
                pictureBox.Size = new Size(152, 114);
                pictureBox.TabIndex = 0;
                pictureBox.TabStop = false;
                Card card = Card.ReadFromString(xml);
                Bitmap bitmap = card.GetBitmap(6);
                pictureBox.Image = (Bitmap)bitmap.Clone();
                //
                if (password != "")
                {
                    TextBox passwordText = new TextBox();
                    Button open = new Button();
                    panel.Controls.Add(passwordText);
                    panel.Controls.Add(open);
                    passwordText.Size = new Size(152, 14);
                    passwordText.Location = new Point(15, 28);
                    passwordText.PasswordChar = '*';
                    passwordText.Visible = false;

                    open.Size = new Size(67, 30);
                    open.Location = new Point(14, 118);
                    open.Text = "Ouvrir";
                    open.Visible = false;

                    passwordText.BringToFront();
                    open.BringToFront();

                    pictureBox.Click += (sender, e) =>
                    {
                        passwordText.Visible = true;
                        open.Visible = true;
                        passwordText.Focus();
                    };
                    open.Click += (sender, e) =>
                    {
                        if (passwordText.Text != password)
                        {
                            MessageBox.Show("Le mot de passe saisi est incorrect");
                        }
                        else
                        {
                            string option = (string)comboBox.SelectedItem;
                            Program.IsSpectator = (option == "Editeur" ? false : true);
                            Program.SDispatcher.EditionConnectionM.GetCard(name);
                            Close();
                        }
                    };
                }
                else
                {
                    pictureBox.Click += (sender, e) =>
                    {
                        string option = (string)comboBox.SelectedItem;
                        Program.IsSpectator = (option == "Editeur" ? false : true);
                        Program.SDispatcher.EditionConnectionM.GetCard(name);
                        Close();
                    };
                }
                // comboBox1
                // 
                comboBox.FormattingEnabled = true;
                comboBox.Font = new Font("Sitka Small", 10.8F, FontStyle.Regular, GraphicsUnit.Point, ((byte)(0)));

                comboBox.Items.AddRange(new object[] { "Editeur", "Spectateur"});
                comboBox.Location = new Point(81, 119);
                comboBox.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox.SelectedIndex = 0;
                //comboBox.Name = "comboBox1";
                comboBox.Size = new Size(87, 21);
                comboBox.TabIndex = 0;
                comboBox.BringToFront();
                //comboBox.ItemHeight = 15;
                //
                nameLabel.AutoSize = true;
                nameLabel.Location = new Point(15, 3);
                //nameLabel.Name = "label1";
                nameLabel.Size = new Size(90, 23);
                nameLabel.TabIndex = 1;
                nameLabel.Text = name;
                // 
                statusLabel.AutoSize = true;
                statusLabel.Location = new Point(15, 148);
                //statusLabel.Name = "label2";
                statusLabel.Size = new Size(115, 23);
                statusLabel.TabIndex = 2;
                statusLabel.Text = (password != "") ? "Privée" : "Public";
                // 
                // label3
                // 
                scoreLabel.AutoSize = true;
                scoreLabel.Location = new Point(15, 168);
                scoreLabel.Name = "label3";
                scoreLabel.Size = new Size(52, 23);
                scoreLabel.TabIndex = 3;
                scoreLabel.Text = "Score : " + score;
                // 
                /*this.m_flowLayout.ResumeLayout(false);
                panel.ResumeLayout(false);
                panel.PerformLayout();
                ((System.ComponentModel.ISupportInitialize)(pictureBox)).EndInit();
                this.ResumeLayout(false);*/
            }
        }

        private void OpenCard_FormClosing(object sender, FormClosingEventArgs e)
        {
            Program.SDispatcher.EditionConnectionM.CardPlusReceived -= AddCard;
        }
    }
}
