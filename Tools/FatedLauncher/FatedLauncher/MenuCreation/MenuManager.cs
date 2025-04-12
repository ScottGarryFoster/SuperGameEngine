using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FatedLauncher
{
    public class MenuManager
    {
        private ISingleMenu leftClickMenu;

        public MenuManager()
        {
            this.leftClickMenu = new SingleMenu();
        }

        public void ShowMainMenu()
        {
            this.leftClickMenu.Show();
        }
    }
}
