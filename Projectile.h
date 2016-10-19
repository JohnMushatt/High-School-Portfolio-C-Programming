#include <string>
#include <stdlib.h>
#include <SFML\Graphics.hpp>
using namespace std;
#define WIDTH 1000
#define HEIGHT 1000
#define PLAYER_SPEED 200

class TopDownGame
{
	sf::Texture playerTexture;
	sf::RenderWindow window;
	sf::Texture bg;
	sf::Sprite bgSprite;

	TopDownGame();

	void run();
	void update(sf::Time t);
	void processEvent();
	void render();

};

class Player
{
public:
	sf::Texture playerTexture;


	sf::Clock shotTimer;
	void update(sf::Time t);

	Player();
	Player(sf::Vector2f position, TopDownGame* game);

	void fire();
};
class Projectile
{
public:
	sf::Vector2f position;
	sf::Vector2f velocity;
	float rotation;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::CircleShape shape;

	void update()
	{
		sprite.move(velocity);
	}

	void loadSprite(string bulletfile)
	{
		if(!texture.loadFromFile(bulletfile.c_str()))
			cout << "ERRATA" << endl;
		sprite.setTexture(texture);
		sprite.setPosition(position);

		shape.setRadius(10);
		shape.setPosition(position);
		sprite.setOrigin(70,650);
		sprite.setRotation(rotation -90);
		sprite.setScale(.25,.25);
	}
		

};

