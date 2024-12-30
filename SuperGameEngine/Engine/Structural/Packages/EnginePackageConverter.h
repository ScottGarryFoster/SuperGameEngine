#pragma once
#include <memory>

namespace SuperGameEngine
{
    class GrandScenePackage;
    class SceneLoadPackage;

    /// <summary>
    /// Converts packages from one form to another.
    /// </summary>
    class EnginePackageConverter
    {
    public:

        static std::shared_ptr<SceneLoadPackage> Convert(const std::shared_ptr<GrandScenePackage>& grandScenePackage);
    };
}
