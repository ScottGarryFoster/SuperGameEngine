using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FatedLauncher
{
    /// <summary>
    /// Provides paths.
    /// </summary>
    public interface IMenuPaths
    {
        /// <summary>
        /// Directory for the configs.
        /// </summary>
        string ConfigDirectory { get; }
    }
}
