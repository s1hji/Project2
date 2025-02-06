#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

class SoundGame {

public:
	SoundGame();

	void loadSounds();
	void playJumpSound();
	void playGameOverSound();
	void playBonusSound();
	void setVolume(float volume);

private:
	SoundBuffer jumpBuffer;
	SoundBuffer gameOverBuffer;
	SoundBuffer bonusBuffer;

	Sound jumpSound;
	Sound gameOverSound;
	Sound bonusSound;


	float volume;
};




#endif