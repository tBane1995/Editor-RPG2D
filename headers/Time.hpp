#ifndef Time_hpp
#define Time_hpp

sf::Clock timeClock;	// main clock for GameObjects

sf::Time prevTime;
sf::Time currentTime;
float dt;   // delta time

sf::Clock FPSClock;	// clock for calculate FPS
sf::Clock FPSClockUpdate;	// clock for show FPS in main loop of Editor



#endif