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
            //si spectateur retourner
            if (Program.OnLine && Program.IsSpectator)
                return;

            if ( curseurValide_ )
            {
                string poteau;
                string id = Guid.NewGuid().ToString();
                lock (Program.NoyauLock)
                {
                    poteau = Marshal.PtrToStringAnsi(FonctionsNatives.ajouterNoeudSimple(NOM_POTEAU, x, y, Program.OnLine, id));
                }
                if (Program.OnLine)
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
            lock (Program.NoyauLock)
            {
                curseurValide_ = FonctionsNatives.verifierCurseurPoteau(x, y);
            }
            return curseurValide_;
        }
    }
}

