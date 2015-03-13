using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace iPhone_Tools.Custom
{
    public static class ErrorManager
    {
        public static void ShowError(string msg, Exception ex)
        {
            MessageBox.Show(string.Format("{0} : {1}", msg, ex.ToString()), "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }
    }
}
