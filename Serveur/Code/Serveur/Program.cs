using System;
using System.Diagnostics;
using System.IO;

namespace Server
{
    class Program
    {
        static public Listener s_listener;
        static public CommandDispatcher CmdDispatcher;
        static public int s_port = 5001;

        public const string CardsDirectory = "Cards";
        public const string DBDirectory = "DB";
        public const string ProfilesDirectory = DBDirectory + "/Profiles";
        
        static void Main(string[] args)
        {
            if (!Directory.Exists(CardsDirectory))
            {
                Directory.CreateDirectory(CardsDirectory);
            }
            if (!Directory.Exists(DBDirectory))
            {
                Directory.CreateDirectory(DBDirectory);
            }
            if (Directory.Exists(DBDirectory) && !Directory.Exists(ProfilesDirectory))
            {
                Directory.CreateDirectory(ProfilesDirectory);
            }

            Process.GetCurrentProcess().Exited += Program_Exited;
            CmdDispatcher = new CommandDispatcher();
            s_listener = new Listener(s_port);
            s_listener.SocketAccepted += SocketAccepted;
            s_listener.Start();
            Console.WriteLine("Listening");            
            System.Diagnostics.Process.GetCurrentProcess().WaitForExit();
        }

        static void SocketAccepted(object sender, SocketAcceptedEventHandler e)
        {
            Console.WriteLine("Nouvelle connexion : {0}\n{1}\n==============================", e.Accepted.RemoteEndPoint, DateTime.Now);

            User newUser = new User(e.Accepted);
            CmdDispatcher.AddUser(newUser);
            newUser.BeginReceive();
        }

        private static void Program_Exited(object sender, EventArgs e)
        {
            Environment.Exit(0);
        }
    }
}
