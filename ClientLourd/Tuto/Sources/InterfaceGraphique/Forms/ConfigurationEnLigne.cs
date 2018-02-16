using System;
using System.Windows.Forms;
using Client;
using System.Xml.Serialization;
using System.IO;
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
            m_messageReceivedCheckBox.Checked = Program.edition.SoundConfiguration.messageReceived;
            m_messageSentCheckBox.Checked = Program.edition.SoundConfiguration.messageSent;
            m_imageReceivedCheckBox.Checked = Program.edition.SoundConfiguration.imageReceived;
            m_imageSentCheckBox.Checked = Program.edition.SoundConfiguration.imageSent;
            m_connectionCheckBox.Checked = Program.edition.SoundConfiguration.logIn;
            m_disconnectionCheckBox.Checked = Program.edition.SoundConfiguration.logOut;
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
                    XmlSerializer xs = new XmlSerializer(typeof(Connection));
                    using (StreamWriter wd = new StreamWriter("données/connexion.xml"))
                    {
                        xs.Serialize(wd, Program.SConnection);
                    }
                    if (Program.SConnection.IsConnected)
                    {
                        Program.SConnection.Disconnect();
                        Program.SConnection.ConnectToServer();
                    }
                    Close();
                }
            }
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void m_saveSoundButton_Click(object sender, EventArgs e)
        {
            Program.edition.SoundConfiguration.messageReceived = m_messageReceivedCheckBox.Checked;
            Program.edition.SoundConfiguration.messageSent = m_messageSentCheckBox.Checked;
            Program.edition.SoundConfiguration.imageReceived = m_imageReceivedCheckBox.Checked;
            Program.edition.SoundConfiguration.imageSent = m_imageSentCheckBox.Checked;
            Program.edition.SoundConfiguration.logIn = m_connectionCheckBox.Checked;
            Program.edition.SoundConfiguration.logOut = m_disconnectionCheckBox.Checked;
            Program.edition.SoundConfiguration.Write("données/configuration-son");
            Close();
        }
    }
}
