/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      EventTypes.hh
Purpose:        File that abstracts all window events into our own enum. This was in case we wanted to switch out window libs
                this was a mistake and a waste of time.
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Abstractions/WindowAbst.hpp>

namespace BE
{
    enum BE_EventType
    {
        BE_QUIT = SDL_QUIT, /**< User-requested quit */

        BE_WINDOWEVENT  = SDL_WINDOWEVENT,  /**< Window state change */
        BE_SYSWMEVENT   = SDL_SYSWMEVENT,   /**< System specific event */

        BE_KEYDOWN          = SDL_KEYDOWN,          /**< Key pressed */
        BE_KEYUP            = SDL_KEYUP,            /**< Key released */
        BE_TEXTEDITING      = SDL_TEXTEDITING,      /**< Keyboard text editing (composition) */
        BE_TEXTINPUT        = SDL_TEXTINPUT,        /**< Keyboard text input */
        BE_KEYMAPCHANGED    = SDL_KEYMAPCHANGED,    /**< Keymap changed due to a system event such as an input language or keyboard layout change. */

        BE_MOUSEMOTION      = SDL_MOUSEMOTION, /**< Mouse moved */
        BE_MOUSEBUTTONDOWN  = SDL_MOUSEBUTTONDOWN,  /**< Mouse button pressed */
        BE_MOUSEBUTTONUP    = SDL_MOUSEBUTTONUP,    /**< Mouse button released */
        BE_MOUSEWHEEL       = SDL_MOUSEWHEEL,       /**< Mouse wheel motion */

        BE_JOYAXISMOTION    = SDL_JOYAXISMOTION,    /**< Joystick axis motion */
        BE_JOYBALLMOTION    = SDL_JOYBALLMOTION,    /**< Joystick trackball motion */
        BE_JOYHATMOTION     = SDL_JOYHATMOTION,     /**< Joystick hat position change */
        BE_JOYBUTTONDOWN    = SDL_JOYBUTTONDOWN,    /**< Joystick button pressed */
        BE_JOYBUTTONUP      = SDL_JOYBUTTONUP,      /**< Joystick button released */
        BE_JOYDEVICEADDED   = SDL_JOYDEVICEADDED,   /**< A new joystick has been inserted into the system */
        BE_JOYDEVICEREMOVED = SDL_JOYDEVICEREMOVED, /**< An opened joystick has been removed */

        BE_CONTROLLERAXISMOTION     = SDL_CONTROLLERAXISMOTION,     /**< Game controller axis motion */
        BE_CONTROLLERBUTTONDOWN     = SDL_CONTROLLERBUTTONDOWN,     /**< Game controller button pressed */
        BE_CONTROLLERBUTTONUP       = SDL_CONTROLLERBUTTONUP,       /**< Game controller button released */
        BE_CONTROLLERDEVICEADDED    = SDL_CONTROLLERDEVICEADDED,    /**< A new Game controller has been inserted into the system */
        BE_CONTROLLERDEVICEREMOVED  = SDL_CONTROLLERDEVICEREMOVED,  /**< An opened Game controller has been removed */
        BE_CONTROLLERDEVICEREMAPPED = SDL_CONTROLLERDEVICEREMAPPED, /**< The controller mapping was updated */

        BE_CLIPBOARDUPDATE  = SDL_CLIPBOARDUPDATE, /**< The clipboard changed */

        BE_DROPFILE = SDL_DROPFILE, /**< The system requests a file open */

        BE_AUDIODEVICEADDED     = SDL_AUDIODEVICEADDED,     /**< A new audio device is available */
        BE_AUDIODEVICEREMOVED   = SDL_AUDIODEVICEREMOVED,   /**< An audio device has been removed. */

        BE_RENDER_TARGETS_RESET = SDL_RENDER_TARGETS_RESET, /**< The render targets have been reset and their contents need to be updated */
        BE_RENDER_DEVICE_RESET  = SDL_RENDER_DEVICE_RESET,  /**< The device has been reset and all textures need to be recreated */
    };

    enum BE_WindowEventID
    {
        BE_WINDOWEVENT_NONE         = SDL_WINDOWEVENT_NONE,         /**< Never used */
        BE_WINDOWEVENT_SHOWN        = SDL_WINDOWEVENT_SHOWN,        /**< Window has been shown */
        BE_WINDOWEVENT_HIDDEN       = SDL_WINDOWEVENT_HIDDEN,       /**< Window has been hidden */
        BE_WINDOWEVENT_EXPOSED      = SDL_WINDOWEVENT_EXPOSED,      /**< Window has been exposed and should be redrawn */
        BE_WINDOWEVENT_MOVED        = SDL_WINDOWEVENT_MOVED,        /**< Window has been moved to data1, data2 */
        BE_WINDOWEVENT_RESIZED      = SDL_WINDOWEVENT_RESIZED,      /**< Window has been resized to data1xdata2 */
        BE_WINDOWEVENT_SIZE_CHANGED = SDL_WINDOWEVENT_SIZE_CHANGED, /**< The window size has changed, either as result of an API call or through the system or user changing the window size. */
        BE_WINDOWEVENT_MINIMIZED    = SDL_WINDOWEVENT_MINIMIZED,    /**< Window has been minimized */
        BE_WINDOWEVENT_MAXIMIZED    = SDL_WINDOWEVENT_MAXIMIZED,    /**< Window has been maximized */
        BE_WINDOWEVENT_RESTORED     = SDL_WINDOWEVENT_RESTORED,     /**< Window has been restored to normal size and position */
        BE_WINDOWEVENT_ENTER        = SDL_WINDOWEVENT_ENTER,        /**< Window has gained mouse focus */
        BE_WINDOWEVENT_LEAVE        = SDL_WINDOWEVENT_LEAVE,        /**< Window has lost mouse focus */
        BE_WINDOWEVENT_FOCUS_GAINED = SDL_WINDOWEVENT_FOCUS_GAINED, /**< Window has gained keyboard focus */
        BE_WINDOWEVENT_FOCUS_LOST   = SDL_WINDOWEVENT_FOCUS_LOST,   /**< Window has lost keyboard focus */
        BE_WINDOWEVENT_CLOSE        = SDL_WINDOWEVENT_CLOSE         /**< The window manager requests that the window be closed */
    };
}