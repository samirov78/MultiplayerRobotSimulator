﻿///////////////////////////////////////////////////////////////////////////////
/// @file Simulation.cs
/// @author INF2990 Eq.11
/// @date 2016-03-21
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
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Web.UI;
using System.Windows.Threading;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Simulation
    /// @brief Classe correspondant au formulaire principale du mode Simulation.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-03-21
    ///////////////////////////////////////////////////////////////////////////
    public partial class Simulation : Form
    {
        /// Enregistre le mode courant du robot
        private bool modeEstManuel = false;
        /// represente la configuration des touches de controle du robot
        private ConfigurationControle controle;
        /// le profil selectionné dans le menu profils
        ToolStripMenuItem profilSelectionne;
        // la vue selectionne (orbite, orthographique ou premiere personne)
        ToolStripMenuItem vueSelectionnee;
        /// Enregistre si le bouton droit est presse ou pas
        private bool boutonDroitePresse = false;
        /// Compteur de deplacement de la souris pour ignorer un pixel sur deux dans le 
        /// deplacement de la fenetre
        private int compteurDeplacement_ = 0;
        /// Enregistre si la touche pour faire avancer le robot est appuie
        private bool toucheControleAvancerAppuyee = false;
        /// Enregistre si la touche pour faire reculer le robot est appuie
        private bool toucheControleReculerAppuyee = false;
        /// Enregistre si la touche pour faire tourner le robot au sens horaire est appuie
        private bool toucheControleRotationHAppuyee = false;
        /// Enregistre si la touche pour faire tourner le robot au sens antihoraire est appuie
        private bool toucheControleRotationAHAppuyee = false;
        /// Enregistre si le menu est affiche (pause)
        private bool menuAffiche = false;
        /// Enregistre la commande de retour au menu principale en mode test passe a l'edition
        private bool retourAPrincipal = false;
        //projet3
        private int compteurMaj = 0;
        DispatcherTimer DispatcherTimer;
        private bool simulationTerminee = false;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Simulation()
        ///
        /// Constructeur avec un seul parametre.
        /// 
        /// @param[in] simulation : si simulation = true la fenetre créer est une
        /// instance simulation sinon c'est une instance Test
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public Simulation(bool simulation)
        {
            this.KeyPreview = true;
            this.BackColor = Color.Black;
            Program.peutAfficher = true;
            InitializeComponent();
            chargerProfils();
            if (simulation)
                FonctionsNatives.changerModeApplication('S');
            else
                FonctionsNatives.changerModeApplication('T');
            InitialiserAnimation();
            controle = new ConfigurationControle("données/Configuration.xml");
            orthographiqueToolStripMenuItem.BackColor = Color.LightSkyBlue;
            vueSelectionnee = orthographiqueToolStripMenuItem;
            if (simulation)
                modeEditionToolStripMenuItem.Visible = false;
            else
            {
                this.Text = "Test";
                premièrePersonneToolStripMenuItem.Visible = false;
            }
            m_chatPanel.Controls.Add(Program.SChatPanel);
            m_chatPanel.Visible = true;
            Program.SChatPanel.In = "Simulation";
            //*spredlancersimulation( simulation begin positionrobot)
            Program.SDispatcher.SimulationConnectionM.ChaineRobotReceived += mettreAjourRobot;
            Program.SDispatcher.SimulationConnectionM.FinSimulationReceived += terminerSimulation;

        }

        /*private void initialiseSimulOnLine(string username)
        {
            lock (Program.NoyauLock)
            {
                FonctionsNatives.SetRobotUsername(username);
                
                //lancer la simulation
            }
        }*/





        private void terminerSimulation()
        {
            lock (Program.NoyauLock)
            {
                FonctionsNatives.EnleverFlechesOnline();
            }
            simulationTerminee = true;
            modeEditionToolStripMenuItem_Click(null, null);
        }

        private void mettreAjourRobot(string chaineRobot)
        {
            lock (Program.NoyauLock)
            {
                FonctionsNatives.mettreAjourRobot(chaineRobot);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void chargerProfils()
        ///
        /// Charge les profils dans le menu profils depuis le fichier profils.xml
        /// et mettre le profil actif comme profil selectionne
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void chargerProfils()
        {
            System.Xml.XmlTextReader reader = new System.Xml.XmlTextReader("données/profils.xml");
            bool profilActifTrouve = false;
            while (reader.Read() && !profilActifTrouve)
            {
                reader.MoveToContent();
                if (reader.NodeType == System.Xml.XmlNodeType.Element && reader.Name == "profils")
                {
                    profilSelectionne = new System.Windows.Forms.ToolStripMenuItem((reader.GetAttribute("actif")));
                    profilSelectionne.BackColor = Color.LightSkyBlue;
                    profilSelectionne.Click += new System.EventHandler(this.profilToolStripMenuItem_Click);
                    profilsToolStripMenuItem.DropDownItems.Add(profilSelectionne);
                    profilActifTrouve = true;
                }
            }

            while (reader.Read())
            {
                reader.MoveToContent();
                if (reader.NodeType == System.Xml.XmlNodeType.Element && reader.Name == "profil")
                {
                    if (!reader.GetAttribute("nom").Equals(profilSelectionne.ToString()))
                    {
                        ToolStripMenuItem menuItem = new System.Windows.Forms.ToolStripMenuItem((reader.GetAttribute("nom")));
                        menuItem.Click += new System.EventHandler(this.profilToolStripMenuItem_Click);
                        profilsToolStripMenuItem.DropDownItems.Add(menuItem);
                    }
                }
            }
            reader.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void changerProfilActif(string nomProfil)
        ///
        /// Change le profil selectionne et appel la fonction adequat du noyeau 
        /// pour charger le profil choisi
        /// 
        /// @param[in] nomProfil : le nom du profil a selectionne et a charger
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void changerProfilActif(string nomProfil)
        {
            System.Xml.XmlDocument document = new System.Xml.XmlDocument();
            document.Load("données/profils.xml");
            System.Xml.XmlNode nodeProfils = document.SelectSingleNode("profils");
            nodeProfils.Attributes["actif"].Value = nomProfil;
            System.Xml.XmlTextWriter writer = new System.Xml.XmlTextWriter("données/profils.xml", Encoding.UTF8);
            writer.Formatting = System.Xml.Formatting.Indented;
            document.WriteTo(writer);
            writer.Close();
            FonctionsNatives.chargerProfilRobot(nomProfil);
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn ~Simulation()
        ///
        /// Destructeur
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        ~Simulation()
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool lancerSimulation(String fileName)
        ///
        /// Lance la simulation courante
        /// 
        /// @param[in] fileName : le nom du fichier contenant la scene a simuler
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public bool lancerSimulation(String fileName)
        {
            //FonctionsNatives.jouerMusiqueSimulation();
            FonctionsNatives.chargerZoneDeSimulation(fileName);
            if (!Program.IsSpectator)
               FonctionsNatives.initialiserRobot(false);
            FonctionsNatives.redimensionnerFenetre(scene.Width, scene.Height);

            menuStrip.Hide();
            if (!Program.IsSpectator)
                FonctionsNatives.actionnerModeAutomatique();
            if (Program.OnLine)
            {
                if (!Program.IsSpectator)
                {
                    lock (Program.NoyauLock)
                    {
                        FonctionsNatives.SetRobotUsername(Program.SConnection.UserName);
                    }
                }
            }
            this.ShowDialog();

            //init
            return retourAPrincipal;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void InitialiserAnimation()
        ///
        /// Methode permettant l'initialisation d'OpenGL et du dessin OpenGL
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            FonctionsNatives.initialiserOpenGL(scene.Handle);
            FonctionsNatives.dessinerOpenGL(0);
            // FonctionsNatives.jouerMusiqueSimulation();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void MettreAJour(double tempsInterAffichage)
        ///
        /// Methode permettant la mise a jour de la scene.
        /// 
        /// @param[in] tempsInterAffichage : intervalle de temps entre chaque image
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL(tempsInterAffichage);
                });
            }
            catch (Exception)
            {
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void  Simulation_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        ///
        /// Methode permettant la capture d'evenement PreviewKeyDown pour definir les touche de
        /// controles a capturer et traiter par KeyDown quand la fenetre simulation a le focus.
        /// 
        /// @param[in] sender : Represente la touche reliee a l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Simulation_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            scene_PreviewKeyDown(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void  scene_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        ///
        /// Methode permettant la capture d'evenement PreviewKeyDown pour definir les touche de
        /// controles a capturer et traiter par KeyDown quand la scene a le focus.
        /// 
        /// @param[in] sender : Represente le declencher de l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void scene_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.NumPad1:
                case Keys.D1:
                case Keys.NumPad2:
                case Keys.D2:
                case Keys.Left:
                case Keys.Right:
                case Keys.Up:
                case Keys.Down:
                case Keys.Escape:
                case Keys.Back:
                case Keys.Add:
                case Keys.Oemplus:
                case Keys.Subtract:
                case Keys.OemMinus:
                    e.IsInputKey = true;
                    break;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void  Simulation_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        ///
        /// Methode permettant la capture d'evenement KeyDown et definie la réaction adequate pour
        /// chaque touche capturé.
        /// 
        /// @param[in] sender : Represente le declencher de l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Simulation_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Back:
                    if (!menuAffiche)
                    {
                        FonctionsNatives.libererRobot();
                        FonctionsNatives.initialiserRobot(false);
                        FonctionsNatives.redimensionnerFenetre(scene.Width, scene.Height);
                        //FonctionsNatives.libererFmod();
                        //FonctionsNatives.jouerMusiqueSimulation();
                        if (!modeEstManuel)
                            FonctionsNatives.actionnerModeAutomatique();
                    }
                    break;
                case Keys.Left:
                    if (!menuAffiche)
                        FonctionsNatives.deplacerDroite();
                    break;
                case Keys.Right:
                    if (!menuAffiche)
                        FonctionsNatives.deplacerGauche();
                    break;
                case Keys.Up:
                    if (!menuAffiche)
                        FonctionsNatives.deplacerBas();
                    break;
                case Keys.Down:
                    if (!menuAffiche)
                        FonctionsNatives.deplacerHaut();
                    break;
                case Keys.Add:
                case Keys.Oemplus:
                    if (!menuAffiche)
                        FonctionsNatives.zoomIn();
                    break;
                case Keys.Subtract:
                case Keys.OemMinus:
                    if (!menuAffiche)
                        FonctionsNatives.zoomOut();
                    break;
                case Keys.Escape:
                    if (!menuAffiche)
                    {
                        Program.peutAfficher = false;
                        menuStrip.Show();
                        menuAffiche = true;
                        boutonDroitePresse = false;
                        this.Cursor = Cursors.Default;
                        FonctionsNatives.pauseSonSimulation();
                    }
                    else
                    {
                        menuStrip.Hide();
                        menuAffiche = false;
                        Program.peutAfficher = true;
                        FonctionsNatives.UnPauseSonSimulation();
                    }
                    break;
                case Keys.D1:
                case Keys.NumPad1:
                    if (!menuAffiche)
                        orthographiqueToolStripMenuItem_Click(null, null);
                    break;
                case Keys.D2:
                case Keys.NumPad2:
                    if (!menuAffiche)
                        orbiteToolStripMenuItem_Click(null, null);
                    break;
                case Keys.D3:
                case Keys.NumPad3:
                    if (this.Text == "Simulation" && !menuAffiche)
                        premièrePersonneToolStripMenuItem_Click(null, null);
                    break;
                case Keys.T:
                    if (this.Text == "Test" && !menuAffiche)
                        modeEditionToolStripMenuItem_Click(null, null);
                    break;
                case Keys.J:
                    if (!menuAffiche)
                        FonctionsNatives.basculerActivationLumiereAmbiante();
                    break;
                case Keys.K:
                    if (!menuAffiche)
                        FonctionsNatives.basculerActivationLumiereDirectionnelle();
                    break;
                case Keys.L:
                    if (!menuAffiche)
                        FonctionsNatives.basculerActivationSpots();
                    break;
                case Keys.B:
                    if (!menuAffiche)
                        FonctionsNatives.basculerActivationDebougage();
                    break;
                default:
                    if (e.KeyCode == Keys.Q && e.Control)
                    {
                        menuPrincipalCtrlQToolStripMenuItem_Click(null, null);
                        break;
                    }
                    if (!menuAffiche)
                    {
                        if (modeEstManuel)
                        {
                            if (e.KeyCode == controle.toucheControleAvancer || e.KeyCode == controle.toucheControleReculer
                                || e.KeyCode == controle.toucheControleRotationH || e.KeyCode == controle.toucheControleRotationAH)
                            {
                                if (e.KeyCode == controle.toucheControleAvancer)
                                    toucheControleAvancerAppuyee = true;
                                else if (e.KeyCode == controle.toucheControleReculer)
                                    toucheControleReculerAppuyee = true;
                                else if (e.KeyCode == controle.toucheControleRotationH)
                                    toucheControleRotationHAppuyee = true;
                                else if (e.KeyCode == controle.toucheControleRotationAH)
                                    toucheControleRotationAHAppuyee = true;
                                interpreterTouches();
                            }
                        }
                        if (e.KeyCode == controle.toucheControleModeMA)
                        {
                            modeEstManuel = !modeEstManuel;
                            if (!modeEstManuel)
                                FonctionsNatives.actionnerModeAutomatique();
                            else
                                FonctionsNatives.stopperModeAutomatique();
                        }
                    }
                    break;
            }
            e.Handled = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void  interpreterTouches()
        ///
        /// Methode permettant l'invocation de l'execution d'un certain comportement sur le robot
        /// dependement des touches de controles pressées.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void interpreterTouches()
        {
            if (toucheControleAvancerAppuyee)
            {
                if (toucheControleReculerAppuyee)
                {
                    if (toucheControleRotationAHAppuyee)
                    {
                        if (toucheControleRotationHAppuyee)
                            FonctionsNatives.arreterRobot();
                        else
                            FonctionsNatives.actionnerRobot(0.0, 1.0, true);
                    }
                    else
                    {
                        if (toucheControleRotationHAppuyee)
                            FonctionsNatives.actionnerRobot(1.0, 0.0, true);
                        else
                            FonctionsNatives.arreterRobot();
                    }
                }
                else
                {
                    if (toucheControleRotationAHAppuyee)
                    {
                        if (toucheControleRotationHAppuyee)
                            FonctionsNatives.actionnerRobot(1.0, 1.0, true);
                        else
                            FonctionsNatives.actionnerRobot(0.5, 1.0, true);
                    }
                    else
                    {
                        if (toucheControleRotationHAppuyee)
                            FonctionsNatives.actionnerRobot(1.0, 0.5, true);
                        else
                            FonctionsNatives.actionnerRobot(1.0, 1.0, true);
                    }
                }
            }
            else
            {
                if (toucheControleReculerAppuyee)
                {
                    if (toucheControleRotationAHAppuyee)
                    {
                        if (toucheControleRotationHAppuyee)
                            FonctionsNatives.actionnerRobot(1.0, 1.0, false);
                        else
                            FonctionsNatives.actionnerRobot(1.0, 0.5, false);
                    }
                    else
                    {
                        if (toucheControleRotationHAppuyee)
                            FonctionsNatives.actionnerRobot(0.5, 1.0, false);
                        else
                            FonctionsNatives.actionnerRobot(1.0, 1.0, false);
                    }
                }
                else
                {
                    if (toucheControleRotationAHAppuyee)
                    {
                        if (toucheControleRotationHAppuyee)
                            FonctionsNatives.arreterRobot();
                        else
                            FonctionsNatives.actionnerRobot(0.0, 1.0, true);
                    }
                    else
                    {
                        if (toucheControleRotationHAppuyee)
                            FonctionsNatives.actionnerRobot(1.0, 0.0, true);
                        else
                            FonctionsNatives.arreterRobot();
                    }
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Simulation_KeyUp(object sender, KeyEventArgs e)
        ///
        /// Methode permettant la capture d'evenement KeyUp et defini la réaction
        /// adequate du robot si une touche du controle est concerne
        /// 
        /// @param[in] sender : Represente le declencher de l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Simulation_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == controle.toucheControleAvancer)
                toucheControleAvancerAppuyee = false;
            else
            {
                if (e.KeyCode == controle.toucheControleReculer)
                    toucheControleReculerAppuyee = false;
                else
                {
                    if (e.KeyCode == controle.toucheControleRotationH)
                        toucheControleRotationHAppuyee = false;
                    else
                    {
                        if (e.KeyCode == controle.toucheControleRotationAH)
                            toucheControleRotationAHAppuyee = false;
                    }
                }
            }
            interpreterTouches();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Simulation_FormClosing(object sender, FormClosingEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic le bouton de fermeture
        /// de la fenetre et libere OpenGL et desactive l'affichage
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Simulation_FormClosing(object sender, FormClosingEventArgs e)
        {
            Program.SDispatcher.SimulationConnectionM.ChaineRobotReceived -= mettreAjourRobot;
            DispatcherTimer.Tick -= dispatcherTimer_Tick;
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                FonctionsNatives.libererFmod();
                Program.peutAfficher = false;
            }
            Program.SChatPanel.In = "";
            if (this.Controls.Contains(Program.SChatPanel))
                this.Controls.Remove(Program.SChatPanel);
            else
                Program.SChatWindow.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void menuPrincipalCtrlQToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur l'option retour
        /// au menu principalele et ferme la fenetre avec changement de la variable 
        /// retourAPrincipal pour que le mode edition (en cas de test) retourne au menu principale.
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void menuPrincipalCtrlQToolStripMenuItem_Click(object sender, EventArgs e)
        {
            retourAPrincipal = true;
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant l'activation de la vue orthographique
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////    
        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (orthographiqueToolStripMenuItem != vueSelectionnee)
            {
                vueSelectionnee.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                orthographiqueToolStripMenuItem.BackColor = Color.LightSkyBlue;
                vueSelectionnee = orthographiqueToolStripMenuItem;
                FonctionsNatives.activerVueOrthographique();
                FonctionsNatives.redimensionnerFenetre(scene.Width, scene.Height);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void premièrePersonneToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant l'activation de la vue première Personne
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        //////////////////////////////////////////////////////////////////////// 
        private void premièrePersonneToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (premièrePersonneToolStripMenuItem != vueSelectionnee)
            {
                vueSelectionnee.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                premièrePersonneToolStripMenuItem.BackColor = Color.LightSkyBlue;
                vueSelectionnee = premièrePersonneToolStripMenuItem;
                FonctionsNatives.activerVuePremierePersonne();
                FonctionsNatives.redimensionnerFenetre(scene.Width, scene.Height);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant l'activation de la vue en orbite
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (orbiteToolStripMenuItem != vueSelectionnee)
            {
                vueSelectionnee.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                orbiteToolStripMenuItem.BackColor = Color.LightSkyBlue;
                vueSelectionnee = orbiteToolStripMenuItem;
                FonctionsNatives.activerVueOrbite();
                FonctionsNatives.redimensionnerFenetre(scene.Width, scene.Height);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoneDeDessin_MouseWheel(object sender, MouseEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement provenant de roulette de
        /// la souris l'interprete en zoom avant ou arriere.
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void scene_MouseWheel(object sender, MouseEventArgs e)
        {
            if (!menuAffiche)
            {
                int nombreDeZoom = e.Delta / 120;
                for (int i = 0; i < Math.Abs(nombreDeZoom); i++)
                {
                    if (nombreDeZoom < 0)
                        FonctionsNatives.zoomOut();
                    else
                        FonctionsNatives.zoomIn();
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Simulation_Resize(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de redimensionnement de 
        /// la fenetre d'edition et la redimentionne tout en mettant a jour l'affichage.
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void Simulation_Resize(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(scene.Width, scene.Height);
            Program.executerMiseAJour();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Simulation_Resize(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de selection d'un profil 
        /// et le met comme profil actif
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void profilToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (sender != profilSelectionne)
            {
                changerProfilActif(sender.ToString());
                profilSelectionne.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                profilSelectionne = (System.Windows.Forms.ToolStripMenuItem)sender;
                profilSelectionne.BackColor = Color.LightSkyBlue;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void scene_MouseDown(object sender, MouseEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic et initialise le
        /// deplacement de la scene si le bouton est droit et la scene n'est pas en pause
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void scene_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right && !menuAffiche)
            {
                FonctionsNatives.sauverPositionSouris(e.Location.X, e.Location.Y);
                this.Cursor = Cursors.SizeAll;
                boutonDroitePresse = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void scene_MouseMove(object sender, MouseEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de deplacement de la souris
        /// et deplace la scene si le bouton droit presse et le scene n'est pas en pause
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void scene_MouseMove(object sender, MouseEventArgs e)
        {
            // Said à enlever
            FonctionsNatives.verifierPositionCurseur(e.Location.X, e.Location.Y);
            if (boutonDroitePresse && !menuAffiche)
            {
                if (compteurDeplacement_ == 2)
                {
                    FonctionsNatives.deplacerFenetreVirtuelleSouris(e.Location.X, e.Location.Y);
                    compteurDeplacement_ = 0;
                }
                else
                    compteurDeplacement_++;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void scene_MouseUp(object sender, MouseEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de relachement du bouton
        /// de la souris et change le curseur et marque le bouton non presse
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void scene_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                boutonDroitePresse = false;
                this.Cursor = Cursors.Default;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void modeEditionToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de selection de l'option mode edition
        /// et ferme la fenetre pour retourner a la fenetre d'edition
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void modeEditionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
            if (!simulationTerminee)
                Program.SDispatcher.SimulationConnectionM.SpreadFinSimulation();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void scene_MouseEnter(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de faire entrer le curseur
        /// de la souris dans le panel de la scene et donne le focus a ce dernier 
        /// pour regler le probleme de zoom avec roulette
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void scene_MouseEnter(object sender, EventArgs e)
        {
            if (!Program.clavardageEnPremierPlan_)
            {
                scene.Focus();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Simulation_Load(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement chargement de la page
        /// et defini DispacherTimer qui va etre executer a chaque intervalle du temps
        /// definis par tempsEcouleVoulu du program pour forcer le rafrichisement de l'image 
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Simulation_Load(object sender, EventArgs e)
        {
            DispatcherTimer = new DispatcherTimer(DispatcherPriority.Background);
            DispatcherTimer.Tick += dispatcherTimer_Tick;
            DispatcherTimer.Interval = Program.tempsEcouleVoulu;
            DispatcherTimer.Start();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void dispatcherTimer_Tick(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de fin du temps precisé
        /// dans la definition du DispatcherTimer et lance l'execution de la fonction
        /// permettant le rafraichisement de l'image
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            string chaineRobot = "";
            Program.executerMiseAJour();
            if (Program.OnLine)
            {
                //compteurMaj++;
                //if (compteurMaj >= 2)
                {
                    // capturer l etat du robot et diffuser
                    lock (Program.NoyauLock)
                    {
                        chaineRobot = Marshal.PtrToStringAnsi(FonctionsNatives.getInfosRobot());
                        Console.WriteLine("chaine robot :  {0}", chaineRobot);
                    }
                    Program.SDispatcher.SimulationConnectionM.SpreadInfoRobot(chaineRobot);
                    //compteurMaj = 0;
                }
            }
        }

        private void tutorielToolStripMenuItem_Click(object sender, EventArgs e)
        {
            lancerTutoriel();
        }

        public void lancerTutoriel()
        {
            const string file = "../Tuto/Exe/InterfaceGraphique";
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = false;
            startInfo.UseShellExecute = false;
            startInfo.FileName = file;
            startInfo.WorkingDirectory = "../Tuto/Exe/";
            //startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.Arguments = "Simulation";
            try
            {
                using (Process exeProcess = Process.Start(startInfo))
                {
                    exeProcess.WaitForExit();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    /// @class FonctionsNatives
    /// @brief Classe contenant des fonction externe implementer au niveau du
    /// noyau de l'application.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserRobot(bool vuePremierePersonne);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void arreterRobot();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void actionnerRobot(double rapportVitesseGauche, double rapportVitesseDroit, bool sensDirect);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerProfilRobot(string nomProfil);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void actionnerModeAutomatique();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void stopperModeAutomatique();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererRobot();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void basculerActivationLumiereAmbiante();
                    
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void basculerActivationLumiereDirectionnelle();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void basculerActivationSpots();
                    
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void basculerActivationDebougage();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerVueOrbite();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerVueOrthographique();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerVuePremierePersonne();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void jouerMusiqueSimulation();
        //initialiserSonEditeur


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserSonEditeur();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererFmod();

        //
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void pauseSonSimulation();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void UnPauseSonSimulation();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetRobotUsername(string username);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getInfosRobot();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mettreAjourRobot(string chaineRobot);
        //initialiserFleche
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserFleches(string fleche);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void EnleverFlechesOnline();
    }
}
