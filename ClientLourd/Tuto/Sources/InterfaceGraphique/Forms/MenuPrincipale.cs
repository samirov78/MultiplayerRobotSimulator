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
           this.Hide();
           Program.edition = new Edition();
           Program.edition.lancerEdition();
           Program.edition = null;
           this.Show();
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
            Application.Exit();
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

            if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.Hide();
                Program.simulation = new Simulation(true);
                Program.simulation.lancerSimulation(openFileDialog.FileName);
                this.Show();
            }
        }

        private void bConfiguration_Click(object sender, EventArgs e)
        {
            Configuration configuration = new Configuration();
            configuration.lancerConfiguration(this);
        }
    }
}
