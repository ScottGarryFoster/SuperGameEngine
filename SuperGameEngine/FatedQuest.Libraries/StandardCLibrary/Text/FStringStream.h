#pragma once
#include <sstream>
#include <memory>

namespace StandardCLibrary
{
    /// <summary>
    /// Wraps StringStream and provides more functionality.
    /// </summary>
    class FStringStream
    {
    public:
        FStringStream(std::shared_ptr<std::stringstream> stringStream);
        FStringStream(std::shared_ptr<std::istringstream> stringStream);
        virtual ~FStringStream();

        /// <summary>
        /// Read a char into the stream.
        /// </summary>
        /// <param name="input">Input to read. </param>
        /// <param name="count">Size of the input to use. </param>
        void Read(char* input, std::streamsize count);

        /// <summary>
        /// Seek to exactly this location.
        /// </summary>
        /// <param name="location">Location to seek to. </param>
        void SeekTo(size_t location);

        /// <summary>
        /// Move the current seek location by this amount.
        /// </summary>
        /// <param name="location">Location to move by. </param>
        void MoveSeekBy(size_t location);

        /// <summary>
        /// Get the entire contents of the string.
        /// </summary>
        /// <returns>All the string stream. </returns>
        std::string GetAllString();

        /// <summary>
        /// Get the string from the seeked location.
        /// </summary>
        /// <returns>A string from the seeked location to the end. </returns>
        std::string GetSeekedString();

    private:
        /// <summary>
        /// String Stream this wraps.
        /// </summary>
        std::shared_ptr<std::stringstream> m_stringStream;

        /// <summary>
        /// String Stream this wraps.
        /// This is the Binary In version.
        /// </summary>
        std::shared_ptr<std::istringstream> m_binaryInStringStream;

        /// <summary>
        /// Location seeked to.
        /// This is different than the one given by the standard library
        /// because this allows us to provide strings and never need to
        /// worry about end of lines.
        /// </summary>
        size_t m_customSeekLocation;
    };
}