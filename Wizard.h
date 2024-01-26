#pragma once
#include "Animation.h"
#include "Timer.h"

enum WizardState { ATTACKING, IDLE };

/**
 * An animated wizard that throws fire.
 */
struct Wizard {

  // The wizard has 2 animations that draw him to the screen, one for when
  // he is idle, and another when he is attacking.
  Animation *idleAnimation;
  Animation *attackAnimation;

  // We need a timer to tell us if we have been idle for 4 seconds.
  Timer idleTimer;

  // Every game object needs a location where it's drawn to the screen.
  Vector2 location;

  // We need some kind of state variable to tell us what we are doing.
  // in the case there are only two states (attacking and idle);
  WizardState state;

  Wizard() : idleTimer(4.0f), state(IDLE) {
    // Idle animation is 128px height and width, and should take 500 ms to
    // complete
    idleAnimation =
        new Animation("resources/Firewizard/Idle.png", 128.0f, 128.0f, 0.500f);

    // Attack animation is 128px height and width, and should take 1250 ms to
    // complete
    attackAnimation = new Animation("resources/Firewizard/Flame_jet.png",
                                    128.0f, 128.0f, 1.250f);
  }

  // We need a destructor to handle our resources.
  ~Wizard() {
    delete attackAnimation;
    delete idleAnimation;
  }

  // Don't allow copying.  (See the Animation class copy constructor for more
  // details)
  Wizard(Wizard &rhs) = delete;

  // Update the wizard to move ahead the amount of timeSinceLastFrameDrawn in
  // seconds.
  void update(float timeSinceLastFrameDrawn) {

    // If we are attacking, update the animation
    if (state == ATTACKING) {
      idleTimer.reset();
      attackAnimation->update(timeSinceLastFrameDrawn);
      if (attackAnimation->animationComplete()) {
        state = IDLE;
        attackAnimation->reset();
      }
    } else {
      // We are not currently attacking, handle user input.
      // importantly we don't allow the user to start another
      // attack if we are already attacking this way.
      if (IsKeyPressed(KEY_SPACE)) {
        // User started an attack, change state.
        state = ATTACKING;
        // Attacking someone means we aren't idle, so reset the idleTimer,
        // so that it counts down another 4 seconds from the start of the
        // attack.
        idleTimer.reset();
      }

      // If we just started an attack this is impossible, but if not
      // we need to see if it's been 4 seconds since we did anything.
      // if so, we are going to start the idle animation.
      if (idleTimer.isUp()) {
        // It's been 4 seconds since any user input, lets reset the timer and
        // start the animation.
        idleTimer.reset();
        idleAnimation->update(timeSinceLastFrameDrawn);
      } else if (idleAnimation->isActive()) {
        // If we were already doing the idle animation just advance it.
        idleAnimation->update(timeSinceLastFrameDrawn);
      }
    }
  }

  // Draw the Wizard to the screen.
  void draw() {

    // If we are attacking we need to draw the attack animation.
    // Notice that since we already handled updating the animation
    // in the update method we can literally just call "draw()" and
    // tell it where on the screen we are.
    if (state == ATTACKING) {
      attackAnimation->draw(location);
    } else {

      // If you aren't attacking, then your idle.  Again the animation
      // was already updated in update(), so we just draw it.
      idleAnimation->draw(location);
    }
  }
};
