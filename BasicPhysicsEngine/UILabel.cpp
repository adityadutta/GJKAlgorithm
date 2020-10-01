#include "UILabel.h"

UILabel::UILabel(std::string _text, Vec3 _position, SDL_Color _color, int _fontSize)
{
	text = _text;
	position = _position;
	color = _color;
	fontSize = _fontSize;
}

void UILabel::SetFont(std::string _fontName)
{
	fontName = _fontName;
}
