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
    public partial class ProfileSettings : Form
    {
        private string m_imageFile;

        public ProfileSettings()
        {
            InitializeComponent();
        }

        private void m_choseImageButton_Click(object sender, EventArgs e)
        {
            m_choseImageDialog.Filter = Utility.GetImageFilter();
            m_choseImageDialog.InitialDirectory = Path.Combine(Application.StartupPath, @"Images");
            m_choseImageDialog.RestoreDirectory = true;

            if (m_choseImageDialog.ShowDialog() == DialogResult.OK)
            {
                m_imageFile = m_choseImageDialog.FileName;
                m_profilPicture.ImageLocation = m_choseImageDialog.FileName;
            }
        }

        private void m_deleteImageButton_Click(object sender, EventArgs e)
        {
            m_profilPicture.Image = null;
            m_imageFile = null;
        }

        private void m_changeImageButton_Click(object sender, EventArgs e)
        {
            Program.SDispatcher.ConfigurationConnectionM.ChangeProfileImage(m_imageFile);
            this.Close();
        }

        private void m_changeEmailButton_Click(object sender, EventArgs e)
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
            else
                Program.SDispatcher.ConfigurationConnectionM.ChangeEmail(m_emailTextBox.Text);
            this.Close();
        }

        private void m_changePasswordButton_Click(object sender, EventArgs e)
        {
            if (m_oldPasswordTextBox.Text == "")
                MessageBox.Show("Le champs ancien mot de passse ne peut pas être vide");
            else if (m_newPassword1TextBox.Text == "")
                MessageBox.Show("Le premier champs nouveau mot de passse ne peut pas être vide");
            else if (m_newPassword1TextBox.Text != m_newPassword2TextBox.Text)
                MessageBox.Show("Les deux mots de passe ne sont pas les mêmes");
            else
                Program.SDispatcher.ConfigurationConnectionM.ChangePassword(m_oldPasswordTextBox.Text, 
                    m_newPassword1TextBox.Text);
            this.Close();
        }

        private void m_changeTypeButton_Click(object sender, EventArgs e)
        {
            if (m_adminRadioButton.Checked && m_adminTextBox.Text == "")
                MessageBox.Show("Vous souhaitez devenir administrateur,\nmais Le champ mot de passe de l'administrateur est vide");
            else
            {
                Program.SDispatcher.ConfigurationConnectionM.ChangeUserType(m_adminRadioButton.Checked ? "1" : "0",
                    m_adminTextBox.Text);
                this.Close();
            }
        }

        private void m_adminRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            if (m_adminRadioButton.Checked)
            {
                m_adminTextBox.Visible = true;
                m_adminLabel.Visible = true;
                m_adminTextBox.Focus();
            }
            else
            {
                m_adminTextBox.Visible = false;
                m_adminLabel.Visible = false; 
            }
        }
    }
}
