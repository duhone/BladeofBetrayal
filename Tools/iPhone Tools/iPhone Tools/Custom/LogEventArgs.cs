using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace iPhone_Tools.Custom
{
    public class LogEventArgs : EventArgs
    {
        string _msg;

        public LogEventArgs(string msg)
        {
            _msg = msg;
        }

        public string Msg
        {
            get { return _msg; }
        }
    }
}
