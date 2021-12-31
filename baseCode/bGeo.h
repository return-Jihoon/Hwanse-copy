#pragma once

enum Pivot
{
	LT,
	T,
	RT,
	R,
	RB,
	B,
	LB,
	L,
	CENTER,
	CUSTOM
};

class Pos
{
public:
	static Pos ZERO;

public:
	typedef class _iPos
	{
	public:
		int X;
		int Y;
	}iPos;

	union
	{
		struct 
		{
			float X;
			float Y;
		};
		iPos IPOS;
		__int64 I64;
	};

public:
	bool operator == (const Pos& _other)
	{
		return X == _other.X && Y == _other.Y;
	}

	Pos operator * (const float _value)
	{
		return { X* _value, Y * _value };
	}

	Pos operator + (const Pos& _other)
	{
		return { X + _other.X, Y + _other.Y };
	}

	Pos& operator += (const Pos& _other)
	{ 
		X += _other.X;
		Y += _other.Y;
		return *this;
	}

	Pos operator - (const Pos& _other)
	{
		return { X - _other.X, Y - _other.Y };
	}

	Pos& operator = (const Pos& _other)
	{
		X = _other.X;
		Y = _other.Y;
		return *this;
	}

public:
	iPos ConvertInt()
	{
		iPos tmp;
		tmp.X = (int)X;
		tmp.Y = (int)Y;
		return tmp;
	}

	float HX() const
	{
		return X * 0.5f;
	}
	
	float HY() const
	{
		return Y * 0.5f;
	}

	inline int IX() const
	{
		return (int)X;
	}

	inline int IY() const
	{
		return (int)Y;
	}

	int IHX() const
	{
		return (int)HX();
	}

	int IHY() const
	{
		return (int)HY();
	}

public:
	Pos() : X(0.0f), Y(0.0f)
	{}
	Pos(float _x, float _y) : X(_x), Y(_y)
	{}
	~Pos() {}
};

typedef Pos pSize;

class bRect
{
public:
	Pivot m_Pivot;
	Pos pos;
	Pos size;

public:
	int iLeft() const
	{
		return (int)Left();
	}

	float Left() const
	{
		switch (m_Pivot)
		{
		case LT:
			return pos.X;
		case T:
			break;
		case RT:
			break;
		case R:
			break;
		case RB:
			break;
		case B:
			break;
		case LB:
			break;
		case L:
			break;
		case CENTER:
			return pos.X - size.HX();
		default:
			break;
		}
		return 0;
	}
	float Right() const
	{
		switch (m_Pivot)
		{
		case LT:
			return pos.X + size.X;
		case T:
			break;
		case RT:
			break;
		case R:
			break;
		case RB:
			break;
		case B:
			break;
		case LB:
			break;
		case L:
			break;
		case CENTER:
			return pos.X + size.HX();
		default:
			break;
		}
		return 0;
	}
	float Top() const
	{
		switch (m_Pivot)
		{
		case LT:
			return pos.Y;
		case T:
			break;
		case RT:
			break;
		case R:
			break;
		case RB:
			break;
		case B:
			break;
		case LB:
			break;
		case L:
			break;
		case CENTER:
			return pos.Y - size.HY();
		default:
			break;
		}
		return 0;
	}
	float Bot() const
	{
		switch (m_Pivot)
		{
		case LT:
			return pos.Y + size.Y;
		case T:
			break;
		case RT:
			break;
		case R:
			break;
		case RB:
			break;
		case B:
			break;
		case LB:
			break;
		case L:
			break;
		case CENTER:
			return pos.Y + size.HY();
		default:
			break;
		}
		return 0;
	}

	Pos LeftTop() const
	{
		return { Left(), Top() };
	}

	Pos RightTop() const
	{
		return { Right(), Top() };
	}

	Pos LeftBot() const
	{
		return { Left(), Bot() };
	}

	Pos RightBot() const
	{
		return { Right(), Bot() };
	}

public:
	bRect & operator = (const bRect& _other)
	{
		m_Pivot = _other.m_Pivot;
		size = _other.size;
		pos = _other.pos;
		return *this;
	}

public:
	bRect() : m_Pivot(LT)
	{

	}

	bRect(Pivot _pivot)
	{
		m_Pivot = _pivot;
	}

};

typedef bRect bCircle;

class Geomath
{
private:
	static bRect WCRECT;
	static bRect HCRECT;

public:
	static bool RectToRect(const bRect& _left, const bRect& _right);
	static bool RectToPoint(const bRect& _left, const Pos& _pos);
	static bool CircleToCircle(const bCircle& _left, const bCircle& _right);
	static bool CircleToPoint(const bCircle& _left, const Pos& _pos);

	static bool RectToCircle(const bRect& _left, const bCircle& _right);
	static float ABS(float _value);
	static float PToPDis(const Pos& _left, const Pos& _right);
};