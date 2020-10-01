#ifndef UILABEL_H
#define UILABEL_H

#include<SDL.h>
#include"Vector.h"
#include<string>

using namespace MATH;
///Class to hold text elements of the UI
class UILabel
{
public:
	std::string text;
	Vec3 position;								//variable to hold the value of position
	SDL_Color color;
	int fontSize;
	std::string fontName;

	UILabel(std::string _text, Vec3 _position, SDL_Color _color, int _fontSize);
	void SetFont(std::string _fontName);
};

#endif //!UILABEL_H

