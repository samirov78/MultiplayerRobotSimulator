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


// pour tutoriel
using System.Drawing;
using Commun;
using InterfaceGraphique.Forms;
using System.Globalization;
using System.Media;
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

            if (Program.edition.tuto == true)

            {
                Program.edition.enregistrerToolStripButton.Enabled = false;
                Program.edition.text1.Location = new Point(284, 100);
                Program.edition.text1.Font = new Font(Program.edition.text1.Font, FontStyle.Bold);
                Program.edition.text1.Text = "Pour effectuer le déplacement de l'objet il faut cliquer le boutton indiqué par la fleche";
                                              
                Program.edition.felche1.Visible = true;
                Program.edition.felche1.Location = new Point(239, 14);
                Program.edition.enregistrerToolStripButton.Enabled = false;

                //Program.edition.supprimerToolStripButton.Enabled = true;
                Program.edition.deplacementToolStripButton.Enabled = true;

                Program.edition.duplicationToolStripButton.Enabled = false;
            }
            string chaine = "";
            bool duplique = false;
            lock (Program.NoyauLock)
            {
                if (Program.edition.OnLine == false) //hors ligne
                {
                    duplique = FonctionsNatives.dupliquerObjetsSelectionnes(x, y, false);
                }
                else if (Program.edition.OnLine)
                {
                    chaine = Marshal.PtrToStringAnsi(FonctionsNatives.duplicateSelNoAction(x, y, false));
                    Program.SDispatcher.EditionConnectionM.SpreadDuplicateSelection(chaine);
                    //pour duplique --->new fonctionNative get FacadeModele::duplique_ 
                }
            }
            if (duplique)
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

            if (Program.edition.tuto == true)

            {
                Program.edition.text1.Text = "vous pouvez déposer l'objet mais il faut faire attention à que l'objet soit dans la table";
                Program.edition.text1.Location = new Point(284, 281);
                //  Program.edition.felche1.Location = new Point(253, 19);
                Program.edition.enregistrerToolStripButton.Enabled = false;
            }



            bool duplique =false;
            lock (Program.NoyauLock)
            {
                if (Program.edition.OnLine == false) //hors ligne
                {
                    FonctionsNatives.supprimerNoeudsDupliques();
                    duplique = FonctionsNatives.dupliquerObjetsSelectionnes(x, y, true);
                }
                else if (Program.edition.OnLine) //en ligne
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
            lock (Program.NoyauLock)
            {
                FonctionsNatives.supprimerNoeudsDupliques();
            }
            Program.edition.Cursor = Cursors.Default;
            return true;
        }
    }
}
