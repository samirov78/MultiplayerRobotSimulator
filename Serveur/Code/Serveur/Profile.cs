using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml.Serialization;

namespace Server
{
    public class Profile
    {
        public enum Creation
        {
            User,
            Password,
            Email,
            Admin,
            AdminPassword,
        }

        public string username;
        public string firstName;
        public string lastName;
        public string email;
        public bool isAdmin;
        public string image;

        public Profile()
        {
        }

        public Profile(string username, string firstName, string lastName, string email, bool isAdmin)
        {
            this.username = username;
            this.firstName = firstName;
            this.lastName = lastName;
            if(email != "")
                this.email = email;
            this.isAdmin = isAdmin;
        }

        public static Profile Read(string name)
        {
            Profile profile = null;
            XmlSerializer xs = new XmlSerializer(typeof(Profile));
            using (StreamReader rd = new StreamReader(Program.ProfilesDirectory + "/" + name + ".xml"))
            {
                profile = xs.Deserialize(rd) as Profile;
            }
            return profile;
        }

        public void Write()
        {
            XmlSerializer xs = new XmlSerializer(typeof(Profile));
            using (StreamWriter stream = new StreamWriter(Program.ProfilesDirectory + "/" + username + ".xml"))
            {
                XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
                ns.Add("", "");
                xs.Serialize(stream, this, ns);
            }
        }
    }
}
