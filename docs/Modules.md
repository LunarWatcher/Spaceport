# Modules

Spaceport relies on modules to do its stuff. These are split into two categories; hard-coded modules, and data modules.

## Built-in modules

## Data modules

Data modules support arbitrary data, and can be plugged into anything, including the dedicated client. The main purpose of this module is to support arbitrary data logging. This can be used for anything; sensors on servers, or external sensors feeding to a server, hardware monitoring, weather tracking, concurrent connections to a server, disk R/W speeds, network throughput, amount of deaths in some game server, ...

In general, if there isn't a built-in module for it, and it isn't common enough to warrant creating a proper module, data modules are what you're looking for.
