using InterfaceGraphique;
using System;
using Commun;

namespace Client
{
    public class SimulationConnectionManager
    {
        //Events
        public event InitSimulationOnlineHandler InitSimulationOnline;
        public event ChaineRobotReceivedHandler ChaineRobotReceived;
        public event FinSimulationReceivedHandler FinSimulationReceived;//InitFlechesReceived
        public event InitFlechesReceivedHandler InitFlechesReceived;

        //Handlers
        public delegate void InitSimulationOnlineHandler();
        public delegate void ChaineRobotReceivedHandler(string chaineRobot);
        public delegate void FinSimulationReceivedHandler();
        public delegate void InitFlechesReceivedHandler(string fleche);

        private Connection m_connection;

        public SimulationConnectionManager(Connection connection)
        {
            m_connection = connection;
        }

        public void HandleReceivedData(string receivedData)
        {
            //throw new NotImplementedException();
            //begin
            //   Program.edition.lancerSimulationOnLine
            //  ()
            // modify robot
            string data = Utility.GetData(receivedData);
            string[] splitData = null;
            switch (Utility.GetCommand(receivedData))
            {
                case (int)Utility.SimulationResponse.InitSimulationOnline:
                    InitSimulationOnline?.Invoke(); //(content)
                    break;
                case (int)Utility.SimulationResponse.DiffuserChaineRobot:
                    ChaineRobotReceived?.Invoke(receivedData);
                    break;
                case (int)Utility.SimulationResponse.FinSimulation:
                    FinSimulationReceived?.Invoke();
                    break;
                case (int)Utility.SimulationResponse.InitFleches:
                    InitFlechesReceived?.Invoke(data);
                    m_connection.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationCommand.ArrowInitialized);
                    break;
                default:
                    break;
            }
         }

      
        /*public void SpreadInitFleches()
        {
            m_connection.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationCommand.InitFleches);
        }*/

        public void SpreadInitSimulationOnline()
        {
            m_connection.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationCommand.InitSimulationOnline);
        }
        
        public void SpreadInfoRobot(string chaineRobot)
        {
            m_connection.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationCommand.DiffuserChaineRobot,chaineRobot);
        }
        //SpreadFinSimulation
        public void SpreadFinSimulation()
        {
            m_connection.Send((int)Utility.BasicCommand.Simulation, (int)Utility.SimulationCommand.FinSimulation);
        }
    }
}