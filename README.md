# LoopMill
MIDI sequencer for (classic) Amiga

## NOTE
This project has been archived, as I doubt I will have time to work on it.

## System requirements
* Processor. Plain 68000 @ 7 MHz should be enough for basic use. See no point in 020/030/040/060 compilation.
* Memory. Probably 1 MB will be enough, maybe limiting project size a bit.
* Graphic chipset. I will probably use 8 or 16 colours on a system screen (so all it works also on RTG screen). AGA not required. Minimum screen size: 640 x 256 pixels.
* Kickstart. Well, I will use the system extensively. Kick 3.0 is minimum.

To sum it up, stock A1200 is enough. It also should be practically usable on A500 with system 3.0. Note that hardware requirements for building from sources are higher. LoopMill is built natively on Amiga with 68020 @ 28 MHz and 64 MB fast RAM. Compiler used is native build of GCC 2.95.3.
* MIDI is handled via camd.library. It handles Amiga serial port, some extensions, as well as USB MIDI on nextgen systems.
* GUI toolkit. Well, MUI is nice, but too slow. I plan to use ProTracker style hand-made GUI.

## Basic ideas
* Tracker-style pattern editor. Adjustable number of tracks with free MIDI mapping (any track can be assigned to any MIDI port/channel).
* Possible feature: 4 tracks using Paula channels and samples (ProTracker like). Low priority.

## Pattern entry layout
* Event, probably one character using icon graphics. Note on, note off, channel pressure, aftertouch, [sysex].
* Event "force", 2 hex characters (00 to 7F). Velocity for notes, pressure for channel pressure and aftertouch.
* Note. For on/off and aftertouch. Empty for channel pressure.
* Instrument. 3 hex characters, so 4096 instruments possible. Indirectly covers Program Change and Bank Select controller via user editable maps. Takes care of proper bank/program change sequence. GM[2] map provided by default.
* Two(?) columns of effects. Each effect has 4 characters. First two are CC number. As there are only 127 CC-s, effects from $80 to $8F may be used to map ProTracker effects where applicable. Last 2 hex digits are used for controller value.
* How to handle 14-bit controllers? Separately? Extend value to 4 hex digits storing either 2 x 7 bits or one 14-bit number?
* Pitch bend should be mapped as controller $90.
