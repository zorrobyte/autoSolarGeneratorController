# autoSolarGeneratorController

This sketch is simple. It does two things:
* Turns on a relay (fans) if temps from a DHT11 reaches 100F or above
* Monitor for a switch to be toggled to then trigger two relays, each for three seconds each.

I can now start/stop my generator (Champion 3500W) using the wireless fob (hooked to Arduino's relays). The Victron Venus's relay kicks on when the generator needs start/stopped.
