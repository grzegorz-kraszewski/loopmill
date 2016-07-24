/*###########################################*/
/*# LoopMill - tracker style MIDI sequencer #*/
/*# Grzegorz Kraszewski, 2016               #*/
/*###########################################*/


#define APP_NAME                 "LoopMill"
#define APP_VER                  0
#define APP_REV                  1
#define APP_VERSION              "0.1"
#define APP_DATE                 "24.7.2016"

/*-------------*/
/* Error codes */
/*-------------*/

#define E_NOCAMD                 1
#define E_NOMIDINODE             2
#define E_NOMIDILINK             3

#define E_COUNT                  3


/*---------------*/
/* Library bases */
/*---------------*/

extern struct Library
	*SysBase,
	*DOSBase,
	*CamdBase;