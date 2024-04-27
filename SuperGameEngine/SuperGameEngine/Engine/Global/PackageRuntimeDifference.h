#pragma once

namespace SuperGameEngine
{
    /// <summary>
    /// Gives some variables which may affect the envrionment the game
    /// is running on, for instance a console vs a pc.
    /// </summary>
    static class PackageRuntimeDifference
    {
    public:
        PackageRuntimeDifference()
        {
            m_doThrow = false;
        }


        /// <summary>
        /// When the application is unable to continue due to null references,
        /// for instance in constructors, do throw exceptions or just assert?
        /// Asserting is always on in debug mode, exception are only on if true.
        /// </summary>
        /// <returns>True means we do throw for exceptions.</returns>
        static bool DoThrowNullReferenceExceptions()
        {
            return m_doThrow;
        }

        static bool SetThrowNullReferenceExceptions(bool newValue)
        {
            m_doThrow = newValue;
        }

    private:
        static bool m_doThrow;
    };
}

