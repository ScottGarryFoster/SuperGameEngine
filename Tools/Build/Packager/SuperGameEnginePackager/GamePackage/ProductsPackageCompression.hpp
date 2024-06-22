#pragma once
#include "../LibraryIncludes.h"

namespace SuperGameEnginePackager
{
    /// <summary>
    /// Describes how to package products.
    /// </summary>
    enum class ProductsPackageCompression
    {
        Unknown = -1,

        /// <summary>
        /// In a folder in a raw format.
        /// </summary>
        Uncompressed,

        /// <summary>
        /// In a folder in a binary form.
        /// </summary>
        UncompressedBinary,

        /// <summary>
        /// In an archive with nothing else applied.
        /// </summary>
        Archive,

        /// <summary>
        /// In an archive with binary files.
        /// </summary>
        BinaryArchive,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EProductsPackageCompression : public Object
    {
    public:
        static ProductsPackageCompression Min() { return ProductsPackageCompression::Uncompressed; }
        static ProductsPackageCompression Max() { return ProductsPackageCompression::BinaryArchive; }
        static ProductsPackageCompression* ToArray()
        {
            static ProductsPackageCompression arr[] =
            {
                ProductsPackageCompression::Uncompressed,
                ProductsPackageCompression::UncompressedBinary,
                ProductsPackageCompression::Archive,
                ProductsPackageCompression::BinaryArchive,
            };
            return arr;
        }

        static std::vector<ProductsPackageCompression> ToVector()
        {
            static std::vector<ProductsPackageCompression> returnVector =
            {
                ProductsPackageCompression::Uncompressed,
                ProductsPackageCompression::UncompressedBinary,
                ProductsPackageCompression::Archive,
                ProductsPackageCompression::BinaryArchive,
            };
            return returnVector;
        }

        static std::string ToString(ProductsPackageCompression value)
        {
            switch (value)
            {
            case ProductsPackageCompression::Unknown: return "Unknown";
            case ProductsPackageCompression::Uncompressed: return "Uncompressed";
            case ProductsPackageCompression::UncompressedBinary: return "UncompressedBinary";
            case ProductsPackageCompression::Archive: return "Archive";
            case ProductsPackageCompression::BinaryArchive: return "BinaryArchive";
            }

            Logger::Assert(NotImplementedException(), FString("EProductsPackageCompression"), FString("ToString"),
                FString("No string value for a ProductsPackageCompression requested."));
            return "Unknown";
        }

        static ProductsPackageCompression FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (FString(value) == "Unknown") return ProductsPackageCompression::Unknown;
                if (FString(value) == "Uncompressed") return ProductsPackageCompression::Uncompressed;
                if (FString(value) == "UncompressedBinary") return ProductsPackageCompression::UncompressedBinary;
                if (FString(value) == "Archive") return ProductsPackageCompression::Archive;
                if (FString(value) == "BinaryArchive") return ProductsPackageCompression::BinaryArchive;
            }
            else
            {
                if (FString(value).ToLower() == FString("Unknown").ToLower()) return ProductsPackageCompression::Unknown;
                if (FString(value).ToLower() == FString("Uncompressed").ToLower()) return ProductsPackageCompression::Uncompressed;
                if (FString(value).ToLower() == FString("UncompressedBinary").ToLower()) return ProductsPackageCompression::UncompressedBinary;
                if (FString(value).ToLower() == FString("Archive").ToLower()) return ProductsPackageCompression::Archive;
                if (FString(value).ToLower() == FString("BinaryArchive").ToLower()) return ProductsPackageCompression::BinaryArchive;
            }

            Logger::Assert(NotImplementedException(), FString("EProductsPackageCompression"), FString("FromString"),
                FString("No Controller value for a ProductsPackageCompression requested."));
            return ProductsPackageCompression::Unknown;
        }
    };
}