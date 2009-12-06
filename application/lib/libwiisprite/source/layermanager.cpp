#include "gamewindow.h"
#include "layermanager.h"

namespace wsp{
	LayerManager::LayerManager(u32 boundary) :
		_width(900), _height(800), _x(0), _y(0), // Biggest possible numbers on init
		_layers(NULL), _size(0), _boundary(boundary)
	{
		// Initialize our layers for usage
		_layers = new Layer*[_boundary];
		for(u32 i = 0; i < _boundary; i++)_layers[i] = NULL;
	}

	LayerManager::~LayerManager(){
		if(_layers)
			delete[] _layers; _layers = NULL;
	}

	void LayerManager::Append(Layer* layer){
		if(layer == NULL)return;
		// Remove it first from the Manager
		Remove(layer);
		// Check if it can be appended
		if(_size >= _boundary)return;

		// Set layer on farthest position
		_layers[_size] = layer;
		_size++;
	}

	void LayerManager::Insert(Layer* layer, u32 index){
		if(layer == NULL || index > _size)return;
		// Remove it first from the Manager
		Remove(layer);
		// Check if it can be inserted
		if(_size >= _boundary || index > _size)return;

		// Make some space for our new layer
		for(u32 i = _size; i > index; i--){
			_layers[i] = _layers[i-1];
		}
		_layers[index] = layer;
		_size++;
	}

	void LayerManager::Remove(Layer* layer){
		if(layer == NULL)return;

		bool shift = false;

		for(u32 i = 0; i < _size; i++){
			// Layer found and shifting everything forward
			if(shift){
				_layers[i] = _layers[i+1];
				if(i+2 == _size){ // One position before stop
					_layers[i+1] = NULL; break;
				}
			// Or check if the layers are equal and turn shifting on
			}else if(layer == _layers[i]){
				_layers[i] = NULL;
				shift = true;
				if(i+1 == _size)break;
			}
		}

		if(shift)_size--; // Success!
	}

	void LayerManager::RemoveAll(){
		for(u32 i = 0; i < _size; i++){
			_layers[i] = NULL;
		}
		_size = 0;
	}

	// TODO: Maybe add sorting?

	Layer* LayerManager::GetLayerAt(u32 index) const{
		if(index >= _size)return NULL;
		return _layers[index];
	}
	
	u32 LayerManager::GetSize() const{
		return _size;
	}

	void LayerManager::SetViewWindow(s32 x, s32 y, u32 width, u32 height){
		_x = x; _y = y;
		_width = width; _height = height;
	}

	void LayerManager::Draw(s32 x, s32 y) const{
		// Since this manager is using a modified scissor box, we use the data + hardcoded values
		GX_SetScissorBoxOffset(-x,-y-31);
		GX_SetScissor(0, 0, _width, _height);
		
		// Do the layers!	
		for(u32 i = _size; i > 0; i--){
			if(i == 0) break;
			if(_layers[i-1])
				_layers[i-1]->Draw(-_x, (-_y)-31); // As strange as it might look like, this fixes everything.
		}
		
		// Set Scissor boxes back to normal again
		GX_SetScissorBoxOffset(0, 0);
		GX_SetScissor(0, 0, GameWindow::GetWidth(), GameWindow::GetHeight());
	}
};
