using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Commun;

namespace Server
{
    public class SimulationManager : ICommandManager
    {
        private List<User> m_users;
        private int compteurInitFleches;

        public SimulationManager(List<User> users)
        {
            m_users = users;
            compteurInitFleches = 0;
        }

        public void HandleReceivedData(User user, string receivedData)
        {
          
            string data = Utility.GetData(receivedData);
            string[] splitData = null;
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.SimulationCommand.InitSimulationOnline:
                    SpreadInitFleches(user);
                    //SpreadInitSimulationOnline(user);
                    break;
                case (int)Utility.SimulationCommand.DiffuserChaineRobot:
                    SpreadDiffuserChaineRobot(user, data);
                    break;
                case (int)Utility.SimulationCommand.FinSimulation:
                    SpreadFinSimulation(user);
                    break;
                case (int)Utility.SimulationCommand.ArrowInitialized:         
                    SpreadInitSimulationOnline(user);
                    break;
                //case (int)Utility.SimulationCommand.InitFleches:
                //    SpreadInitFleches(user);
                //    break;
                default:
                    break;
            }
        }

        private void SpreadInitSimulationOnline(User sender)
        {
            List<User> editors =  Program.CmdDispatcher.EditionM.Editors[sender.Card];
            //diffuser pour les autres editeurs de la carte
            //foreach (User user in editors)
            //{
                sender.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationResponse.InitSimulationOnline);
            //}
        }
        //SpreadDiffuserChaineRobot(user, data);
        private void SpreadDiffuserChaineRobot(User sender, string data)
        {
            List<User> editors = Program.CmdDispatcher.EditionM.Editors[sender.Card];
            //diffuser pour les autres editeurs de la carte
            foreach (User user in editors)
            {
                if (user.ID != sender.ID)
                {
                    user.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationResponse.DiffuserChaineRobot,data);
                }
            }
        }
        
        private void SpreadFinSimulation(User sender)
        {
            List<User> editors = Program.CmdDispatcher.EditionM.Editors[sender.Card];
            //diffuser pour les autres editeurs de la carte
            foreach (User user in editors)
            {
                if (user.ID != sender.ID)
                {
                    user.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationResponse.FinSimulation);
                }
            }
        }

        private void SpreadInitFleches(User sender)
        {
            List<User> editors = Program.CmdDispatcher.EditionM.Editors[sender.Card];
            string chaineFleches = "";
            for (int i= 0; i < editors.Count - 1;i++ )
            {
                chaineFleches +=  editors[i].Fleche + Utility.AttributesSeperator;//editors[i].UserName + ":" 
            }
            chaineFleches +=  editors[editors.Count - 1].Fleche;//editors[editors.Count - 1].UserName+ ":"

            //diffuser pour les autres editeurs de la carte
            foreach (User user in editors)
            {
                user.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationResponse.InitFleches, user.Fleche +
                    Utility.AttributesSeperator + chaineFleches);
            }
        }


    }
}
