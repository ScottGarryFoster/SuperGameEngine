#include <iostream>
#include <string>
#include "../../../../SuperGameEngine/FatedQuest.Libraries/StandardCLibrary/Text/FString.h"
#include "../../../../SuperGameEngine/FatedQuest.Libraries/StandardCLibrary/Text/StringHelpers.h"
#include "../SuperGameEnginePackager/GamePackage/ProductsPackager.h"
using namespace SuperGameEnginePackager;

using namespace StandardCLibrary;

static void RunProducts();

int main()
{
    std::cout << "Hello World!\n";

    while (true)
    {

        std::string command;
        while (true)
        {
            std::cout << "Please enter a command" << std::endl;

            std::getline(std::cin, command);
            command = StringHelpers::Trim(command);
            StringHelpers::ConvertToLower(command);

            if (command == "products")
            {
                break;
            }

            std::cout << "Could not find command: " << command << std::endl;
        }

        if (command == "products")
        {
            RunProducts();
        }
    }
}

static void RunProducts()
{
    std::cout << "Archiving Products" << std::endl << std::endl;

    std::cout << "Enter a directory in" << std::endl;
    std::string inDirectory;
    while (true)
    {
        std::string inDir;
        std::getline(std::cin, inDir);
        inDirectory = StringHelpers::Trim(inDir);
        if (inDirectory.length() > 1)
        {
            break;
        }
        else
        {
            std::cout << "Error: Directory cannot be empty. " << std::endl;
            std::cout << "Error: Given: " << inDirectory << std::endl;
        }
    }

    std::cout << "Enter a directory out" << std::endl;
    std::string outDirectory;
    while (true)
    {
        std::string outDir;
        std::getline(std::cin, outDir);
        outDirectory = StringHelpers::Trim(outDir);
        if (inDirectory.length() > 1)
        {
            break;
        }
        else
        {
            std::cout << "Error: Directory cannot be empty. " << std::endl;
        }
    }

    ProductsPackager product;
    std::string error = std::string();
    if (!product.PackageProducts(inDirectory, outDirectory, ProductsPackageCompression::BinaryArchive, error))
    {
        std::cout << "ERROR: " << error << std::endl;
    }
    else
    {
        std::cout << "Created" << std::endl;
    }
}