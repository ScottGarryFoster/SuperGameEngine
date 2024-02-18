#pragma once
#include <SDL.h>
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes the posible keys pressed on a keyboard.
    /// </summary>
    enum class InputKeyCode
    {
        /// <summary>
        /// None is only used when a scancode does not exist.
        /// Meaning there is not a unique key for the input.
        /// </summary>
        None,
        Backspace,
        Tab,
        Clear,
        Return,
        Pause,
        Escape,
        Space,
        Exclaim,
        Quotedbl,
        Hash,
        Dollar,
        Ampersand,
        Quote,
        LeftParenthesis,
        RightParenthesis,
        Asterisk,
        Plus,
        Comma,
        Minus,
        Period,
        Slash,
        Zero,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Colon,
        Semicolon,
        Less,
        Equals,
        Greater,
        Question,
        At,
        LeftBracket,
        Backslash,
        RightBracket,
        Caret,
        Underscore,
        Backquote,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Delete,
        KeyPadZero,
        KeyPadOne,
        KeyPadTwo,
        KeyPadThree,
        KeyPadFour,
        KeyPadFive,
        KeyPadSix,
        KeyPadSeven,
        KeyPadEight,
        KeyPadNine,
        KeyPadPeriod,
        KeyPadDivide,
        KeyPadMultiply,
        KeyPadMinus,
        KeyPadPlus,
        KeyPadEnter,
        KeyPadEquals,
        Up,
        Down,
        Right,
        Left,
        Insert,
        Home,
        End,
        PageUp,
        PageDown,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        Numlock,
        Capslock,
        Scrollock,
        RightShift,
        LeftShift,
        RightCtrl,
        LeftCtrl,
        RightAlt,
        LeftAlt,
        LeftSuper,
        RightSuper,
        Mode,
        Help,
        Print,
        Sysreq,
        Menu,
        Power,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EInputKeyCode : public Object
    {
    public:
        static InputKeyCode Min() { return InputKeyCode::Backspace; }
        static InputKeyCode Max() { return InputKeyCode::Power; }
        static InputKeyCode* ToArray()
        {
            static InputKeyCode arr[] = 
            {
                InputKeyCode::Backspace,
                InputKeyCode::Tab,
                InputKeyCode::Clear,
                InputKeyCode::Return,
                InputKeyCode::Pause,
                InputKeyCode::Escape,
                InputKeyCode::Space,
                InputKeyCode::Exclaim,
                InputKeyCode::Quotedbl,
                InputKeyCode::Hash,
                InputKeyCode::Dollar,
                InputKeyCode::Ampersand,
                InputKeyCode::Quote,
                InputKeyCode::LeftParenthesis,
                InputKeyCode::RightParenthesis,
                InputKeyCode::Asterisk,
                InputKeyCode::Plus,
                InputKeyCode::Comma,
                InputKeyCode::Minus,
                InputKeyCode::Period,
                InputKeyCode::Slash,
                InputKeyCode::Zero,
                InputKeyCode::One,
                InputKeyCode::Two,
                InputKeyCode::Three,
                InputKeyCode::Four,
                InputKeyCode::Five,
                InputKeyCode::Six,
                InputKeyCode::Seven,
                InputKeyCode::Eight,
                InputKeyCode::Nine,
                InputKeyCode::Colon,
                InputKeyCode::Semicolon,
                InputKeyCode::Less,
                InputKeyCode::Equals,
                InputKeyCode::Greater,
                InputKeyCode::Question,
                InputKeyCode::At,
                InputKeyCode::LeftBracket,
                InputKeyCode::Backslash,
                InputKeyCode::RightBracket,
                InputKeyCode::Caret,
                InputKeyCode::Underscore,
                InputKeyCode::Backquote,
                InputKeyCode::A,
                InputKeyCode::B,
                InputKeyCode::C,
                InputKeyCode::D,
                InputKeyCode::E,
                InputKeyCode::F,
                InputKeyCode::G,
                InputKeyCode::H,
                InputKeyCode::I,
                InputKeyCode::J,
                InputKeyCode::K,
                InputKeyCode::L,
                InputKeyCode::M,
                InputKeyCode::N,
                InputKeyCode::O,
                InputKeyCode::P,
                InputKeyCode::Q,
                InputKeyCode::R,
                InputKeyCode::S,
                InputKeyCode::T,
                InputKeyCode::U,
                InputKeyCode::V,
                InputKeyCode::W,
                InputKeyCode::X,
                InputKeyCode::Y,
                InputKeyCode::Z,
                InputKeyCode::Delete,
                InputKeyCode::KeyPadZero,
                InputKeyCode::KeyPadOne,
                InputKeyCode::KeyPadTwo,
                InputKeyCode::KeyPadThree,
                InputKeyCode::KeyPadFour,
                InputKeyCode::KeyPadFive,
                InputKeyCode::KeyPadSix,
                InputKeyCode::KeyPadSeven,
                InputKeyCode::KeyPadEight,
                InputKeyCode::KeyPadNine,
                InputKeyCode::KeyPadPeriod,
                InputKeyCode::KeyPadDivide,
                InputKeyCode::KeyPadMultiply,
                InputKeyCode::KeyPadMinus,
                InputKeyCode::KeyPadPlus,
                InputKeyCode::KeyPadEnter,
                InputKeyCode::KeyPadEquals,
                InputKeyCode::Up,
                InputKeyCode::Down,
                InputKeyCode::Right,
                InputKeyCode::Left,
                InputKeyCode::Insert,
                InputKeyCode::Home,
                InputKeyCode::End,
                InputKeyCode::PageUp,
                InputKeyCode::PageDown,
                InputKeyCode::F1,
                InputKeyCode::F2,
                InputKeyCode::F3,
                InputKeyCode::F4,
                InputKeyCode::F5,
                InputKeyCode::F6,
                InputKeyCode::F7,
                InputKeyCode::F8,
                InputKeyCode::F9,
                InputKeyCode::F10,
                InputKeyCode::F11,
                InputKeyCode::F12,
                InputKeyCode::F13,
                InputKeyCode::F14,
                InputKeyCode::F15,
                InputKeyCode::Numlock,
                InputKeyCode::Capslock,
                InputKeyCode::Scrollock,
                InputKeyCode::RightShift,
                InputKeyCode::LeftShift,
                InputKeyCode::RightCtrl,
                InputKeyCode::LeftCtrl,
                InputKeyCode::RightAlt,
                InputKeyCode::LeftAlt,
                InputKeyCode::LeftSuper,
                InputKeyCode::RightSuper,
                InputKeyCode::Mode,
                InputKeyCode::Help,
                InputKeyCode::Print,
                InputKeyCode::Sysreq,
                InputKeyCode::Menu,
                InputKeyCode::Power,
            };
            return arr;
        }

        static std::vector<InputKeyCode> ToVector()
        {
            static std::vector<InputKeyCode> returnVector = 
            {
                InputKeyCode::Backspace,
                InputKeyCode::Tab,
                InputKeyCode::Clear,
                InputKeyCode::Return,
                InputKeyCode::Pause,
                InputKeyCode::Escape,
                InputKeyCode::Space,
                InputKeyCode::Exclaim,
                InputKeyCode::Quotedbl,
                InputKeyCode::Hash,
                InputKeyCode::Dollar,
                InputKeyCode::Ampersand,
                InputKeyCode::Quote,
                InputKeyCode::LeftParenthesis,
                InputKeyCode::RightParenthesis,
                InputKeyCode::Asterisk,
                InputKeyCode::Plus,
                InputKeyCode::Comma,
                InputKeyCode::Minus,
                InputKeyCode::Period,
                InputKeyCode::Slash,
                InputKeyCode::Zero,
                InputKeyCode::One,
                InputKeyCode::Two,
                InputKeyCode::Three,
                InputKeyCode::Four,
                InputKeyCode::Five,
                InputKeyCode::Six,
                InputKeyCode::Seven,
                InputKeyCode::Eight,
                InputKeyCode::Nine,
                InputKeyCode::Colon,
                InputKeyCode::Semicolon,
                InputKeyCode::Less,
                InputKeyCode::Equals,
                InputKeyCode::Greater,
                InputKeyCode::Question,
                InputKeyCode::At,
                InputKeyCode::LeftBracket,
                InputKeyCode::Backslash,
                InputKeyCode::RightBracket,
                InputKeyCode::Caret,
                InputKeyCode::Underscore,
                InputKeyCode::Backquote,
                InputKeyCode::A,
                InputKeyCode::B,
                InputKeyCode::C,
                InputKeyCode::D,
                InputKeyCode::E,
                InputKeyCode::F,
                InputKeyCode::G,
                InputKeyCode::H,
                InputKeyCode::I,
                InputKeyCode::J,
                InputKeyCode::K,
                InputKeyCode::L,
                InputKeyCode::M,
                InputKeyCode::N,
                InputKeyCode::O,
                InputKeyCode::P,
                InputKeyCode::Q,
                InputKeyCode::R,
                InputKeyCode::S,
                InputKeyCode::T,
                InputKeyCode::U,
                InputKeyCode::V,
                InputKeyCode::W,
                InputKeyCode::X,
                InputKeyCode::Y,
                InputKeyCode::Z,
                InputKeyCode::Delete,
                InputKeyCode::KeyPadZero,
                InputKeyCode::KeyPadOne,
                InputKeyCode::KeyPadTwo,
                InputKeyCode::KeyPadThree,
                InputKeyCode::KeyPadFour,
                InputKeyCode::KeyPadFive,
                InputKeyCode::KeyPadSix,
                InputKeyCode::KeyPadSeven,
                InputKeyCode::KeyPadEight,
                InputKeyCode::KeyPadNine,
                InputKeyCode::KeyPadPeriod,
                InputKeyCode::KeyPadDivide,
                InputKeyCode::KeyPadMultiply,
                InputKeyCode::KeyPadMinus,
                InputKeyCode::KeyPadPlus,
                InputKeyCode::KeyPadEnter,
                InputKeyCode::KeyPadEquals,
                InputKeyCode::Up,
                InputKeyCode::Down,
                InputKeyCode::Right,
                InputKeyCode::Left,
                InputKeyCode::Insert,
                InputKeyCode::Home,
                InputKeyCode::End,
                InputKeyCode::PageUp,
                InputKeyCode::PageDown,
                InputKeyCode::F1,
                InputKeyCode::F2,
                InputKeyCode::F3,
                InputKeyCode::F4,
                InputKeyCode::F5,
                InputKeyCode::F6,
                InputKeyCode::F7,
                InputKeyCode::F8,
                InputKeyCode::F9,
                InputKeyCode::F10,
                InputKeyCode::F11,
                InputKeyCode::F12,
                InputKeyCode::F13,
                InputKeyCode::F14,
                InputKeyCode::F15,
                InputKeyCode::Numlock,
                InputKeyCode::Capslock,
                InputKeyCode::Scrollock,
                InputKeyCode::RightShift,
                InputKeyCode::LeftShift,
                InputKeyCode::RightCtrl,
                InputKeyCode::LeftCtrl,
                InputKeyCode::RightAlt,
                InputKeyCode::LeftAlt,
                InputKeyCode::LeftSuper,
                InputKeyCode::RightSuper,
                InputKeyCode::Mode,
                InputKeyCode::Help,
                InputKeyCode::Print,
                InputKeyCode::Sysreq,
                InputKeyCode::Menu,
                InputKeyCode::Power,
            };

            return returnVector;
        }

        static std::string ToString(InputKeyCode value)
        {
            switch (value)
            {
                case InputKeyCode::None: return "None";
                case InputKeyCode::Backspace: return "Backspace";
                case InputKeyCode::Tab: return "Tab";
                case InputKeyCode::Clear: return "Clear";
                case InputKeyCode::Return: return "Return";
                case InputKeyCode::Pause: return "Pause";
                case InputKeyCode::Escape: return "Escape";
                case InputKeyCode::Space: return "Space";
                case InputKeyCode::Exclaim: return "Exclaim";
                case InputKeyCode::Quotedbl: return "Quotedbl";
                case InputKeyCode::Hash: return "Hash";
                case InputKeyCode::Dollar: return "Dollar";
                case InputKeyCode::Ampersand: return "Ampersand";
                case InputKeyCode::Quote: return "Quote";
                case InputKeyCode::LeftParenthesis: return "LeftParenthesis";
                case InputKeyCode::RightParenthesis: return "RightParenthesis";
                case InputKeyCode::Asterisk: return "Asterisk";
                case InputKeyCode::Plus: return "Plus";
                case InputKeyCode::Comma: return "Comma";
                case InputKeyCode::Minus: return "Minus";
                case InputKeyCode::Period: return "Period";
                case InputKeyCode::Slash: return "Slash";
                case InputKeyCode::Zero: return "Zero";
                case InputKeyCode::One: return "One";
                case InputKeyCode::Two: return "Two";
                case InputKeyCode::Three: return "Three";
                case InputKeyCode::Four: return "Four";
                case InputKeyCode::Five: return "Five";
                case InputKeyCode::Six: return "Six";
                case InputKeyCode::Seven: return "Seven";
                case InputKeyCode::Eight: return "Eight";
                case InputKeyCode::Nine: return "Nine";
                case InputKeyCode::Colon: return "Colon";
                case InputKeyCode::Semicolon: return "Semicolon";
                case InputKeyCode::Less: return "Less";
                case InputKeyCode::Equals: return "Equals";
                case InputKeyCode::Greater: return "Greater";
                case InputKeyCode::Question: return "Question";
                case InputKeyCode::At: return "At";
                case InputKeyCode::LeftBracket: return "LeftBracket";
                case InputKeyCode::Backslash: return "Backslash";
                case InputKeyCode::RightBracket: return "RightBracket";
                case InputKeyCode::Caret: return "Caret";
                case InputKeyCode::Underscore: return "Underscore";
                case InputKeyCode::Backquote: return "Backquote";
                case InputKeyCode::A: return "A";
                case InputKeyCode::B: return "B";
                case InputKeyCode::C: return "C";
                case InputKeyCode::D: return "D";
                case InputKeyCode::E: return "E";
                case InputKeyCode::F: return "F";
                case InputKeyCode::G: return "G";
                case InputKeyCode::H: return "H";
                case InputKeyCode::I: return "I";
                case InputKeyCode::J: return "J";
                case InputKeyCode::K: return "K";
                case InputKeyCode::L: return "L";
                case InputKeyCode::M: return "M";
                case InputKeyCode::N: return "N";
                case InputKeyCode::O: return "O";
                case InputKeyCode::P: return "P";
                case InputKeyCode::Q: return "Q";
                case InputKeyCode::R: return "R";
                case InputKeyCode::S: return "S";
                case InputKeyCode::T: return "T";
                case InputKeyCode::U: return "U";
                case InputKeyCode::V: return "V";
                case InputKeyCode::W: return "W";
                case InputKeyCode::X: return "X";
                case InputKeyCode::Y: return "Y";
                case InputKeyCode::Z: return "Z";
                case InputKeyCode::Delete: return "Delete";
                case InputKeyCode::KeyPadZero: return "KeyPadZero";
                case InputKeyCode::KeyPadOne: return "KeyPadOne";
                case InputKeyCode::KeyPadTwo: return "KeyPadTwo";
                case InputKeyCode::KeyPadThree: return "KeyPadThree";
                case InputKeyCode::KeyPadFour: return "KeyPadFour";
                case InputKeyCode::KeyPadFive: return "KeyPadFive";
                case InputKeyCode::KeyPadSix: return "KeyPadSix";
                case InputKeyCode::KeyPadSeven: return "KeyPadSeven";
                case InputKeyCode::KeyPadEight: return "KeyPadEight";
                case InputKeyCode::KeyPadNine: return "KeyPadNine";
                case InputKeyCode::KeyPadPeriod: return "KeyPadPeriod";
                case InputKeyCode::KeyPadMultiply: return "KeyPadMultiply";
                case InputKeyCode::KeyPadMinus: return "KeyPadMinus";
                case InputKeyCode::KeyPadPlus: return "KeyPadPlus";
                case InputKeyCode::KeyPadEnter: return "KeyPadEnter";
                case InputKeyCode::KeyPadEquals: return "KeyPadEquals";
                case InputKeyCode::Up: return "Up";
                case InputKeyCode::Down: return "Down";
                case InputKeyCode::Right: return "Right";
                case InputKeyCode::Left: return "Left";
                case InputKeyCode::Insert: return "Insert";
                case InputKeyCode::Home: return "Home";
                case InputKeyCode::End: return "End";
                case InputKeyCode::PageUp: return "PageUp";
                case InputKeyCode::PageDown: return "PageDown";
                case InputKeyCode::F1: return "F1";
                case InputKeyCode::F2: return "F2";
                case InputKeyCode::F3: return "F3";
                case InputKeyCode::F4: return "F4";
                case InputKeyCode::F5: return "F5";
                case InputKeyCode::F6: return "F6";
                case InputKeyCode::F7: return "F7";
                case InputKeyCode::F8: return "F8";
                case InputKeyCode::F9: return "F9";
                case InputKeyCode::F10: return "F10";
                case InputKeyCode::F11: return "F11";
                case InputKeyCode::F12: return "F12";
                case InputKeyCode::F13: return "F13";
                case InputKeyCode::F14: return "F14";
                case InputKeyCode::F15: return "F15";
                case InputKeyCode::Numlock: return "Numlock";
                case InputKeyCode::Capslock: return "Capslock";
                case InputKeyCode::Scrollock: return "Scrollock";
                case InputKeyCode::RightShift: return "RightShift";
                case InputKeyCode::LeftShift: return "LeftShift";
                case InputKeyCode::RightCtrl: return "RightCtrl";
                case InputKeyCode::LeftCtrl: return "LeftCtrl";
                case InputKeyCode::RightAlt: return "RightAlt";
                case InputKeyCode::LeftAlt: return "LeftAlt";
                case InputKeyCode::LeftSuper: return "LeftSuper";
                case InputKeyCode::RightSuper: return "RightSuper";
                case InputKeyCode::Mode: return "Mode";
                case InputKeyCode::Help: return "Help";
                case InputKeyCode::Print: return "Print";
                case InputKeyCode::Sysreq: return "Sysreq";
                case InputKeyCode::Menu: return "Menu";
                case InputKeyCode::Power: return "Power";
            }

            Logger::Assert(NotImplementedException(), FString("EInputKeyCode"), FString("ToString"),
                FString("No string value for a Input Key Code requested."));
            return "None";
        }

        static InputKeyCode FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                FString stringValue = value;
                if (stringValue == "None") return InputKeyCode::None;
                if (stringValue == "Backspace") return InputKeyCode::Backspace;
                if (stringValue == "Tab") return InputKeyCode::Tab;
                if (stringValue == "Clear") return InputKeyCode::Clear;
                if (stringValue == "Return") return InputKeyCode::Return;
                if (stringValue == "Pause") return InputKeyCode::Pause;
                if (stringValue == "Escape") return InputKeyCode::Escape;
                if (stringValue == "Space") return InputKeyCode::Space;
                if (stringValue == "Exclaim") return InputKeyCode::Exclaim;
                if (stringValue == "Quotedbl") return InputKeyCode::Quotedbl;
                if (stringValue == "Hash") return InputKeyCode::Hash;
                if (stringValue == "Dollar") return InputKeyCode::Dollar;
                if (stringValue == "Ampersand") return InputKeyCode::Ampersand;
                if (stringValue == "Quote") return InputKeyCode::Quote;
                if (stringValue == "LeftParenthesis") return InputKeyCode::LeftParenthesis;
                if (stringValue == "RightParenthesis") return InputKeyCode::RightParenthesis;
                if (stringValue == "Asterisk") return InputKeyCode::Asterisk;
                if (stringValue == "Plus") return InputKeyCode::Plus;
                if (stringValue == "Comma") return InputKeyCode::Comma;
                if (stringValue == "Minus") return InputKeyCode::Minus;
                if (stringValue == "Period") return InputKeyCode::Period;
                if (stringValue == "Slash") return InputKeyCode::Slash;
                if (stringValue == "Zero") return InputKeyCode::Zero;
                if (stringValue == "One") return InputKeyCode::One;
                if (stringValue == "Two") return InputKeyCode::Two;
                if (stringValue == "Three") return InputKeyCode::Three;
                if (stringValue == "Four") return InputKeyCode::Four;
                if (stringValue == "Five") return InputKeyCode::Five;
                if (stringValue == "Six") return InputKeyCode::Six;
                if (stringValue == "Seven") return InputKeyCode::Seven;
                if (stringValue == "Eight") return InputKeyCode::Eight;
                if (stringValue == "Nine") return InputKeyCode::Nine;
                if (stringValue == "Colon") return InputKeyCode::Colon;
                if (stringValue == "Semicolon") return InputKeyCode::Semicolon;
                if (stringValue == "Less") return InputKeyCode::Less;
                if (stringValue == "Equals") return InputKeyCode::Equals;
                if (stringValue == "Greater") return InputKeyCode::Greater;
                if (stringValue == "Question") return InputKeyCode::Question;
                if (stringValue == "At") return InputKeyCode::At;
                if (stringValue == "LeftBracket") return InputKeyCode::LeftBracket;
                if (stringValue == "Backslash") return InputKeyCode::Backslash;
                if (stringValue == "RightBracket") return InputKeyCode::RightBracket;
                if (stringValue == "Caret") return InputKeyCode::Caret;
                if (stringValue == "Underscore") return InputKeyCode::Underscore;
                if (stringValue == "Backquote") return InputKeyCode::Backquote;
                if (stringValue == "A") return InputKeyCode::A;
                if (stringValue == "B") return InputKeyCode::B;
                if (stringValue == "C") return InputKeyCode::C;
                if (stringValue == "D") return InputKeyCode::D;
                if (stringValue == "E") return InputKeyCode::E;
                if (stringValue == "F") return InputKeyCode::F;
                if (stringValue == "G") return InputKeyCode::G;
                if (stringValue == "H") return InputKeyCode::H;
                if (stringValue == "I") return InputKeyCode::I;
                if (stringValue == "J") return InputKeyCode::J;
                if (stringValue == "K") return InputKeyCode::K;
                if (stringValue == "L") return InputKeyCode::L;
                if (stringValue == "M") return InputKeyCode::M;
                if (stringValue == "N") return InputKeyCode::N;
                if (stringValue == "O") return InputKeyCode::O;
                if (stringValue == "P") return InputKeyCode::P;
                if (stringValue == "Q") return InputKeyCode::Q;
                if (stringValue == "R") return InputKeyCode::R;
                if (stringValue == "S") return InputKeyCode::S;
                if (stringValue == "T") return InputKeyCode::T;
                if (stringValue == "U") return InputKeyCode::U;
                if (stringValue == "V") return InputKeyCode::V;
                if (stringValue == "W") return InputKeyCode::W;
                if (stringValue == "X") return InputKeyCode::X;
                if (stringValue == "Y") return InputKeyCode::Y;
                if (stringValue == "Z") return InputKeyCode::Z;
                if (stringValue == "Delete") return InputKeyCode::Delete;
                if (stringValue == "KeyPadZero") return InputKeyCode::KeyPadZero;
                if (stringValue == "KeyPadOne") return InputKeyCode::KeyPadOne;
                if (stringValue == "KeyPadTwo") return InputKeyCode::KeyPadTwo;
                if (stringValue == "KeyPadThree") return InputKeyCode::KeyPadThree;
                if (stringValue == "KeyPadFour") return InputKeyCode::KeyPadFour;
                if (stringValue == "KeyPadFive") return InputKeyCode::KeyPadFive;
                if (stringValue == "KeyPadSix") return InputKeyCode::KeyPadSix;
                if (stringValue == "KeyPadSeven") return InputKeyCode::KeyPadSeven;
                if (stringValue == "KeyPadEight") return InputKeyCode::KeyPadEight;
                if (stringValue == "KeyPadNine") return InputKeyCode::KeyPadNine;
                if (stringValue == "KeyPadPeriod") return InputKeyCode::KeyPadPeriod;
                if (stringValue == "KeyPadMultiply") return InputKeyCode::KeyPadMultiply;
                if (stringValue == "KeyPadMinus") return InputKeyCode::KeyPadMinus;
                if (stringValue == "KeyPadPlus") return InputKeyCode::KeyPadPlus;
                if (stringValue == "KeyPadEnter") return InputKeyCode::KeyPadEnter;
                if (stringValue == "KeyPadEquals") return InputKeyCode::KeyPadEquals;
                if (stringValue == "Up") return InputKeyCode::Up;
                if (stringValue == "Down") return InputKeyCode::Down;
                if (stringValue == "Right") return InputKeyCode::Right;
                if (stringValue == "Left") return InputKeyCode::Left;
                if (stringValue == "Insert") return InputKeyCode::Insert;
                if (stringValue == "Home") return InputKeyCode::Home;
                if (stringValue == "End") return InputKeyCode::End;
                if (stringValue == "PageUp") return InputKeyCode::PageUp;
                if (stringValue == "PageDown") return InputKeyCode::PageDown;
                if (stringValue == "F1") return InputKeyCode::F1;
                if (stringValue == "F2") return InputKeyCode::F2;
                if (stringValue == "F3") return InputKeyCode::F3;
                if (stringValue == "F4") return InputKeyCode::F4;
                if (stringValue == "F5") return InputKeyCode::F5;
                if (stringValue == "F6") return InputKeyCode::F6;
                if (stringValue == "F7") return InputKeyCode::F7;
                if (stringValue == "F8") return InputKeyCode::F8;
                if (stringValue == "F9") return InputKeyCode::F9;
                if (stringValue == "F10") return InputKeyCode::F10;
                if (stringValue == "F11") return InputKeyCode::F11;
                if (stringValue == "F12") return InputKeyCode::F12;
                if (stringValue == "F13") return InputKeyCode::F13;
                if (stringValue == "F14") return InputKeyCode::F14;
                if (stringValue == "F15") return InputKeyCode::F15;
                if (stringValue == "Numlock") return InputKeyCode::Numlock;
                if (stringValue == "Capslock") return InputKeyCode::Capslock;
                if (stringValue == "Scrollock") return InputKeyCode::Scrollock;
                if (stringValue == "RightShift") return InputKeyCode::RightShift;
                if (stringValue == "LeftShift") return InputKeyCode::LeftShift;
                if (stringValue == "RightCtrl") return InputKeyCode::RightCtrl;
                if (stringValue == "LeftCtrl") return InputKeyCode::LeftCtrl;
                if (stringValue == "RightAlt") return InputKeyCode::RightAlt;
                if (stringValue == "LeftAlt") return InputKeyCode::LeftAlt;
                if (stringValue == "LeftSuper") return InputKeyCode::LeftSuper;
                if (stringValue == "RightSuper") return InputKeyCode::RightSuper;
                if (stringValue == "Mode") return InputKeyCode::Mode;
                if (stringValue == "Help") return InputKeyCode::Help;
                if (stringValue == "Print") return InputKeyCode::Print;
                if (stringValue == "Sysreq") return InputKeyCode::Sysreq;
                if (stringValue == "Menu") return InputKeyCode::Menu;
                if (stringValue == "Power") return InputKeyCode::Power;
            }
            else
            {
                FString stringValueLower = value;
                stringValueLower.ConvertToLower();
                if (stringValueLower == FString("None").ToLower()) return InputKeyCode::None;
                if (stringValueLower == FString("Backspace").ToLower()) return InputKeyCode::Backspace;
                if (stringValueLower == FString("Tab").ToLower()) return InputKeyCode::Tab;
                if (stringValueLower == FString("Clear").ToLower()) return InputKeyCode::Clear;
                if (stringValueLower == FString("Return").ToLower()) return InputKeyCode::Return;
                if (stringValueLower == FString("Pause").ToLower()) return InputKeyCode::Pause;
                if (stringValueLower == FString("Escape").ToLower()) return InputKeyCode::Escape;
                if (stringValueLower == FString("Space").ToLower()) return InputKeyCode::Space;
                if (stringValueLower == FString("Exclaim").ToLower()) return InputKeyCode::Exclaim;
                if (stringValueLower == FString("Quotedbl").ToLower()) return InputKeyCode::Quotedbl;
                if (stringValueLower == FString("Hash").ToLower()) return InputKeyCode::Hash;
                if (stringValueLower == FString("Dollar").ToLower()) return InputKeyCode::Dollar;
                if (stringValueLower == FString("Ampersand").ToLower()) return InputKeyCode::Ampersand;
                if (stringValueLower == FString("Quote").ToLower()) return InputKeyCode::Quote;
                if (stringValueLower == FString("LeftParenthesis").ToLower()) return InputKeyCode::LeftParenthesis;
                if (stringValueLower == FString("RightParenthesis").ToLower()) return InputKeyCode::RightParenthesis;
                if (stringValueLower == FString("Asterisk").ToLower()) return InputKeyCode::Asterisk;
                if (stringValueLower == FString("Plus").ToLower()) return InputKeyCode::Plus;
                if (stringValueLower == FString("Comma").ToLower()) return InputKeyCode::Comma;
                if (stringValueLower == FString("Minus").ToLower()) return InputKeyCode::Minus;
                if (stringValueLower == FString("Period").ToLower()) return InputKeyCode::Period;
                if (stringValueLower == FString("Slash").ToLower()) return InputKeyCode::Slash;
                if (stringValueLower == FString("Zero").ToLower()) return InputKeyCode::Zero;
                if (stringValueLower == FString("One").ToLower()) return InputKeyCode::One;
                if (stringValueLower == FString("Two").ToLower()) return InputKeyCode::Two;
                if (stringValueLower == FString("Three").ToLower()) return InputKeyCode::Three;
                if (stringValueLower == FString("Four").ToLower()) return InputKeyCode::Four;
                if (stringValueLower == FString("Five").ToLower()) return InputKeyCode::Five;
                if (stringValueLower == FString("Six").ToLower()) return InputKeyCode::Six;
                if (stringValueLower == FString("Seven").ToLower()) return InputKeyCode::Seven;
                if (stringValueLower == FString("Eight").ToLower()) return InputKeyCode::Eight;
                if (stringValueLower == FString("Nine").ToLower()) return InputKeyCode::Nine;
                if (stringValueLower == FString("Colon").ToLower()) return InputKeyCode::Colon;
                if (stringValueLower == FString("Semicolon").ToLower()) return InputKeyCode::Semicolon;
                if (stringValueLower == FString("Less").ToLower()) return InputKeyCode::Less;
                if (stringValueLower == FString("Equals").ToLower()) return InputKeyCode::Equals;
                if (stringValueLower == FString("Greater").ToLower()) return InputKeyCode::Greater;
                if (stringValueLower == FString("Question").ToLower()) return InputKeyCode::Question;
                if (stringValueLower == FString("At").ToLower()) return InputKeyCode::At;
                if (stringValueLower == FString("LeftBracket").ToLower()) return InputKeyCode::LeftBracket;
                if (stringValueLower == FString("Backslash").ToLower()) return InputKeyCode::Backslash;
                if (stringValueLower == FString("RightBracket").ToLower()) return InputKeyCode::RightBracket;
                if (stringValueLower == FString("Caret").ToLower()) return InputKeyCode::Caret;
                if (stringValueLower == FString("Underscore").ToLower()) return InputKeyCode::Underscore;
                if (stringValueLower == FString("Backquote").ToLower()) return InputKeyCode::Backquote;
                if (stringValueLower == FString("A").ToLower()) return InputKeyCode::A;
                if (stringValueLower == FString("B").ToLower()) return InputKeyCode::B;
                if (stringValueLower == FString("C").ToLower()) return InputKeyCode::C;
                if (stringValueLower == FString("D").ToLower()) return InputKeyCode::D;
                if (stringValueLower == FString("E").ToLower()) return InputKeyCode::E;
                if (stringValueLower == FString("F").ToLower()) return InputKeyCode::F;
                if (stringValueLower == FString("G").ToLower()) return InputKeyCode::G;
                if (stringValueLower == FString("H").ToLower()) return InputKeyCode::H;
                if (stringValueLower == FString("I").ToLower()) return InputKeyCode::I;
                if (stringValueLower == FString("J").ToLower()) return InputKeyCode::J;
                if (stringValueLower == FString("K").ToLower()) return InputKeyCode::K;
                if (stringValueLower == FString("L").ToLower()) return InputKeyCode::L;
                if (stringValueLower == FString("M").ToLower()) return InputKeyCode::M;
                if (stringValueLower == FString("N").ToLower()) return InputKeyCode::N;
                if (stringValueLower == FString("O").ToLower()) return InputKeyCode::O;
                if (stringValueLower == FString("P").ToLower()) return InputKeyCode::P;
                if (stringValueLower == FString("Q").ToLower()) return InputKeyCode::Q;
                if (stringValueLower == FString("R").ToLower()) return InputKeyCode::R;
                if (stringValueLower == FString("S").ToLower()) return InputKeyCode::S;
                if (stringValueLower == FString("T").ToLower()) return InputKeyCode::T;
                if (stringValueLower == FString("U").ToLower()) return InputKeyCode::U;
                if (stringValueLower == FString("V").ToLower()) return InputKeyCode::V;
                if (stringValueLower == FString("W").ToLower()) return InputKeyCode::W;
                if (stringValueLower == FString("X").ToLower()) return InputKeyCode::X;
                if (stringValueLower == FString("Y").ToLower()) return InputKeyCode::Y;
                if (stringValueLower == FString("Z").ToLower()) return InputKeyCode::Z;
                if (stringValueLower == FString("Delete").ToLower()) return InputKeyCode::Delete;
                if (stringValueLower == FString("KeyPadZero").ToLower()) return InputKeyCode::KeyPadZero;
                if (stringValueLower == FString("KeyPadOne").ToLower()) return InputKeyCode::KeyPadOne;
                if (stringValueLower == FString("KeyPadTwo").ToLower()) return InputKeyCode::KeyPadTwo;
                if (stringValueLower == FString("KeyPadThree").ToLower()) return InputKeyCode::KeyPadThree;
                if (stringValueLower == FString("KeyPadFour").ToLower()) return InputKeyCode::KeyPadFour;
                if (stringValueLower == FString("KeyPadFive").ToLower()) return InputKeyCode::KeyPadFive;
                if (stringValueLower == FString("KeyPadSix").ToLower()) return InputKeyCode::KeyPadSix;
                if (stringValueLower == FString("KeyPadSeven").ToLower()) return InputKeyCode::KeyPadSeven;
                if (stringValueLower == FString("KeyPadEight").ToLower()) return InputKeyCode::KeyPadEight;
                if (stringValueLower == FString("KeyPadNine").ToLower()) return InputKeyCode::KeyPadNine;
                if (stringValueLower == FString("KeyPadPeriod").ToLower()) return InputKeyCode::KeyPadPeriod;
                if (stringValueLower == FString("KeyPadMultiply").ToLower()) return InputKeyCode::KeyPadMultiply;
                if (stringValueLower == FString("KeyPadMinus").ToLower()) return InputKeyCode::KeyPadMinus;
                if (stringValueLower == FString("KeyPadPlus").ToLower()) return InputKeyCode::KeyPadPlus;
                if (stringValueLower == FString("KeyPadEnter").ToLower()) return InputKeyCode::KeyPadEnter;
                if (stringValueLower == FString("KeyPadEquals").ToLower()) return InputKeyCode::KeyPadEquals;
                if (stringValueLower == FString("Up").ToLower()) return InputKeyCode::Up;
                if (stringValueLower == FString("Down").ToLower()) return InputKeyCode::Down;
                if (stringValueLower == FString("Right").ToLower()) return InputKeyCode::Right;
                if (stringValueLower == FString("Left").ToLower()) return InputKeyCode::Left;
                if (stringValueLower == FString("Insert").ToLower()) return InputKeyCode::Insert;
                if (stringValueLower == FString("Home").ToLower()) return InputKeyCode::Home;
                if (stringValueLower == FString("End").ToLower()) return InputKeyCode::End;
                if (stringValueLower == FString("PageUp").ToLower()) return InputKeyCode::PageUp;
                if (stringValueLower == FString("PageDown").ToLower()) return InputKeyCode::PageDown;
                if (stringValueLower == FString("F1").ToLower()) return InputKeyCode::F1;
                if (stringValueLower == FString("F2").ToLower()) return InputKeyCode::F2;
                if (stringValueLower == FString("F3").ToLower()) return InputKeyCode::F3;
                if (stringValueLower == FString("F4").ToLower()) return InputKeyCode::F4;
                if (stringValueLower == FString("F5").ToLower()) return InputKeyCode::F5;
                if (stringValueLower == FString("F6").ToLower()) return InputKeyCode::F6;
                if (stringValueLower == FString("F7").ToLower()) return InputKeyCode::F7;
                if (stringValueLower == FString("F8").ToLower()) return InputKeyCode::F8;
                if (stringValueLower == FString("F9").ToLower()) return InputKeyCode::F9;
                if (stringValueLower == FString("F10").ToLower()) return InputKeyCode::F10;
                if (stringValueLower == FString("F11").ToLower()) return InputKeyCode::F11;
                if (stringValueLower == FString("F12").ToLower()) return InputKeyCode::F12;
                if (stringValueLower == FString("F13").ToLower()) return InputKeyCode::F13;
                if (stringValueLower == FString("F14").ToLower()) return InputKeyCode::F14;
                if (stringValueLower == FString("F15").ToLower()) return InputKeyCode::F15;
                if (stringValueLower == FString("Numlock").ToLower()) return InputKeyCode::Numlock;
                if (stringValueLower == FString("Capslock").ToLower()) return InputKeyCode::Capslock;
                if (stringValueLower == FString("Scrollock").ToLower()) return InputKeyCode::Scrollock;
                if (stringValueLower == FString("RightShift").ToLower()) return InputKeyCode::RightShift;
                if (stringValueLower == FString("LeftShift").ToLower()) return InputKeyCode::LeftShift;
                if (stringValueLower == FString("RightCtrl").ToLower()) return InputKeyCode::RightCtrl;
                if (stringValueLower == FString("LeftCtrl").ToLower()) return InputKeyCode::LeftCtrl;
                if (stringValueLower == FString("RightAlt").ToLower()) return InputKeyCode::RightAlt;
                if (stringValueLower == FString("LeftAlt").ToLower()) return InputKeyCode::LeftAlt;
                if (stringValueLower == FString("LeftSuper").ToLower()) return InputKeyCode::LeftSuper;
                if (stringValueLower == FString("RightSuper").ToLower()) return InputKeyCode::RightSuper;
                if (stringValueLower == FString("Mode").ToLower()) return InputKeyCode::Mode;
                if (stringValueLower == FString("Help").ToLower()) return InputKeyCode::Help;
                if (stringValueLower == FString("Print").ToLower()) return InputKeyCode::Print;
                if (stringValueLower == FString("Sysreq").ToLower()) return InputKeyCode::Sysreq;
                if (stringValueLower == FString("Menu").ToLower()) return InputKeyCode::Menu;
                if (stringValueLower == FString("Power").ToLower()) return InputKeyCode::Power;
            }

            Logger::Assert(NotImplementedException(), FString("EInputKeyCode"), FString("FromString"),
                FString("No Input Key Code value for a button requested: ") + value);
            return InputKeyCode::None;
        }

        /// <summary>
        /// Converts to SDL_Scancode.
        /// Will return SDL_SCANCODE_UNKNOWN if an equlivent does not exist!
        /// </summary>
        static SDL_Scancode ToSDLScanKeycode(InputKeyCode code)
        {
            switch (code)
            {
            case InputKeyCode::Backspace: return SDL_SCANCODE_BACKSPACE;
            case InputKeyCode::Tab: return SDL_SCANCODE_TAB;
            case InputKeyCode::Clear: return SDL_SCANCODE_CLEAR;
            case InputKeyCode::Return: return SDL_SCANCODE_RETURN;
            case InputKeyCode::Pause: return SDL_SCANCODE_PAUSE;
            case InputKeyCode::Escape: return SDL_SCANCODE_ESCAPE;
            case InputKeyCode::Space: return SDL_SCANCODE_SPACE;
            case InputKeyCode::Exclaim: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Quotedbl: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Hash: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Dollar: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Ampersand: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Quote: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::LeftParenthesis: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::RightParenthesis: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Asterisk: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Plus: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Comma: return SDL_SCANCODE_COMMA;
            case InputKeyCode::Minus: return SDL_SCANCODE_MINUS;
            case InputKeyCode::Period: return SDL_SCANCODE_PERIOD;
            case InputKeyCode::Slash: return SDL_SCANCODE_SLASH;
            case InputKeyCode::Zero: return SDL_SCANCODE_0;
            case InputKeyCode::One: return SDL_SCANCODE_1;
            case InputKeyCode::Two: return SDL_SCANCODE_2;
            case InputKeyCode::Three: return SDL_SCANCODE_3;
            case InputKeyCode::Four: return SDL_SCANCODE_4;
            case InputKeyCode::Five: return SDL_SCANCODE_5;
            case InputKeyCode::Six: return SDL_SCANCODE_6;
            case InputKeyCode::Seven: return SDL_SCANCODE_7;
            case InputKeyCode::Eight: return SDL_SCANCODE_8;
            case InputKeyCode::Nine: return SDL_SCANCODE_9;
            case InputKeyCode::Colon: return SDL_SCANCODE_KP_COLON;
            case InputKeyCode::Semicolon: return SDL_SCANCODE_SEMICOLON;
            case InputKeyCode::Less: return SDL_SCANCODE_KP_LESS;
            case InputKeyCode::Equals: return SDL_SCANCODE_EQUALS;
            case InputKeyCode::Greater: return SDL_SCANCODE_KP_GREATER;
            case InputKeyCode::Question: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::At: return SDL_SCANCODE_KP_AT;
            case InputKeyCode::LeftBracket: return SDL_SCANCODE_LEFTBRACKET;
            case InputKeyCode::Backslash: return SDL_SCANCODE_BACKSLASH;
            case InputKeyCode::RightBracket: return SDL_SCANCODE_RIGHTBRACKET;
            case InputKeyCode::Caret: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Underscore: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::Backquote: return SDL_SCANCODE_UNKNOWN;
            case InputKeyCode::A: return SDL_SCANCODE_A;
            case InputKeyCode::B: return SDL_SCANCODE_B;
            case InputKeyCode::C: return SDL_SCANCODE_C;
            case InputKeyCode::D: return SDL_SCANCODE_D;
            case InputKeyCode::E: return SDL_SCANCODE_E;
            case InputKeyCode::F: return SDL_SCANCODE_F;
            case InputKeyCode::G: return SDL_SCANCODE_G;
            case InputKeyCode::H: return SDL_SCANCODE_H;
            case InputKeyCode::I: return SDL_SCANCODE_I;
            case InputKeyCode::J: return SDL_SCANCODE_J;
            case InputKeyCode::K: return SDL_SCANCODE_K;
            case InputKeyCode::L: return SDL_SCANCODE_L;
            case InputKeyCode::M: return SDL_SCANCODE_M;
            case InputKeyCode::N: return SDL_SCANCODE_N;
            case InputKeyCode::O: return SDL_SCANCODE_O;
            case InputKeyCode::P: return SDL_SCANCODE_P;
            case InputKeyCode::Q: return SDL_SCANCODE_Q;
            case InputKeyCode::R: return SDL_SCANCODE_R;
            case InputKeyCode::S: return SDL_SCANCODE_S;
            case InputKeyCode::T: return SDL_SCANCODE_T;
            case InputKeyCode::U: return SDL_SCANCODE_U;
            case InputKeyCode::V: return SDL_SCANCODE_V;
            case InputKeyCode::W: return SDL_SCANCODE_W;
            case InputKeyCode::X: return SDL_SCANCODE_X;
            case InputKeyCode::Y: return SDL_SCANCODE_Y;
            case InputKeyCode::Z: return SDL_SCANCODE_Z;
            case InputKeyCode::Delete: return SDL_SCANCODE_DELETE;
            case InputKeyCode::KeyPadZero: return SDL_SCANCODE_KP_0;
            case InputKeyCode::KeyPadOne: return SDL_SCANCODE_KP_1;
            case InputKeyCode::KeyPadTwo: return SDL_SCANCODE_KP_2;
            case InputKeyCode::KeyPadThree: return SDL_SCANCODE_KP_3;
            case InputKeyCode::KeyPadFour: return SDL_SCANCODE_KP_4;
            case InputKeyCode::KeyPadFive: return SDL_SCANCODE_KP_5;
            case InputKeyCode::KeyPadSix: return SDL_SCANCODE_KP_6;
            case InputKeyCode::KeyPadSeven: return SDL_SCANCODE_KP_7;
            case InputKeyCode::KeyPadEight: return SDL_SCANCODE_KP_8;
            case InputKeyCode::KeyPadNine: return SDL_SCANCODE_KP_9;
            case InputKeyCode::KeyPadPeriod: return SDL_SCANCODE_KP_PERIOD;
            case InputKeyCode::KeyPadMultiply: return SDL_SCANCODE_KP_MULTIPLY;
            case InputKeyCode::KeyPadMinus: return SDL_SCANCODE_KP_MINUS;
            case InputKeyCode::KeyPadPlus: return SDL_SCANCODE_KP_PLUS;
            case InputKeyCode::KeyPadEnter: return SDL_SCANCODE_KP_ENTER;
            case InputKeyCode::KeyPadEquals: return SDL_SCANCODE_KP_EQUALS;
            case InputKeyCode::Up: return SDL_SCANCODE_UP;
            case InputKeyCode::Down: return SDL_SCANCODE_DOWN;
            case InputKeyCode::Right: return SDL_SCANCODE_RIGHT;
            case InputKeyCode::Left: return SDL_SCANCODE_LEFT;
            case InputKeyCode::Insert: return SDL_SCANCODE_INSERT;
            case InputKeyCode::Home: return SDL_SCANCODE_HOME;
            case InputKeyCode::End: return SDL_SCANCODE_END;
            case InputKeyCode::PageUp: return SDL_SCANCODE_PAGEUP;
            case InputKeyCode::PageDown: return SDL_SCANCODE_PAGEDOWN;
            case InputKeyCode::F1: return SDL_SCANCODE_F1;
            case InputKeyCode::F2: return SDL_SCANCODE_F2;
            case InputKeyCode::F3: return SDL_SCANCODE_F3;
            case InputKeyCode::F4: return SDL_SCANCODE_F4;
            case InputKeyCode::F5: return SDL_SCANCODE_F5;
            case InputKeyCode::F6: return SDL_SCANCODE_F6;
            case InputKeyCode::F7: return SDL_SCANCODE_F7;
            case InputKeyCode::F8: return SDL_SCANCODE_F8;
            case InputKeyCode::F9: return SDL_SCANCODE_F9;
            case InputKeyCode::F10: return SDL_SCANCODE_F10;
            case InputKeyCode::F11: return SDL_SCANCODE_F11;
            case InputKeyCode::F12: return SDL_SCANCODE_F12;
            case InputKeyCode::F13: return SDL_SCANCODE_F13;
            case InputKeyCode::F14: return SDL_SCANCODE_F14;
            case InputKeyCode::F15: return SDL_SCANCODE_F15;
            case InputKeyCode::Numlock: return SDL_SCANCODE_NUMLOCKCLEAR;
            case InputKeyCode::Capslock: return SDL_SCANCODE_CAPSLOCK;
            case InputKeyCode::Scrollock: return SDL_SCANCODE_SCROLLLOCK;
            case InputKeyCode::RightShift: return SDL_SCANCODE_RSHIFT;
            case InputKeyCode::LeftShift: return SDL_SCANCODE_LSHIFT;
            case InputKeyCode::RightCtrl: return SDL_SCANCODE_RCTRL;
            case InputKeyCode::LeftCtrl: return SDL_SCANCODE_LCTRL;
            case InputKeyCode::RightAlt: return SDL_SCANCODE_RALT;
            case InputKeyCode::LeftAlt: return SDL_SCANCODE_LALT;
            case InputKeyCode::LeftSuper: return SDL_SCANCODE_LGUI;
            case InputKeyCode::RightSuper: return SDL_SCANCODE_RGUI;
            case InputKeyCode::Mode: return SDL_SCANCODE_MODE;
            case InputKeyCode::Help: return SDL_SCANCODE_HELP;
            case InputKeyCode::Print: return SDL_SCANCODE_PRINTSCREEN;
            case InputKeyCode::Sysreq: return SDL_SCANCODE_SYSREQ;
            case InputKeyCode::Menu: return SDL_SCANCODE_MENU;
            case InputKeyCode::Power: return SDL_SCANCODE_POWER;
            }
            return SDL_SCANCODE_UNKNOWN;
        };

        static SDL_KeyCode ToSDLKKeycode(InputKeyCode code)
        {
            switch (code)
            {
            case InputKeyCode::Backspace: return SDLK_BACKSPACE;
            case InputKeyCode::Tab: return SDLK_TAB;
            case InputKeyCode::Clear: return SDLK_CLEAR;
            case InputKeyCode::Return: return SDLK_RETURN;
            case InputKeyCode::Pause: return SDLK_PAUSE;
            case InputKeyCode::Escape: return SDLK_ESCAPE;
            case InputKeyCode::Space: return SDLK_SPACE;
            case InputKeyCode::Exclaim: return SDLK_EXCLAIM;
            case InputKeyCode::Quotedbl: return SDLK_QUOTEDBL;
            case InputKeyCode::Hash: return SDLK_HASH;
            case InputKeyCode::Dollar: return SDLK_DOLLAR;
            case InputKeyCode::Ampersand: return SDLK_AMPERSAND;
            case InputKeyCode::Quote: return SDLK_QUOTE;
            case InputKeyCode::LeftParenthesis: return SDLK_LEFTPAREN;
            case InputKeyCode::RightParenthesis: return SDLK_RIGHTPAREN;
            case InputKeyCode::Asterisk: return SDLK_ASTERISK;
            case InputKeyCode::Plus: return SDLK_PLUS;
            case InputKeyCode::Comma: return SDLK_COMMA;
            case InputKeyCode::Minus: return SDLK_MINUS;
            case InputKeyCode::Period: return SDLK_PERIOD;
            case InputKeyCode::Slash: return SDLK_SLASH;
            case InputKeyCode::Zero: return SDLK_0;
            case InputKeyCode::One: return SDLK_1;
            case InputKeyCode::Two: return SDLK_2;
            case InputKeyCode::Three: return SDLK_3;
            case InputKeyCode::Four: return SDLK_4;
            case InputKeyCode::Five: return SDLK_5;
            case InputKeyCode::Six: return SDLK_6;
            case InputKeyCode::Seven: return SDLK_7;
            case InputKeyCode::Eight: return SDLK_8;
            case InputKeyCode::Nine: return SDLK_9;
            case InputKeyCode::Colon: return SDLK_COLON;
            case InputKeyCode::Semicolon: return SDLK_SEMICOLON;
            case InputKeyCode::Less: return SDLK_LESS;
            case InputKeyCode::Equals: return SDLK_EQUALS;
            case InputKeyCode::Greater: return SDLK_GREATER;
            case InputKeyCode::Question: return SDLK_QUESTION;
            case InputKeyCode::At: return SDLK_AT;
            case InputKeyCode::LeftBracket: return SDLK_LEFTBRACKET;
            case InputKeyCode::Backslash: return SDLK_BACKSLASH;
            case InputKeyCode::RightBracket: return SDLK_RIGHTBRACKET;
            case InputKeyCode::Caret: return SDLK_CARET;
            case InputKeyCode::Underscore: return SDLK_UNDERSCORE;
            case InputKeyCode::Backquote: return SDLK_BACKQUOTE;
            case InputKeyCode::A: return SDLK_a;
            case InputKeyCode::B: return SDLK_b;
            case InputKeyCode::C: return SDLK_c;
            case InputKeyCode::D: return SDLK_d;
            case InputKeyCode::E: return SDLK_e;
            case InputKeyCode::F: return SDLK_f;
            case InputKeyCode::G: return SDLK_g;
            case InputKeyCode::H: return SDLK_h;
            case InputKeyCode::I: return SDLK_i;
            case InputKeyCode::J: return SDLK_j;
            case InputKeyCode::K: return SDLK_k;
            case InputKeyCode::L: return SDLK_l;
            case InputKeyCode::M: return SDLK_m;
            case InputKeyCode::N: return SDLK_n;
            case InputKeyCode::O: return SDLK_o;
            case InputKeyCode::P: return SDLK_p;
            case InputKeyCode::Q: return SDLK_q;
            case InputKeyCode::R: return SDLK_r;
            case InputKeyCode::S: return SDLK_s;
            case InputKeyCode::T: return SDLK_t;
            case InputKeyCode::U: return SDLK_u;
            case InputKeyCode::V: return SDLK_v;
            case InputKeyCode::W: return SDLK_w;
            case InputKeyCode::X: return SDLK_x;
            case InputKeyCode::Y: return SDLK_y;
            case InputKeyCode::Z: return SDLK_z;
            case InputKeyCode::Delete: return SDLK_DELETE;
            case InputKeyCode::KeyPadZero: return SDLK_KP_0;
            case InputKeyCode::KeyPadOne: return SDLK_KP_1;
            case InputKeyCode::KeyPadTwo: return SDLK_KP_2;
            case InputKeyCode::KeyPadThree: return SDLK_KP_3;
            case InputKeyCode::KeyPadFour: return SDLK_KP_4;
            case InputKeyCode::KeyPadFive: return SDLK_KP_5;
            case InputKeyCode::KeyPadSix: return SDLK_KP_6;
            case InputKeyCode::KeyPadSeven: return SDLK_KP_7;
            case InputKeyCode::KeyPadEight: return SDLK_KP_8;
            case InputKeyCode::KeyPadNine: return SDLK_KP_9;
            case InputKeyCode::KeyPadPeriod: return SDLK_KP_PERIOD;
            case InputKeyCode::KeyPadMultiply: return SDLK_KP_MULTIPLY;
            case InputKeyCode::KeyPadMinus: return SDLK_KP_MINUS;
            case InputKeyCode::KeyPadPlus: return SDLK_KP_PLUS;
            case InputKeyCode::KeyPadEnter: return SDLK_KP_ENTER;
            case InputKeyCode::KeyPadEquals: return SDLK_KP_EQUALS;
            case InputKeyCode::Up: return SDLK_UP;
            case InputKeyCode::Down: return SDLK_DOWN;
            case InputKeyCode::Right: return SDLK_RIGHT;
            case InputKeyCode::Left: return SDLK_LEFT;
            case InputKeyCode::Insert: return SDLK_INSERT;
            case InputKeyCode::Home: return SDLK_HOME;
            case InputKeyCode::End: return SDLK_END;
            case InputKeyCode::PageUp: return SDLK_PAGEUP;
            case InputKeyCode::PageDown: return SDLK_PAGEDOWN;
            case InputKeyCode::F1: return SDLK_F1;
            case InputKeyCode::F2: return SDLK_F2;
            case InputKeyCode::F3: return SDLK_F3;
            case InputKeyCode::F4: return SDLK_F4;
            case InputKeyCode::F5: return SDLK_F5;
            case InputKeyCode::F6: return SDLK_F6;
            case InputKeyCode::F7: return SDLK_F7;
            case InputKeyCode::F8: return SDLK_F8;
            case InputKeyCode::F9: return SDLK_F9;
            case InputKeyCode::F10: return SDLK_F10;
            case InputKeyCode::F11: return SDLK_F11;
            case InputKeyCode::F12: return SDLK_F12;
            case InputKeyCode::F13: return SDLK_F13;
            case InputKeyCode::F14: return SDLK_F14;
            case InputKeyCode::F15: return SDLK_F15;
            case InputKeyCode::Numlock: return SDLK_NUMLOCKCLEAR;
            case InputKeyCode::Capslock: return SDLK_CAPSLOCK;
            case InputKeyCode::Scrollock: return SDLK_SCROLLLOCK;
            case InputKeyCode::RightShift: return SDLK_RSHIFT;
            case InputKeyCode::LeftShift: return SDLK_LSHIFT;
            case InputKeyCode::RightCtrl: return SDLK_RCTRL;
            case InputKeyCode::LeftCtrl: return SDLK_LCTRL;
            case InputKeyCode::RightAlt: return SDLK_RALT;
            case InputKeyCode::LeftAlt: return SDLK_LALT;
            case InputKeyCode::LeftSuper: return SDLK_LGUI;
            case InputKeyCode::RightSuper: return SDLK_RGUI;
            case InputKeyCode::Mode: return SDLK_MODE;
            case InputKeyCode::Help: return SDLK_HELP;
            case InputKeyCode::Print: return SDLK_PRINTSCREEN;
            case InputKeyCode::Sysreq: return SDLK_SYSREQ;
            case InputKeyCode::Menu: return SDLK_MENU;
            case InputKeyCode::Power: return SDLK_POWER;
            }

            Logger::Assert(ArgumentNullException(), FString("EInputKeyCode"), FString("ToSDLKeycode"), FString("Fell out of enum. Type: ") + (int)code);
            return SDLK_BACKSPACE;
        };
    };
}