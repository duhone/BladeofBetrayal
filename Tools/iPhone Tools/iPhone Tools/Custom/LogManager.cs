using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace iPhone_Tools.Custom
{
    public static class LogManager
    {
        public static event EventHandler<LogEventArgs> LogMessage;

        public static void OnLogMessage(object sender, string message)
        {
            if (LogMessage != null)
                LogMessage(sender, new LogEventArgs(message));
        }
    }
}
