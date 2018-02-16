using System;
using System.Windows.Forms;
using Commun;

namespace InterfaceGraphique
{
    public partial class ConfigurationEnLigne : Form
    {
        public ConfigurationEnLigne()
        {
            InitializeComponent();
            m_ipTextBox.Text = Program.SConnection.IP;
            m_portTextBox.Text = Program.SConnection.Port.ToString();
            m_messageReceivedCheckBox.Checked = Program.SoundConfiguration.messageReceived;
            m_messageSentCheckBox.Checked = Program.SoundConfiguration.messageSent;
            m_imageReceivedCheckBox.Checked = Program.SoundConfiguration.imageReceived;
            m_imageSentCheckBox.Checked = Program.SoundConfiguration.imageSent;
            m_connectionCheckBox.Checked = Program.SoundConfiguration.logIn;
            m_disconnectionCheckBox.Checked = Program.SoundConfiguration.logOut;
        }

        private void m_portTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        private void m_ipTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) &&
                (e.KeyChar != '.'))
            {
                e.Handled = true;
            }
        }

        private void m_saveButton_Click(object sender, EventArgs e)
        {
            if (m_ipTextBox.Text == Program.SConnection.IP &&
                Int32.Parse(m_portTextBox.Text) == Program.SConnection.Port)
            {
                Close();
                return;
            }
            if (!Utility.IsValidIp(m_ipTextBox.Text))
            {
                MessageBox.Show("Adresse IP invalide");
            }
            else
            {
                if (!Utility.IsValidIp(m_ipTextBox.Text))
                    MessageBox.Show("Port Invalide (5000 - 5050)");
                else
                {
                    Program.SConnection.IP = m_ipTextBox.Text;
                    Program.SConnection.Port = Int32.Parse(m_portTextBox.Text);
                    Program.SConnection.WriteXML();
                    if (Program.SConnection.IsConnected)
                        Program.SConnection.Disconnect();
                    Close();
                }
            }
            
        }

        private void m_saveSoundButton_Click(object sender, EventArgs e)
        {
            Program.SoundConfiguration.messageReceived = m_messageReceivedCheckBox.Checked;
            Program.SoundConfiguration.messageSent = m_messageSentCheckBox.Checked;
            Program.SoundConfiguration.imageReceived = m_imageReceivedCheckBox.Checked;
            Program.SoundConfiguration.imageSent = m_imageSentCheckBox.Checked;
            Program.SoundConfiguration.logIn = m_connectionCheckBox.Checked;
            Program.SoundConfiguration.logOut = m_disconnectionCheckBox.Checked;
            Program.SoundConfiguration.Write("données/configuration-son");
            Close();
        }
    }
}
