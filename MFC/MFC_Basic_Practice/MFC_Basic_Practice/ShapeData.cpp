#include "stdafx.h"
#include "ShapeData.h"


ShapeData::ShapeData()
{
}

ShapeData::ShapeData(CPoint _pt, COLORREF _color, int _type, int _width)
	:pt(_pt), color(_color), type(_type), width(_width)
{
}


ShapeData::~ShapeData()
{
}
