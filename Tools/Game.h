#pragma once
#include "Application.h"
class Player;
class AI;
class PauseMenu;
class Game // when the a game object is created the fight starts.Game is responsible for loading,collision detection,deciding what the ai must do,ending the game and managing the rounds
{
    graphics::Brush map, loadingscreen, pause, option1, option2, option3, option4, gamepaused, countdown,animation;
    graphics::MouseState mouse;
    Player* player;
    AI* ai;
    PauseMenu* pausemenu;
    float loading,duration,timebetweenrounds,timeuntilroundwait,timeuntilgameend = 0;
    unsigned short mapframes,aiwin_counter,playerwin_counter = 0;
    unsigned short frame,roundnumber = 1;
    std::string mapname;
    std::string Playerfilename;
    std::string AIfilename;
    unsigned short countdown_num = 4;
    bool paused = false;
    bool roundwait,playerleftorright = true;
public:
    Game(std::string const& name, unsigned int const& frames, std::string const& filep, std::string const& fileai);
    void draw();
    void update();
    void adjustCanvas(int w, int h);
    void BackgroundAnimation(const std::string& name, unsigned const int& frames, unsigned const int& ms);
    void AIactions();
    void CollisionDetector();
    void AssetWarmUp();
    bool roundEnd();
    ~Game();
};