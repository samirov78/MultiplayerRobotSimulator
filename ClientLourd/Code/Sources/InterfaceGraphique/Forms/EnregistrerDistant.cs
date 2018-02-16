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
    public partial class EnregistrerDistant : Form
    {
        public EnregistrerDistant()
        {
            InitializeComponent();
            Program.SDispatcher.EditionConnectionM.CardSaved += UnscribeAndClose;
        }

        private void UnscribeAndClose(string name, bool onLigne)
        {
            Program.SDispatcher.EditionConnectionM.CardSaved -= UnscribeAndClose;
            Close();
        }

        private void m_cardNameTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && !char.IsLetter(e.KeyChar) &&
                (e.KeyChar != '_'))
            {
                e.Handled = true;
            }
        }

        private void m_saveButton_Click(object sender, EventArgs e)
        {
            if (m_privateRadioButton.Checked == true && m_passwordTextBox.Text.Length < 4)
            {
                MessageBox.Show("Le mot de passe doit être de longueur supérieure ou égale à quatre");
                return;
            }
            FonctionsNatives.enregistrerZoneDeSimulation(Edition.ServerTempCardName);
            string password = "";
            if (m_privateRadioButton.Checked == true)
                password = m_passwordTextBox.Text;
            Program.SDispatcher.EditionConnectionM.SaveCard(m_cardNameTextBox.Text, Edition.ServerTempCardName, password, 
                m_onLigneCheckBox.Checked);
        }

        private void m_privateRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            m_passwordTextBox.Visible = true;
            m_passwordLabel.Visible = true;
            m_passwordTextBox.Focus();
        }

        private void m_publicRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            m_passwordTextBox.Visible = false;
            m_passwordLabel.Visible = false;
        }
    }
}
