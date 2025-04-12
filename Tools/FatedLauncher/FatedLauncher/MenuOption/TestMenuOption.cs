using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

namespace FatedLauncher
{
    public class TestMenuOption : IMenuOption
    {
        /// <summary>
        /// Label to display.
        /// </summary>
        public string Label { get; }

        public TestMenuOption(string label)
        {
            Label = label;
        }

        /// <summary>
        /// Occurs on selection.
        /// </summary>
        /// <param name="args">Arugment to use as context. </param>
        public void OnClick(MenuEventArguments args)
        {
            System.Windows.MessageBox.Show($"You clicked: {Label} with this button: {args.Button}.", "Tray Option");
        }
    }
}
