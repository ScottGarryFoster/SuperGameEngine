using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace FileHandling
{
    /// <summary>
    /// Wraps XML Document for testing.
    /// </summary>
    public interface IXMLDocument
    {
        /// <summary>
        /// Attempts to load an XML document from a file path.
        /// Does not throw exceptions.
        /// </summary>
        /// <param name="path">Full path to the document. </param>
        /// <param name="xmlDocument">New document if posible. </param>
        /// <param name="exception">If parsing failed this is the given reason. </param>
        /// <returns>True means could parse. </returns>
        bool TryLoadXMLDocumentFromPath(string path, out XmlDocument xmlDocument, out string exception);

        /// <summary>
        /// Attempts to load an XML document from file contents.
        /// Does not throw exceptions.
        /// </summary>
        /// <param name="contents">Contents of a document in XML Format. </param>
        /// <param name="xmlDocument">New document if posible. </param>
        /// <param name="exception">If parsing failed this is the given reason. </param>
        /// <returns>True means could parse. </returns>
        bool TryLoadXMLDocumentFromContents(string contents, out XmlDocument xmlDocument, out string exception);
    }
}
