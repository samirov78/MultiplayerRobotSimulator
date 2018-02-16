using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Commun;
using System.IO;
using System.Net.Mail;

namespace Server
{
    public class ConfigurationManager : ICommandManager
    {
        private List<User> m_users;
        
        public ConfigurationManager(List<User> users)
        {
            m_users = users;
        }

        public void HandleReceivedData(User user, string receivedData)
        {
            string data = Utility.GetData(receivedData);
            string[] dataSplit = null;
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.ConfigurationCommand.CreateProfil:
                    ///(user; prenom; nom; E(password); E(courriel); admin ? "1" : "0"; E(adminPassword))
                    dataSplit = data.Split(Utility.CommandSeperator);
                    if (dataSplit[5] == "1" && !Program.CmdDispatcher.ConnectionM.IsRightPassword("admin", Utility.Decode(dataSplit[6])))
                    {
                        user.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationResponse.WrongAdminPassword);
                        return;
                    }
                    else if (Program.CmdDispatcher.ConnectionM.IsAlreadyUsed(dataSplit[0]))
                    {
                        user.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationResponse.NameAlreadyUsed, dataSplit[0]);
                        return;
                    }
                    CreateProfile(dataSplit[0], dataSplit[1], dataSplit[2], Utility.Decode(dataSplit[3]), Utility.Decode(dataSplit[4]),
                        (dataSplit[5] == "1") ? true : false);
                    string toSend = dataSplit[0] + Utility.CommandSeperator + dataSplit[5];
                    user.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationResponse.ProfilCreated, toSend);
                    break;
                case (int)Utility.ConfigurationCommand.ChangeProfileImage:
                    //((E)image, extention)
                    dataSplit = data.Split(Utility.CommandSeperator);
                    string fileName = Program.ProfilesDirectory + "/" + user.UserName + dataSplit[1];
                    File.WriteAllBytes(fileName, Convert.FromBase64String(Utility.Decode(dataSplit[0])));
                    user.Image = fileName;
                    Program.CmdDispatcher.profiles.Write();
                    break;
                case (int)Utility.ConfigurationCommand.ChangeEmail:
                    user.Email = (data == "") ? null : data;
                    Program.CmdDispatcher.profiles.Write();
                    user.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationResponse.EmailChanged, data);
                    break;
                case (int)Utility.ConfigurationCommand.ChangePassword:
                    dataSplit = data.Split(Utility.CommandSeperator);
                    if (!Program.CmdDispatcher.ConnectionM.IsRightPassword(user.UserName, dataSplit[0]))
                        user.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationResponse.WrongOldPassword);
                    else
                    {
                        Program.CmdDispatcher.ConnectionM.ChangePassword(user.UserName, dataSplit[1]);
                        if(user.Email != null && user.Email != "")
                            SendPasswordChanged(user.FirstName, dataSplit[1], user.Email);
                        user.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationResponse.PasswordChanged, dataSplit[1]);
                    }
                    break;
                case (int)Utility.ConfigurationCommand.ChangeProfileType:
                    dataSplit = data.Split(Utility.CommandSeperator);
                    if (dataSplit[0] == "1" && !Program.CmdDispatcher.ConnectionM.IsRightPassword("admin", Utility.Decode(dataSplit[1])))
                    {
                        user.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationResponse.WrongAdminPassword);
                        return;
                    }
                    else
                    {
                        user.IsAdmin = (dataSplit[0] == "1") ? true : false;
                        Program.CmdDispatcher.profiles.Write();
                    }
                    break;
                case (int)Utility.ConfigurationCommand.AddInappropriateWord:
                    Program.CmdDispatcher.ChatM.AddInappropriateWord(data);
                    user.Send((int)Utility.BasicCommand.Configuration,
                        (int)Utility.ConfigurationResponse.InappropriateWordAdded, data);
                    break;
                case (int)Utility.ConfigurationCommand.GetInappropriateWords:
                    user.Send((int)Utility.BasicCommand.Configuration, (int)Utility.ConfigurationResponse.InappropriateWordsList,
                        Program.CmdDispatcher.ChatM.GetInappropriateWords());
                    break;
                case (int)Utility.ConfigurationCommand.RemoveInappropriateWord:
                    Program.CmdDispatcher.ChatM.RemoveInappropriateWord(data);
                    user.Send((int)Utility.BasicCommand.Configuration, 
                        (int)Utility.ConfigurationResponse.InappropriateWordRemoved, data);
                    break;
                case (int)Utility.ConfigurationCommand.GetMyCards:
                    string message = GetCards(user.UserName);
                    user.Send((int)Utility.BasicCommand.Configuration,
                        (int)Utility.ConfigurationResponse.YourCards, message);
                    break;
                case (int)Utility.ConfigurationCommand.ChangeCardPassword:
                    //(name;password)
                    dataSplit = data.Split(Utility.CommandSeperator);
                    ChangeCardPassword(user, dataSplit[0], dataSplit[1]);
                    break;
                default:
                    break;
            }
        }

        private void ChangeCardPassword(User user, string name, string password)
        {
            Program.CmdDispatcher.cards.ChangeCardPassword(user, name, password);
        }

        private string GetCards(string userName)
        {
            string cardsString = "";
            List<CardProfile> profiles = Program.CmdDispatcher.cards.cards;
            if (profiles == null)
                return cardsString;
            profiles = profiles.FindAll((card) => card.creator == userName);
            if (profiles == null)
                return cardsString;
            for (int i = 0; i < profiles.Count - 1; i++)
            {
                cardsString += profiles[i].name + Utility.CommandSeperator + profiles[i].score;
                if (profiles[i].password == null)
                    cardsString += Utility.CommandSeperator + "" + Utility.CommandSeperator;
                else
                    cardsString += Utility.CommandSeperator + profiles[i].password + Utility.CommandSeperator;
            }
            if (profiles.Count - 1 >= 0)
            {
                cardsString += profiles[profiles.Count - 1].name + Utility.CommandSeperator + profiles[profiles.Count - 1].score;
                if (profiles[profiles.Count - 1].password == null)
                    cardsString += Utility.CommandSeperator + "";
                else
                    cardsString += Utility.CommandSeperator + profiles[profiles.Count - 1].password;
            }
            return cardsString;
        }

        private void CreateProfile(string username, string prenom, string nom, string password, string email, bool isAdmin)
        {
            Program.CmdDispatcher.ConnectionM.SaveLoginPassword(username, password);
            if(email != "")
                SendConfirmationEmail(username, password, email, isAdmin?"Administrateur":"Simple Utilisateur");
            Profile profile = new Profile(username,prenom, nom, email, isAdmin);
            Program.CmdDispatcher.profiles.Add(profile);
        }

        private void SendPasswordChanged(string name, string password, string to)
        {
            string subject = "Changement de mot de passe dans WALL-E2";
            string body = "Bonjour " + name + "\n";
            body += "Nous confirmons le changement de mot de passe dans Wall-E2\n";
            body += "Votre nouveau mot de passe est : " + password;
            SendEmail(subject, body, to);
        }

        private void SendConfirmationEmail(string name, string password, string to, string status)
        {
            string subject = "Création d'un profil dans WALL-E2";
            string body = "Bonjour " + name + "\n";
            body += "Nous confirmons la création de profil avec les informations suivantes :\n";
            body += "Identifiant : " + name + "\n";
            body += "Mot de passe : " + password + "\n";
            body += "statut : " + status + "\n";

            SendEmail(subject, body, to);
        }

        private void SendEmail(string subject, string body, string to)
        {
            string from = "projet3poly2017@gmail.com";
            MailMessage message = new MailMessage(from, to);
            message.Subject = subject;
            message.Body = body;
            SmtpClient client = new SmtpClient();
            client.Port = 587;
            client.DeliveryMethod = SmtpDeliveryMethod.Network;
            client.UseDefaultCredentials = false;
            client.EnableSsl = true;
            client.Credentials = new System.Net.NetworkCredential("projet3poly2017@gmail.com", "Projet3Poly?");
            client.Host = "smtp.gmail.com";
            try
            {
                client.Send(message);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception : {0}", ex.ToString());
            }
        }
    }
}

