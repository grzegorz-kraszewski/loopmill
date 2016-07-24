/*###########################################*/
/*# LoopMill - tracker style MIDI sequencer #*/
/*# Grzegorz Kraszewski, 2016               #*/
/*###########################################*/

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/camd.h>

#include "main.h"

extern struct Library *DOSBase, *SysBase;

struct Library *CamdBase;



struct AppData
{
	struct MidiNode *mnode;
	struct MidiLink *mlink;
};	



const STRPTR ErrorMessages[] = {
	NULL,
	"Can't open camd.library v37+.",
	"Can't create MIDI node.",
	"Can't create MIDI link to \"out.0\"."
};


#define BANK_MSB   121
#define BANK_LSB     9
#define PROGRAM      0


ULONG Empty2(struct AppData *apd)
{
	ULONG result = E_NOMIDILINK;

	if (apd->mlink = AddMidiLink(apd->mnode, MLTYPE_Sender,
		MLINK_Location, (ULONG)"out.0",
	TAG_END))
	{
		Printf("MIDI link @ $%08lx.\n", (ULONG)apd->mlink);

		PutMidi(apd->mlink, 0xB0000000 + (BANK_MSB << 8));
		PutMidi(apd->mlink, 0xB0200000 + (BANK_LSB << 8));
		PutMidi(apd->mlink, 0xC0000000 + (PROGRAM << 16));
		Delay(5);

		PutMidi(apd->mlink, 0x903C7F00);
		Delay(100);
		PutMidi(apd->mlink, 0x803C0000);
		RemoveMidiLink(apd->mlink);
		result = 0;
	}
	return result;
}



ULONG Empty(struct AppData *apd)
{
	ULONG result = E_NOMIDINODE;

	if (apd->mnode = CreateMidi(
		MIDI_Name, APP_NAME,
	TAG_END))
	{
		Printf("MIDI node @ $%08lx.\n", apd->mnode);
		result = Empty2(apd);
		DeleteMidi(apd->mnode);
		
	}

	Printf("CamdBase = $%08lx.\n", CamdBase);
	return result;
};




ULONG GetCamd(struct AppData *apd)
{
	ULONG result = E_NOCAMD;

	if (CamdBase = OpenLibrary("camd.library", 37))
	{
		result = Empty(apd);
		CloseLibrary(CamdBase);
	}

	return result;
}


/*---------------*/

ULONG Main(void)
{
	struct AppData apd;
	ULONG error;

	error = GetCamd(&apd);

	if (error)
	{
		if (error < E_COUNT)
		{
			Printf(APP_NAME ": %s.\n", (LONG)ErrorMessages[error]);
		}
		else Printf(APP_NAME ": unknown error %lu.\n", error);
	}

	return error;
}
