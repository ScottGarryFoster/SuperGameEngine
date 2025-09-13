using System.Drawing;
using System.Windows.Forms;

class DarkModeRenderer : ToolStripProfessionalRenderer
{
    public DarkModeRenderer() : base(new DarkModeColors()) { }

    private class DarkModeColors : ProfessionalColorTable
    {
        /// <summary>
        /// Background.
        /// </summary>
        public override Color ToolStripDropDownBackground => Color.FromArgb(30, 30, 30);

        /// <summary>
        /// On Hover Background.
        /// </summary>
        public override Color MenuItemSelected => Color.FromArgb(60, 60, 60);

        /// <summary>
        /// On Hover Border
        /// </summary>
        public override Color MenuItemBorder => Color.FromArgb(60, 60, 60);

        /// <summary>
        /// Outer border
        /// </summary>
        public override Color ToolStripBorder => Color.FromArgb(30, 30, 30);
    }
}