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
        public event NewImageReceivedHandler NewImageReceived;
        public event ImageSentHandler ImageSent;

        public delegate void NewMessageReceivedHandler(string source, string message, string time, string destination);
        public delegate void NewImageReceivedHandler(string source, string imageName, string image,string timeStamp, string destination);
        public delegate void ImageSentHandler(string imageName, string timeStamp, string to);

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
                    //(userName; message; timeStamp; destination)
                    if (data != null)
                    {
                        splitData = data.Split(';');
                        if(splitData != null && splitData.Length == 4)
                            NewMessageReceived?.Invoke(splitData[0], Utility.Decode(splitData[1]), splitData[2], splitData[3]);
                    }
                    break;
                case (int)Utility.ChatResponse.NewImage:
                    //(userName; imageName; E(image); timestamp; destination)
                    if (data != null)
                    {
                        splitData = data.Split(';');
                        if(splitData != null && splitData.Length == 5)
                            NewImageReceived?.Invoke(splitData[0], splitData[1], Utility.Decode(splitData[2]), splitData[3], splitData[4]);
                    }
                    break;
                case (int)Utility.ChatResponse.ImageSent:
                    //(imageName; timestamp; destination)
                    if (data != null)
                    {
                        splitData = data.Split(';');
                        if (splitData != null && splitData.Length == 3)
                            ImageSent?.Invoke(splitData[0], splitData[1], splitData[2]);
                    }
                    break;
                default:
                    break;
            }
        }

        public void SpreadMessage(string message, string timeStamp, string to)
        {
            message = Utility.Encode(message) + ";" + Utility.Encode(timeStamp) + ";" + to;
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.SendMessage, message);
            //playSound(sendMassageSound);
        }

        public void SendImage(string imageName, byte[] imageBytes, string timeStamp, string to)
        {
            string image = Convert.ToBase64String(imageBytes, 0, imageBytes.Length);
            String message = imageName + ";" + Utility.Encode(image) + ";" + timeStamp + ";" + to ;
            m_connection.Send((int)Utility.BasicCommand.Chat, (int)Utility.ChatCommand.SendImage, message);
        }
    }
}
