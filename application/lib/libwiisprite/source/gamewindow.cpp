#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamewindow.h"

#define DEFAULT_FIFO_SIZE (1024*1024)

//extern GXRModeObj TVEurgb60Hz480IntDf;

namespace wsp{
	// Initializes the static members
	u32 GameWindow::_width = 0;
	u32 GameWindow::_height = 0;
	bool GameWindow::_initialized = false;
	Image* GameWindow::_lastimage = NULL;
	bool GameWindow::_lastimagebilinear = false;
	
	GameWindow::GameWindow() :
		_fb(0), _first(true), _rmode(NULL), _gp_fifo(NULL)
	{
		if(_initialized)return; // Don't mess with me!
		_frameBuffer[0] = NULL; _frameBuffer[1] = NULL;
	}
	GameWindow::~GameWindow(){
		StopVideo(); // Stops video automatically
	}

	void GameWindow::InitVideo(){
		// This Code is taken from many examples, but modified for this lib
		if(_initialized)return;
		// Start initializing
		VIDEO_Init();
		_rmode = VIDEO_GetPreferredMode(NULL);
		if(_rmode == NULL){
			exit(0);
			return;
		}
		
		// Allocate two framebuffers for double buffering
		_frameBuffer[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(_rmode));
		_frameBuffer[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(_rmode));

		// Check if they were allocated
		if(_frameBuffer[0] == NULL || _frameBuffer[1] == NULL){
			exit(0);
			return;
		}

		//_rmode = &TVEurgb60Hz480IntDf; // Fixes display mode for 480i PAL. Is in next libogc release.
		// Do some Init work
		VIDEO_Configure(_rmode);
		VIDEO_SetNextFramebuffer(_frameBuffer[_fb]);
		VIDEO_Flush();
		VIDEO_WaitVSync();
		if(_rmode->viTVMode&VI_NON_INTERLACE){
			 VIDEO_WaitVSync();
		}
		_fb ^= 1;

		// Init GX
		_gp_fifo = memalign(32, DEFAULT_FIFO_SIZE);
		memset(_gp_fifo, 0, DEFAULT_FIFO_SIZE);
		GX_Init(_gp_fifo, DEFAULT_FIFO_SIZE);

		// Set our background
		GXColor background = {0x00, 0x00, 0x00, 0x00};
		GX_SetCopyClear(background, 0x00ffffff);

		// Set up the display
		f32 yscale = 0; u32 xfbHeight = 0;
		yscale = GX_GetYScaleFactor(_rmode->efbHeight, _rmode->xfbHeight);
		xfbHeight = GX_SetDispCopyYScale(yscale);
		GX_SetViewport(0, 0,_rmode->fbWidth,_rmode->efbHeight, 0, 1);
		GX_SetScissor(0, 0, _rmode->fbWidth, _rmode->efbHeight);
		GX_SetDispCopySrc(0, 0, _rmode->fbWidth, _rmode->efbHeight);
		GX_SetDispCopyDst(_rmode->fbWidth, xfbHeight);
		GX_SetCopyFilter(_rmode->aa, _rmode->sample_pattern, GX_TRUE, _rmode->vfilter);
		// Use these values for GetWidth() and GetHeight()
		_width = (u32)_rmode->fbWidth; _height = (u32)_rmode->efbHeight;
		
		// Some additional Init code
		GX_SetFieldMode(_rmode->field_rendering, ((_rmode->viHeight == 2*_rmode->xfbHeight)?GX_ENABLE:GX_DISABLE));

		if(_rmode->aa){
			GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
		}else{
			GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
		}

		GX_SetCullMode(GX_CULL_NONE);
		GX_CopyDisp(_frameBuffer[0],GX_TRUE);
		GX_SetDispCopyGamma(GX_GM_1_0);

		GX_ClearVtxDesc();
		GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
		GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
		GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	
		GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0); // Positions given in 2 f32's (f32 x, f32 y)
		GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0); // Texture coordinates given in 2 f32's
		GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);		

		GX_SetNumChans(1);
		GX_SetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHTNULL, GX_DF_NONE, GX_AF_NONE);

		GX_SetNumTexGens(1);
		GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);	

		GX_InvalidateTexAll();
		
		Mtx GXmodelView2D;
		Mtx44 perspective;
		// Reset the model view matrix
		guMtxIdentity(GXmodelView2D);
		guMtxTransApply(GXmodelView2D, GXmodelView2D, 0.0f, 0.0f, -5.0f);
		// Apply changes to model view matrix
		GX_LoadPosMtxImm(GXmodelView2D,GX_PNMTX0);

		// Set the viewing matrix to use orthographic projection
		// guOrtho function completely modified for libwiisprite
		// TODO: make a different one for every resolution to make libwiisprite
		// 		look the same on every display
		if(_rmode == &TVPal528IntDf){ // PAL
			guOrtho(perspective, -37, 510, 0, 639, 0, 300); // No fix yet.
		}else{ // 480i
			guOrtho(perspective, -37, 510, 0, 639, 0, 300);
		}

		// Apply changes to the projection matrix
		GX_LoadProjectionMtx(perspective, GX_ORTHOGRAPHIC);

		GX_SetViewport(0, 0, _rmode->fbWidth, _rmode->efbHeight, 0, 1);
		GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
		GX_SetAlphaUpdate(GX_TRUE);
	
		// The final scissor box
		GX_SetScissorBoxOffset(0, 0);
		GX_SetScissor(0, 0, _width, _height);

		_initialized = true;
	}

	void GameWindow::StopVideo(){
		if(!_initialized)return;
		
		// Dhewg.. You rescued our asses again.
		// This code should be run before exiting the app.
		GX_AbortFrame();
		GX_Flush();

		// Thx to jepler for these quite obvious hints
		free(MEM_K1_TO_K0(_frameBuffer[0])); _frameBuffer[0] = NULL;
		free(MEM_K1_TO_K0(_frameBuffer[1])); _frameBuffer[1] = NULL;
		free(_gp_fifo); _gp_fifo = NULL;

		_initialized = false;
	}

	void GameWindow::SetBackground(GXColor bgcolor){
		GX_SetCopyClear(bgcolor, 0x00ffffff);
	}

	bool GameWindow::IsInitialized(){
		return _initialized;
	}

	void GameWindow::Flush(){
		GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
		GX_SetColorUpdate(GX_TRUE);
		GX_CopyDisp(_frameBuffer[_fb],GX_TRUE);
		GX_DrawDone();

		VIDEO_SetNextFramebuffer(_frameBuffer[_fb]);
		if(_first == true){
			_first = false;
			VIDEO_SetBlack(false); // --Now render everything again
		}
		VIDEO_Flush();
		VIDEO_WaitVSync();
 		_fb ^= 1;		// Flip framebuffer

		GX_InvalidateTexAll(); // Fixes some texture garbles
	}

	u32 GameWindow::GetWidth(){
		if(!_initialized)return 0;
		return _width;
	}

	u32 GameWindow::GetHeight(){
		if(!_initialized)return 0;
		return _height;
	}
};
