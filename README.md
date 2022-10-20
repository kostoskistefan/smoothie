# Smoothie

Smoothie is a software that converts your digital keyboard into an analog input device. It's designed to be used in driving games where you need more precision.

## Concept

Once you start Smoothie, a new virtual HID device called **Smoothie Virtual Controller** will be created.

Make sure to start Smoothie **BEFORE** you start the game or other piece of software which requires analog input.

Pressing one of the Action Keys will lock the steering to a particular percentage. After doing so, pressing the steering keys will only move the virtual X axis by the selected percentage.

## Disclaimer

This tool can be considered as cheating for certain games, make sure to do some research before actually using Smoothie.

I am not responsible for any negative outcomes that might come out from using this tool.

## Dependencies

 * libsigc++

## Configuration

To change the default key bindings, you need to edit the configuration file and restart Smoothie.

Configuration file location:
 * Linux: `$HOME/.config/smoothie/smoothie.cfg`

Additionally, to run smoothie on Linux you need to be a member of the group `input` (or alternatively, run it as root).

### Defaults

The default keymap is as follows:

| Key          | Action                          |
| ------------ | ------------------------------- |
| Up arrow     | Emulates a Y button press       |
| Down arrow   | Emulates a X button press       |
| Left arrow   | Moves the X axis to the left    |
| Right arrow  | Moves the X axis to the right   |
| 1            | Set steering percentage to 10%  |
| 2            | Set steering percentage to 20%  |
| 3            | Set steering percentage to 30%  |
| 4            | Set steering percentage to 40%  |
| 5            | Set steering percentage to 50%  |
| 6            | Set steering percentage to 60%  |
| 7            | Set steering percentage to 70%  |
| 8            | Set steering percentage to 80%  |
| 9            | Set steering percentage to 90%  |
| 0            | Set steering percentage to 100% |

### Format

Under the `[Key Bindings]` section in the configuration file, you will find which key is bound to a particular action.

The format of the configuratio file follows a simple concept: 
`ACTION = KEY_CODE`

 * The `ACTION` part should be replaced by one of the [available actions](#Actions).
 * The `KEY_CODE` part should be replaced by a one of the [available keys](#Keys).

If you do not wish to bind any key to an action, leave the `KEY_CODE` part blank (but leave the equal `=` sign). Example: `Action Key 3 = `.

All empty lines or lines that start with a hashtag `#` or a left bracket `[` symbol will be ignored.

### Actions

| ACTION        | Explanation                         |
| ------------- | ----------------------------------- |
| Accelerate    | Emulate an Y button press           |
| Brake         | Emulate a X button press            |
| Steer Left    | Move the X axis to the left         |
| Steer Reft    | Move the X axis to the right        |
| Action Key 1  | Set the steering percentage to 10%  |
| Action Key 2  | Set the steering percentage to 20%  |
| Action Key 3  | Set the steering percentage to 30%  |
| Action Key 4  | Set the steering percentage to 40%  |
| Action Key 5  | Set the steering percentage to 50%  |
| Action Key 6  | Set the steering percentage to 60%  |
| Action Key 7  | Set the steering percentage to 70%  |
| Action Key 8  | Set the steering percentage to 80%  |
| Action Key 9  | Set the steering percentage to 90%  |
| Action Key 10 | Set the steering percentage to 100% |

### Keys

| KEY_CODE   | Explanation       |
| ---------- | ----------------- |
| A          | Key A             |
| B          | Key B             |
| C          | Key C             |
| D          | Key D             |
| E          | Key E             |
| F          | Key F             |
| G          | Key G             |
| H          | Key H             |
| I          | Key I             |
| J          | Key J             |
| K          | Key K             |
| L          | Key L             |
| M          | Key M             |
| N          | Key N             |
| O          | Key O             |
| P          | Key P             |
| Q          | Key Q             |
| R          | Key R             |
| S          | Key S             |
| T          | Key T             |
| U          | Key U             |
| V          | Key V             |
| W          | Key W             |
| X          | Key X             |
| Y          | Key Y             |
| Z          | Key Z             |
| 0          | Key 0             |
| 1          | Key 1             |
| 2          | Key 2             |
| 3          | Key 3             |
| 4          | Key 4             |
| 5          | Key 5             |
| 6          | Key 6             |
| 7          | Key 7             |
| 8          | Key 8             |
| 9          | Key 9             |
| KP0        | Keypad 0          |
| KP1        | Keypad 1          |
| KP2        | Keypad 2          |
| KP3        | Keypad 3          |
| KP4        | Keypad 4          |
| KP5        | Keypad 5          |
| KP6        | Keypad 6          |
| KP7        | Keypad 7          |
| KP8        | Keypad 8          |
| KP9        | Keypad 9          |
| KPDOT      | Keypad Dot        |
| KPPLUS     | Keypad Plus       |
| KPSLASH    | Keypad Slash      |
| KPMINUS    | Keypad Minus      |
| KPENTER    | Keypad Enter      |
| KPASTERISK | Keypad Asterisk   |
| DOT        | Key Dot           |
| COMMA      | Key Comma         |
| SLASH      | Key Forward Slash |
| MINUS      | Key Minus         |
| EQUAL      | Key Equal         |
| LEFTBRACE  | Key Left Brace    |
| BACKSLASH  | Key Back Slash    |
| SEMICOLON  | Key Semicolon     |
| RIGHTBRACE | Key Right Brace   |
| APOSTROPHE | Key Apostrophe    |
| TAB        | Key Tab           |
| SPACE      | Key Space         |
| ENTER      | Key Enter         |
| BACKSPACE  | Key Backspace     |
| UP         | Key Up Arrow      |
| DOWN       | Key Down Arrow    |
| LEFT       | Key Left Arrow    |
| RIGHT      | Key Right Arrow   |
| F1         | Key F1            |
| F2         | Key F2            |
| F3         | Key F3            |
| F4         | Key F4            |
| F5         | Key F5            |
| F6         | Key F6            |
| F7         | Key F7            |
| F8         | Key F8            |
| F9         | Key F9            |
| F10        | Key F10           |
| F11        | Key F11           |
| F12        | Key F12           |
| END        | Key End           |
| ESC        | Key Escape        |
| HOME       | Key Home          |
| PRINT      | Key Print         |
| INSERT     | Key Insert        |
| DELETE     | Key Delete        |
| PAGEUP     | Key Page Up       |
| PAGEDOWN   | Key Page Down     |

## Getting help

If you have questions, concerns, bug reports, etc, please file an issue in this repository's [Issue Tracker](https://github.com/kostoskistefan/smoothie/issues).

## Getting involved

There are two primary ways to help:

 * Using the issue tracker
 * Changing the code-base
 
### Using the issue tracker

Use the [Issue Tracker](https://github.com/kostoskistefan/smoothie/issues) to suggest feature requests, report bugs, and ask questions. Any feedback is greatly appreciated.

### Changing the code base

If you want to directly affect the code, you should fork this repository, make changes on your own fork, then submit a pull request.
