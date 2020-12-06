/******************************************************************************
*
*  ACADEMIC INTEGRITY DECLARATION
*
*   I, George Graham Boots declare that except where I have referenced,
*  the work I am are submitting in this attachment is my own work. I
*  acknowledge and agree that the assessor of this assignment may,
*  for the purpose of authenticating this assignment, reproduce it
*  for the purpose of detecting plagiarism. I have read and am aware
*  of the Think Education Policy and Procedure viewable online at
*  http://www.think.edu.au/studying-at-think/policies-and-procedures/
*
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Snake.h"
#include "Fruit.h"
#include "Border.h"
#include "textpixels_enums.h"
#include "textpixels.h"

using namespace std;
using namespace textpixels;

// enumaration of screens
enum Screen
{
  MENU = 1, //main menu
  PLAY, //runs game
  PAUSE, //Pause screen to explain game/ break for player
  GAMEOVER, //ends PLAY, return to MENU
  EXIT, //cancel program
  NONE //not set
}; //Collection of screens

// Game functions
void drawLevelAndGui(int playerScore);
int displayMenuScreen();
int playGame();
void drawPauseScreen();

// global vars
const int LEVEL_WIDTH = 35;
const int LEVEL_HEIGHT = 20;
const int GUI_HEIGHT = 10;
int setDifficulty = 0;
bool teleportSnake = false;
bool easterEgg = false;


// Main ---------------------------------------------/
int main()
{
  textpixels::setupWindow( LEVEL_WIDTH, LEVEL_HEIGHT+GUI_HEIGHT, 20, 20 ); //DRAWS Screen

  int screen = Screen::MENU; //Start
 
  int seed = time(NULL);
  srand(seed);

  // Main game loop
  while (screen != Screen::EXIT)
  {
    if (screen == Screen::MENU)
    {
      screen = displayMenuScreen();
    }
    else if (screen == Screen::PLAY)
    {
      playGame();
      screen = Screen::MENU;      
    }
    else if (screen == Screen::PAUSE)
    {
      drawPauseScreen();
      screen = Screen::MENU;
    }
  }
  return (0);
}

// Random Function
int randInRange(int rangeMax)
{
    int ranged = (rand() % rangeMax) + 1;
    return ranged;
}

void drawLevelAndGui(int playerScore) 
{
  if (teleportSnake == false) 
  {
      fillWindow(FG_GREY);
  }
  else if (teleportSnake == true)
  {
      fillWindow(FG_DARK_GREY);
  }
  fillRect(1, 1, LEVEL_WIDTH - 2, LEVEL_HEIGHT - 2, FG_BLACK);
  fillRect(0, LEVEL_HEIGHT, LEVEL_WIDTH, GUI_HEIGHT, FG_BLACK);

  drawString(2, LEVEL_HEIGHT + 1, "(Q) ", FG_WHITE);
  drawString(2, LEVEL_HEIGHT + 3, "(P) ", FG_WHITE);
  drawString(6, LEVEL_HEIGHT + 1, "Quit", FG_GREY);
  drawString(6, LEVEL_HEIGHT + 3, "Pause", FG_GREY);
  drawString(2, LEVEL_HEIGHT + 5, "FPS: ", FG_GREY);
  drawString(7, LEVEL_HEIGHT + 5, textpixels::getFpsString(), FG_YELLOW);

  drawString(20, LEVEL_HEIGHT + 1, "Score: ", FG_GREEN);
  drawString(27, LEVEL_HEIGHT + 1, to_string(playerScore), FG_GREEN);
  //drawString(20, LEVEL_HEIGHT + 2, "Lives: ", FG_WHITE); attempt after completeing main functionality of game
  //drawString(27, LEVEL_HEIGHT + 2, totalLives, FG_RED);
}

// Draws pause Screen to console whenever run
void drawPauseScreen()
{
    bool endPauseGUI = false;
    textpixels::startFrame();
    do
    {
        fillRect(1, 1, 33, 18, BG_BLACK);
        drawString(3, 2, "Game Instructions: ", FG_WHITE);
        drawString(17, 4, "[W] - Upwards");
        drawString(17, 6, "[S] - Downwards");
        drawString(17, 8, "[A] - Left");
        drawString(17, 10, "[D] - Right");

        drawString(3, 4, " ", BG_YELLOW);
        drawString(5, 4, "- Banana");
        drawString(7, 5, "(3pts)");
        drawString(3, 7, " ",BG_RED);
        drawString(5, 7, "- Apple");
        drawString(3, 9, " ", BG_BLUE);
        drawString(5, 9, "- Berry");
        drawString(7, 10, "(1pts)");
        drawString(9, 13, "--- GameOver ---");
        drawWCharacter(5, 15, '??', layerColours(FG_GREEN, BG_MAGENTA));
        drawString(7, 15, "- Poison");
        drawString(19, 15, " ", BG_GREY);
        drawString(21, 15, "- Wall");
       

        drawString(8, 18, "Press (R) to return", FG_WHITE);
        if (keyIsDown('R'))
        {
            break;
        }
        textpixels::endFrame();
    } while (endPauseGUI != true);
}

// Draw PoisonGUI when player hits poison
void drawPoisonFruitGUI()
{
    bool endPoisonGUI = false;
    textpixels::startFrame();
    do
    {
        fillRect(1, 1, 33, 18, BG_BLACK);
        drawString(6, 5, " You drank some Poison ", layerColours(FG_DARK_GREEN, BG_DARK_MAGENTA));
        drawWCharacter(4, 5, '??', layerColours(FG_DARK_GREEN, BG_DARK_MAGENTA));
        drawWCharacter(30, 5, '??', layerColours(FG_DARK_GREEN, BG_DARK_MAGENTA));
        drawString(10, 9, "Press (Q)uit", FG_WHITE);
        drawString(10, 11, "Press (R)eplay", FG_WHITE);
        if (keyIsDown('Q'))
        {
            endPoisonGUI = true;
        }
        if (keyIsDown('R'))
        {
            playGame();
        }
        textpixels::endFrame();
    } while (endPoisonGUI != true);
}

// Draw borderGUI whenever players hits border location
void drawBorderCollisionGUI()
{
    bool endBorderGUI = false;
    textpixels::startFrame();
    do
    {
        fillRect(1, 1, 33, 18, BG_BLACK);
        drawString(7, 5, "  You hit the wall   ", layerColours(FG_WHITE, BG_RED));
        drawString(10, 9, "Press (Q)uit", FG_WHITE);
        drawString(10, 11, "Press (R)eplay", FG_WHITE); 
        

      if (keyIsDown('Q'))
      {
        endBorderGUI = true;
      }
      if (keyIsDown('R'))
      {
        playGame();
      }
      textpixels::endFrame();
    } while (endBorderGUI != true);

}

// Menu for game ---------------------------------------------/
int displayMenuScreen()
{
    textpixels::setFps(60);
    int choice = Screen::NONE;
    
    do// Keeps looping, waiting for input
    {
        textpixels::startFrame();   // Needed always at start of game loop
        fillWindow(FG_BLACK);
        drawString(10, 1, "Monty the Python", layerColours(FG_WHITE, BG_DARK_BLUE));
        drawString(3, 4, "Select Mode:", layerColours(FG_WHITE, BG_BLACK));
        drawString(3, 6, "(1) Normal", layerColours(FG_WHITE, BG_BLACK));
        drawString(3, 8, "(2) Veteran", layerColours(FG_WHITE, BG_BLACK));
        drawString(3, 10, "(3) No Walls", layerColours(FG_WHITE, BG_BLACK));
        drawString(3, 18, "(X) Exit", layerColours(FG_WHITE, BG_DARK_GREY));
        drawString(3, 15, "(I) Instructions", FG_WHITE);
        drawString(3, 13, "(E) EasterEgg", FG_WHITE);

        if (keyIsDown('1'))
        {
            setDifficulty = 8;
            teleportSnake = false;
            easterEgg = false;
            choice = Screen::PLAY;
        }
        else if (keyIsDown('2'))
        {
            setDifficulty = 4; 
            teleportSnake = false;
            easterEgg = false;
            choice = Screen::PLAY;
        }
        else if (keyIsDown('3'))
        {
            setDifficulty = 8;
            teleportSnake = true;
            easterEgg = false;
            choice = Screen::PLAY;
        }
        else if (keyIsDown('I'))
        {
            choice = Screen::PAUSE;
        }
        else if (keyIsDown('X'))
        {
            choice = Screen::EXIT;
        }
        else if (keyIsDown('E'))
        {
            setDifficulty = 8;
            easterEgg = true;
            choice = Screen::PLAY;
            
        }
        
        textpixels::endFrame();     // Needed always at end of game loop.
    } while (choice == Screen::NONE);     // Only stop when playerHasQuit
    
    return(choice);
}

// Play Game ------------------------------------------------------/
int playGame()
{
    Snake monty;
    monty.colour = FG_RED;
    monty.location.x = 16;
    monty.location.y = 9;

    textpixels::setFps(100); //Changes FPS outputed to screen
    const int moveEveryNFrames = setDifficulty; //Normal = 10, Hard = 4

    int score = 0;
    bool playerHasQuit = false;
  
    monty.xSpeed = Direction::RIGHT;
    monty.ySpeed = Direction::NONE;
    int moveCountdown = moveEveryNFrames;  // Initialise the live countdown from a constant

    Border upperBorder;
    upperBorder.location.x = 0;
    upperBorder.location.y = 0;

    Border lowerBorder;
    lowerBorder.location.x = 34;
    lowerBorder.location.y = 19;
  
    // Create fruit
    vector<Fruit> fruitCollection;
    vector<Snake> snakeSegments;
    
  
    Fruit apple; //FruitCollection 1
    apple.colour = FG_RED;
    apple.location.x = randInRange(18);
    apple.location.y = randInRange(18);
    fruitCollection.push_back(apple);

    Fruit blueberry; //fruitCollection 2
    blueberry.colour = FG_BLUE;
    blueberry.location.x = randInRange(18);
    blueberry.location.y = randInRange(18);
    fruitCollection.push_back(blueberry);

    Fruit banana; //fruitCollection 3
    banana.colour = FG_YELLOW;
    banana.location.x = randInRange(18);
    banana.location.y = randInRange(18);
    fruitCollection.push_back(banana);
    
    Fruit poison;
    poison.colour = textpixels::layerColours(FG_DARK_GREEN, BG_DARK_MAGENTA);
    poison.symbol = '??';
    poison.location.x = randInRange(18);
    poison.location.y = randInRange(18);
    
  
    
  // Main game loop
    do
    {
        textpixels::startFrame();// Let textpixels know we're doing stuff in this frame
        int montyGrowth = 1;
        

    if (keyIsDown('Q'))
    {
        playerHasQuit = true; 
        break;  // End the DO loop now, go to the line after it ends (return score?)
    }
    if (keyIsDown('P'))
    {
        drawPauseScreen();
    }

    Snake montyPast;
    montyPast.location.y = monty.location.y;
    montyPast.location.x = monty.location.x;
    snakeSegments.push_back(montyPast);

    // controls for snake
    Direction xDirectionInput = textpixels::getLeftRightInput();
    Direction yDirectionInput = textpixels::getUpDownInput();

    if (xDirectionInput != Direction::NONE)
    {
    // Change our snake speed to match the direction that was entered
    monty.xSpeed = xDirectionInput;
    monty.ySpeed = Direction::NONE;
    }
    else if (yDirectionInput != Direction::NONE)
    {
    monty.ySpeed = yDirectionInput;
    monty.xSpeed = Direction::NONE;
    }

        moveCountdown -= 1;
        if (moveCountdown <= 0)  
        {
            monty.location.x += monty.xSpeed;
            monty.location.y += monty.ySpeed;
            moveCountdown = moveEveryNFrames;

            // ensures that poison is not hidden behind fruit
            // 
        if (poison.location.isEqualTo(fruitCollection[0, 1, 2].location))
        {
            poison.location.x = randInRange(18);
            poison.location.y = randInRange(18);
        }
        // Checks Montys position with Fruit
        //
        if (monty.location.isEqualTo(fruitCollection[0].location))
        {
            score = score + 1;
            montyGrowth = montyGrowth + 1;
            fruitCollection[0].location.x = randInRange(18);
            fruitCollection[0].location.y = randInRange(18);
            poison.location.x = randInRange(18);
            poison.location.y = randInRange(18);
            drawPixel(fruitCollection[0].location.x, fruitCollection[0].location.y, fruitCollection[0].colour);
        }
        else if (monty.location.isEqualTo(fruitCollection[1].location))
        {
            score = score + 1;
            montyGrowth++;
            fruitCollection[1].location.x = randInRange(18);
            fruitCollection[1].location.y = randInRange(18);
            poison.location.x = randInRange(18);
            poison.location.y = randInRange(18);
            drawPixel(fruitCollection[1].location.x, fruitCollection[1].location.y, fruitCollection[1].colour);
        }
        else if (monty.location.isEqualTo(fruitCollection[2].location))
        {
            score = score + 3;
            montyGrowth = montyGrowth + 1;
            fruitCollection[2].location.x = randInRange(18);
            fruitCollection[2].location.y = randInRange(18);
            poison.location.x = randInRange(18);
            poison.location.y = randInRange(18);
            drawPixel(fruitCollection[2].location.x, fruitCollection[2].location.y, fruitCollection[2].colour);
        }

        if (monty.location.isEqualTo(poison.location))
        {
            drawPoisonFruitGUI();
            playerHasQuit = true;
        }

        // Checks Players position against border
        // to be moved into function
        if (teleportSnake == false) 
        {
            // cannot combine as isEqualTo, x and y coordinates need to be separate
            if (monty.location.x == upperBorder.location.x || monty.location.y == upperBorder.location.y)
            {
                drawBorderCollisionGUI();
                playerHasQuit = true;
            }
            else if (monty.location.x == lowerBorder.location.x || monty.location.y == lowerBorder.location.y)
            {
                drawBorderCollisionGUI();
                playerHasQuit = true;
            }
        }
        else if (teleportSnake == true)
        {
            if (monty.location.x == upperBorder.location.x)
            {
                monty.location.x = lowerBorder.location.x - 1;
            }
            else if (monty.location.y == upperBorder.location.y)
            {
                monty.location.y = lowerBorder.location.y - 1;
            }
            else if (monty.location.x == lowerBorder.location.x)
            {
                monty.location.x = upperBorder.location.x + 1;
            }
            else if (monty.location.y == lowerBorder.location.y)
            {
                monty.location.y = upperBorder.location.y + 1;
            }
        }

        drawLevelAndGui(score); //draws location of objects, onto screen
        drawPixel(monty.location.x, monty.location.y, monty.colour);
        drawPixel(montyPast.location.x, montyPast.location.y, monty.colour);
       
        if (easterEgg != false)
        {
            for (int i = 0; i < snakeSegments.size(); i++)
            {
                drawPixel(snakeSegments[i].location.x, snakeSegments[i].location.y, FG_DARK_MAGENTA);

            }
        }

        drawWCharacter(poison.location.x, poison.location.y, poison.symbol, poison.colour);

        for (auto apple : fruitCollection)
        {
            drawPixel(fruitCollection[0].location.x, fruitCollection[0].location.y, fruitCollection[0].colour); //apple
            drawPixel(fruitCollection[1].location.x, fruitCollection[1].location.y, fruitCollection[1].colour); //blueberry
            drawPixel(fruitCollection[2].location.x, fruitCollection[2].location.y, fruitCollection[2].colour); //banana
        }
    }
    textpixels::endFrame();  
  } while (!playerHasQuit);    
  
  return score;
}