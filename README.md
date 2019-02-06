# autoSolarGeneratorController

This is an Arduino Sketch to (hopefully) automatically manage a generator and power inverter to deal with an RV's Solar and Generator power sources.

I have transfer switches, a charge controller for Solar, Inverter, a Victron Battery Monitor with low charge relay, etc. BUT what I don't have is a little switch on my control center that would either turn off my 120VAC inverter, or start my generator to power - and charge the house batteries.

So, I'm going to 3D Print a little case, put in a three position switch and some buttons, wire it all up in my RV.

Goals:
Three position switch that can control what happens when the Victron Battery Monitor triggers a low battery state (whatever I set as the "alarm" in Depth of Discharge setting).

Option 1: Start Generator
My Champion 3500W inverter generator has a remote wireless start. I want to trigger a relay which will push the generator start button.
A very important aspect of this is to monitor if the generator start was successful, and either try again to start, before throwing an alarm.

Option 2: Turn off Inverter
If I'm at a location where I don't want to, or can't start a noisy generator (such as at most parks during quiet hours), a low battery event will turn off the inverter (with all 120V loads). My camper's critical systems, like the furnace, fridge, etc run off 12V and are much lower draw, and a low voltage disconnect can switch these off if the battery voltage is dire (with an override switch for temporary, emergency operation. BSS LVD is awesome!)

Option 3: Manual control
The 3rd option for my 3 position switch is to simply do nothing.

Emergency failsafe:
I'll likely need to use the Victron's BMS RS232 port to receive data, which adds much complexity. Long story short, I want to kill all loads, period, if the battery bank reaches a critical state. House 12V systems are cutoff by the BSS LVD. The power inverter will only automatically turn off (built in function) if the bank reaches 10V (which is BAD for the batteries). Really "bad" design, imo - this should be user configurable.

So, I'll need to monitor DoD through the BMS's RS232 as a standard check, and force the inverter OFF if it reaches a critical state, regardless of any other conotrol structure. This accounts for the generator running out of fuel, etc.

WIP!
