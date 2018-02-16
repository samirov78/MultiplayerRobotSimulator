///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionZoom.cs
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

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionZoom
    /// @brief Classe decrivant l'etat d'edition de zoom.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionZoom : EtatEdition
    {
        private int xDebut_;
        private int yDebut_;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void initialiserDebut( int x, int y )
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
        public override void initialiserDebut( int x, int y )
        {
            xDebut_ = x;
            yDebut_ = y;
           // FonctionsNatives.tracerRectangleElastique(x, y);
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
            lock (Program.NoyauLock)
            {
                FonctionsNatives.terminerRectangleElastique(x, y);
            }
            double xMin = Math.Min(xDebut_, x);
            double xMax = Math.Max(xDebut_, x);
            double yMin = Math.Min(yDebut_, y);
            double yMax = Math.Max(yDebut_, y);

            double hauteurFenetre = (double)Edition.obtenirHauteur();
            double largeurFenetre = (double)Edition.obtenirLargeur();
            double ratioFenetre = largeurFenetre / hauteurFenetre ;
            
            double largeurRectangle = (double)(xMax - xMin);
            double hauteurRectangle = (double)(yMax - yMin);
            double ratioRectangle = largeurRectangle / hauteurRectangle;
            
            if (k == Keys.None)
            {
                if (ratioRectangle < ratioFenetre)
                {
                    xMin = xMin - (ratioFenetre * hauteurRectangle - largeurRectangle) / 2;
                    xMax = xMax + (ratioFenetre * hauteurRectangle - largeurRectangle) / 2;
                }
                else
                {
                    yMin = yMin - (largeurRectangle / ratioFenetre - hauteurRectangle) / 2;
                    yMax = yMax + (largeurRectangle / ratioFenetre - hauteurRectangle) / 2;
                }
                lock (Program.NoyauLock)
                {
                    FonctionsNatives.zoomInRectangle((int)xMin, (int)xMax, (int)yMin, (int)yMax);
                }
            }
            else
                if (k == Keys.Alt)
                {
                    if (ratioRectangle < ratioFenetre)
                    {
                        yMin = yMin + (hauteurRectangle - largeurRectangle / ratioFenetre ) / 2;
                        yMax = yMax - (hauteurRectangle - largeurRectangle / ratioFenetre) / 2;
                    }
                    else
                    {
                        xMin = xMin + (largeurRectangle - hauteurRectangle * ratioFenetre) / 2;
                        xMax = xMax - (largeurRectangle - hauteurRectangle * ratioFenetre) / 2;
                    }

                    largeurRectangle = xMax - xMin;
                    hauteurRectangle = yMax - yMin;

                    yMin = -yMin * hauteurFenetre / hauteurRectangle;
                    yMax = hauteurFenetre + (hauteurFenetre - yMax) * hauteurFenetre / hauteurRectangle;

                    xMin = -xMin * largeurFenetre / largeurRectangle;
                    xMax = largeurFenetre + (largeurFenetre - xMax) * largeurFenetre / largeurRectangle;

                    lock (Program.NoyauLock)
                    {
                        FonctionsNatives.zoomOutRectangle((int)xMin, (int)xMax, (int)yMin, (int)yMax);
                        //FonctionsNatives.zoomOutRectangle((int)(largeurFenetre / 4), (int)(largeurFenetre * 3 / 4), (int)(hauteurFenetre / 4), (int)(hauteurFenetre * 3 / 4));
                    }
                }
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
            lock (Program.NoyauLock)
            {
                FonctionsNatives.tracerRectangleElastique(x, y);
            }
        }
    }
}
