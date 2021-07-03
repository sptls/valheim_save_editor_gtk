#include <iostream>
#include <string.h>
#include "src/parser.h"
#include "src/gui_crap.h"
#include <gtkmm.h>


int main(int argc, char** argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("org.gtkmm.example");
	IHateGTK gui;
	gui.GetWidgets();
	
	return app->run(*gui.window);
}
