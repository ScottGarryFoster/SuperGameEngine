using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FatedLauncher
{
    /// <summary>
    /// Arguments when responding to a option click.
    /// </summary>
    public class MenuEventArguments : EventArgs
    {
        /// <summary>
        /// Button used.
        /// </summary>
        public MouseButtonType Button;
    }
}
