/*
 * Spritetest for libwiisprite by Chaosteil
 *
 * Showcases some features of the library.
 *
 * If you load this program with wiiload, make sure
 * libwiisprite.png is in your root directory.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <fat.h>

#include <wiisprite.h> // The main libwiisprite header.
using namespace wsp; // To not make us type this again and again

#include "libwiisprite.h" // This is the header file we got from the devkitPPC tool "raw2c"

GameWindow gwd; // Initializes and renders our scene.
Sprite sprite; // The drawable object we can modify.
Sprite sprite2; // Another drawable object we can modify.
Quad quad; // A drawable rectangle for fading in and out.
Image image; // Holds our image/texture from the SD Card.
Image image2; // Holds our buffer image/texture.

// A little helper function to calculate our fading data
bool calc_fade(u8 fade);
u8 fadedata = 0xff; // And a var to help us calculate fading.

// Entry point
int main(int argc, char **argv) {
	// Initialize filesystem to load from SD Card
	fatInitDefault();

	// Initialize Video
	gwd.InitVideo();
	
	// We initialize our layermanager with max. 3 layers, just for our testing purposes.
	LayerManager manager(3); // DO NOT FORGET TO INCREASE THIS NUMBER FOR YOUR OWN TESTS.

	// Now we're loading an image.
	// If the image is not found at our location, we exit to the loader
	if(image.LoadImage("libwiisprite.png") != IMG_LOAD_ERROR_NONE)exit(0);
	// The second image is loaded from the buffer.
	// We can simply use the same command.
	if(image2.LoadImage(libwiisprite) != IMG_LOAD_ERROR_NONE)exit(0);

	// We assign the loaded images to the sprites
	sprite.SetImage(&image);
	sprite2.SetImage(&image2);

	// We're gonna move the first sprite with the pointer
	sprite.SetPosition(0, 0);
	// Fix the second sprite to a position at the center of the screen.
	// The reference pixel is set to the center of the image at start,
	// so we can just set the right position after a simple refpixel
	// command.
	sprite2.SetRefPixelPositioning(REFPIXEL_POS_PIXEL); //X and Y move the refpixel to the coordinate.
	sprite2.SetPosition(320, 240); //Draws the center at the center of the screen

	// We set our quad to a far enough position to support all televisions.
	quad.SetPosition(-40, -40);
	// And set the width and height to a big enough number to use the full screen.
	quad.SetWidth(800);		// These are not optimized values, but should give
	quad.SetHeight(600);	// you an idea what to do.
	
	// Load both sprites and the quad into the LayerManager
	manager.Append(&sprite); // Gets drawn the closest.
	manager.Append(&sprite2); // Gets drawn the farthest.
	manager.Insert(&quad, 0); // Puts the quad to the first position.


	// This function initialises the wiimotes.
	WPAD_Init();
	// And this one gives us access to the accelerometers and infrared.
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

	// A small helper var with our fading process with the Quad.
	u8 fading = 1;
	while(1) {
		// Call WPAD_ScanPads each loop, this reads the latest controller states
		WPAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		u32 pressed = WPAD_ButtonsHeld(WPAD_CHAN_0);

		// We start the exiting via setting the fading value to 2.
		if(pressed & WPAD_BUTTON_HOME)fading = 2;
		// If the calc_fade function tells us to return, we will
		if(calc_fade(fading))break;	
		// Don't do anything if the quad is fully invisible.
		if(fadedata == 0x00)fading = 0;

		// With plus and minus we can zoom the sprite in or out
		if(pressed & WPAD_BUTTON_MINUS)
			sprite.SetZoom(sprite.GetZoom()-0.1f);
		if(pressed & WPAD_BUTTON_PLUS)
			sprite.SetZoom(sprite.GetZoom()+0.1f);
		// With A and B we can modify our transparency, just for fun.
		// We have to do the checks, so our program doesn't flip the transparency values.
		if(pressed & WPAD_BUTTON_A && sprite.GetTransparency() < 0xff-4)
			sprite.SetTransparency(sprite.GetTransparency()+5);
		if(pressed & WPAD_BUTTON_B && sprite.GetTransparency() > 4){
			sprite.SetTransparency(sprite.GetTransparency()-5);
		}

		// With the directional pad we modify the stretch values of the second sprite.
		if(pressed & WPAD_BUTTON_UP)
			sprite2.SetStretchHeight(sprite2.GetStretchHeight()+0.1f);
		if(pressed & WPAD_BUTTON_DOWN)
			sprite2.SetStretchHeight(sprite2.GetStretchHeight()-0.1f);
		if(pressed & WPAD_BUTTON_RIGHT)
			sprite2.SetStretchWidth(sprite2.GetStretchWidth()+0.1f);
		if(pressed & WPAD_BUTTON_LEFT)
			sprite2.SetStretchWidth(sprite2.GetStretchWidth()-0.1f);

		// Infrared calculation
		ir_t ir; // The struct for infrared
		WPAD_IR(WPAD_CHAN_0, &ir); // Let's get our infrared data
		// Give our sprite the positions and the angle.
		sprite.SetPosition(ir.sx-WSP_POINTER_CORRECTION_X, ir.sy-WSP_POINTER_CORRECTION_Y); // We use these constants to translate the position correctly to the screen
		sprite.Move(-((f32)sprite.GetWidth()/2), -((f32)sprite.GetHeight()/2)); // And these to make our image appear at the center of this position.
		sprite.SetRotation(ir.angle/2); // Set angle/2 to translate correctly
		
		// Draw everything what's in the manager.
		manager.Draw(0, 0); 

		// Finish rendering of everything.
		gwd.Flush();
	}

	// One last draw and flush..
	manager.Draw(0, 0);
	gwd.Flush();
	
	// And we return to our loader!
	return 0;
}

// Calculates what to do with the quad.
bool calc_fade(u8 fade){
	// Here we calculate the current amount of transparency. 0 does nothing.
	if(fade == 1){ // Fading in
		if(fadedata < 0x10)fadedata = 0x10;
		fadedata -= 0x10;
	}else if(fade == 2){ //Fading out
		if(0xef < fadedata)fadedata = 0xef;
		fadedata += 0x10;
	}
	// The fade is applied here. 0x00, 0x00, 0x00, 0xff are the default values of the quad,
	// so we don't set them before this command.
	quad.SetFillColor((GXColor){0x00, 0x00, 0x00, fadedata});
	// Now a check what to do with our fading.
	if(fade == 2 && fadedata == 0xff)return true;
	
	// Nothing is happening
	return false;
}
