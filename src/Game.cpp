#include <SFML/Graphics.hpp>
//#include <iostream>
#include<cmath>
using namespace sf;
using namespace std;

#define PI 3.14159265
char map[6][8] = { "1112111",
					"2000002",
					"1020001",
					"1000001",
					"1000001",
					"1111111"
};

class Player {
public :
	float pos_x, pos_y, rotation;
	Player(float x, float y, float trn);
};
Player::Player(float x, float y, float trn) {
	pos_x = x;
	pos_y = y;
	rotation = trn;
}

void drawing(RenderWindow& thiswindow, Player player) {
	thiswindow.clear(Color::Black);

	Texture wall_texture;
	wall_texture.loadFromFile("sprites/wall.png");
	Sprite sprite;
	sprite.setTexture(wall_texture);

	double hit,y;

	extern char map[6][8];



	RectangleShape shape2;
	for (float i = -40; i < 40; i += 0.1) {
		double ugol, length = 0;
		ugol = (player.rotation  -i) * PI / 180;
		for (; length < 400; length += 0.1) {
			float xx = player.pos_x + length * cos(ugol);
			float yy = player.pos_y + length * sin(ugol);
			//cout << xx << " " << yy<<" "<<length <<" "<< int(xx) / 50 + int(yy ) / 50 << endl;
			if (map[int(yy) / 50 ][int(xx) / 50]!='0'){
				switch(map[int(yy) / 50 ][int(xx) / 50]){
				case '1':
					shape2.setFillColor(sf::Color(250,250,250));
					break;
				case'2':
					shape2.setFillColor(sf::Color(150,10,20));
					break;
				}
				if(int(yy)%50<2 || int(yy)%50>48)hit = modf(xx/50,&y)*1184;
				else hit = modf(yy/50,&y)*1184;
				//hit = modf(yy/50,&y)*1184;
				break;
			}
		}
		length *= cos(player.rotation*PI/180-ugol);
		shape2.setSize(Vector2f((10000/length), 1.f));
		sprite.setTextureRect(IntRect(int(hit),0,int(hit),1184));
		sprite.setScale(1.f,(10000/length)/1184);
		shape2.setPosition(Vector2f(i*10+400,(600- 8000 / length + 1)/2));
		sprite.setPosition(Vector2f(i*10+400,(600- 8000 / length + 1)/2));
		thiswindow.draw(sprite);
		shape2.setRotation(90);
		//float shades = (0);
		//thiswindow.draw(shape2);

		//if(int(i)==0)cout<<(10000/length)/1184<<" "<<hit<<endl;
		thiswindow.draw(sprite);
		//thiswindow.draw(shape2);
	}
	RectangleShape bibka;
	for (int t = 0; t < 6; t++) {
				for (int i = 0; i < 8; i++) {
					if (map[t][i] == '1') {
						bibka.setPosition(i*50, t * 50);
						bibka.setSize(Vector2f(50, 50));
						bibka.setFillColor(Color::Green);
						thiswindow.draw(bibka);
					}
					if (map[t][i] == '2') {
						bibka.setPosition(i*50, t * 50);
						bibka.setSize(Vector2f(50, 50));
						bibka.setFillColor(Color::Blue);
						thiswindow.draw(bibka);
					}
			}
	}
	CircleShape shape(10.f);
	shape.setPosition(player.pos_x - 10, player.pos_y - 10);
	thiswindow.draw(shape);
	RectangleShape fov;
	fov.setSize(Vector2f(150,1));
	fov.setPosition(player.pos_x,player.pos_y);
	fov.setRotation(player.rotation);
	thiswindow.draw(fov);
}

int main()
{
	RenderWindow thiswindow(sf::VideoMode(800, 600), "My window");
	//thiswindow.setFramerateLimit(60);
	Player player(175, 175, 0);
	while (thiswindow.isOpen()) {
		Event event;
		//player.rotation+=0.5;
		while (thiswindow.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				thiswindow.close();


		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.rotation += 1.f;
			if (player.rotation > 360) {
				player.rotation -= 360.f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.rotation -= 1.f;
			if (player.rotation < 0) {
				player.rotation += 360.f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.pos_y += 1.f*sin(player.rotation*PI/180);
			player.pos_x += 1.f * cos(player.rotation * PI / 180);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player.pos_y -= 1.f * sin(player.rotation * PI / 180);
			player.pos_x -= 1.f * cos(player.rotation * PI / 180);
		}
		drawing(thiswindow, player);

		thiswindow.display();
	}
	return 0;
}
