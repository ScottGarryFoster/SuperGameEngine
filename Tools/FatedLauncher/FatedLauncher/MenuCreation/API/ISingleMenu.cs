using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FatedLauncher
{
    /// <summary>
    /// Represents a menu with all of its options.
    /// </summary>
    public interface ISingleMenu
    {
        /// <summary>
        /// Shows the menu.
        /// </summary>
        void Show();

        /// <summary>
        /// Hide the Menu.
        /// </summary>
        void Hide();
    }
}
