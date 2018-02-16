using System;
using System.Collections.Generic;
using System.Linq;
using Commun;
using System.IO;

namespace Server
{
    public class ChatManager : ICommandManager
    {
        private List<User> m_users;
        private List<string> m_inappropriateWords;
        private const string inappropriateWordsFileName = "DB/inappropriate-words.txt";

        private Dictionary<string, List<string>> m_canals;

        public ChatManager(List<User> users)
        {
            m_users = users;
            if (File.Exists(inappropriateWordsFileName))
            {
                string inappropriateWords = File.ReadAllText(inappropriateWordsFileName);
                if (inappropriateWords != "")
                    m_inappropriateWords =  inappropriateWords.Split(Utility.InappropriateWordsSeperator).ToList();
            }
            m_canals = new Dictionary<string, List<string>>();
        }

        public void HandleReceivedData(User sender, string receivedData)
        {
            string data = Utility.GetData(receivedData);
            string[] splitData = null;
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.ChatCommand.SendMessage:
                    //(message; timeStamp; user-destination)
                    if (data != null)
                        splitData = data.Split(Utility.CommandSeperator);
                    List<string> words = new List<string>();
                    string message = splitData[0];
                    bool found = true;
                    while (found)
                    {
                        found = false;
                        for (int i = 0; i < m_inappropriateWords.Count; i++)
                        {
                            //word in the middle
                            int index = message.IndexOf(" " + m_inappropriateWords[i] + " ");
                            if (index < 0)
                            {
                                // word in the end
                                index = message.IndexOf(" " + m_inappropriateWords[i]);
                                if (index + m_inappropriateWords[i].Length + 1 != message.Length)
                                    index = -1;
                                if (index < 0)
                                {
                                    //word in the begining
                                    index = message.IndexOf(m_inappropriateWords[i] + " ");
                                    if (index != 0)
                                        index = -1;
                                    if (index < 0)
                                    {
                                        index = message.IndexOf(m_inappropriateWords[i]);
                                        if (index != 0 || m_inappropriateWords[i].Length != message.Length)
                                            index = -1;
                                    }
                                }
                                else
                                    index += 1;
                            }
                            else
                                index += 1;
                            if (index >= 0)
                            {
                                found = true;
                                message = message.Substring(0, index) + new string('*', m_inappropriateWords[i].Length)
                                    + message.Substring(index + m_inappropriateWords[i].Length, message.Length - index - m_inappropriateWords[i].Length); 
                                words.Add(m_inappropriateWords[i]);
                            }
                        }
                    }
                    SendMessage(sender, message, splitData[1], splitData[2], words);
                    break;
                case (int)Utility.ChatCommand.SendImage:
                    if (data != null)
                    {
                        splitData = data.Split(';');
                        if (splitData != null && splitData.Length == 4)//(imageName;E(image);timeStamp;destination)
                            SendImage(sender, splitData[0], splitData[1], splitData[2], splitData[3]);
                    }
                    break;
                case (int)Utility.ChatCommand.SpreadMessage:
                    //(message; timeStamp; group-destination)
                    if (data != null)
                        splitData = data.Split(Utility.CommandSeperator);
                    if (!m_canals.ContainsKey(splitData[2]))
                        return;
                    List<string> wordsSpread = new List<string>();
                    string messageSpread = splitData[0];
                    bool foundSpread = true;
                    while (foundSpread)
                    {
                        foundSpread = false;
                        for (int i = 0; i < m_inappropriateWords.Count; i++)
                        {
                            //word in the middle
                            int index = messageSpread.IndexOf(" " + m_inappropriateWords[i] + " ");
                            if (index < 0)
                            {
                                // word in the end
                                index = messageSpread.IndexOf(" " + m_inappropriateWords[i]);
                                if (index + m_inappropriateWords[i].Length + 1 != messageSpread.Length)
                                    index = -1;
                                if (index < 0)
                                {
                                    //word in the begining
                                    index = messageSpread.IndexOf(m_inappropriateWords[i] + " ");
                                    if (index != 0)
                                        index = -1;
                                    if (index < 0)
                                    {
                                        index = messageSpread.IndexOf(m_inappropriateWords[i]);
                                        if (index != 0 || m_inappropriateWords[i].Length != messageSpread.Length)
                                            index = -1;
                                    }
                                }
                                else
                                    index += 1;
                            }
                            else
                                index += 1;
                            if (index >= 0)
                            {
                                foundSpread = true;
                                messageSpread = messageSpread.Substring(0, index) + new string('*', m_inappropriateWords[i].Length)
                                    + messageSpread.Substring(index + m_inappropriateWords[i].Length,
                                    messageSpread.Length - index - m_inappropriateWords[i].Length);
                                wordsSpread.Add(m_inappropriateWords[i]);
                            }
                        }
                    }
                    SpreadMessage(sender, messageSpread, splitData[1], splitData[2], wordsSpread);
                    break;
                case (int)Utility.ChatCommand.CreateGroup:
                    string group = CreateGroup(sender, data);
                    sender.DiscussionGroups.Add(group);
                    sender.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.GroupCreated, group);
                    lock (m_users)
                    {
                        foreach (User user in m_users)
                        {
                            if(user.UserName != sender.UserName && user.IsLogged)
                                user.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.NewGroup, group);
                        }
                    }
                    break;
                case (int)Utility.ChatCommand.JoinGroup:
                    if (m_canals.ContainsKey(data))
                    {
                        m_canals[data].Add(sender.UserName);
                        sender.DiscussionGroups.Add(data);
                        sender.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.GroupJoined, data);
                    }
                    break;
                case (int)Utility.ChatCommand.QuitGroup:
                    if (m_canals.ContainsKey(data))
                    {
                        m_canals[data].Remove(sender.UserName);
                        sender.DiscussionGroups.Remove(data);
                        sender.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.NewGroup, data);
                    }
                    break;
                case (int)Utility.ChatCommand.InviteToJoinGroup:
                    splitData = data.Split(Utility.CommandSeperator);
                    if (splitData != null && splitData.Length == 2)
                        InviteToJoinGroup(sender.UserName, splitData[0], splitData[1]);
                    break;
                default:
                    break;
            }
        }

        private void InviteToJoinGroup(string sender, string destination,  string group)
        {
            User userDestination = m_users.Find((el) => el.UserName == destination);
            if (userDestination != null)
            {
                string message = sender + Utility.CommandSeperator + group;
                userDestination.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.InvitationToJoinGroup, message);
            }
        }

        public void QuitDiscussionGroups(User user)
        {
            lock (m_canals)
            {
                foreach (string group in user.DiscussionGroups)
                {
                    if (m_canals.ContainsKey(group))
                        m_canals[group].Remove(user.UserName);
                }
                user.DiscussionGroups.Clear();
            }
        }

        public void SendGroupsList(User user)
        {
            string toSend = String.Join(Utility.CommandSeperator.ToString(), m_canals.Keys.ToArray());
            user.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.GroupsList, toSend);
        }

        public string CreateGroup(User sender, string group)
        {
            string newGroup = group;
            int i = 1;
            while (m_canals.ContainsKey(newGroup))
            {
                newGroup = group + i;
                i++;
            }
            List<string> users = new List<string>();
            users.Add(sender.UserName);
            m_canals.Add(newGroup, users);
            return newGroup;
        }

        private void SendMessage(User sender, string message, string timeStamp, string to, List<string> inappropriate)
        {
            lock (m_users)
            {
                if (to == "")
                {
                    lock (m_users)
                    {
                        foreach (User x in m_users)
                        {
                            string toSand = sender.UserName + ";" + message + ";" + timeStamp + ";" + to;
                            x.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.NewMessage, toSand);
                        }
                    }
                }
                User destination = m_users.Find((el) => el.UserName == to);
                if (destination == null)
                    return;
                if (destination.IsLogged)
                {
                    string toSand = sender.UserName + ";" + message + ";" + timeStamp + ";" + to;
                    destination.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.NewMessage, toSand);
                    sender.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.NewMessage, toSand);
                }
                if (inappropriate.Count != 0)
                {
                    string adminMessage = "Les mots suivants sont intérdits par l'administration : ";
                    for (int i = 0; i < inappropriate.Count - 1; i++)
                        adminMessage += inappropriate[i] + ", ";
                    adminMessage += inappropriate[inappropriate.Count - 1];
                    string toSand = adminMessage + ";" + timeStamp + ";" + to;
                    sender.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.SimpleAdministration, toSand);
                }
            }
        }

        private void SpreadMessage(User sender, string message, string timeStamp, string to, List<string> inappropriate)
        {
            lock (m_users)
            {
                string toSand = sender.UserName + ";" + message + ";" + timeStamp + ";" + to;
                //sender.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.NewSpreadMessage, toSand);
                List<string> users = m_canals[to];
                foreach (string element in users)
                {
                    User destination = m_users.Find((el) => el.UserName == element);
                    if (destination != null && destination.IsLogged)
                    {
                        destination.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.NewSpreadMessage, toSand);
                    }
                }
                if (inappropriate.Count != 0)
                {
                    string adminMessage = "Les mots suivants sont intérdits par l'administration : ";
                    for (int i = 0; i < inappropriate.Count - 1; i++)
                        adminMessage += inappropriate[i] + ", ";
                    adminMessage += inappropriate[inappropriate.Count - 1];
                    string inapp = adminMessage + ";" + timeStamp + ";" + to;
                    sender.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.GroupAdministration, inapp);
                }
            }
        }

        //(imageName;E(image);timeStamp;destination)
        private void SendImage(User sender, string imageName, string image, string timeStamp, string to)
        {
            User user = m_users.Find((el) => el.UserName == to);
            if (user.IsLogged)
            {
                string receipt = imageName + ";" + timeStamp + ";" + to;
                sender.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.ImageSent, receipt);
                string imageToSend = sender.UserName + ";" + imageName + ";" + image + ";" + timeStamp + ";" + to;
                user.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.NewImage, imageToSend);
            }
        }

        public void ForceJoinGroup(User user, string group)
        {
            if (m_canals[group] == null)
                m_canals.Add(group, new List<string>());
            m_canals[group].Add(user.UserName);
            user.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatResponse.ForceJoinGroup, group);
        }

        public void AddInappropriateWord(string word)
        {
            if (m_inappropriateWords == null)
                m_inappropriateWords = new List<string>();
            if (!m_inappropriateWords.Contains(word))
            {
                m_inappropriateWords.Add(word);
                File.WriteAllText(inappropriateWordsFileName, GetInappropriateWords());
            }
        }

        public string GetInappropriateWords()
        {
            string inappropriateWords = "";
            if (m_inappropriateWords.Count <= 0)
                return inappropriateWords;
            for (int i = 0; i < m_inappropriateWords.Count - 1; i++)
                inappropriateWords += m_inappropriateWords[i] + Utility.InappropriateWordsSeperator;
            inappropriateWords += m_inappropriateWords[m_inappropriateWords.Count - 1];
            return inappropriateWords;
        }

        public void RemoveInappropriateWord(string word)
        {
            m_inappropriateWords.Remove(word);
            File.WriteAllText(inappropriateWordsFileName, GetInappropriateWords());
        }
    }
}
