#pragma once
#include <raylib.h>
#include <string>

/**
 * This file controls an Animation that we can use to render an object ot the
 * screen.
 */
struct Animation {

  ////////
  /// Variables
  ///////

  // The image to draw the animation from
  Texture2D texture;

  // How long it should take to draw the entire animation
  float duration;

  // How many seconds into the animation we are.
  float timeIntoAnimation;

  // Constants that control the width and height of the sprites (individual
  // pictures)
  const float SPRITE_WIDTH;
  const float SPRITE_HEIGHT;

  // This will be set based on the size of the texture and the width of the
  // sprite
  int spriteCount;

  /**
   * A constructore for an animation that takes in 4 arguments
   * 1. A std::string that tells me where to find the image file.
   * 2. A float that is the width of the sprite in pixels.
   * 3. A float that is the height of the sprite in pixels.
   * 4. A float that is the duration the entire animation should last (in
   * seconds.)
   */
  Animation(std::string imageFile, float sprite_width, float sprite_height,
            float duration)
      : SPRITE_WIDTH(sprite_width), SPRITE_HEIGHT(sprite_height),
        duration(duration), timeIntoAnimation(0.0f) {

    // Load in the texture to the GPU.
    texture = LoadTexture(imageFile.c_str());

    // Set the value of how many sprites are on the sprite sheet.
    spriteCount = texture.width / SPRITE_WIDTH;
  }

  // A destructor to unload the texture when no longer needed.
  ~Animation() { UnloadTexture(texture); }

  // This will prevent anyone from making a copy of this animation.
  // If we want copies of the animation to be made we need to be careful
  // that we don't unload the texture until all copies are deleted, and
  // that we make sure we do unload the texture when the last copy is
  // deleted.  That sounds complex, so for now we set this function to
  // "delete" which means no one can make a copy.
  Animation(Animation &rhs) = delete;

  // This method will tell you if an animation is in the middle of drawing
  // still.
  bool isActive() { return timeIntoAnimation > 0; }

  // This advances the animation by delta_t seconds.
  void update(float delta_t) { timeIntoAnimation += delta_t; }

  // This method tells you if the animation is completed (i.e. gone past it's
  // duration.)
  bool animationComplete() { return timeIntoAnimation > duration; }

  // Reset the animation to time 0
  void reset() { timeIntoAnimation = 0.0f; }

  // Draw the sprite to the screen at this location
  void draw(const Vector2 &locationOnScreen) {

    // It's possible that we called draw before we realized the animation was
    // complete in that case we reset the animation here to ensure we don't go
    // out of bounds of our memory
    if (animationComplete()) {
      reset();
    }

    // Determine which sprite we are drawing.
    int animationFrame = timeIntoAnimation / (duration / (float)spriteCount);

    // Setup the floating window that will determine the sprites border.
    Rectangle window{animationFrame * SPRITE_WIDTH, 0, SPRITE_WIDTH,
                     SPRITE_HEIGHT};

    // Draw that sprite to the screen.
    DrawTextureRec(texture, window, locationOnScreen, WHITE);
  }
};
