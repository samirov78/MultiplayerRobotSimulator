using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class EnregistrerDistant : Form
    {
        public EnregistrerDistant()
        {
            InitializeComponent();
            Program.SDispatcher.EditionConnectionM.CardSaved += UnscribeAndClose;
        }

        private void UnscribeAndClose()
        {
            Program.SDispatcher.EditionConnectionM.CardSaved -= UnscribeAndClose;
            Close();
        }

        private void m_cardNameTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && !char.IsLetter(e.KeyChar) &&
                (e.KeyChar != '_'))
            {
                e.Handled = true;
            }
        }

        private void m_saveButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.enregistrerZoneDeSimulation(Edition.ServerTempCardName);
            Program.SDispatcher.EditionConnectionM.SaveCard(m_cardNameTextBox.Text, Edition.ServerTempCardName);
        }
    }
}
