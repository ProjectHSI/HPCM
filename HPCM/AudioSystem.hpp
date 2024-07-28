#include <mutex>
#include <SDL.h>
#include <SDL_audio.h>

namespace HPCM {
	namespace AudioSystem {
		template <typename Mutex>
		class SDLAudioLock : protected std::lock_guard<Mutex> {

		private:
			SDL_AudioDeviceID audioDeviceId {};

		public:
			SDLAudioLock(SDL_AudioDeviceID audioDeviceId, Mutex mutex) : std::lock_guard<Mutex>(mutex) {
				this->audioDeviceId = audioDeviceId;

				SDL_LockAudioDevice(audioDeviceId);
			};
			~SDLAudioLock() {
				SDL_UnlockAudioDevice(audioDeviceId);
			};

		};
	}
}