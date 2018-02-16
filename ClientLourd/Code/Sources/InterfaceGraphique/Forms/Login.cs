using System;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class Login : Form
    {
        private delegate void CloseHandler(string name);

        public Login()
        {
            InitializeComponent();
            Program.SDispatcher.ConnectionM.AlreadyLoggedIn += AlreadyLoggedIn;
        }

        private void AlreadyLoggedIn()
        {
            MessageBox.Show("Ce nom d'utilisateur est déja connecté");
        }

        public void Run()
        {
            Program.SDispatcher.ConnectionM.LoggedIn += Close;
            ShowDialog();
        }

        private void m_idPasswordConnectButton_Click(object sender, EventArgs e)
        {
            if (m_idPasswordIdTextBox.Text.Trim() == "")
            {
                MessageBox.Show("Le champs Identifiant est vide");
                return;
            }

            string password = m_idPasswordPasswordTextBox.Text;
            if (password.Length < 4)
            {
                MessageBox.Show("Le mot de passe saisi est incorrect");
                return;
            }
            Program.SConnection.TempUserName = m_idPasswordIdTextBox.Text.Trim();
            
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
            Program.SDispatcher.ConnectionM.AlreadyLoggedIn -= AlreadyLoggedIn;
        }

        private void Login_Load(object sender, EventArgs e)
        {
            if (Program.SConnection.UserName != null && Program.SConnection.UserName != "")
            {
                m_idPasswordImagePanel.Visible = true;
                m_idPasswordPanel.Visible = false;
                m_idPasswordImageLoginLabel.Visible = true;
                m_idPasswordImageIdTextBox.Visible = true;
                m_anotherAcountButton.Visible = false;
                if (Program.SConnection.Image != null && Program.SConnection.Image != "")
                {
                    m_profilePictureBox.ImageLocation = Program.SConnection.Image;
                }
                if ((Program.SConnection.LastName != null && Program.SConnection.LastName != "")
                    || (Program.SConnection.FirstName != null && Program.SConnection.FirstName != ""))
                {
                    m_idPasswordImageNameLabel.Text = Program.SConnection.FirstName + " " + Program.SConnection.LastName;
                }
                else
                {
                    m_idPasswordImageNameLabel.Text = Program.SConnection.UserName;
                }
            }
            else
            {
                m_idPasswordImagePanel.Visible = false;
                m_idPasswordPanel.Visible = true;
            }
        }

        private void m_anotherAcountButton_Click(object sender, EventArgs e)
        {
            m_idPasswordImageIdTextBox.Visible = true;
            m_anotherAcountButton.Visible = false;
            m_idPasswordImageLoginLabel.Visible = true;
        }

        private void m_profilePictureBox_Click(object sender, EventArgs e)
        {
            m_idPasswordImageIdTextBox.Visible = false;
            m_anotherAcountButton.Visible = true;
            m_idPasswordImageLoginLabel.Visible = false;
        }

        private void m_idPasswordImageConnectButton_Click(object sender, EventArgs e)
        {
            if (m_idPasswordImageIdTextBox.Visible == true && m_idPasswordImageIdTextBox.Text.Trim() == "")
            {
                MessageBox.Show("Le champs Identifiant est vide");
                return;
            }

            string password = m_idPasswordImagePasswordTextBox.Text;
            if (password.Length < 4)
            {
                MessageBox.Show("Le mot de passe saisi est incorrect");
                return;
            }
            if(m_idPasswordImageIdTextBox.Visible == true)
                Program.SConnection.TempUserName = m_idPasswordImageIdTextBox.Text.Trim();
            else
                Program.SConnection.TempUserName = Program.SConnection.UserName;

            Program.SDispatcher.ConnectionM.Login(password);
        }
    }
}
