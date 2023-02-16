#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>


void playsCount(int &play) {
    std::cout << play << std::endl;
}


int main()
{
    // Seeding
    srand(time(NULL));

    // Variables
    int gamestate = 0;
    int frame = 1;
    sf::Clock clock;
    sf::Clock timer;
    int currenttime = timer.getElapsedTime().asSeconds();
    bool timecheck = false;
    int hi = 0;
    bool a = false;
    int p = 0;

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(700, 800), "Donkey Kong");
    app.setFramerateLimit(60);

    // Load a sprite to display

    // Menu splash
    sf::Texture splashTexture;
    splashTexture.loadFromFile("splash.png");
    sf::Sprite splash(splashTexture);
    splash.setScale(2.5, 2.5);
    splash.setPosition(100, 150);

    sf::Texture dksplashTexture;
    dksplashTexture.loadFromFile("dksplash.png");

    sf::RectangleShape dksplash(sf::Vector2f(59, 42));

    dksplash.setTexture(&dksplashTexture);

    dksplash.setScale(3, 3);
    dksplash.setPosition(270, 430);

    sf::Font font;
    font.loadFromFile("nes.ttf");

    sf::Text menuText;
    menuText.setFont(font);
    menuText.setString("Press Space to Start!");
    menuText.setPosition(110, 600);
    menuText.setCharacterSize(24);

    // Donkey Kong & animation
    sf::RectangleShape dkl(sf::Vector2f(59, 42));
    dkl.setPosition(270, 430);
    dkl.setScale(3, 3);

    sf::Texture ab;
    ab.loadFromFile("dksplash.png");

    sf::Texture abc;
    abc.loadFromFile("dksplashL.png");

    // Mario
    sf::Texture mario;
    mario.loadFromFile("mario.png");
    sf::Sprite player(mario);
    player.scale(0.15, 0.15);
    player.setOrigin(45/2, 60/2);
    player.setPosition(100, 715);

    // Mario Left
    sf::Texture marioL;
    marioL.loadFromFile("marioL.png");

    // Platform
    sf::Texture platform;
    platform.loadFromFile("platform.png");

    // Win platform texture
    sf::Texture platformW;
    platformW.loadFromFile("platformW.png");

    // Barrel
    sf::Texture barrelTexture;
    barrelTexture.loadFromFile("barrel.png");
    sf::Sprite barrel[5];
    for (int i = 0; i < 5; i++) {
        barrel[i].setTexture(barrelTexture);
        barrel[i].setScale(0.15, 0.15);
        barrel[i].setPosition(99, -460+(100*i));
        barrel[i].setOrigin(242/2, 208);
    }

    // Right platforms
    sf::Sprite platformArrayRight[3];
    for (int i = 0; i < 3; i++) {
        platformArrayRight[i].setTexture(platform);
        platformArrayRight[i].setPosition(100, 260*i+250);
        platformArrayRight[i].rotate(-2);
        platformArrayRight[i].setScale(1.5, 1.1);
    }

    // Left platforms
    sf::Sprite platformArrayLeft[3];
    for (int i = 0; i < 3; i++) {
        platformArrayLeft[i].setTexture(platform);
        platformArrayLeft[i].setPosition(-80, 260*i+100);
        platformArrayLeft[i].rotate(2);
        platformArrayLeft[i].setScale(1.5, 1.1);
    }

    // Ladder
    sf::Texture ladder;
    ladder.loadFromFile("ladder.png");

    // Right ladders
    sf::Sprite ladderArrayRight[3];
    for (int i = 0; i < 3; i++) {
        ladderArrayRight[i].setTexture(ladder);
        ladderArrayRight[i].setPosition(530, 260*i+124);
        ladderArrayRight[i].setScale(1.1, 2.5);
    }

    // Left ladders
    sf::Sprite ladderArrayLeft[2];
    for (int i = 0; i < 2; i++) {
        ladderArrayLeft[i].setTexture(ladder);
        ladderArrayLeft[i].setPosition(160, 260*i+250);
        ladderArrayLeft[i].setScale(1.1, 2.6);
    }

    // Winning ladders
    sf::Sprite winLadder[2];
    for (int i = 0; i < 2; i++) {
        winLadder[i].setTexture(ladder);
        winLadder[i].setPosition(315+i*100, 45);
        winLadder[i].setScale(1, 2);
    }

    // Winning platform
    sf::Sprite winPlatform;
    winPlatform.setTexture(platformW);
    winPlatform.setPosition(301, 45);

    // Princess
    sf::Texture princessTexture;
    princessTexture.loadFromFile("princessSprite.png");

    sf::Sprite princess;
    princess.setTexture(princessTexture);
    princess.setPosition(300, -1.5);
    princess.setScale(0.9, 0.9);

    // Timer & fastest time text
    sf::Text timetext;
    timetext.setFont(font);
    timetext.setString("Time:");
    timetext.setPosition(580, 10);
    timetext.setCharacterSize(12);

    sf::Text time;
    time.setFont(font);
    time.setPosition(650, 10);
    time.setString(std::to_string(currenttime));
    time.setCharacterSize(12);

    sf::Text highscore;
    highscore.setFont(font);
    highscore.setPosition(10, 10);
    highscore.setString("Fastest Time:");
    highscore.setCharacterSize(12);

    sf::Text score;
    score.setFont(font);
    score.setPosition(180, 10);
    score.setString("None");
    score.setCharacterSize(12);

    // Restart/victory text
    sf::Text restarttext;
    restarttext.setFont(font);
    restarttext.setPosition(180, 400);
    restarttext.setString("Press R to try again!");
    restarttext.setCharacterSize(16);

    sf::Text victorytext;
    victorytext.setFont(font);
    victorytext.setPosition(100, 300);
    victorytext.setString("Congratulations! You won!");
    victorytext.setCharacterSize(20);

    // Music/sounds
    sf::SoundBuffer music;
    music.loadFromFile("music.wav");
    sf::Sound bgmusic;
    bgmusic.setBuffer(music);
    bgmusic.play();

    sf::SoundBuffer ending;
    ending.loadFromFile("lose.wav");
    sf::Sound lose;
    lose.setBuffer(ending);

    sf::SoundBuffer winning;
    winning.loadFromFile("win.wav");
    sf::Sound win;
    win.setBuffer(winning);

    sf::Texture runright;
    runright.loadFromFile("mariorun.png");

    sf::Texture runleft;
    runleft.loadFromFile("mariorunl.png");

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Game loop
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gamestate == 0) {
            gamestate = 1;
            timecheck = true;
            p++;
            playsCount(p);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && gamestate == 2 || sf::Keyboard::isKeyPressed(sf::Keyboard::R) && gamestate == 3) {
            a = true;
            if (a == true) {
                gamestate = 0;
                frame = 1;
                currenttime = timer.getElapsedTime().asSeconds();
                timecheck = false;
                player.setPosition(100, 715);
                for (int i = 0; i < 5; i++) {
                    barrel[i].setPosition(99, -460+(100*i));
                }
                bgmusic.play();
                a = false;
            }
        }

        // Right platform player movement
        if (gamestate == 1) {
            for (int i = 0; i < 3 ; i++)
                if (player.getGlobalBounds().intersects(platformArrayRight[i].getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x >= 100) {
                        player.setTexture(runright);
                        player.move(3.5, -0.118);
                    }
                    else if (player.getGlobalBounds().intersects(platformArrayRight[i].getGlobalBounds())) {
                        player.setTexture(mario);
                    }
                }
        }

        if (gamestate == 1) {
            for (int i = 0; i < 3 ; i++) {
                if (player.getGlobalBounds().intersects(platformArrayRight[i].getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x >= 100) {
                        player.setTexture(runleft);
                        player.move(-3.5, 0.118);
                    } else if (player.getPosition().x < 100) {
                        player.setTexture(marioL);
                        player.move(3.5, -0.118);
                    } else if (player.getPosition().x >= 685) {
                        player.setTexture(marioL);
                        player.move(-3.5, 0.118);
                    }
                }
            }
        }

        // Left platform player movement
        if (gamestate == 1) {
            for (int i = 0; i < 3 ; i++)
                if (player.getGlobalBounds().intersects(platformArrayLeft[i].getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x <= 600 && player.getPosition().y <= platformArrayLeft[i].getPosition().y) {
                        player.setTexture(runleft);
                        player.move(-3.5, -0.118);
                    }
                    else if (player.getGlobalBounds().intersects(platformArrayLeft[i].getGlobalBounds())) {
                        player.setTexture(marioL);
                    }
                }
        }

        if (gamestate == 1) {
            for (int i = 0; i < 3 ; i++) {
                if (player.getGlobalBounds().intersects(platformArrayLeft[i].getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x <= 575) {
                        player.setTexture(runright);
                        player.move(3.5, 0.118);
                    } else if (player.getPosition().x > 600) {
                        player.setTexture(mario);
                        player.move(-3.5, -0.118);
                    } else if (player.getPosition().x <= 15) {
                        player.setTexture(mario);
                        player.move(3.5, 0.118);
                    }
                }
            }
        }

        // Ladder climbing
        if (gamestate == 1) {
            for (int i = 0; i < 3; i++) {
                if (player.getGlobalBounds().intersects(ladderArrayRight[i].getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y >= ladderArrayRight[i].getPosition().y-50) {
                        player.move(0, -3);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y <= ladderArrayRight[i].getPosition().y+58) {
                        player.move(0, 3);
                    }
                }
            }
        }

        if (gamestate == 1) {
            for (int i = 0; i < 2; i++) {
                if (player.getGlobalBounds().intersects(ladderArrayLeft[i].getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y >= ladderArrayLeft[i].getPosition().y-50) {
                        player.move(0, -3);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y <= ladderArrayLeft[i].getPosition().y+65) {
                        player.move(0, 3);
                    }
                }
            }
        }

        // Winning ladders & platform
        if (gamestate == 1) {
            for (int i = 0; i < 2; i++) {
                if (player.getGlobalBounds().intersects(winLadder[i].getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.getPosition().y >= winLadder[i].getPosition().y-50) {
                        player.move(0, -3);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player.getPosition().y <= winLadder[i].getPosition().y+65) {
                        player.move(0, 3);
                    }
                }
            }
        }

        if (gamestate == 1) {
            if (player.getPosition().y < winPlatform.getPosition().y) {
                gamestate = 3;
                bgmusic.stop();
                win.play();
            }
        }

        // Barrel movements/intersection
        if (gamestate == 1) {
            for (int i = 0; i < 3; i++) {
                for (int a = 0; a < 5; a++) {
                    if (barrel[a].getGlobalBounds().intersects(platformArrayLeft[i].getGlobalBounds())) {
                        barrel[a].move(5, 0.18);
                    }
                    else if (barrel[a].getGlobalBounds().intersects(platformArrayRight[i].getGlobalBounds())) {
                        barrel[a].move(-5, 0.18);
                    }
                    else if (barrel[a].getPosition().x > 600 || barrel[a].getPosition().x < 100) {
                        barrel[a].move(0, 1.25);
                    }
                }
            }
        }

        if (gamestate == 1) {
            for (int i = 0; i < 5; i++) {
                if (barrel[i].getPosition().y >= 800) {
                    barrel[i].setPosition(99, -460+(rand()%100)+(100*i));
                }
            }
        }


        if (gamestate == 1) {
            for (int i = 0; i < 5; i++) {
                if (barrel[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
                    gamestate = 2;
                    lose.play();
                }
            }
        }

        // Donkey Kong animation
        if (clock.getElapsedTime().asSeconds()> .5f) {
            frame ++;
            if (frame == 3) {
                frame = 1;
            }
            if (frame == 1) {
                dkl.setTexture(&ab);
            } else if (frame == 2) {
                dkl.setTexture(&abc);
            }
            clock.restart();
        }

        // Timer
        currenttime = timer.getElapsedTime().asSeconds();
        time.setString(std::to_string(currenttime));

        if (timecheck == true) {
            timer.restart();
            timecheck = false;
        }

        if (gamestate == 3) {
            score.setString(std::to_string(currenttime));
        }

        // Clear screen
        app.clear();

        // Rendering

        // Menu (gamestate == 0) Rendering
        if (gamestate == 0) {
            dkl.setPosition(270, 430);
            dkl.setScale(3, 3);
            app.draw(splash);
            app.draw(dkl);
            app.draw(menuText);
            app.draw(highscore);
            app.draw(score);
            app.display();
        }

        // Play (gamestate == 1) Rendering
        else if (gamestate == 1) {
            for (int i = 0; i < 2; i++) {
                app.draw(winLadder[i]);
                app.draw(ladderArrayLeft[i]);
            }
            for (int i = 0; i < 3; i++) {
                app.draw(ladderArrayRight[i]);
                app.draw(platformArrayRight[i]);
                app.draw(platformArrayLeft[i]);
            }
            app.draw(dkl);
            dkl.setPosition(100, 14.5);
            dkl.setScale(2.5, 2.5);
            for (int i = 0; i < 5; i++) {
                app.draw(barrel[i]);
            }
            app.draw(winPlatform);
            app.draw(princess);
            app.draw(player);
            app.draw(timetext);
            app.draw(time);
            app.draw(highscore);
            app.draw(score);
            app.display();
        }

        // Game over (gamestate == 2) Rendering
        else if (gamestate == 2) {
            bgmusic.stop();
            app.draw(player);
            player.move(0, 4);
            if (player.getPosition().y > 800) {
                app.draw(restarttext);
            }
            hi = currenttime;
            app.display();
        }

        // Win (gamestate == 3) Rendering
        else if (gamestate == 3) {
            app.draw(victorytext);
            app.draw(restarttext);
            hi = currenttime;
            app.display();
        }

    }

    return EXIT_SUCCESS;
}
