/*!
\file CellMachine/ApplicationContext.cpp

\brief This file supplies the CellMachine::ApplicationContext namespace.

This module provides context about the application environment.

\see CellMachine/ApplicationContext.hpp
*/

#include "ApplicationContext.hpp"
#include <cstdio>
#include <filesystem>
#include <memory>
//#include <process.h>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <SDL_error.h>
#include <SDL_stdinc.h>

const char *CellMachine::ApplicationContext::basePathChar = nullptr;
const char *CellMachine::ApplicationContext::prefPathChar = nullptr;
std::string CellMachine::ApplicationContext::basePathString {};
std::string CellMachine::ApplicationContext::prefPathString {};
std::filesystem::path CellMachine::ApplicationContext::basePathPath {};
std::filesystem::path CellMachine::ApplicationContext::prefPathPath {};

void CellMachine::ApplicationContext::initalize() {

#pragma region Base Path
	basePathChar = SDL_GetBasePath();

	if (basePathChar == NULL) {
		/*
		// showsimplemessagebox might fail, and that stores it's own thing in SDL's error func, so we store it so that it can't be cleared.
		std::string errorMessage = SDL_GetError();

		if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ApplicationContext Initalization Failure", (std::string {
			"ApplicationContxt failed to initalize on start-up. The application will now close.\n"
			"\n"
			"Base path could not be initalized due to an error in SDL.\n"
			"The error reported by SDL: "} + errorMessage).c_str(),
			NULL) < 0)
		*/
			fprintf(stderr,
				"ApplicationContext failed to initalize on start-up. The application will now close.\n"
				"\n"
				"Base path could not be initalized due to an error in SDL.\n"
				"Additionally, an error occurred while attempting to display a msesage box.\n"
				"\n"
				"The error reported by SDL for the base path: %s\n",
				//"The error reported by SDL for the message box: %s\n",
				SDL_GetError());

		throw std::runtime_error((std::string("Base path initalization failure; ") + SDL_GetError()).c_str());
	}
#pragma endregion

#pragma region Pref Path
	prefPathChar = SDL_GetPrefPath("ProjectHSI", "HPCM");

	if (prefPathChar == NULL) {
		/*
		// showsimplemessagebox might fail, and that stores it's own thing in SDL's error func, so we store it so that it can't be cleared.
		std::string errorMessage = std::string(SDL_GetError());

		if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ApplicationContext Initalization Failure", (std::string {
			"ApplicationContxt failed to initalize on start-up. This is not a fatal error, and the application can continue (although preference saving may be disabled).\n"
			"\n"
			"Pref path could not be initalized due to an error in SDL.\n"
			"The error reported by SDL: "} + errorMessage).c_str(),
			NULL) < 0)
		*/
			fprintf(stderr,
				"ApplicationContext failed to initalize on start-up. This is not a fatal error, and the application can continue (although preference saving may be disabled).\n"
				"\n"
				"Pref path could not be initalized due to an error in SDL.\n"
				"Additionally, an error occurred while attempting to display a msesage box.\n"
				"\n"
				"The error reported by SDL for the pref path: %s\n",
				SDL_GetError());

	}
#pragma endregion

#pragma region Post-Processing
	basePathString = std::string(basePathChar);
	if (prefPathChar)
		prefPathString = std::string(prefPathChar);

	basePathPath = std::filesystem::path(basePathString);
	
	if (prefPathChar)
		prefPathPath = std::filesystem::path(prefPathString);
#pragma endregion

	return;
}

void CellMachine::ApplicationContext::destroy() {
	CellMachine::ApplicationContext::basePathPath = std::filesystem::path {};
	CellMachine::ApplicationContext::basePathString = {};
	SDL_free(const_cast<void*>(reinterpret_cast<const void*>(CellMachine::ApplicationContext::basePathChar)));

	if (CellMachine::ApplicationContext::prefPathChar != nullptr) {
		CellMachine::ApplicationContext::prefPathPath = std::filesystem::path {};
		CellMachine::ApplicationContext::prefPathString = {};
		SDL_free(const_cast< void * >(reinterpret_cast< const void * >(CellMachine::ApplicationContext::prefPathChar)));
	}

	return;
}