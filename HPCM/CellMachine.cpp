// CellMachine.cpp : Defines the entry point for the application.
//

#define SDL_MAIN_HANDLED

#include "ApplicationContext.hpp"
#include "CellMachine.h"
#include "Interface.hpp"
#include "Settings.hpp"
#include <cstdio>
#include <google/protobuf/stubs/common.h>
#include <SDL.h>
#include <SDL_events.h>
#include <test.pb.h>
#include "Logic/Logic.hpp"

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	CellMachine::ApplicationContext::initalize();
	CellMachine::Settings::load();
	SDL_Init(SDL_INIT_EVERYTHING);

	CellMachine::Logic::Logic::logic();

	SDL_Quit();
	CellMachine::ApplicationContext::destroy();
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
