cmake_minimum_required(VERSION 3.20)
project(FatedQuestSolution)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define solution-wide configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug")

# Add subdirectories
add_subdirectory(SuperGameEngine)
add_subdirectory(Engine)
add_subdirectory(EngineTests)
add_subdirectory(Tools)
add_subdirectory(ToolsTests)
add_subdirectory(Input)
add_subdirectory(InputTests)

# Libraries under FatedQuest.Libraries
add_subdirectory(../FatedQuest.Libraries/StandardObjects StandardObjects)
add_subdirectory(../FatedQuest.Libraries/StandardOperations StandardOperations)
add_subdirectory(../FatedQuest.Libraries/StandardOperationsTests StandardOperationsTests)
add_subdirectory(../FatedQuest.Libraries/StandardObjectsTests StandardObjectsTests)
add_subdirectory(../FatedQuest.Libraries/GamePackage GamePackage)
add_subdirectory(../FatedQuest.Libraries/GamePackageTests GamePackageTests)
add_subdirectory(../FatedQuest.Libraries/BinaryOperations BinaryOperations)
add_subdirectory(../FatedQuest.Libraries/XmlDocument XmlDocument)
add_subdirectory(../FatedQuest.Libraries/XmlDocumentTests XmlDocumentTests)
add_subdirectory(../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../FatedQuest.Libraries/Observer Observer)
add_subdirectory(../FatedQuest.Libraries/ClassTypes ClassTypes)
add_subdirectory(../FatedQuest.Libraries/StoredDocument StoredDocument)
add_subdirectory(../FatedQuest.Libraries/SharedEnums SharedEnums)

# Solution Folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(StandardObjects PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(StandardOperations PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(StandardOperationsTests PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(StandardObjectsTests PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(GamePackage PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(GamePackageTests PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(BinaryOperations PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(XmlDocument PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(XmlDocumentTests PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(Logger PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(Observer PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(ClassTypes PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(StoredDocument PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(SharedEnums PROPERTIES FOLDER "FatedQuest.Libraries")
