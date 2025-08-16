using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace FatedLauncher
{
    public class SingleMenu : ISingleMenu
    {
        /// <summary>
        /// The actual menu.
        /// </summary>
        private ContextMenuStrip menuStrip;

        /// <summary>
        /// The last button pressed on a button.
        /// </summary>
        private MouseButtonType listMouseButton;

        private List<Tuple<ToolStripItem, IMenuOption>> items;

        private List<IMenuOption> options;

        private Timer menuCloseTimer;

        public SingleMenu()
        {
            this.menuStrip = new ContextMenuStrip();
            this.options = new List<IMenuOption>();
            this.items = new List<Tuple<ToolStripItem, IMenuOption>>();

            // For now we'll add some:
            this.options.Add(new TestMenuOption("Test"));
            this.menuStrip.Items.Add(options[0].Label, null, (s, e) => 
                {
                    options[0].OnClick(new MenuEventArguments() { Button = this.listMouseButton });
                });
            this.items.Add(new Tuple<ToolStripItem, IMenuOption>(
                this.menuStrip.Items[this.menuStrip.Items.Count - 1], this.options.Last()));

            

            this.menuStrip.MouseClick += OnMouseDown;
        }

        private void OnMouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            this.listMouseButton = e.Button.ToMouseButtonType();
        }

        /// <summary>
        /// Shows the menu.
        /// </summary>
        /// <param name="position">Location to show the menu.</param>
        public void Show()
        {
            var pos = System.Windows.Forms.Control.MousePosition;
            this.menuStrip.Show(pos);
            StartMenuCloseWatcher();
        }

        /// <summary>
        /// Hide the Menu.
        /// </summary>
        public void Hide()
        {
            this.menuStrip.Close();
        }

        private void StartMenuCloseWatcher()
        {
            if (this.menuCloseTimer == null)
            {
                this.menuCloseTimer = new Timer();
                this.menuCloseTimer.Interval = 100;
                this.menuCloseTimer.Tick += (s, e) =>
                {
                    if (!this.menuStrip.Visible)
                    {
                        menuCloseTimer.Stop();
                        return;
                    }

                    // If left mouse is clicked outside the menu
                    if (System.Windows.Forms.Control.MouseButtons != MouseButtons.None)
                    {
                        var mousePos = System.Windows.Forms.Control.MousePosition;
                        if (!this.menuStrip.Bounds.Contains(mousePos))
                        {
                            this.menuStrip.Close();
                        }

                        if (System.Windows.Forms.Control.MouseButtons == MouseButtons.Middle)
                        {
                            Tuple<ToolStripItem, IMenuOption> selected = this.items.FirstOrDefault(x => x.Item1.Selected);
                            if(selected != null)
                            {
                                selected.Item2.OnClick(new MenuEventArguments() { Button = System.Windows.Forms.Control.MouseButtons.ToMouseButtonType() });
                                this.menuStrip.Close();
                            }
                        }
                    }
                };
            }

            menuCloseTimer?.Start();
        }
    }
}
