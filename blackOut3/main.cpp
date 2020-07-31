#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "view.h"
#include <sstream>
#include <list>
#include <vector>

using namespace sf;
using namespace std;

float offsetX = 0, offsetY = 0;

const int H = 27;
const int W = 150;

String TileMap[H] = {
"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000r",
"0                                                                                                                                                    r",
"0                                                                                                                                                    r",
"0                                                                                                                                                    r",
"0                                     ccc                                                                                                            r",
"0                                                                                                                                                    r",
"0                                      f                                                                                                             r",
"0                              f    kkkkkkkk                                                                                       c                 r", 
"0                            rrrrr                                                                                              kkkkk                r",
"0                                                                                                                        kkkkk                       r",
"0                    rrrrr                                                    cc                                                                     r",
"0                                             t0                             rrk                 c            c     kkkkk                            r",
"0   G   G     G   G                  d        00              t0            rkrr                 G            G          G           G               r",
"0g         g                 g                00 h    f  f    00    f      rrrkr   f        h                     g            g         g      g    r",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP  PP",
"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzrrrrrrrrr      rzz",
"zzzzzzzzzzzzzzzkkkzkzzzkkkkzkkkzkzkzzzzkkkzkzkzkkkzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzrcc            rzz",
"zzzzzzzzzzzzzzzkzkzkzzzkzzkzkzzzkzkzzzzkzkzkzkzzkzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzr         rrrr rzz",
"zzzzzzzzzzzzzzzkkkzkzzzkkkkzkzzzkkzzzzzkzkzkzkzzkzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzrrrrrrrrrrrzzrfrzz",
"zzzzzzzzzzzzzzzkzkzkzzzkzzkzkzzzkzkzzzzkzkzkzkzzkzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzrrrzz",
"lllllllllllllllkkklkkklkllklkkklklkllllkkklkkkllklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",
"llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",
"llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",
"llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",
"llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",
"llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",

};

class PLAYER {

public:

	float dx, dy;
	FloatRect rect;
	bool onGround, life;
	Sprite sprite;
	float currentFrame;
	int dir, playerScore;
	double health;

	PLAYER(Texture& image)
	{
		dir = 0; playerScore = 0;
		health = 100;
		life = true;
		sprite.setTexture(image);
		rect = FloatRect(100, 180, 16, 16);

		dx = dy = 0.1;
		currentFrame = 0;
	}

	void update(float time)
	{

		rect.left += dx * time;
		Collision(0);

		if (!onGround) dy = dy + 0.0005 * time;
		rect.top += dy * time;
		onGround = false;
		Collision(1);
		
		currentFrame += time * 0.005;
		if (currentFrame > 2) currentFrame -= 2;

		if (dx > 0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame), 144, 16, 16));
		if (dx < 0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;

		if (health <= 0) { life = false; }
	}



	void Collision(int num)
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
				{
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;   dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
					
				}
				if (TileMap[i][j] == 'h') {
					health += 20;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'f') {
						health -= 40;
						TileMap[i][j] = ' ';
					}
				if (TileMap[i][j] == 'c') {
					playerScore++;
					TileMap[i][j]=' '; 
				}
			}
	}

};

class ENEMY
{

public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	bool life;


	void set(Texture& image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 16, 16);

		dx = 0.05;
		currentFrame = 0;
		life = true;
	}

	void update(float time)
	{
		rect.left += dx * time;

		Collision();
		
		currentFrame += time * 0.005;
		if (currentFrame > 2) currentFrame -= 2;

		sprite.setTextureRect(IntRect(18 * int(currentFrame), 0, 16, 16));
		if (!life) sprite.setTextureRect(IntRect(58, 0, 16, 16));

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}
	 
	void Collision()
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0'))
				{
					if (dx > 0)
					{
						rect.left = j * 16 - rect.width; dx *= -1;
					}
					else if (dx < 0)
					{
						rect.left = j * 16 + 16;  dx *= -1;
					}

				}
	}

};

void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("img/menu_newGame.png");
	menuTexture2.loadFromFile("img/menu_about.png");
	menuTexture3.loadFromFile("img/menu_exit.png");
	aboutTexture.loadFromFile("img/about.png");
	menuBackground.loadFromFile("img/blackout.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Red); menuNum = 3; }
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	
}


bool startGame(){

	RenderWindow window(VideoMode(750, 430), "Black Out");
	menu(window);

	view.reset(sf::FloatRect(0, 0, 750, 430));

	Font font;
	font.loadFromFile("pixelFont.ttf");
	Text text("", font, 20);

	Texture tileSet,bg;
	bg.loadFromFile("img/bg.png");
	tileSet.loadFromFile("img/Mario_Tileset2.png");


	PLAYER p(tileSet);
	ENEMY  enemy;
	enemy.set(tileSet, 48 * 16, 13 * 16);

	Sprite tile(tileSet);

	Sprite background(bg);
	background.setOrigin(bg.getSize().x / 2, bg.getSize().y / 2);

	SoundBuffer buffer;
	buffer.loadFromFile("img/jump.ogg");
	Sound sound(buffer);
	sound.setVolume(15.f);

	/*SoundBuffer buffer1;
	buffer1.loadFromFile("img/go.ogg");
	Sound sound1(buffer1);
	sound1.setVolume(15.f);*/

	Music music;
	music.openFromFile("img/theme.ogg");
	music.play();
	music.setLoop(true);
	music.setVolume(40.f);

	Clock clock;
	Clock getTimeClock;
	
	int gameTime = 0;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) {
			gameTime = getTimeClock.getElapsedTime().asSeconds();
		}
		else { view.move(0.01, 0); }

		if (p.playerScore == 10) {
			view.move(0.01, 0);
		}
	
		clock.restart();

		time = time / 500; 

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (p.life && p.playerScore <10) {
			if (Keyboard::isKeyPressed(Keyboard::Left))    p.dx = -0.1;

			if (Keyboard::isKeyPressed(Keyboard::Right))    p.dx = 0.1;

			if (Keyboard::isKeyPressed(Keyboard::Up))	if (p.onGround) { p.dy = -0.27; p.onGround = false;  sound.play(); }
		} 
		
		if (Keyboard::isKeyPressed(Keyboard::Backspace)) menu(window);

		if (Keyboard::isKeyPressed(Keyboard::P))    music.stop();
		if (Keyboard::isKeyPressed(Keyboard::O))    music.play();

		if (Keyboard::isKeyPressed(Keyboard::R)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }

		//if (p.health == 0) { sound1.play(); }

		p.update(time);
		enemy.update(time);

	
		if (p.rect.intersects(enemy.rect))
		{
			if (enemy.life) {
				if (p.dy > 0) { enemy.dx = 0; p.dy = -0.2; enemy.life = false; }
				else { p.health -= 0.1; };
			}
		}
	


		//if (p.rect.left > 200) offsetX = p.rect.left - 200;
		if (p.rect.left > 200) offsetX = p.rect.left - 200;

	
		window.clear(Color::Blue);
		background.setPosition(view.getCenter());
		window.draw(background);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P')  tile.setTextureRect(IntRect(96, 112, 16, 16));

				if (TileMap[i][j] == 'z')  tile.setTextureRect(IntRect(80, 112, 16, 16));

				if (TileMap[i][j] == 'l')  tile.setTextureRect(IntRect(96, 128, 16, 16));

				if (TileMap[i][j] == 'k')  tile.setTextureRect(IntRect(143, 112, 16, 16));

				if (TileMap[i][j] == 'f')  tile.setTextureRect(IntRect(59, 23, 19, 16));

				if (TileMap[i][j] == 'h')  tile.setTextureRect(IntRect(88, 1, 17, 16));

				if (TileMap[i][j] == 'c')  tile.setTextureRect(IntRect(143 - 16, 112, 16, 16));

				if (TileMap[i][j] == 't')  tile.setTextureRect(IntRect(0, 47, 32, 95 - 47));

				if (TileMap[i][j] == 'g')  tile.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

				if (TileMap[i][j] == 'G')  tile.setTextureRect(IntRect(169, 225, 29, 32));

				if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(19, 97, 43, 40));

				if (TileMap[i][j] == 'w')  tile.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

				if (TileMap[i][j] == 'r')  tile.setTextureRect(IntRect(143 - 32, 112, 16, 16));

				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

				tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
				
				window.draw(tile);
			}
	
		ostringstream playerScoreString, playerHealthString, gameTimeString;    
		playerScoreString << p.playerScore, playerHealthString << p.health, gameTimeString << gameTime;		
		text.setString("Score:   " + playerScoreString.str() + "/ Health:  " + playerHealthString.str() + "/ Time: " + gameTimeString.str()+" seconds");
		if (p.life == false){ text.setString("GAME OVER - Score: " + playerScoreString.str());}
		if (p.playerScore == 10) { text.setString("Game complete. Congrats! Press Esc to exit"); }
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);
		
		window.draw(text);
		window.draw(p.sprite);
		window.draw(enemy.sprite);
		window.display();
	}

}
void gameRunning()
{
	if (startGame()) { gameRunning(); }
}

int main()
{
	gameRunning();
	return 0;
}



