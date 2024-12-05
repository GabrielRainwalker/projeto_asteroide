//
// Created by T-Gamer on 05/12/2024.
//

#ifndef AUDIO_H
#define AUDIO_H

#include <irrKlang.h>
#include <string>

class GerenciadorAudio {
public:
    GerenciadorAudio();
    ~GerenciadorAudio();

    void tocarMusicaFundo();
    void tocarSomTiro();
    void tocarSomExplosao();
    void setVolume(float volume);

private:
    irrklang::ISoundEngine* engine;
    irrklang::ISound* musicaFundo;
    float volumeGeral;
};

#endif //AUDIO_H
