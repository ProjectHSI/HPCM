/*!
\file CellMachine/ApplicationContext.hpp

\brief This file supplies the CellMachine::ApplicationContext namespace.

This module provides context about the application environment.

\see CellMachine/ApplicationContext.cpp
*/

#include <filesystem>
#include <string>

namespace CellMachine {
	namespace ApplicationContext {
		/*!
		\brief The base path of the application executable.
		\see CellMachine::ApplicationContext::basePathString
		\see CellMachine::ApplicationContext::basePathPath
		*/
		extern const char *basePathChar;
		/*!
		\brief The pref path of the organization "ProjectHSI" and the application name "HPCM".

		\warning This may be a nullptr - confirm before using.
		\see CellMachine::ApplicationContext::prefPathString
		\see CellMachine::ApplicationContext::prefPathPath
		*/
		extern const char *prefPathChar;
		/*!
		\brief The base path of the application executable in a std::string.
		\see CellMachine::ApplicationContext::basePathString
		\see CellMachine::ApplicationContext::basePathPath
		*/
		extern std::string basePathString;
		/*!
		\brief The pref path in a std::string.
		\see CellMachine::ApplicationContext::prefPathChar
		\see CellMachine::ApplicationContext::prefPathPath
		*/
		extern std::string prefPathString;
		/*!
		\brief The base path of the application in a std::filesystem::path.
		\see CellMachine::ApplicationContext::basePathChar
		\see CellMachine::ApplicationContext::basePathString
		*/
		extern std::filesystem::path basePathPath;
		/*!
		\brief The pref path in a std::filesystem::path.
		\see CellMachine::ApplicationContext::prefPathChar
		\see CellMachine::ApplicationContext::prefPathString
		*/
		extern std::filesystem::path prefPathPath;

		/*!
		\brief Initalizes the variables in the ApplicationContext namespace.

		\warning You must call this function *before* accessing any of the variables defined in CellMachine::ApplicationContext.
		*/
		void initalize();
		/*!
		\brief Destroys the variables in the ApplicationContext namespace.
		*/
		void destroy();
	}
}