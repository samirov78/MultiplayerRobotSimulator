using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Commun;
using System.IO;
using System.Xml.Serialization;

namespace Server
{
    public class EditionManager : ICommandManager
    {
        private List<User> m_users;
        //code provisoire pour tester la selection en ligne
        private string[] availabaleColors = new string[4];
        private string[] availableArrows = new string[4];

        object editionLock = new object();

        private Dictionary<string, Card> m_cards;
        public Dictionary<string, List<User>> Editors;
        private string initialscales_;

        private Dictionary<string, string> m_credentials;

        public EditionManager(List<User> users)
        {
            m_users = users;
            m_cards = new Dictionary<string, Card>();
            Editors = new Dictionary<string, List<User>>();
            //code provisoire pour tester la selection en ligne
            availabaleColors[1] = "255:102:0"; //orange
            availabaleColors[0] = "245:245:0";//yellow
            availabaleColors[2] = "0:230:115"; //cold green
            availabaleColors[3] = "0:100:200";//blue

            availableArrows[0] = "Fleche1";
            availableArrows[1] = "Fleche2";
            availableArrows[2] = "Fleche3";
            availableArrows[3] = "Fleche4";
        }

        public void HandleReceivedData(User user, string receivedData)
        {

            for (int i = 0; i < m_users.Count; i++)
            {
                m_users[i].Color = availabaleColors[i]; //Attribuer une couleur
                m_users[i].Fleche = availableArrows[i]; // Attribuer une Fleche
            }
            string data = Utility.GetData(receivedData);
            string[] splitData = null;
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.EditionCommand.SaveCard:
                    //(name; xmlCard; password; online) password = "" pour public / onligne = "1" pour on ligne
                    if (data != null)
                    {
                        splitData = data.Split(Utility.CommandSeperator);
                        if (splitData != null && splitData.Length == 4)
                        {
                            string fileToSave = Program.CardsDirectory + @"\" + splitData[0] + ".xml";
                            File.WriteAllText(fileToSave, splitData[1]);
                            if(splitData[3] == "1")
                                AddCardEditor(user, splitData[0]);
                            user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.CardSaved, 
                                splitData[0] + Utility.CommandSeperator + splitData[3]);
                            CardProfile profile;
                            if (splitData[2] == "")
                                profile = new CardProfile(splitData[0], user.UserName, false);
                            else
                                profile = new CardProfile(splitData[0], user.UserName, true, splitData[2]);
                            Program.CmdDispatcher.cards.Add(profile);
                        }
                    }
                    break;
                case (int)Utility.EditionCommand.GetCard:
                    string cardFile = Program.CardsDirectory + @"\" + data + ".xml";
                    bool response = AddCardEditor(user, data);
                    if (response == true)
                    {
                        string content = File.ReadAllText(cardFile);
                        //string users = UsersString(data);
                        user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.Card, content /*+ ";" + users*/);
                    }
                    else
                    {
                        user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.NoCard, data);
                    }
                    
                    break;
                case (int)Utility.EditionCommand.GetCards:
                    SendCards(user);
                    break;
                case (int)Utility.EditionCommand.Select:
                    SpreadSelectNodes(user, data); //spread selected IDs to all users
                    break;
                case (int)Utility.EditionCommand.Deselect:
                    SpreadDeselectNodes(user); //spread deselected IDs to all users
                    break;
                case (int)Utility.EditionCommand.SelectElastic:
                    SpreadSelectElastic(user, data); //spread deselected IDs to all users
                    break;
                case (int)Utility.EditionCommand.DeleteSelection:
                    SpreadDeleteSelection(user); //spread delete selected IDs to all users except sender
                    break;
                case (int)Utility.EditionCommand.ScaleSelection:
                    SpreadScaleSelection(user, data); //spread delete selected IDs to all users except sender InitScale
                    break;
                case (int)Utility.EditionCommand.InitScale:
                    SpreadInitScaleSelection(user);
                    break;
                case (int)Utility.EditionCommand.InitDeplacement:
                    SpreadInitDeplacement(user);
                    break;
                case (int)Utility.EditionCommand.DeplacerSelection:
                    SpreadMoveSelection(user, data);
                    break;
                case (int)Utility.EditionCommand.DuplicateSelection:
                    SpreadDuplicateSelection(user, data);
                    break;
                case (int)Utility.EditionCommand.RetourToInitialScale:
                    SpreadRetourToInitialScale(user);
                    break;
                case (int)Utility.EditionCommand.UpdateMySelectedNodes:////
                    SpreadUpdateMySelectedNodes(user);
                    break;
                case (int)Utility.EditionCommand.PivoterObjetSelectionne:
                    SpreadPivoterObjetSelectionne(user, data);
                    break;
                case (int)Utility.EditionCommand.PivoterObjetsMultiples:
                    SpreadPivoterObjetsMultiples(user, data);
                    break;
                case (int)Utility.EditionCommand.AnnulerRotation:
                    SpreadAnnulerRotation(user);
                    break;
                case (int)Utility.EditionCommand.UpdateDuplicatesServer:
                    if (data == null)
                        return;
                    splitData = data.Split(Utility.CommandSeperator);
                    if (splitData != null && splitData.Length == 2)
                    {
                        Card card = m_cards[user.Card];
                        lock (card)
                        {
                            if (card != null)
                            {
                                int phantom;
                                if (int.TryParse(splitData[1], out phantom))
                                {
                                    if (phantom == (int)Utility.DrawState.Final)
                                        card.CreateNode(splitData[0]);
                                }
                            }
                        }
                    }
                    break;
                case (int)Utility.EditionCommand.CreateNode:
                    if (data == null)
                        return;
                    splitData = data.Split(Utility.CommandSeperator);
                    if (splitData != null && splitData.Length == 2)
                    {
                        Card card = m_cards[user.Card];
                        lock (card)
                        {
                            if (card != null)
                            {
                                int phantom;
                                if (int.TryParse(splitData[1], out phantom))
                                {
                                    if (phantom == (int)Utility.DrawState.Final)
                                        card.CreateNode(splitData[0]);
                                    SpreadCreateNode(user.UserName, user.Card, splitData[0]);
                                }
                            }
                            Program.CmdDispatcher.cards.AddModifier(user);
                        }
                    }
                    break;
                case (int)Utility.EditionCommand.ModifyNode:
                    if (data == null)
                        return;
                    splitData = data.Split(Utility.CommandSeperator);
                    if (splitData != null && splitData.Length == 2)
                    {
                        Card card = m_cards[user.Card];
                        lock (card)
                        {
                            if (card != null)
                            {
                                int phantom;
                                if (int.TryParse(splitData[1], out phantom))
                                {
                                    if (phantom == (int)Utility.DrawState.Final)
                                        card.ModifyNode(splitData[0]);
                                    SpreadModifyNode(user.UserName, user.Card, splitData[0]);
                                }
                            }
                            Program.CmdDispatcher.cards.AddModifier(user);
                        }
                    }
                    break;
                case (int)Utility.EditionCommand.GetCardRate:
                    splitData = data.Split(Utility.CommandSeperator);
                    if (splitData != null && splitData.Length == 2)
                    {
                        int rate;
                        bool parsed = int.TryParse(splitData[1], out rate);
                        if (parsed)
                            Program.CmdDispatcher.RateCard(splitData[0], rate);
                    }
                    break;
                case (int)Utility.EditionCommand.GetCardInfo:
                    CardProfile cardProfile = Program.CmdDispatcher.cards.GetProfile(data);
                    string message = cardProfile.name + Utility.CommandSeperator + cardProfile.score + Utility.CommandSeperator +
                        cardProfile.votes;
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.CardInfo, message);
                    break;
                case (int)Utility.EditionCommand.SuppDernierNoeud:
                    SpreadSuppDernierNoeud(user,data);
                    break;
                default:
                    break;
            }
        }

        public void EjectEditors(User sender, string name)
        {
            lock (m_users)
            {
                if (Editors.ContainsKey(name))
                {
                    bool senderIsEditor = false;
                    foreach (User user in Editors[name])
                    {
                        if (user != sender)
                        {
                            user.Card = null;
                            user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.EjectEditor);
                        }
                        else
                        {
                            senderIsEditor = true;
                        }
                    }
                    if (!senderIsEditor)
                        Editors.Remove(name);
                    else
                    {
                        Editors[name].Clear();
                        Editors[name].Add(sender);
                    }

                }
            }
        }

        private void SendCards(User user)
        {
            string[] files = Directory.GetFiles(Program.CardsDirectory);
            for (int i = 0; i < files.Length; i++)
            {
                if (Path.GetExtension(files[i]) == ".xml")
                {
                    string xml = File.ReadAllText(files[i]);
                    string name = Path.GetFileNameWithoutExtension(files[i]);
                    CardProfile profile = Program.CmdDispatcher.cards.GetProfile(name);
                    string status = profile.password;
                    string score = profile.score.ToString();
                    //(xml; name; password; score)
                    string message = xml + Utility.CommandSeperator + name + Utility.CommandSeperator + status +
                        Utility.CommandSeperator + score;
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.CardPlus, message);
                }
            }
        }

        private void SpreadModifyNode(string sender, string cardName, string data)
        {
            List<User> editors = Editors[cardName];
            lock (editionLock)
            {
                foreach (User user in editors)
                    if (user.UserName != sender)
                        user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.ModifyNode, data);
            }
        }

        private string UsersString(string card)
        {
            string usersString = "";
            lock (editionLock)
            {
                if (Editors.ContainsKey(card))
                {
                    List<User> users = Editors[card];
                    for (int i = 0; i < users.Count - 1; i++)
                        usersString += users.ElementAt(i).UserName + ";" + users.ElementAt(i).state + ";";
                    usersString += users.ElementAt(users.Count - 1).UserName + ";" + users.ElementAt(users.Count - 1).state;
                }
            }
            return usersString;
        }

        private bool AddCardEditor(User user, string cardName)
        {
            string cardFile = Program.CardsDirectory + @"\" + cardName + ".xml";
            if (!File.Exists(cardFile))
                return false;
            lock (editionLock)
            {
                if (!m_cards.ContainsKey(cardName))
                {
                    Card card = Card.ReadXml(cardFile);
                    m_cards.Add(cardName, card);
                    Editors.Add(cardName, new List<User>());
                    Program.CmdDispatcher.ChatM.CreateGroup(user, "G-" + cardName);
                }
                Editors[cardName].Add(user);
                Program.CmdDispatcher.ChatM.ForceJoinGroup(user, "G-" + cardName);
            }
            user.Card = cardName;
            return true;
        }

        private void SpreadCreateNode(string sender, string cardName, string data)
        {
            List<User> editors = Editors[cardName];
            lock (editionLock)
            {
                foreach (User user in editors)
                    if (user.UserName != sender)
                        user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.CreateNode, data);
            }
        }

        private void SpreadSelectNodes(User sender, string data)
        {
            List<User> editors = Editors[sender.Card];
            if (data.IndexOf(";") == -1) //un seul ID  id == data
            {
                if (IDdejaSelectionne(data, editors, sender) == false)
                {
                    if (sender.SelectedNodesIDs.Contains(data) == false)
                    {
                        sender.SelectedNodesIDs.Clear();
                        sender.SelectedNodesIDs.Add(data);
                    }
                    else if (sender.SelectedNodesIDs.Contains(data))
                    {
                        sender.SelectedNodesIDs.Remove(data);
                    }
                }
            } //end if un seul ID selectionne
            else
            {
                //si data contient plusieurs IDs
                string[] ids = data.Split(';');
                List<string> IDsList = new List<string>(ids);
                //supprimer les selections anterieures
                sender.SelectedNodesIDs.Clear();
                //traiter chaque ID
                foreach (string id in IDsList)
                {

                    if (IDdejaSelectionne(id, editors, sender) == false)
                    {
                        if (sender.SelectedNodesIDs.Contains(id) == false)
                        {
                            sender.SelectedNodesIDs.Add(id);
                        }
                        else if (sender.SelectedNodesIDs.Contains(id))
                        {
                            sender.SelectedNodesIDs.Remove(id);
                        }
                    }
                }
            }
            //former la chaine a envoyer contenant toutes les selections
            broadcastSelections(editors);
        }

        private void SpreadDeselectNodes(User sender) //pour deselect les noeuds localement selectionnes
        {
            List<User> editors = Editors[sender.Card];
            if (sender.SelectedNodesIDs.Count > 0) //if any selected nodes
            {
                sender.SelectedNodesIDs.Clear();
            }
            broadcastSelections(editors);
        }
        
        private void SpreadSuppDernierNoeud(User sender, string data)
        {
            List<User> editors = Editors[sender.Card];
            //diffuser pour les autres editeurs de la carte
            foreach (User user in editors)
            {
                if (user.ID != sender.ID)
                {
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.SuppDernierNoeud, data);
                }
            }

        }


        private void SpreadSelectElastic(User sender, string data)
        {
            List<User> editors = Editors[sender.Card];
            if (data.IndexOf(";") == -1) //un seul ID  id == data
            {
                if (IDdejaSelectionne(data, editors, sender) == false)
                {
                    sender.SelectedNodesIDs.Clear();
                    sender.SelectedNodesIDs.Add(data);
                }
            } //end if un seul ID selectionne
            else
            {
                //si data contient plusieurs IDs
                string[] ids = data.Split(';');
                List<string> IDsList = new List<string>(ids);
                //supprimer les selections anterieures
                sender.SelectedNodesIDs.Clear();
                //traiter chaque ID
                foreach (string id in IDsList)
                {

                    if (IDdejaSelectionne(id, editors, sender) == false)
                    {
                        if (sender.SelectedNodesIDs.Contains(id) == false)
                        {
                            sender.SelectedNodesIDs.Add(id);
                        }
                    }
                }
            }
            //former la chaine a envoyer contenant toutes les selections
            broadcastSelections(editors);
        }

        private void SpreadDeleteSelection(User sender)
        {
            string IDsToDelete = "";
            List<User> editors = Editors[sender.Card];
            bool toModify = false;
            if (sender.SelectedNodesIDs.Count > 0)
            {
                for (int i = 0; i < sender.SelectedNodesIDs.Count - 1; i++)
                {
                    m_cards[sender.Card].RemoveNode(sender.SelectedNodesIDs[i]);
                    IDsToDelete += sender.SelectedNodesIDs[i] + ";";
                }
                m_cards[sender.Card].RemoveNode(sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1]);
                IDsToDelete += sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1];
                toModify = true;
            }
            sender.SelectedNodesIDs.Clear();
            if(toModify)
                Program.CmdDispatcher.cards.AddModifier(sender);
            //diffuser pour les autres editeurs de la carte
            foreach (User user in editors)
            {
                //if (user.ID != sender.ID)
                //{
                user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.DeleteSelection, IDsToDelete);
                //}
            }
            m_cards[sender.Card].Save();
        }
        //SpreadInitScaleSelection
        private void SpreadInitScaleSelection(User sender)
        {
            List<User> editors = Editors[sender.Card];
            //diffuser pour les autres editeurs de la carte
            foreach (User user in editors)
            {
                if (user.ID != sender.ID)
                {
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.InitScaleSel);
                }
            }
        }  //SpreadInitDeplacement

        private void SpreadInitDeplacement(User sender)
        {
            List<User> editors = Editors[sender.Card];
            //diffuser pour les autres editeurs de la carte
            foreach (User user in editors)
            {
                if (user.ID != sender.ID)
                {
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.InitDeplacement);
                }
            }
        }



        private void SpreadScaleSelection(User sender, string data)
        {
            string IDsToScale = "";
            List<User> editors = Editors[sender.Card];
            if (sender.SelectedNodesIDs.Count > 0)
            {

                for (int i = 0; i < sender.SelectedNodesIDs.Count - 1; i++)
                    IDsToScale += sender.SelectedNodesIDs[i] + ";";
                IDsToScale += sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1];

                //diffuser pour les autres editeurs de la carte
                foreach (User user in editors)
                {
                    //if (user.ID != sender.ID)
                    //{
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.ScaleSelection, data + ':' + IDsToScale);
                    //}
                }
                Program.CmdDispatcher.cards.AddModifier(sender);
            }
            m_cards[sender.Card].Save();
        }
        //SpreadMoveSelection
        private void SpreadMoveSelection(User sender, string data)
        {
            string IDsToMove = "";
            List<User> editors = Editors[sender.Card];
            if (sender.SelectedNodesIDs.Count > 0)
            {

                for (int i = 0; i < sender.SelectedNodesIDs.Count - 1; i++)
                    IDsToMove += sender.SelectedNodesIDs[i] + ";";
                IDsToMove += sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1];

                //diffuser pour les autres editeurs de la carte
                foreach (User user in editors)
                {
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.DeplacerSelection, data + ':' + IDsToMove);
                }
                Program.CmdDispatcher.cards.AddModifier(sender);
            }
            m_cards[sender.Card].Save();
        }

        private void SpreadPivoterObjetSelectionne(User sender, string data)
        {
            string IDsToRotate = "";
            List<User> editors = Editors[sender.Card];
            if (sender.SelectedNodesIDs.Count > 0)
            {

                for (int i = 0; i < sender.SelectedNodesIDs.Count - 1; i++)
                    IDsToRotate += sender.SelectedNodesIDs[i] + ";";
                IDsToRotate += sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1];

                //diffuser pour les autres editeurs de la carte
                foreach (User user in editors)
                {
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.PivoterObjetSelectionne, data + ':' + IDsToRotate);
                }
                Program.CmdDispatcher.cards.AddModifier(sender);
            }
            m_cards[sender.Card].Save();
        }
        
        private void SpreadPivoterObjetsMultiples(User sender, string data)
        {
            string IDsToRotate = "";
            List<User> editors = Editors[sender.Card];
            if (sender.SelectedNodesIDs.Count > 0)
            {

                for (int i = 0; i < sender.SelectedNodesIDs.Count - 1; i++)
                    IDsToRotate += sender.SelectedNodesIDs[i] + ";";
                IDsToRotate += sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1];

                //diffuser pour les autres editeurs de la carte
                foreach (User user in editors)
                {
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.PivoterObjetsMultiples, data + ':' + IDsToRotate);
                }
                Program.CmdDispatcher.cards.AddModifier(sender);
            }
            m_cards[sender.Card].Save();
        }



        private void SpreadDuplicateSelection(User sender, string data)
        {
            string IDsToDuplicate = "";
            List<User> editors = Editors[sender.Card];
            if (sender.SelectedNodesIDs.Count > 0)
            {

                for (int i = 0; i < sender.SelectedNodesIDs.Count - 1; i++)
                    IDsToDuplicate += sender.SelectedNodesIDs[i] + ";";
                IDsToDuplicate += sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1];

                //diffuser pour les autres editeurs de la carte
                foreach (User user in editors)
                {
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.DuplicateSelection, data + ':' + IDsToDuplicate);
                }
                Program.CmdDispatcher.cards.AddModifier(sender);
            }
            m_cards[sender.Card].Save();
        }
        //SpreadRetourToInitialScale
        private void SpreadRetourToInitialScale(User sender)
        {
            List<User> editors = Editors[sender.Card];
            foreach (User user in editors)
            {
                user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.RetourToInitialScale);
            }
            m_cards[sender.Card].Save();
        }

        private void SpreadUpdateMySelectedNodes(User sender)
        {
            string theIDs = "";
            List<User> editors = Editors[sender.Card];
            for (int i = 0; i < sender.SelectedNodesIDs.Count - 1; i++)
                theIDs += sender.SelectedNodesIDs[i] + ";";
            if(sender.SelectedNodesIDs.Count - 1 > 0)
                theIDs += sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1];
            Program.CmdDispatcher.cards.AddModifier(sender);
            sender.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.UpdateMySelectedNodes, theIDs);
        }

        private void SpreadAnnulerRotation(User sender)
        {
            string theIDs = "";
            List<User> editors = Editors[sender.Card];
            for (int i = 0; i < sender.SelectedNodesIDs.Count - 1; i++)
                theIDs += sender.SelectedNodesIDs[i] + ";";
            theIDs += sender.SelectedNodesIDs[sender.SelectedNodesIDs.Count - 1];
            foreach (User user in editors)
            {
                user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.AnnulerRotation, theIDs);
            }
            m_cards[sender.Card].Save();
        }

        public bool IDdejaSelectionne(string id, List<User> users, User theUser)
        {
            bool existe = false;
            foreach (User user in users)
            {
                if (user.ID != theUser.ID)
                {
                    if (user.SelectedNodesIDs.Contains(id))
                    { existe = true; }
                }
            }
            return existe;
        }

        public void broadcastSelections(List<User> editeurs)
        {
            string broadcastString = "";
            //former la chaine a envoyer contenant toutes les selections
            foreach (User user in editeurs)
            {
                if (user.SelectedNodesIDs.Count > 0) //si user a des selections
                {
                    for (int i = 0; i < user.SelectedNodesIDs.Count - 1; i++)
                        broadcastString += user.SelectedNodesIDs[i] + ";";
                    broadcastString += user.SelectedNodesIDs[user.SelectedNodesIDs.Count - 1];
                    broadcastString += ";" + user.Color + "@"; //F pour fin: c un separateur des IDs des differents users
                }

            }
            if (broadcastString == "") // si rien n est selectionne pour tous les users
                broadcastString = "d";
            //diffuser a tous les users
            lock (editionLock)
            {
                foreach (User user in editeurs)
                {
                    user.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionResponce.Select, broadcastString);
                }
            }
        }



        public void RemoveEditor(User user)
        {
            if (user.Card != null)
            {
                lock (editionLock)
                {
                    List<User> editors = Editors[user.Card];
                    if (editors != null)
                    {
                        editors.Remove(user);
                        if (editors.Count == 0)
                            m_cards.Remove(user.Card);
                    }
                }
            }
        }
    }

    public class CardProfile
    {
        public string name;
        public bool isPrivate;
        public string password;
        public float score;
        public int votes;
        public string creator;
        public List<string> modifiers;

        public CardProfile()
        {
        }

        public CardProfile(string name, string creator, bool isPrivate, string password = "")
        {
            this.name = name;
            this.isPrivate = isPrivate;
            this.creator = creator;
            if (password != "")
                this.password = password;
        }
    }
}
