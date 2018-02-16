///////////////////////////////////////////////////////////////////////////////
/// @file ConfigurationControle.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.ComponentModel;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class ConfigurationControle
    /// @brief Classe correspondant aux touches de controle du robot
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-03-21
    ///////////////////////////////////////////////////////////////////////////
    class ConfigurationControle
    {
        /// touche pour faire avancer le robot
        private Keys _toucheControleAvancer;
        /// touche pour faire reculer le robot
        private Keys _toucheControleReculer;
        /// touche pour faire tourner le robot au sens horaire
        private Keys _toucheControleRotationH;
        /// touche pour faire tourner le robot au sens anti-horaire
        private Keys _toucheControleRotationAH;
        /// touche pour changer le mode manuel/automatique
        private Keys _toucheControleModeMA;


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Keys toucheControleAvancer
        /// 
        /// setter et getter de l'attribut _toucheControleAvancer
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la touche Controle Avancer
        /// 
        /// @return _toucheControleAvancer
        /// 
        ////////////////////////////////////////////////////////////////////////
        public Keys toucheControleAvancer
        {
            get { return _toucheControleAvancer; }
            set { 
                _toucheControleAvancer = value;
                changerAttribut("avancer", value);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Keys toucheControleReculer
        /// 
        /// setter et getter de l'attribut _toucheControleReculer
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la touche Controle Reculer
        /// 
        /// @return _toucheControleReculer
        /// 
        ////////////////////////////////////////////////////////////////////////
        public Keys toucheControleReculer
        {
            get { return _toucheControleReculer; }
            set { 
                _toucheControleReculer = value;
                changerAttribut("reculer", value);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Keys toucheControleRotationH
        /// 
        /// setter et getter de l'attribut _toucheControleRotationH
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la touche Controle Rotation Horaire
        /// 
        /// @return _toucheControleRotationH
        /// 
        ////////////////////////////////////////////////////////////////////////
        public Keys toucheControleRotationH
        {
            get { return _toucheControleRotationH; }
            set { 
                _toucheControleRotationH = value;
                changerAttribut("rotation-horaire", value);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Keys toucheControleRotationAH
        /// 
        /// setter et getter de l'attribut _toucheControleRotationAH
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : la touche Controle Rotation Anti Horaire
        /// 
        /// @return _toucheControleRotationAH
        /// 
        ////////////////////////////////////////////////////////////////////////
        public Keys toucheControleRotationAH
        {
            get { return _toucheControleRotationAH; }
            set { 
                _toucheControleRotationAH = value;
                changerAttribut("rotation-antihoraire", value);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Keys toucheControleModeMA
        /// 
        /// setter et getter de l'attribut _toucheControleModeMA
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] value : le touche de Controle de changement de Mode
        /// 
        /// @return _toucheControleModeMA
        /// 
        ////////////////////////////////////////////////////////////////////////
        public Keys toucheControleModeMA
        {
            get { return _toucheControleModeMA; }
            set { 
                _toucheControleModeMA = value;
                changerAttribut("mode", value);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void changerAttribut(String attribut, Keys value)
        /// 
        /// change la valeur d'un attribut dans la partie controle du fichier de 
        /// configuration par une touche
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] attribut : chaine de caractere representant l'attribut a changer
        /// 
        /// @param[in] value : une touche du clavier a mettre dans l'attribut
        /// 
        /// @return Rien
        /// 
        ////////////////////////////////////////////////////////////////////////
        void changerAttribut(String attribut, Keys value)
        {
            System.Xml.XmlDocument document = new System.Xml.XmlDocument();
            document.Load("données/configuration.xml");
            System.Xml.XmlNodeList nodeList = document.SelectNodes("//controle");
            foreach (System.Xml.XmlNode node in nodeList)
                node.Attributes[attribut].Value = value.ToString();
            System.Xml.XmlTextWriter writer = new System.Xml.XmlTextWriter("données/configuration.xml", Encoding.UTF8);
            writer.Formatting = System.Xml.Formatting.Indented;
            document.WriteTo(writer);
            writer.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ConfigurationControle(String nomFichier)
        /// 
        /// Constructeur qui initialise les données de controle a partir d'un fichier
        /// 
        /// @author INF2990 Eq.11
        /// 
        /// @param[in] nomFichier : le nom de fichier xml a charger
        /// 
        /// @return Rien
        /// 
        ////////////////////////////////////////////////////////////////////////
        public ConfigurationControle(String nomFichier)
        {
            System.Xml.XmlTextReader reader = new System.Xml.XmlTextReader(nomFichier);
            bool controleTrouve = false;
            while (reader.Read() && !controleTrouve)
            {
                reader.MoveToContent();
                if (reader.NodeType == System.Xml.XmlNodeType.Element && reader.Name == "controle")
                {
                    TypeConverter converter = TypeDescriptor.GetConverter(typeof(Keys));
                    String touche = reader.GetAttribute("avancer");
                    _toucheControleAvancer = (Keys)converter.ConvertFromString(touche);

                    touche = reader.GetAttribute("reculer");
                    _toucheControleReculer = (Keys)converter.ConvertFromString(touche);

                    touche = reader.GetAttribute("rotation-horaire");
                    _toucheControleRotationH = (Keys)converter.ConvertFromString(touche);

                    touche = reader.GetAttribute("rotation-antihoraire");
                    _toucheControleRotationAH = (Keys)converter.ConvertFromString(touche);

                    touche = reader.GetAttribute("mode");
                    _toucheControleModeMA = (Keys)converter.ConvertFromString(touche);
                }
            }
            reader.Close();
        }
    }
}
