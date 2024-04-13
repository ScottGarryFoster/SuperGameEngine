#pragma once
#include "../../../LibraryIncludes.h"
#include "../../../../FatedQuest.Libraries/Logging/Logger.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes the collision responce in an answer.
    /// </summary>
    enum class CollisionAnswerState
    {
        /// <summary>
        /// There is no responce.
        /// </summary>
        Unknown,

        /// <summary>
        /// Collision has started.
        /// </summary>
        OnCollisionBegin,

        /// <summary>
        /// Collision is happening now.
        /// </summary>
        OnCollisionOccuring,

        /// <summary>
        /// Collision has ended.
        /// </summary>
        OnCollisionEnd,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class ECollisionAnswerState : public Object
    {
    public:
        static CollisionAnswerState Min() { return CollisionAnswerState::OnCollisionBegin; }
        static CollisionAnswerState Max() { return CollisionAnswerState::OnCollisionEnd; }
        static CollisionAnswerState* ToArray()
        {
            static CollisionAnswerState arr[] =
            {
                CollisionAnswerState::OnCollisionBegin,
                CollisionAnswerState::OnCollisionOccuring,
                CollisionAnswerState::OnCollisionEnd,
            };
            return arr;
        }

        static std::vector<CollisionAnswerState> ToVector()
        {
            static std::vector<CollisionAnswerState> returnVector =
            {
                CollisionAnswerState::OnCollisionBegin,
                CollisionAnswerState::OnCollisionOccuring,
                CollisionAnswerState::OnCollisionEnd,
            };
            return returnVector;
        }

        static std::string ToString(CollisionAnswerState value)
        {
            switch (value)
            {
            case CollisionAnswerState::Unknown: return "Unknown";
            case CollisionAnswerState::OnCollisionBegin: return "OnCollisionBegin";
            case CollisionAnswerState::OnCollisionOccuring: return "OnCollisionOccuring";
            case CollisionAnswerState::OnCollisionEnd: return "OnCollisionEnd";
            }

            Logger::Assert(NotImplementedException(), FString("ECollisionAnswerState"), FString("ToString"),
                FString("No string value for a CollisionAnswerState requested."));
            return "Unknown";
        }

        static CollisionAnswerState FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (FString(value) == "Unknown") return CollisionAnswerState::Unknown;
                if (FString(value) == "OnCollisionBegin") return CollisionAnswerState::OnCollisionBegin;
                if (FString(value) == "OnCollisionOccuring") return CollisionAnswerState::OnCollisionOccuring;
                if (FString(value) == "OnCollisionEnd") return CollisionAnswerState::OnCollisionEnd;
            }
            else
            {
                if (FString(value).ToLower() == FString("Unknown").ToLower()) return CollisionAnswerState::Unknown;
                if (FString(value).ToLower() == FString("OnCollisionBegin").ToLower()) return CollisionAnswerState::OnCollisionBegin;
                if (FString(value).ToLower() == FString("OnCollisionOccuring").ToLower()) return CollisionAnswerState::OnCollisionOccuring;
                if (FString(value).ToLower() == FString("OnCollisionEnd").ToLower()) return CollisionAnswerState::OnCollisionEnd;
            }

            Logger::Assert(NotImplementedException(), FString("ECollisionAnswerState"), FString("FromString"),
                FString("No Controller value for a CollisionAnswerState requested."));
            return CollisionAnswerState::Unknown;
        }
    };
}