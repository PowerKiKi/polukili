/************************************************
Balls - A Box2D Test Program for the Nintendo Wii

                                    (c)2008 0xtob
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <wiisprite.h>
#include <Box2D.h>
#include <fat.h>

using namespace wsp;

b2World *world = 0;

const float PIXELS_PER_UNIT     = 80.0;
const float DEFAULT_DENSITY     = 5.0f;
const float DEFAULT_FRICTION    = 0.3f;
const float DEFAULT_RESTITUTION = 0.9f;

const int MAX_BALLS             = 1000;

const float BALL_RADIUS         = 17.0;
const float32 timeStep          = 1.0f / 60.0f;
const int32 iterations          = 10;

int screen_width, screen_height;

Image *ballimage;

Sprite pointersprite;

class Ball
{
	public:
		
		Sprite sprite;
		b2Body *body;
		
		Ball(float x, float y);
		~Ball();
		void draw(void);
};

Ball::Ball(float x, float y)
{
	sprite.SetImage(ballimage, 48, 48);
	sprite.SetFrame(rand()%4);
	
	b2BodyDef bodyDef;
	bodyDef.position.Set(x / PIXELS_PER_UNIT, y / PIXELS_PER_UNIT);
	body = world->CreateBody(&bodyDef);
	b2CircleDef circledef;
	circledef.radius = BALL_RADIUS / PIXELS_PER_UNIT;
	
	circledef.density = DEFAULT_DENSITY;
	circledef.friction = DEFAULT_FRICTION;
	circledef.restitution = DEFAULT_RESTITUTION;
	
	body->CreateShape(&circledef);
	body->SetMassFromShapes();
}

Ball::~Ball()
{
	world->DestroyBody(body);
}

void Ball::draw(void)
{
	sprite.SetRotation((float)body->GetAngle() / M_PI * 180.0);
	b2Vec2 pos = body->GetPosition();
	sprite.SetPosition(PIXELS_PER_UNIT*pos.x, PIXELS_PER_UNIT*pos.y);
	sprite.Draw();
}

Ball *balls[MAX_BALLS];
int n_balls = 0;

void makeWorld(void)
{
	b2AABB worldAABB;
	// Visible area is 8x6 units
	worldAABB.lowerBound.Set(-8.0f, -6.0f);
	worldAABB.upperBound.Set(16.0f, 12.0f);
	b2Vec2 gravity(0.0f, 10.0f);
	bool doSleep = false;
	world = new b2World(worldAABB, gravity, doSleep);
	
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	
	// Get Screen Resolution
	// It turns out this is tricky because in a TV you never know your effective resolution and origin
	// So, I'm using works-for-me heuristics
	GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);
	screen_width = (int)((float)rmode->viWidth * 0.9f); // <- works for me
	screen_height = (int)((float)rmode->viHeight * 0.9f);
	float32 width = (float)screen_width / PIXELS_PER_UNIT;
	float32 height = (float)screen_height / PIXELS_PER_UNIT;
	
	// Create a room
	b2PolygonDef groundShapeDef[4];
	groundShapeDef[0].SetAsBox(float32(width), float32(0.1f),   b2Vec2(width/2.0, -0.1),       0.0);
	groundShapeDef[1].SetAsBox(float32(width), float32(0.1f),   b2Vec2(width/2.0, height),     0.0);
	groundShapeDef[2].SetAsBox(float32(0.1f),  float32(height), b2Vec2(-0.1,      height/2.0), 0.0);
	groundShapeDef[3].SetAsBox(float32(0.1f),  float32(height), b2Vec2(width,     height/2.0), 0.0);
	
	for(int i=0;i<4;++i)
		groundBody->CreateShape(&groundShapeDef[i]);
}

int main(int argc, char **argv)
{
	fatInitDefault();
	
	// Create the game window and initalise the VIDEO subsystem
	GameWindow gwd;
	gwd.InitVideo();

	gwd.SetBackground((GXColor){ 255, 255, 255, 255 });

	// Initialise Wiimote
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
	
	makeWorld();
	
	ballimage = new Image();
	
	if(ballimage->LoadImage("./data/enemies.png") != IMG_LOAD_ERROR_NONE)
		exit(0);
	
	pointersprite.SetImage(ballimage, 48, 48);
	pointersprite.SetFrame(2);
	
	for(;;)
	{
		WPAD_ScanPads();
		
		u16 btnsdown = WPAD_ButtonsDown(0);
		u16 btnsheld = WPAD_ButtonsHeld(0);

		// Infrared calculation
		ir_t ir; // The struct for infrared
		WPAD_IR(WPAD_CHAN_0, &ir); // Let's get our infrared data
		
		pointersprite.SetPosition(ir.sx-200, ir.sy-250);
		pointersprite.SetRotation(ir.angle/2); // Set angle/2 to translate correctly
		pointersprite.Draw();
		
		if(btnsdown & WPAD_BUTTON_HOME)
			break;
		
		// The A button spawns a ball
		if(btnsdown & WPAD_BUTTON_A)
		{
			if(n_balls < MAX_BALLS - 1)
			{
				balls[n_balls] = new Ball(ir.sx-200, ir.sy-250);
				n_balls++;
			}
		}
		
		// The 1 button clears you balls
		if(btnsdown & WPAD_BUTTON_1)
		{
			for(int b=0; b<n_balls; ++b)
			{
				delete balls[b];
			}
			n_balls = 0;
		}
		
		// While the B button is pressed, you can adjust gravity by tilting the Wiimote
		if(btnsheld & WPAD_BUTTON_B)
		{
			struct gforce_t gforce;
			WPAD_GForce(0, &gforce);
			b2Vec2 g;
			g.x = gforce.x;
			g.y = - gforce.y;
			world->SetGravity(20.0f * g);
		}
		
		// Draw the balls
		for(int b=0; b<n_balls; ++b)
		{
			balls[b]->draw();
		}
		
		gwd.Flush();
		
		// Advance the physics simulation
		world->Step(timeStep, iterations);
	}
	return 0;
}
