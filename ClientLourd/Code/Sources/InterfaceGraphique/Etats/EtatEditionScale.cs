///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionScale.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionScale
    /// @brief Classe decrivant le redimensionnement d'un objet.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionScale : EtatEdition
    {
        private int compteurDeplacement_ = 0;
        //private bool 
        private bool enScale_;
        int xDebut, yDebut;
     

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
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return;

            xDebut = x;
            yDebut = y;
            enScale_ = true;
            lock (Program.NoyauLock)
            {
                FonctionsNatives.initialiserScaleEnTraitement();
                if (Program.OnLine) //en ligne
                {
                    Program.SDispatcher.EditionConnectionM.SpreadUpdateMySelectedNodes();
                    Program.SDispatcher.EditionConnectionM.SpreadInitScaleSel();
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn  public override void interpreterGlissement( int x, int y )
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
        public override void interpreterGlissement( int x, int y )
        {

            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return;

            double facteur1000;
            string facteurStr = "";
            if (enScale_)
            {
                Program.edition.Cursor = Cursors.NoMoveVert;
                if (compteurDeplacement_ == 2)
                {
                    double facteurScale = 1.0 - (y - yDebut) / 60.0;

                    if (facteurScale <= 0.01)
                    {
                        facteurScale = 0.01;
                    }
                    lock (Program.NoyauLock)
                    {
                        if (Program.OnLine == false)
                        {
                            facteurStr = Marshal.PtrToStringAnsi(FonctionsNatives.scaleSelection(facteurScale));
                        }
                        else if (Program.OnLine) //en ligne
                        {
                            facteur1000 = facteurScale * 1000;//;
                            Program.SDispatcher.EditionConnectionM.SpreadScaleSelection(facteur1000.ToString());
                        }
                       
                    }
                    compteurDeplacement_ = 0;
                }
                else
                    compteurDeplacement_++;
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
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return;

            double facteur1000;
            string factorStr = "";
            if (enScale_)
            {
                // code a executer quand le bouton est relaché
                Program.edition.Cursor = Cursors.Default;
                lock (Program.NoyauLock)
                {
                    if (!FonctionsNatives.objetsSelectionnesSurLaTable())
                    {
                        if (Program.OnLine == false)
                        {
                            factorStr = Marshal.PtrToStringAnsi(FonctionsNatives.scaleSelection(1.0));
                        }


                        if (Program.OnLine) //en ligne
                        {
                            //FonctionsNatives.retournerAuScaleInitiale();
                            //facteur1000 = 1.0000;
                            //Program.SDispatcher.EditionConnectionM.SpreadScaleSelection(facteur1000.ToString());
                            Program.SDispatcher.EditionConnectionM.SpreadRetourAuscaleInit();
                        }

                    }
                    else
                    {
                        if (Program.OnLine) //en ligne
                        {
                            //mise a jour de la carte au niveau du serveur
                            string selectedNodesString = Marshal.PtrToStringAnsi(FonctionsNatives.getMySelectedNodesString());
                            string[] dataSplit = selectedNodesString.Split('@');
                            for (int i = 0; i < dataSplit.Length; i++)
                            {
                                Program.SDispatcher.EditionConnectionM.SpreadModifyNode(dataSplit[i]);
                            }
                        }
                        else
                            Program.edition.marquerModificationDansLaScene();
                    }
                }
                enScale_ = false;
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
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return true;

            if (enScale_)
            {
                Program.edition.Cursor = Cursors.Default;
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.scaleSelection(1.0);
                }
                enScale_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }
   }
}

