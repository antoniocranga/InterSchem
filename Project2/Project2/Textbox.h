#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <queue>
#include <sstream>
using namespace std;
using namespace sf;
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
class Textbox
{
public: Textbox(){}
		Textbox(int size, Color color, bool sel , float x , float y , float width, float heigth)
		{
			rectangle.setPosition(x, y);
			rectangle.setSize({ width, heigth });
			rectangle.setFillColor(Color::White);
			textbox.setCharacterSize(size);
			textbox.setFillColor(color);
			isSelected = sel;
			if (sel)
			{
				textbox.setString("_");
			}
			else textbox.setString("");
		}
		void setFont(Font &font)
		{
			textbox.setFont(font);
		}
		void setPosition(int x, int y)
		{
			textbox.setPosition(x, y);
		}
		void setLimit(bool ToF, int lim)
		{
			hasLimit = ToF;
			limit = lim;
		}
		void drawTo(RenderWindow &window)
		{
			window.draw(rectangle);
			window.draw(textbox);
		}
		void typedOn(Event input)
		{
			if (isSelected)
			{
				int charTyped = input.text.unicode;
				if (charTyped < 128)
				{
					if (hasLimit == false)
					{
						if (text.str().length() <= limit)
						{
							inputLogic(charTyped);
						}
						else if (text.str().length() > limit && charTyped == DELETE_KEY)
						{
							deleteLastChar();
						}
					}
				}
			}
		}
		string getText()
		{
			return text.str();
		}
		void update(Vector2f mousePos, Event event)
		{
			if (this->rectangle.getGlobalBounds().contains(mousePos))
			{
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && this->isSelected == false)
					this->isSelected = true , textbox.setString(text.str() + "_");
			}
			else
			{
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && this->isSelected == true)
				{
					this->isSelected = false;
					string t = text.str();
					string newT = "";
					for (int i = 0; i < t.length(); i++)
					{
						newT += t[i];
					}
					text.str("");
					text << newT;
					textbox.setString(text.str());
				}
			}
		}
private: Text textbox;
		 RectangleShape rectangle;
		 ostringstream text;
		 bool isSelected = false;
		 bool hasLimit = false;
		 int limit = 100;
		 void inputLogic(int charTyped)
		 {
			 if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
			 {
				 text << static_cast<char>(charTyped);
			 }
			 else if (charTyped == DELETE_KEY)
			 {
				 if (text.str().length() > 0)
				 {
					 deleteLastChar();
				 }
			 }
			 textbox.setString(text.str() + "_");
		 }
		 void deleteLastChar()
		 {
			 string t = text.str();
			 string newT = "";
			 for (int i = 0; i < t.length() - 1; i++)
			 {
				 newT +=t[i];
			 }
			 text.str("");
			 text << newT;
			 textbox.setString(text.str());
		 } 
};
