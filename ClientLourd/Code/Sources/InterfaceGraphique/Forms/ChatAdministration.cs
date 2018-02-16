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

namespace InterfaceGraphique.Forms
{
    public partial class ChatAdministration : Form
    {
        private delegate void OneParameterStringHandler(string chaine);

        public ChatAdministration()
        {
            InitializeComponent();
        }

        private void InappropriateWordsListReceived(string words)
        {
            Console.WriteLine("received ({0})", words);
            if (this.InvokeRequired)
            {
                this.Invoke(new OneParameterStringHandler(InappropriateWordsListReceived), words);
            }
            else
            {
                Console.WriteLine("i ll add ({0})", words);
                m_inappropriateComboBox.Items.Clear();
                m_inappropriateComboBox.Items.AddRange(words.Split(Utility.InappropriateWordsSeperator));
            }
        }

        private void m_addWordButton_Click(object sender, EventArgs e)
        {
            if (m_wordTextBox.Text.Trim() == "")
                MessageBox.Show("Le champs de mot à ajouter est vide");
            else
                Program.SDispatcher.ConfigurationConnectionM.AddInappropriateWord(m_wordTextBox.Text.Trim());
        }

        private void ChatAdministration_FormClosing(object sender, FormClosingEventArgs e)
        {
            Program.SDispatcher.ConfigurationConnectionM.InappropriateWordsListReceived -= InappropriateWordsListReceived;
        }

        private void m_deleteWordButton_Click(object sender, EventArgs e)
        {
            if (m_inappropriateComboBox.SelectedItem != null)
                Program.SDispatcher.ConfigurationConnectionM.RemoveInappropriateWord
                    (m_inappropriateComboBox.SelectedItem.ToString());
        }

        private void m_wordTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsLetter(e.KeyChar) && (e.KeyChar != '-') &&
               (e.KeyChar != ':') && (e.KeyChar != ' '))
            {
                e.Handled = true;
            }
        }

        private void ChatAdministration_Shown(object sender, EventArgs e)
        {
            Program.SDispatcher.ConfigurationConnectionM.InappropriateWordsListReceived += 
                InappropriateWordsListReceived;
            Program.SDispatcher.ConfigurationConnectionM.GetInappropriateWords();
        }
    }
}
