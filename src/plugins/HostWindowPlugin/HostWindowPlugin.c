/* Automatically generated by
	SmartSyntaxPluginCodeGenerator VMMaker-oscog.8 uuid: b336429e-652e-4551-8d38-a00ef67eaa61
   from
	HostWindowPlugin VMMaker-oscog.8 uuid: b336429e-652e-4551-8d38-a00ef67eaa61
 */
static char __buildInfo[] = "HostWindowPlugin VMMaker-oscog.8 uuid: b336429e-652e-4551-8d38-a00ef67eaa61 " __DATE__ ;




#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif
#include "HostWindowPlugin.h"

#include "sqMemoryAccess.h"



/*** Constants ***/


/*** Function Prototypes ***/
static VirtualMachine * getInterpreter(void);
EXPORT(const char*) getModuleName(void);
static sqInt halt(void);
static sqInt msg(char *s);
static sqInt pointFromCompactPointEncoding(sqInt encodedPoint);
EXPORT(sqInt) primitiveCloseHostWindow(void);
EXPORT(sqInt) primitiveCreateHostWindow(void);
EXPORT(sqInt) primitiveHostWindowPosition(void);
EXPORT(sqInt) primitiveHostWindowPositionSet(void);
EXPORT(sqInt) primitiveHostWindowScreenWorkAreaPosition(void);
EXPORT(sqInt) primitiveHostWindowScreenWorkAreaSize(void);
EXPORT(sqInt) primitiveHostWindowSize(void);
EXPORT(sqInt) primitiveHostWindowSizeSet(void);
EXPORT(sqInt) primitiveHostWindowTitle(void);
EXPORT(sqInt) primitiveNativeDisplayPosition(void);
EXPORT(sqInt) primitiveNativeDisplaySize(void);
EXPORT(sqInt) primitiveNativeWindowPosition(void);
EXPORT(sqInt) primitiveNativeWindowSize(void);
EXPORT(sqInt) primitiveSetCursorPosition(void);
EXPORT(sqInt) primitiveShowHostWindowRect(void);
EXPORT(sqInt) primitiveSqueakWindowHandle(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
EXPORT(sqInt) shutdownModule(void);
static void sqAssert(sqInt aBool);


/*** Variables ***/

#ifdef SQUEAK_BUILTIN_PLUGIN
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"HostWindowPlugin VMMaker-oscog.8 (i)"
#else
	"HostWindowPlugin VMMaker-oscog.8 (e)"
#endif
;



/*	Note: This is coded so that plugins can be run from Squeak. */

static VirtualMachine *
getInterpreter(void) {
	return interpreterProxy;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*)
getModuleName(void) {
	return moduleName;
}

static sqInt
halt(void) {
	;
	return 0;
}

static sqInt
msg(char *s) {
	fprintf(stderr, "\n%s: %s", moduleName, s);
	return 0;
}


/*	Answer a point from one of the funky encoded x,y position/size values the
	VM uses.
	The issue here is that the values can be negative, each value being in the
	range -32768 to 32767
 */

static sqInt
pointFromCompactPointEncoding(sqInt encodedPoint) {
	return interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) encodedPoint) >> 16)), ((short) (encodedPoint & 65535)));
}


/*	Close a host window. windowIndex is the SmallInt handle returned
	previously by primitiveCreateHostWindow. Fail if the index is invalid or
	the platform code fails
 */

EXPORT(sqInt)
primitiveCloseHostWindow(void) {
	sqInt ok;
	sqInt windowIndex;

	windowIndex = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	ok = closeWindow(windowIndex);
	if (!(ok)) {
		interpreterProxy->primitiveFail();
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(1);
	return null;
}


/*	Create a host window of width 'w' pixels, height 'h' with the origin of
	the user area at 'x@y' from the topleft corner of the screen.
	Return the SmallInt value of the internal index to the window description
	block - which is whatever the host platform code needs it to be.
 */

EXPORT(sqInt)
primitiveCreateHostWindow(void) {
	sqInt windowIndex;
	sqInt listLength;
	sqInt w;
	sqInt h;
	sqInt x;
	sqInt y;
	char *list;
	sqInt _return_value;

	w = interpreterProxy->stackIntegerValue(4);
	h = interpreterProxy->stackIntegerValue(3);
	x = interpreterProxy->stackIntegerValue(2);
	y = interpreterProxy->stackIntegerValue(1);
	interpreterProxy->success(interpreterProxy->isBytes(interpreterProxy->stackValue(0)));
	list = ((char *) (interpreterProxy->firstIndexableField(interpreterProxy->stackValue(0))));
	if (interpreterProxy->failed()) {
		return null;
	}
	listLength = interpreterProxy->slotSizeOf(((sqInt)(long)(list) - 4));
	windowIndex = createWindowWidthheightoriginXyattrlength(w, h, x, y, list, listLength);
	if (windowIndex > 0) {
		_return_value = interpreterProxy->integerObjectOf(windowIndex);
		if (interpreterProxy->failed()) {
			return null;
		}
		interpreterProxy->popthenPush(6, _return_value);
		return null;
	}
	else {
		interpreterProxy->primitiveFail();
		return null;
	}
}


/*	Return the origin position of the user area of the window in pixels from
	the topleft corner of the screen. Fail if the windowIndex is invalid or
	the platform routine returns -1 to indicate failure
 */

EXPORT(sqInt)
primitiveHostWindowPosition(void) {
	sqInt pos;
	sqInt windowIndex;
	sqInt _return_value;

	windowIndex = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	pos = ioPositionOfWindow(windowIndex);
	if (pos == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) pos) >> 16)), ((short) (pos & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}


/*	Set the origin position of the user area of the window in pixels from the
	topleft corner of the screen- return the position actually set by the
	OS/GUI/window manager. Fail if the windowIndex is invalid or the platform
	routine returns -1 to indicate failure
 */

EXPORT(sqInt)
primitiveHostWindowPositionSet(void) {
	sqInt pos;
	sqInt windowIndex;
	sqInt x;
	sqInt y;
	sqInt _return_value;

	windowIndex = interpreterProxy->stackIntegerValue(2);
	x = interpreterProxy->stackIntegerValue(1);
	y = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	pos = ioPositionOfWindowSetxy(windowIndex, x, y);
	if (pos == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) pos) >> 16)), ((short) (pos & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(4, _return_value);
	return null;
}


/*	Answer the platform's notion of the available work area on the screen
	containing the given window.
 */

EXPORT(sqInt)
primitiveHostWindowScreenWorkAreaPosition(void) {
	sqInt size;
	sqInt windex;
	sqInt _return_value;

	windex = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	size = ioPositionOfScreenWorkArea(windex);
	if (size == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}


/*	Answer the platform's notion of the available work area on the screen
	containing the given window.
 */

EXPORT(sqInt)
primitiveHostWindowScreenWorkAreaSize(void) {
	sqInt size;
	sqInt windex;
	sqInt _return_value;

	windex = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	size = ioSizeOfScreenWorkArea(windex);
	if (size == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}


/*	Return the size of the user area of the window in pixels. Fail if the
	windowIndex is invalid or the platform routine returns -1 to indicate
	failure 
 */

EXPORT(sqInt)
primitiveHostWindowSize(void) {
	sqInt size;
	sqInt windowIndex;
	sqInt _return_value;

	windowIndex = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	size = ioSizeOfWindow(windowIndex);
	if (size == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}


/*	Set the size of the user area of the window in pixels - return what is
	actually set by the OS/GUI/window manager. Fail if the windowIndex is
	invalid or the platform routine returns -1 to indicate failure
 */

EXPORT(sqInt)
primitiveHostWindowSizeSet(void) {
	sqInt size;
	sqInt windowIndex;
	sqInt x;
	sqInt y;
	sqInt _return_value;

	windowIndex = interpreterProxy->stackIntegerValue(2);
	x = interpreterProxy->stackIntegerValue(1);
	y = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	size = ioSizeOfWindowSetxy(windowIndex, x, y);
	if (size == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(4, _return_value);
	return null;
}


/*	Set the title bar label of the window. Fail if the windowIndex is invalid
	or the platform routine returns -1 to indicate failure
 */

EXPORT(sqInt)
primitiveHostWindowTitle(void) {
	sqInt res;
	sqInt titleLength;
	sqInt id;
	char *titleString;

	id = interpreterProxy->stackIntegerValue(1);
	interpreterProxy->success(interpreterProxy->isBytes(interpreterProxy->stackValue(0)));
	titleString = ((char *) (interpreterProxy->firstIndexableField(interpreterProxy->stackValue(0))));
	if (interpreterProxy->failed()) {
		return null;
	}
	titleLength = interpreterProxy->slotSizeOf(((sqInt)(long)(titleString) - 4));
	res = ioSetTitleOfWindow(id, titleString, titleLength);
	if (res == -1) {
		interpreterProxy->primitiveFail();
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(2);
	return null;
}


/*	Answer the origin position of the user area of the given native window in
	pixels from the topleft corner of the screen.
	Fail if the windowHandle is invalid or the platform routine returns -1 to
	indicate failure
 */

EXPORT(sqInt)
primitiveNativeDisplayPosition(void) {
	sqInt pos;
	unsigned long windowHandle;
	sqInt _return_value;

	windowHandle = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	pos = ioPositionOfNativeDisplay(windowHandle);
	if (pos == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) pos) >> 16)), ((short) (pos & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}


/*	Answer the size of the user area of the given native window in pixels.
	Fail if the windowHandle is invalid or the platform routine returns -1 to
	indicate failure */

EXPORT(sqInt)
primitiveNativeDisplaySize(void) {
	sqInt size;
	unsigned long windowHandle;
	sqInt _return_value;

	windowHandle = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	size = ioSizeOfNativeDisplay(windowHandle);
	if (size == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}


/*	Answer the origin position of the given native window in pixels from the
	topleft corner of the screen.
	Fail if the windowHandle is invalid or the platform routine returns -1 to
	indicate failure
 */

EXPORT(sqInt)
primitiveNativeWindowPosition(void) {
	sqInt pos;
	unsigned long windowHandle;
	sqInt _return_value;

	windowHandle = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	pos = ioPositionOfNativeWindow(windowHandle);
	if (pos == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) pos) >> 16)), ((short) (pos & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}


/*	Answer the size of the given native window in pixels.
	Fail if the windowHandle is invalid or the platform routine returns -1 to
	indicate failure */

EXPORT(sqInt)
primitiveNativeWindowSize(void) {
	sqInt size;
	unsigned long windowHandle;
	sqInt _return_value;

	windowHandle = interpreterProxy->positive32BitValueOf(interpreterProxy->stackValue(0));
	if (interpreterProxy->failed()) {
		return null;
	}
	size = ioSizeOfNativeWindow(windowHandle);
	if (size == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->makePointwithxValueyValue(((short) (((usqInt) size) >> 16)), ((short) (size & 65535)));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(2, _return_value);
	return null;
}


/*	Set the position of the cursor to the specified position on the desktop.
	Fail if the platform routine returns -1 to indicate failure. */

EXPORT(sqInt)
primitiveSetCursorPosition(void) {
	sqInt result;
	sqInt x;
	sqInt y;

	x = interpreterProxy->stackIntegerValue(1);
	y = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	result = ioSetCursorPositionXY(x, y);
	if (result == -1) {
		interpreterProxy->primitiveFail();
		return null;
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(2);
	return null;
}


/*	Host window analogue of DisplayScreen> primShowRectLeft:right:top:bottom:
	(Interpreter>primitiveShowDisplayRect) which takes the window index,
	bitmap details and the rectangle bounds. Fail if the windowIndex is
	invalid or the
	platform routine returns false to indicate failure
 */

EXPORT(sqInt)
primitiveShowHostWindowRect(void) {
	sqInt ok;
	sqInt windowIndex;
	usqInt *dispBits;
	sqInt w;
	sqInt h;
	sqInt d;
	sqInt left;
	sqInt right;
	sqInt top;
	sqInt bottom;

	windowIndex = interpreterProxy->stackIntegerValue(8);
	interpreterProxy->success(interpreterProxy->isWords(interpreterProxy->stackValue(7)));
	dispBits = ((unsigned *) (interpreterProxy->firstIndexableField(interpreterProxy->stackValue(7))));
	w = interpreterProxy->stackIntegerValue(6);
	h = interpreterProxy->stackIntegerValue(5);
	d = interpreterProxy->stackIntegerValue(4);
	left = interpreterProxy->stackIntegerValue(3);
	right = interpreterProxy->stackIntegerValue(2);
	top = interpreterProxy->stackIntegerValue(1);
	bottom = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	ok = ioShowDisplayOnWindow(dispBits, w, h, d, left, right, top,
bottom, windowIndex);
	if (!(ok)) {
		interpreterProxy->primitiveFail();
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(9);
	return null;
}


/*	Answer the native Squeak window handle, presumably a pointer, as an
	unsigned integer.
	This value should be usable in native calls to the window manager as well
	as the argument to primitiveNativeWindowPosition: */

EXPORT(sqInt)
primitiveSqueakWindowHandle(void) {
	void *handle;
	sqInt _return_value;

	handle = ioGetWindowHandle();
	if (handle == 0) {
		interpreterProxy->primitiveFail();
		return null;
	}
	_return_value = interpreterProxy->positive32BitIntegerFor(((sqInt) handle));
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush(1, _return_value);
	return null;
}


/*	Note: This is coded so that is can be run from Squeak. */

EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter) {
	sqInt ok;

	interpreterProxy = anInterpreter;
	ok = interpreterProxy->majorVersion() == VM_PROXY_MAJOR;
	if (ok == 0) {
		return 0;
	}
	ok = interpreterProxy->minorVersion() >= VM_PROXY_MINOR;
	return ok;
}


/*	do any window related VM closing down work your platform requires. */

EXPORT(sqInt)
shutdownModule(void) {
	return ioCloseAllWindows();
}

static void
sqAssert(sqInt aBool) {
	/* missing DebugCode */;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

void* HostWindowPlugin_exports[][3] = {
	{"HostWindowPlugin", "getModuleName", (void*)getModuleName},
	{"HostWindowPlugin", "primitiveCloseHostWindow", (void*)primitiveCloseHostWindow},
	{"HostWindowPlugin", "primitiveCreateHostWindow", (void*)primitiveCreateHostWindow},
	{"HostWindowPlugin", "primitiveHostWindowPosition", (void*)primitiveHostWindowPosition},
	{"HostWindowPlugin", "primitiveHostWindowPositionSet", (void*)primitiveHostWindowPositionSet},
	{"HostWindowPlugin", "primitiveHostWindowScreenWorkAreaPosition", (void*)primitiveHostWindowScreenWorkAreaPosition},
	{"HostWindowPlugin", "primitiveHostWindowScreenWorkAreaSize", (void*)primitiveHostWindowScreenWorkAreaSize},
	{"HostWindowPlugin", "primitiveHostWindowSize", (void*)primitiveHostWindowSize},
	{"HostWindowPlugin", "primitiveHostWindowSizeSet", (void*)primitiveHostWindowSizeSet},
	{"HostWindowPlugin", "primitiveHostWindowTitle", (void*)primitiveHostWindowTitle},
	{"HostWindowPlugin", "primitiveNativeDisplayPosition", (void*)primitiveNativeDisplayPosition},
	{"HostWindowPlugin", "primitiveNativeDisplaySize", (void*)primitiveNativeDisplaySize},
	{"HostWindowPlugin", "primitiveNativeWindowPosition", (void*)primitiveNativeWindowPosition},
	{"HostWindowPlugin", "primitiveNativeWindowSize", (void*)primitiveNativeWindowSize},
	{"HostWindowPlugin", "primitiveSetCursorPosition", (void*)primitiveSetCursorPosition},
	{"HostWindowPlugin", "primitiveShowHostWindowRect", (void*)primitiveShowHostWindowRect},
	{"HostWindowPlugin", "primitiveSqueakWindowHandle", (void*)primitiveSqueakWindowHandle},
	{"HostWindowPlugin", "setInterpreter", (void*)setInterpreter},
	{"HostWindowPlugin", "shutdownModule", (void*)shutdownModule},
	{NULL, NULL, NULL}
};

#endif /* ifdef SQ_BUILTIN_PLUGIN */