﻿///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionSelection.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.IO;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


// pour tutoriel
using System.Drawing;
using Commun;
using InterfaceGraphique.Forms;
using System.Globalization;
using System.Media;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionSelection
    /// @brief Classe decrivant le comportement d'un objet lors de sa selection.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionSelection : EtatEdition
    {
        private int xDebut_ = 0;
        private int yDebut_ = 0;
        private int xFin_ = 0;
        private int yFin_ = 0;
        private bool rectangleAffiche_ = false;
        //private Keys modificateur_ = Keys.None;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void initialiserDebut(int x, int y)
        ///
        /// Methode permettant l'initialisation de certaines donnees lors d'un
        /// clic de souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void initialiserDebut(int x, int y)
        {
            xDebut_ = x;
            yDebut_ = y;
            lock (Program.NoyauLock)
            {
                FonctionsNatives.tracerRectangleElastique(x, y);
            }
            rectangleAffiche_ = true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterClic(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithmes lors d'un clic d'une
        /// touche quelconque.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @param[in] k : Represente la touche appuyer.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterClic(int x, int y, Keys k)
        {
            // code pour la selection de l'objet au dessus du clic

            /*   Button oo = new Button();
               oo.Text = "gggggggggggggggg";*/
               

           
           
            

            bool aActiver;
            int nombreElementSelectionne;
            string chaineDeSelection;
            if (!Program.edition.OnLine) //hors ligne
             {
                lock (Program.NoyauLock)
                {
                    if (k == Keys.Control)
                        chaineDeSelection = Marshal.PtrToStringAnsi(FonctionsNatives.selectionObjet(x, y + 5, false));
                    else
                        chaineDeSelection = Marshal.PtrToStringAnsi(FonctionsNatives.selectionObjet(x, y + 5, true));
                    nombreElementSelectionne = FonctionsNatives.obtenirNombreNoeudsSelectionnes();


                    /// pour tutoriel
                    if (nombreElementSelectionne >= 1 && Program.edition.tuto == true )
                    {

                        Program.edition.pictureBox1.Visible = false;
                        Program.edition.text2.Visible = false;
                        Program.edition.selectionToolStripButton.Enabled = false;
                        Program.edition.rotationToolStripButton.Enabled = true;

                        Program.edition.felche1.Visible = true;
                        Program.edition.felche1.Location = new Point(273, 14);
                        Program.edition.text1.Visible = true;
                        Program.edition.text1.Location = new Point(284, 100);
                        Program.edition.text1.Font = new Font(Program.edition.text1.Font, FontStyle.Bold);
                        Program.edition.text1.Text = "Pour effectuer la Rotation de cet objet il faut appuyer sur le boutton indiqué par la fleche ";
                                                      
                    }



                    aActiver = (nombreElementSelectionne > 1 ||
                        (nombreElementSelectionne == 1 && !FonctionsNatives.noeudSelectionneEstFleche()));
                    Console.WriteLine("chaine de selection: C# : {0} ", chaineDeSelection);
                    Program.edition.changerEtatOptionSupprimmer(aActiver);
                    if (nombreElementSelectionne == 1)
                        Program.edition.enableConfigurationPanel();
                    else
                        Program.edition.disableConfigurationPanel();
                }
            }
            else if (Program.edition.OnLine) // si en ligne
            {
               // Console.WriteLine("online: {0} ", Program.edition.inline);
                lock (Program.NoyauLock)
                {
                    if (k == Keys.Control)
                        chaineDeSelection = Marshal.PtrToStringAnsi(FonctionsNatives.selectionObjet(x, y, false));
                    else
                    {
                        //Program.SDispatcher.EditionConnectionM.SpreadDeselectNodes();
                        chaineDeSelection = Marshal.PtrToStringAnsi(FonctionsNatives.selectionObjet(x, y, true));
                    }
                    nombreElementSelectionne = FonctionsNatives.obtenirNombreNoeudsSelectionnes();
                    aActiver = (nombreElementSelectionne > 1 ||
                        (nombreElementSelectionne == 1 && !FonctionsNatives.noeudSelectionneEstFleche()));
                    //en cas de la selection en ligne, diviser les IDs et les envoyer au serveur
                    string[] splitData = null;
                    if (chaineDeSelection == "")
                    {
                        Program.SDispatcher.EditionConnectionM.SpreadDeselectNodes();
                    }
                    else if (chaineDeSelection.IndexOf(";") == -1)//un seul noeud selectionne
                    {
                        string[] unicSelection = { chaineDeSelection };
                        //Console.WriteLine("un seul ID selectionne");
                        Program.SDispatcher.EditionConnectionM.SpreadSelectNodes(unicSelection);
                    }
                    else
                    {
                        splitData = chaineDeSelection.Split(';'); 
                        Program.SDispatcher.EditionConnectionM.SpreadSelectNodes(splitData);
                    }
                    Program.edition.changerEtatOptionSupprimmer(aActiver);
                    if (nombreElementSelectionne == 1)
                        Program.edition.enableConfigurationPanel();
                    else
                        Program.edition.disableConfigurationPanel();
                }
            }
           

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterDepot(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithmes lors du relachement d'un
        /// bouton de souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @param[in] k : Represente la touche appuyer.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterDepot(int x, int y, Keys k)
        {
            // code pour la selection de l'objet au dessus du clic
            // FonctionsNatives.terminerRectangleElastique(x, y);
            string chaineDeSelection = "";
            if ( rectangleAffiche_ )
            {
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.terminerRectangleElastique(x, y);
                }
                bool estEnfonce = false;
                if (k == Keys.Control)
                {
                    estEnfonce = true; 
                }
                lock (Program.NoyauLock)
                {
                    chaineDeSelection = Marshal.PtrToStringAnsi(FonctionsNatives.selectRectElastique(xDebut_, yDebut_, x, y, estEnfonce));
                    Console.WriteLine("chaine de selection: C# : {0} ", chaineDeSelection);
                }
                if (Program.edition.OnLine) //en ligne
                {
                    string[] splitData = null;
                    if (chaineDeSelection == "")
                    {
                        Program.SDispatcher.EditionConnectionM.SpreadDeselectNodes();
                    }
                    else if (chaineDeSelection.IndexOf(";") == -1)//un seul noeud selectionne
                    {
                        string[] unicSelection = { chaineDeSelection };
                        Console.WriteLine("un seul ID selectionne");
                        Program.SDispatcher.EditionConnectionM.SpreadSelectElastique(unicSelection);
                    }
                    else
                    {
                        splitData = chaineDeSelection.Split(';');
                        Program.SDispatcher.EditionConnectionM.SpreadSelectElastique(splitData);
                    }
                }
                }
            else 
            {
                if (Math.Abs(x - xDebut_) <= 3 && Math.Abs(y - xDebut_) <= 3)
                    interpreterClic(x, y, k);
            }
            bool aActiver;
            int nombreElementSelectionne;
            lock (Program.NoyauLock)
            {
                nombreElementSelectionne = FonctionsNatives.obtenirNombreNoeudsSelectionnes();
                aActiver = (nombreElementSelectionne > 1 ||
                    (nombreElementSelectionne == 1 && !FonctionsNatives.noeudSelectionneEstFleche()));
            }
            if (nombreElementSelectionne == 1)
                Program.edition.enableConfigurationPanel();
            else
                Program.edition.disableConfigurationPanel();
            Program.edition.changerEtatOptionSupprimmer(aActiver);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterGlissement(int x, int y)
        ///
        /// Methode permettant le lancement d'algorithme lors du deplacement de
        /// la souris avec un certain bouton enfonce.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterGlissement(int x, int y)
        {
            xFin_ = x;
            yFin_ = y;
            if ( x == xDebut_ || y == yDebut_ || ( Math.Abs(x - xDebut_) <= 3 && Math.Abs(y - xDebut_) <= 3 ) )
            {
                if ( rectangleAffiche_ )
                {
                    lock (Program.NoyauLock)
                    {
                        FonctionsNatives.tracerRectangleElastique(x, y);
                        FonctionsNatives.terminerRectangleElastique(x, y);
                    }
                    rectangleAffiche_ = false;
                }
            }
            else
            {
                if ( !rectangleAffiche_ )
                {
                    lock (Program.NoyauLock)
                    {
                        FonctionsNatives.tracerRectangleElastique(xDebut_, yDebut_);
                    }
                    rectangleAffiche_ = true;
                }
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.tracerRectangleElastique(x, y);
                }
            }
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool interpreterEchap()
        ///
        /// Methode permettant le lancement d'algorithme lors de l'appui de la touche
        /// Echap.
        /// 
        /// @return True par defaut.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool interpreterEchap()
        {
            if (rectangleAffiche_)
            {
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.terminerRectangleElastique(xFin_, yFin_);
                }
                rectangleAffiche_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }


        /*public void updatePos(int x, int y)
        {
            xD = x;
            yMouseDown = y;
        }*/
    }

}