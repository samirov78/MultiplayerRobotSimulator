///////////////////////////////////////////////////////////////////////////////
/// @file GestionProfils.cs
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
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class GestionProfils
    /// @brief Classe responsable du chargement le gestion et l'enregistrement
    /// sur un fichier xml des profils du robot
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-03-21
    ///////////////////////////////////////////////////////////////////////////
    class GestionProfils
    {
        ///////////////////////////////////////////////////////////////////////////
        /// @class ElementXML
        /// @brief Classe contenant les constantes utilisé dans l'enregistrement du
        /// fichier de profils XML
        ///
        /// @author INF2990 Eq.11
        /// @date 2016-03-21
        ///////////////////////////////////////////////////////////////////////////
        public static partial class ElementXML
        {
            /// PROFILS = "profils";
            public const string PROFILS = "profils";
            /// PROFIL = "profil";
            public const string PROFIL = "profil";
            /// NOM = "nom";
            public const string NOM = "nom";
            /// ACTIF = "actif";
            public const string ACTIF = "actif";
            /// SUIVANT_SUIVI_LIGNE = "suivant-suivi-ligne";
            public const string SUIVANT_SUIVI_LIGNE = "suivant-suivi-ligne";
            /// SUIVANT_BALAYAGE = "suivant-balayage";
            public const string SUIVANT_BALAYAGE = "suivant-balayage";
            /// SUIVANT_BALAYAGE = "suivant-balayage";
            public const string SUIVANT_DEVIATION_DROITE = "suivant-deviation-droite";
            /// ANGLE_DEVIATION_DROITE = "angle-deviation-droite";
            public const string ANGLE_DEVIATION_DROITE = "angle-deviation-droite";
            /// SUIVANT_DEVIATION_GAUCHE = "suivant-deviation-gauche";
            public const string SUIVANT_DEVIATION_GAUCHE = "suivant-deviation-gauche";
            /// ANGLE_DEVIATION_GAUCHE = "angle-deviation-gauche";
            public const string ANGLE_DEVIATION_GAUCHE = "angle-deviation-gauche";
            /// SUIVANT_EVITER_DROITE = "suivant-eviter-droite";
            public const string SUIVANT_EVITER_DROITE = "suivant-eviter-droite";
            /// ANGLE_PIVOTEMENT_DROITE = "angle-pivotement-droite";
            public const string ANGLE_PIVOTEMENT_DROITE = "angle-pivotement-droite";
            /// DUREE_RECUL_DROITE = "duree-recul-droite";
            public const string DUREE_RECUL_DROITE = "duree-recul-droite";
            /// SUIVANT_EVITER_GAUCHE = "suivant-eviter-gauche";
            public const string SUIVANT_EVITER_GAUCHE = "suivant-eviter-gauche";
            /// ANGLE_PIVOTEMENT_GAUCHE = "angle-pivotement-gauche";
            public const string ANGLE_PIVOTEMENT_GAUCHE = "angle-pivotement-gauche";
            /// DUREE_RECUL_GAUCHE = "duree-recul-gauche";
            public const string DUREE_RECUL_GAUCHE = "duree-recul-gauche";
            /// SUIVANT_DANGER_GAUCHE = "suivant-danger-gauche";
            public const string SUIVANT_DANGER_GAUCHE = "suivant-danger-gauche";
            /// SUIVANT_SECURITAIRE_GAUCHE = "suivant-securitaire-gauche";
            public const string SUIVANT_SECURITAIRE_GAUCHE = "suivant-securitaire-gauche";
            /// LONGUEUR_DANGER_GHAUCHE = "longueur-danger-gauche";
            public const string LONGUEUR_DANGER_GHAUCHE = "longueur-danger-gauche";
            /// LONGUEUR_SECURITAIRE_GHAUCHE = "longueur-securitaire-gauche";
            public const string LONGUEUR_SECURITAIRE_GHAUCHE = "longueur-securitaire-gauche";
            /// SUIVANT_DANGER_MILIEU = "suivant-danger-milieu";
            public const string SUIVANT_DANGER_MILIEU = "suivant-danger-milieu";
            /// SUIVANT_SECURITAIRE_MILIEU = "suivant-securitaire-milieu";
            public const string SUIVANT_SECURITAIRE_MILIEU = "suivant-securitaire-milieu";
            /// LONGUEUR_DANGER_MILIEU = "longueur-danger-milieu";
            public const string LONGUEUR_DANGER_MILIEU = "longueur-danger-milieu";
            /// LONGUEUR_SECURITAIRE_MILIEU = "longueur-securitaire-milieu";
            public const string LONGUEUR_SECURITAIRE_MILIEU = "longueur-securitaire-milieu";
            /// SUIVANT_DANGER_DROITE = "suivant-danger-droite";
            public const string SUIVANT_DANGER_DROITE = "suivant-danger-droite";
            /// SUIVANT_SECURITAIRE_DROITE = "suivant-securitaire-droite";
            public const string SUIVANT_SECURITAIRE_DROITE = "suivant-securitaire-droite";
            /// LONGUEUR_DANGER_DROITE = "longueur-danger-droite";
            public const string LONGUEUR_DANGER_DROITE = "longueur-danger-droite";
            /// LONGUEUR_SECURITAIRE_DROITE = "longueur-securitaire-droite";
            public const string LONGUEUR_SECURITAIRE_DROITE = "longueur-securitaire-droite";
            /// CAPTEUR_GAUCHE = "capteur-gauche";
            public const string CAPTEUR_GAUCHE = "capteur-gauche";
            /// CAPTEUR_DROIT = "capteur-droit";
            public const string CAPTEUR_DROIT = "capteur-droit";
            /// 
            public const string CAPTEUR_MILIEU = "capteur-milieu";
            /// SUIVEUR_LIGNE = "suiveur-ligne";
            public const string SUIVEUR_LIGNE = "suiveur-ligne";
        };
        
        /// enumeration des etats de comportement du robot
        public enum ETATS 
        {
            DEFAUT = 0,
            BALAYAGE,
            DEVIATION_DROITE,
            DEVIATION_GAUCHE,
            EVITER_DROITE,
            EVITER_GAUCHE,
            SUIVI_LIGNE
        };

        /// constatnte enregistrant le nom de profil de defaut
        private const string nomProfilDefaut = "defaut";
        /// tableau enregistrant les chaine de caractere corespondant aux 
        /// enumeration des etats du robot
        public static string[] etats = new string[7] 
        { "Défaut", "Balayage sur 180°", "Déviation vers la droite", "Déviation vers la gauche",
          "Eviter par la droite", "Eviter par la gauche", "Suivi de ligne"};

        /// represente le nom du fihchier XML
        private string _nomFichier;
        /// represente la liste de profils enregistre
        private List<string> _profils;
        /// represente le profil actif
        private string _profilActif ;
        /// represente l'etat suivant de l'etats suivant ligne
        private ETATS _suivantSuiviLigne;
        /// represente l'etat suivant de l'etats Balayage
        private ETATS _suivantBalayage;
        /// represente l'etat suivant de l'etats deviation droite    
        private ETATS _suivantDeviationDroite;
        /// represente l'angle de deviation droite
        private float _angleDeviationDroite;
        /// represente l'etat suivant de l'etats deviation gauche
        private ETATS _suivantDeviationGauche;
        /// represente l'angle de deviation gauche
        private float _angleDeviationGauche;
        /// represente l'etat suivant de l'etats suivant eviter droite
        private ETATS _suivantEviterDroite;
        /// represente l'angle de pivotement droite
        private float _anglePivotementDroite;
        /// represente la duree de recule pour eviter droite
        private int _dureeReculDroite;
        /// represente l'etat suivant de l'etats eviter gauche
        private ETATS _suivantEviterGauche;
        /// represente l'angle de pivotement gauche
        private float _anglePivotementGauche;
        /// represente la duree de recul pour eviter gauche
        private int _dureeReculGauche;
        /// represente l'etat suivant la detection d'obstacle dans la zone de danger 
        /// du capteur gauche 
        private ETATS _suivantDangerCapteurG;
        /// represente l'etat suivant la detection d'obstacle dans la zone securitaire 
        /// du capteur gauche 
        private ETATS _suivantSecuritaireCapteurG;
        /// represente la longueur de la zone de danger du capteur gauche
        private float _longueurDangerCapteurG;
        /// represente la longueur de la zone securitaire du capteur gauche
        private float _longueurSecuritaireCapteurG;
        /// represente l'etat suivant la detection d'obstacle dans la zone de danger 
        /// du capteur du milieu 
        private ETATS _suivantDangerCapteurM;
        /// represente l'etat suivant la detection d'obstacle dans la zone de danger 
        /// du capteur du milieu 
        private ETATS _suivantSecuritaireCapteurM;
        /// represente la longueur de la zone de danger du capteur du milieu
        private float _longueurDangerCapteurM;
        /// represente la longueur de la zone securitaire du capteur du milieu
        private float _longueurSecuritaireCapteurM;
        /// represente l'etat suivant la detection d'obstacle dans la zone de danger 
        /// du capteur droit 
        private ETATS _suivantDangerCapteurD;
        /// represente l'etat suivant la detection d'obstacle dans la zone securitaire
        /// du capteur droit 
        private ETATS _suivantSecuritaireCapteurD;
        /// represente la longueur de la zone de danger du capteur droit
        private float _longueurDangerCapteurD;
        /// represente la longueur de la zone securitaire du capteur droit
        private float _longueurSecuritaireCapteurD;
        /// Enregistre si l'affichage du capteur gauche est active
        private bool _capteurGaucheActif;
        /// Enregistre si l'affichage du capteur droit est active
        private bool _capteurDroitActif;
        /// Enregistre si l'affichage du capteur du milieu est active
        private bool _capteurMilieuActif;
        /// Enregistre si le suiveur de ligne est active
        private bool _suiveurLigneActif;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public List<string> profils
        /// 
        /// getter de l'attribut _profils
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @return _profils
        /// 
        ////////////////////////////////////////////////////////////////////////
        public List<string> profils
        {
            get { return _profils; }
        }

         ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public string profilActif
        /// 
        /// setter et getter de l'attribut _profilActif
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _profilActif
        /// 
        /// @return _profilActif
        /// 
        ////////////////////////////////////////////////////////////////////////
        public string profilActif
        {
            get { return _profilActif; }
            set { _profilActif = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantSuiviLigne
        /// 
        /// setter et getter de l'attribut _suivantSuiviLigne
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantSuiviLigne
        /// 
        /// @return _suivantSuiviLigne
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantSuiviLigne
        {
            get { return _suivantSuiviLigne; }
            set { _suivantSuiviLigne = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantBalayage
        /// 
        /// setter et getter de l'attribut _suivantBalayage
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantBalayage
        /// 
        /// @return _suivantBalayage
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantBalayage
        {
            get { return _suivantBalayage; }
            set { _suivantBalayage = value;}
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantDeviationDroite
        /// 
        /// setter et getter de l'attribut _suivantDeviationDroite
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantDeviationDroite
        /// 
        /// @return _suivantDeviationDroite
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantDeviationDroite
        {
            get { return _suivantDeviationDroite; }
            set { _suivantDeviationDroite = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float angleDeviationDroite
        /// 
        /// setter et getter de l'attribut _angleDeviationDroite
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _angleDeviationDroite
        /// 
        /// @return _angleDeviationDroite
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float angleDeviationDroite
        {
            get { return _angleDeviationDroite; }
            set { _angleDeviationDroite = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantDeviationGauche
        /// 
        /// setter et getter de l'attribut _suivantDeviationGauche
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantDeviationGauche
        /// 
        /// @return _suivantDeviationGauche
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantDeviationGauche
        {
            get { return _suivantDeviationGauche; }
            set { _suivantDeviationGauche = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float angleDeviationGauche
        /// 
        /// setter et getter de l'attribut _angleDeviationGauche
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _angleDeviationGauche
        /// 
        /// @return _angleDeviationGauche
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float angleDeviationGauche
        {
            get { return _angleDeviationGauche; }
            set { _angleDeviationGauche = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantEviterDroite
        /// 
        /// setter et getter de l'attribut _suivantEviterDroite
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantEviterDroite
        /// 
        /// @return _suivantEviterDroite
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantEviterDroite
        {
            get { return _suivantEviterDroite; }
            set { _suivantEviterDroite = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float anglePivotementDroite
        /// 
        /// setter et getter de l'attribut _anglePivotementDroite
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _anglePivotementDroite
        /// 
        /// @return _anglePivotementDroite
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float anglePivotementDroite
        {
            get { return _anglePivotementDroite; }
            set { _anglePivotementDroite = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public int dureeReculDroite
        /// 
        /// setter et getter de l'attribut _dureeReculDroite
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _dureeReculDroite
        /// 
        /// @return _dureeReculDroite
        /// 
        ////////////////////////////////////////////////////////////////////////
        public int dureeReculDroite
        {
            get { return _dureeReculDroite; }
            set { _dureeReculDroite = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantEviterGauche
        /// 
        /// setter et getter de l'attribut _suivantEviterGauche
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantEviterGauche
        /// 
        /// @return _suivantEviterGauche
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantEviterGauche
        {
            get { return _suivantEviterGauche; }
            set { _suivantEviterGauche = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float anglePivotementGauche
        /// 
        /// setter et getter de l'attribut _anglePivotementGauche
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _anglePivotementGauche
        /// 
        /// @return _anglePivotementGauche
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float anglePivotementGauche
        {
            get { return _anglePivotementGauche; }
            set {  _anglePivotementGauche = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public int dureeReculGauche
        /// 
        /// setter et getter de l'attribut _dureeReculGauche
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _dureeReculGauche
        /// 
        /// @return _dureeReculGauche
        /// 
        ////////////////////////////////////////////////////////////////////////
        public int dureeReculGauche
        {
            get { return _dureeReculGauche; }
            set { _dureeReculGauche = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantDangerCapteurG
        /// 
        /// setter et getter de l'attribut _suivantDangerCapteurG
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantDangerCapteurG
        /// 
        /// @return _suivantDangerCapteurG
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantDangerCapteurG
        {
            get { return _suivantDangerCapteurG; }
            set { _suivantDangerCapteurG = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantSecuritaireCapteurG
        /// 
        /// setter et getter de l'attribut _suivantSecuritaireCapteurG
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvella valeur de _suivantSecuritaireCapteurG
        /// 
        /// @return _suivantSecuritaireCapteurG
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantSecuritaireCapteurG
        {
            get { return _suivantSecuritaireCapteurG; }
            set { _suivantSecuritaireCapteurG = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float longueurDangerCapteurG
        /// 
        /// setter et getter de l'attribut _longueurDangerCapteurG
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvella valeur de _longueurDangerCapteurG
        /// 
        /// @return _longueurDangerCapteurG
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float longueurDangerCapteurG
        {
            get { return _longueurDangerCapteurG; }
            set { _longueurDangerCapteurG = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float longueurSecuritaireCapteurG
        /// 
        /// setter et getter de l'attribut _longueurSecuritaireCapteurG
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvella valeur de _longueurSecuritaireCapteurG
        /// 
        /// @return _longueurSecuritaireCapteurG
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float longueurSecuritaireCapteurG
        {
            get { return _longueurSecuritaireCapteurG; }
            set { _longueurSecuritaireCapteurG = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantDangerCapteurM
        /// 
        /// setter et getter de l'attribut _suivantDangerCapteurM
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantDangerCapteurM
        /// 
        /// @return _suivantDangerCapteurM
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantDangerCapteurM
        {
            get { return _suivantDangerCapteurM; }
            set { _suivantDangerCapteurM = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantSecuritaireMilieu
        /// 
        /// setter et getter de l'attribut _suivantSecuritaireCapteurM
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantSecuritaireCapteurM
        /// 
        /// @return _suivantSecuritaireCapteurM
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantSecuritaireMilieu
        {
            get { return _suivantSecuritaireCapteurM; }
            set { _suivantSecuritaireCapteurM = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float longueurDangerCapteurM
        /// 
        /// setter et getter de l'attribut _longueurDangerCapteurM
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvella valeur de _longueurDangerCapteurM
        /// 
        /// @return _longueurDangerCapteurM
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float longueurDangerCapteurM
        {
            get { return _longueurDangerCapteurM; }
            set { _longueurDangerCapteurM = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float longueurSecuritaireCapteurM
        /// 
        /// setter et getter de l'attribut _longueurSecuritaireCapteurM
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvella valeur de _longueurSecuritaireCapteurM
        /// 
        /// @return _longueurSecuritaireCapteurM
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float longueurSecuritaireCapteurM
        {
            get { return _longueurSecuritaireCapteurM; }
            set { _longueurSecuritaireCapteurM = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantDangerCapteurD
        /// 
        /// setter et getter de l'attribut _suivantDangerCapteurD
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la nouvelle valeur de _suivantDangerCapteurD
        /// 
        /// @return _suivantDangerCapteurD
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantDangerCapteurD
        {
            get { return _suivantDangerCapteurD; }
            set { _suivantDangerCapteurD = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ETATS suivantSecuritaireCapteurD
        /// 
        /// setter et getter de l'attribut _suivantSecuritaireCapteurD
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : l'etat suivant la detection d'obstacle sur la zone 
        /// Securitaire du Capteur Droit
        /// 
        /// @return _suivantSecuritaireCapteurD
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ETATS suivantSecuritaireCapteurD
        {
            get { return _suivantSecuritaireCapteurD; }
            set { _suivantSecuritaireCapteurD = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float longueurDangerCapteurD
        /// 
        /// setter et getter de l'attribut _longueurDangerCapteurD
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : le longueur de la zone de Danger du Capteur Droit
        /// 
        /// @return _longueurDangerCapteurD
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float longueurDangerCapteurD
        {
            get { return _longueurDangerCapteurD; }
            set { _longueurDangerCapteurD = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public float longueurSecuritaireCapteurD
        /// 
        /// setter et getter de l'attribut _longueurSecuritaireCapteurD
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : le longueur de la zone Securitaire du Capteur Droit
        /// 
        /// @return _longueurSecuritaireCapteurD
        /// 
        ////////////////////////////////////////////////////////////////////////
        public float longueurSecuritaireCapteurD
        {
            get { return _longueurSecuritaireCapteurD; }
            set { _longueurSecuritaireCapteurD = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool capteurGaucheActif
        /// 
        /// setter et getter de l'attribut _capteurGaucheActif
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : boolean indiquant si le capteur Gauche est Actif
        /// 
        /// @return _capteurGaucheActif
        /// 
        ////////////////////////////////////////////////////////////////////////
        public bool capteurGaucheActif
        {
            get { return _capteurGaucheActif; }
            set { _capteurGaucheActif = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool capteurDroitActif
        /// 
        /// setter et getter de l'attribut _capteurDroitActif
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : boolean indiquant si le capteur Droit est Actif
        /// 
        /// @return _capteurDroitActif
        /// 
        ////////////////////////////////////////////////////////////////////////
        public bool capteurDroitActif
        {
            get { return _capteurDroitActif; }
            set { _capteurDroitActif = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool capteurMilieuActif
        /// 
        /// setter et getter de l'attribut _capteurMilieuActif
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : boolean indiquant si le capteur Milieu est Actif
        /// 
        /// @return _capteurMilieuActif
        /// 
        ////////////////////////////////////////////////////////////////////////
        public bool capteurMilieuActif
        {
            get { return _capteurMilieuActif; }
            set { _capteurMilieuActif = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool suiveurLigneActif
        /// 
        /// setter et getter de l'attribut _suiveurLigneActif
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : boolean indiquant si le suiveur de ligne est actif
        /// 
        /// @return _suiveurLigneActif
        /// 
        ////////////////////////////////////////////////////////////////////////
        public bool suiveurLigneActif
        {
            get { return _suiveurLigneActif; }
            set { _suiveurLigneActif = value; }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public GestionProfils(string nomFichier)
        ///
        /// Constructeur qui construit une instance de GestionProfil à partir 
        /// d'un nom de fichier XML
        /// 
        /// @param[in] nomFichier : le nom de fichier XML qui contient les 
        /// informations de profils
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public GestionProfils(string nomFichier)
        {
            _nomFichier = nomFichier;
            System.Xml.XmlTextReader reader = new System.Xml.XmlTextReader(nomFichier);
            _profils = new List<string>();
            while ( reader.Read() )
            {
                reader.MoveToContent();
                if (reader.NodeType == System.Xml.XmlNodeType.Element && reader.Name == "profil")
                    _profils.Add( reader.GetAttribute(ElementXML.NOM) );
            }
            reader.Close();
            chargerProfil(nomProfilDefaut);
        }

        ////////////////////////////////////////////////////////////////////////
        /// 
        /// @fn private ETATS convertirEtatXML(String etat)
        /// 
        /// Convertit une valeur d'etat d'un element XML en chaine de caractere 
        /// vers un etat enum ETATS
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] etat : la valeur de l'etat de l'element XML 
        /// 
        /// @return l'etat enum ETATS
        ////////////////////////////////////////////////////////////////////////
        private ETATS convertirEtatXML(String etat)
        {
            if (etat.Equals("defaut"))
                return ETATS.DEFAUT;
            if (etat.Equals("balayage"))
                return ETATS.BALAYAGE;
            if (etat.Equals("deviation-droite"))
                return ETATS.DEVIATION_DROITE;
            if (etat.Equals("deviation-gauche"))
                return ETATS.DEVIATION_GAUCHE;
            if (etat.Equals("eviter-droite"))
                return ETATS.EVITER_DROITE;
            if (etat.Equals("eviter-gauche"))
                return ETATS.EVITER_GAUCHE;
            if (etat.Equals("suivi-ligne"))
                return ETATS.SUIVI_LIGNE;
            return ETATS.DEFAUT;
        }

        ////////////////////////////////////////////////////////////////////////
        /// 
        /// @fn private string convertirEtatXML(ETATS etat)
        /// 
        /// Convertit un etat en num ETATS vers une valeur d'un element XML sous 
        /// forme d'une chaine de caractere
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] etat : l'etat enum a convertir  
        /// 
        /// @return la valeur de l'element XML
        ////////////////////////////////////////////////////////////////////////
        private string convertirEtatXML(ETATS etat)
        {
            if ( etat == ETATS.SUIVI_LIGNE )
                return "suivi-ligne";
            if ( etat == ETATS.BALAYAGE )
                return "balayage";
            if ( etat == ETATS.DEVIATION_DROITE )
                return  "deviation-droite";
            if ( etat == ETATS.DEVIATION_GAUCHE )
                return "deviation-gauche";
            if ( etat == ETATS.EVITER_DROITE )
                return "eviter-droite";
            if ( etat == ETATS.EVITER_GAUCHE )
                return "eviter-gauche";
            return "defaut";
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn bool convertirActivation(string etat)
        /// 
        /// Convertit l'etat d'activation en chaine de caractere vers un etat 
        /// d'activation boolean
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] etat : l'etat d'activation en chaine de caractere "actif" 
        /// ou "inactif" 
        /// 
        /// @return l'etat d'activation en boolean true ou false
        /// 
        ////////////////////////////////////////////////////////////////////////
        bool convertirActivation(string etat)
        {
            if (etat == null)
            {
                return true;
            }
            if (etat.Equals("actif"))
                return true;
            else
                return false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn string convertirActivation(bool etat)
        /// 
        /// Convertit l'etat d'activation en boolean vers un etat d'activation 
        /// chaine de caractere
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] etat : l'etat d'activation en boolean true ou false
        /// 
        /// @return l'etat d'activation en chaine de caractere "actif" ou "inactif" 
        /// 
        ////////////////////////////////////////////////////////////////////////
        string convertirActivation(bool etat)
        {
            if (etat)
                return "actif";
            else
                return "inactif";
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void chargerProfil(string nomProfil)
        /// 
        /// Charge un profil XML dans l'instance de GestionProfils courante
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] nomProfil : le nom du profil
        /// 
        /// @return Rien
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void chargerProfil(string nomProfil)
        {
            System.Xml.XmlTextReader reader = new System.Xml.XmlTextReader(_nomFichier);
            bool profilTrouve = false;
            while (reader.Read() && !profilTrouve)
            {
                reader.MoveToContent();
                if (reader.NodeType == System.Xml.XmlNodeType.Element && 
                    reader.Name.Equals("profil") && reader.GetAttribute("nom").Equals(nomProfil))
                {
                    profilTrouve = true;
                    _profilActif = nomProfil;
                    _suivantSuiviLigne = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_SUIVI_LIGNE));
                    _suivantBalayage = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_BALAYAGE));
                    _suivantDeviationDroite = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_DEVIATION_DROITE));
                    _angleDeviationDroite = float.Parse(reader.GetAttribute
                        (ElementXML.ANGLE_DEVIATION_DROITE));

                    _suivantDeviationGauche = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_DEVIATION_GAUCHE));
                    _angleDeviationGauche = float.Parse(reader.GetAttribute
                        (ElementXML.ANGLE_DEVIATION_GAUCHE));

                    _suivantEviterDroite = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_EVITER_DROITE));
                    _anglePivotementDroite = float.Parse(reader.GetAttribute
                        (ElementXML.ANGLE_PIVOTEMENT_DROITE));
                    _dureeReculDroite = int.Parse(reader.GetAttribute
                        (ElementXML.DUREE_RECUL_DROITE));

                    _suivantEviterGauche = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_EVITER_GAUCHE));
                    _anglePivotementGauche = float.Parse(reader.GetAttribute
                        (ElementXML.ANGLE_PIVOTEMENT_GAUCHE));
                    _dureeReculGauche = int.Parse(reader.GetAttribute
                        (ElementXML.DUREE_RECUL_GAUCHE));

                    _suivantDangerCapteurG = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_DANGER_GAUCHE));
                    _suivantSecuritaireCapteurG = convertirEtatXML
                        (reader.GetAttribute(ElementXML.SUIVANT_SECURITAIRE_GAUCHE));
                    _longueurDangerCapteurG = float.Parse(reader.GetAttribute
                        (ElementXML.LONGUEUR_DANGER_GHAUCHE));
                    _longueurSecuritaireCapteurG = float.Parse(reader.GetAttribute
                        (ElementXML.LONGUEUR_SECURITAIRE_GHAUCHE));

                    _suivantDangerCapteurM = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_DANGER_MILIEU));
                    _suivantSecuritaireCapteurM = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_SECURITAIRE_MILIEU));
                    _longueurDangerCapteurM = float.Parse(reader.GetAttribute
                        (ElementXML.LONGUEUR_DANGER_MILIEU));
                    _longueurSecuritaireCapteurM = float.Parse(reader.GetAttribute
                        (ElementXML.LONGUEUR_SECURITAIRE_MILIEU));

                    _suivantDangerCapteurD = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_DANGER_DROITE));
                    _suivantSecuritaireCapteurD = convertirEtatXML(reader.GetAttribute
                        (ElementXML.SUIVANT_SECURITAIRE_DROITE));
                    _longueurDangerCapteurD = float.Parse(reader.GetAttribute
                        (ElementXML.LONGUEUR_DANGER_DROITE));
                    _longueurSecuritaireCapteurD = float.Parse(reader.GetAttribute
                        (ElementXML.LONGUEUR_SECURITAIRE_DROITE));

                    _capteurGaucheActif = convertirActivation(reader.GetAttribute
                        (ElementXML.CAPTEUR_GAUCHE));
                    _capteurDroitActif = convertirActivation(reader.GetAttribute
                        (ElementXML.CAPTEUR_DROIT));
                    _capteurMilieuActif = convertirActivation(reader.GetAttribute
                        (ElementXML.CAPTEUR_MILIEU));
                    _suiveurLigneActif = convertirActivation(reader.GetAttribute
                        (ElementXML.SUIVEUR_LIGNE));
                }
            }
            reader.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void changerProfilActif(string attribut, string valeur)
        /// 
        /// Change un attribut XML du noeud du profil courant
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] attribut : l'attribut a changer
        /// @param[in] valeur : la nouvelle valeur de l'attribut a changer
        /// 
        /// @return Rien
        /// 
        ////////////////////////////////////////////////////////////////////////
        void changerProfilActif(string attribut, string valeur)
        {
            System.Xml.XmlDocument document = new System.Xml.XmlDocument();
            document.Load(_nomFichier);
            System.Xml.XmlNodeList nodeList = document.SelectNodes("//profil");
            foreach (System.Xml.XmlNode node in nodeList)
            {
                if (node.Attributes["nom"].Value == _profilActif)
                {
                    node.Attributes[attribut].Value = valeur.ToString();
                    break;
                }
            }
            System.Xml.XmlTextWriter writer = new System.Xml.XmlTextWriter(_nomFichier, Encoding.UTF8);
            writer.Formatting = System.Xml.Formatting.Indented;
            document.WriteTo(writer);
            writer.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public string creerNoeudProfil()
        /// 
        /// Crée une chaine de caractére sous forme d'un noued XML à partir des 
        /// données du profil courant
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @return une chaine de caracteres string sous forme d'un noeud xml
        /// 
        ////////////////////////////////////////////////////////////////////////
        public string creerNoeudProfil()
        {
            string noeud =  "<profil " + ElementXML.NOM + "=\"" + _profilActif + "\" ";
            noeud += ElementXML.SUIVANT_SUIVI_LIGNE + "=\"" + convertirEtatXML(_suivantSuiviLigne) + "\" ";
            noeud += ElementXML.SUIVANT_BALAYAGE + "=\"" + convertirEtatXML(_suivantBalayage) + "\" ";
            noeud += ElementXML.SUIVANT_DEVIATION_DROITE + "=\"" + convertirEtatXML(_suivantDeviationDroite) + "\" ";
            noeud += ElementXML.ANGLE_DEVIATION_DROITE + "=\"" + _angleDeviationDroite + "\" ";
            noeud += ElementXML.SUIVANT_DEVIATION_GAUCHE + "=\"" + convertirEtatXML(_suivantDeviationGauche) + "\" ";
            noeud += ElementXML.ANGLE_DEVIATION_GAUCHE + "=\"" + _angleDeviationGauche + "\" ";
            noeud += ElementXML.SUIVANT_EVITER_DROITE + "=\"" + convertirEtatXML(_suivantEviterDroite) + "\" ";
            noeud += ElementXML.DUREE_RECUL_DROITE + "=\"" + dureeReculDroite + "\" ";
            noeud += ElementXML.ANGLE_PIVOTEMENT_DROITE + "=\"" + _anglePivotementDroite + "\" ";
            noeud += ElementXML.SUIVANT_EVITER_GAUCHE + "=\"" + convertirEtatXML(_suivantEviterGauche) + "\" ";
            noeud += ElementXML.DUREE_RECUL_GAUCHE + "=\"" + _dureeReculGauche + "\" ";
            noeud += ElementXML.ANGLE_PIVOTEMENT_GAUCHE + "=\"" + _anglePivotementGauche + "\" ";

            noeud += ElementXML.SUIVANT_DANGER_GAUCHE + "=\"" + convertirEtatXML(_suivantDangerCapteurG) + "\" ";
            noeud += ElementXML.SUIVANT_SECURITAIRE_GAUCHE + "=\"" + convertirEtatXML(_suivantSecuritaireCapteurG) + "\" ";
            noeud += ElementXML.LONGUEUR_DANGER_GHAUCHE + "=\"" + _longueurDangerCapteurG + "\" ";
            noeud += ElementXML.LONGUEUR_SECURITAIRE_GHAUCHE + "=\"" + _longueurSecuritaireCapteurG + "\" ";

            noeud += ElementXML.SUIVANT_DANGER_DROITE + "=\"" + convertirEtatXML(_suivantDangerCapteurD) + "\" ";
            noeud += ElementXML.SUIVANT_SECURITAIRE_DROITE + "=\"" + convertirEtatXML(_suivantSecuritaireCapteurD) + "\" ";
            noeud += ElementXML.LONGUEUR_DANGER_DROITE + "=\"" + _longueurDangerCapteurD + "\" ";
            noeud += ElementXML.LONGUEUR_SECURITAIRE_DROITE + "=\"" + _longueurSecuritaireCapteurD + "\" ";

            noeud += ElementXML.SUIVANT_DANGER_MILIEU + "=\"" + convertirEtatXML(_suivantDangerCapteurM) + "\" ";
            noeud += ElementXML.SUIVANT_SECURITAIRE_MILIEU + "=\"" + convertirEtatXML(_suivantSecuritaireCapteurM) + "\" ";
            noeud += ElementXML.LONGUEUR_DANGER_MILIEU + "=\"" + _longueurDangerCapteurM + "\" ";
            noeud += ElementXML.LONGUEUR_SECURITAIRE_MILIEU + "=\"" + _longueurSecuritaireCapteurM + "\" ";

            noeud += ElementXML.CAPTEUR_GAUCHE + "=\"" + convertirActivation(_capteurGaucheActif) + "\" ";
            noeud += ElementXML.CAPTEUR_DROIT + "=\"" + convertirActivation(_capteurDroitActif) + "\" ";
            noeud += ElementXML.CAPTEUR_MILIEU + "=\"" + convertirActivation(_capteurMilieuActif) + "\" ";
            noeud += ElementXML.SUIVEUR_LIGNE + "=\"" + convertirActivation(_suiveurLigneActif) + "\"/>";
            return noeud;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void enregistrerProfil()
        /// 
        /// Enregistre le profil courant noued dans le fichier xml courant
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @return Rien
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void enregistrerProfil()
        {
            System.Xml.XmlDocument document = new System.Xml.XmlDocument();
            document.Load(_nomFichier);
            System.Xml.XmlNodeList nodeList = document.SelectNodes("//profil");
            foreach (System.Xml.XmlNode node in nodeList)
            {
                if (node.Attributes["nom"].Value == _profilActif)
                {
                    document.SelectSingleNode("profils").RemoveChild(node);
                    break;
                }
            }
            String chaineNoeud = creerNoeudProfil();
            System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
            doc.LoadXml(chaineNoeud);
            System.Xml.XmlNode nouveauNoeud = doc.DocumentElement;
            System.Xml.XmlNode nodeProfils = document.SelectSingleNode("profils");
            nodeProfils.AppendChild(document.ImportNode(nouveauNoeud, true));
            System.Xml.XmlTextWriter writer = new System.Xml.XmlTextWriter(_nomFichier, Encoding.UTF8);
            writer.Formatting = System.Xml.Formatting.Indented;
            document.WriteTo(writer);
            writer.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void supprimerProfilCourant()
        /// 
        /// Supprime le profil courant
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @return Rien
        /// 
        ////////////////////////////////////////////////////////////////////////
        public void supprimerProfilCourant()
        {
            System.Xml.XmlDocument document = new System.Xml.XmlDocument();
            document.Load(_nomFichier);
            System.Xml.XmlNodeList nodeList = document.SelectNodes("//profil");
            foreach (System.Xml.XmlNode node in nodeList)
            {
                if (node.Attributes["nom"].Value == _profilActif)
                {
                    document.SelectSingleNode("profils").RemoveChild(node);
                    System.Xml.XmlNode nodeProfils = document.SelectSingleNode("profils");
                    if ( nodeProfils.Attributes["actif"].Value ==  _profilActif )
                        nodeProfils.Attributes["actif"].Value = "defaut";
                    break;
                }
            }
            System.Xml.XmlTextWriter writer = new System.Xml.XmlTextWriter(_nomFichier, Encoding.UTF8);
            writer.Formatting = System.Xml.Formatting.Indented;
            document.WriteTo(writer);
            writer.Close();
        }
    }
}
