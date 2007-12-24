%{
#include <CEGUIInputEvent.h>
%}

%rename(Window) CEGUI::WindowEventArgs::window;

%rename(Position) CEGUI::MouseEventArgs::position;
%rename(MoveDelta) CEGUI::MouseEventArgs::moveDelta;
%rename(Button) CEGUI::MouseEventArgs::button;
%rename(SysKeys) CEGUI::MouseEventArgs::sysKeys;
%rename(WheelChange) CEGUI::MouseEventArgs::wheelChange;
%rename(ClickCount) CEGUI::MouseEventArgs::clickCount;

%rename(MouseCursor) CEGUI::MouseCursorEventArgs::mouseCursor;
%rename(Image) CEGUI::MouseCursorEventArgs::image;

%rename(Codepoint) CEGUI::KeyEventArgs::codepoint;
%rename(Scancode) CEGUI::KeyEventArgs::scancode;
%rename(SysKeys) CEGUI::KeyEventArgs::sysKeys;

%rename(OldIndex) CEGUI::HeaderSequenceEventArgs::d_oldIdx;
%rename(NewIndex) CEGUI::HeaderSequenceEventArgs::d_newIdx;

%rename(OtherWindow) CEGUI::ActivationEventArgs::otherWindow;

%rename(DragDropItem) CEGUI::DragDropEventArgs::dragDropItem;

%include /usr/include/CEGUI/CEGUIInputEvent.h