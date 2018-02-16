using System;
using System.Collections.Generic;
using Commun;
using System.Xml.Serialization;
using System.IO;

namespace Server
{
    public class CommandDispatcher : ICommandManager
    {
        private List<User> m_users;
        public Profiles profiles;
        public CardProfiles cards; 

        public ChatManager ChatM;
        public ConnectionManager ConnectionM;
        public EditionManager EditionM;
        public SimulationManager SimulationM;
        public ConfigurationManager ConfigurationM;

        public CommandDispatcher()
        {
            m_users = new List<User>();
            ChatM = new ChatManager(m_users);
            ConnectionM = new ConnectionManager(m_users);
            EditionM = new EditionManager(m_users);
            SimulationM = new SimulationManager(m_users);
            ConfigurationM = new ConfigurationManager(m_users);
            profiles = Profiles.Read();
            if (profiles == null)
                profiles = new Profiles();
            cards = CardProfiles.Read();
            if (cards == null)
                cards = new CardProfiles();
        }

        public void AddUser(User user)
        {
            Console.WriteLine("ajout d'un utilisateur");
            user.DataReceived += HandleReceivedData;
            user.Disconnected += ConnectionM.Disconnect;
            lock (m_users)
            {
                m_users.Add(user);
            }
        }

        public void HandleReceivedData(User user, string receivedData)
        {
            Console.WriteLine("Réception de: (" + receivedData + ")");

            string data = Utility.GetData(receivedData);
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.BasicCommand.Connection:
                    ConnectionM.HandleReceivedData(user, data);
                    break;
                case (int)Utility.BasicCommand.Chat:
                    if (!user.IsLogged)
                    {
                        user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.NotLogged);
                        return;
                    }
                    ChatM.HandleReceivedData(user, data);
                    break;
                case (int)Utility.BasicCommand.Edition:
                    if (!user.IsLogged)
                    {
                        user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.NotLogged);
                        return;
                    }
                    EditionM.HandleReceivedData(user, data);
                    break;
                case (int)Utility.BasicCommand.Simulation:
                    if (!user.IsLogged)
                    {
                        user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.NotLogged);
                        return;
                    }
                    SimulationM.HandleReceivedData(user, data);
                    break;
                case (int)Utility.BasicCommand.Configuration:
                    /*if (!user.IsLogged)
                    {
                        user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.NotLogged);
                        return;
                    }*/
                    ConfigurationM.HandleReceivedData(user, data);
                    break;
                default:
                    break;
            }
        }

        public void RateCard(string name, int rate)
        {
            CardProfile card = cards.GetProfile(name);
            card.score = (card.votes * card.score + rate) / (card.votes + 1);
            card.votes++;
            cards.Write();
        }
    }

    [XmlRoot("profiles")]
    public class Profiles
    {
        [XmlElement("profile")]
        public List<Profile> profiles = new List<Profile>();

        public Profiles()
        {
        }

        public void Add(Profile profile)
        {
            profiles.Add(profile);
            Write();
        }

        public static Profiles Read()
        {
            Profiles profiles = new Profiles();
            if (File.Exists(Program.ProfilesDirectory + "/profiles.xml"))
            {
                XmlSerializer xs = new XmlSerializer(typeof(Profiles));
                using (StreamReader rd = new StreamReader(Program.ProfilesDirectory + "/profiles.xml"))
                {
                    profiles = xs.Deserialize(rd) as Profiles;
                }
            }
            return profiles;
        }

        public void Write()
        {
            XmlSerializer xs = new XmlSerializer(typeof(Profiles));
            using (StreamWriter stream = new StreamWriter(Program.ProfilesDirectory + "/profiles.xml"))
            {
                XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
                ns.Add("", "");
                xs.Serialize(stream, this, ns);
            }
        }

        public Profile GetProfile(string name)
        {
            return profiles.Find((profile) => profile.username == name);
        }
    }

    [XmlRoot("cards")]
    public class CardProfiles
    {
        [XmlElement("card")]
        public List<CardProfile> cards = new List<CardProfile>();

        public CardProfiles()
        {
        }

        public void Add(CardProfile profile)
        {
            cards.Add(profile);
            Write();
        }

        public static CardProfiles Read()
        {
            CardProfiles profiles = new CardProfiles();
            if (File.Exists(Program.ProfilesDirectory + "/cards.xml"))
            {
                XmlSerializer xs = new XmlSerializer(typeof(CardProfiles));
                using (StreamReader rd = new StreamReader(Program.ProfilesDirectory + "/cards.xml"))
                {
                    profiles = xs.Deserialize(rd) as CardProfiles;
                }
            }
            return profiles;
        }

        public void Write()
        {
            XmlSerializer xs = new XmlSerializer(typeof(CardProfiles));
            using (StreamWriter stream = new StreamWriter(Program.ProfilesDirectory + "/cards.xml"))
            {
                XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
                ns.Add("", "");
                xs.Serialize(stream, this, ns);
            }
        }

        public CardProfile GetProfile(string name)
        {
            return cards.Find((profile) => profile.name == name);
        }

        public void ChangeCardPassword(User user, string name, string password ="")
        {
            CardProfile card = cards.Find((profile) => profile.name == name);
            if (password == "")
            {
                card.password = null;
                card.isPrivate = false;
            }
            else
            {
                if (card.password != password)
                {
                    card.password = password;
                    card.isPrivate = true;
                    Program.CmdDispatcher.EditionM.EjectEditors(user, name);
                }
            }
            Write();
        }

        public void AddModifier(User user)
        {
            CardProfile card = cards.Find((profile) => profile.name == user.Card);
            card.modifiers.Add(user.UserName);
            Write();
        }
    }
}
