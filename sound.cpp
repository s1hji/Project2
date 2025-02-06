#include "sound.hpp"
#include "config.hpp"

SoundGame::SoundGame() : volume(50.0f) {
    loadSounds();
}

void SoundGame::loadSounds() {
    jumpBuffer.loadFromFile(config::JUMP_SOUND);
    gameOverBuffer.loadFromFile(config::GAME_OVER_SOUND);
    bonusBuffer.loadFromFile(config::BONUS_SOUND);

    jumpSound.setBuffer(jumpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bonusSound.setBuffer(bonusBuffer);

    setVolume(volume);
}

void SoundGame::playJumpSound() {
    jumpSound.play();
}

void SoundGame::playGameOverSound() {
    gameOverSound.play();
}

void SoundGame::playBonusSound() {
    bonusSound.play();
}

void SoundGame::setVolume(float volume) {
    this->volume = volume;
    jumpSound.setVolume(volume);
    gameOverSound.setVolume(volume);
    bonusSound.setVolume(volume);
}