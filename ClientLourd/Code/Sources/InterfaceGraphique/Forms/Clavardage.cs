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
        private string m_selectedDestination = null;
        private DestinationType m_destinationType;

        private readonly ContextMenuStrip collectionRoundMenuStrip;
        private string m_selectedMenuItem;

        public DestinationType MessageDestinationType
        {
            get { return m_destinationType; }
            set {
                m_destinationType = value;
                m_quitGroupButton.Enabled = (m_destinationType == DestinationType.Group); 
            }
        }


        /////////////// Delegates
        private delegate void NoParameterStringHandler();
        private delegate void EnableHandler(string message, bool enable);
        private delegate void OneParameterStringHandler(string chaine);
        private delegate void ThreeParametersStringHandler(string chaine1, string chaine2, string chaine3);
        private delegate void OneParameterArrayStringHandler(string[] chaines);
        private delegate void FourParametersStringHandler(string source, string message, string time, string destination);
        private delegate void MessageReceivedCallback(string source, string message, string time, string destination, 
            DestinationType type);
        private delegate void HandleGroupsReceivedCallback(string[] groups);
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

            var toolStripMenuItem = new ToolStripMenuItem { Text = "Joindre le groupe" };
            toolStripMenuItem.Click += toolStripMenuItem_Click;
            collectionRoundMenuStrip = new ContextMenuStrip();
            collectionRoundMenuStrip.Items.Add(toolStripMenuItem);
            MessageDestinationType = DestinationType.User;
            
            Program.SDispatcher.ConnectionM.LoggedIn += HandleLoggedIn;
            Program.SDispatcher.ConnectionM.LoggedOut += HandleLoggedOut;
            Program.SDispatcher.ConnectionM.NewUserLoggedIn += HandleNewUserLoggedIn;
            Program.SDispatcher.ConnectionM.UserLoggedOut += HandleUserLoggedOut;
            Program.SDispatcher.ConnectionM.NewLoggedInUsersList += HandleNewLoggedInUsersList;

            Program.SDispatcher.ChatConnectionM.NewMessageReceived += HandleNewMessageReceived;
            Program.SDispatcher.ChatConnectionM.SimpleAdministrationMessageReceived += HandleSimpleAdministrationMessageReceived;
            Program.SDispatcher.ChatConnectionM.GroupAdministrationMessageReceived += HandleGroupAdministrationMessageReceived;
            Program.SDispatcher.ChatConnectionM.ImageSent += HandleImageSent;
            Program.SDispatcher.ChatConnectionM.NewImageReceived += HandleNewImageReceived;
            Program.SDispatcher.ChatConnectionM.SpreadMessageReceived += HandleSpreadMessageReceived;
            Program.SDispatcher.ChatConnectionM.GroupCreated += HandleGroupCreated;
            Program.SDispatcher.ChatConnectionM.GroupsListReceived += HandleGroupsReceived;
            Program.SDispatcher.ChatConnectionM.GroupJoined += HandleGroupJoined;
            Program.SDispatcher.ChatConnectionM.NewGroupReceived += HandleNewGroupReceived;
            Program.SDispatcher.ChatConnectionM.InvitationToJoinGroupReceived += HandleInvitationToJoinGroupReceived;
            Program.SDispatcher.ChatConnectionM.ForceJoinGroup += HandleForceJoinGroup;
        }

        private void HandleForceJoinGroup(string name)
        {
            if (InvokeRequired)
            {
                Invoke(new OneParameterStringHandler(HandleForceJoinGroup), name);
            }
            else
            {
                if (!m_messagesAreas.ContainsKey(name))
                {
                    m_messagesAreas.Add(name, CreateNewMessagesRichText());
                    this.Controls.Add(m_messagesAreas[name]);
                    m_discussionGroupListBox.Items.Add(name);

                    m_messagesAreas[name].SelectionColor = Color.Blue;
                    m_messagesAreas[name].AppendText("Vous avez joint le groupe\n");
                    m_messagesAreas[name].SelectionColor = m_messagesAreas[name].ForeColor;

                    m_discussionGroupListBox.SetSelected(m_discussionGroupListBox.FindStringExact(name), true);
                    m_messageRichTextBox.Focus();
                }
            }
        }

        private void HandleInvitationToJoinGroupReceived(string from, string group)
        {
            MessageBoxButtons boite = MessageBoxButtons.YesNo;
            DialogResult resultat = MessageBox.Show("Vous avez recu une invitation de " + from + " pour joindre le groupe " + group + "\nVoulez vous l'accepter?",
                "Invitation recue", boite, MessageBoxIcon.Information);
            if (resultat == DialogResult.Yes)
            {
                Program.SDispatcher.ChatConnectionM.JoinGroup(group);
            }
            else
            {
            }
        }
        private void toolStripMenuItem_Click(object sender, EventArgs e)
        {
            Program.SDispatcher.ChatConnectionM.InviteToJoinGroup(m_selectedMenuItem, m_selectedDestination);
        }

        private void HandleNewGroupReceived(string name)
        {
            if (InvokeRequired)
            {
                Invoke(new OneParameterStringHandler(HandleNewGroupReceived), name);
            }
            else
            {
                m_groupsComboBox.Items.Add(name);
            }
        }

        private void HandleGroupsReceived(string[] groups)
        {
            if (m_groupsComboBox.InvokeRequired)
            {
                m_groupsComboBox.Invoke(new HandleGroupsReceivedCallback(HandleGroupsReceived), new object[] { groups });
            }
            else
            {
                m_groupsComboBox.Items.AddRange(groups);
                if(m_groupsComboBox.Items.Count > 0)
                    m_groupsComboBox.SelectedIndex = 0;
            }
        }

        private void HandleGroupCreated(string group)
        {
            if (InvokeRequired)
            {
                Invoke(new OneParameterStringHandler(HandleGroupCreated), group);
            }
            else
            {
                if (!m_messagesAreas.ContainsKey(group))
                {
                    m_messagesAreas.Add(group, CreateNewMessagesRichText());
                    this.Controls.Add(m_messagesAreas[group]);
                    m_discussionGroupListBox.Items.Add(group);

                    m_messagesAreas[group].SelectionColor = Color.Blue;
                    m_messagesAreas[group].AppendText("Vous avez joint le groupe\n");
                    m_messagesAreas[group].SelectionColor = m_messagesAreas[group].ForeColor;

                    m_discussionGroupListBox.SetSelected(m_discussionGroupListBox.FindStringExact(group), true);
                    m_messageRichTextBox.Focus();
                }
            }
        }

        private void HandleGroupJoined(string group)
        {
            if (InvokeRequired)
            {
                Invoke(new OneParameterStringHandler(HandleGroupJoined), group);
            }
            else
            {
                if (!m_messagesAreas.ContainsKey(group))
                {
                    m_messagesAreas.Add(group, CreateNewMessagesRichText());
                    this.Controls.Add(m_messagesAreas[group]);
                    m_discussionGroupListBox.Items.Add(group);

                    m_messagesAreas[group].SelectionColor = Color.Blue;
                    m_messagesAreas[group].AppendText("Vous avez joint le groupe\n");
                    m_messagesAreas[group].SelectionColor = m_messagesAreas[group].ForeColor;

                    m_discussionGroupListBox.SetSelected(m_discussionGroupListBox.FindStringExact(group), true);
                    m_groupsComboBox.Items.Remove(group);
                    m_messageRichTextBox.Focus();
                }
            }
        }

        private void HandleGroupAdministrationMessageReceived(string message, string time, string destination)
        {
            HandleAdministrationMessageReceived(message, time, destination, DestinationType.Group);
        }

        private void HandleSimpleAdministrationMessageReceived(string message, string time, string destination)
        {
            HandleAdministrationMessageReceived(message, time, destination, DestinationType.User);
        }

        private void HandleAdministrationMessageReceived(string message, string time, string destination, DestinationType type)
        {
            if (this.InvokeRequired)
                this.Invoke(new ThreeParametersStringHandler(HandleSimpleAdministrationMessageReceived), message, time, destination);
            else
            {
                ListBox list;
                if (type == DestinationType.User)
                    list = m_connectedUsersListBox;
                else
                    list = m_discussionGroupListBox;
                string area = destination;
                Color color = Color.Red;
                if (m_messagesAreas.ContainsKey(area))
                {
                    m_messagesAreas[area].SelectionColor = color;
                    m_messagesAreas[area].AppendText("Admin (" + time + ") : ");
                    AppendContent(m_messagesAreas[area], message);
                    m_messagesAreas[area].SelectionColor = m_messagesAreas[area].ForeColor;
                    list.SetSelected(list.FindStringExact(area), true);
                    m_messageRichTextBox.Focus();
                }
            }
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
                if (Program.SoundConfiguration.imageSent)
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
            if (Program.SoundConfiguration.imageReceived)
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
                m_localUserNameLabel.Text = username + " (" + Program.SConnection.UserName + ")";
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
                /*foreach (string item in m_connectedUsersListBox.Items)
                {
                    m_disconnectedListBox.Items.Add(item);
                }*/
                m_messagesAreas.Clear();
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
                    if (m_selectedDestination == null)
                        m_connectedUsersListBox.SetSelected(0, true);
                    m_messageRichTextBox.Focus();
                }
            }
        }

        private void HandleSpreadMessageReceived(string source, string message, string time, string destination)
        {
            MessageReceived(source, message, time, destination, DestinationType.Group);
        }

        private void HandleNewMessageReceived(string source, string content, string time, string destination)
        {
            MessageReceived(source, content, time, destination, DestinationType.User);
        }

        private void MessageReceived(string source, string content, string time, string destination, DestinationType type)
        {
            if (this.InvokeRequired)
                this.Invoke(new MessageReceivedCallback(MessageReceived), source, content, time, destination, type);
            else
            {
                ListBox list;
                string area = destination;
                if (type == DestinationType.User)
                {
                    list = m_connectedUsersListBox;
                    if (source != Program.SConnection.UserName)
                        area = source;
                }
                else
                {
                    list = m_discussionGroupListBox;
                }
               
                Color color = Color.Blue;
                if (source == Program.SConnection.UserName)
                {
                    color = Color.Green;
                    if (Program.SoundConfiguration.messageSent)
                        playSound(messageSentSound);
                }
                else
                {
                    if (Program.SoundConfiguration.messageReceived)
                        playSound(messageReceivedSound);
                }

                if (m_messagesAreas.ContainsKey(area))
                {
                    m_messagesAreas[area].SelectionColor = color;
                    m_messagesAreas[area].AppendText(source + " (" + time + ") : ");
                    m_messagesAreas[area].SelectionColor = m_messagesAreas[area].ForeColor;
                    AppendContent(m_messagesAreas[area], content);
                    list.SetSelected(list.FindStringExact(area), true);
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
                    try
                    {
                        switch (content[index + 1])
                        {
                            case ')':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\smile.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case '(':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\sad.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'D':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\big-smile.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'L':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\laugh.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'P':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\tongue.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'O':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\shout.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'G':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\glasses.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'V':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\devil.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'Z':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\sleep.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'H':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\love.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'R':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\rose.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            case 'C':
                                lock (Program.ChatLock)
                                {
                                    IDataObject orgData = Clipboard.GetDataObject();
                                    Clipboard.SetImage(Image.FromFile(@"emoticones\mobile.png"));
                                    richTextBox.SelectionStart = richTextBox.TextLength;
                                    richTextBox.ReadOnly = false;
                                    richTextBox.Paste();
                                    richTextBox.ReadOnly = true;
                                    Clipboard.SetDataObject(orgData);
                                }
                                index++;
                                break;
                            default:
                                richTextBox.AppendText(":");
                                break;
                        }
                    }
                    catch
                    {
                    }
                }
                else if (content[index] == ';' && content[index + 1] == ')')
                {
                    lock (Program.ChatLock)
                    {
                        try
                        {
                            IDataObject orgData = Clipboard.GetDataObject();
                            Clipboard.SetImage(Image.FromFile(@"emoticones\wink.png"));
                            richTextBox.SelectionStart = richTextBox.TextLength;
                            richTextBox.ReadOnly = false;
                            richTextBox.Paste();
                            richTextBox.ReadOnly = true;
                            Clipboard.SetDataObject(orgData);
                        }
                        catch
                        {
                        }
                    }
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

                if (m_selectedDestination == null)
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
            if (m_selectedDestination != null && m_messageRichTextBox.Text != "")
            {
                if(MessageDestinationType == DestinationType.User)
                    Program.SDispatcher.ChatConnectionM.SendMessage(m_messageRichTextBox.Text, DateTime.Now.ToShortTimeString(),
                    m_selectedDestination);
                else
                    Program.SDispatcher.ChatConnectionM.SpreadMessage(m_messageRichTextBox.Text, DateTime.Now.ToShortTimeString(),
                    m_selectedDestination);
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
            if (Program.SChatPanel.In == "Edition")
            {
                Program.edition.m_chatPanel.Controls.Add(Program.SChatPanel);
                Program.edition.m_chatPanel.Visible = true;
                Program.edition.Edition_Resize(null, null);
            }
            else if (Program.SChatPanel.In == "Simulation")
            {
                Program.simulation.m_chatPanel.Controls.Add(Program.SChatPanel);
                Program.simulation.m_chatPanel.Visible = true;
                Program.simulation.Simulation_Resize(null, null);
            }
            Program.clavardageEnPremierPlan_ = false;
        }

        private RichTextBox CreateNewMessagesRichText()
        {
            RichTextBox textBox = new RichTextBox();
            textBox.BackColor = Color.SeaShell;
            textBox.HideSelection = false;
            textBox.Location = new Point(20, 112);
            textBox.Name = "m_messagesRichTextBox";
            textBox.Size = new Size(730, 230);
            textBox.TabIndex = 8;
            textBox.ReadOnly = true;
            textBox.Text = "";
            textBox.DetectUrls = true;
            textBox.LinkClicked += messagesArea_LinkClicked;
            m_messageRichTextBox.Focus();
            return textBox;
        }

        private void m_discussionGroupListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListBox groupsList = (ListBox)sender;

            if (groupsList.SelectedIndex >= 0)
            {
                m_selectedDestination = groupsList.SelectedItem.ToString();
                MessageDestinationType = DestinationType.Group;
                m_userNameLabel.Text = m_selectedDestination;
                m_messagesAreas[m_selectedDestination].BringToFront();
                if (Program.SConnection.IsLoggedIn)
                    EnableSendMessage("", true);
                m_messageRichTextBox.Focus();
            }
        }

        private void m_connectedUsersListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListBox usersList = (ListBox)sender;

            if (usersList.SelectedIndex >= 0)
            {
                m_selectedDestination = usersList.SelectedItem.ToString();
                MessageDestinationType = DestinationType.User;
                m_userNameLabel.Text = m_selectedDestination;
                m_messagesAreas[m_selectedDestination].BringToFront();
                if (Program.SConnection.IsLoggedIn)
                    EnableSendMessage("", true);
            }
        }

        private void m_disconnectedListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListBox usersList = (ListBox)sender;

            if (usersList.SelectedIndex >= 0)
            {
                m_selectedDestination = usersList.SelectedItem.ToString();
                m_userNameLabel.Text = m_selectedDestination;
                m_messagesAreas[m_selectedDestination].BringToFront();
                if (Program.SConnection.IsLoggedIn)
                    EnableSendMessage(m_selectedDestination + " est déconnecté", false);
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
                Program.SDispatcher.ChatConnectionM.SendImage(Path.GetFileName(fileImage), imageBytes, DateTime.Now.ToShortTimeString(),
                    m_selectedDestination);
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

        private void m_groupNameTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsLetterOrDigit(e.KeyChar) && (e.KeyChar != '-') &&
                (e.KeyChar != '_') && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }
        }

        private void m_createButton_Click(object sender, EventArgs e)
        {
            if (m_groupNameTextBox.Text == "")
            {
                MessageBox.Show("Le champs nom du groupe ne peut pas être vide");
            }
            else
            {
                Program.SDispatcher.ChatConnectionM.CreateGroup(m_groupNameTextBox.Text);
                m_groupNameTextBox.Text = "";
                m_messageRichTextBox.Focus();
            }
        }

        private void m_joinGroupButton_Click(object sender, EventArgs e)
        {
            if (m_groupsComboBox.SelectedItem == null)
            {
                MessageBox.Show("Aucun groupe n'est sélectionné");
                m_messageRichTextBox.Focus();
            }
            else
            {
                Program.SDispatcher.ChatConnectionM.JoinGroup(m_groupsComboBox.SelectedItem.ToString());
                m_messageRichTextBox.Focus();
            }
        }

        private void m_quitGroupButton_Click(object sender, EventArgs e)
        {
            if (m_messagesAreas.ContainsKey(m_selectedDestination))
            {
                Program.SDispatcher.ChatConnectionM.QuitGroup(m_selectedDestination);
                m_messagesAreas[m_selectedDestination].Dispose();
                m_messagesAreas.Remove(m_selectedDestination);
                m_discussionGroupListBox.Items.Remove(m_selectedDestination);
                if (m_discussionGroupListBox.Items.Count > 0)
                {
                    m_discussionGroupListBox.SetSelected(0, true);
                }
                else if (m_connectedUsersListBox.Items.Count > 0)
                {
                    m_connectedUsersListBox.SetSelected(0, true);
                }
                else if (m_sameCardUserslistBox.Items.Count > 0)
                {
                    m_sameCardUserslistBox.SetSelected(0, true);
                }
                else if (m_disconnectedListBox.Items.Count > 0)
                {
                    m_disconnectedListBox.SetSelected(0, true);
                }
            }
        }

        private void m_connectedUsersListBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Right)
                return;
            if (MessageDestinationType == DestinationType.User)
                return;
            var index = m_connectedUsersListBox.IndexFromPoint(e.Location);
            if (index != ListBox.NoMatches)
            {
                m_selectedMenuItem = m_connectedUsersListBox.Items[index].ToString();
                collectionRoundMenuStrip.Show(Cursor.Position);
                collectionRoundMenuStrip.Visible = true;
            }
            else
            {
                collectionRoundMenuStrip.Visible = false;
            }
        }
    }

    public enum DestinationType
    {
        User,
        Group,
    }
}
