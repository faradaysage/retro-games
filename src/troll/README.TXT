Sprite.h - deals with sprite routines, background routines (should have made background.h)
change filenames for enemys/objects, or add them, in enemyobj.h
change filenames for person (main sprite) or background in test.h

editmap is a program to edit a map.  to parameters: first is the pcx file second is the map file (program uses for collisions in map and initializing enemy/objects)
in edit map: "s" - show passable blocks
             "p" - make (un)passable
             "e" - make (non)enemy
             "a" - make (not)attainable (implemented: when person walks over attainable, move to new board [not used in test])
             "q" - quit and save
             esc - quit
             move cursor with arrows

in demo game (test.exe): use arrows to move
                         alt to shoot
                         space to throw rock (didn't open rock sprite, not eneough memory [this is where I quit])
                         "q" - quit

to add x-lib you should only have to change:
        DrawScreen() - should now only flip the page
        page_type should be the current page 1, 2, 3... not a buffer
        put_image()
        put_vbackground() (put virtual background)