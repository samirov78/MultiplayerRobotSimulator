using Commun;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Forms
{
    public partial class CreateProfile : Form
    {
        public CreateProfile()
        {
            InitializeComponent();
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsLetterOrDigit(e.KeyChar) && (e.KeyChar != '-') &&
                (e.KeyChar != '_') && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }
        }

        private void m_createProfilButton_Click(object sender, EventArgs e)
        {
            if (m_loginTextBox.Text == "")
                MessageBox.Show("Le champs identifiant ne peut pas être vide");
            else if (m_loginTextBox.Text.ToLower() == "admin" || m_loginTextBox.Text.ToLower() == "administrateur")
                MessageBox.Show("L'identifiant choisi est réservé à l'administrateur");
            else if(m_firstNameTextBox.Text == "")
                MessageBox.Show("Le champs prénom ne peut pas être vide");
            else if (m_lastNameTextBox.Text == "")
                MessageBox.Show("Le champs nom ne peut pas être vide");
            else if (m_password1TextBox.Text == "")
                MessageBox.Show("Le premier champs mot de passse est vide");
            else if (m_password1TextBox.Text != m_password2TextBox.Text)
                MessageBox.Show("Les deux mots de passe ne sont pas les mêmes");
            else
            {
                DialogResult resultat;
                if (m_emailTextBox.Text == "")
                {
                    resultat = MessageBox.Show("Le champs adresse electronique est vide \nVoulez vous continuer quand même?",
                    "Champ vide", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
                    if (resultat == DialogResult.Cancel)
                        return;
                }
                if (m_emailTextBox.Text != "" && !Utility.IsValidEmail(m_emailTextBox.Text))
                    MessageBox.Show("Adresse electronique invalide");
                else if (m_adminCheckBox.Checked && m_adminPasswordTextBox.Text == "")
                    MessageBox.Show("Vous souhaitez de vous enregistrer comme administrateur,\nmais Le champ mot de passe de l'administrateur est vide");
                else
                {
                    Program.SDispatcher.ConfigurationConnectionM.CreateProfil(m_loginTextBox.Text, m_firstNameTextBox.Text,
                        m_lastNameTextBox.Text, m_password1TextBox.Text, m_emailTextBox.Text, m_adminCheckBox.Checked, 
                        m_adminPasswordTextBox.Text);
                    this.Close();
                }
            }
        }

        private void m_emailTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (char.IsWhiteSpace(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        private void m_adminCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_adminCheckBox.Checked)
            {
                m_adminPasswordTextBox.Visible = true;
                m_adminLabel.Visible = true;
                m_adminCheckBox.Focus();
            }
            else
            {
                m_adminPasswordTextBox.Visible = false;
                m_adminLabel.Visible = false;
            }
        }
    }
}