using System;
using System.Collections.Generic;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;

namespace Commun
{
    static class Utility
    {
        public const char CommandSeperator = ';';
        public const char AttributesSeperator = '#';
        public const char ChildrenSeperator = ':';
        public const char InappropriateWordsSeperator = ':';

        public enum BasicCommand
        {
            Connection,//
            Configuration,//
            Chat,//
            Edition,//
            Simulation, //
        }

        public enum ConnectionCommand
        {
            LogIn,//(userName;password)
            LogOut,//()
            LoggedInUsers, //()
        }

        public enum ConnectionResponse
        {
            LoggedIn,//()
            AlreadyLoggedIn, //(userName)
            WrongIdentification,//()
            UserNameAlreadyLoggedIn,//()
            LoggedOut, //()
            AlreadyLoggedOut,//()
            NewUserLoggedIn, //(userName)
            UserLoggedOut, //(userName)
            LoggedInUsers, //(user1;user2;....)
            NotLogged,
        }

        public enum ConfigurationCommand
        {
            CreateProfil, //(user;prenom;nom;E(password);E(courriel);admin?"1":"0";E(adminPassword))
            ChangeProfileImage, //(image,extention)
            ChangeEmail,//(email)
            ChangePassword,
            ChangeProfileType,//(admin; password)
            AddInappropriateWord,//(word)
            GetInappropriateWords,//()
            RemoveInappropriateWord,//(word)
            GetMyCards,//()
            ChangeCardPassword,//(name;E(password))
        }

        public enum ConfigurationResponse
        {
            WrongAdminPassword,
            NameAlreadyUsed,
            ProfilCreated,
            ProfileImageChanged,
            EmailChanged,
            PasswordChanged,
            WrongOldPassword,
            ProfileTypeChanged,
            InappropriateWordAdded,//(word)
            InappropriateWordRemoved, //(word)
            InappropriateWordsList,//(word1:word2:.....)
            YourCards,//(name;score;E(password);name;score;E(password);.........)
        }

        public enum ChatCommand
        {
            SendMessage,//(message;timeStamp;destination)
            SendImage,//(imageName;E(image);timeStamp;destination);
            SpreadMessage,//(message;timeStamp;destination)
            CreateGroup,//(name)
            GetGroups,//()
            JoinGroup,//(name)
            QuitGroup,//(name)
            InviteToJoinGroup,
        }

        public enum ChatResponse
        {
            NewMessage,//(userName;message;timeStamp;destination)
            NewImage, //(userName;imageName;image;timestamp;destination)
            ImageSent,//(imageName;timeStamp;destination)
            SimpleAdministration,//
            NewSpreadMessage,//(userName;message;timeStamp;destination)
            GroupAdministration,//
            GroupCreated,//(name)
            GroupsList,//(groupe1;groupe2;.....)
            GroupJoined,//(name)
            NewGroup,//(name)
            InvitationToJoinGroup,//(name)
            ForceJoinGroup,//(name)
        }

        public enum EditionCommand
        {
            SaveCard,//(name;xmlCard;password;online) password = "" pour public / onligne = "1" pour on ligne
            GetCard,//
            CreateNode,//
            Select,//
            Deselect,//
            ModifyNode,//(node,phantom)
            SelectElastic,
            DeleteSelection,
            ScaleSelection,
            InitScale,
            InitDeplacement,
            DeplacerSelection,
            DuplicateSelection,
            RetourToInitialScale,
            UpdateMySelectedNodes,
            PivoterObjetSelectionne,
            PivoterObjetsMultiples,
            AnnulerRotation,
            UpdateDuplicatesServer, //pas de reponse correspondante pour le serveur
            GetCards,//()
            GetCardRate,//(name,rate)
            GetCardInfo, //(name)
            SuppDernierNoeud,
        }

        public enum EditionResponce
        {
            CardSaved,//(name)
            Card,// send card (content)
            NoCard,// non existatnt card
            CreateNode,//
            Select,//
            Deselect,//
            ModifyNode,//(data)
            DeleteSelection,
            ScaleSelection,
            InitScaleSel,
            InitDeplacement,
            DeplacerSelection,
            DuplicateSelection,
            RetourToInitialScale,
            UpdateMySelectedNodes,
            PivoterObjetSelectionne,
            PivoterObjetsMultiples,
            AnnulerRotation,
            CardPlus,//(xml;name;password;score)
            CardInfo,//(name, score, votes)
            SuppDernierNoeud,
            EjectEditor,//()
        }

        public enum SimulationCommand
        {
            InitSimulationOnline,
            DiffuserChaineRobot,
            FinSimulation,
            //InitFleches,
            ArrowInitialized,
            DeleteArrows,
        }

        public enum SimulationResponse
        {
            InitSimulationOnline,
            DiffuserChaineRobot,
            FinSimulation,
            InitFleches,
            DeleteArrows,
        }

        public enum Status
        {
            SimpleUser,
            Admin,
        }

        public enum DrawState
        {
            Phantom,
            Final,
        }

        /// <summary>
        /// Check if a string is a valid IP
        /// </summary>
        /// <param name="ip">The string to check</param>
        /// <returns>true if the Ip is valid</returns>
        public static bool IsValidIp(string ip)
        {
            if (String.IsNullOrWhiteSpace(ip))
            {
                return false;
            }
            string[] splitValues = ip.Split('.');
            if (splitValues.Length != 4)
            {
                return false;
            }
            byte tempForParsing;
            return splitValues.All(r => byte.TryParse(r, out tempForParsing));
        }

        /// <summary>
        /// Check if a port is valid in Polytechnique
        /// </summary>
        /// <param name="port"></param>
        /// <returns>true if the port is valid false if not</returns>
        public static bool IsValidPort(int port)
        {
            if (port <= 5050 && port >= 5000)
                return true;
            else
                return false;
        }

        /// <summary>
        /// Code a string by rplacement of ; by %s
        /// </summary>
        /// <param name="data">The string to encode</param>
        /// <returns>Encoded string</returns>
        public static string Encode(string data)
        {
            data.Replace("%s", "%%s");
            return data.Replace(";", "%s");
        }

        /// <summary>
        /// Decode a string encoded with Encode()
        /// </summary>
        /// <param name="data">The string to decode</param>
        /// <returns>Decoded string</returns>
        public static string Decode(string data)
        {
            char[] dataArray = data.ToArray();
            string result = "";

            for (int i = 0; i < dataArray.Length; i++)
            {
                if ((i == dataArray.Length - 1) || (dataArray[i] != '%') || (dataArray[i + 1] != 's'))
                {
                    result += dataArray[i];
                }
                else
                {
                    if (i == 0 || dataArray[i - 1] != '%')
                    {
                        result += ';';
                        i++;
                    }
                }
            }
            return result;
        }

        public static int GetCommand(string message)
        {
            int index = message.IndexOf(';');
            string command = "-1";
            if (index > 0)
                command = message.Substring(0, index);
            else
                command = message;
            try
            {
                int cmd = int.Parse(command);
                return cmd;
            }
            catch
            {
                return -1;
            }
        }

        public static string GetData(string message)
        {
            if (message == null)
                return null;
            int index = message.IndexOf(';');
            if (index > 0)
                return message.Substring(index + 1, message.Length - index - 1);
            else
                return null;
        }

        public static byte[] Combine(byte[] first, byte[] second)
        {
            byte[] ret = new byte[first.Length + second.Length];
            Buffer.BlockCopy(first, 0, ret, 0, first.Length);
            Buffer.BlockCopy(second, 0, ret, first.Length, second.Length);
            return ret;
        }

        public static string GetImageFilter()
        {
            StringBuilder allImageExtensions = new StringBuilder();
            string separator = "";
            ImageCodecInfo[] codecs = ImageCodecInfo.GetImageEncoders();
            Dictionary<string, string> images = new Dictionary<string, string>();
            foreach (ImageCodecInfo codec in codecs)
            {
                allImageExtensions.Append(separator);
                allImageExtensions.Append(codec.FilenameExtension);
                separator = ";";
                images.Add(string.Format("{0} Files: ({1})", codec.FormatDescription, codec.FilenameExtension),
                           codec.FilenameExtension);
            }
            StringBuilder sb = new StringBuilder();
            if (allImageExtensions.Length > 0)
            {
                sb.AppendFormat("{0}|{1}", "All Images", allImageExtensions.ToString());
            }
            images.Add("All Files", "*.*");
            foreach (KeyValuePair<string, string> image in images)
            {
                sb.AppendFormat("|{0}|{1}", image.Key, image.Value);
            }
            return sb.ToString();
        }

        public static bool IsValidEmail(string email)
        {
            try
            {
                var addr = new System.Net.Mail.MailAddress(email);
                return addr.Address == email;
            }
            catch
            {
                return false;
            }
        }

        public static ImageCodecInfo GetEncoder(ImageFormat format)
        {
            ImageCodecInfo[] codecs = ImageCodecInfo.GetImageDecoders();
            foreach (ImageCodecInfo codec in codecs)
            {
                if (codec.FormatID == format.Guid)
                {
                    return codec;
                }
            }
            return null;
        }

        public static double DegreeToRadian(double angle)
        {
            return Math.PI * angle / 180.0;
        }
    }

    

    public static class NodesNames
    {
        public const string FLECHE = "fleche";
        public const string POTEAU = "poteau";
        public const string MUR = "mur";
        public const string LIGNE = "ligne";
        public const string SEGMENT = "segment";
    }

    public static class AttributesNames
    {
        public const string Id = "Id";
        public const string Type = "Type";
        public const string Affiche = "Affiche";
        public const string Enregistrable = "Enregistrable";
        public const string Selectionnable = "Selectionnable";
        public const string Selectionne = "Selectionne";
        public const string Angle = "Angle";
        public const string x = "x";
        public const string y = "y";
        public const string z = "z";
        public const string Pos_x = "Pos_x";
        public const string Pos_y = "Pos_y";
        public const string Pos_z = "Pos_z";
        public const string Redim_x = "Redim_x";
        public const string Redim_y = "Redim_y";
        public const string Redim_z = "Redim_z";
        public const string Depart_x = "Depart_x";
        public const string Depart_y = "Depart_y";
        public const string Depart_z = "Depart_z";
        public const string Fin_x = "Fin_x";
        public const string Fin_y = "Fin_y";
        public const string Fin_z = "Fin_z";

        public enum Enum
        {
            Id,
            Type,
            Affiche,
            Enregistrable,
            Selectionnable,
            Angle,
            x,
            y,
            z,
            Pos_x,
            Pos_y,
            Pos_z,
            Redim_x,
            Redim_y,
            Redim_z,
            Depart_x,
            Depart_y,
            Depart_z,
            Fin_x,
            Fin_y,
            Fin_z,
        }

        public static string GetString(int index)
        {
            switch (index)
            {
                case (int)Enum.Id:
                    return AttributesNames.Id;
                case (int)Enum.Type:
                    return AttributesNames.Type;
                case (int)Enum.Affiche:
                    return AttributesNames.Affiche;
                case (int)Enum.Enregistrable:
                    return AttributesNames.Enregistrable;
                case (int)Enum.Selectionnable:
                    return AttributesNames.Selectionnable;
                case (int)Enum.Angle:
                    return AttributesNames.Angle;
                case (int)Enum.x:
                    return AttributesNames.x;
                case (int)Enum.y:
                    return AttributesNames.y;
                case (int)Enum.z:
                    return AttributesNames.z;
                case (int)Enum.Pos_x:
                    return AttributesNames.Pos_x;
                case (int)Enum.Pos_y:
                    return AttributesNames.Pos_y;
                case (int)Enum.Pos_z:
                    return AttributesNames.Pos_z;
                case (int)Enum.Redim_x:
                    return AttributesNames.Redim_x;
                case (int)Enum.Redim_y:
                    return AttributesNames.Redim_y;
                case (int)Enum.Redim_z:
                    return AttributesNames.Redim_z;
                case (int)Enum.Depart_x:
                    return AttributesNames.Depart_x;
                case (int)Enum.Depart_y:
                    return AttributesNames.Depart_y;
                case (int)Enum.Depart_z:
                    return AttributesNames.Depart_z;
                case (int)Enum.Fin_x:
                    return AttributesNames.Fin_x;
                case (int)Enum.Fin_y:
                    return AttributesNames.Fin_y;
                case (int)Enum.Fin_z:
                    return AttributesNames.Fin_z;
                default:
                    return "";
            }
        }
    }
}
