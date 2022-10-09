// AdverserialProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define HEIGHT 800
#define WIDTH 600

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>
#include "Network.h"

#include "Layer.h"

void QuitApp(SDL_Window* window, SDL_Renderer* renderer);
void Draw(SDL_Renderer* renderer);
void Wait(std::chrono::milliseconds amount);

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        //No init
        return 1;
    };
    //Pointer til viduet
    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderTarget = nullptr;
    //Lager window
    mWindow = SDL_CreateWindow("Machine Learning", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, SDL_WINDOW_SHOWN);
    mRenderTarget = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mWindow == NULL) {
        //Get fucked
        QuitApp(mWindow, mRenderTarget);
        return 0;
    }
    SDL_Event ev;
    srand((unsigned int)time(0));
    //Les pgn 
    std::ifstream carlsenGamesFile("");
    //std::vector<Chess> carlsenGames;
    if (carlsenGamesFile.is_open()) {
        //Chess game;
        //For each move found, game.DoMove(from, to)
    }
    //
    //for(int i = 0; i < carlsenGames.size(); i++){
    //  input = carlsenGames[i].GetBoardWeights/Values();
    //  
    // //Go trough network
    //}
    //The weight for each piece is the input, 0 is empty piece, positive is white, negative is black
    std::vector<float> chessBoard;
    //Dette prosjektet blir nå sjakk?
    //Create some input to feed the layers
    std::vector<float> input;
    for (int i = 0; i < 3; i++) {
        input.push_back((rand() % 100) / 100);
        std::cout << (rand() % 100) / 100.f << std::endl;
    }
    std::cout << "Created inputs" << std::endl;
    //Create Layers
    std::vector<Layer*> mLayers;
    //Use the size of input as the size of the first in nodes
    mLayers.push_back(new Layer(input.size(), 5));
    mLayers.push_back(new Layer(5, 3));
    for (int i = 0; i < mLayers.size(); i++) {
        mLayers[i]->PopulateWithRandomness();
    }
    Network net(mLayers);
    
    
    //The out of this layer = the input of the next layer
    //for (int i = 0; i < mLayers.size(); i++) {
    //    input = mLayers[i]->Output(input);
    //    std::cout << "Got output from layer : " + i << std::endl;
    //}
    //Input is now the output of the last layer
    //Replaced by
    input = net.Output(input);
    //Prints the output of the net
    for (int i = 0; i < input.size(); i++) {
        std::cout << "Input : " + static_cast<int16_t>(i) << " : " << input[i] << std::endl;
    }

    //Write network to file
    net.WriteToFile("chessNetwork");
    bool bIsRunning = true;
    while (bIsRunning) {
        //Henter event som skjer
        while (SDL_PollEvent(&ev) != 0) {
            //Hvis det er av type KEYDOWn
            if (ev.type == SDL_KEYDOWN) {
                //Switch som g�r p� symbolet som ble trykker
                switch (ev.key.keysym.sym) {
                    //Hvis det er escape
                case SDLK_ESCAPE:
                    bIsRunning = false;
                    QuitApp(mWindow, mRenderTarget);

                    break;
                case SDLK_RIGHT:
                    //Next step?
                    break;
                }
            }
        }

        Draw(mRenderTarget);
    }
    return 0;
}

void QuitApp(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    exit(1);
}

void Draw(SDL_Renderer* renderer)
{
    // We clear what we draw before
    SDL_RenderClear(renderer);
    // Set our color for the draw functions
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // Now we can draw our point
    //for (size_t i = 0; i < entities.size(); i++)
    //{
    //    //Set color to entites color
    //    SDL_SetRenderDrawColor(renderer, entities[i]->r, entities[i]->g, entities[i]->b, 0xFF);
    //    //Draw point with color at entity posistion
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX, entities[i]->mY);
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX + 1, entities[i]->mY);
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX - 1, entities[i]->mY);
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX + 1, entities[i]->mY - 1);
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX - 1, entities[i]->mY + 1);
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX + 1, entities[i]->mY + 1);
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX - 1, entities[i]->mY - 1);
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX, entities[i]->mY + 1);
    //    SDL_RenderDrawPoint(renderer, entities[i]->mX, entities[i]->mY - 1);
    //}

    // Set the color to what was before
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    // .. you could do some other drawing here
    // And now we present everything we draw after the clear.
    SDL_RenderPresent(renderer);
}

void Wait(std::chrono::milliseconds amount)
{
    std::this_thread::sleep_until(std::chrono::system_clock::now() + amount);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
