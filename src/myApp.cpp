#include "myApp.h"
#include "myFrame.h"

bool myApp::OnInit()
{
	myFrame *frame = new myFrame( "ffConvert", wxPoint(50, 50), wxSize(640, 480) );
    frame->Show( true );
	return true;
}
