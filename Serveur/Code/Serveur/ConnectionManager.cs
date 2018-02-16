using Commun;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Serialization;

namespace Server
{
    public class ConnectionManager : ICommandManager
    {
        private List<User> m_users;
        private Dictionary<string, string> m_credentials;
        private const string CredentialsFile = "credentials.xml";

        public ConnectionManager(List<User> users)
        {
            m_users = users;
            XmlSerializer serializer = new XmlSerializer(typeof(LoginPassword[]),
                new XmlRootAttribute() { ElementName = "lps" });
            if (File.Exists((Program.DBDirectory + @"\" + CredentialsFile)))
            {
                using (StreamReader stream = new StreamReader(Program.DBDirectory + @"\" + CredentialsFile))
                {
                    m_credentials = ((LoginPassword[])serializer.Deserialize(stream))
                       .ToDictionary(i => i.login, i => i.password);
                }
            }
            Console.WriteLine("Dictionnary is");
            foreach (KeyValuePair<string, string> entry in m_credentials)
                Console.WriteLine("Login ({0}) password ({1})", entry.Key, entry.Value);
        }

        public bool IsRightPassword(string username, string password)
        {
            if (m_credentials.ContainsKey(username) && m_credentials[username] == password)
                return true;
            return false;
        }

        public void ChangePassword(string username, string password)
        {
            m_credentials[username] = password;

            SaveCredentials();
        }

        public void HandleReceivedData(User client, string receivedData)
        {
            string data = Utility.GetData(receivedData);
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.ConnectionCommand.LogIn:
                    string[] splitData = data.Split(Utility.CommandSeperator);
                    LogIn(client, splitData[0], Utility.Decode(splitData[1]));
                    break;
                case (int)Utility.ConnectionCommand.LogOut:
                    LogOut(client);
                    break;
                case (int)Utility.ConnectionCommand.LoggedInUsers:
                    SendLoggedInUsersList(client);
                    break;
                default:
                    break;
            }
        }

        public bool IsAlreadyUsed(string username)
        {
            if (m_credentials.ContainsKey(username))
                return true;
            else
                return false;
        }

        public void SaveLoginPassword(string username, string password)
        {
            m_credentials.Add(username, password);
            SaveCredentials();
        }

        private void SaveCredentials()
        {
            XmlSerializer serializer = new XmlSerializer(typeof(LoginPassword[]),
                 new XmlRootAttribute() { ElementName = "lps" });
            using (StreamWriter stream = new StreamWriter(Program.DBDirectory + @"\" + CredentialsFile))
            {
                XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
                ns.Add("", "");
                serializer.Serialize(stream, m_credentials.Select
                    (kv => new LoginPassword() { login = kv.Key, password = kv.Value }).ToArray(), ns);
            }
        }

        public void RemoveClient(User client)
        {
            client.Close();
            lock (m_users)
            {
                Program.CmdDispatcher.EditionM.RemoveEditor(client);
                m_users.Remove(client);
            }
        }

        private void LogIn(User user, string name, string password)
        {
            if (user.IsLogged)
            {
                user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.AlreadyLoggedIn, user.UserName);
            }
            else
            {
                if (!m_credentials.ContainsKey(name) || m_credentials[name] != password)
                {
                    user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.WrongIdentification);
                    return;
                }
                bool nameAlreadyLogged = false;
                lock (m_users)
                {
                    var names = m_users.Select(element => element.UserName);
                    if (names.Contains(name))
                    {
                        nameAlreadyLogged = true;
                    }
                }
                if (nameAlreadyLogged)
                {
                    user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.UserNameAlreadyLoggedIn);
                }
                else
                {
                    Profile profile = Program.CmdDispatcher.profiles.GetProfile(name);
                    user.SetProfile(profile);
                    string toSend = user.FirstName + Utility.CommandSeperator + user.LastName + Utility.CommandSeperator 
                        + ((user.IsAdmin) ? "1" : "0") + Utility.CommandSeperator + user.Email;
                    if (user.Image != null)
                    {
                        try
                        {
                            byte[] imageBytes = File.ReadAllBytes(user.Image);
                            string image = Utility.Encode(Convert.ToBase64String(imageBytes, 0, imageBytes.Length));
                            toSend += Utility.CommandSeperator + image + Utility.CommandSeperator + Path.GetFileName(user.Image);
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine("Exception : {0}", e.ToString());
                        }
                        
                    }
                    user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.LoggedIn, toSend);
                    Program.CmdDispatcher.ChatM.SendGroupsList(user);
                    SpreadLoggedIn(user);
                }
            }
        }

        private void SpreadLoggedIn(User sender)
        {
            lock (m_users)
            {
                foreach (User user in m_users)
                {
                    if (user.UserName != sender.UserName && user.IsLogged)
                        user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.NewUserLoggedIn, sender.UserName);
                }
            }
            Console.WriteLine("Spread loggedIn finished");
        }

        private void SpreadLoggedOut(string name)
        {
            lock (m_users)
            {
                foreach (User client in m_users)
                {
                    if (client.IsLogged)
                        client.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.UserLoggedOut, name);
                }
            }
            Console.WriteLine("Spread LoggedOut finished");
        }

        void SendLoggedInUsersList(User user)
        {
            string toSend = "";
            lock (m_users)
            {
                var names = m_users.Select(element => element.UserName).Where(name => (name != user.UserName && name != ""));
                if (names.Count() > 0)
                {
                    for (int i = 0; i < names.Count() - 1; i++)
                        toSend += names.ElementAt(i) + ";";
                    toSend += names.ElementAt(names.Count() - 1);
                }
            }
            user.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.LoggedInUsers, toSend);
        }

        public void LogOut(User sender)
        {
            if (sender.IsLogged)
            {
                string userName = sender.UserName;
                Program.CmdDispatcher.EditionM.RemoveEditor(sender);
                sender.SetProfile(null);
                sender.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionResponse.LoggedOut);
                Program.CmdDispatcher.ChatM.QuitDiscussionGroups(sender);
                SpreadLoggedOut(userName);
                Console.WriteLine("L'utilisateur {0} a ete logged out", sender.UserName);
            }
        }

        public void Disconnect(User sender)
        {
            Program.CmdDispatcher.ChatM.QuitDiscussionGroups(sender);
            Program.CmdDispatcher.EditionM.RemoveEditor(sender);
            string name = sender.UserName;
            RemoveClient(sender);
            SpreadLoggedOut(name);
            Console.WriteLine("L'utilisateur {0} a ete deconecte", sender.UserName);
        }
    }

    public class LoginPassword
    {
        [XmlAttribute]
        public string login;
        [XmlAttribute]
        public string password;

        public LoginPassword()
        {
        }
    }
}
