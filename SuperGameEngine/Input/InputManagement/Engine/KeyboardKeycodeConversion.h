#pragma once
#include "../Event/KeyboardKeycode.h"
#include "KeyCode.h"

namespace SuperGameInput
{
    /// <summary>
    /// Conversion methods.
    /// </summary>
    class KeyboardKeycodeConversion
    {
    public:

        /// <summary>
        /// Converts from <see cref="KeyCode"/> to <see cref="KeyboardKeycode"/>
        /// </summary>
        /// <param name="code">Code to convert. </param>
        /// <returns>Converted code. </returns>
        static KeyboardKeycode FromKeyCode(const KeyCode& code)
        {
            switch (code)
            {
                case KeyCode::Unknown:
                case KeyCode::None: return KeyboardKeycode::Unknown;
                case KeyCode::Backspace: return KeyboardKeycode::SDLK_BACKSPACE;
                case KeyCode::Tab: return KeyboardKeycode::SDLK_TAB;
                case KeyCode::Clear: return KeyboardKeycode::SDLK_CLEAR;
                case KeyCode::Return: return KeyboardKeycode::SDLK_RETURN;
                case KeyCode::Pause: return KeyboardKeycode::SDLK_PAUSE;
                case KeyCode::Escape: return KeyboardKeycode::SDLK_ESCAPE;
                case KeyCode::Space: return KeyboardKeycode::SDLK_SPACE;
                case KeyCode::Exclaim: return KeyboardKeycode::SDLK_EXCLAIM;
                case KeyCode::Quotedbl: return KeyboardKeycode::SDLK_QUOTEDBL;
                case KeyCode::Hash: return KeyboardKeycode::SDLK_HASH;
                case KeyCode::Dollar: return KeyboardKeycode::SDLK_DOLLAR;
                case KeyCode::Ampersand: return KeyboardKeycode::SDLK_AMPERSAND;
                case KeyCode::Quote: return KeyboardKeycode::SDLK_QUOTE;
                case KeyCode::LeftParenthesis: return KeyboardKeycode::SDLK_LEFTPAREN;
                case KeyCode::RightParenthesis: return KeyboardKeycode::SDLK_RIGHTPAREN;
                case KeyCode::Asterisk: return KeyboardKeycode::SDLK_ASTERISK;
                case KeyCode::Plus: return KeyboardKeycode::SDLK_PLUS;
                case KeyCode::Comma: return KeyboardKeycode::SDLK_COMMA;
                case KeyCode::Minus: return KeyboardKeycode::SDLK_MINUS;
                case KeyCode::Period: return KeyboardKeycode::SDLK_PERIOD;
                case KeyCode::Slash: return KeyboardKeycode::SDLK_SLASH;
                case KeyCode::Zero: return KeyboardKeycode::SDLK_0;
                case KeyCode::One: return KeyboardKeycode::SDLK_1;
                case KeyCode::Two: return KeyboardKeycode::SDLK_2;
                case KeyCode::Three: return KeyboardKeycode::SDLK_3;
                case KeyCode::Four: return KeyboardKeycode::SDLK_4;
                case KeyCode::Five: return KeyboardKeycode::SDLK_5;
                case KeyCode::Six: return KeyboardKeycode::SDLK_6;
                case KeyCode::Seven: return KeyboardKeycode::SDLK_7;
                case KeyCode::Eight: return KeyboardKeycode::SDLK_8;
                case KeyCode::Nine: return KeyboardKeycode::SDLK_9;
                case KeyCode::Colon: return KeyboardKeycode::SDLK_COLON;
                case KeyCode::Semicolon: return KeyboardKeycode::SDLK_SEMICOLON;
                case KeyCode::Less: return KeyboardKeycode::SDLK_LESS;
                case KeyCode::Equals: return KeyboardKeycode::SDLK_EQUALS;
                case KeyCode::Greater: return KeyboardKeycode::SDLK_GREATER;
                case KeyCode::Question: return KeyboardKeycode::SDLK_QUESTION;
                case KeyCode::At: return KeyboardKeycode::SDLK_AT;
                case KeyCode::LeftBracket: return KeyboardKeycode::SDLK_LEFTBRACKET;
                case KeyCode::Backslash: return KeyboardKeycode::SDLK_BACKSLASH;
                case KeyCode::RightBracket: return KeyboardKeycode::SDLK_RIGHTBRACKET;
                case KeyCode::Caret: return KeyboardKeycode::SDLK_CARET;
                case KeyCode::Underscore: return KeyboardKeycode::SDLK_UNDERSCORE;
                case KeyCode::Backquote: return KeyboardKeycode::SDLK_BACKQUOTE;
                case KeyCode::A: return KeyboardKeycode::SDLK_a;
                case KeyCode::B: return KeyboardKeycode::SDLK_b;
                case KeyCode::C: return KeyboardKeycode::SDLK_c;
                case KeyCode::D: return KeyboardKeycode::SDLK_d;
                case KeyCode::E: return KeyboardKeycode::SDLK_e;
                case KeyCode::F: return KeyboardKeycode::SDLK_f;
                case KeyCode::G: return KeyboardKeycode::SDLK_g;
                case KeyCode::H: return KeyboardKeycode::SDLK_h;
                case KeyCode::I: return KeyboardKeycode::SDLK_i;
                case KeyCode::J: return KeyboardKeycode::SDLK_j;
                case KeyCode::K: return KeyboardKeycode::SDLK_k;
                case KeyCode::L: return KeyboardKeycode::SDLK_l;
                case KeyCode::M: return KeyboardKeycode::SDLK_m;
                case KeyCode::N: return KeyboardKeycode::SDLK_n;
                case KeyCode::O: return KeyboardKeycode::SDLK_o;
                case KeyCode::P: return KeyboardKeycode::SDLK_p;
                case KeyCode::Q: return KeyboardKeycode::SDLK_q;
                case KeyCode::R: return KeyboardKeycode::SDLK_r;
                case KeyCode::S: return KeyboardKeycode::SDLK_s;
                case KeyCode::T: return KeyboardKeycode::SDLK_t;
                case KeyCode::U: return KeyboardKeycode::SDLK_u;
                case KeyCode::V: return KeyboardKeycode::SDLK_v;
                case KeyCode::W: return KeyboardKeycode::SDLK_w;
                case KeyCode::X: return KeyboardKeycode::SDLK_x;
                case KeyCode::Y: return KeyboardKeycode::SDLK_y;
                case KeyCode::Z: return KeyboardKeycode::SDLK_z;
                case KeyCode::Delete: return KeyboardKeycode::SDLK_DELETE;
                case KeyCode::KeyPadZero: return KeyboardKeycode::SDLK_KP_0;
                case KeyCode::KeyPadOne: return KeyboardKeycode::SDLK_KP_1;
                case KeyCode::KeyPadTwo: return KeyboardKeycode::SDLK_KP_2;
                case KeyCode::KeyPadThree: return KeyboardKeycode::SDLK_KP_3;
                case KeyCode::KeyPadFour: return KeyboardKeycode::SDLK_KP_4;
                case KeyCode::KeyPadFive: return KeyboardKeycode::SDLK_KP_5;
                case KeyCode::KeyPadSix: return KeyboardKeycode::SDLK_KP_6;
                case KeyCode::KeyPadSeven: return KeyboardKeycode::SDLK_KP_7;
                case KeyCode::KeyPadEight: return KeyboardKeycode::SDLK_KP_8;
                case KeyCode::KeyPadNine: return KeyboardKeycode::SDLK_KP_9;
                case KeyCode::KeyPadPeriod: return KeyboardKeycode::SDLK_KP_PERIOD;
                case KeyCode::KeyPadMultiply: return KeyboardKeycode::SDLK_KP_MULTIPLY;
                case KeyCode::KeyPadDivide: return KeyboardKeycode::SDLK_KP_DIVIDE;
                case KeyCode::KeyPadMinus: return KeyboardKeycode::SDLK_KP_MINUS;
                case KeyCode::KeyPadPlus: return KeyboardKeycode::SDLK_KP_PLUS;
                case KeyCode::KeyPadEnter: return KeyboardKeycode::SDLK_KP_ENTER;
                case KeyCode::KeyPadEquals: return KeyboardKeycode::SDLK_KP_EQUALS;
                case KeyCode::Up: return KeyboardKeycode::SDLK_UP;
                case KeyCode::Down: return KeyboardKeycode::SDLK_DOWN;
                case KeyCode::Right: return KeyboardKeycode::SDLK_RIGHT;
                case KeyCode::Left: return KeyboardKeycode::SDLK_LEFT;
                case KeyCode::Insert: return KeyboardKeycode::SDLK_INSERT;
                case KeyCode::Home: return KeyboardKeycode::SDLK_HOME;
                case KeyCode::End: return KeyboardKeycode::SDLK_END;
                case KeyCode::PageUp: return KeyboardKeycode::SDLK_PAGEUP;
                case KeyCode::PageDown: return KeyboardKeycode::SDLK_PAGEDOWN;
                case KeyCode::F1: return KeyboardKeycode::SDLK_F1;
                case KeyCode::F2: return KeyboardKeycode::SDLK_F2;
                case KeyCode::F3: return KeyboardKeycode::SDLK_F3;
                case KeyCode::F4: return KeyboardKeycode::SDLK_F4;
                case KeyCode::F5: return KeyboardKeycode::SDLK_F5;
                case KeyCode::F6: return KeyboardKeycode::SDLK_F6;
                case KeyCode::F7: return KeyboardKeycode::SDLK_F7;
                case KeyCode::F8: return KeyboardKeycode::SDLK_F8;
                case KeyCode::F9: return KeyboardKeycode::SDLK_F9;
                case KeyCode::F10: return KeyboardKeycode::SDLK_F10;
                case KeyCode::F11: return KeyboardKeycode::SDLK_F11;
                case KeyCode::F12: return KeyboardKeycode::SDLK_F12;
                case KeyCode::F13: return KeyboardKeycode::SDLK_F13;
                case KeyCode::F14: return KeyboardKeycode::SDLK_F14;
                case KeyCode::F15: return KeyboardKeycode::SDLK_F15;
                case KeyCode::Numlock: return KeyboardKeycode::SDLK_NUMLOCKCLEAR;
                case KeyCode::Capslock: return KeyboardKeycode::SDLK_CAPSLOCK;
                case KeyCode::Scrollock: return KeyboardKeycode::SDLK_SCROLLLOCK;
                case KeyCode::RightShift: return KeyboardKeycode::SDLK_RSHIFT;
                case KeyCode::LeftShift: return KeyboardKeycode::SDLK_LSHIFT;
                case KeyCode::RightCtrl: return KeyboardKeycode::SDLK_RCTRL;
                case KeyCode::LeftCtrl: return KeyboardKeycode::SDLK_LCTRL;
                case KeyCode::RightAlt: return KeyboardKeycode::SDLK_RALT;
                case KeyCode::LeftAlt: return KeyboardKeycode::SDLK_LALT;
                case KeyCode::LeftSuper: return KeyboardKeycode::SDLK_LGUI;
                case KeyCode::RightSuper: return KeyboardKeycode::SDLK_RGUI;
                case KeyCode::Mode: return KeyboardKeycode::SDLK_MODE;
                case KeyCode::Help: return KeyboardKeycode::SDLK_HELP;
                case KeyCode::Print: return KeyboardKeycode::SDLK_PRINTSCREEN;
                case KeyCode::Sysreq: return KeyboardKeycode::SDLK_SYSREQ;
                case KeyCode::Menu: return KeyboardKeycode::SDLK_MENU;
                case KeyCode::Power: return KeyboardKeycode::SDLK_POWER;
            }

            return KeyboardKeycode::Unknown;
        }

        /// <summary>
        /// Convert from <see cref="KeyboardKeycode"/> to <see cref="KeyCode"/>
        /// </summary>
        /// <param name="code">Value to convert. </param>
        /// <returns>Converted value. </returns>
        static KeyCode FromKeyCode(const KeyboardKeycode& code)
        {
            switch (code)
            {
                case KeyboardKeycode::Unknown: return KeyCode::None;
                case KeyboardKeycode::SDLK_BACKSPACE: return KeyCode::Backspace;
                case KeyboardKeycode::SDLK_TAB: return KeyCode::Tab;
                case KeyboardKeycode::SDLK_CLEAR: return KeyCode::Clear;
                case KeyboardKeycode::SDLK_RETURN: return KeyCode::Return;
                case KeyboardKeycode::SDLK_PAUSE: return KeyCode::Pause;
                case KeyboardKeycode::SDLK_ESCAPE: return KeyCode::Escape;
                case KeyboardKeycode::SDLK_SPACE: return KeyCode::Space;
                case KeyboardKeycode::SDLK_EXCLAIM: return KeyCode::Exclaim;
                case KeyboardKeycode::SDLK_QUOTEDBL: return KeyCode::Quotedbl;
                case KeyboardKeycode::SDLK_HASH: return KeyCode::Hash;
                case KeyboardKeycode::SDLK_DOLLAR: return KeyCode::Dollar;
                case KeyboardKeycode::SDLK_AMPERSAND: return KeyCode::Ampersand;
                case KeyboardKeycode::SDLK_QUOTE: return KeyCode::Quote;
                case KeyboardKeycode::SDLK_LEFTPAREN: return KeyCode::LeftParenthesis;
                case KeyboardKeycode::SDLK_RIGHTPAREN: return KeyCode::RightParenthesis;
                case KeyboardKeycode::SDLK_ASTERISK: return KeyCode::Asterisk;
                case KeyboardKeycode::SDLK_PLUS: return KeyCode::Plus;
                case KeyboardKeycode::SDLK_COMMA: return KeyCode::Comma;
                case KeyboardKeycode::SDLK_MINUS: return KeyCode::Minus;
                case KeyboardKeycode::SDLK_PERIOD: return KeyCode::Period;
                case KeyboardKeycode::SDLK_SLASH: return KeyCode::Slash;
                case KeyboardKeycode::SDLK_0: return KeyCode::Zero;
                case KeyboardKeycode::SDLK_1: return KeyCode::One;
                case KeyboardKeycode::SDLK_2: return KeyCode::Two;
                case KeyboardKeycode::SDLK_3: return KeyCode::Three;
                case KeyboardKeycode::SDLK_4: return KeyCode::Four;
                case KeyboardKeycode::SDLK_5: return KeyCode::Five;
                case KeyboardKeycode::SDLK_6: return KeyCode::Six;
                case KeyboardKeycode::SDLK_7: return KeyCode::Seven;
                case KeyboardKeycode::SDLK_8: return KeyCode::Eight;
                case KeyboardKeycode::SDLK_9: return KeyCode::Nine;
                case KeyboardKeycode::SDLK_COLON: return KeyCode::Colon;
                case KeyboardKeycode::SDLK_SEMICOLON: return KeyCode::Semicolon;
                case KeyboardKeycode::SDLK_LESS: return KeyCode::Less;
                case KeyboardKeycode::SDLK_EQUALS: return KeyCode::Equals;
                case KeyboardKeycode::SDLK_GREATER: return KeyCode::Greater;
                case KeyboardKeycode::SDLK_QUESTION: return KeyCode::Question;
                case KeyboardKeycode::SDLK_AT: return KeyCode::At;
                case KeyboardKeycode::SDLK_LEFTBRACKET: return KeyCode::LeftBracket;
                case KeyboardKeycode::SDLK_BACKSLASH: return KeyCode::Backslash;
                case KeyboardKeycode::SDLK_RIGHTBRACKET: return KeyCode::RightBracket;
                case KeyboardKeycode::SDLK_CARET: return KeyCode::Caret;
                case KeyboardKeycode::SDLK_UNDERSCORE: return KeyCode::Underscore;
                case KeyboardKeycode::SDLK_BACKQUOTE: return KeyCode::Backquote;
                case KeyboardKeycode::SDLK_a: return KeyCode::A;
                case KeyboardKeycode::SDLK_b: return KeyCode::B;
                case KeyboardKeycode::SDLK_c: return KeyCode::C;
                case KeyboardKeycode::SDLK_d: return KeyCode::D;
                case KeyboardKeycode::SDLK_e: return KeyCode::E;
                case KeyboardKeycode::SDLK_f: return KeyCode::F;
                case KeyboardKeycode::SDLK_g: return KeyCode::G;
                case KeyboardKeycode::SDLK_h: return KeyCode::H;
                case KeyboardKeycode::SDLK_i: return KeyCode::I;
                case KeyboardKeycode::SDLK_j: return KeyCode::J;
                case KeyboardKeycode::SDLK_k: return KeyCode::K;
                case KeyboardKeycode::SDLK_l: return KeyCode::L;
                case KeyboardKeycode::SDLK_m: return KeyCode::M;
                case KeyboardKeycode::SDLK_n: return KeyCode::N;
                case KeyboardKeycode::SDLK_o: return KeyCode::O;
                case KeyboardKeycode::SDLK_p: return KeyCode::P;
                case KeyboardKeycode::SDLK_q: return KeyCode::Q;
                case KeyboardKeycode::SDLK_r: return KeyCode::R;
                case KeyboardKeycode::SDLK_s: return KeyCode::S;
                case KeyboardKeycode::SDLK_t: return KeyCode::T;
                case KeyboardKeycode::SDLK_u: return KeyCode::U;
                case KeyboardKeycode::SDLK_v: return KeyCode::V;
                case KeyboardKeycode::SDLK_w: return KeyCode::W;
                case KeyboardKeycode::SDLK_x: return KeyCode::X;
                case KeyboardKeycode::SDLK_y: return KeyCode::Y;
                case KeyboardKeycode::SDLK_z: return KeyCode::Z;
                case KeyboardKeycode::SDLK_DELETE: return KeyCode::Delete;
                case KeyboardKeycode::SDLK_KP_0: return KeyCode::KeyPadZero;
                case KeyboardKeycode::SDLK_KP_1: return KeyCode::KeyPadOne;
                case KeyboardKeycode::SDLK_KP_2: return KeyCode::KeyPadTwo;
                case KeyboardKeycode::SDLK_KP_3: return KeyCode::KeyPadThree;
                case KeyboardKeycode::SDLK_KP_4: return KeyCode::KeyPadFour;
                case KeyboardKeycode::SDLK_KP_5: return KeyCode::KeyPadFive;
                case KeyboardKeycode::SDLK_KP_6: return KeyCode::KeyPadSix;
                case KeyboardKeycode::SDLK_KP_7: return KeyCode::KeyPadSeven;
                case KeyboardKeycode::SDLK_KP_8: return KeyCode::KeyPadEight;
                case KeyboardKeycode::SDLK_KP_9: return KeyCode::KeyPadNine;
                case KeyboardKeycode::SDLK_KP_PERIOD: return KeyCode::KeyPadPeriod;
                case KeyboardKeycode::SDLK_KP_MULTIPLY: return KeyCode::KeyPadMultiply;
                case KeyboardKeycode::SDLK_KP_DIVIDE: return KeyCode::KeyPadDivide;
                case KeyboardKeycode::SDLK_KP_MINUS: return KeyCode::KeyPadMinus;
                case KeyboardKeycode::SDLK_KP_PLUS: return KeyCode::KeyPadPlus;
                case KeyboardKeycode::SDLK_KP_ENTER: return KeyCode::KeyPadEnter;
                case KeyboardKeycode::SDLK_KP_EQUALS: return KeyCode::KeyPadEquals;
                case KeyboardKeycode::SDLK_UP: return KeyCode::Up;
                case KeyboardKeycode::SDLK_DOWN: return KeyCode::Down;
                case KeyboardKeycode::SDLK_RIGHT: return KeyCode::Right;
                case KeyboardKeycode::SDLK_LEFT: return KeyCode::Left;
                case KeyboardKeycode::SDLK_INSERT: return KeyCode::Insert;
                case KeyboardKeycode::SDLK_HOME: return KeyCode::Home;
                case KeyboardKeycode::SDLK_END: return KeyCode::End;
                case KeyboardKeycode::SDLK_PAGEUP: return KeyCode::PageUp;
                case KeyboardKeycode::SDLK_PAGEDOWN: return KeyCode::PageDown;
                case KeyboardKeycode::SDLK_F1: return KeyCode::F1;
                case KeyboardKeycode::SDLK_F2: return KeyCode::F2;
                case KeyboardKeycode::SDLK_F3: return KeyCode::F3;
                case KeyboardKeycode::SDLK_F4: return KeyCode::F4;
                case KeyboardKeycode::SDLK_F5: return KeyCode::F5;
                case KeyboardKeycode::SDLK_F6: return KeyCode::F6;
                case KeyboardKeycode::SDLK_F7: return KeyCode::F7;
                case KeyboardKeycode::SDLK_F8: return KeyCode::F8;
                case KeyboardKeycode::SDLK_F9: return KeyCode::F9;
                case KeyboardKeycode::SDLK_F10: return KeyCode::F10;
                case KeyboardKeycode::SDLK_F11: return KeyCode::F11;
                case KeyboardKeycode::SDLK_F12: return KeyCode::F12;
                case KeyboardKeycode::SDLK_F13: return KeyCode::F13;
                case KeyboardKeycode::SDLK_F14: return KeyCode::F14;
                case KeyboardKeycode::SDLK_F15: return KeyCode::F15;
                case KeyboardKeycode::SDLK_NUMLOCKCLEAR: return KeyCode::Numlock;
                case KeyboardKeycode::SDLK_CAPSLOCK: return KeyCode::Capslock;
                case KeyboardKeycode::SDLK_SCROLLLOCK: return KeyCode::Scrollock;
                case KeyboardKeycode::SDLK_RSHIFT: return KeyCode::RightShift;
                case KeyboardKeycode::SDLK_LSHIFT: return KeyCode::LeftShift;
                case KeyboardKeycode::SDLK_RCTRL: return KeyCode::RightCtrl;
                case KeyboardKeycode::SDLK_LCTRL: return KeyCode::LeftCtrl;
                case KeyboardKeycode::SDLK_RALT: return KeyCode::RightAlt;
                case KeyboardKeycode::SDLK_LALT: return KeyCode::LeftAlt;
                case KeyboardKeycode::SDLK_LGUI: return KeyCode::LeftSuper;
                case KeyboardKeycode::SDLK_RGUI: return KeyCode::RightSuper;
                case KeyboardKeycode::SDLK_MODE: return KeyCode::Mode;
                case KeyboardKeycode::SDLK_HELP: return KeyCode::Help;
                case KeyboardKeycode::SDLK_PRINTSCREEN: return KeyCode::Print;
                case KeyboardKeycode::SDLK_SYSREQ: return KeyCode::Sysreq;
                case KeyboardKeycode::SDLK_MENU: return KeyCode::Menu;
                case KeyboardKeycode::SDLK_POWER: return KeyCode::Power;
            }

            return KeyCode::Unknown;
        }
    };
}
