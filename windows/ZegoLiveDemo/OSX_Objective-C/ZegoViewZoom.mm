
#import <Foundation/Foundation.h>
#import <cocoa/cocoa.h>
#import "ZegoViewZoom.h"

void showMinimizedOnMac(QDialog *dialog)
{
    NSView *view = (NSView *)dialog->winId();
    NSWindow *wnd = [view window];
    [wnd miniaturize: wnd];
}

void showMaximizedOnMac(QDialog *dialog)
{
	NSView *view = (NSView *)dialog->winId();
    NSWindow *wnd = [view window];
    [wnd zoom: wnd];
}
