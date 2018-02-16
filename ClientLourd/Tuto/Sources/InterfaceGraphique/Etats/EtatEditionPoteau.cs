///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionPoteau.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
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
    /// @class EtatEditionPoteau
    /// @brief Classe decrivant l'etat d'edition d'un poteau
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionPoteau : EtatEdition
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
            if ( curseurValide_ )
            {
                if (Program.edition.tuto == true)

                {
                    Program.edition.enregistrerToolStripButton.Enabled = false;
                    // Program.edition.text2.Location = new Point(194, 31);
                    Program.edition.text1.Visible = true;
                    Program.edition.text2.Visible = false;
                     Program.edition.text1.Location = new Point(284, 100);
                    Program.edition.text1.Text = "Bravo le tutoriel est fini ,appuyer sur quitter maintenant pour commencez a éditer";
                                                 
                    // Program.edition.felche1.Location = new Point(311, 14);
                }

               // Program.edition.rotationToolStripButton.Enabled = false;
               // Program.edition.miseAEchelleToolStripButton.Enabled = true;


                string poteau;
                string id = Guid.NewGuid().ToString();
                lock (Program.NoyauLock)
                {
                    poteau = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudSimple(NOM_POTEAU, x, y, Program.edition.OnLine, id));
                }
                if (Program.edition.OnLine)
                    Program.SDispatcher.EditionConnectionM.SpreadCreateNode(poteau);
                else
                    Program.edition.marquerModificationDansLaScene();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool verifierCurseur(int x, int y)
        ///
        /// Methode permettant la verification de la position du curseur pour
        /// l'edition du poteau
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Vrai lorsque le curseur est dans la bonne position pour editer
        /// un poteau, faux autrement.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool verifierCurseur(int x, int y)
        {

            // tutoriel
            if (Program.edition.tuto == true)

            {
                // Program.edition.text1.Visible = false;
                // Program.edition.text1.Text = "vous pouvez le déposez ";
                // Program.edition.text1.Location = new Point(284, 100);
              
                Program.edition.text1.Font = new Font(Program.edition.text1.Font, FontStyle.Bold);
                Program.edition.enregistrerToolStripButton.Enabled = false;
            }
            lock (Program.NoyauLock)
            {
                curseurValide_ = FonctionsNatives.verifierCurseurPoteau(x, y);
            }
            return curseurValide_;
        }
    }
}

