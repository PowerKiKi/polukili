/*
 * libwiisprite - TiledLayer
 */

#ifndef LIBWIISPRITE_TILEDLAYER
#define LIBWIISPRITE_TILEDLAYER

#include <stdlib.h>
#include <gccore.h>
#include "image.h"
#include "layer.h"

//!libwiisprite namespace
namespace wsp{
	//!Capable of drawing a grid of cells with tiles from an image.
	class TiledLayer : public Layer{
		public:
			//!Constructor.
			//!\param columns The number of columns.
			//!\param rows The number of rows.
			//!\param ani The possible number of tiles with animations.
			TiledLayer(s32 columns, s32 rows, u32 ani);
			//!Destructor.
			virtual ~TiledLayer();
			
			//Gets an Image and sets it as a tileset.
			//!\param image The image to set as the new Tilesetlayer. If the Image has more or equal tiles, the data won't change.
			//!\param tileWidth The width of each tile.
			//!\param tileHeight The height of each tile.
			void SetStaticTileset(Image* image, u32 tileWidth, u32 tileHeight);
			//!Sets a cell with a specific tile.
			//!\param col The column of the cell.
			//!\param row The row of the cell.
			//!\param tileIndex A static or animated tile.
			void SetCell(u32 col, u32 row, s32 tileIndex);
			
			//!Fills a rectangle with a specific tile.
			//!\param col The column to start.
			//!\param row The row to start.
			//!\param numCols The length in columns.
			//!\param numRows The length in rows.
			//!\param tileIndex A static or animated tile.
			void FillCells(u32 col, u32 row, u32 numCols, u32 numRows, s32 tileIndex);

			//!Creates an animated tile.
			//!\return The index of the tile or 0, if there is no more space left. 
			//!\sa \ref tiledlayer_animations_page
			s32 CreateAnimatedTile();
			//!Gets which tile is currently drawn on the animated tile.
			//!\param animatedTileIndex The index of the animated tile.
			//!\return The tile currently drawn at the specified animated tile.
			//!\sa \ref tiledlayer_animations_page
			u32 GetAnimatedTile(s32 animatedTileIndex) const;
			//!Changes the tile that is drawn at the animated tile.
			//!\param animatedTileIndex The index of the animated tile.
			//!\param staticTileIndex The static tile to be drawn at the animated tile.
			//!\sa \ref tiledlayer_animations_page
			void SetAnimatedTile(s32 animatedTileIndex, u32 staticTileIndex);

			//!Gets the cell at a specified position.
			//!\param col The column of the cell.
			//!\param row The row of the cell.
			//!\return A static or animated tile at this position.
			s32 GetCell(u32 col, u32 row) const;
			//!Gets the cell width.
			//!\return The width of a single cell.
			u32 GetCellWidth() const;
			//!Gets the cell height.
			//!\return The height of a single cell.
			u32 GetCellHeight() const;
			//!Gets the size of the columns.
			//!\return The size of one column.
			u32 GetColumns() const;
			//!Gets the size of the rows.
			//!\return The size of one row.
			u32 GetRows() const;
			//!Gets the image of the tiledlayer.
			//!\return A pointer to the image. NULL if there is no image specified.
			const Image* GetImage() const;

			//!Sets the transparency of the tiledlayer. 
			//!\param alpha Sets the transparency. Has a range from 0x00 (invisible) to 0xFF (fully visible)
			void SetTransparency(u8 alpha);
			//!Gets the transparency of the tiledlayer.
			//!\return The current transparency of the tiledlayer. Has a range from 0x00 (invisible) to 0xFF (fully visible)
			u8 GetTransparency() const;

			//!Draws the tiledlayer to the current viewport.
			void Draw(f32 offsetX = 0, f32 offsetY = 0) const;
		protected:
		private:
			s32* _data; u32 _columns, _rows;
			u32 _tileWidth, _tileHeight;
			u32* _animations; u32 _aniSize, _aniBoundary;
			Image* _image; u32 _tiles;
			u8 _alpha;
	};
};
/*! \page tiledlayer_animations_page TiledLayer - Animations
 * Animations can help you bring that little movement in a normally static layer.
 *
 * You probably already understand how to set cells on a TiledLayer and how to draw them. TiledLayer
 * can actually help you make these tiles animated, without big hassle for the developer.
 *
 * Animations are basically negative numbers which have a positive tile assigned to them. When
 * you initialize TiledLayer, you specify how many of these animation tiles you want to possibly have.
 *
 * If you want to get a new index for an animated tile, call CreateAnimatedTile() and the TiledLayer
 * will return a new nuber to use. The first animated tile is -1, the second is -2, the third -3 and so
 * on. You can SetCell() or FillCell() the TiledLayer with this index.
 *
 * The first assigned value to an animated tile is 0, to change it, you can use
 * SetAnimatedTile(). To retrieve the current assigned value, you can use GetAnimatedTile().
 * You will see how every tile you assigned with the animated tile changes to this new tile.
 * 
 * Developers should make their own animation flip methods to animate water with tiles or to
 * make a fire flicker. Animated tiles just make it easier.
 *
 */

#endif
