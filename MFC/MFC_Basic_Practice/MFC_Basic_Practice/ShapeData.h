#pragma once
class ShapeData
{
	CPoint pt;
	COLORREF color;
	int type;
	int width;
public:
	ShapeData();
	ShapeData(CPoint _pt, COLORREF _color, int _type, int _width);
	~ShapeData();
public:
	void SetPt(CPoint value)	{	pt = value;	}
	void SetColor(COLORREF value) { color = value; }
	void SetType(int value) { type = value; }
	void SetWidth(int value) { width = value; }
	CPoint GetPt() const { return pt; }
	COLORREF GetColor() const { return color; }
	int GetType() const { return type; }
	int GetWidth() const { return width; }
public:

};

