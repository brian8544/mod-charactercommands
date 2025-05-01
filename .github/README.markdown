# CharacterCommands Module

The `mod-charactercommands` module for AzerothCore adds chat commands that allow players to customize their characters, change their race, or switch their faction. By typing commands like `u customize`, `u changerace`, or `u changefaction`, players can trigger these changes, which are applied after logging out. This module provides a convenient way for players to personalize their characters without needing external tools or addons, inspired by similar features on popular World of Warcraft private servers.

## Requirements
- A standard AzerothCore server setup with the module properly installed.

## Installation
1. Clone this repository into your AzerothCore `modules` directory.
2. Re-run CMake and rebuild your AzerothCore server to include the `mod-charactercommands` module.
3. Ensure the module is enabled in your server configuration (check for `CharacterScripts.Enable` in your configuration file).

## Copyright
License: GPL 2.0