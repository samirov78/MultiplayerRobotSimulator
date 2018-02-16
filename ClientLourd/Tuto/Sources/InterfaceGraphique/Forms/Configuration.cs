///////////////////////////////////////////////////////////////////////////////
/// @file Configuration.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Configuration
    /// @brief Classe correspondant au formulaire de l'option Configuration.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-03-21
    ///////////////////////////////////////////////////////////////////////////
    public partial class Configuration : Form
    {
        /// Constatnte pour garder le nom du profil par defaut
        private const string nomProfilDefaut = "defaut";
        /// représente la configuration des touches du controle du robot
        private ConfigurationControle _controle;
        /// représente la configuration du debogage
        private ConfigurationDebougage _debougage;
        /// une instance gestionprofil qui contient des informations sur le profil actif
        private GestionProfils _gestionProfils;
        /// boolean pour acticvation ou desactivation des controles pour l'ajout d'un profil
        bool _controlesProfilActives = true;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Configuration()
        ///
        /// Constructeur de la classe.
        ///
        /// @param Aucun.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        public Configuration()
        {
            InitializeComponent();
            this.KeyPreview = true;
            _controle = new ConfigurationControle("données/configuration.xml");
            initialiser(_controle);
            _debougage = new ConfigurationDebougage("données/configuration.xml");
            initialiser(_debougage);
            _gestionProfils = new GestionProfils("données/profils.xml");
            initialiser(_gestionProfils);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void initialiser(ConfigurationControle configuration)
        /// 
        /// initialise les champs associés aux touches de controle par une instance Configuration
        ///
        /// @param[in] configuration: 
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void initialiser(ConfigurationControle configuration)
        {
            textBoxAvancer.Text = configuration.toucheControleAvancer.ToString();
            textBoxReculer.Text = configuration.toucheControleReculer.ToString();
            textBoxRotationAH.Text = configuration.toucheControleRotationAH.ToString();
            textBoxRotationH.Text = configuration.toucheControleRotationH.ToString();
            textBoxModeMA.Text = configuration.toucheControleModeMA.ToString();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void initialiser(ConfigurationDebougage debougage)
        ///
        /// initialise les champs associés aux options de debogage par une instance 
        /// Configuration
        ///
        /// @param[in] debougage: 
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void initialiser(ConfigurationDebougage debougage)
        {
            checkBoxConsole.Checked = debougage.console;
            checkBoxAlteration.Checked = debougage.alterationEffetsVisuels;
            
            if (debougage.activationDesactivationEclairage)
                ouiActivationDesactivationEclairage.Checked = true;
            else
                nonActivationDesactivationEclairage.Checked = true;

            if (debougage.changementComportement)
                ouiChangementComportement.Checked = true;
            else
                nonChangementComportement.Checked = true;

            if (debougage.identificationZonesCapteurs)
                ouiIdentificationCapteurs.Checked = true;
            else
                nonIdentificationCapteurs.Checked = true;

            if (checkBoxConsole.Checked)
            {
                ouiActivationDesactivationEclairage.Enabled = true;
                ouiChangementComportement.Enabled = true;
                nonActivationDesactivationEclairage.Enabled = true;
                nonChangementComportement.Enabled = true;
            }
            else
            {
                ouiActivationDesactivationEclairage.Enabled = false;
                ouiChangementComportement.Enabled = false;
                nonActivationDesactivationEclairage.Enabled = false;
                nonChangementComportement.Enabled = false;
            }

            if (checkBoxAlteration.Checked)
            {
                ouiIdentificationCapteurs.Enabled = true;
                nonIdentificationCapteurs.Enabled = true;
            }
            else
            {
                ouiIdentificationCapteurs.Enabled = false;
                nonIdentificationCapteurs.Enabled = false;
            }

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void initialiser(GestionProfils gestionProfils)
        ///
        /// Initialise les controles de l'interface par les données d'une instance de GestionProfils 
        ///
        /// @param[in] gestionProfils: 
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void initialiser(GestionProfils gestionProfils)
        {
            cacherControleNouveauProfil();
            int nombreProfils = gestionProfils.profils.Count;
            if (nombreProfils > 0)
            {
                for (int i = 0; i < gestionProfils.profils.Count; i++)
                    comboBProfils.Items.Add(gestionProfils.profils[i]);
                comboBProfils.SelectedIndex = comboBProfils.Items.IndexOf(_gestionProfils.profilActif);
                importerProfilActif();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cacherControleNouveauProfil()
        ///
        /// Cache les controles relatifs au creation d'un nouveau profil
        ///
        /// @param Aucun. 
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void cacherControleNouveauProfil()
        {
            labelNomNouveauProfil.Hide();
            buttonEnregistrerProfil.Hide();
            textBNomProfil.Hide();
            buttonEnregistrerM.Show();
            buttonSupprimer.Show();
            comboBProfils.Enabled = true;
            buttonNouveauProfil.Text = "Nouveau profil";
            textBNomProfil.Text = "";
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cacherControleNouveauProfil()
        ///
        /// Affiche les controles relatifs au creation d'un nouveau profil
        ///
        /// @param Aucun. 
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void afficherControleNouveauProfil()
        {
            labelNomNouveauProfil.Show();
            buttonEnregistrerProfil.Show();
            textBNomProfil.Show();
            buttonEnregistrerM.Hide();
            buttonSupprimer.Hide();
            comboBProfils.Enabled = false;
            buttonNouveauProfil.Text = "Annuler";
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cacherControleNouveauProfil()
        ///
        /// Importe le profil actif de l'instance courante de GestionProfil dans 
        /// l'interface profil
        ///
        /// @param Aucun. 
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void importerProfilActif()
        {
            comboBSuiviLigne.SelectedIndex = comboBSuiviLigne.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantSuiviLigne]);
            comboBBalayage.SelectedIndex = comboBBalayage.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantBalayage]);
            
            comboBDeviationGauche.SelectedIndex = comboBDeviationGauche.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantDeviationGauche]);
            textBAngleDeviationGauche.Text = _gestionProfils.angleDeviationGauche.ToString();
            
            comboBDeviationDroite.SelectedIndex = comboBDeviationDroite.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantDeviationDroite]);
            textBAngleDeviationDroite.Text = _gestionProfils.angleDeviationDroite.ToString();

            comboBEviterDroite.SelectedIndex = comboBEviterDroite.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantEviterDroite]);
            textBPivotementEviterD.Text = _gestionProfils.anglePivotementDroite.ToString();
            textBReculEviterDroite.Text = _gestionProfils.dureeReculDroite.ToString();
            
            comboBEviterGauche.SelectedIndex = comboBEviterGauche.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantEviterGauche]);
            textBPivotementEviterG.Text = _gestionProfils.anglePivotementGauche.ToString();
            textBReculEviterGauche.Text = _gestionProfils.dureeReculGauche.ToString();

            comboBDangerDroit.SelectedIndex = comboBDangerDroit.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantDangerCapteurD]);
            comboBSecuritaireDroit.SelectedIndex = comboBSecuritaireDroit.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantSecuritaireCapteurD]);
            textBLongueurDangerD.Text = _gestionProfils.longueurDangerCapteurD.ToString();
            textBLongueurSecuritaireD.Text = _gestionProfils.longueurSecuritaireCapteurD.ToString();

            comboBDangerMilieu.SelectedIndex = comboBDangerMilieu.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantDangerCapteurM]);
            comboBSecuritaireMilieu.SelectedIndex = comboBSecuritaireMilieu.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantSecuritaireMilieu]);
            textBLongueurDangerM.Text = _gestionProfils.longueurDangerCapteurM.ToString();
            textBLongueurSecuritaireM.Text = _gestionProfils.longueurSecuritaireCapteurM.ToString();

            comboBDangerGauche.SelectedIndex = comboBDangerGauche.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantDangerCapteurG]);
            comboBSecuritaireGauche.SelectedIndex = comboBSecuritaireGauche.Items.IndexOf
                (GestionProfils.etats[(int)_gestionProfils.suivantSecuritaireCapteurG]);
            textBLongueurDangerG.Text = _gestionProfils.longueurDangerCapteurG.ToString();
            textBLongueurSecuritaireG.Text = _gestionProfils.longueurSecuritaireCapteurG.ToString();

            checkBCapteurDroit.Checked = _gestionProfils.capteurDroitActif;
            checkBCapteurGauche.Checked = _gestionProfils.capteurGaucheActif;
            checkBCapteurMilieu.Checked = _gestionProfils.capteurMilieuActif;
            checkBSuiveurL.Checked = _gestionProfils.suiveurLigneActif;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void cacherControleNouveauProfil()
        ///
        /// permet a de lancer le formulaire depuis un fenetre parent
        ///
        /// @param[in] parent : le form parent
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void lancerConfiguration(Form parent)
        {
            this.ShowDialog(parent);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonReinitialiserC_Click(object sender, EventArgs e)
        ///
        /// Reinitialise les touches de controle par les valeur de defaut 
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonReinitialiserC_Click(object sender, EventArgs e)
        {
            _controle.toucheControleAvancer = Keys.W;
            textBoxAvancer.Text = Keys.W.ToString();
            _controle.toucheControleReculer = Keys.S;
            textBoxReculer.Text = Keys.S.ToString();
            _controle.toucheControleRotationH = Keys.D;
            textBoxRotationH.Text = Keys.D.ToString();
            _controle.toucheControleRotationAH = Keys.A;
            textBoxRotationAH.Text = Keys.A.ToString();
            _controle.toucheControleModeMA = Keys.Space;
            textBoxModeMA.Text = Keys.Space.ToString();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn bool toucheReservee(Keys key)
        ///
        /// Methode permettant de verifier si une touche est reserve ou non.
        ///
        /// @param[in] key : la touche en question.
        /// 
        /// @return Vrai si reserve, faux sinon.
        ///
        ////////////////////////////////////////////////////////////////////////
        bool toucheReservee(Keys key)
        {
            if (key == Keys.J || key == Keys.K || key == Keys.L || key == Keys.B || key == Keys.Escape
                || key == Keys.D1 || key == Keys.D2 || key == Keys.D3 || key == Keys.T
                || key == Keys.Up || key == Keys.Down || key == Keys.Left || key == Keys.Right
                || key == Keys.Oemplus || key == Keys.OemMinus || key == Keys.Subtract || key == Keys.Add
                || key == Keys.Control || key == Keys.Back)
                return true;
            else
                return false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxRotationAH_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Change la configuration de la touche de controle de rotation antihoraire 
        /// par la touche appuiee
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxRotationAH_KeyDown(object sender, KeyEventArgs e)
        {
            if ( !toucheReservee(e.KeyCode) )
            { 
                if (e.KeyCode != _controle.toucheControleAvancer && e.KeyCode != _controle.toucheControleReculer
                    && e.KeyCode != _controle.toucheControleRotationH && e.KeyCode != _controle.toucheControleModeMA)                    
                {
                    textBoxRotationAH.Text = e.KeyCode.ToString();
                    _controle.toucheControleRotationAH = e.KeyCode;
                }
                else
                    MessageBox.Show("Touche déjà utilisée dans un autre champs", "Touche invalide", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
            }
            else
                MessageBox.Show("Touche résérvé pour une autre utilisation\nVeuillez choisir une autre touche", "Touche Réservée", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxAvancer_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Change la configuration de la touche de controle de Avancer 
        /// par la touche appuiee
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxAvancer_KeyDown(object sender, KeyEventArgs e)
        {
            if (!toucheReservee(e.KeyCode))
            {
                if (e.KeyCode != _controle.toucheControleReculer && e.KeyCode != _controle.toucheControleRotationH
                    && e.KeyCode != _controle.toucheControleRotationAH && e.KeyCode != _controle.toucheControleModeMA)
                {
                    textBoxAvancer.Text = e.KeyCode.ToString();
                    _controle.toucheControleAvancer = e.KeyCode;
                }
                else
                    MessageBox.Show("Touche déjà utilisée dans un autre champs", "Touche invalide", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
            }
            else
                MessageBox.Show("Touche résérvé pour une autre utilisation\nVeuillez choisir une autre touche", "Touche Réservée", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxReculer_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Change la configuration de la touche de controle de Reculer 
        /// par la touche appuiee
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxReculer_KeyDown(object sender, KeyEventArgs e)
        {
            if (!toucheReservee(e.KeyCode))
            {
                if (e.KeyCode != _controle.toucheControleAvancer && e.KeyCode != _controle.toucheControleRotationH
                    && e.KeyCode != _controle.toucheControleRotationAH && e.KeyCode != _controle.toucheControleModeMA)
                {
                    textBoxReculer.Text = e.KeyCode.ToString();
                    _controle.toucheControleReculer = e.KeyCode;
                }
                else
                    MessageBox.Show("Touche déjà utilisée dans un autre champs", "Touche invalide", MessageBoxButtons.OK,
                                       MessageBoxIcon.Information);
            }
            else
                MessageBox.Show("Touche résérvé pour une autre utilisation\nVeuillez choisir une autre touche", "Touche Réservée", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxRotationH_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Change la configuration de la touche de controle de rotation horaire 
        /// par la touche appuiee
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxRotationH_KeyDown(object sender, KeyEventArgs e)
        {
            if (!toucheReservee(e.KeyCode))
            {
                if (e.KeyCode != _controle.toucheControleAvancer && e.KeyCode != _controle.toucheControleReculer
                    && e.KeyCode != _controle.toucheControleRotationAH && e.KeyCode != _controle.toucheControleModeMA)
                {
                    textBoxRotationH.Text = e.KeyCode.ToString();
                    _controle.toucheControleRotationH = e.KeyCode;
                }
                else
                    MessageBox.Show("Touche déjà utilisée dans un autre champs", "Touche invalide", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
            }
            else
                MessageBox.Show("Touche résérvé pour une autre utilisation\nVeuillez choisir une autre touche", "Touche Réservée", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBoxModeMA_KeyDown(object sender, KeyEventArgs e)
        ///
        /// Change la configuration de la touche de controle de changement de mode 
        /// par la touche appuiee
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBoxModeMA_KeyDown(object sender, KeyEventArgs e)
        {
            if (!toucheReservee(e.KeyCode))
            {
                if (e.KeyCode != _controle.toucheControleAvancer && e.KeyCode != _controle.toucheControleReculer
                    && e.KeyCode != _controle.toucheControleRotationH && e.KeyCode != _controle.toucheControleRotationAH)
                {
                    textBoxModeMA.Text = e.KeyCode.ToString();
                    _controle.toucheControleModeMA = e.KeyCode;
                }
                else
                    MessageBox.Show("Touche déjà utilisée dans un autre champs", "Touche invalide", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
            }
            else
                MessageBox.Show("Touche résérvé pour une autre utilisation\nVeuillez choisir une autre touche", "Touche Réservée", MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void checkBoxConsole_CheckedChanged(object sender, EventArgs e)
        ///
        /// Bascule la configuration de l'affichage sur console 
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void checkBoxConsole_CheckedChanged(object sender, EventArgs e)
        {
            _debougage.console = checkBoxConsole.Checked;
            if (checkBoxConsole.Checked)
            {
                ouiActivationDesactivationEclairage.Enabled = true;
                ouiChangementComportement.Enabled = true;
                nonActivationDesactivationEclairage.Enabled = true;
                nonChangementComportement.Enabled = true;
            }
            else 
            {
                ouiActivationDesactivationEclairage.Enabled = false;
                ouiChangementComportement.Enabled = false;
                nonActivationDesactivationEclairage.Enabled = false;
                nonChangementComportement.Enabled = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void checkBoxAlteration_CheckedChanged(object sender, EventArgs e)
        ///
        /// Bascule la configuration de l'affichage des capteurs de distance
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void checkBoxAlteration_CheckedChanged(object sender, EventArgs e)
        {
            _debougage.alterationEffetsVisuels = checkBoxAlteration.Checked;
            if (checkBoxAlteration.Checked)
            {
                ouiIdentificationCapteurs.Enabled = true;
                nonIdentificationCapteurs.Enabled = true;
            }
            else
            {
                ouiIdentificationCapteurs.Enabled = false;
                nonIdentificationCapteurs.Enabled = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouiChangementComportement_CheckedChanged(object sender, EventArgs e)
        ///
        /// Bascule la configuration de l'affichage sur console du changement de comportement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouiChangementComportement_CheckedChanged(object sender, EventArgs e)
        {
            _debougage.changementComportement = ouiChangementComportement.Checked;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouiActivationDesactivationEclairage_CheckedChanged(object sender, EventArgs e)
        ///
        /// Bascule la configuration de l'affichage sur console de l'activation de l'eclairage
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouiActivationDesactivationEclairage_CheckedChanged(object sender, EventArgs e)
        {
            _debougage.activationDesactivationEclairage = ouiActivationDesactivationEclairage.Checked;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouiIdentificationCapteurs_CheckedChanged(object sender, EventArgs e)
        ///
        /// Bascule la configuration de l'affichage des capteur de distance
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouiIdentificationCapteurs_CheckedChanged(object sender, EventArgs e)
        {
            _debougage.identificationZonesCapteurs = ouiIdentificationCapteurs.Checked;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonReinitialiserD_Click(object sender, EventArgs e)
        ///
        /// Reinitialise les options de configuration de debogage par les valeur 
        /// par defaut
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonReinitialiserD_Click(object sender, EventArgs e)
        {
            checkBoxConsole.Checked = true;
            _debougage.console = true;

            checkBoxAlteration.Checked = true;
            _debougage.alterationEffetsVisuels = true;
            
            ouiActivationDesactivationEclairage.Checked = true;
            _debougage.activationDesactivationEclairage = true;
            
            ouiChangementComportement.Checked = true;
            _debougage.changementComportement = true;

            ouiIdentificationCapteurs.Checked = true;
            _debougage.identificationZonesCapteurs = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonNouveauProfil_Click(object sender, EventArgs e)
        ///
        /// Defini l'action a effectuer lors d'un click sur le bouton nouveau profil.
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonNouveauProfil_Click(object sender, EventArgs e)
        {
            if (buttonNouveauProfil.Text == "Nouveau profil")
            {
                afficherControleNouveauProfil();
                viderControlesProfil();
                if (!_controlesProfilActives)
                {
                    activerControlesProfil();
                    _controlesProfilActives = true;
                }

            }
            else
            {
                cacherControleNouveauProfil();
                importerProfilActif();
                if (comboBProfils.SelectedItem.ToString().Equals(nomProfilDefaut))
                {
                    desactiverControlesProfil();
                    _controlesProfilActives = false;
                }
            }
            
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void desactiverControlesProfil()
        ///
        /// Rend les controles liés a l'edition d'un profil inactifs
        ///
        /// @param Aucun.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void desactiverControlesProfil()
        {
            buttonEnregistrerM.Enabled = false;
            buttonSupprimer.Enabled = false;
            comboBSuiviLigne.Enabled = false;
            comboBBalayage.Enabled = false;

            comboBDeviationGauche.Enabled = false;
            textBAngleDeviationGauche.Enabled = false;

            comboBDeviationDroite.Enabled = false;
            textBAngleDeviationDroite.Enabled = false;

            comboBEviterDroite.Enabled = false;
            textBPivotementEviterD.Enabled = false;
            textBReculEviterDroite.Enabled = false;

            comboBEviterGauche.Enabled = false;
            textBPivotementEviterG.Enabled = false;
            textBReculEviterGauche.Enabled = false;

            comboBDangerDroit.Enabled = false;
            comboBSecuritaireDroit.Enabled = false;
            textBLongueurDangerD.Enabled = false;
            textBLongueurSecuritaireD.Enabled = false;

            comboBDangerMilieu.Enabled = false;
            comboBSecuritaireMilieu.Enabled = false;
            textBLongueurDangerM.Enabled = false;
            textBLongueurSecuritaireM.Enabled = false;

            comboBDangerGauche.Enabled = false;
            comboBSecuritaireGauche.Enabled = false;
            textBLongueurDangerG.Enabled = false;
            textBLongueurSecuritaireG.Enabled = false;

            checkBCapteurDroit.Enabled = false;
            checkBCapteurGauche.Enabled = false;
            checkBCapteurMilieu.Enabled = false;
            checkBSuiveurL.Enabled = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void activerControlesProfil()
        ///
        /// Rend les controles liés a l'edition d'un profil actifs
        ///
        /// @param Aucun.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void activerControlesProfil()
        {
            buttonEnregistrerM.Enabled = true;
            buttonSupprimer.Enabled = true;
            comboBSuiviLigne.Enabled = true;
            comboBBalayage.Enabled = true;

            comboBDeviationGauche.Enabled = true;
            textBAngleDeviationGauche.Enabled = true;

            comboBDeviationDroite.Enabled = true;
            textBAngleDeviationDroite.Enabled = true;

            comboBEviterDroite.Enabled = true;
            textBPivotementEviterD.Enabled = true;
            textBReculEviterDroite.Enabled = true;

            comboBEviterGauche.Enabled = true;
            textBPivotementEviterG.Enabled = true;
            textBReculEviterGauche.Enabled = true;

            comboBDangerDroit.Enabled = true;
            comboBSecuritaireDroit.Enabled = true;
            textBLongueurDangerD.Enabled = true;
            textBLongueurSecuritaireD.Enabled = true;

            comboBDangerMilieu.Enabled = true;
            comboBSecuritaireMilieu.Enabled = true;
            textBLongueurDangerM.Enabled = true;
            textBLongueurSecuritaireM.Enabled = true;

            comboBDangerGauche.Enabled = true;
            comboBSecuritaireGauche.Enabled = true;
            textBLongueurDangerG.Enabled = true;
            textBLongueurSecuritaireG.Enabled = true;

            checkBCapteurDroit.Enabled = true;
            checkBCapteurGauche.Enabled = true;
            checkBCapteurMilieu.Enabled = true;
            checkBSuiveurL.Enabled = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void viderControlesProfil()
        ///
        /// Vide les controles liées a l'edition d'un profil 
        ///
        /// @param Aucun.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        void viderControlesProfil()
        {
            comboBSuiviLigne.SelectedIndex = 0;
            comboBBalayage.SelectedIndex = 0;

            comboBDeviationGauche.SelectedIndex = 0;
            textBAngleDeviationGauche.Text = String.Empty;

            comboBDeviationDroite.SelectedIndex = 0;
            textBAngleDeviationDroite.Text = String.Empty;

            comboBEviterDroite.SelectedIndex = 0;
            textBPivotementEviterD.Text = String.Empty;
            textBReculEviterDroite.Text = String.Empty;

            comboBEviterGauche.SelectedIndex = 0;
            textBPivotementEviterG.Text = String.Empty;
            textBReculEviterGauche.Text = String.Empty;

            comboBDangerDroit.SelectedIndex = 0;
            comboBSecuritaireDroit.SelectedIndex = 0;
            textBLongueurDangerD.Text = String.Empty;
            textBLongueurSecuritaireD.Text = String.Empty;

            comboBDangerMilieu.SelectedIndex = 0;
            comboBSecuritaireMilieu.SelectedIndex = 0;
            textBLongueurDangerM.Text = String.Empty;
            textBLongueurSecuritaireM.Text = String.Empty;

            comboBDangerGauche.SelectedIndex = 0;
            comboBSecuritaireGauche.SelectedIndex = 0;
            textBLongueurDangerG.Text = String.Empty;
            textBLongueurSecuritaireG.Text = String.Empty;

            checkBCapteurDroit.Checked = false;
            checkBCapteurGauche.Checked = false;
            checkBCapteurMilieu.Checked = false;
            checkBSuiveurL.Checked = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void comboBProfils_SelectedIndexChanged(object sender, EventArgs e)
        ///
        /// Charge le profil selectionne par l'utilisateur
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void comboBProfils_SelectedIndexChanged(object sender, EventArgs e)
        {
            _gestionProfils.chargerProfil(comboBProfils.SelectedItem.ToString());
            importerProfilActif();
            if (_gestionProfils.profilActif.Equals(nomProfilDefaut))
            {
                desactiverControlesProfil();
                _controlesProfilActives = false;
            }
            else if ( !_controlesProfilActives )
            {
                _controlesProfilActives = true;
                activerControlesProfil();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool verifierIntegrite()
        ///
        /// Verifie l'integrité (validité) des informations dans le profil.
        ///
        /// @param Aucun.
        ///
        /// @return Vrai si tout est bon, faux sinon.
        ///
        ////////////////////////////////////////////////////////////////////////
        private bool verifierIntegrite()
        {
            if ( textBAngleDeviationGauche.Text == String.Empty )
            {
                MessageBox.Show("Veuillez saisir l'angle dans l'état Déviation vers la gauche", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( textBAngleDeviationDroite.Text == String.Empty )
            {
                MessageBox.Show("Veuillez saisir l'angle dans l'état Déviation vers la droite", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( textBPivotementEviterD.Text == String.Empty )
            {
                MessageBox.Show("Veuillez saisir l'angle dans l'état Eviter par la droite", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            
            if ( textBReculEviterDroite.Text == String.Empty )
            {
                MessageBox.Show("Veuillez saisir la durée de recul dans l'état Eviter par la droite", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if (textBPivotementEviterG.Text == String.Empty)
            {
                MessageBox.Show("Veuillez saisir l'angle dans l'état Eviter par la gauche", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if (textBReculEviterGauche.Text == String.Empty)
            {
                MessageBox.Show("Veuillez saisir la durée de recul dans l'état Eviter par la gauche", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if (textBLongueurDangerD.Text == String.Empty)
            {
                MessageBox.Show("Veuillez saisir la longueur de la zone de danger du capteur droit", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( textBLongueurSecuritaireD.Text == String.Empty )
            {
                MessageBox.Show("Veuillez saisir la longueur de la zone sécuritaire du capteur droit", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( textBLongueurDangerM.Text == String.Empty )
            {
                MessageBox.Show("Veuillez saisir la longueur de la zone de danger du capteur du milieu", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if (textBLongueurSecuritaireM.Text == String.Empty)
            {
                MessageBox.Show("Veuillez saisir la longueur de la zone sécuritaire du capteur du milieu", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if (textBLongueurDangerG.Text == String.Empty)
            {
                MessageBox.Show("Veuillez saisir la longueur de la zone de danger du capteur gauche", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( textBLongueurSecuritaireG.Text == String.Empty )
            {
                MessageBox.Show("Veuillez saisir la longueur de la zone sécuritaire du capteur gauche", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( float.Parse(textBPivotementEviterG.Text) > 360 )
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 360 pour l'angle dans l'état Eviter par la gauche", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            if ( float.Parse(textBAngleDeviationGauche.Text ) > 360 )
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 360 pour l'angle dans l'état Déviation vers la gauche", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( float.Parse( textBAngleDeviationDroite.Text ) > 360)
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 360 pour l'angle dans l'état Déviation vers la droite", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( float.Parse( textBPivotementEviterD.Text ) > 360)
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 360 pour l'angle dans l'état Eviter par la droite", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            if ( float.Parse(textBReculEviterDroite.Text) > 2000 )
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 2000 pour la durée de recul dans l'état Eviter par la droite", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            if ( float.Parse( textBReculEviterGauche.Text ) > 2000 )
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 2000 pour la durée de recul dans l'état Eviter par la gauche", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            if ( float.Parse( textBLongueurDangerD.Text ) > 30)
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 30 pour la longueur de la zone de danger du capteur droit", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( float.Parse( textBLongueurSecuritaireD.Text ) > 30 )
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 30 pour la longueur de la zone sécuritaire du capteur droit", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( float.Parse( textBLongueurDangerM.Text ) > 30)
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 30 pour la longueur de la zone de danger du capteur du milieu", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( float.Parse( textBLongueurSecuritaireM.Text ) > 30)
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 30 pour la longueur de la zone sécuritaire du capteur du milieu", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( float.Parse( textBLongueurDangerG.Text ) > 30)
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 30 pour la longueur de la zone de danger du capteur gauche", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }

            if ( float.Parse( textBLongueurSecuritaireG.Text ) > 30)
            {
                MessageBox.Show("Veuillez saisir une valeur inférieure ou égal à 30 pour la longueur de la zone sécuritaire du capteur gauche", "Valeur invalide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            if ( float.Parse( textBLongueurDangerD.Text ) + float.Parse( textBLongueurSecuritaireD.Text ) > 30)
            {
                MessageBox.Show("La somme de la longueur de la zone de danger avec celle de la zone sécuritaire du capteur droit ne peut pas dépasser 30po", "Valeurs invalides", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            if (float.Parse(textBLongueurDangerG.Text) + float.Parse(textBLongueurSecuritaireG.Text) > 30)
            {
                MessageBox.Show("La somme de la longueur de la zone de danger avec celle de la zone sécuritaire du capteur gauche ne peut pas dépasser 30po", "Valeurs invalides", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            if (float.Parse(textBLongueurDangerM.Text) + float.Parse(textBLongueurSecuritaireM.Text) > 30)
            {
                MessageBox.Show("La somme de la longueur de la zone de danger avec celle de la zone sécuritaire du capteur du milieu ne peut pas dépasser 30po", "Valeurs invalides", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                return false;
            }
            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonEnregistrerProfil_Click(object sender, EventArgs e)
        ///
        /// Defini l'action a effectuer lors d'un click sur le bouton enregistrer du profil.
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonEnregistrerProfil_Click(object sender, EventArgs e)
        {
            if (textBNomProfil.Text.Equals(string.Empty))
                MessageBox.Show("Veuillez saisir un nom du profil", "Zone vide", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
            else
            {
                if (comboBProfils.Items.Contains(textBNomProfil.Text))
                    MessageBox.Show("Veuillez choisir un autre nom pour ce profil", "Profil existe déja", MessageBoxButtons.OK,
                                   MessageBoxIcon.Information);
                else
                {
                    if (verifierIntegrite())
                    {
                        _gestionProfils.profilActif = textBNomProfil.Text;
                        exporterProfil();
                        _gestionProfils.enregistrerProfil();
                        comboBProfils.Items.Add(textBNomProfil.Text);
                        comboBProfils.SelectedItem = textBNomProfil.Text;
                        cacherControleNouveauProfil();
                    }
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private int indiceDansEtats(string chaine)
        ///
        /// Cherche l'indice d'une chaine dans le tableau d'etats GestionProfils.etats
        ///
        /// @param[in] chaine : la chaine qu'on cherche l'indice.
        ///
        /// @return Indice de la chaine.
        ///
        ////////////////////////////////////////////////////////////////////////
        private int indiceDansEtats(string chaine)
        {
            int indice = 0;
            bool existe = false;
            for ( indice = 0; indice < GestionProfils.etats.Length && !existe; indice++ )
            {
                if (GestionProfils.etats[indice].Equals(chaine))
                    existe = true;
            }
            if ( existe )
                return indice - 1;
            else 
                return -1;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void exporterProfil()
        ///
        /// Exporte les données du profil dans l'interface profil vers l'instance 
        /// courante de GestionProfils
        ///
        /// @param Aucun.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void exporterProfil()
        {
            _gestionProfils.suivantSuiviLigne = (GestionProfils.ETATS)indiceDansEtats
                (comboBSuiviLigne.SelectedItem.ToString());
            _gestionProfils.suivantBalayage = (GestionProfils.ETATS)indiceDansEtats
                (comboBBalayage.SelectedItem.ToString());

            _gestionProfils.suivantDeviationGauche = (GestionProfils.ETATS)indiceDansEtats
                (comboBDeviationGauche.SelectedItem.ToString());
            _gestionProfils.angleDeviationGauche =  float.Parse(textBAngleDeviationGauche.Text);

            _gestionProfils.suivantDeviationDroite = (GestionProfils.ETATS)indiceDansEtats
                (comboBDeviationDroite.SelectedItem.ToString());
            _gestionProfils.angleDeviationDroite = float.Parse(textBAngleDeviationDroite.Text);

            _gestionProfils.suivantEviterDroite = (GestionProfils.ETATS)indiceDansEtats
                (comboBEviterDroite.SelectedItem.ToString());
            _gestionProfils.anglePivotementDroite = float.Parse(textBPivotementEviterD.Text);
            _gestionProfils.dureeReculDroite = int.Parse(textBReculEviterDroite.Text);

            _gestionProfils.suivantEviterGauche = (GestionProfils.ETATS)indiceDansEtats
                (comboBEviterGauche.SelectedItem.ToString());
            _gestionProfils.anglePivotementGauche = float.Parse(textBPivotementEviterG.Text);
            _gestionProfils.dureeReculGauche = int.Parse(textBReculEviterGauche.Text );

            _gestionProfils.suivantDangerCapteurD = (GestionProfils.ETATS)indiceDansEtats
                (comboBDangerDroit.SelectedItem.ToString());
            _gestionProfils.suivantSecuritaireCapteurD = (GestionProfils.ETATS)indiceDansEtats
                (comboBSecuritaireDroit.SelectedItem.ToString());
            _gestionProfils.longueurDangerCapteurD = float.Parse(textBLongueurDangerD.Text);
            _gestionProfils.longueurSecuritaireCapteurD = float.Parse(textBLongueurSecuritaireD.Text);

            _gestionProfils.suivantDangerCapteurM = (GestionProfils.ETATS)indiceDansEtats
                (comboBDangerMilieu.SelectedItem.ToString());
            _gestionProfils.suivantSecuritaireMilieu = (GestionProfils.ETATS)indiceDansEtats
                (comboBSecuritaireMilieu.SelectedItem.ToString());
            _gestionProfils.longueurDangerCapteurM = float.Parse(textBLongueurDangerM.Text);
            _gestionProfils.longueurSecuritaireCapteurM = float.Parse(textBLongueurSecuritaireM.Text);

            _gestionProfils.suivantDangerCapteurG = (GestionProfils.ETATS)indiceDansEtats
                (comboBDangerGauche.SelectedItem.ToString());
            _gestionProfils.suivantSecuritaireCapteurG = (GestionProfils.ETATS)indiceDansEtats
                (comboBSecuritaireGauche.SelectedItem.ToString());
            _gestionProfils.longueurDangerCapteurG = float.Parse(textBLongueurDangerG.Text);
            _gestionProfils.longueurSecuritaireCapteurG = float.Parse(textBLongueurSecuritaireG.Text);

            _gestionProfils.capteurDroitActif = checkBCapteurDroit.Checked;
            _gestionProfils.capteurGaucheActif = checkBCapteurGauche.Checked;
            _gestionProfils.capteurMilieuActif = checkBCapteurMilieu.Checked;
            _gestionProfils.suiveurLigneActif = checkBSuiveurL.Checked;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonAnnuler_Click(object sender, EventArgs e)
        ///
        /// Defini l'action a effectuer lors d'un click sur le bouton annuler.
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonAnnuler_Click(object sender, EventArgs e)
        {
            cacherControleNouveauProfil();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBNomProfil_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie du nom de profil aux lettres sans accent,
        /// les chiffres et - et _
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBNomProfil_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ( !char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && ( !char.IsLetter(e.KeyChar) 
                || (e.KeyChar == 'é') || (e.KeyChar == 'è') || (e.KeyChar == 'ê') || (e.KeyChar == 'ô')
                || (e.KeyChar == 'ç') || (e.KeyChar == 'à') || (e.KeyChar == 'â') || (e.KeyChar == 'î') 
                || (e.KeyChar == 'ù') || (e.KeyChar == 'û') ) && (e.KeyChar != '_') && (e.KeyChar != '-') )
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBPivotementEviterD_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de l'angle de pivotement de l'etat eviter droite
        /// aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBPivotementEviterD_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBReculEviterDroite_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie du temps de recul de l'etat eviter droite
        /// aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBReculEviterDroite_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBReculEviterGauche_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie du temps de recul de l'etat eviter gauche
        /// aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBReculEviterGauche_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBPivotementEviterG_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de l'angle de pivotement de l'etat eviter gauche
        /// aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBPivotementEviterG_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBAngleDeviationGauche_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de l'angle de deviation de l'etat deviation gauche
        /// aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBAngleDeviationGauche_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBAngleDeviationDroite_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de l'angle de deviation de l'etat deviation droite
        /// aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBAngleDeviationDroite_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBLongeurDangerG_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de la longueur de la zone de danger du
        /// capteur gauche aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBLongeurDangerG_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBLongueurSecuritaireG_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de la longueur de la zone securitaire du
        /// capteur gauche aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBLongueurSecuritaireG_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBLongueurDangerM_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de la longueur de la zone de danger du
        /// capteur milieu aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBLongueurDangerM_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBLongueurSecuritaireM_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de la longueur de la zone securitaire du
        /// capteur du milieu aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBLongueurSecuritaireM_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBLongueurDangerD_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de la longueur de la zone de danger du
        /// capteur droit aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBLongueurDangerD_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBLongueurSecuritaireD_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Limite les touches permis dans la saisie de la longueur de la zone securitaire du
        /// capteur droit aux chiffres seulement
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBLongueurSecuritaireD_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonEnregistrerM_Click(object sender, EventArgs e)
        ///
        /// Enregiste les modification apporté au profil actif
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonEnregistrerM_Click(object sender, EventArgs e)
        {
            if (verifierIntegrite())
            {
                exporterProfil();
                _gestionProfils.enregistrerProfil();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void buttonSupprimer_Click(object sender, EventArgs e)
        ///
        /// Supprime le profil selectionne
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void buttonSupprimer_Click(object sender, EventArgs e)
        {
            comboBProfils.Items.Remove(comboBProfils.SelectedItem);
            _gestionProfils.supprimerProfilCourant();
            comboBProfils.SelectedItem = nomProfilDefaut;
            //importerProfilActif();
        }
    }
}
