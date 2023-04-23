#pragma once
class Resources
{
public:
	explicit Resources(LPDIRECT3DDEVICE9 device) { d3dDevice_ = device; }
	~Resources() {}
	/*Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;*/
public:
	virtual void render() = 0;
	//virtual HRESULT initialize() = 0;
	//virtual HRESULT release() = 0;
protected:
	LPDIRECT3DDEVICE9 d3dDevice_;
};

