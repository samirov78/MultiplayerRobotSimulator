using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Commun;
using System.IO;
using System.Windows.Forms;

namespace Client
{
    public class EditionConnectionManager
    {
        public event CreateNodeHandler CreateNode;
        public event ModifyNodeHandler ModifyNode;
        public event CardReceivedHandler CardReceived;
        public event CardPlusReceivedHandler CardPlusReceived;
        public event NoCardHandler NoCard;
        public event CardSavedHandler CardSaved;
        public event SelectNoeudsHandler SelectNoeuds;
        public event DeselectNoeudsHandler DeselectNoeuds;
        public event DeleteNoeudsHandler DeleteSelectedNodes;
        public event ScaleSelectionHandler scaleSelection;
        public event InitScaleSelHandler initScaleSelectedNodes;
        public event InitMoveSelHandler initMoveSelectedNodes;
        public event MoveSelHandler MoveSelectedNodes;
        public event DuplicateSelHandler DuplicateSelectedNodes;
        public event BackToInitialScaleHandler BackToInitialScale;
        public event UpdateMySelectedNodesHandler UpdateMySelectedNodes;
        public event PivoterObjetSelectionneHandler PivoterObjetSelectionne;
        public event AnnulerRotationHandler AnnulerRotation;
        public event PivoterObjetsMultiplesHandler PivoterObjetsMultiples;
        public event CardInfoReceivedHandler CardInfoReceived;
        public event SuppDernierNoeudReceivedHandler SuppDernierNoeudReceived;
        public event EjectEditorHandler EjectEditor;
        //initMoveSelectedNodes

        public delegate void SuppDernierNoeudReceivedHandler(string id);
        public delegate void CreateNodeHandler(string data);
        public delegate void ModifyNodeHandler(string data);
        public delegate void CardReceivedHandler(string cardXml);
        public delegate void CardPlusReceivedHandler(string xml, string name, string password, string score);
        public delegate void NoCardHandler(string cardName);
        public delegate void CardSavedHandler(string name, bool onLigne);
        public delegate void SelectNoeudsHandler(string broadcastElements);
        public delegate void DeselectNoeudsHandler(string[] ids);
        public delegate void DeleteNoeudsHandler(string[] ids);
        public delegate void ScaleSelectionHandler(string IdsAndFactor);
        public delegate void InitScaleSelHandler();
        public delegate void InitMoveSelHandler();
        public delegate void MoveSelHandler(string IdsAndDebutFin);
        public delegate void DuplicateSelHandler(string chaineDuplication);
        public delegate void BackToInitialScaleHandler();
        public delegate void UpdateMySelectedNodesHandler(string theIDs);
        public delegate void PivoterObjetSelectionneHandler(string deltaIDs);
        public delegate void PivoterObjetsMultiplesHandler(string deltaIDs);
        public delegate void AnnulerRotationHandler(string theIDs);
        public delegate void CardInfoReceivedHandler(string name, float score, int votes);
        public delegate void EjectEditorHandler();

        Connection m_connection;
        public string commandedCardName = "";

        public EditionConnectionManager(Connection connection)
        {
            m_connection = connection;
        }

        ~EditionConnectionManager()
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
                case (int)Utility.EditionResponce.Card:
                    CardReceived?.Invoke(data); //(content)
                    break;
                case (int)Utility.EditionResponce.CardPlus:
                    //(xml; name; password; score)
                    splitData = data.Split(Utility.CommandSeperator);
                    if (splitData != null && splitData.Length == 4)
                        CardPlusReceived?.Invoke(splitData[0], splitData[1], Utility.Decode(splitData[2]), splitData[3]);
                    break;
                case (int)Utility.EditionResponce.NoCard:
                    NoCard?.Invoke(data);
                    break;
                case (int)Utility.EditionResponce.CardSaved: //()
                    splitData = data.Split(Utility.CommandSeperator);
                    if(splitData != null && splitData.Length == 2)
                        CardSaved?.Invoke(splitData[0], (splitData[1] == "1")?true:false);
                    break;
                case (int)Utility.EditionResponce.CreateNode:
                    if (data == null)
                        return;
                    CreateNode?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.ModifyNode:
                    if (data == null)
                        return;
                    ModifyNode?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.Select: 
                    SelectNoeuds?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.Deselect:
                    splitData = data.Split(';');
                    DeselectNoeuds?.Invoke(splitData); //
                    break;
                case (int)Utility.EditionResponce.DeleteSelection:
                    splitData = data.Split(';');
                    DeleteSelectedNodes?.Invoke(splitData); //
                    break;
                case (int)Utility.EditionResponce.ScaleSelection:
                    scaleSelection?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.InitScaleSel:
                    initScaleSelectedNodes?.Invoke(); //
                    break;
                case (int)Utility.EditionResponce.InitDeplacement:
                    initMoveSelectedNodes?.Invoke(); //
                    break;
                case (int)Utility.EditionResponce.DeplacerSelection:
                    MoveSelectedNodes?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.DuplicateSelection:
                    DuplicateSelectedNodes?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.RetourToInitialScale:
                    BackToInitialScale?.Invoke(); //
                    break;
                case (int)Utility.EditionResponce.UpdateMySelectedNodes:
                    UpdateMySelectedNodes?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.PivoterObjetSelectionne:
                    PivoterObjetSelectionne?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.PivoterObjetsMultiples:
                    PivoterObjetsMultiples?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.AnnulerRotation:
                    AnnulerRotation?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.SuppDernierNoeud:
                    SuppDernierNoeudReceived?.Invoke(data); //
                    break;
                case (int)Utility.EditionResponce.CardInfo:
                    splitData = data.Split(Utility.CommandSeperator);
                    if (splitData != null && splitData.Length == 3)
                    {
                        float score;
                        bool scoreParsed = float.TryParse(splitData[1], out score);
                        if (!scoreParsed)
                            break;
                        int votes;
                        bool votesParsed = int.TryParse(splitData[2], out votes);
                        if (!votesParsed)
                            break;
                        CardInfoReceived?.Invoke(splitData[0], score, votes);
                    }
                    break;
                case (int)Utility.EditionResponce.EjectEditor:
                    EjectEditor?.Invoke();
                    break;
                default:
                    break;
            }
        }

        public void SpreadModifyNode(string data, Boolean phantom = false)
        {
            data += ";" + (phantom ? (int)Utility.DrawState.Phantom : (int)Utility.DrawState.Final);
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.ModifyNode, data);
        }

        public void SpreadCreateNode(string data, Boolean phantom = false)
        {
            data += ";" + (phantom ? (int)Utility.DrawState.Phantom : (int)Utility.DrawState.Final);
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.CreateNode, data);
        }

        public void SaveCard(string name, string file, string password = "", bool onLigne = false)
        {
            string content = File.ReadAllText(file);
            string message = name + Utility.CommandSeperator + content + Utility.CommandSeperator + password + 
                Utility.CommandSeperator + (onLigne?"1":"0");
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.SaveCard, message);
        }

        public void GetCard(string name)
        {
            commandedCardName = name;
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.GetCard, name);
        }

        public void SpreadSelectNodes(string[] ids)
        {
            if (ids == null || ids.Length == 0)
                return;
            string message = "";
            for (int i = 0; i < ids.Length - 1; i++)
                message += ids[i] + ";";
            message += ids[ids.Length - 1];
            Console.WriteLine("spreadSelecNode le message: {0} ", message);
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.Select, message);
        }

        public void SpreadSelectElastique(string[] ids)
        {
            if (ids == null || ids.Length == 0)
                return;
            string message = "";
            for (int i = 0; i < ids.Length - 1; i++)
                message += ids[i] + ";";
            message += ids[ids.Length - 1];
            Console.WriteLine("spreadSelecNode le message: {0} ", message);
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.SelectElastic, message);
        }

        public void SpreadSupprimerSelection()
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.DeleteSelection);
        }


        public void SpreadDeselectNodes()
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.Deselect);
        }

        public void SpreadScaleSelection(string factor)
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.ScaleSelection, factor);
            //
        } //SpreadInitScaleSel

        public void SpreadInitScaleSel()
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.InitScale);
        }

        public void SpreadInitDeplacement()
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.InitDeplacement);
        }
        //SpreadMoveSelection
        public void SpreadMoveSelection(string chaineDebutFin)
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.DeplacerSelection, chaineDebutFin);
        }
        //SpreadDuplicateSelection
        public void SpreadDuplicateSelection(string chaineDuplication)
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.DuplicateSelection, chaineDuplication);
        }
        //SpreadRetourAuscaleInit
        public void SpreadRetourAuscaleInit()
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.RetourToInitialScale);
        }
        //SpreadUpdateMySelectedNodes
        public void SpreadUpdateMySelectedNodes()
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.UpdateMySelectedNodes);
        }
        //SpreadPivoterObjetSelectionne
        public void SpreadPivoterObjetSelectionne(string delta)
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.PivoterObjetSelectionne, delta);
        }

        public void SpreadPivoterObjetsMultiples(string delta)
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.PivoterObjetsMultiples, delta);
        }

        public void SpreadAnnulerRotation()
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.AnnulerRotation);
        }
        
        public void SpreadSuppDernierNoeud(string id)
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.SuppDernierNoeud,id);
        }

        public void SpreadUpdateDuplicatesServer(string chaineDuplication)
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.UpdateDuplicatesServer, chaineDuplication);
        }

        public void GetCards()
        {
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.GetCards);
        }

        public void SendCurrentCardRate(decimal value)
        {
            string message = m_connection.Card + Utility.CommandSeperator + value;
            m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.GetCardRate, message);
        }

        public void GetCardInfo()
        {
            if(m_connection.Card != null && m_connection.Card != "")
                m_connection.Send((int)Utility.BasicCommand.Edition, (int)Utility.EditionCommand.GetCardInfo, m_connection.Card);
        }
    }
}

