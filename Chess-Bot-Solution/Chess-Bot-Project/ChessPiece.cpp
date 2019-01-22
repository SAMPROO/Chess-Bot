#include "ChessPiece.h"

ChessPiece::ChessPiece(std::wstring unicode, int color, int code) {
	_unicode = unicode;
	_code = code;
	_color = color;
}

void ChessPiece::setCode(int code) {
	_code = code;
}

int ChessPiece::getCode() {
	return _code;
}

void ChessPiece::setUnicode(std::wstring unicode) {
	_unicode = unicode;
}

std::wstring ChessPiece::getUnicode() {
	return _unicode;
}

void ChessPiece::setColor(int color) {
	_color = color;
}

int ChessPiece::getColor() {
	return _color;
}