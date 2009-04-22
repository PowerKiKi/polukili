/*
 * libwiisprite - LayerManager
 */

#ifndef LIBWIISPRITE_LAYERMANAGER
#define LIBWIISPRITE_LAYERMANAGER

#include <stdlib.h>
#include <gccore.h>
#include "layer.h"

//!libwiisprite namespace
namespace wsp{
	//!Groups layers into one block in which they can be managed.
	class LayerManager{
		public:
			//!Constructor.
			//!\param boundary Specifies how many layers can be grouped into this manager.
			LayerManager(u32 boundary);
			//!Destructor.
			virtual ~LayerManager();

			//!Appends a layer at the end, thus drawing it at last.
			//!\param layer The layer to append. If it is already in the list, it gets removed first.
			//!\sa \ref layermanager_append_page
			void Append(Layer* layer);
			//!Inserts a layer into the manager. 
			//!\param layer The layer to insert. If it is already in the list, it gets removed first.
			//!\param index The new index of the layer. Can't be bigger than GetSize().
			//!\sa \ref layermanager_append_page
			void Insert(Layer* layer, u32 index);
			//!Removes a layer from the list.
			//!\param layer A layer that is in the list.
			//!\sa \ref layermanager_append_page
			void Remove(Layer* layer);
			//!Clears the whole LayerManager from all Layers.
			//!\sa \ref layermanager_append_page
			void RemoveAll();

			//!Returns a layer at a specified index.
			//!\param index The index from where to poll the layer. Can't be bigger than GetSize().
			//!\return A pointer to the layer at the index. NULL if index is out of bounds.
			//!\sa \ref layermanager_append_page
			Layer* GetLayerAt(u32 index) const;
			//!Returns the size of the list of layers.
			//!\return The size of the current layerlist.
			//!\sa \ref layermanager_append_page
			u32 GetSize() const;

			//!Specifies where to view the current scene.
			//!\param x The upper left corners X position.
			//!\param y The upper left corners Y position.
			//!\param width The width of the window.
			//!\param height The height of the window.
			//!\sa \ref layermanager_viewwindows_page
			void SetViewWindow(s32 x, s32 y, u32 width, u32 height);
			
			//!Draws all the layers in this LayerManager.
			//!\param x The X offset for drawing.
			//!\param y The Y offset for drawing.
			//!\sa \ref layermanager_viewwindows_page
			void Draw(s32 x, s32 y) const;
		protected:
			u32 _width, //!< The width of the viewwindow.
				_height; //!< The height of the viewwindow.
			s32 _x, //!< The X position of the viewwindow.
				_y; //!< The Y position of the viewwindow.
		private:
			Layer** _layers;
			u32 _size,
				_boundary;
	};
};

/*! \page layermanager_viewwindows_page LayerManager - ViewWindows
 * ViewWindows are an advanced feature of libwiisprite, as they allow to render only a specific part
 * of a scene at another specific position. It is the friend of friends when doing multiple views
 * or limiting the viewing rage.
 *
 * They also look complicated on the first look, but they are quite easy. Look at this graph to
 * understand:
 * \image html viewwindow.png
 * x and y mark the position of the ViewWindow and width and height specify how big the area
 * should be. For example: if you have a sprite that is drawn at (0;0) and you start your
 * ViewWindow at (5;5), the sprite gets a little bit cut off.
 *
 * The LayerManagers Draw() function does not alter the content of the ViewWindow at all, just where
 * it is displayed.
 */
/*! \page layermanager_append_page LayerManager - Appending Layers
 * To use your project efficiently, LayerManagers are ultimately recommended. They allow for easy
 * position change of a whole area or to limit the viewing range of it.
 *
 * LayerManagers do this by grouping many layers into one and drawing one after another. When you
 * append a Layer, it goes to the bottom, so it gets drawn the last. When you append another one,
 * this new one is going to be the last.
 *
 * When you Insert Layers, you can actually specify the index of the Layers. If you specify 0, it is
 * going to be the first Layer, if you specify 1 it is going to be the Layer after the first Layer
 * and so on.
 *
 * When you Insert and Append Layers, they get removed from the old LayerManager position to the new one,
 * but a Layer can be in multiple LayerManagers at once. Take this in mind when creating sorting
 * algorithms to use with the library.
 */

#endif
