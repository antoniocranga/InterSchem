#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <queue>
using namespace sf;
using namespace std;
enum button_states {
	BTN_IDLE=0, BTN_HOVER
};
class Button
{
private : 
	short unsigned buttonStates;
	RectangleShape shape;
	Font *font;
	Text text;
	Color textColor;
	Color idleColor;
	Color hoverColor;
	bool clicked;
	string instructiune;
public: 
	Button(float x, float y, float width, float heigth, Font*font, string text, Color idleColor, Color hoverColor , Color textColor , string instructiune);
	~Button();
	void update(const Vector2f mousePos, Event event);
	void render(RenderTarget* target);
};

#endif