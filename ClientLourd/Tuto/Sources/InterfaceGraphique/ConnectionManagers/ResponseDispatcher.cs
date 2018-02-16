using Commun;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Client
{
    class ResponseDispatcher
    {
        //public event NewUserConnectedHandler NewUserConnected;
        //public event UserDisconnectedHandler UserDisconnected;
        //public event LoggedInHandler LoggedIn;
        //public event LoggedOutHandler LoggedOut;
        //public event AlreadyLoggedInHandler AlreadyLoggedIn;
        //public event ConnectionFailedHandler ConnectionFailed;
        //public event ConnectedUsersHandler HandleConnectedUsers;
        //public event DisconnectedHandler Disconnected;

        //public delegate void LoggedInHandler(string username);
        //public delegate void LoggedOutHandler(string username);
        //public delegate void AlreadyLoggedInHandler();
        //public delegate void NewUserConnectedHandler(string username);
        //public delegate void UserDisconnectedHandler(string username);
        //public delegate void DisconnectedHandler(string username);
        //public delegate void ConnectionFailedHandler(string cause);
        //public delegate void ConnectedUsersHandler(string[] users);

        //public List<string> ConnectedUsers;

        private Connection m_connection;

        public ChatConnectionManager ChatConnectionM;
        public ConnectionManager ConnectionM;
        public EditionConnectionManager EditionConnectionM;
        public SimulationConnectionManager SimulationConnectionM;
        public ConfigurationConnectionManager ConfigurationConnectionM;

        public ResponseDispatcher(Connection connection)
        {
            m_connection = connection;
            m_connection.DataReceived += HandleReceivedData;

            ChatConnectionM = new ChatConnectionManager(m_connection);
            ConnectionM = new ConnectionManager(m_connection);
            EditionConnectionM = new EditionConnectionManager(m_connection);
            SimulationConnectionM = new SimulationConnectionManager(m_connection);
            ConfigurationConnectionM = new ConfigurationConnectionManager(m_connection);
        }
        
        

        public void HandleReceivedData(string receivedData)
        {
            Console.WriteLine("Client I've received : (" + receivedData + ")");

            string data = Utility.GetData(receivedData);
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.BasicCommand.Connection:
                    ConnectionM.HandleReceivedData(data);
                    break;
                case (int)Utility.BasicCommand.Chat:
                    ChatConnectionM.HandleReceivedData(data);
                    break;
                case (int)Utility.BasicCommand.Edition:
                    EditionConnectionM.HandleReceivedData(data);
                    break;
                case (int)Utility.BasicCommand.Simulation:
                    SimulationConnectionM.HandleReceivedData(data);
                    break;
                case (int)Utility.BasicCommand.Configuration:
                    ConfigurationConnectionM.HandleReceivedData(data);
                    break;
                default:
                    break;
            }
        }
    }
}
