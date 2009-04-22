
Box2DBalls - A small Box2D test app for the Nintendo Wii

                                          (c) 0xtob 2008


  This is my first attempt at Wii homebrew, and
  I'm pleasantly surprised by how easy it is
  thanks to the great libraries already availble.

  It turns out Box2D and the Wiimote play very well
  together. This might result in some more
  interesting games in the future :)


Controls:

  Press A to create Balls
  Hold B and tilt the Wiimote to adjust gravity
  Press 1 to clear the screen

Installation:

  Copy the Box2DBalls folder to the apps folder of
  your SD card and launch it through the homebrew
  channel.

Building the source:

  You need devkitPPC, libogc libwiisprite and Box2D.
  To build Box2D for the Wii, add the following lines
  to Source/Makefile:

================================================================================
WII_COMPILE_FLAGS= -c -g -O2 -mrvl -Wall $(MACHDEP) -I$(DEVKITPPC)/local/include

Gen/wii-fixed/%.o:      %.cpp
    @mkdir -p $(dir $@)
    powerpc-gekko-g++ $(WII_COMPILE_FLAGS) -DTARGET_FLOAT32_IS_FIXED -o $@ $<

Gen/wii-fixed/lib/libbox2d.a:   $(addprefix Gen/wii-fixed/,$(SOURCES:.cpp=.o))
    @mkdir -p $(dir $@)
    powerpc-gekko-ar cr $@ $^
    powerpc-gekko-ranlib $@ 

Gen/wii-fixed/%.d:      %.cpp
    @mkdir -p $(dir $@)
    powerpc-gekko-g++ -MM -MT $(@:.d=.o) $(WII_COMPILE_FLAGS) \
        -DTARGET_FLOAT32_IS_FIXED -o $@ $<
================================================================================

  Coming from the DS, I'm afraid of FPUs, thus I only added
  the fixed point target, so I'll leave you the float target
  as homework :)

Libraries:

  http://box2d.org
  http://wiibrew.org/wiki/Development_Applications/libwiisprite
  http://sourceforge.net/project/showfiles.php?group_id=114505&package_id=124208
  http://sourceforge.net/project/showfiles.php?group_id=114505&package_id=126925

Contact:

       IRC: _0xtob in #wiidev in Blitzed
    e-Mail: mii@tobw.net
      Blog: http://blog.dev-scene.com/0xtob/
  Homepage: http://tobw.net

