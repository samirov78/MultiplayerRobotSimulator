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
    public partial class Login : Form
    {
        private delegate void CloseHandler(string name);

        public Login()
        {
            InitializeComponent();
        }

        public void Run()
        {
            Program.SDispatcher.ConnectionM.LoggedIn += Close;
            ShowDialog();
        }

        private void m_connectButton_Click(object sender, EventArgs e)
        {
            if (m_idTextBox.Text.Trim() == "")
            {
                MessageBox.Show("Le champs Identifiant est vide");
                return;
            }

            string password = m_passwordTextBox.Text;
            if (password.Length < 4)
            {
                MessageBox.Show("Le mot de passe saisi est incorrect");
                return;
            }
            Program.SConnection.UserName = m_idTextBox.Text;
            
            Program.SDispatcher.ConnectionM.Login(password);
        }

        private void Close(string userName)
        {
            if (this.InvokeRequired)
                this.Invoke(new CloseHandler(Close), userName);
            else
                Close();
        }

        private void m_idTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsLetterOrDigit(e.KeyChar) && (e.KeyChar != '-') &&
                (e.KeyChar != '_') && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }
        }

        private void Login_FormClosing(object sender, FormClosingEventArgs e)
        {
            Program.SDispatcher.ConnectionM.LoggedIn -= Close;
        }
    }
}
