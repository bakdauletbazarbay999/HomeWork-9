// Facade
#include <iostream>
#include <string>
using namespace std;

class TV {
public:
    void on() { cout << "TV is ON\n"; }
    void off() { cout << "TV is OFF\n"; }
    void setChannel(int channel) { cout << "TV channel set to " << channel << "\n"; }
};
class AudioSystem {
    int volume = 10;
public:
    void on() { cout << "AudioSystem is ON\n"; }
    void off() { cout << "AudioSystem is OFF\n"; }
    void setVolume(int v) {
        volume = v;
        cout << "Volume set to " << volume << "\n";
    }
};
class DVDPlayer {
public:
    void on() { cout << "DVD Player is ON\n"; }
    void off() { cout << "DVD Player is OFF\n"; }
    void play() { cout << "DVD playing...\n"; }
    void pause() { cout << "DVD paused.\n"; }
    void stop() { cout << "DVD stopped.\n"; }
};
class GameConsole {
public:
    void on() { cout << "Game Console is ON\n"; }
    void startGame(const string& game) { cout << "Starting game: " << game << "\n"; }
};
class HomeTheaterFacade {
    TV* tv;
    AudioSystem* audio;
    DVDPlayer* dvd;
    GameConsole* console;
public:
    HomeTheaterFacade(TV* t, AudioSystem* a, DVDPlayer* d, GameConsole* c)
        : tv(t), audio(a), dvd(d), console(c) {
    }
    void watchMovie() {
        cout << "\n=== Starting Movie Mode ===\n";
        tv->on();
        audio->on();
        audio->setVolume(15);
        dvd->on();
        dvd->play();
        cout << "Enjoy your movie!\n";
    }
    void endMovie() {
        cout << "\n=== Shutting Down Movie Mode ===\n";
        dvd->stop();
        dvd->off();
        audio->off();
        tv->off();
    }
    void playGame(const string& game) {
        cout << "\n=== Starting Game Mode ===\n";
        tv->on();
        audio->on();
        audio->setVolume(12);
        console->on();
        console->startGame(game);
    }
    void listenToMusic() {
        cout << "\n=== Music Mode ===\n";
        tv->on();
        audio->on();
        audio->setVolume(18);
        cout << "TV set to Audio Input. Playing music...\n";
    }
    void setVolume(int volume) {
        audio->setVolume(volume);
    }
    void shutdownAll() {
        cout << "\n=== Shutting Down All Systems ===\n";
        tv->off();
        audio->off();
        dvd->off();
        cout << "All systems are now OFF.\n";
    }
};
int main() {
    TV tv;
    AudioSystem audio;
    DVDPlayer dvd;
    GameConsole console;

    HomeTheaterFacade home(&tv, &audio, &dvd, &console);

    home.watchMovie();
    home.setVolume(20);
    home.endMovie();

    home.playGame("The Witcher 3");
    home.shutdownAll();

    home.listenToMusic();
    home.shutdownAll();

    return 0;
}
