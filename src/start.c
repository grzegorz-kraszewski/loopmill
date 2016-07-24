/*###########################################*/
/*# LoopMill - tracker style MIDI sequencer #*/
/*# Grzegorz Kraszewski, 2016               #*/
/*###########################################*/

#include <proto/exec.h>
#include <proto/dos.h>
#include <dos/dos.h>
#include <workbench/startup.h>

#include "main.h"

struct Library *SysBase;
struct Library *DOSBase;

extern ULONG Main(void);

__attribute__((saveds)) ULONG Start(void)
{
	struct Process *myproc = NULL;
	struct Message *wbmsg = NULL;
	BOOL have_shell = FALSE;
	ULONG result = RETURN_OK;

	SysBase = *(struct Library**)4L;
	myproc = (struct Process*)FindTask(NULL);
	if (myproc->pr_CLI) have_shell = TRUE;

	if (!have_shell)
	{
		WaitPort(&myproc->pr_MsgPort);
		wbmsg = GetMsg(&myproc->pr_MsgPort);
	}

	if (DOSBase = OpenLibrary("dos.library", 39))
	{
		result = Main();
		CloseLibrary(DOSBase);
	}
	else result = RETURN_FAIL;

	if (wbmsg)
	{
		Forbid();
		ReplyMsg(wbmsg);
	}

	return result;
}


__attribute__((section(".text"))) UBYTE VString[] =
	"$VER: " APP_NAME " " APP_VERSION " (" APP_DATE ")\r\n";
