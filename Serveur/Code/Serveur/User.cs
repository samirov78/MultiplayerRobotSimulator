using Commun;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace Server
{
    public class User
    {
        private static ManualResetEvent sendDone = new ManualResetEvent(false);
        private static ManualResetEvent receiveDone = new ManualResetEvent(false);

        public string ID
        {
            get;
            private set;
        }
        public IPEndPoint EndPoint
        {
            get;
            private set;
        }

        Profile m_profile;

        public List<string> DiscussionGroups;

        public string UserName
        {
            get { return (m_profile == null) ? null : m_profile.username; }
        }

        public string Image
        {
            get { return (m_profile == null) ? null : m_profile.image; }
            set { if(m_profile != null) m_profile.image = value; }
        }

        public string Email
        {
            get { return (m_profile == null) ? null : m_profile.email; }
            set { if (m_profile != null) m_profile.email = value; }
        }

        public string FirstName
        {
            get { return (m_profile == null) ? null : m_profile.firstName; }
        }

        public string LastName
        {
            get { return (m_profile == null) ? null : m_profile.lastName; }
        }

        public bool IsAdmin
        {
            get { return (m_profile == null) ? false : m_profile.isAdmin; }
            set { if (m_profile != null) m_profile.isAdmin = value; }
        }

        public int state
        {
            set;
            get;
        }

        public string Color
        {
            get;
            set;
        }

        public string Fleche
        {
            get;
            set;
        }


        public List <string> SelectedNodesIDs
        {
            get;
            set;
        }

        public string Card 
        {
            get;
            set;
        }
        public bool IsLogged 
        {
            get { return m_profile != null; }
        }

        private LinkedList<string> m_friends;

        public Socket m_socket;

        public User(Socket acceptedSck)
        {
            m_socket = acceptedSck;
            ID = Guid.NewGuid().ToString();
            m_friends = new LinkedList<string>();
            SelectedNodesIDs = new List<string>();
            DiscussionGroups = new List<string>();
        }

        public void SetProfile(Profile profile)
        {
            m_profile = profile;
        }

        public void SaveProfile()
        {
            if ( m_profile != null )
            {
                m_profile.Write();
            }
        }
        /// <summary>
        /// Begin receiving data
        /// </summary>
        public void BeginReceive()
        {
            StateObject state = new StateObject();
            state.workSocket = m_socket;
            try
            {
                m_socket.BeginReceive(state.buffer, 0, 4, 0,
                    new AsyncCallback(ReceiveCallback), state);
                receiveDone.WaitOne();
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception : " + e.ToString());
                Disconnected?.Invoke(this);
            }
        }

        /// <summary>
        /// Callaback for the function BeginReceive
        /// </summary>
        /// <param name="ar">state of the asynchronous receive</param>
        private void ReceiveCallback(IAsyncResult ar)
        {
            try
            {
                StateObject state = (StateObject)ar.AsyncState;
                Socket client = state.workSocket;
                SocketError socketError;
                int bytesRead = client.EndReceive(ar, out socketError);
                if (socketError != SocketError.Success || bytesRead <= 0)
                {
                    Disconnected?.Invoke(this);
                    return;
                }
                if (state.size == -1)
                {
                    state.size = BitConverter.ToInt32(state.buffer, 0);
                    state.message = new byte[state.size];
                    //Array.Copy(state.buffer, 4, state.message, state.index, bytesRead - 4);
                    //state.index = state.index + bytesRead - 4;  
                }
                else
                {
                    Array.Copy(state.buffer, 0, state.message, state.index, bytesRead);
                    state.index = state.index + bytesRead;
                }

                if (state.index >= state.size)
                {
                    receiveDone.Set();
                    BeginReceive();
                    DataReceived(this, Encoding.UTF8.GetString(state.message));
                }
                else
                {
                    client.BeginReceive(state.buffer, 0, Math.Min(state.size - state.index, StateObject.BufferSize), 0, 
                        new AsyncCallback(ReceiveCallback), state);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception : " + e.ToString());
                //Disconnected?.Invoke(this);
            }
        }

        /// <summary>
        /// Send data with a specific basic command and second command
        /// </summary>
        /// <param name="basicCmd">basic command (chat edition connection)</param>
        /// <param name="secCmd"> second command</param>
        /// <param name="args">data sent for this command</param>
        public void Send(int basicCmd, int secCmd, string args = "")
        {
            string cmdString = basicCmd.ToString() + Utility.CommandSeperator + secCmd.ToString();

            if (args != "")
            {
                cmdString += Utility.CommandSeperator + args;
            }
            Console.WriteLine("Server I'll send: ({0})", cmdString);
            Send(cmdString);
        }

        /// <summary>
        /// Send data as a string
        /// </summary>
        /// <param name="data">data to send</param>
        private void Send(String data)
        {
            byte[] byteData = Encoding.UTF8.GetBytes(data);
            Send(byteData);
        }

        /// <summary>
        /// Send raw data (byta data)
        /// </summary>
        /// <param name="data">data to send</param>
        private void Send(byte[] data)
        {
            byte[] toSend = Utility.Combine(BitConverter.GetBytes(data.Length), data);
            try
            {
                m_socket.BeginSend(toSend, 0, toSend.Length, SocketFlags.None,
                    new AsyncCallback(SendCallback), m_socket);
                sendDone.WaitOne();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                Disconnected?.Invoke(this);
            }
        }

        private void SendCallback(IAsyncResult ar)
        {
            try
            {
                Socket handler = (Socket)ar.AsyncState;
                SocketError socketError;
                int bytesSent = handler.EndSend(ar, out socketError);
                if (socketError != SocketError.Success)
                {
                    Disconnected?.Invoke(this);
                    return;
                }
                sendDone.Set();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                Disconnected?.Invoke(this);
            }
        }

        /// <summary>
        /// close the connection of this client
        /// </summary>
        public void Close()
        {
            if (m_socket != null && m_socket.Connected)
            {
                m_socket.Close();
                m_socket.Dispose();
            }
        }

        public event DataReceivedHandler DataReceived;
        public event ClientDisconnectedHandler Disconnected;

        public delegate void DataReceivedHandler(User sender, string data);
        public delegate void ClientDisconnectedHandler(User sender);
    }

    // State object for reading client data asynchronously  
    public class StateObject
    {
        public Socket workSocket = null;
        public const int BufferSize = 8192;
        public int size = -1;
        public byte[] buffer = new byte[BufferSize];
        public byte[] message;
        public int index = 0;
    }
}
