using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    class ChatPanel : Panel
    {
        public string In;
        private Button m_quitGroupButton;
        private Button m_quitIntegratedButton;
        private GroupBox groupBox1;
        private Button m_smileButton;
        private Button m_sadButton;
        private Button m_tongueButton;
        private Button m_spleepButton;
        private Button m_glacesButton;
        private Button m_winkButton;
        private Button m_heartButton;
        private Button m_laughButton;
        private Button m_bigSmileButton;
        private Button m_roseButton;
        private Button m_surpriseButton;
        private Button m_devilButton;
        private Button m_celButton;
        private ListBox m_discussionGroupListBox;
        private ListBox m_connectedUsersListBox;
        private ListBox m_sameCardUserslistBox;
        private Button m_effacerButton;
        private Label m_localUserNameLabel;
        private Label label9;
        private Label m_userNameLabel;
        private Label label6;
        private Label label5;
        private RichTextBox m_messageRichTextBox;
        private Button m_sendButton;
        private Label label1;
        private Label label2;

        private Dictionary<string, RichTextBox> m_messagesAreas;
        private string m_selectedDestination = null;
        private DestinationType m_destinationType;

        private readonly ContextMenuStrip collectionRoundMenuStrip;
        private string m_selectedMenuItem;

        public DestinationType MessageDestinationType
        {
            get { return m_destinationType; }
            set
            {
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

        public ChatPanel()
        {
            InitializeComponent();

            EnableSendMessage("Vous êtes déconnecté", false);
            m_messagesAreas = new Dictionary<string, RichTextBox>();

            var toolStripMenuItem = new ToolStripMenuItem { Text = "Joindre le groupe" };
            toolStripMenuItem.Click += toolStripMenuItem_Click;
            collectionRoundMenuStrip = new ContextMenuStrip();
            collectionRoundMenuStrip.Items.Add(toolStripMenuItem);

            Program.SDispatcher.ConnectionM.LoggedIn += HandleLoggedIn;
            Program.SDispatcher.ConnectionM.LoggedOut += HandleLoggedOut;
            Program.SDispatcher.ConnectionM.NewUserLoggedIn += HandleNewUserLoggedIn;
            Program.SDispatcher.ConnectionM.UserLoggedOut += HandleUserLoggedOut;
            Program.SDispatcher.ConnectionM.NewLoggedInUsersList += HandleNewLoggedInUsersList;

            Program.SDispatcher.ChatConnectionM.NewMessageReceived += HandleNewMessageReceived;
            Program.SDispatcher.ChatConnectionM.SimpleAdministrationMessageReceived += HandleSimpleAdministrationMessageReceived;
            Program.SDispatcher.ChatConnectionM.GroupAdministrationMessageReceived += HandleGroupAdministrationMessageReceived;
            Program.SDispatcher.ChatConnectionM.SpreadMessageReceived += HandleSpreadMessageReceived;
            Program.SDispatcher.ChatConnectionM.GroupCreated += HandleGroupCreated;
            Program.SDispatcher.ChatConnectionM.GroupJoined += HandleGroupJoined;
            Program.SDispatcher.ChatConnectionM.ForceJoinGroup += HandleForceJoinGroup;
        }

        private void InitializeComponent()
        {
            this.m_quitGroupButton = new System.Windows.Forms.Button();
            this.m_quitIntegratedButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.m_smileButton = new System.Windows.Forms.Button();
            this.m_sadButton = new System.Windows.Forms.Button();
            this.m_tongueButton = new System.Windows.Forms.Button();
            this.m_spleepButton = new System.Windows.Forms.Button();
            this.m_glacesButton = new System.Windows.Forms.Button();
            this.m_winkButton = new System.Windows.Forms.Button();
            this.m_heartButton = new System.Windows.Forms.Button();
            this.m_laughButton = new System.Windows.Forms.Button();
            this.m_bigSmileButton = new System.Windows.Forms.Button();
            this.m_roseButton = new System.Windows.Forms.Button();
            this.m_surpriseButton = new System.Windows.Forms.Button();
            this.m_devilButton = new System.Windows.Forms.Button();
            this.m_celButton = new System.Windows.Forms.Button();
            this.m_discussionGroupListBox = new System.Windows.Forms.ListBox();
            this.m_connectedUsersListBox = new System.Windows.Forms.ListBox();
            this.m_sameCardUserslistBox = new System.Windows.Forms.ListBox();
            this.m_effacerButton = new System.Windows.Forms.Button();
            this.m_localUserNameLabel = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.m_userNameLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.m_messageRichTextBox = new System.Windows.Forms.RichTextBox();
            this.m_sendButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_chatPanel
            // 
            this.Controls.Add(this.m_quitGroupButton);
            this.Controls.Add(this.m_quitIntegratedButton);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.m_discussionGroupListBox);
            this.Controls.Add(this.m_connectedUsersListBox);
            this.Controls.Add(this.m_sameCardUserslistBox);
            this.Controls.Add(this.m_effacerButton);
            this.Controls.Add(this.m_localUserNameLabel);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.m_userNameLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.m_messageRichTextBox);
            this.Controls.Add(this.m_sendButton);
            this.Location = new System.Drawing.Point(0, 1);
            this.Name = "m_chatPanel";
            this.Size = new System.Drawing.Size(256, 477);
            this.TabIndex = 0;
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
            // 
            // m_quitGroupButton
            // 
            this.m_quitGroupButton.Location = new Point(147, 227);
            this.m_quitGroupButton.Margin = new Padding(0);
            this.m_quitGroupButton.Name = "m_quitGroupButton";
            this.m_quitGroupButton.Size = new System.Drawing.Size(100, 22);
            this.m_quitGroupButton.TabIndex = 31;
            this.m_quitGroupButton.Text = "Quitter le groupe";
            this.m_quitGroupButton.Enabled = false;
            this.m_quitGroupButton.UseVisualStyleBackColor = true;
            this.m_quitGroupButton.Click += new System.EventHandler(this.m_quitGroupButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.m_smileButton);
            this.groupBox1.Controls.Add(this.m_sadButton);
            this.groupBox1.Controls.Add(this.m_tongueButton);
            this.groupBox1.Controls.Add(this.m_spleepButton);
            this.groupBox1.Controls.Add(this.m_glacesButton);
            this.groupBox1.Controls.Add(this.m_winkButton);
            this.groupBox1.Controls.Add(this.m_heartButton);
            this.groupBox1.Controls.Add(this.m_laughButton);
            this.groupBox1.Controls.Add(this.m_bigSmileButton);
            this.groupBox1.Controls.Add(this.m_roseButton);
            this.groupBox1.Controls.Add(this.m_surpriseButton);
            this.groupBox1.Controls.Add(this.m_devilButton);
            this.groupBox1.Controls.Add(this.m_celButton);
            this.groupBox1.Location = new System.Drawing.Point(2, 304);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Size = new System.Drawing.Size(187, 72);
            this.groupBox1.TabIndex = 29;
            this.groupBox1.TabStop = false;
            // 
            // m_smileButton
            // 
            this.m_smileButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_smileButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.smile1;
            this.m_smileButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_smileButton.FlatAppearance.BorderSize = 0;
            this.m_smileButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_smileButton.Location = new System.Drawing.Point(3, 7);
            this.m_smileButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_smileButton.Name = "m_smileButton";
            this.m_smileButton.Size = new System.Drawing.Size(30, 30);
            this.m_smileButton.TabIndex = 11;
            this.m_smileButton.UseVisualStyleBackColor = false;
            this.m_smileButton.Click += new System.EventHandler(this.m_smileButton_Click);
            // 
            // m_sadButton
            // 
            this.m_sadButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_sadButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.sad;
            this.m_sadButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_sadButton.FlatAppearance.BorderSize = 0;
            this.m_sadButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_sadButton.Location = new System.Drawing.Point(154, 7);
            this.m_sadButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_sadButton.Name = "m_sadButton";
            this.m_sadButton.Size = new System.Drawing.Size(30, 30);
            this.m_sadButton.TabIndex = 11;
            this.m_sadButton.UseVisualStyleBackColor = false;
            this.m_sadButton.Click += new System.EventHandler(this.m_sadButton_Click);
            // 
            // m_tongueButton
            // 
            this.m_tongueButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_tongueButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.tongue;
            this.m_tongueButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_tongueButton.FlatAppearance.BorderSize = 0;
            this.m_tongueButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_tongueButton.Location = new System.Drawing.Point(122, 7);
            this.m_tongueButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_tongueButton.Name = "m_tongueButton";
            this.m_tongueButton.Size = new System.Drawing.Size(30, 30);
            this.m_tongueButton.TabIndex = 11;
            this.m_tongueButton.UseVisualStyleBackColor = false;
            this.m_tongueButton.Click += new System.EventHandler(this.m_tongueButton_Click);
            // 
            // m_spleepButton
            // 
            this.m_spleepButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_spleepButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.sleep;
            this.m_spleepButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_spleepButton.FlatAppearance.BorderSize = 0;
            this.m_spleepButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_spleepButton.Location = new System.Drawing.Point(127, 38);
            this.m_spleepButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_spleepButton.Name = "m_spleepButton";
            this.m_spleepButton.Size = new System.Drawing.Size(30, 30);
            this.m_spleepButton.TabIndex = 11;
            this.m_spleepButton.UseVisualStyleBackColor = false;
            this.m_spleepButton.Click += new System.EventHandler(this.m_spleepButton_Click);
            // 
            // m_glacesButton
            // 
            this.m_glacesButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_glacesButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.glasses;
            this.m_glacesButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_glacesButton.FlatAppearance.BorderSize = 0;
            this.m_glacesButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_glacesButton.Location = new System.Drawing.Point(3, 38);
            this.m_glacesButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_glacesButton.Name = "m_glacesButton";
            this.m_glacesButton.Size = new System.Drawing.Size(30, 30);
            this.m_glacesButton.TabIndex = 11;
            this.m_glacesButton.UseVisualStyleBackColor = false;
            this.m_glacesButton.Click += new System.EventHandler(this.m_glacesButton_Click);
            // 
            // m_winkButton
            // 
            this.m_winkButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_winkButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.wink;
            this.m_winkButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_winkButton.FlatAppearance.BorderSize = 0;
            this.m_winkButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_winkButton.Location = new System.Drawing.Point(91, 7);
            this.m_winkButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_winkButton.Name = "m_winkButton";
            this.m_winkButton.Size = new System.Drawing.Size(30, 30);
            this.m_winkButton.TabIndex = 11;
            this.m_winkButton.UseVisualStyleBackColor = false;
            this.m_winkButton.Click += new System.EventHandler(this.m_winkButton_Click);
            // 
            // m_heartButton
            // 
            this.m_heartButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_heartButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.love;
            this.m_heartButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_heartButton.FlatAppearance.BorderSize = 0;
            this.m_heartButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_heartButton.Location = new System.Drawing.Point(80, 38);
            this.m_heartButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_heartButton.Name = "m_heartButton";
            this.m_heartButton.Size = new System.Drawing.Size(30, 30);
            this.m_heartButton.TabIndex = 11;
            this.m_heartButton.UseVisualStyleBackColor = false;
            this.m_heartButton.Click += new System.EventHandler(this.m_heartButton_Click);
            // 
            // m_laughButton
            // 
            this.m_laughButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_laughButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.laugh;
            this.m_laughButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_laughButton.FlatAppearance.BorderSize = 0;
            this.m_laughButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_laughButton.Location = new System.Drawing.Point(61, 7);
            this.m_laughButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_laughButton.Name = "m_laughButton";
            this.m_laughButton.Size = new System.Drawing.Size(30, 30);
            this.m_laughButton.TabIndex = 11;
            this.m_laughButton.UseVisualStyleBackColor = false;
            this.m_laughButton.Click += new System.EventHandler(this.m_laughButton_Click);
            // 
            // m_bigSmileButton
            // 
            this.m_bigSmileButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_bigSmileButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.big_smile;
            this.m_bigSmileButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_bigSmileButton.FlatAppearance.BorderSize = 0;
            this.m_bigSmileButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_bigSmileButton.Location = new System.Drawing.Point(32, 7);
            this.m_bigSmileButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_bigSmileButton.Name = "m_bigSmileButton";
            this.m_bigSmileButton.Size = new System.Drawing.Size(30, 30);
            this.m_bigSmileButton.TabIndex = 11;
            this.m_bigSmileButton.UseVisualStyleBackColor = false;
            this.m_bigSmileButton.Click += new System.EventHandler(this.m_bigSmileButton_Click);
            // 
            // m_roseButton
            // 
            this.m_roseButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_roseButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.rose;
            this.m_roseButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_roseButton.FlatAppearance.BorderSize = 0;
            this.m_roseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_roseButton.Location = new System.Drawing.Point(102, 38);
            this.m_roseButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_roseButton.Name = "m_roseButton";
            this.m_roseButton.Size = new System.Drawing.Size(30, 30);
            this.m_roseButton.TabIndex = 11;
            this.m_roseButton.UseVisualStyleBackColor = false;
            this.m_roseButton.Click += new System.EventHandler(this.m_roseButton_Click);
            // 
            // m_surpriseButton
            // 
            this.m_surpriseButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_surpriseButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.shout;
            this.m_surpriseButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_surpriseButton.FlatAppearance.BorderSize = 0;
            this.m_surpriseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_surpriseButton.Location = new System.Drawing.Point(156, 38);
            this.m_surpriseButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_surpriseButton.Name = "m_surpriseButton";
            this.m_surpriseButton.Size = new System.Drawing.Size(30, 30);
            this.m_surpriseButton.TabIndex = 11;
            this.m_surpriseButton.UseVisualStyleBackColor = false;
            this.m_surpriseButton.Click += new System.EventHandler(this.m_surpriseButton_Click);
            // 
            // m_devilButton
            // 
            this.m_devilButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_devilButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.devil;
            this.m_devilButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_devilButton.FlatAppearance.BorderSize = 0;
            this.m_devilButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_devilButton.Location = new System.Drawing.Point(31, 38);
            this.m_devilButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_devilButton.Name = "m_devilButton";
            this.m_devilButton.Size = new System.Drawing.Size(30, 30);
            this.m_devilButton.TabIndex = 11;
            this.m_devilButton.UseVisualStyleBackColor = false;
            this.m_devilButton.Click += new System.EventHandler(this.m_devilButton_Click);
            // 
            // m_celButton
            // 
            this.m_celButton.BackColor = System.Drawing.SystemColors.MenuBar;
            this.m_celButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.mobile;
            this.m_celButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.m_celButton.FlatAppearance.BorderSize = 0;
            this.m_celButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.m_celButton.Location = new System.Drawing.Point(55, 38);
            this.m_celButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_celButton.Name = "m_celButton";
            this.m_celButton.Size = new System.Drawing.Size(30, 30);
            this.m_celButton.TabIndex = 11;
            this.m_celButton.UseVisualStyleBackColor = false;
            this.m_celButton.Click += new System.EventHandler(this.m_celButton_Click);
            // 
            // m_discussionGroupListBox
            // 
            this.m_discussionGroupListBox.BackColor = System.Drawing.Color.AliceBlue;
            this.m_discussionGroupListBox.FormattingEnabled = true;
            this.m_discussionGroupListBox.Location = new System.Drawing.Point(2, 476);
            this.m_discussionGroupListBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_discussionGroupListBox.Name = "m_discussionGroupListBox";
            this.m_discussionGroupListBox.Size = new System.Drawing.Size(120, 56);
            this.m_discussionGroupListBox.Sorted = true;
            this.m_discussionGroupListBox.TabIndex = 26;
            this.m_discussionGroupListBox.TabStop = false;
            this.m_discussionGroupListBox.SelectedIndexChanged += new System.EventHandler(this.m_discussionGroupListBox_SelectedIndexChanged);
            // 
            // m_connectedUsersListBox
            // 
            this.m_connectedUsersListBox.BackColor = System.Drawing.Color.AliceBlue;
            this.m_connectedUsersListBox.FormattingEnabled = true;
            this.m_connectedUsersListBox.Location = new System.Drawing.Point(130, 410);
            this.m_connectedUsersListBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_connectedUsersListBox.Name = "m_connectedUsersListBox";
            this.m_connectedUsersListBox.Size = new System.Drawing.Size(120, 121);
            this.m_connectedUsersListBox.Sorted = true;
            this.m_connectedUsersListBox.TabIndex = 25;
            this.m_connectedUsersListBox.TabStop = false;
            this.m_connectedUsersListBox.SelectedIndexChanged += new System.EventHandler(this.m_connectedUsersListBox_SelectedIndexChanged);
            // 
            // m_sameCardUserslistBox
            // 
            this.m_sameCardUserslistBox.BackColor = System.Drawing.Color.AliceBlue;
            this.m_sameCardUserslistBox.FormattingEnabled = true;
            this.m_sameCardUserslistBox.Location = new System.Drawing.Point(2, 410);
            this.m_sameCardUserslistBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_sameCardUserslistBox.Name = "m_sameCardUserslistBox";
            this.m_sameCardUserslistBox.Size = new System.Drawing.Size(120, 56);
            this.m_sameCardUserslistBox.Sorted = true;
            this.m_sameCardUserslistBox.TabIndex = 24;
            this.m_sameCardUserslistBox.TabStop = false;
            this.m_sameCardUserslistBox.SelectedIndexChanged += new System.EventHandler(this.m_connectedUsersListBox_SelectedIndexChanged);
            // 
            // m_effacerButton
            // 
            this.m_effacerButton.Location = new System.Drawing.Point(193, 344);
            this.m_effacerButton.Margin = new System.Windows.Forms.Padding(0);
            this.m_effacerButton.Name = "m_effacerButton";
            this.m_effacerButton.Size = new System.Drawing.Size(55, 30);
            this.m_effacerButton.TabIndex = 16;
            this.m_effacerButton.Text = "Effacer";
            this.m_effacerButton.UseVisualStyleBackColor = true;
            this.m_effacerButton.Click += new System.EventHandler(this.m_effacerButton_Click);
            // 
            // m_localUserNameLabel
            // 
            this.m_localUserNameLabel.AutoSize = true;
            this.m_localUserNameLabel.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_localUserNameLabel.Location = new System.Drawing.Point(2, 230);
            this.m_localUserNameLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_localUserNameLabel.Name = "m_localUserNameLabel";
            this.m_localUserNameLabel.Size = new System.Drawing.Size(0, 18);
            this.m_localUserNameLabel.TabIndex = 22;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(2, 460);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(60, 18);
            this.label9.TabIndex = 21;
            this.label9.Text = "Groupes";
            // 
            // m_userNameLabel
            // 
            this.m_userNameLabel.AutoSize = true;
            this.m_userNameLabel.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_userNameLabel.Location = new System.Drawing.Point(2, 0);
            this.m_userNameLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_userNameLabel.Name = "m_userNameLabel";
            this.m_userNameLabel.Size = new System.Drawing.Size(0, 18);
            this.m_userNameLabel.TabIndex = 19;
            this.m_userNameLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(2, 393);
            this.label1.Margin = new System.Windows.Forms.Padding(0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 18);
            this.label1.TabIndex = 18;
            this.label1.Text = "la même carte";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(2, 379);
            this.label6.Margin = new System.Windows.Forms.Padding(0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(95, 18);
            this.label6.TabIndex = 18;
            this.label6.Text = "Utilisateurs de";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(128, 393);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 18);
            this.label2.TabIndex = 17;
            this.label2.Text = "connectés";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Book Antiqua", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(128, 379);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(118, 18);
            this.label5.TabIndex = 17;
            this.label5.Text = "Autres utilisateurs";
            // 
            // m_messageRichTextBox
            // 
            this.m_messageRichTextBox.HideSelection = false;
            this.m_messageRichTextBox.Location = new System.Drawing.Point(2, 250);
            this.m_messageRichTextBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.m_messageRichTextBox.Name = "m_messageRichTextBox";
            this.m_messageRichTextBox.Size = new System.Drawing.Size(246, 55);
            this.m_messageRichTextBox.TabIndex = 15;
            this.m_messageRichTextBox.Text = "";
            this.m_messageRichTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.m_messageRichTextBox_KeyDown);
            // 
            // m_sendButton
            // 
            this.m_sendButton.Location = new System.Drawing.Point(193, 309);
            this.m_sendButton.Margin = new System.Windows.Forms.Padding(0);
            this.m_sendButton.Name = "m_sendButton";
            this.m_sendButton.Size = new System.Drawing.Size(55, 30);
            this.m_sendButton.TabIndex = 23;
            this.m_sendButton.Text = "Envoyer";
            this.m_sendButton.UseVisualStyleBackColor = true;
            this.m_sendButton.Click += new System.EventHandler(this.m_sendButton_Click);
            // 
            // m_quitIntegratedButton
            // 
            this.m_quitIntegratedButton.Location = new Point(55, 540);
            this.m_quitIntegratedButton.Margin = new Padding(0);
            this.m_quitIntegratedButton.Size = new System.Drawing.Size(140, 30);
            this.m_quitIntegratedButton.TabIndex = 31;
            this.m_quitIntegratedButton.Text = "Quitter le mode intégré";
            this.m_quitIntegratedButton.UseVisualStyleBackColor = true;
            this.m_quitIntegratedButton.Click += new System.EventHandler(this.m_quitIntegratedButton_Click);
            //
            this.ResumeLayout(false);
            this.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
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

        private void m_quitIntegratedButton_Click(object sender, EventArgs e)
        {
            Control parent = this.Parent;
            parent.Controls.Remove(this);
            parent.Visible = false;
            if (In == "Edition")
                Program.edition.Edition_Resize(null, null);
            else if (In == "Simulation")
                Program.simulation.Simulation_Resize(null, null);
            if (!Program.SChatWindow.Visible)
            {
                Program.clavardageEnPremierPlan_ = true;
                Program.SChatWindow.Show();
            }
            Program.SChatWindow.Activate();
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
                    m_messagesAreas[name].Dispose();
                    m_connectedUsersListBox.Items.Remove(name);
                    m_messageRichTextBox.Focus();
                }
            }
        }

        private void m_sendButton_Click(object sender, EventArgs e)
        {
            if (m_selectedDestination != null && m_messageRichTextBox.Text != "")
            {
                if (MessageDestinationType == DestinationType.User)
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

        private RichTextBox CreateNewMessagesRichText()
        {
            RichTextBox textBox = new RichTextBox();
            textBox.BackColor = Color.SeaShell;
            textBox.HideSelection = false;
            textBox.Location = new Point(2, 16);
            textBox.Name = "m_messagesRichTextBox";
            textBox.Size = new Size(246, 210);
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
}
