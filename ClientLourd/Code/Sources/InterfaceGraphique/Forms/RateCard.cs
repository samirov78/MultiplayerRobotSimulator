using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Forms
{
    public partial class RateCard : Form
    {
        private delegate void CardInfoReceivedCallback(string name, float score, int votes);

        public RateCard()
        {
            InitializeComponent();
            Program.SDispatcher.EditionConnectionM.CardInfoReceived += CardInfoReceivedHandler;
        }

        private void m_saveButton_Click(object sender, EventArgs e)
        {
            Program.SDispatcher.EditionConnectionM.SendCurrentCardRate(m_rateNumeric.Value);
            Close();
        }

        private void RateCard_FormClosing(object sender, FormClosingEventArgs e)
        {
            Program.SDispatcher.EditionConnectionM.CardInfoReceived -= CardInfoReceivedHandler;
        }

        private void CardInfoReceivedHandler(string name, float score, int votes)
        {
            if (InvokeRequired)
            {
                Invoke(new CardInfoReceivedCallback(CardInfoReceivedHandler), name, score, votes);
            }
            else
            {
                m_cardScoreLabel.Text = "Score : " + score.ToString("0.00");
                m_cardNameLabel.Text = "Nom de la carte : " + name;
                m_votesLabel.Text = "Nombre de votes : " + votes;
            }
        }
    }
}
