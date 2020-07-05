#pragma once

typedef enum
{
    Key_FIRSTEVENT     = 0,     /**< Unused (do not remove) */

    /* Application events */
    Key_QUIT           = 0x100, /**< User-requested quit */

    /* These application events have special meaning on iOS, see README-ios.md for details */
    Key_APP_TERMINATING,        /**< The application is being terminated by the OS
                                     Called on iOS in applicationWillTerminate()
                                     Called on Android in onDestroy()
                                */
    Key_APP_LOWMEMORY,          /**< The application is low on memory, free memory if possible.
                                     Called on iOS in applicationDidReceiveMemoryWarning()
                                     Called on Android in onLowMemory()
                                */
    Key_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
                                     Called on iOS in applicationWillResignActive()
                                     Called on Android in onPause()
                                */
    Key_APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not get CPU for some time
                                     Called on iOS in applicationDidEnterBackground()
                                     Called on Android in onPause()
                                */
    Key_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
                                     Called on iOS in applicationWillEnterForeground()
                                     Called on Android in onResume()
                                */
    Key_APP_DIDENTERFOREGROUND, /**< The application is now interactive
                                     Called on iOS in applicationDidBecomeActive()
                                     Called on Android in onResume()
                                */

    /* Window events */
    Key_WINDOWEVENT    = 0x200, /**< Window state change */
    Key_SYSWMEVENT,             /**< System specific event */

    /* Keyboard events */
    Key_KEYDOWN        = 0x300, /**< Key pressed */
    Key_KEYUP,                  /**< Key released */
    Key_TEXTEDITING,            /**< Keyboard text editing (composition) */
    Key_TEXTINPUT,              /**< Keyboard text input */
    Key_KEYMAPCHANGED,          /**< Keymap changed due to a system event such as an
                                     input language or keyboard layout change.
                                */

    /* Mouse events */
    Key_MOUSEMOTION    = 0x400, /**< Mouse moved */
    Key_MOUSEBUTTONDOWN,        /**< Mouse button pressed */
    Key_MOUSEBUTTONUP,          /**< Mouse button released */
    Key_MOUSEWHEEL,             /**< Mouse wheel motion */

    /* Joystick events */
    Key_JOYAXISMOTION  = 0x600, /**< Joystick axis motion */
    Key_JOYBALLMOTION,          /**< Joystick trackball motion */
    Key_JOYHATMOTION,           /**< Joystick hat position change */
    Key_JOYBUTTONDOWN,          /**< Joystick button pressed */
    Key_JOYBUTTONUP,            /**< Joystick button released */
    Key_JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
    Key_JOYDEVICEREMOVED,       /**< An opened joystick has been removed */

    /* Game controller events */
    Key_CONTROLLERAXISMOTION  = 0x650, /**< Game controller axis motion */
    Key_CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
    Key_CONTROLLERBUTTONUP,            /**< Game controller button released */
    Key_CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
    Key_CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
    Key_CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */

    /* Touch events */
    Key_FINGERDOWN      = 0x700,
    Key_FINGERUP,
    Key_FINGERMOTION,

    /* Gesture events */
    Key_DOLLARGESTURE   = 0x800,
    Key_DOLLARRECORD,
    Key_MULTIGESTURE,

    /* Clipboard events */
    Key_CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */

    /* Drag and drop events */
    Key_DROPFILE        = 0x1000, /**< The system requests a file open */
    Key_DROPTEXT,                 /**< text/plain drag-and-drop event */
    Key_DROPBEGIN,                /**< A new set of drops is beginning (NULL filename) */
    Key_DROPCOMPLETE,             /**< Current set of drops is now complete (NULL filename) */

    /* Audio hotplug events */
    Key_AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
    Key_AUDIODEVICEREMOVED,        /**< An audio device has been removed. */

    /* Render events */
    Key_RENDER_TARGETS_RESET = 0x2000, /**< The render targets have been reset and their contents need to be updated */
    Key_RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */

    /** Events ::Key_USEREVENT through ::Key_LASTEVENT are for your use,
     *  and should be allocated with Key_RegisterEvents()
     */
    Key_USEREVENT    = 0x8000,

    /**
     *  This last event is only for bounding internal arrays
     */
    Key_LASTEVENT    = 0xFFFF
} Key_EventType;
typedef enum
{
    Key_SCANCODE_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    Key_SCANCODE_A = 4,
    Key_SCANCODE_B = 5,
    Key_SCANCODE_C = 6,
    Key_SCANCODE_D = 7,
    Key_SCANCODE_E = 8,
    Key_SCANCODE_F = 9,
    Key_SCANCODE_G = 10,
    Key_SCANCODE_H = 11,
    Key_SCANCODE_I = 12,
    Key_SCANCODE_J = 13,
    Key_SCANCODE_K = 14,
    Key_SCANCODE_L = 15,
    Key_SCANCODE_M = 16,
    Key_SCANCODE_N = 17,
    Key_SCANCODE_O = 18,
    Key_SCANCODE_P = 19,
    Key_SCANCODE_Q = 20,
    Key_SCANCODE_R = 21,
    Key_SCANCODE_S = 22,
    Key_SCANCODE_T = 23,
    Key_SCANCODE_U = 24,
    Key_SCANCODE_V = 25,
    Key_SCANCODE_W = 26,
    Key_SCANCODE_X = 27,
    Key_SCANCODE_Y = 28,
    Key_SCANCODE_Z = 29,

    Key_SCANCODE_1 = 30,
    Key_SCANCODE_2 = 31,
    Key_SCANCODE_3 = 32,
    Key_SCANCODE_4 = 33,
    Key_SCANCODE_5 = 34,
    Key_SCANCODE_6 = 35,
    Key_SCANCODE_7 = 36,
    Key_SCANCODE_8 = 37,
    Key_SCANCODE_9 = 38,
    Key_SCANCODE_0 = 39,

    Key_SCANCODE_RETURN = 40,
    Key_SCANCODE_ESCAPE = 41,
    Key_SCANCODE_BACKSPACE = 42,
    Key_SCANCODE_TAB = 43,
    Key_SCANCODE_SPACE = 44,

    Key_SCANCODE_MINUS = 45,
    Key_SCANCODE_EQUALS = 46,
    Key_SCANCODE_LEFTBRACKET = 47,
    Key_SCANCODE_RIGHTBRACKET = 48,
    Key_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    Key_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate Key_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    Key_SCANCODE_SEMICOLON = 51,
    Key_SCANCODE_APOSTROPHE = 52,
    Key_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    Key_SCANCODE_COMMA = 54,
    Key_SCANCODE_PERIOD = 55,
    Key_SCANCODE_SLASH = 56,

    Key_SCANCODE_CAPSLOCK = 57,

    Key_SCANCODE_F1 = 58,
    Key_SCANCODE_F2 = 59,
    Key_SCANCODE_F3 = 60,
    Key_SCANCODE_F4 = 61,
    Key_SCANCODE_F5 = 62,
    Key_SCANCODE_F6 = 63,
    Key_SCANCODE_F7 = 64,
    Key_SCANCODE_F8 = 65,
    Key_SCANCODE_F9 = 66,
    Key_SCANCODE_F10 = 67,
    Key_SCANCODE_F11 = 68,
    Key_SCANCODE_F12 = 69,

    Key_SCANCODE_PRINTSCREEN = 70,
    Key_SCANCODE_SCROLLLOCK = 71,
    Key_SCANCODE_PAUSE = 72,
    Key_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    Key_SCANCODE_HOME = 74,
    Key_SCANCODE_PAGEUP = 75,
    Key_SCANCODE_DELETE = 76,
    Key_SCANCODE_END = 77,
    Key_SCANCODE_PAGEDOWN = 78,
    Key_SCANCODE_RIGHT = 79,
    Key_SCANCODE_LEFT = 80,
    Key_SCANCODE_DOWN = 81,
    Key_SCANCODE_UP = 82,

    Key_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    Key_SCANCODE_KP_DIVIDE = 84,
    Key_SCANCODE_KP_MULTIPLY = 85,
    Key_SCANCODE_KP_MINUS = 86,
    Key_SCANCODE_KP_PLUS = 87,
    Key_SCANCODE_KP_ENTER = 88,
    Key_SCANCODE_KP_1 = 89,
    Key_SCANCODE_KP_2 = 90,
    Key_SCANCODE_KP_3 = 91,
    Key_SCANCODE_KP_4 = 92,
    Key_SCANCODE_KP_5 = 93,
    Key_SCANCODE_KP_6 = 94,
    Key_SCANCODE_KP_7 = 95,
    Key_SCANCODE_KP_8 = 96,
    Key_SCANCODE_KP_9 = 97,
    Key_SCANCODE_KP_0 = 98,
    Key_SCANCODE_KP_PERIOD = 99,

    Key_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
																						*   keyboards have over ANSI ones,
																						*   located between left shift and Y.
																						*   Produces GRAVE ACCENT and TILDE in a
																						*   US or UK Mac layout, REVERSE SOLIDUS
																						*   (backslash) and VERTICAL LINE in a
																						*   US or UK Windows layout, and
																						*   LESS-THAN SIGN and GREATER-THAN SIGN
																						*   in a Swiss German, German, or French
																						*   layout. */
    Key_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
    Key_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
															   *   not a physical key - but some Mac keyboards
															   *   do have a power key. */
    Key_SCANCODE_KP_EQUALS = 103,
    Key_SCANCODE_F13 = 104,
    Key_SCANCODE_F14 = 105,
    Key_SCANCODE_F15 = 106,
    Key_SCANCODE_F16 = 107,
    Key_SCANCODE_F17 = 108,
    Key_SCANCODE_F18 = 109,
    Key_SCANCODE_F19 = 110,
    Key_SCANCODE_F20 = 111,
    Key_SCANCODE_F21 = 112,
    Key_SCANCODE_F22 = 113,
    Key_SCANCODE_F23 = 114,
    Key_SCANCODE_F24 = 115,
    Key_SCANCODE_EXECUTE = 116,
    Key_SCANCODE_HELP = 117,
    Key_SCANCODE_MENU = 118,
    Key_SCANCODE_SELECT = 119,
    Key_SCANCODE_STOP = 120,
    Key_SCANCODE_AGAIN = 121,   /**< redo */
    Key_SCANCODE_UNDO = 122,
    Key_SCANCODE_CUT = 123,
    Key_SCANCODE_COPY = 124,
    Key_SCANCODE_PASTE = 125,
    Key_SCANCODE_FIND = 126,
    Key_SCANCODE_MUTE = 127,
    Key_SCANCODE_VOLUMEUP = 128,
    Key_SCANCODE_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     Key_SCANCODE_LOCKINGCAPSLOCK = 130,  */
/*     Key_SCANCODE_LOCKINGNUMLOCK = 131, */
/*     Key_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    Key_SCANCODE_KP_COMMA = 133,
    Key_SCANCODE_KP_EQUALSAS400 = 134,

    Key_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    Key_SCANCODE_INTERNATIONAL2 = 136,
    Key_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
    Key_SCANCODE_INTERNATIONAL4 = 138,
    Key_SCANCODE_INTERNATIONAL5 = 139,
    Key_SCANCODE_INTERNATIONAL6 = 140,
    Key_SCANCODE_INTERNATIONAL7 = 141,
    Key_SCANCODE_INTERNATIONAL8 = 142,
    Key_SCANCODE_INTERNATIONAL9 = 143,
    Key_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
    Key_SCANCODE_LANG2 = 145, /**< Hanja conversion */
    Key_SCANCODE_LANG3 = 146, /**< Katakana */
    Key_SCANCODE_LANG4 = 147, /**< Hiragana */
    Key_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    Key_SCANCODE_LANG6 = 149, /**< reserved */
    Key_SCANCODE_LANG7 = 150, /**< reserved */
    Key_SCANCODE_LANG8 = 151, /**< reserved */
    Key_SCANCODE_LANG9 = 152, /**< reserved */

    Key_SCANCODE_ALTERASE = 153, /**< Erase-Eaze */
    Key_SCANCODE_SYSREQ = 154,
    Key_SCANCODE_CANCEL = 155,
    Key_SCANCODE_CLEAR = 156,
    Key_SCANCODE_PRIOR = 157,
    Key_SCANCODE_RETURN2 = 158,
    Key_SCANCODE_SEPARATOR = 159,
    Key_SCANCODE_OUT = 160,
    Key_SCANCODE_OPER = 161,
    Key_SCANCODE_CLEARAGAIN = 162,
    Key_SCANCODE_CRSEL = 163,
    Key_SCANCODE_EXSEL = 164,

    Key_SCANCODE_KP_00 = 176,
    Key_SCANCODE_KP_000 = 177,
    Key_SCANCODE_THOUSANDSSEPARATOR = 178,
    Key_SCANCODE_DECIMALSEPARATOR = 179,
    Key_SCANCODE_CURRENCYUNIT = 180,
    Key_SCANCODE_CURRENCYSUBUNIT = 181,
    Key_SCANCODE_KP_LEFTPAREN = 182,
    Key_SCANCODE_KP_RIGHTPAREN = 183,
    Key_SCANCODE_KP_LEFTBRACE = 184,
    Key_SCANCODE_KP_RIGHTBRACE = 185,
    Key_SCANCODE_KP_TAB = 186,
    Key_SCANCODE_KP_BACKSPACE = 187,
    Key_SCANCODE_KP_A = 188,
    Key_SCANCODE_KP_B = 189,
    Key_SCANCODE_KP_C = 190,
    Key_SCANCODE_KP_D = 191,
    Key_SCANCODE_KP_E = 192,
    Key_SCANCODE_KP_F = 193,
    Key_SCANCODE_KP_XOR = 194,
    Key_SCANCODE_KP_POWER = 195,
    Key_SCANCODE_KP_PERCENT = 196,
    Key_SCANCODE_KP_LESS = 197,
    Key_SCANCODE_KP_GREATER = 198,
    Key_SCANCODE_KP_AMPERSAND = 199,
    Key_SCANCODE_KP_DBLAMPERSAND = 200,
    Key_SCANCODE_KP_VERTICALBAR = 201,
    Key_SCANCODE_KP_DBLVERTICALBAR = 202,
    Key_SCANCODE_KP_COLON = 203,
    Key_SCANCODE_KP_HASH = 204,
    Key_SCANCODE_KP_SPACE = 205,
    Key_SCANCODE_KP_AT = 206,
    Key_SCANCODE_KP_EXCLAM = 207,
    Key_SCANCODE_KP_MEMSTORE = 208,
    Key_SCANCODE_KP_MEMRECALL = 209,
    Key_SCANCODE_KP_MEMCLEAR = 210,
    Key_SCANCODE_KP_MEMADD = 211,
    Key_SCANCODE_KP_MEMSUBTRACT = 212,
    Key_SCANCODE_KP_MEMMULTIPLY = 213,
    Key_SCANCODE_KP_MEMDIVIDE = 214,
    Key_SCANCODE_KP_PLUSMINUS = 215,
    Key_SCANCODE_KP_CLEAR = 216,
    Key_SCANCODE_KP_CLEARENTRY = 217,
    Key_SCANCODE_KP_BINARY = 218,
    Key_SCANCODE_KP_OCTAL = 219,
    Key_SCANCODE_KP_DECIMAL = 220,
    Key_SCANCODE_KP_HEXADECIMAL = 221,

    Key_SCANCODE_LCTRL = 224,
    Key_SCANCODE_LSHIFT = 225,
    Key_SCANCODE_LALT = 226, /**< alt, option */
    Key_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    Key_SCANCODE_RCTRL = 228,
    Key_SCANCODE_RSHIFT = 229,
    Key_SCANCODE_RALT = 230, /**< alt gr, option */
    Key_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

    Key_SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    Key_SCANCODE_AUDIONEXT = 258,
    Key_SCANCODE_AUDIOPREV = 259,
    Key_SCANCODE_AUDIOSTOP = 260,
    Key_SCANCODE_AUDIOPLAY = 261,
    Key_SCANCODE_AUDIOMUTE = 262,
    Key_SCANCODE_MEDIASELECT = 263,
    Key_SCANCODE_WWW = 264,
    Key_SCANCODE_MAIL = 265,
    Key_SCANCODE_CALCULATOR = 266,
    Key_SCANCODE_COMPUTER = 267,
    Key_SCANCODE_AC_SEARCH = 268,
    Key_SCANCODE_AC_HOME = 269,
    Key_SCANCODE_AC_BACK = 270,
    Key_SCANCODE_AC_FORWARD = 271,
    Key_SCANCODE_AC_STOP = 272,
    Key_SCANCODE_AC_REFRESH = 273,
    Key_SCANCODE_AC_BOOKMARKS = 274,

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    Key_SCANCODE_BRIGHTNESSDOWN = 275,
    Key_SCANCODE_BRIGHTNESSUP = 276,
    Key_SCANCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    Key_SCANCODE_KBDILLUMTOGGLE = 278,
    Key_SCANCODE_KBDILLUMDOWN = 279,
    Key_SCANCODE_KBDILLUMUP = 280,
    Key_SCANCODE_EJECT = 281,
    Key_SCANCODE_SLEEP = 282,

    Key_SCANCODE_APP1 = 283,
    Key_SCANCODE_APP2 = 284,

    /* @} *//* Walther keys */

    /* Add any other keys here. */

    Key_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
															for array bounds */
} Key_Scancode;

typedef enum
{
    Key_CONTROLLER_AXIS_INVALID = -1,
    Key_CONTROLLER_AXIS_LEFTX,
    Key_CONTROLLER_AXIS_LEFTY,
    Key_CONTROLLER_AXIS_RIGHTX,
    Key_CONTROLLER_AXIS_RIGHTY,
    Key_CONTROLLER_AXIS_TRIGGERLEFT,
    Key_CONTROLLER_AXIS_TRIGGERRIGHT,
    Key_CONTROLLER_AXIS_MAX
} Key_GameControllerAxis;

typedef enum
{
	Key_CONTROLLER_BUTTON_INVALID = -1,
	Key_CONTROLLER_BUTTON_A,
	Key_CONTROLLER_BUTTON_B,
	Key_CONTROLLER_BUTTON_X,
	Key_CONTROLLER_BUTTON_Y,
	Key_CONTROLLER_BUTTON_BACK,
	Key_CONTROLLER_BUTTON_GUIDE,
	Key_CONTROLLER_BUTTON_START,
	Key_CONTROLLER_BUTTON_LEFTSTICK,
	Key_CONTROLLER_BUTTON_RIGHTSTICK,
	Key_CONTROLLER_BUTTON_LEFTSHOULDER,
	Key_CONTROLLER_BUTTON_RIGHTSHOULDER,
	Key_CONTROLLER_BUTTON_DPAD_UP,
	Key_CONTROLLER_BUTTON_DPAD_DOWN,
	Key_CONTROLLER_BUTTON_DPAD_LEFT,
	Key_CONTROLLER_BUTTON_DPAD_RIGHT,
	Key_CONTROLLER_BUTTON_MAX
} Key_GameControllerButton;
