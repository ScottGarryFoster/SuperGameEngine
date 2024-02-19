#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../../LibraryIncludes.h"

#include "ControllerLayoutCollection.h"
#include "ControllerLayoutFromXML.h"
#include "../../Engine/Basic/FilesAndFolders.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

ControllerLayoutCollection::ControllerLayoutCollection()
{
    m_controllerLayout = new FList<ControllerLayout*>();

    ControllerLayoutFromXML* fromXML = new ControllerLayoutFromXML();
    FString directory = FString(FilesAndFolders::GetProductsFolder()) + "\\Engine\\Input\\ControllerMappings";
    if (Directory::Exists(directory))
    {
        FList<FString> paths = Directory::GetFilepaths(directory);
        for (FString filePath : paths)
        {
            Logger::Info(filePath);
            FString fileContents = File::ReadFileContents(filePath);
            FString error;

            ControllerLayout* extractedLayout = fromXML->CreateFromXML(fileContents, error);
            if (extractedLayout == nullptr)
            {
                Logger::Error(FString(GetTypeName() + ": Could not add controller mapping: ") +
                    filePath + " ERROR: " + error);
            }
            else
            {
                m_controllerLayout->Add(extractedLayout);
            }
        }
    }

    delete fromXML;
}

ControllerLayoutCollection::~ControllerLayoutCollection()
{
    for (ControllerLayout* layout : *m_controllerLayout)
    {
        delete layout;
    }
    delete m_controllerLayout;
}

FList<ControllerLayout*>* ControllerLayoutCollection::GetControllerLayouts()
{
    return m_controllerLayout;
}