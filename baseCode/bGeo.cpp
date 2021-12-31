#include "bGeo.h"
#include <math.h>

Pos Pos::ZERO = { 0.0F, 0.0F };


bool Geomath::RectToPoint(const bRect& _left, const Pos& _pos)
{
	if (_left.Right() < _pos.X)
		return false;
	if (_left.Left() > _pos.X)
		return false;
	if (_left.Top() > _pos.Y)
		return false;
	if (_left.Bot() < _pos.Y)
		return false;
	return true;
}

bool Geomath::RectToRect(const bRect& _left, const bRect& _right)
{
	if (_left.Right() < _right.Left())
		return false;
	if (_left.Left() > _right.Right())
		return false;
	if (_left.Top() > _right.Bot())
		return false;
	if (_left.Bot() < _right.Top())
		return false;
	return true;
}

bool Geomath::CircleToCircle(const bCircle& _left, const bCircle& _right)
{
	float Dis = PToPDis(_left.pos, _right.pos);
	float RSum = _left.size.X + _right.size.X;
	return Dis < RSum;
}

bool Geomath::CircleToPoint(const bCircle& _left, const Pos& _pos)
{
	float Dis = PToPDis(_left.pos, _pos);
	float RSum = _left.size.X;
	return Dis < RSum;
}

bRect Geomath::WCRECT;
bRect Geomath::HCRECT;

bool Geomath::RectToCircle(const bRect& _left, const bCircle& _right)
{
	WCRECT = _left;
	HCRECT = _left;

	WCRECT.size.X += _right.size.X * 2.0f;
	WCRECT.size.Y += _right.size.Y * 2.0f;

	if (true == RectToPoint(WCRECT, _right.pos) || 
		true == RectToPoint(HCRECT, _right.pos))
	{
		return true;
	}

	if (true == CircleToPoint(_right, _left.LeftTop()) ||
		true == CircleToPoint(_right, _left.LeftBot()) ||
		true == CircleToPoint(_right, _left.RightTop()) ||
		true == CircleToPoint(_right, _left.RightBot()))
	{
		return true;
	}
	return false;
}

float Geomath::ABS(float _value)
{
	return _value < 0 ? _value * -1.0f : _value;
}

float Geomath::PToPDis(const Pos& _left, const Pos& _right)
{
	float X = ABS(_left.X - _right.X);
	float Y = ABS(_left.Y - _right.Y);
	return sqrtf((X * X) + (Y * Y));
}
