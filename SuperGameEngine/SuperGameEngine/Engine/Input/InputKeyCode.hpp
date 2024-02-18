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