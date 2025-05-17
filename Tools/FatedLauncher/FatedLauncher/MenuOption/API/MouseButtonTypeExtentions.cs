using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FatedLauncher
{
    public static class MouseButtonTypeExtentions
    {
        public static MouseButtonType ToMouseButtonType(this MouseButtons button)
        {
            switch(button)
            {
                case MouseButtons.Left: return MouseButtonType.Left;
                case MouseButtons.Right: return MouseButtonType.Right;
                case MouseButtons.Middle: return MouseButtonType.Middle;
                case MouseButtons.XButton1: return MouseButtonType.Forward;
                case MouseButtons.XButton2: return MouseButtonType.Back;
            }
            throw new ArgumentOutOfRangeException(nameof(button), $"Unsupported button: {button}");
        }

        public static MouseButtons ToMouseButtonsType(this MouseButtonType button)
        {
            switch (button)
            {
                case MouseButtonType.Left: return MouseButtons.Left;
                case MouseButtonType.Right: return MouseButtons.Right;
                case MouseButtonType.Middle: return MouseButtons.Middle;
                case MouseButtonType.Forward: return MouseButtons.XButton1;
                case MouseButtonType.Back: return MouseButtons.XButton2;
            }
            throw new ArgumentOutOfRangeException(nameof(button), $"Unsupported button: {button}");
        }
    }
}
