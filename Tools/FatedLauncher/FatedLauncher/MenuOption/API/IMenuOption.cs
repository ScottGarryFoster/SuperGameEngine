using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FatedLauncher
{
    /// <summary>
    /// A single menu option.
    /// </summary>
    public interface IMenuOption
    {
        /// <summary>
        /// Label to display.
        /// </summary>
        string Label { get; }

        /// <summary>
        /// Occurs on selection.
        /// </summary>
        /// <param name="args">Arugment to use as context. </param>
        void OnClick(MenuEventArguments args);
    }
}
