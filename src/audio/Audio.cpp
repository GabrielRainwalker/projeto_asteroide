//
// Created by T-Gamer on 05/12/2024.
//

#include "Audio.h"
#include <stdexcept>

GerenciadorAudio::GerenciadorAudio() : volumeGeral(1.0f) {
    engine = irrklang::createIrrKlangDevice();
    if (!engine) {
        throw std::runtime_error("Falha ao inicializar sistema de áudio");
    }
}

GerenciadorAudio::~GerenciadorAudio() {
    if (engine) {
        engine->drop();
    }
}

void GerenciadorAudio::tocarMusicaFundo() {
    if (engine) {
        musicaFundo = engine->play2D("assets/musica.wav", true, false, true);
        if (musicaFundo) {
            musicaFundo->setVolume(volumeGeral);
        }
    }
}

void GerenciadorAudio::tocarSomTiro() {
    if (engine) {
        engine->play2D("assets/tiro.wav", false);
    }
}

void GerenciadorAudio::setVolume(float volume) {
    volumeGeral = volume;
    if (musicaFundo) {
        musicaFundo->setVolume(volumeGeral);
    }
}