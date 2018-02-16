using System.IO;
using System.Xml.Serialization;

namespace InterfaceGraphique
{
    public class ConfigurationSon
    {
        public bool messageReceived;
        public bool messageSent;
        public bool imageSent;
        public bool imageReceived;
        public bool logIn;
        public bool logOut;

        public ConfigurationSon()
        {
        }

        public ConfigurationSon(string file)
        {
            ConfigurationSon configurationSon = ConfigurationSon.Read(file);
            if (configurationSon == null)
            {
                configurationSon = new ConfigurationSon();
                configurationSon.Write(file);
            }
            else
            {
                messageReceived = configurationSon.messageReceived;
                messageSent = configurationSon.messageSent;
                imageSent = configurationSon.messageSent;
                imageReceived = configurationSon.imageReceived;
                logIn = configurationSon.logIn;
                logOut = configurationSon.logOut;
            }
        }

        public static ConfigurationSon Read(string nomFichier)
        {
            ConfigurationSon configurationSon = null;
            if (!File.Exists(nomFichier))
                return configurationSon;
            XmlSerializer xs = new XmlSerializer(typeof(ConfigurationSon));
            using (StreamReader rd = new StreamReader(nomFichier))
            {
                configurationSon = xs.Deserialize(rd) as ConfigurationSon;
            }
            return configurationSon;
        }

        public void Write(string nomFichier)
        {
            XmlSerializer xs = new XmlSerializer(typeof(ConfigurationSon));
            using (StreamWriter wd = new StreamWriter(nomFichier))
            {
                XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
                ns.Add("", "");
                xs.Serialize(wd, this, ns);
            }
        }
    }
}
