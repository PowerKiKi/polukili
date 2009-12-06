#include <math.h>
#include "tiledlayer.h"

#define FRAME_CORRECTION 0.375f //!< Displays frames a lot nicer, still needs a complete fix.

namespace wsp{
	TiledLayer::TiledLayer(s32 columns, s32 rows, u32 ani) : Layer(),
		_data(NULL), _columns(columns), _rows(rows),
		_tileWidth(0), _tileHeight(0),
		_animations(NULL), _aniSize(0), _aniBoundary(ani),
		_image(NULL), _tiles(0), _alpha(0xff)
	{
		// Initialize data
		_data = new s32[_columns*_rows];
		for(u32 i = 0; i < _columns*_rows; i++)
			_data[i] = 0;
		
		// Initialize animationarray
		_animations = new u32[_aniBoundary];
		for(u32 i = 0; i < _aniBoundary; i++)
			_animations[i] = 0;
	}
	TiledLayer::~TiledLayer(){
		// Delete data
		if(_data)
			delete[] _data; _data = NULL;
		if(_animations)
			delete[] _animations; _animations = NULL;
	}

	void TiledLayer::SetStaticTileset(Image* image, u32 tileWidth, u32 tileHeight){
		if(_rows < 1 || _columns < 1 || image == NULL || !image->IsInitialized() ||
			tileWidth < 1 || tileHeight < 1 ||
			image->GetWidth() % tileWidth != 0 || image->GetHeight() % tileHeight != 0)return;

		// All checks are done, we can erase the old data and init our tileset
		u32 width = image->GetWidth()/tileWidth, height = image->GetHeight()/tileHeight;
		_tileWidth = tileWidth; _tileHeight = tileHeight;
		
		// If imagedata has as many or more tiles, data gets preserved
		if(_image != NULL){
			if(width*height >= _tiles){
				_tiles = width*height;
				_image = image;
				return;
			}
		}
		_tiles = width*height;
		_image = image;
		
		// If data is different, erase all data
		for(u32 i = 0; i < _columns*_rows; i++)
			_data[i] = 0;
		_aniSize = 0;
		for(u32 i = 0; i < _aniBoundary; i++)
			_animations[i] = 0;
	}
	void TiledLayer::SetCell(u32 col, u32 row, s32 tileIndex){
		if(col < 0 || row < 0 || col >= _columns || row >= _rows || tileIndex > (s32)_tiles)return;

		_data[(row*_columns)+col] = tileIndex;
	}
	void TiledLayer::FillCells(u32 col, u32 row, u32 numCols, u32 numRows, s32 tileIndex){
		if(numCols < 1 || numRows < 1 || col < 0 || row < 0 || tileIndex > (s32)_tiles ||
			col+numCols > _columns || row+numRows > _rows)return;
		
		// All checks are done, so we can continue filling our tileset
		for(u32 y = row; y < row+numRows; y++){
			for(u32 x = col; x < col+numCols; x++){
				_data[(y*_columns)+x] = tileIndex;
			}
		}
	}

	s32 TiledLayer::CreateAnimatedTile(){
		if(_aniSize+1 > _aniBoundary)return 0;

		_aniSize++;
		return -_aniSize;
	}
	u32 TiledLayer::GetAnimatedTile(s32 animatedTileIndex) const{
		if(animatedTileIndex >= 0 || (u32)-animatedTileIndex > _aniSize)return 0;
		
		return _animations[-animatedTileIndex-1];
	}
	void TiledLayer::SetAnimatedTile(s32 animatedTileIndex, u32 staticTileIndex){
		if(animatedTileIndex >= 0 || (u32)-animatedTileIndex > _aniSize ||
			staticTileIndex > _tiles)return;

		_animations[-animatedTileIndex-1] = staticTileIndex;
	}
	
	s32 TiledLayer::GetCell(u32 col, u32 row) const{
		if(col >= _columns || row >= _rows)return 0;

		return _data[(row*_columns)+col];
	}
	u32 TiledLayer::GetCellWidth() const{
		return _tileWidth;
	}
	u32 TiledLayer::GetCellHeight() const{
		return _tileHeight;
	}
	u32 TiledLayer::GetColumns() const{
		return _columns;
	}
	u32 TiledLayer::GetRows() const{
		return _rows;
	}
	const Image* TiledLayer::GetImage() const{
		return _image;
	}

	void TiledLayer::SetTransparency(u8 alpha){
		_alpha = alpha;
	}
	u8 TiledLayer::GetTransparency() const{
		return _alpha;
	}

	void TiledLayer::Draw(f32 offsetX, f32 offsetY) const{
		// TODO: There is a very small problem with displaying tiles this way.
		// Sometimes additional lines get drawn, which shouldn't be there.
		// This problem is also present in Sprite, but due to how sprites are
		// made, this problem is not so noticable.
		
		if(_image == NULL || !_image->IsInitialized() || _image->GetWidth() == 0 ||
			IsVisible() == false || _alpha == 0x00 ||
			_tileWidth == 0 || _tileHeight == 0)return;
		
		// Get width and height
		f32 width = _tileWidth/2,
			height = _tileHeight/2;

		// Use the image
		_image->BindTexture(false);

		for(u32 y = 0; y < _rows; y++){
			for(u32 x = 0; x < _columns; x++){
				s32 data = _data[y*_columns+x];
				// Check if tile should be displayed
				if(data == 0 || -data > (s32)_aniSize)continue;
				// Get animation frame data
				if(data < 0)data = _animations[-data-1];
				// Last bit of checks
				if(data <= 0 || data > (s32)_tiles)continue;
				data--;
				
				// Get frame position
				f32 frameX = (data%(_image->GetWidth()/_tileWidth))*_tileWidth,
					frameY = (data/(_image->GetWidth()/_tileWidth))*_tileHeight;

				// Init position
				Mtx model, tmp;
				guMtxIdentity(model);
				guMtxRotDeg(tmp, 'z', 0.0f);
				guMtxConcat(model, tmp, model);
				guMtxTransApply(model, model, GetX()+x*_tileWidth+width+offsetX, GetY()+y*_tileHeight+height+offsetY, 0.0f);
				guMtxConcat(model, tmp, model);
				GX_LoadPosMtxImm(model, GX_PNMTX0);

				// Draw the texture on the quad
				f32 txCoords[4] = {
					frameX/_image->GetWidth()+(FRAME_CORRECTION/_image->GetWidth()),
					frameY/_image->GetHeight()+(FRAME_CORRECTION/_image->GetHeight()),
					(frameX+_tileWidth)/_image->GetWidth()-(FRAME_CORRECTION/_image->GetWidth()),
					(frameY+_tileHeight)/_image->GetHeight()-(FRAME_CORRECTION/_image->GetHeight())
				};	

				// Draw the Quad
				GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
					GX_Position2f32(-width, -height);
					GX_Color4u8(0xff,0xff,0xff, _alpha);
			 		GX_TexCoord2f32(txCoords[0], txCoords[1]);
					GX_Position2f32(width, -height);
					GX_Color4u8(0xff,0xff,0xff, _alpha);
					GX_TexCoord2f32(txCoords[2], txCoords[1]);
					GX_Position2f32(width,height);
					GX_Color4u8(0xff,0xff,0xff, _alpha);
					GX_TexCoord2f32(txCoords[2], txCoords[3]);
					GX_Position2f32(-width,height);
					GX_Color4u8(0xff,0xff,0xff, _alpha);
					GX_TexCoord2f32(txCoords[0], txCoords[3]);
				GX_End();
			}
		}
	}
};
