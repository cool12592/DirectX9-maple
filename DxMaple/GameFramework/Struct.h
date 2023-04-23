#pragma once
//버텍스
typedef struct tagCustomVertex
{
	float x, y, z;
	D3DCOLOR color;
	float u, v;
}CUSTOMVERTEX;
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//인덱스
typedef struct tagCustomIndex
{
	WORD _0, _1, _2;
	
}CUSTOMINDEX;



typedef struct tagScreenVertex
{
	float x, y, z;
	float rhw;
	float u, v;
}SCREENVERTEX;
#define D3DFVF_SCREENVERTEX (D3DFVF_XYZRHW|D3DFVF_TEX1)



typedef struct tagColliderRect
{
	D3DXVECTOR3 minPosition;
	D3DXVECTOR3 maxPosition;
}COLLIDERRECT;

typedef struct tagColliderRect2D
{
	float left;
	float right;
	float top;
	float bottom;
}COLLIDERRECT2D;