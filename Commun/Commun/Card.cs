using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Xml.Serialization;

namespace Commun
{
    [XmlRoot("configuration")]
    public class Card
    {
        public const int tableWidth = 96;
        public const int tableHeight = 48;
        public const float murHeight = (float)0.25;
        public const float ligneHeight = (float)0.75;
        public const int PoteauDiameter = 2;

        //public int Scale = 8;

        [XmlElement("CScene")]
        public Scene scene;

        private string file;

        public Card()
        {
        }

        /// <summary>
        /// Lire un fihchier contenant la carte pour le constructeur de la carte 
        /// </summary>
        /// <param name="nomFichier">le nom du fichier contennat la carte</param>
        public static Card ReadXml(string nomFichier)
        {
            Card card;
            XmlSerializer xs = new XmlSerializer(typeof(Card));
            using (StreamReader reader = new StreamReader(nomFichier))
            {
                card = xs.Deserialize(reader) as Card;
                card.file = nomFichier;
            }
            return card;
        }

        public static Card ReadFromString(string xml)
        {
            Card card;
            XmlSerializer xs = new XmlSerializer(typeof(Card));

            using (TextReader reader = new StringReader(xml))
            {
                card = xs.Deserialize(reader) as Card;
            }

            return card;
        }

        public void WriteXml(string nomFichier)
        {
            XmlSerializer xs = new XmlSerializer(typeof(Card));
            using (StreamWriter wd = new StreamWriter(nomFichier))
            {
                XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
                ns.Add("", "");
                xs.Serialize(wd, this, ns);
            }
        }

        public void ConvertCoordonates(ref float x, ref float y, int scale)
        {
            x = (x * scale) + (tableWidth * scale / 2);
            y = -(y * scale) + (tableHeight * scale / 2);
        }

        public void ConvertCoordonates(ref PointF point, int scale)
        {
            point.X = (point.X * scale) + (tableWidth * scale / 2);
            point.Y = -(point.Y * scale) + (tableHeight * scale / 2);
        }

        public void SaveAsImage(string fileName, int scale)
        {
            if (!Path.HasExtension(fileName))
                return;
            Bitmap bitmap = GetBitmap(scale);
            string extension = Path.GetExtension(fileName);
            switch (extension)
            {
                case ".bmp":
                    bitmap.Save(fileName);
                    break;
                case ".jpg":
                    EncoderParameters encoderParametersJpg = new EncoderParameters(1);
                    EncoderParameter encoderParameterJpg = new EncoderParameter(Encoder.Quality, 100L);
                    encoderParametersJpg.Param[0] = encoderParameterJpg;
                    bitmap.Save(fileName, Utility.GetEncoder(ImageFormat.Jpeg), encoderParametersJpg);
                    break;
                case ".png":
                    EncoderParameters encoderParametersPng = new EncoderParameters(1);
                    encoderParametersPng.Param[0] = new EncoderParameter(Encoder.Quality, 1L);
                    bitmap.Save(fileName, Utility.GetEncoder(ImageFormat.Png), encoderParametersPng);
                    break;
                default:
                    break;
            }
        }

        public Bitmap GetBitmap(int scale)
        {
            //Bitmap bitmap = new Bitmap(tableWidth * scale, (int)(tableWidth * (scale / 4.0) * 3));
            Bitmap bitmap = new Bitmap(tableWidth * scale, tableHeight * scale);
            using (Graphics g = Graphics.FromImage(bitmap))
            {
                //g.FillRectangle(Brushes.Black, 0, 0, tableWidth * scale, tableWidth);
                g.FillRectangle(Brushes.White, 0, 0, tableWidth * scale, tableHeight * scale);
                //g.FillRectangle(Brushes.Black, 0, tableWidth * (((3 * scale) - 4) / 4), tableWidth * scale, tableWidth);

                for (int i = 0; i < scene.m_noeuds.Count; i++)
                {
                    Node node = scene.m_noeuds.ElementAt(i);
                    if (node is Poteau)
                        node.Draw(g, Brushes.Blue, this, scale);
                    else if (node is Mur)
                        node.Draw(g, Brushes.Red, this, scale);
                    else if (node is Ligne)
                        node.Draw(g, Brushes.Black, this, scale);
                    else if (node is Fleche)
                        node.Draw(g, Brushes.Magenta, this, scale);
                }
            }
            return bitmap;
        }

        public void DrawRectangle(Graphics g, Brush b, PointF begin, PointF end, float height, int scale)
        {
            float norme = (float)Math.Sqrt((end.X - begin.X) * (end.X - begin.X) + (end.Y - begin.Y) * (end.Y - begin.Y));
            PointF pointU = new PointF((end.X - begin.X) / norme, (end.Y - begin.Y) / norme);
            PointF pointR90 = new PointF(
                (float)(pointU.X * Math.Cos(Math.PI / 2) - pointU.Y * Math.Sin(Math.PI / 2)) * height / 2,
                (float)(pointU.X * Math.Sin(Math.PI / 2) + pointU.Y * Math.Cos(Math.PI / 2)) * height / 2);

            PointF point1 = new PointF(begin.X + pointR90.X, begin.Y + pointR90.Y);
            PointF point4 = new PointF(begin.X - pointR90.X, begin.Y - pointR90.Y);
            PointF point2 = new PointF(end.X + pointR90.X, end.Y + pointR90.Y);
            PointF point3 = new PointF(end.X - pointR90.X, end.Y - pointR90.Y);

            ConvertCoordonates(ref point1, scale);
            ConvertCoordonates(ref point2, scale);
            ConvertCoordonates(ref point3, scale);
            ConvertCoordonates(ref point4, scale);
            PointF[] points = { point1, point2, point3, point4 };
            g.FillPolygon(b, points);
        } 

        public void Save()
        {
            WriteXml(file);
        }

        /// <summary>
        /// Add a node to th card
        /// </summary>
        /// <param name="data">node's data</param>
        /// <returns>true if added false is the format is incorrect</returns>
        public bool CreateNode(string data)
        {
            string[] rootWithChildren = data.Split(Utility.ChildrenSeperator);
            string[] rootAttributes = rootWithChildren[0].Split(Utility.AttributesSeperator);
            string type, id;
            try
            {
                id = rootAttributes[0];
                type = rootAttributes[1];
            }
            catch
            {
                return false;
            }
            Node node = GetNodeById(id);
            if (node == null)
            {
                switch (type)
                {
                    case NodesNames.POTEAU:
                        node = new Poteau(rootAttributes);
                        break;
                    case NodesNames.FLECHE:
                        node = new Fleche(rootAttributes);
                        break;
                    case NodesNames.MUR:
                        node = new Mur(rootAttributes);
                        break;
                    case NodesNames.LIGNE:
                        string[] children = null;
                        if (rootWithChildren.Length > 1)
                        {
                            children = new string[rootWithChildren.Length - 1];
                            Array.Copy(rootWithChildren, 1, children, 0, children.Length);
                            node = new Ligne(rootAttributes, children);
                        }
                        break;
                }
                if (node != null)
                {
                    scene.AddNode(node);
                    Save();
                    return true;
                }
            }
            return false;
        }

        public bool ModifyNode(string data)
        {
            string[] rootWithChildren = data.Split(Utility.ChildrenSeperator);
            string[] rootAttributes = rootWithChildren[0].Split(Utility.AttributesSeperator);
            string type, id;
            try
            {
                id = rootAttributes[0];
                type = rootAttributes[1];
            }
            catch
            {
                return false;
            }
            Node node = GetNodeById(id);
            if (node == null)
            {
                switch (type)
                {
                    case NodesNames.POTEAU:
                        node = new Poteau(rootAttributes);
                        break;
                    case NodesNames.FLECHE:
                        node = new Fleche(rootAttributes);
                        break;
                    case NodesNames.MUR:
                        node = new Mur(rootAttributes);
                        break;
                    case NodesNames.LIGNE:
                        string[] children = null;
                        if (rootWithChildren.Length > 1)
                        {
                            children = new string[rootWithChildren.Length - 1];
                            Array.Copy(rootWithChildren, 1, children, 0, children.Length);
                            node = new Ligne(rootAttributes, children);
                        }
                        break;
                }
                if (node != null)
                {
                    scene.AddNode(node);
                    Save();
                    return true;
                }
                return false;
            }
            else
            {
                switch (type)
                {
                    case NodesNames.POTEAU:
                    case NodesNames.FLECHE:
                    case NodesNames.MUR:
                        node.ModifyAttributes(rootAttributes);
                        break;
                    case NodesNames.LIGNE:
                        string[] children = null;
                        if (rootWithChildren.Length > 1)
                        {
                            children = new string[rootWithChildren.Length - 1];
                            Array.Copy(rootWithChildren, 1, children, 0, children.Length);
                            (node as Ligne).ModifyAttributes(rootAttributes, children);
                        }
                        else
                            return false;
                        break;
                }
                Save();
                return true;
            }
        }

        private Node GetNodeById(string id)
        {
            for (int i = 0; i < scene.m_noeuds.Count; i++)
            {
                if (scene.m_noeuds.ElementAt(i).ID == id)
                    return scene.m_noeuds.ElementAt(i);
            }
            return null;
        }

        public void RemoveNode(string id)
        {
            Node node = GetNodeById(id);
            scene.m_noeuds.Remove(node);
            Save();
        }
    }

    public class Scene
    {
        [XmlAttribute]
        public int CALCULS_PAR_IMAGE;

        [XmlElement("fleche", typeof(Fleche))]
        [XmlElement("poteau", typeof(Poteau))]
        [XmlElement("ligne", typeof(Ligne))]
        [XmlElement("mur", typeof(Mur))]
        public List<Node> m_noeuds;

        public void AddNode(Node node)
        {
            m_noeuds.Add(node);
        }
    }

    public abstract class Node
    {
        [XmlAttribute]
        public string ID;
        [XmlAttribute]
        public string Type;
        [XmlAttribute]
        public string Affiche;
        [XmlAttribute]
        public string Enregistrable;
        [XmlAttribute]
        public string Selectionnable;
        [XmlIgnore]
        public string Selectionne;
        [XmlAttribute]
        public string Angle;
        [XmlAttribute]
        public string x;
        [XmlAttribute]
        public string y;
        [XmlAttribute]
        public string z;
        [XmlAttribute]
        public string Pos_x;
        [XmlAttribute]
        public string Pos_y;
        [XmlAttribute]
        public string Pos_z;
        [XmlAttribute]
        public string Redim_x;
        [XmlAttribute]
        public string Redim_y;
        [XmlAttribute]
        public string Redim_z;

        public Node()
        {
        }

        public Node(string[] attributes)
        {
            ModifyAttributes(attributes);
        }

        public void ModifyAttributes(string[] attributes)
        {
            ID = attributes[(int)AttributesNames.Enum.Id];
            Type = attributes[(int)AttributesNames.Enum.Type];
            Affiche = attributes[(int)AttributesNames.Enum.Affiche];
            Enregistrable = attributes[(int)AttributesNames.Enum.Enregistrable];
            Selectionnable = attributes[(int)AttributesNames.Enum.Selectionnable];
            Selectionne = "0";
            Angle = attributes[(int)AttributesNames.Enum.Angle];
            x = attributes[(int)AttributesNames.Enum.x];
            y = attributes[(int)AttributesNames.Enum.y];
            z = attributes[(int)AttributesNames.Enum.z];
            Pos_x = attributes[(int)AttributesNames.Enum.Pos_x];
            Pos_y = attributes[(int)AttributesNames.Enum.Pos_y];
            Pos_z = attributes[(int)AttributesNames.Enum.Pos_z];
            Redim_x = attributes[(int)AttributesNames.Enum.Redim_x];
            Redim_y = attributes[(int)AttributesNames.Enum.Redim_y];
            Redim_z = attributes[(int)AttributesNames.Enum.Redim_z];
        }

        public PointF GetBeginPoint()
        {
            float longueur = float.Parse(Redim_x, CultureInfo.InvariantCulture);
            float positionX = float.Parse(Pos_x, CultureInfo.InvariantCulture);
            float positionY = float.Parse(Pos_y, CultureInfo.InvariantCulture);
            float angle = float.Parse(Angle, CultureInfo.InvariantCulture);
            PointF begin = new PointF();
            begin.X = -(float)((longueur / 2.0) * Math.Cos(Utility.DegreeToRadian(angle))) + positionX;
            begin.Y = -(float)((longueur / 2.0) * Math.Sin(Utility.DegreeToRadian(angle))) + positionY;
            return begin;
        }

        public PointF GetEndPoint()
        {
            float longueur = float.Parse(Redim_x, CultureInfo.InvariantCulture);
            float positionX = float.Parse(Pos_x, CultureInfo.InvariantCulture);
            float positionY = float.Parse(Pos_y, CultureInfo.InvariantCulture);
            float angle = float.Parse(Angle, CultureInfo.InvariantCulture);
            PointF end = new PointF();
            end.X = (float)((longueur / 2.0) * Math.Cos(Utility.DegreeToRadian(angle))) + positionX;
            end.Y = (float)((longueur / 2.0) * Math.Sin(Utility.DegreeToRadian(angle))) + positionY;
            return end;
        }

        public abstract void Draw(Graphics g, Brush b, Card card, int scale);
    }

    [XmlRoot("Fleche")]
    public class Fleche : Node
    {
        public Fleche()
        {
            Type = "fleche";
        }

        public Fleche(string[] attributes) : base(attributes)
        {
            ModifyAttributes(attributes);
        }

        public override void Draw(Graphics g, Brush b, Card card, int scale)
        {
            PointF position = new PointF(float.Parse(Pos_x, CultureInfo.InvariantCulture),
                            float.Parse(Pos_y, CultureInfo.InvariantCulture));
            float angle = float.Parse(Angle, CultureInfo.InvariantCulture);

            PointF point1 = new PointF((float)1.65 + position.X, (float)0.5 + position.Y);
            PointF point2 = new PointF((float)-1.65 + position.X, (float)0.5 + position.Y);
            PointF point3 = new PointF((float)-1.65 + position.X, 1 + position.Y);
            PointF point4 = new PointF((float)-3.65 + position.X, position.Y);
            PointF point5 = new PointF((float)-1.65 + position.X, -1 + position.Y);
            PointF point6 = new PointF((float)-1.65 + position.X, (float)-0.5 + position.Y);
            PointF point7 = new PointF((float)1.65 + position.X, (float)-0.5 + position.Y);

            System.Drawing.Drawing2D.Matrix rotateMatrix = new System.Drawing.Drawing2D.Matrix();
            card.ConvertCoordonates(ref position, scale);
            rotateMatrix.RotateAt(-angle, position);

            card.ConvertCoordonates(ref point1, scale);
            card.ConvertCoordonates(ref point2, scale);
            card.ConvertCoordonates(ref point3, scale);
            card.ConvertCoordonates(ref point4, scale);
            card.ConvertCoordonates(ref point5, scale);
            card.ConvertCoordonates(ref point6, scale);
            card.ConvertCoordonates(ref point7, scale);

            PointF[] points = { point1, point2, point3, point4, point5, point6, point7 };
            rotateMatrix.TransformPoints(points);
            g.FillPolygon(b, points);
        }
    }

    public class Poteau : Node
    {
        public Poteau()
        {
            Type = "poteau";
        }

        public Poteau(string[] attributes) : base(attributes)
        {
            ModifyAttributes(attributes);
        }

        public override void Draw(Graphics g, Brush b, Card card, int scale)
        {
            float redx = float.Parse(Redim_x, CultureInfo.InvariantCulture);
            float redy = float.Parse(Redim_y, CultureInfo.InvariantCulture);
            float x = float.Parse(Pos_x, CultureInfo.InvariantCulture) - Card.PoteauDiameter * redx / 2;
            float y = float.Parse(Pos_y, CultureInfo.InvariantCulture) + Card.PoteauDiameter * redy / 2;
            card.ConvertCoordonates(ref x, ref y, scale);
            g.FillEllipse(b, x, y, redx * scale * Card.PoteauDiameter, redy * scale * Card.PoteauDiameter);
        }
    }

    public class Mur : Node
    {
        public Mur()
        {
            Type = "mur";
        }

        public Mur(string[] attributes) : base(attributes)
        {
            ModifyAttributes(attributes);
        }

        public override void Draw(Graphics g, Brush b, Card card, int scale)
        {
            card.DrawRectangle(g, b, GetBeginPoint(), GetEndPoint(), Card.murHeight, scale);
        }
    }
    
    public class Segment : Node
    {
        public Segment()
        {
            Type = "segment";
        }

        public Segment(string[] attributes) : base(attributes)
        {
           ModifyAttributes(attributes);
        }

        public override void Draw(Graphics g, Brush b, Card card, int scale)
        {
           card.DrawRectangle(g, b, GetBeginPoint(), GetEndPoint(), Card.ligneHeight, scale);
        }
    }

    public class Ligne : Node
    {
        [XmlElement("segment", typeof(Segment))]
        public List<Segment> segments = new List<Segment>();
        public Ligne()
        {
            Type = "ligne";
        }

        public Ligne(string[] rootAttributes, string[] children) : base (rootAttributes)
        {
            if (children == null || children.Length == 0)
                return;
            foreach (string child in children)
            {
                Segment segment = new Segment(child.Split(Utility.AttributesSeperator));
                segments.Add(segment);
            }
        }

        public void ModifyAttributes(string[] rootAttributes, string[] children)
        {
            base.ModifyAttributes(rootAttributes);
            if (children == null || children.Length == 0)
            {
                return;
            }
            segments.Clear();
            foreach (string child in children)
            {
                Segment segment = new Segment(child.Split(Utility.AttributesSeperator));
                segments.Add(segment);
            }
        }

        public override void Draw(Graphics g, Brush b, Card card, int scale)
        {
            foreach (Segment segment in segments)
                segment.Draw(g, b, card, scale);
        }
    }
}
