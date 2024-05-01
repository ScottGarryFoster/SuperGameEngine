#pragma once

#include "../FatedQuest.Libraries/StandardCLibrary/LibraryIncludes.h"

// C26495 Variable 'testing::internal::Mutex::critical_section_' is uninitialized.Always initialize a member variable(type.6).
#pragma warning(push)
#pragma warning(disable : 26495)
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#pragma warning(pop)

using ::testing::AtLeast;
using ::testing::_;
using ::testing::Return;
using ::testing::Sequence;


//class Turtle 
//{
//        virtual ~Turtle() {}
//    virtual void PenUp() = 0;
//    virtual void PenDown() = 0;
//    virtual void Forward(int distance) = 0;
//    virtual void Turn(int degrees) = 0;
//    virtual void GoTo(int x, int y) = 0;
//    virtual int GetX() const = 0;
//    virtual int GetY() const = 0;
//};
//
//class MockTurtle : public Turtle {
//public:
//        MOCK_METHOD(void, PenUp, (), (override));
//    MOCK_METHOD(void, PenDown, (), (override));
//    MOCK_METHOD(void, Forward, (int distance), (override));
//    MOCK_METHOD(void, Turn, (int degrees), (override));
//    MOCK_METHOD(void, GoTo, (int x, int y), (override));
//    MOCK_METHOD(int, GetX, (), (const, override));
//    MOCK_METHOD(int, GetY, (), (const, override));
//};