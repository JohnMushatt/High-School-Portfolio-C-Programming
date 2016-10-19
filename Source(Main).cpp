#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include <ctime>
#include <string>
#include "Projectile.h"
#include <vector>

/* What we have: Main character sprite and background, basic movement , weapons and bullets
   What we need: Player collision(with cover), enemy spawns*/

int circle_position[2] = { 0, 0 };
int window_width = 1000, window_height = 1000;
sf::Sprite mainChar;
double sx, sy; 
double vx, vy;
double viewOfSprite[2];
double posOfSprite[2];
vector<Projectile*> bullets;
sf::Sprite enemy;
sf::Sprite ksg;
bool usingKSG = false;
bool usingPistol = false;
sf::Sprite pistol;
sf::Sprite weapon[2] = {ksg, pistol};
sf::Sprite cover;
sf::Sprite player2;

using namespace std;
void keyboardCallback(sf::RenderWindow& window, sf::Event event) //Player Movement
{
	
	switch (event.key.code) //Can't declare variables inside, fix
	{
	case sf::Keyboard::W: 
		mainChar.move(0, -10);
			break;
	case sf::Keyboard::A:
		mainChar.move(-10, 0);			
			break;
	case sf::Keyboard::S:
		mainChar.move(0, 10);
			break;
	case sf::Keyboard::D:
		mainChar.move(10, 0);
			break;
	case sf::Keyboard::Escape:
		window.close();
	case sf::Keyboard::Num1: //Select Shotgun
		usingKSG = true;
		usingPistol = false;
		
			break;
	case sf::Keyboard::Num2: //Select Pistol
		usingKSG = false;
		usingPistol = true;
		
			break; 
	default:
		   ;
	} 
}
void mouseMotionCallback(sf::RenderWindow& window, sf::Event event) 
{
	sf::Vector2f currentPosition = mainChar.getPosition();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	double PI = 3.14159265;

	double a = currentPosition.x - mousePosition.x;
	double b = currentPosition.y - mousePosition.y;

	double rot = std::atan2(b,a) * 180.0f/PI;
	mainChar.setRotation(rot - 90);
	ksg.setRotation(rot -90);
	pistol.setRotation(rot -90);
		
}
void mouseButtonCallback(sf::RenderWindow& window, sf::Event event)
{
	sf::Vector2f dir;
	sf::Vector2f loc = mainChar.getPosition();
	sf::Vector2f trajectory = sf::Vector2f(event.mouseButton.x, event.mouseButton.y) - mainChar.getPosition();

	float length = sqrt((trajectory.x * trajectory.x ) + (trajectory.y * trajectory.y));
	dir = trajectory / length;

	sf::Vector2i mousePosition = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
	double PI = 3.14159265;

	double a = loc.x - mousePosition.x;
	double b = loc.y - mousePosition.y;

	double rot = std::atan2(b,a) * 180.0f/PI;

	int last_bullet = bullets.size();
	bullets.push_back(new Projectile());
	bullets[last_bullet]->velocity = dir * 2.0f;
	bullets[last_bullet]->position = loc;
	bullets[last_bullet]->rotation = rot;
	bullets[last_bullet]->loadSprite("C:/Users/student/Desktop/John M/Assets/bullet_8bit.png");

}
int main() //Drawing player sprite, weapons, and background
{
	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Top Down Shooter");
	window.setFramerateLimit(60);
	sf::Texture backgroundTexture;
	sf::Sprite bg;
	backgroundTexture.loadFromFile("C:/Users/student/Desktop/John M/Assets/background_2_8bit.png");
	bg.setTexture(backgroundTexture);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("C:/Users/student/Desktop/John M/Assets/MainCharacter_8bit.png");
	mainChar.setTexture(playerTexture);
	mainChar.setPosition(450, 600);
	mainChar.setOrigin(90,100);

	sf::Texture ksgTexture;
	ksgTexture.loadFromFile("C:/Users/student/Desktop/John M/Assets/ksg_2_8bit.png");
	ksg.setTexture(ksgTexture);
	ksg.setOrigin(60, 200);
	

	sf::Texture pistolTexture;
	pistolTexture.loadFromFile("C:/Users/student/Desktop/John M/Assets/pistol_2_8bit.png");
	pistol.setTexture(pistolTexture);
	pistol.setOrigin(70, 190);



	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("C:/Users/student/Desktop/John M/Assets/enemy_8bit.png");
	enemy.setTexture(enemyTexture);

	sf::Texture coverTexture;
	coverTexture.loadFromFile("C:/Users/student/Desktop/John M/Assets/cover_8bit.png");
	cover.setTexture(coverTexture);
	cover.setOrigin(200,200);
	cover.setPosition(500,500);
	cover.setScale(1,.75);

	sf::Texture player2Texture;
	player2Texture.loadFromFile("C:/Users/student/Desktop/John M/Assets/MainCharacter_8bit - Copy.png");
	player2.setTexture(player2Texture);
	player2.setOrigin(90,100);
	player2.setPosition(500, 100);
	player2.setRotation(180);
	
	sf::Time changeInTime = clock.restart();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) // If event is a key press
			{ 
				
				keyboardCallback(window, event);
				if(usingKSG)
				{
					ksg.setPosition(mainChar.getPosition());
					pistol.setPosition(2000, 2000);
				}
				else if(usingPistol)
				{
					pistol.setPosition(mainChar.getPosition());
					ksg.setPosition(2000, 2000);
				}
				
			}
			else if (event.type == sf::Event::MouseMoved) // If event is a mouse motion
			{
				mouseMotionCallback(window, event);
			}
			else if (event.type == sf::Event::MouseButtonPressed )
			{
				mouseButtonCallback(window, event);

			}
			if(mainChar.getGlobalBounds().intersects(cover.getGlobalBounds()));	
				mainChar.setPosition(500, 800);
		}

			window.clear();
			window.draw(bg);
			window.draw(mainChar);
			window.draw(ksg);
			window.draw(pistol);
			window.draw(cover);
			window.draw(player2);
			
			for(int i = 0; i < bullets.size(); i++)
			{
				window.draw(bullets[i]->sprite);
				bullets[i]->update();

			}

			window.display();
	}
	
	for(int i = 0; i < bullets.size(); i++)
		delete bullets[i];

	return 0;
	
}
