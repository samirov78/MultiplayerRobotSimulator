using Commun;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
    class ConnectionManager
    {
        private String response = String.Empty;
        private Connection m_connection;

        public List<string> LoggedUsers;

        public ConnectionManager(Connection connection)
        {
            m_connection = connection;
            LoggedUsers = new List<string>();
            m_connection.Disconnected += () => LoggedOut?.Invoke(m_connection.UserName);
            WrongIdentification += () => MessageBox.Show
            ("Le nom d'utilisateur Ou le mot de passe est incorrect");
        }

        public void HandleReceivedData(string receivedData)
        {
            string data = Utility.GetData(receivedData);
            string[] splitData = null;
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.ConnectionResponse.LoggedIn:
                    GetLoggedInUsers();
                    splitData = data.Split(Utility.CommandSeperator);
                    m_connection.FirstName = splitData[0];
                    m_connection.LastName = splitData[1];
                    m_connection.IsAdmin = (splitData[2] == "1") ? true : false;
                    m_connection.UserName = m_connection.TempUserName;
                    if (splitData[3] != "")
                        m_connection.Email = splitData[3];
                    if (splitData.Length == 6)
                    {
                        m_connection.Image = "Images/" + splitData[5];
                        File.WriteAllBytes(m_connection.Image, Convert.FromBase64String
                            (Utility.Decode(splitData[4])));
                    }
                    else
                        m_connection.Image = null;
                    m_connection.WriteXML();
                    LoggedIn?.Invoke(splitData[0]);
                    break;
                case (int)Utility.ConnectionResponse.WrongIdentification:
                    WrongIdentification?.Invoke();
                    break;
                case (int)Utility.ConnectionResponse.LoggedOut:
                    lock (LoggedUsers)
                    {
                        LoggedUsers.Clear();
                    }
                    LoggedOut?.Invoke(m_connection.UserName);
                    break;
                case (int)Utility.ConnectionResponse.NewUserLoggedIn:
                    lock (LoggedUsers)
                    {
                        LoggedUsers.Add(data);
                    }
                    NewUserLoggedIn?.Invoke(data);
                    break;
                case (int)Utility.ConnectionResponse.UserLoggedOut:
                    lock (LoggedUsers)
                    {
                        LoggedUsers.Remove(data);
                    }
                    UserLoggedOut?.Invoke(data);
                    break;
                case (int)Utility.ConnectionResponse.AlreadyLoggedIn:
                    AlreadyLoggedIn?.Invoke();
                    break;
                case (int)Utility.ConnectionResponse.LoggedInUsers:
                    splitData = data?.Split(';');
                    LoggedUsers.Clear();
                    if (splitData != null)
                        LoggedUsers = splitData.ToList<string>();
                    NewLoggedInUsersList?.Invoke(splitData);
                    break;
                default:
                    break;
            }
        }

        public void Login(string password)
        {
            string message =  m_connection.TempUserName + ";" + Utility.Encode(password);
            m_connection.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionCommand.LogIn, message);
        }

        public void LogOut()
        {
            m_connection.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionCommand.LogOut);
        }

        public void GetLoggedInUsers()
        {
            m_connection.Send((int)Utility.BasicCommand.Connection, (int)Utility.ConnectionCommand.LoggedInUsers);
        }

        public event LoggedInHandler LoggedIn;
        public event WrongIdentificationHandler WrongIdentification;
        public event AlreadyLoggedInHandler AlreadyLoggedIn;
        public event LoggedOutHandler LoggedOut;
        public event NewUserLoggedInHandler NewUserLoggedIn;
        public event UserLoggedOutHandler UserLoggedOut;
        public event NewLoggedInUsersListHandler NewLoggedInUsersList;

        public delegate void LoggedInHandler(string username);
        public delegate void WrongIdentificationHandler();
        public delegate void AlreadyLoggedInHandler();
        public delegate void LoggedOutHandler(string username);
        public delegate void NewUserLoggedInHandler(string username);
        public delegate void UserLoggedOutHandler(string username);
        public delegate void NewLoggedInUsersListHandler(string [] users);


    }
}
