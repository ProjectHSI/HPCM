// CellMachine.cpp : Defines the entry point for the application.
//

#define SDL_MAIN_HANDLED

#include "ApplicationContext.hpp"
#include "CellMachine.h"
#include "Interface.hpp"
#include "Logic/Logic.hpp"
#include "Screens/LoadingScreen/LoadingScreen.hpp"
#include "Settings/Settings.hpp"
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <google/protobuf/stubs/common.h>
#include <random>
#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_events.h>
#include <SDL_rwops.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <test.pb.h>
#include <thread>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

std::vector<uint8_t> buf {};
uint32_t len {};
uint32_t bufPosition {};

std::mt19937 rng {};

constexpr float _8bitDiv = static_cast< float >(rng.max()) / 255;

void SDLCALL my_callback_function(void *userdata, uint8_t *stream, int len) {
	//printf("%i", len);

	for (size_t i = 0; i < len; i++) {
		//printf("%i", len);
		stream[i] = !buf.empty() && buf.size() > bufPosition + i ? buf[bufPosition + i] : 0;
	}

	bufPosition += len;
}

void audioTest() {
	SDL_AudioSpec audioDeviceSpec { };
	audioDeviceSpec.freq = 44100;
	audioDeviceSpec.format = AUDIO_F32SYS;
	audioDeviceSpec.samples = 3852;
	audioDeviceSpec.channels = 2;
	audioDeviceSpec.callback = my_callback_function;
	SDL_AudioDeviceID id = SDL_OpenAudioDevice(NULL, 0, &audioDeviceSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

	if (id == 0) {
		printf("%s", SDL_GetError());
	}

	SDL_PauseAudioDevice(id, 0);

	int i5 = 0;

	for (auto &i : std::filesystem::directory_iterator((CellMachine::ApplicationContext::basePathString + "/Resources/Sound/Music/"))) {
		if (i5 < 1) {
			i5++;
			continue;
		}

		uint8_t *tempBuf;
		uint32_t tempLen;

		SDL_AudioSpec wavSpec;
		SDL_AudioSpec *wavSpecActual = SDL_LoadWAV_RW(SDL_RWFromFile(i.path().generic_string().c_str(), "rb"), 1, &wavSpec, &tempBuf, &tempLen);

		if (wavSpecActual == NULL) {
			printf("%s", SDL_GetError());
		}

		SDL_AudioCVT audioCvt;
		SDL_BuildAudioCVT(&audioCvt, wavSpec.format, wavSpec.channels, wavSpec.freq, audioDeviceSpec.format, audioDeviceSpec.channels, audioDeviceSpec.freq);
		SDL_assert(audioCvt.needed);

		// note: std::vector stores a continous memory region.
		// if changing data type - ensure this is the case.
		std::vector<uint8_t> audioVector(tempLen * audioCvt.len_mult);
		memcpy(audioVector.data(), tempBuf, tempLen);

		audioCvt.len = tempLen;
		audioCvt.buf = audioVector.data();

		SDL_ConvertAudio(&audioCvt);

		audioVector.resize(tempLen * audioCvt.len_ratio);

		SDL_LockAudioDevice(id);
		buf = audioVector;
		len = audioVector.size();
		bufPosition = 0;
		SDL_UnlockAudioDevice(id);

		while (bufPosition <= len) {
			std::this_thread::sleep_for(0ms);
		}

		SDL_FreeWAV(tempBuf);
	}

	SDL_CloseAudioDevice(id);
}

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	CellMachine::ApplicationContext::initalize();
	CellMachine::Settings::Settings::load();
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//audioTest();

	HPCM::Screens::LoadingScreen::loadingBars.push_back({"test", 0, 0});

	CellMachine::Logic::Logic::logic();

	TTF_Quit();
	SDL_Quit();
	CellMachine::ApplicationContext::destroy();
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}