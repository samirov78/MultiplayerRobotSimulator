using Commun;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    class ConfigurationConnectionManager
    {
        Connection m_connection;

        public ConfigurationConnectionManager(Connection connection)
        {
            m_connection = connection;
        }

        public void GetMyCards()
        {
            m_connection.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationCommand.GetMyCards);
        }

        ~ConfigurationConnectionManager()
        {
            Dispose();
        }

        public void GetInappropriateWords()
        {
            m_connection.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationCommand.GetInappropriateWords);
        }

        public void Dispose()
        {
        }

        public void HandleReceivedData(string receivedData)
        {
            string data = Utility.GetData(receivedData);
            string[] splitData = null;
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.ConfigurationResponse.ProfilCreated:
                    splitData = data.Split(Utility.CommandSeperator);
                    ProfilCreated(splitData[0], (splitData[1]=="1") ? true : false);
                    break;
                case (int)Utility.ConfigurationResponse.WrongAdminPassword:
                    WrongAdminPassword?.Invoke();
                    break;
                case (int)Utility.ConfigurationResponse.ProfileImageChanged:
                    ProfileImageChanged?.Invoke();
                    break;
                case (int)Utility.ConfigurationResponse.EmailChanged:
                    m_connection.Email = data;
                    EmailChanged?.Invoke(data);
                    break;
                case (int)Utility.ConfigurationResponse.PasswordChanged:
                    PasswordChanged?.Invoke(data);
                    break;
                case (int)Utility.ConfigurationResponse.ProfileTypeChanged:
                    m_connection.IsAdmin = (data == "1") ? true : false;
                    ProfileTypeChanged?.Invoke(data == "1" ? true : false);
                    break;
                case (int)Utility.ConfigurationResponse.InappropriateWordsList:
                    InappropriateWordsListReceived?.Invoke(data);
                    break;
                case (int)Utility.ConfigurationResponse.InappropriateWordAdded:
                    InappropriateWordAdded?.Invoke(data);
                    break;
                case (int)Utility.ConfigurationResponse.InappropriateWordRemoved:
                    InappropriateWordRemoved?.Invoke(data);
                    break;
                case (int)Utility.ConfigurationResponse.YourCards:
                    splitData = data.Split(Utility.CommandSeperator);
                    List<CardProfile> profiles = new List<CardProfile>();
                    for (int i = 0; i < splitData.Length - 2; i += 3)
                    {
                        CardProfile profile = new CardProfile(splitData[i], float.Parse(splitData[i + 1]), Utility.Decode(splitData[i + 2]));
                        profiles.Add(profile);
                    }
                    MyCardsReceived?.Invoke(profiles);
                    break;
                default:
                    break;
            }
        }

        public void RemoveInappropriateWord(string word)
        {
            m_connection.Send((int)Utility.BasicCommand.Configuration,
                (int)Utility.ConfigurationCommand.RemoveInappropriateWord, word);
        }

        public void AddInappropriateWord(string word)
        {
            m_connection.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationCommand.AddInappropriateWord, word);
        }

        public void CreateProfil(string user, string prenom, string nom, string password, string courriel, bool admin, string adminPassword)
        {
            //(user; prenom; nom; E(password); E(courriel); admin ? "1" : "0"; E(adminPassword))
            string toSend =  user + Utility.CommandSeperator + prenom + Utility.CommandSeperator + nom + Utility.CommandSeperator
                + Utility.Encode(password) + Utility.CommandSeperator + Utility.Encode(courriel) + Utility.CommandSeperator 
                + (admin ? "1" : "0") + Utility.CommandSeperator + Utility.Encode(adminPassword);
            m_connection.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationCommand.CreateProfil, toSend);
        }

        public void ChangeEmail(string email)
        {
            m_connection.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationCommand.ChangeEmail
                ,email);
        }

        public void ChangeProfileImage(string imageFile)
        {
            string image = "";
            string extention = "";
            if (imageFile != null && File.Exists(imageFile))
            {
                byte[] imageBytes = File.ReadAllBytes(imageFile);
                image = Convert.ToBase64String(imageBytes, 0, imageBytes.Length);
                extention = Path.GetExtension(imageFile);
            }
            string toSend = image + Utility.CommandSeperator + extention;
            m_connection.Send((int)Utility.BasicCommand.Configuration, 
                (int)Utility.ConfigurationCommand.ChangeProfileImage, toSend);
        }

        public void ChangeUserType(string admin, string password)
        {
            string toSend = admin + Utility.CommandSeperator + password;
            m_connection.Send((int)Utility.BasicCommand.Configuration,
                (int)Utility.ConfigurationCommand.ChangeProfileType, toSend);
        }

        public void ChangePassword(string oldPassword, string newPassword)
        {
            string toSend = oldPassword + Utility.CommandSeperator + newPassword;
            m_connection.Send((int)Utility.BasicCommand.Configuration,
                (int)Utility.ConfigurationCommand.ChangePassword, toSend);
        }

        public event ProfilCreatedReceivedHandler ProfilCreated;
        public event WrongAdminPasswordHandler WrongAdminPassword;
        public event ProfileImageChangedHandler ProfileImageChanged;
        public event EmailChangedHandler EmailChanged;
        public event PasswordChangedHandler PasswordChanged;
        public event ProfileTypeChangedHandler ProfileTypeChanged;
        public event InappropriateWordsListReceivedHandler InappropriateWordsListReceived;
        public event InappropriateWordAddedHandler InappropriateWordAdded;
        public event InappropriateWordRemovedHandler InappropriateWordRemoved;
        public event MyCardsReceivedHandler MyCardsReceived;

        public delegate void ProfilCreatedReceivedHandler(string username, bool admin);
        public delegate void WrongAdminPasswordHandler();
        public delegate void ProfileImageChangedHandler();
        public delegate void EmailChangedHandler(string email);
        public delegate void PasswordChangedHandler(string password);
        public delegate void ProfileTypeChangedHandler(bool admin);
        public delegate void InappropriateWordsListReceivedHandler(string words);
        public delegate void InappropriateWordAddedHandler(string word);
        public delegate void InappropriateWordRemovedHandler(string word);
        public delegate void MyCardsReceivedHandler(List<CardProfile> cards);
    }

    public class CardProfile
    {
        public string name;
        public string password;
        public float score;

        public CardProfile()
        {
        }

        public CardProfile(string name, float score, string password = "")
        {
            this.name = name;
            this.score = score;
            this.password = password;
        }
    }
}
