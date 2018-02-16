///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionDuplication.cs
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



namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionDuplication
    /// @brief Classe decrivant l'etat de duplication d'un objet
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionDuplication : EtatEdition
    {

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
            //if (verifierCurseur(x, y))
            //{
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return;

            string chaine = "";
            bool duplique = false;
            lock (Program.NoyauLock)
            {
                if (Program.OnLine == false) //hors ligne
                {
                    duplique = FonctionsNatives.dupliquerObjetsSelectionnes(x, y, false);
                }
                else if (Program.OnLine)
                {
                    chaine = Marshal.PtrToStringAnsi(FonctionsNatives.duplicateSelNoAction(x, y, false));
                    Program.SDispatcher.EditionConnectionM.SpreadDuplicateSelection(chaine);
                    //pour duplique --->new fonctionNative get FacadeModele::duplique_ 
                    string chaineDuplication = Marshal.PtrToStringAnsi(FonctionsNatives.getDuplicatedNodesStr());
                    if (chaineDuplication != "cancelled")
                    {
                        string[] dataSplit = chaineDuplication.Split('@');
                        Console.WriteLine("Nombre de dupliques C# : {0}", dataSplit.Length);
                        for (int i = 0; i < dataSplit.Length; i++)
                        {
                            Program.SDispatcher.EditionConnectionM.SpreadUpdateDuplicatesServer(dataSplit[i]+';'+"1");
                        }
                    }  
                }
            }
            if (duplique && !Program.OnLine)
                Program.edition.marquerModificationDansLaScene();
            //}
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterDeplacement(int x, int y)
        ///
        /// Methode permettant le lancement d'algorithme lors du deplacement de
        /// la souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterDeplacement(int x, int y)
        {
            //if (verifierCurseur(x, y))
            //{
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return;

            bool duplique =false;
            lock (Program.NoyauLock)
            {
                if (Program.OnLine == false) //hors ligne
                {
                    FonctionsNatives.supprimerNoeudsDupliques();
                    duplique = FonctionsNatives.dupliquerObjetsSelectionnes(x, y, true);
                }
                else if (Program.OnLine) //en ligne
                {
                    duplique = true;
                }
            }
            if (duplique)
                Program.edition.Cursor = Cursors.Default;
            else
                Program.edition.Cursor = Cursors.No;
            //}
         }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool interpreterEchap()
        ///
        /// Methode permettant le lancement d'algorithme lors du clic de la touche
        /// Echap.
        /// 
        /// @return True par defaut.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool interpreterEchap()
        {
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return false;

            lock (Program.NoyauLock)
            {
                FonctionsNatives.supprimerNoeudsDupliques();
            }
            Program.edition.Cursor = Cursors.Default;
            return true;
        }
    }
}
