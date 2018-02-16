///////////////////////////////////////////////////////////////////////////////
/// @file EtatEdition.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
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
    /// @class EtatEdition
    /// @brief Classe abstraite decrivant les differents etats des objets
    /// pouvant etre present dans la zone de dessin.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    abstract class EtatEdition
    {
        protected static string NOM_LIGNE = "ligne";                   
        protected static string NOM_SEGMENT = "segment";
        protected static string NOM_MUR = "mur";
        protected static string NOM_POTEAU = "poteau";
        protected static string NOM_FLECHE = "fleche";
        protected bool curseurValide_ = false;
        //protected static Keys modificateur_ = Keys.None;
        //enum EtatSouris { SOURIS_HAUT, SOURIS_BAS };
        //private static EtatSouris etatSouris;
        //protected static int xMouseDebut_, yMouseDebut_;

        //protected int xStart_;
        //protected int yStart_;
        //protected int xEnd_;
        //protected int yEnd_;
        //protected bool enTrace_ = false;
        //protected bool activerSuppression_ = false;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public virtual void initialiserDebut(int x, int y)
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
        public virtual void initialiserDebut(int x, int y)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public virtual void interpreterClic(int x, int y, Keys k)
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
        public virtual void interpreterClic(int x, int y, Keys k)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool verifierCursor(int x, int y)
        ///
        /// Methode permettant la verification de la presence ou non du curseur
        /// dans la zone de dessin.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Vrai lorsque le curseur est dans la zone de dessin, faux autrement.
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual bool verifierCurseur(int x, int y)
        {
            bool estEnZoneSimulation;
            lock (Program.NoyauLock)
            {
                estEnZoneSimulation = FonctionsNatives.verifierPositionCurseur(x, y);
            }
            return estEnZoneSimulation;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool verifierCursor(int x, int y)
        ///
        /// Methode permettant le lancement d'algorithmes lors d'un evenement de
        /// relachement d'un bouton de la souris.
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
        public virtual void interpreterDepot(int x, int y, Keys k)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public virtual bool interpreterEchap()
        ///
        /// Methode permettant le lancement d'algorithmes lors de l'appui sur
        /// le bouton Echap.
        /// 
        /// @return La valeur vrai par defaut.
        ///
        ////////////////////////////////////////////////////////////////////////
        public virtual bool interpreterEchap()
        {
            Program.edition.Cursor = Cursors.Default;
            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public virtual void interpreterGlissement(int x, int y)
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
        public virtual void interpreterGlissement(int x, int y)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public virtual void interpreterDeplacement(int x, int y)
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
        public virtual void interpreterDeplacement(int x, int y)
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void updatePos(int x, int y)
        ///
        /// Methode permettant la mise a jour de la position de la souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void updatePos(int x, int y)
        {
            //xMouseDown_ = x;
            //yMouseDown_ = y;
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
        public static extern bool verifierPositionCurseur(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool verifierCurseurPoteau(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool verifierCurseurFinMur(int xDebut, int yDebut, int xFin, int yFin);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool verifierCurseurFinLigne(int xDebut, int yDebut, int xFin, int yFin);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void tracerRectangleElastique(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void terminerRectangleElastique(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerDernierNoeud();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerDerniereLigne();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ajouterNoeudSimple(string nom, int x, int y, bool enligne = false, string id = "");

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ajouterNoeudAvecScale(string nom, int x1, int y1, int x2, int y2, bool estConcret, bool enLigne = false, string id = "");

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void reInitialiserScene();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr selectionObjet(int mouseX, int mouseY, bool selectionUnique);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr deplacerSelection(int xDebut, int yDebut, int xFin, int yFin);
        //deplacerSelNoAction
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr deplacerSelNoAction(int xDebut, int yDebut, int xFin, int yFin);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool dupliquerObjetsSelectionnes(int x, int y, bool estFantome);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerNoeudsDupliques();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool objetsSelectionnesSurLaTable();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserEnTraitement();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserScaleEnTraitement();

        //duplicateSelNoAction
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr duplicateSelNoAction(int x, int y, bool estFantome);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void retournerAuScaleInitiale();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void UpdateMySelNodes(string theIDs);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PivoterselectedNode(string deltaIDs);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PivoterselectedNodes(string deltaIDs);
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getDuplicatedNodesStr();
    }
}
