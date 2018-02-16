using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Commun;
using System.Media;

namespace Client
{
    public class ChatConnectionManager
    {
        public event NewMessageReceivedHandler NewMessageReceived;
        public event SpreadMessageReceivedHandler SpreadMessageReceived;
        public event SimpleAdministrationMessageReceivedHandler SimpleAdministrationMessageReceived;
        public event GroupAdministrationMessageReceivedHandler GroupAdministrationMessageReceived;
        public event NewImageReceivedHandler NewImageReceived;
        public event ImageSentHandler ImageSent;
        public event GroupCreatedHandler GroupCreated;
        public event GroupJoinedHandler GroupJoined;
        public event GroupsListReceivedHandler GroupsListReceived;
        public event NewGroupReceivedHandler NewGroupReceived;
        public event InvitationToJoinGroupReceivedHandler InvitationToJoinGroupReceived;
        public event ForceJoinGroupHandler ForceJoinGroup;

        public delegate void NewMessageReceivedHandler(string source, string message, string time, string destination);
        public delegate void SpreadMessageReceivedHandler(string source, string message, string time, string destination);
        public delegate void NewImageReceivedHandler(string source, string imageName, string image,string timeStamp, string destination);
        public delegate void ImageSentHandler(string imageName, string timeStamp, string to);
        public delegate void SimpleAdministrationMessageReceivedHandler(string message, string time, string destination);
        public delegate void GroupAdministrationMessageReceivedHandler(string message, string time, string destination);
        public delegate void GroupCreatedHandler(string group);
        public delegate void GroupJoinedHandler(string group);
        public delegate void GroupsListReceivedHandler(string[] groups);
        public delegate void NewGroupReceivedHandler(string name);
        public delegate void InvitationToJoinGroupReceivedHandler(string from, string group);
        public delegate void ForceJoinGroupHandler(string name);

        Connection m_connection;

        public ChatConnectionManager(Connection connection)
        {
            m_connection = connection;
        }

        ~ChatConnectionManager()
        {
            Dispose();
        }

        public void Dispose()
        {
            ;
        }

        public void HandleReceivedData(string receivedData)
        {
            string data = Utility.GetData(receivedData);
            string[] splitData = null;
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.ChatResponse.NewMessage:
                    //(userName; message; timeStamp; user-destination)
                    if (data != null)
                    {
                        splitData = data.Split(';');
                        if (splitData != null && splitData.Length == 4)
                            NewMessageReceived?.Invoke(splitData[0], Utility.Decode(splitData[1]), splitData[2], splitData[3]);
                    }
                    break;
                case (int)Utility.ChatResponse.NewSpreadMessage:
                    //(userName; message; timeStamp; group-destination)
                    if (data != null)
                    {
                        splitData = data.Split(';');
                        if (splitData != null && splitData.Length == 4)
                            SpreadMessageReceived?.Invoke(splitData[0], Utility.Decode(splitData[1]), splitData[2], splitData[3]);
                    }
                    break;
                case (int)Utility.ChatResponse.NewImage:
                    //(userName; imageName; E(image); timestamp; destination)
                    if (data != null)
                    {
                        splitData = data.Split(';');
                        if (splitData != null && splitData.Length == 5)
                            NewImageReceived?.Invoke(splitData[0], splitData[1], Utility.Decode(splitData[2]), splitData[3], splitData[4]);
                    }
                    break;
                case (int)Utility.ChatResponse.ImageSent:
                    //(imageName; timestamp; destination)
                    if (data != null)
                    {
                        splitData = data.Split(Utility.CommandSeperator);
                        if (splitData != null && splitData.Length == 3)
                            ImageSent?.Invoke(splitData[0], splitData[1], splitData[2]);
                    }
                    break;
                case (int)Utility.ChatResponse.SimpleAdministration:
                    //(message; timeStamp; destination)
                    if (data != null)
                    {
                        splitData = data.Split(Utility.CommandSeperator);
                        if (splitData != null && splitData.Length == 3)
                            SimpleAdministrationMessageReceived?.Invoke(splitData[0], splitData[1], splitData[2]);
                    }
                    break;
                case (int)Utility.ChatResponse.GroupAdministration:
                    //(message; timeStamp; destination)
                    if (data != null)
                    {
                        splitData = data.Split(Utility.CommandSeperator);
                        if (splitData != null && splitData.Length == 3)
                            GroupAdministrationMessageReceived?.Invoke(splitData[0], splitData[1], splitData[2]);
                    }
                    break;
                case (int)Utility.ChatResponse.GroupCreated:
                    GroupCreated?.Invoke(data);
                    break;
                case (int)Utility.ChatResponse.GroupsList:
                    if (data != null)
                    {
                        splitData = data.Split(Utility.CommandSeperator);
                        if (splitData != null)
                        {
                            GroupsListReceived?.Invoke(splitData);
                        }
                    }
                    break;
                case (int)Utility.ChatResponse.GroupJoined:
                    GroupJoined?.Invoke(data);
                    break;
                case (int)Utility.ChatResponse.NewGroup:
                    NewGroupReceived?.Invoke(data);
                    break;
                case (int)Utility.ChatResponse.InvitationToJoinGroup:
                    splitData = data.Split(Utility.CommandSeperator);
                    if (splitData != null && splitData.Length == 2)
                        InvitationToJoinGroupReceived?.Invoke(splitData[0], splitData[1]);
                    break;
                case (int)Utility.ChatResponse.ForceJoinGroup:
                    ForceJoinGroup?.Invoke(data);
                    break;
                default:
                    break;
            }
        }

        public void InviteToJoinGroup(string user, string group)
        {
            string message = user + Utility.CommandSeperator + group;
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.InviteToJoinGroup, message);
        }

        public void SendMessage(string message, string timeStamp, string to)
        {
            message = Utility.Encode(message) + ";" + Utility.Encode(timeStamp) + ";" + to;
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.SendMessage, message);
        }

        public void SpreadMessage(string message, string timeStamp, string to)
        {
            message = Utility.Encode(message) + ";" + Utility.Encode(timeStamp) + ";" + to;
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.SpreadMessage, message);
        }

        public void SendImage(string imageName, byte[] imageBytes, string timeStamp, string to)
        {
            string image = Convert.ToBase64String(imageBytes, 0, imageBytes.Length);
            String message = imageName + ";" + Utility.Encode(image) + ";" + timeStamp + ";" + to ;
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.SendImage, message);
        }

        public void CreateGroup(string name)
        {
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.CreateGroup, name);
        }

        public void JoinGroup(string name)
        {
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.JoinGroup, name);
        }

        public void QuitGroup(string group)
        {
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.QuitGroup, group);
        }
    }
}
