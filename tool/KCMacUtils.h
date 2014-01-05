#ifndef KCMACUTILS_H
#define KCMACUTILS_H

#ifdef __APPLE__

#include <QMainWindow>

#include <Carbon/Carbon.h>
#include <objc/objc-runtime.h>

void macSetWindowOnAllWorkspaces(QMainWindow *window)
{
	int NSWindowCollectionBehaviorCanJoinAllSpaces = 1 << 0;
	
	objc_object *macView = reinterpret_cast<objc_object *>(window->winId());
	objc_object *macWindow = objc_msgSend(macView, sel_registerName("window"));
	objc_msgSend(macWindow, sel_registerName("setCollectionBehavior:"), NSWindowCollectionBehaviorCanJoinAllSpaces);
}

bool macApplicationIsActive()
{
	ProcessSerialNumber myPSN;
	if(GetCurrentProcess(&myPSN) != noErr)
		qFatal("<Mac> Error getting PSN!");
	
	ProcessSerialNumber frontPSN;
	if(GetFrontProcess(&frontPSN) != noErr)
		qFatal("<Mac> Error getting front PSN!");
	
	return (myPSN.highLongOfPSN == frontPSN.highLongOfPSN &&
			myPSN.lowLongOfPSN == frontPSN.lowLongOfPSN);
}

void macApplicationActivate()
{
	ProcessSerialNumber myPSN;
	if(GetCurrentProcess(&myPSN) != noErr)
		qFatal("<Mac> Error getting PSN!");
	else SetFrontProcess(&myPSN);
}

#endif

#endif
