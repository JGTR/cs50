//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 70

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // initial velocity
    double xvelocity = 2.0;
    double yvelocity = 2.0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
      GEvent event = getNextEvent(MOUSE_EVENT);

      // if we heard one
      if (event != NULL)
      {
        // if the event was movement
        if (getEventType(event) == MOUSE_MOVED)
        {
          double width_paddle = getWidth(paddle);
          // ensure paddle follows top cursor
          double x = getX(event) - width_paddle / 2;
          setLocation(paddle, x, getY(paddle));
        }
      }

      // move ball along
      move(ball, xvelocity, yvelocity);

      // bounce off right edge of window
      if (getX(ball) + getWidth(ball) >= getWidth(window))
      {
          xvelocity = -xvelocity;
      }

      // bounce off left edge of window
      else if (getX(ball) <= 0)
      {
          xvelocity = -xvelocity;
      }

      if (getY(ball) >= getHeight(window))
      {
          lives--;
          pause(10);
          waitForClick();
          GOval ball = initBall(window);
          move(ball, xvelocity, yvelocity);
      }

      // bounce off left edge of window
      else if (getY(ball) <= 0)
      {
          yvelocity = -yvelocity;
      }

      // Bounce off the paddle

      GObject object = detectCollision(window, ball);
      if (object != NULL)
      {
        if (strcmp(getType(object), "GRect") == 0 && strcmp(getType(object), "GLabel") != 0)
        {
          yvelocity = -yvelocity;
          // remove brick
          // if (object == brick){
          //   removeGWindow(window, brick);
          // }
        }
      }

      // linger before moving again
      pause(10);

    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO

  double spacing = 5;
  double brickheight = HEIGHT/ ROWS / 5;
  double brickwidth = WIDTH / COLS;

  // Columns
  for(int x = 0; x < COLS; x++)
  {
    // rows
    for(int y = 0; y < ROWS; y++)
    {
    double xcoord = (x * brickwidth) + spacing;
    double ycoord = (y * brickheight) + spacing;

    GRect brick = newGRect(xcoord, ycoord, brickwidth, brickheight);
    
    if (x % 2 == 0)
    {
      setColor(brick, "GRAY"); // The color of the night

    }
    else
    {
      setColor(brick, "BLUE");
    }
    if (y % 2 == 0)
    {
      setFilled(brick, true);
    }
    add(window, brick);
    }
  }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval circle = newGOval(WIDTH/2, HEIGHT/2 - 100, 20, 20);
    setColor(circle, "RED");
    setFilled(circle, true);
    add(window, circle);
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // define X and Y coordinates for paddle
    double x = (WIDTH / 2) - PADDLE_WIDTH / 2;
    double y = HEIGHT - 30;

    GRect paddle = newGRect(x, y, PADDLE_WIDTH, PADDLE_HEIGHT);
    
    setColor(paddle, "BLACK"); // The color of the night
    setFilled(paddle, true);
    
    add(window, paddle);

    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
