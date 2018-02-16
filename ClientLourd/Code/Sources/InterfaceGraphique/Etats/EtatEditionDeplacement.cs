///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionDeplacement.cs
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
    /// @class EtatEditionDeplacement
    /// @brief Classe decrivant l'etat de deplacement d'un objet.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionDeplacement : EtatEdition
    {
        private int compteurDeplacement_ = 0;
        private bool enDeplacement_; 

        private int xDebut_, yDebut_;

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

            xDebut_ = x;
            yDebut_ = y;
            lock (Program.NoyauLock)
            {
                FonctionsNatives.initialiserEnTraitement();
                if (Program.OnLine) //en ligne
                {
                    Program.SDispatcher.EditionConnectionM.SpreadUpdateMySelectedNodes();
                    Program.SDispatcher.EditionConnectionM.SpreadInitDeplacement();
                }
            }
            enDeplacement_ = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterGlissement( int x, int y )
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

            string chaineDeplacement = "";
            if (enDeplacement_)
            {
                Program.edition.Cursor = Cursors.SizeAll;
                if (compteurDeplacement_ == 3)
                {
                    lock (Program.NoyauLock)
                    {
                        if (Program.OnLine == false)
                        {
                            chaineDeplacement = Marshal.PtrToStringAnsi(FonctionsNatives.deplacerSelection(xDebut_, yDebut_, x, y));
                        }
                        else if (Program.OnLine) //en ligne
                        {
                            chaineDeplacement = Marshal.PtrToStringAnsi(FonctionsNatives.deplacerSelNoAction(xDebut_, yDebut_, x, y));
                            Program.SDispatcher.EditionConnectionM.SpreadMoveSelection(chaineDeplacement);
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
        /// Methode permettant le lancement d'algorithme lors du relachement d'un
        /// bouton de la souris.
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

            string chaineDeplacement = "";
            if (enDeplacement_)
            {
                Program.edition.Cursor = Cursors.Default;
                lock (Program.NoyauLock)
                {
                    if (!FonctionsNatives.objetsSelectionnesSurLaTable())
                    {
                        if (Program.OnLine == false) //en ligne
                        {
                            chaineDeplacement = Marshal.PtrToStringAnsi(FonctionsNatives.deplacerSelection(xDebut_, yDebut_, xDebut_, yDebut_));

                        }
                        else if (Program.OnLine)
                        {
                            chaineDeplacement = Marshal.PtrToStringAnsi(FonctionsNatives.deplacerSelNoAction(xDebut_, yDebut_, xDebut_, yDebut_));
                            Program.SDispatcher.EditionConnectionM.SpreadMoveSelection(chaineDeplacement);
                        }
                    }
                    else
                    {
                        if (Program.OnLine)
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
                enDeplacement_ = false;
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
            if ( enDeplacement_ )
            {
                Program.edition.Cursor = Cursors.Default;
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.deplacerSelection(xDebut_, yDebut_, xDebut_, yDebut_);
                }
                enDeplacement_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }
   }
}
