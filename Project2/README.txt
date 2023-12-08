------------------------------------
        HOW TO COMPILE AND RUN
------------------------------------
Compile: g++ -Wall -Werror -Wpedantic -std=c++17 *.cpp
Compile alternative: g++ *.cpp
run: ./a
------------------------------------
            DEPENDENCES
------------------------------------
Board.h, Candy.h, Candystore.h, Player.h, Utilities.h

Make sure everything is in the same folder so it is compilable

Required text files: candyList.txt, characters.txt, riddles.txt

candyList syntax:
name|description|price|candy_type|effect
there is no effect type because I merged candy type and effect type into one

characters syntax:
name|stamina|gold|candies

riddles syntax:
question|answer
-------------------------------------
        SUBMISSION INFORMATION
-------------------------------------
CSCI 1300 Fall 2023 Project 2
Author: Haeseo Jeong   - haje1510@colorado.edu
Recitation: 203 - Kyler Ruvane
Date: December 7th, 2023
-------------------------------------
        ABOUT THIS PROJECT
-------------------------------------
Candyland - 

A turn based game with hidden treasures, special tiles, and unique interactions. Win by making it  the end castle first.

Known differences -

I made it so that candy type and effect type are essentially just one group

I made drawing cards more like rolling a dice (like the actual game) rather than drawing cards from a set deck of cards (no board games really do this)

I made Gummy Candy a whole group rather than only gummy candy being able to effect turns. I also changed how Gummy Candy works in that it'll affect the player, not the tile
I found this to be more effective in usage and represents how the game should be played better

Github for this project: https://github.com/haejeg/CSCI1300/tree/main/Project2
