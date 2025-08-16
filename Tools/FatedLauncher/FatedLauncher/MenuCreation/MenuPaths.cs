using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FatedLauncher
{
    public class MenuPaths : IMenuPaths
    {
        /// <summary>
        /// Directory for the configs.
        /// </summary>
        public string ConfigDirectory 
        {
            get
            {
                if(!string.IsNullOrWhiteSpace(this.configDirectory))
                {
                    this.configDirectory = GetConfigDirectory();
                }
                
                return configDirectory;
            }
        }

        private string configDirectory;

        private string GetConfigDirectory()
        {
            string exeLocation = System.Reflection.Assembly.GetExecutingAssembly().Location;

            string potentialConfigDirectory = string.Empty;
            try
            {
                potentialConfigDirectory = Path.GetDirectoryName(exeLocation);
                for (int i = 0; i < 5; ++i)
                {
                    foreach (string directory in Directory.GetDirectories(potentialConfigDirectory))
                    {
                        if (string.Equals(Path.GetDirectoryName(directory), "configs", StringComparison.OrdinalIgnoreCase))
                        {
                            return directory;
                        }
                    }

                    potentialConfigDirectory = Path.GetDirectoryName(potentialConfigDirectory);
                }
            }
            catch
            {

            }

            if (!string.IsNullOrWhiteSpace(potentialConfigDirectory))
            {
                return potentialConfigDirectory;
            }

            return exeLocation;
        }
    }
}
