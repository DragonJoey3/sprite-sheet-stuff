#include "Wizard.h"
#include <raylib.h>
#include <vector>

/**
 * Notice how clean the main file of my program is.
 * This basic entrypoint of the program will require
 * basically no maintainence.
 *
 * This is called the "Single Responsibility Principal" (SRP)
 * and we will talk more about it later.
 */
int main() {

  /////////////////////
  /// Initial setup
  ////////////////
  InitWindow(500, 500, "Sprite sheet");
  SetTargetFPS(30);

  // Create a Wizard
  Wizard *wizard = new Wizard;

  while (!WindowShouldClose()) {

    // UPDATE Game Objects

    // Tell the wizard how long it's been since we last drew him.
    wizard->update(GetFrameTime());

    ///////////
    /// DRAWING
    ///////////
    BeginDrawing();
    ClearBackground(WHITE);

    // Wizard knows how to draw itself.
    wizard->draw();

    EndDrawing();
  }

  // Important to delete the Wizard before we call CloseWindow so that
  // All the resouces it created are disposed of before closing the OpenGL
  // context.
  delete wizard;

  // Now we can close the Window.
  CloseWindow();

  // Program exits successfully
  return 0;
}
