#include "Button.h"
using namespace std;
using namespace sf;
Button::Button(float x, float y, float width, float heigth, Font*font, string text, Color idleColor, Color hoverColor, Color textColor , string instructiune)
{
	this->buttonStates = BTN_IDLE;
	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, heigth));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(15);
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->textColor = textColor;
	this->text.setFillColor(textColor);
	this->clicked = false;
	this->instructiune = instructiune;
	FloatRect rectBounds = this->shape.getGlobalBounds();
	FloatRect textBounds = this->text.getGlobalBounds();
	this->text.setPosition(rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2) , rectBounds.top + (rectBounds.height/2) - textBounds.height);
	/*this->text.setPosition(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
						   this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);*/
	
}

Button::~Button()
{

}
void Button::render(RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}