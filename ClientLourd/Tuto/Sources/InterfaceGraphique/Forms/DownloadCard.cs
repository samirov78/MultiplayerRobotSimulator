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
    public partial class DownloadCard : Form
    {
        private delegate void OneParameterStringHandler(string chaine);

        public DownloadCard()
        {
            InitializeComponent();
        }

        private void m_downloadButton_Click(object sender, EventArgs e)
        {
            Program.SDispatcher.EditionConnectionM.GetCard(m_cardNameTextBox.Text);
        }

        public void Close(String chaine)
        {
            if (InvokeRequired)
            {
                this.Invoke(new OneParameterStringHandler(Close), chaine);
            }
            else
            {
                this.Close();
            }
        }
    }
}
