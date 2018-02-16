using System;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Xml.Serialization;
using Commun;
using System.Collections.Generic;

namespace Client
{
    public class Connection
    {
        private static ManualResetEvent connectDone = new ManualResetEvent(false);
        private static ManualResetEvent disconnectDone = new ManualResetEvent(false);
        private static ManualResetEvent sendDone = new ManualResetEvent(false);
        private static ManualResetEvent receiveDone = new ManualResetEvent(false);

        string m_username;
        string m_ip;
        int m_port;
        Socket m_socket;
        //private string m_password;

        [XmlIgnore]
        public bool IsLoggedIn
        {
            get;
            set;
        }

        public string IP
        {
            get { return m_ip; }
            set { m_ip = value; }
        }

        public int Port
        {
            get { return m_port; }
            set { m_port = value; }
        }

        [XmlIgnore]
        public string UserName
        {
            get { return m_username; }
            set { m_username = value; }
        }

        /*
        public string Password
        {
            get { return m_password; }
            set { m_password = value; }
        }*/

        public bool IsConnected
        {
            get { return m_socket == null ? false : m_socket.Connected; }
        }

        public Connection()
        {
            m_ip = "";
            m_port = 0;
            m_username = "";
            IsLoggedIn = false;
        }

        public Connection(string ip, int port, string username)
        {
            m_ip = ip;
            m_port = port;
            m_username = username;
            IsLoggedIn = false;
       }

        /// <summary>
        /// Destructor for liberating the socket
        /// </summary>
        ~Connection()
        {
            Close();
        }

        public void Close()
        {
            if (m_socket != null && m_socket.Connected)
            {
                m_socket.Shutdown(SocketShutdown.Both);
                m_socket.Close();
            }
            IsLoggedIn = false;
        }

        /// <summary>
        /// Establish a connection with the server
        /// </summary>
        /// <returns></returns>
        public void ConnectToServer()
        {
            if (IsConnected)
                return;
            if (!Utility.IsValidIp(m_ip))
            {
                ConnectionFailed?.Invoke("IP Invalide");
                return;
            }
            if (!Utility.IsValidPort(m_port))
            {
                ConnectionFailed?.Invoke("Port Invalide (5000-5050)");
                return;
            }
            try
            {
                IPAddress ipA = IPAddress.Parse(m_ip);
                IPEndPoint ipEP = new IPEndPoint(ipA, m_port);
                m_socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                m_socket.BeginConnect(ipEP, new AsyncCallback(ConnectCallback), m_socket);
                connectDone.WaitOne();
            }
            catch (Exception e)
            {
                ConnectionFailed?.Invoke(e.Message);
            }
        }

        private void ConnectCallback(IAsyncResult ar)
        {
            try
            {
                Socket socket = (Socket)ar.AsyncState;
                socket.EndConnect(ar);
                connectDone.Set();
                BeginReceive();
            }
            catch (Exception e)
            {
                ConnectionFailed?.Invoke(e.Message);
                connectDone.Set();
            }
        }

        public void Disconnect()
        {
            if (m_socket != null && m_socket.Connected)
            {
                m_socket.Shutdown(SocketShutdown.Both);
                try
                {
                    m_socket.BeginDisconnect(true, new AsyncCallback(DisconnectCallback), m_socket);
                    disconnectDone.WaitOne();
                }
                catch (Exception e)
                {
                    MessageBox.Show("Exeception : " + e.ToString());
                }
            }
            else
                Disconnected?.Invoke();
        }

        private void DisconnectCallback(IAsyncResult ar)
        {
            Socket client = (Socket)ar.AsyncState;
            client.EndDisconnect(ar);
            Disconnected?.Invoke();
            disconnectDone.Set();
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
                m_socket.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                    new AsyncCallback(ReceiveCallback), state);
                receiveDone.WaitOne();
            }
            catch (Exception e)
            {
                Console.WriteLine("Exeception : " + e.ToString());
                Disconnect();
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
                    Disconnect();
                    return;
                }
                if (state.size == -1)
                {
                    state.size = BitConverter.ToInt32(state.buffer, 0);
                    state.message = new byte[state.size];
                    Array.Copy(state.buffer, 4, state.message, state.index, bytesRead - 4);
                    state.index = state.index + bytesRead - 4;
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
                    DataReceived?.Invoke(Encoding.UTF8.GetString(state.message));
                }
                else
                {
                    client.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                        new AsyncCallback(ReceiveCallback), state);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Exeception : " + e.ToString());
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
            string cmdString = basicCmd.ToString() + ";" + secCmd.ToString();

            if (args != "")
            {
                cmdString += ";" + args;
            }
            Console.WriteLine("Client I'll send: ({0})", cmdString);
            Send(cmdString);
        }

        private void Send(String data)
        {
            byte[] byteData = Encoding.UTF8.GetBytes(data);
            Send(byteData);
        }

        private void Send(byte[] byteData)
        {
            if (!IsConnected)
                ConnectToServer();
            if (IsConnected)
            {
                byte[] toSend = Utility.Combine(BitConverter.GetBytes(byteData.Length), byteData);
                try
                {
                    m_socket.BeginSend(toSend, 0, toSend.Length, 0,
                        new AsyncCallback(SendCallback), m_socket);
                    sendDone.WaitOne();
                }
                catch (Exception e)
                {
                    MessageBox.Show("Exeception : " + e.ToString());
                }
            }
        }

        private void SendCallback(IAsyncResult ar)
        {
            try
            {
                Socket client = (Socket)ar.AsyncState;
                SocketError socketError;
                int bytesSent = client.EndSend(ar, out socketError);
                if (socketError != SocketError.Success)
                {
                    Disconnect();
                    return;
                }
                sendDone.Set();
            }
            catch (Exception e)
            {
                Console.WriteLine("Exeception : " + e.ToString());
            }
        }

        public event ConnectedHandler Connected;
        public event ConnectionFailedHandler ConnectionFailed;
        public event DisconnectedHandler Disconnected;
        public event DataReceivedHandler DataReceived;

        public delegate void ConnectedHandler();
        public delegate void ConnectionFailedHandler(string cause);
        public delegate void DisconnectedHandler();
        public delegate void DataReceivedHandler(string data);
    }

    public class StateObject
    {
        public Socket workSocket = null;
        public const int BufferSize = 256;
        public int size = -1;
        public byte[] buffer = new byte[BufferSize];
        public byte[] message;
        public int index = 0;
    }
}
