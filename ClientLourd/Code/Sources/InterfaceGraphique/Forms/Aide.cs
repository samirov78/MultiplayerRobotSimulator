///////////////////////////////////////////////////////////////////////////////
/// @file Aide.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class Aide : Form
    {
        public Aide()
        {
            InitializeComponent();
            help.Rows.Add("Réinitialiser environnement édition avec nouvelle scène:\n Cliquez sur Fichier > Nouveau", "Fichier", "Nouveau", "Ctrl+N");
            help.Rows.Add("Ouvrir boite dialogue qui offre chargement zone simulation contenue dans fichier XML:\n 1. Cliquez sur Fichier > Ouvrir\n 2. Choisissez l'emplacement où le fichier XML se trouve\n 3. Cliquez sur Ouvrir", "Fichier", "Ouvrir", "Ctrl+O");
            help.Rows.Add("Sauvegarder scène dans fichier XML courant:\n Si aucun fichier n’est courant, cette option a même effet Enregistrer sous", "Fichier", "Enregistrer", "Ctrl+S");
            help.Rows.Add("Sauvegarder scène en tant que fichier XML:\n 1. Cliquez sur Fichier > Enregistrer sous\n 2. Choisissez l'emplacement où le fichier XML doit être enregistré\n 3. Cliquez sur Enregistrer", "Fichier", "Enregistrer sous", "");
            help.Rows.Add("Basculer mode test:\n Cliquez sur Fichier > Mode test", "Fichier", "Mode test", "");
            help.Rows.Add("Retourner menu principal:\n Cliquez sur Fichier > Menu principal", "Fichier", "Menu principal", "Ctrl+Q");


            help.Rows.Add("Effacer objets sélectionnés:\n Cliquez sur Édition > Supprimer", "Édition", "Supprimer", "Suppr");
            help.Rows.Add("Sélectionner objet scène:\n 1. Cliquez sur Outils > Sélection\n 2. Cliquez sur l'objet ou les objets de la scène à sélectionner", "Outils", "Sélection", "S");
            help.Rows.Add("Déplacer objets présentement sélectionnés:\n Cliquez sur Outils > Déplacement", "Outils", "Déplacement", "D");
            help.Rows.Add("Pivoter objets sélectionnés:\n Cliquez sur Outils > Rotation", "Outils", "Rotation", "R");
            help.Rows.Add("Mettre à échelle objets sélectionnés:\n Cliquez sur Outils > Mise à échelle", "Outils", "Mise à échelle", "E");
           
            help.Rows.Add("Dupliquer objets sélectionnés:\n Cliquez sur Outils > Duplication", "Outils", "Menu principal", "Ctrl+Q");


            help.Rows.Add("Créer poteau:\n 1. Cliquez sur Outils > Création d'objets > Poteau\n 2. Cliquez à l'intérieur de la zone de simulation, pour ajouter un nouvel objet de type poteau ", "Outils", "Création d'objets", "");
            help.Rows.Add("Créer Mur:\n 1. Cliquez sur Outils > Création d'objets > Mur\n 2. Cliquez à l'intérieur de la zone de simulation pour indiquer la position de la première extrémité\n 3. Cliquez une seconde fois à l'intérieur de la zone de simulation pour indiquer la position de la deuxième extrémité", "Outils", "Création d'objets", "");
            help.Rows.Add("Créer Ligne:\n 1. Cliquez sur Outils > Création d'objets > Ligne\n 2. Cliquez à l'intérieur de la zone de simulation pour indiquer la position de la première extrémité\n 3. Cliquez une seconde fois à l'intérieur de la zone de simulation pour indiquer la position de la deuxième extrémité Vous pouvez utiliser la touche \n  \"Ctrl\" pour créer une ligne avec plus d'un segment. Le premier clic initie le début de la ligne.", "Outils", "Création d'objetsr", "");
            help.Rows.Add("Effectuer zoom avec rectangle élastique:\n 1. Cliquez sur Outils > Zoom\n 2. Définissez à l'aide de la souris la proportion à zoomer ", "Outils", "Zoom", "Z");
            help.Rows.Add("Effectuer zoom avant vue avec clavier:\n Pesez sur la touche \" + \" pour effectuer un zoom avant", "", "", "+");
            help.Rows.Add("Effectuer zoom avant vue avec roulette souris:\n Tournez la roulette de la souris vers l'avant", "", "", "");
            help.Rows.Add("Effectuer zoom arrière avec clavier:\n Pesez sur la touche \" - \" pour effectuer un zoom arrière", "", "", "-");

            help.Rows.Add("Effectuer zoom arrière vue avec roulette souris:\n Tournez la roulette de la souris vers l'arrière", "", "", "");
            help.Rows.Add("Choisir vue orthographique:\n Cliquez sur Vues > Orthographique", "Vues", "Orthographique", "1");
            help.Rows.Add("Choisir vue orbite:\n Cliquez sur Vues > Orbite", "Vues", "Orbite", "2");
        }

        private void help_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
        }
    }
}
