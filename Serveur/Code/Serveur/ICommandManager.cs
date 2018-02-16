using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    interface ICommandManager
    {
        void HandleReceivedData(User user, string receivedData);
    }
}
