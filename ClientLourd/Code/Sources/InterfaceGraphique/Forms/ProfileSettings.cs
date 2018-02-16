using Commun;
using System;
using System.IO;
using System.Windows.Forms;
using Client;
using System.Collections.Generic;

namespace InterfaceGraphique.Forms
{
    public partial class ProfileSettings : Form
    {
        private string m_imageFile;
        private List<CardProfile> m_cards;
        private CardProfile m_selectedCard;

        public delegate void MyCardsReceivedHandler(List<CardProfile> cards);

        public ProfileSettings()
        {
            InitializeComponent();
            Program.SDispatcher.ConfigurationConnectionM.MyCardsReceived += HandleMyCardsReceived;
            Program.SDispatcher.ConfigurationConnectionM.GetMyCards();
            
            m_adminRadioButton.Checked = Program.SConnection.IsAdmin;
            m_userRadioButton.Checked = !Program.SConnection.IsAdmin;
            m_emailTextBox.Text = Program.SConnection.Email;
            m_profilPicture.ImageLocation = Program.SConnection.Image;
        }

        public void ShowAndClose()
        {
            this.ShowDialog();
            Program.SDispatcher.ConfigurationConnectionM.MyCardsReceived -= HandleMyCardsReceived;
        }

        private void HandleMyCardsReceived(List<CardProfile> cards)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new MyCardsReceivedHandler(HandleMyCardsReceived), cards);
            }
            else
            {
                m_cards = cards;
                foreach (CardProfile card in m_cards)
                {
                    m_cardsNamesCombo.Items.Add(card.name);
                }
                m_cardsNamesCombo.SelectedIndex = 0;
            }
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

        private void m_cardsNamesCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            string cardName = (string)m_cardsNamesCombo.SelectedItem;
            m_selectedCard = m_cards.Find((card) => card.name == cardName);
            m_scoreLabel.Text = m_selectedCard.score.ToString("0.00");
            m_publicPrivateCombo.SelectedItem = (m_selectedCard.password == "") ? "Public" : "Privée"; 
        }

        private void m_publicPrivateCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            string status = (string)m_publicPrivateCombo.SelectedItem;
            Console.WriteLine("Status : ({0})", status);
            if (status == "Public" && m_selectedCard.password == "")
            {
                m_cardPasswordLabel.Visible = false;
                m_cardPasswordText.Visible = false;
                m_newCardPasswordLabel.Visible = false;
                m_newCardPasswordText.Visible = false;
            }
            else if ((status == "Public" && m_selectedCard.password != "")
                || (status == "Privée" && m_selectedCard.password == ""))
            {
                m_cardPasswordLabel.Visible = true;
                m_cardPasswordText.Visible = true;
                m_newCardPasswordLabel.Visible = false;
                m_newCardPasswordText.Visible = false;
                m_cardPasswordText.Focus();
            }
            else
            {
                m_cardPasswordLabel.Visible = true;
                m_cardPasswordText.Visible = true;
                m_newCardPasswordLabel.Visible = true;
                m_newCardPasswordText.Visible = true;
                m_cardPasswordText.Focus();
            }
        }

        private void m_sendCardChangeButton_Click(object sender, EventArgs e)
        {
            string status = (string)m_publicPrivateCombo.SelectedItem;
            if (m_selectedCard.password == "")
            {
                if (status == "Public")
                {
                    MessageBox.Show("La carte est déja public");
                    return;
                }
                else
                {
                    string password = m_cardPasswordText.Text;
                    if (password.Length < 4)
                        MessageBox.Show("Le mot de passe doit être de longueur supérieure ou égale à 4");
                    else
                    {
                        ChangePassword(m_selectedCard.name, password);
                        Close();
                    }
                }
            }
            else
            {
                if (m_cardPasswordText.Text != m_selectedCard.password)
                    MessageBox.Show("L'ancien mot de passe de la carte est incorrect");
                else
                {
                    ChangePassword(m_selectedCard.name, m_newCardPasswordText.Text);
                    Close();
                }
            }
        }

        private void ChangePassword(string name, string password)
        {
            string message = name + Utility.CommandSeperator + Utility.Encode(password);
            Program.SConnection.Send((int)Utility.BasicCommand.Configuration, 
                (int)Utility.ConfigurationCommand.ChangeCardPassword, message);
        }
    }
}
