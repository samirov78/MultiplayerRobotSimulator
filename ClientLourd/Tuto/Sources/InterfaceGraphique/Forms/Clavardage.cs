using Client;
using Commun;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Media;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class Clavardage : Form
    {
        private Dictionary<string, RichTextBox> m_messagesAreas;
        string m_selectedUser = null;


        /////////////// Delegates
        private delegate void NoParameterStringHandler();
        private delegate void EnableHandler(string message, bool enable);
        private delegate void OneParameterStringHandler(string chaine);
        private delegate void ThreeParametersStringHandler(string chaine1, string chaine2, string chaine3);
        private delegate void OneParameterArrayStringHandler(string[] chaines);
        private delegate void FourParametersStringHandler(string source, string content, string time, string destination);
        ////////////////////////

        ////Sounds
        private string messageSentSound = @"Sons\message-sent.wav";
        private string messageReceivedSound = @"Sons\message-received.wav";
        private string imageSentSound = @"Sons\image-sent.wav";
        private string imageReceivedSound = @"Sons\image-received.wav";

        public Clavardage()
        {
            InitializeComponent();
            EnableSendMessage("Vous êtes déconnecté", false);
            m_messagesAreas = new Dictionary<string, RichTextBox>();

            Program.SDispatcher.ConnectionM.LoggedIn += HandleLoggedIn;
            Program.SDispatcher.ConnectionM.LoggedOut += HandleLoggedOut;
            Program.SDispatcher.ConnectionM.NewUserLoggedIn += HandleNewUserLoggedIn;
            Program.SDispatcher.ConnectionM.UserLoggedOut += HandleUserLoggedOut;
            Program.SDispatcher.ConnectionM.NewLoggedInUsersList += HandleNewLoggedInUsersList;

            Program.SDispatcher.ChatConnectionM.NewMessageReceived += HandleNewMessageReceived;
            Program.SDispatcher.ChatConnectionM.ImageSent += HandleImageSent;
            Program.SDispatcher.ChatConnectionM.NewImageReceived += HandleNewImageReceived;
        }

        private void playSound(string file)
        {
            SoundPlayer simpleSound = new SoundPlayer(file);
            simpleSound.Play();
        }

        private void HandleImageSent(string imageName, string time, string destination)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new ThreeParametersStringHandler(HandleImageSent), imageName, time, destination);
            }
            else if (m_messagesAreas.ContainsKey(destination))
            {
                m_messagesAreas[destination].SelectionColor = Color.Maroon;
                m_messagesAreas[destination].AppendText("(" + time + ") " + "Vous avez envoyé une image à " + destination + " (" + imageName + ")\n");
                m_messagesAreas[destination].SelectionColor = m_messagesAreas[destination].ForeColor;
                m_connectedUsersListBox.SetSelected(m_connectedUsersListBox.FindStringExact(destination), true);
                m_messageRichTextBox.Focus();
                if (Program.edition.SoundConfiguration.imageSent)
                    playSound(imageSentSound);
            }
        }

        private void HandleNewImageReceived(string source, string imageName, string image, string timeStamp, string destination)
        {
            int i = 1;
            string name = Path.GetFileNameWithoutExtension(imageName);
            string extension = Path.GetExtension(imageName);
            while (File.Exists(@"Images/" + imageName))
            {
                imageName = name + i.ToString() + extension;
                i++;
            }
            File.WriteAllBytes(@"Images/" + imageName, Convert.FromBase64String(image));
            WriteImageReceived(source, imageName, timeStamp, destination);
            if (Program.edition.SoundConfiguration.imageReceived)
                playSound(imageReceivedSound);
        }

        private void WriteImageReceived(string source, string imageName, string time, string destination)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new FourParametersStringHandler(WriteImageReceived), source, imageName, time, destination);
            }
            else if (m_messagesAreas.ContainsKey(source))
            {
                m_messagesAreas[source].SelectionColor = Color.Maroon;
                m_messagesAreas[source].AppendText("(" + time + ") " + "Vous avez reçcu une image de " + source + " (" + imageName + ")\n");
                m_messagesAreas[source].SelectionColor = m_messagesAreas[source].ForeColor;
                m_connectedUsersListBox.SetSelected(m_connectedUsersListBox.FindStringExact(source), true);
                m_messageRichTextBox.Focus();
            }
        }

        private void HandleLoggedIn(string username)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new OneParameterStringHandler(HandleLoggedIn), username);
            }
            else
            {
                m_localUserNameLabel.Text = username;
                if (m_messagesAreas.Count > 0)
                    EnableSendMessage("", true);
                else
                    EnableSendMessage("Aucun utilisateur n'est connecté", false);
                m_messageRichTextBox.Focus();
            }
        }

        private void EnableSendMessage(string message, bool enable)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new EnableHandler(EnableSendMessage));
            }
            else
            {
                m_messageRichTextBox.Text = message;
                m_messageRichTextBox.Enabled = enable;
                m_effacerButton.Enabled = enable;
                m_sendButton.Enabled = enable;
                m_sendImageButton.Enabled = enable;
                EnableEmoticones(enable);
                m_messageRichTextBox.Focus();
            }
        }

        private void HandleLoggedOut(string name)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new OneParameterStringHandler(HandleLoggedOut), name);
            }
            else
            {
                foreach (string item in m_connectedUsersListBox.Items)
                {
                    m_disconnectedListBox.Items.Add(item);
                }
                m_connectedUsersListBox.Items.Clear();
                EnableSendMessage("Vous êtes déconnecté", false);
            }
        }

        private void HandleNewLoggedInUsersList(string[] users)
        {
            if (users != null)
            {
                if (this.InvokeRequired)
                {
                    this.Invoke(new OneParameterArrayStringHandler(HandleNewLoggedInUsersList), new object[] { users });
                }
                else
                {
                    foreach (string user in users)
                    {
                        if (!m_messagesAreas.ContainsKey(user))
                        {
                            m_messagesAreas.Add(user, CreateNewMessagesRichText());
                            this.Controls.Add(m_messagesAreas[user]);
                            m_connectedUsersListBox.Items.Add(user);
                        }
                        else if (m_disconnectedListBox.Items.Contains(user))
                        {
                            m_disconnectedListBox.Items.Remove(user);
                            m_connectedUsersListBox.Items.Add(user);
                        }
                    }
                    if (m_selectedUser == null)
                        m_connectedUsersListBox.SetSelected(0, true);
                    m_messageRichTextBox.Focus();
                }
            }
        }

        private void HandleNewMessageReceived(string source, string content, string time, string destination)
        {
            if (this.InvokeRequired)
                this.Invoke(new FourParametersStringHandler(HandleNewMessageReceived), source, content, time, destination);
            else
            {
                string area = source;
                Color color = Color.Blue;
                if (source == Program.SConnection.UserName)
                {
                    area = destination;
                    color = Color.Green;
                    if (Program.edition.SoundConfiguration.messageSent)
                        playSound(messageSentSound);
                }
                else if (Program.edition.SoundConfiguration.messageReceived)
                    playSound(messageReceivedSound);

                if (m_messagesAreas.ContainsKey(area))
                {
                    m_messagesAreas[area].SelectionColor = color;
                    m_messagesAreas[area].AppendText(source + " (" + time + ") : ");
                    m_messagesAreas[area].SelectionColor = m_messagesAreas[area].ForeColor;
                    AppendContent(m_messagesAreas[area], content);
                    m_connectedUsersListBox.SetSelected(m_connectedUsersListBox.FindStringExact(area), true);
                    m_messageRichTextBox.Focus();
                }
            }
        }

        private void AppendContent(RichTextBox richTextBox, string content)
        {
            char[] arrayContent = content.ToCharArray();
            int index = 0;
            for (; index < arrayContent.Length - 1; index++)
            {
                if (content[index] == ':')
                {
                    richTextBox.ReadOnly = false;
                    IDataObject orgData = Clipboard.GetDataObject();
                    switch (content[index + 1])
                    {
                        case ')':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\smile.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case '(':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\sad.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'D':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\big-smile.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'L':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\laugh.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'P':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\tongue.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'O':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\shout.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'G':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\glasses.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'V':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\devil.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'Z':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\sleep.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'H':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\love.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'R':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\rose.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        case 'C':
                            Clipboard.SetImage(Image.FromFile(@"emoticones\mobile.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.Paste();
                            index++;
                            break;
                        default:
                            richTextBox.AppendText(":");
                            break;
                    }
                    Clipboard.SetDataObject(orgData);
                    richTextBox.ReadOnly = true;
                }
                else if (content[index] == ';' && content[index + 1] == ')')
                {

                    richTextBox.ReadOnly = false;
                    IDataObject orgData = Clipboard.GetDataObject();
                    Clipboard.SetImage(Image.FromFile(@"emoticones\wink.png"));
                    richTextBox.SelectionStart = richTextBox.TextLength;
                    richTextBox.Paste();
                    Clipboard.SetDataObject(orgData);
                    richTextBox.ReadOnly = true;
                    index++;
                }
                else
                {
                    richTextBox.AppendText(content[index].ToString());
                }
            }
            if (index == arrayContent.Length - 1)
                richTextBox.AppendText(content[index].ToString());
            richTextBox.AppendText("\n");
        }

        private void HandleNewUserLoggedIn(string name)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new OneParameterStringHandler(HandleNewUserLoggedIn), name);
            }
            else
            {
                if (!m_messagesAreas.ContainsKey(name))
                {
                    m_messagesAreas.Add(name, CreateNewMessagesRichText());
                    this.Controls.Add(m_messagesAreas[name]);
                }
                else
                    m_disconnectedListBox.Items.Remove(name);
                m_connectedUsersListBox.Items.Add(name);
                m_messagesAreas[name].SelectionColor = Color.Blue;
                m_messagesAreas[name].AppendText(name + " Vient de se connecter\n");
                m_messagesAreas[name].SelectionColor = m_messagesAreas[name].ForeColor;

                if (m_selectedUser == null)
                    m_connectedUsersListBox.SetSelected(m_connectedUsersListBox.FindStringExact(name), true);
                m_messageRichTextBox.Focus();
            }
        }

        private void HandleUserLoggedOut(string name)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new OneParameterStringHandler(HandleUserLoggedOut), name);
            }
            else
            {
                if (m_messagesAreas.ContainsKey(name))
                {
                    m_messagesAreas[name].SelectionColor = Color.Red;
                    m_messagesAreas[name].AppendText(name + " Vient de se déconnecter\n");
                    m_messagesAreas[name].SelectionColor = m_messagesAreas[name].ForeColor;
                    m_connectedUsersListBox.Items.Remove(name);
                    m_disconnectedListBox.Items.Add(name);
                    m_disconnectedListBox.SetSelected(m_disconnectedListBox.FindStringExact(name), true);
                    m_messageRichTextBox.Focus();
                }
            }
        }

        private void m_sendButton_Click(object sender, EventArgs e)
        {
            if (m_selectedUser != null && m_messageRichTextBox.Text != "")
            {
                Program.SDispatcher.ChatConnectionM.SpreadMessage(m_messageRichTextBox.Text, DateTime.Now.ToShortTimeString(), m_selectedUser);
                m_messageRichTextBox.Text = "";
            }
        }

        private void m_effacerButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.Clear();
            m_messageRichTextBox.Focus();
        }

        private void m_messageRichTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    if (e.Modifiers == Keys.Shift)
                    {
                        m_messageRichTextBox.AppendText("\n");
                    }
                    else
                        m_sendButton_Click(null, null);
                    e.Handled = true;
                    break;
                default:
                    break;
            }
        }

        private void Clavardage_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private RichTextBox CreateNewMessagesRichText()
        {
            RichTextBox textBox = new RichTextBox();
            textBox.BackColor = System.Drawing.Color.SeaShell;
            textBox.HideSelection = false;
            textBox.Location = new System.Drawing.Point(20, 28);
            textBox.Name = "m_messagesRichTextBox";
            textBox.Size = new System.Drawing.Size(730, 305);
            textBox.TabIndex = 8;
            textBox.ReadOnly = true;
            textBox.Text = "";
            textBox.DetectUrls = true;
            textBox.LinkClicked += messagesArea_LinkClicked;

            return textBox;
        }

        private void m_connectedUsersListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListBox usersList = (ListBox)sender;

            if (usersList.SelectedIndex >= 0)
            {
                m_selectedUser = usersList.SelectedItem.ToString();
                m_userNameLabel.Text = m_selectedUser;
                m_messagesAreas[m_selectedUser].BringToFront();
                if (Program.SConnection.IsLoggedIn)
                    EnableSendMessage("", true);
            }
        }

        private void m_disconnectedListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListBox usersList = (ListBox)sender;

            if (usersList.SelectedIndex >= 0)
            {
                m_selectedUser = usersList.SelectedItem.ToString();
                m_userNameLabel.Text = m_selectedUser;
                m_messagesAreas[m_selectedUser].BringToFront();
                if (Program.SConnection.IsLoggedIn)
                    EnableSendMessage(m_selectedUser + " est déconnecté", false);
            }
        }

        private void m_sendImageButton_Click(object sender, EventArgs e)
        {
            choseImageDialog.Filter = Utility.GetImageFilter();
            //choseImageDialog.InitialDirectory = Path.Combine(Application.StartupPath, @"images");
            choseImageDialog.RestoreDirectory = true;

            if (choseImageDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string fileImage = choseImageDialog.FileName;
                byte[] imageBytes = File.ReadAllBytes(fileImage);
                Program.SDispatcher.ChatConnectionM.SendImage(Path.GetFileName(fileImage), imageBytes, DateTime.Now.ToShortTimeString(), m_selectedUser);
            }
        }

        private void m_smileButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":)");
            m_messageRichTextBox.Focus();
        }

        private void m_bigSmileButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":D");
            m_messageRichTextBox.Focus();
        }

        private void m_laughButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":L");
            m_messageRichTextBox.Focus();
        }

        private void m_tongueButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":P");
            m_messageRichTextBox.Focus();
        }

        private void m_surpriseButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":O");
            m_messageRichTextBox.Focus();
        }

        private void m_winkButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(";)");
            m_messageRichTextBox.Focus();
        }

        private void m_glacesButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":G");
            m_messageRichTextBox.Focus();
        }

        private void m_devilButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":V");
            m_messageRichTextBox.Focus();
        }

        private void m_spleepButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":Z");
            m_messageRichTextBox.Focus();
        }

        private void m_heartButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":H");
            m_messageRichTextBox.Focus();
        }

        private void m_roseButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":R");
            m_messageRichTextBox.Focus();
        }

        private void m_celButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":C");
            m_messageRichTextBox.Focus();
        }

        private void m_sadButton_Click(object sender, EventArgs e)
        {
            m_messageRichTextBox.AppendText(":(");
            m_messageRichTextBox.Focus();
        }

        private void EnableEmoticones(bool enable)
        {
            m_smileButton.Enabled = enable;
            m_bigSmileButton.Enabled = enable;
            m_devilButton.Enabled = enable;
            m_celButton.Enabled = enable;
            m_roseButton.Enabled = enable;
            m_heartButton.Enabled = enable;
            m_tongueButton.Enabled = enable;
            m_surpriseButton.Enabled = enable;
            m_laughButton.Enabled = enable;
            m_winkButton.Enabled = enable;
            m_spleepButton.Enabled = enable;
            m_glacesButton.Enabled = enable;
            m_sadButton.Enabled = enable;
        }

        private void messagesArea_LinkClicked(object sender, LinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start(e.LinkText);
        }
    }
}
