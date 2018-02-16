using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    /**
     * Classe des constantes representant les elements du fichiers de configuration
     * @author Abdellatif
     */
    public static partial class ElementXML {
        public const string CONSOLE = "console";
        public const string COMPORTEMENT = "changement-comportement";
        public const string ECLAIRAGE = "activation-desactivation-eclairage";
        public const string EFFETS = "alteration-effets-visuels";
        public const string CAPTEURS = "identification-zones-capteurs";
        public const string VALEUR = "valeur";
    };
        
    
    /**
     * Classe representants les données de configuration de debougage
     * @author Abdellatif
     */
    class ConfigurationDebougage
    {
        // affichage sur console        
        private bool _console;
        // affichage du changement de comportement sur console
        private bool _changementComportement;
        // Affichage de l'activation et desactivation de l'eclairage sur console
        private bool _activationDesactivationEclairage;
        // Alteration des effets visuels
	    private bool _alterationEffetsVisuels;
        // Identification des zones de capteurs de distance
        private bool _identificationZonesCapteurs;

        /**
        * setter et getter de l'attribut _console
        * @author Abdellatif
        */
        public bool console
        {
            get { return _console; }
            set {
                if (_console != value)
                {
                    _console = value;
                    changerAttribut(ElementXML.CONSOLE, ElementXML.VALEUR, value);
                }
            }
        }

        /**
        * setter et getter de l'attribut _changementComportement
        * @author Abdellatif
        */
        public bool changementComportement
        {
            get { return _changementComportement; }
            set {
                if (_changementComportement != value)
                {
                    _changementComportement = value;
                    changerAttribut(ElementXML.CONSOLE, ElementXML.COMPORTEMENT, value);
                }
            }
        }

        /**
        * setter et getter de l'attribut _activationDesactivationEclairage
        * @author Abdellatif
        */
        public bool activationDesactivationEclairage
        {
            get { return _activationDesactivationEclairage; }
            set { 
                if (_activationDesactivationEclairage != value)
                {
                    _activationDesactivationEclairage = value;
                    changerAttribut(ElementXML.CONSOLE, ElementXML.ECLAIRAGE, value);
                }
            }
        }

        /**
        * setter et getter de l'attribut _alterationEffetsVisuels
        * @author Abdellatif
        */
        public bool alterationEffetsVisuels
        {
            get { return _alterationEffetsVisuels; }
            set {
                if (_alterationEffetsVisuels != value)
                {
                    _alterationEffetsVisuels = value;
                    changerAttribut(ElementXML.EFFETS, ElementXML.VALEUR, value);
                }
            }
        }

        /**
        * setter et getter de l'attribut _identificationZonesCapteurs
        * @author Abdellatif
        */
        public bool identificationZonesCapteurs
        {
            get { return _identificationZonesCapteurs; }
            set {
                if (_identificationZonesCapteurs != value)
                {
                    _identificationZonesCapteurs = value;
                    changerAttribut(ElementXML.EFFETS, ElementXML.CAPTEURS, value);
                }
            }
        }
        
        /**
         * Change un attribut d'un certain element XML dans le fichier configuration.xml
         * @author Abdellatif
         */
        void changerAttribut(String element, String attribut, bool value)
        {
            System.Xml.XmlDocument document = new System.Xml.XmlDocument();
            document.Load("données/configuration.xml");
            System.Xml.XmlNodeList nodeList = document.SelectNodes("//" + element);
            foreach (System.Xml.XmlNode node in nodeList)
            {
                if ( node.Attributes[attribut] != null)
                    node.Attributes[attribut].Value = transformerVersChaine(value);
            }
            
            System.Xml.XmlTextWriter writer = new System.Xml.XmlTextWriter("données/configuration.xml", Encoding.UTF8);
            writer.Formatting = System.Xml.Formatting.Indented;
            document.WriteTo(writer);
            writer.Close();
        }

        /**
         * transforme un boolean a une chaine de caractere oui ou non
         * @author Abdellatif
         */
        private String transformerVersChaine(bool value)
        {
          if (value)
              return "oui";
          else
              return "non";
        }

        /**
         * transforme une chaine de caractere "oui" ou "non" vers un boolean
         * @author Abdellatif
         */
        private bool transformerVersBoolean(String value)
        {
            if (value == null || !value.ToLower().Equals("oui"))
                return false;
            else
                return true;
        }

        /**
         * Contructeur des parametre de debogage apartir d'un fichier XML
         * @author Abdellatif
         */
        public ConfigurationDebougage(String nomFichier)
        {
            System.Xml.XmlTextReader reader = new System.Xml.XmlTextReader(nomFichier);
            bool consoleTrouve = false;
            bool alterationTrouvee = false;
            while ( reader.Read() && (!consoleTrouve || !alterationTrouvee) )
            {
                reader.MoveToContent();
                if (reader.NodeType == System.Xml.XmlNodeType.Element && reader.Name == ElementXML.CONSOLE)
                {
                    if (reader.GetAttribute(ElementXML.VALEUR) != null)
                        _console = transformerVersBoolean(reader.GetAttribute(ElementXML.VALEUR));
                    if (reader.GetAttribute(ElementXML.COMPORTEMENT) != null)
                        _changementComportement = transformerVersBoolean(reader.GetAttribute(ElementXML.COMPORTEMENT));
                    if (reader.GetAttribute(ElementXML.ECLAIRAGE) != null)
                        _activationDesactivationEclairage = transformerVersBoolean(reader.GetAttribute(ElementXML.ECLAIRAGE));
                    consoleTrouve = true;
                }
                if (reader.NodeType == System.Xml.XmlNodeType.Element && reader.Name == ElementXML.EFFETS)
                {
                    if (reader.GetAttribute(ElementXML.VALEUR) != null)
                        _alterationEffetsVisuels = transformerVersBoolean(reader.GetAttribute(ElementXML.VALEUR));
                    if (reader.GetAttribute(ElementXML.CAPTEURS) != null)
                        _identificationZonesCapteurs = transformerVersBoolean(reader.GetAttribute(ElementXML.CAPTEURS));
                    alterationTrouvee = true;
                }
            }
            reader.Close();
        }
    }
}
