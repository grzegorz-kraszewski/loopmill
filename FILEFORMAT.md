#LoopMill project file format

Plaintext file, human editable. Rationale:
* Useful to test player engine while the editor is not yet ready.
* Easy to understand.
* While it is not very space conservative, we have XPK to deal with it.

##Line ends
Writer will emit Unix/Amiga style LF. Reader will handle LF, CRLF, CR.

##First line
Contains string "LoopMill", space and then version.revision as two decimal digits, no higher than 65535. Example:
 LoopMill 1.0
 
##Header
Contains ReadArgs()-parsable set of project parameters and metadata. List of keywords to be defined later, unknown are ignored.
To make it more readable, it may be split into several lines. An empty line ends the header.

##System exclusive messages
[todo]

##Patterns
Each row is a line. Tracks separated by "|". Entry looks like this:
 D C-4 7F 002 ---- 0736
Columns explanation:
1. Event (an editor will replace these letters with appropriate icons).
  * D - note on
  * U - note off
  * P - channel pressure
  * A - aftertouch
  * X - system exclusive
2. Note, typical tracker notation, but using MIDI scale. Note 60 ("central C") is C-4. MIDI note 0 is written as "C-/", (slash precedes 0 in ASCII). Note 127 is G-9. Note is ignored (and should not be written) for events "P" and "X".
3. Note velocity, or pressure. For "X" event, number of predefined SysEx.
4. Instrument number (hexadecimal) in instrument map specified in the header. Ignored (and should not be written) for any event except note on ("D").
5. The first effect. Two hexadecimal digits for effect number, two for parameter.
6. The second effect. The same as above.

A pattern is ended with an empty line. Number of rows in a pattern is arbitrary, but no higher than 256. Number of tracks in a line *must* be equal to number of tracks defined in the header.
