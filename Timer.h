#pragma once
#include <raylib.h>

/**
 * This is a timer class that will help us determine when an interval of time
 * has passed.
 */
struct Timer {

  // The time the timer was started.
  double startTime;

  // How long should this timer run for
  double interval;

  // We only need to set the interval when we create the timer because
  // we can set the start time at creation.  If we need to reset the
  // start time later we can always just call reset();
  Timer(float interval) : interval(interval) { reset(); }

  // Reset the start time to the current time.
  void reset() { startTime = GetTime(); }

  // This will tell you if the timer is up.
  bool isUp() { return ((GetTime() - startTime) > interval); }
};
