///////////////////////////////////////////////////////////////////////////////
/// @file MenuPrincipale.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class MenuPrincipale
    /// @brief Classe decrivant la fenetre de menu principale.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    public partial class MenuPrincipale : Form
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MenuPrincipale()
        ///
        /// Constructeur par defaut.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public MenuPrincipale()
        {
            InitializeComponent();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bEditeur_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant le lancement du mode edition.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bEditeur_Click(object sender, EventArgs e)
        {
            Hide();
            Program.edition = new Edition();
            if (Program.newEdition)
            {
                Program.edition.lancerTutoriel();
                Program.newEdition = false;
                File.AppendAllText("first.first", "Edition");
            }
            Program.edition.lancerEdition();
            Program.edition = null;
            Show();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bQuitter_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant de quitter l'application.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bQuitter_Click(object sender, EventArgs e)
        {
            Environment.Exit(Environment.ExitCode);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MenuPrincipale_Load(object sender, EventArgs e)
        ///
        /// Methode permettant le chargement du menu principale.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MenuPrincipale_Load(object sender, EventArgs e)
        {

        }

        private void bSimulation_Click(object sender, EventArgs e)
        {
            openFileDialog.Filter = "Fichier XML (*.xml)|*.xml";
            openFileDialog.InitialDirectory = Path.Combine(Application.StartupPath, @"zones");
            openFileDialog.RestoreDirectory = true;

            Program.simulation = new Simulation(true);
            if (Program.newSimulation)
            {
                Program.simulation.lancerTutoriel();
                Program.newSimulation = false;
                File.AppendAllText("first.first", "Simulation");
            }
            if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.Hide();
                Program.simulation.lancerSimulation(openFileDialog.FileName);
                this.Show();
            }
            else
                Program.simulation.Dispose();
        }

        private void bConfiguration_Click(object sender, EventArgs e)
        {
            Configuration configuration = new Configuration();
            configuration.lancerConfiguration(this);
        }

        private void m_connectionButton_Click(object sender, EventArgs e)
        {
            Program.SDispatcher.ConnectionM.LoggedIn += LogIn;
            Login login = new InterfaceGraphique.Login();
            login.Run();
            Program.SDispatcher.ConnectionM.LoggedIn -= LogIn;
        }

        void LogIn(string name)
        {
            if (InvokeRequired)
            {
                Invoke(new LogInCallback(LogIn), name);
            }
            else
            {
                m_nameLabel.Text = "Bienvenue " + Program.SConnection.FirstName;
                Program.SConnection.IsLoggedIn = true;
                if (Program.SoundConfiguration.logIn)
                {
                    SoundPlayer simpleSound = new SoundPlayer(Program.loggedInSound);
                    simpleSound.Play();
                }
            }
        }

        private void m_chatButton_Click(object sender, EventArgs e)
        {
            Program.SChatWindow.ShowDialog();
        }

        private delegate void LogInCallback(string name); 
    }
}
