using namespace std;

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

#include "zlib/zlib.h"

using namespace zlib::draw;
using namespace zlib::input;
using namespace zlib::window;

#include "tracker.h"


class EliteProfitTrackerApp : public AppNative {
  public:
	void setup();

	void mouseDown( MouseEvent event );	
	void mouseUp(MouseEvent event);
	void mouseMove(MouseEvent event);
	void mouseDrag(MouseEvent event);
	void keyDown(KeyEvent event);
	void keyUp(KeyEvent event);

	void update();
	void draw();
	void resize();
};

void EliteProfitTrackerApp::setup()
{
	try
	{
		global::readData();
	}
	catch(...)
	{
		//If the file isn't present, and fileIO throws the 'fileNotFound' exception
	}
}

void EliteProfitTrackerApp::mouseDown( MouseEvent event )
{

}

void EliteProfitTrackerApp::mouseUp(MouseEvent event)
{

}

void EliteProfitTrackerApp::mouseMove(MouseEvent event)
{

}

void EliteProfitTrackerApp::mouseDrag(MouseEvent event)
{

}

void EliteProfitTrackerApp::keyDown(KeyEvent event)
{

}

void EliteProfitTrackerApp::keyUp(KeyEvent event)
{

}

void EliteProfitTrackerApp::update()
{

}

void EliteProfitTrackerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );


	
	
}

void EliteProfitTrackerApp::resize()
{
	getWindow()->setSize(500, 500);
	window::update();
}

CINDER_APP_NATIVE( EliteProfitTrackerApp, RendererGl )
