#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "defines.h"

int game_is_running = FALSE;
SDL_Window* window = NULL; 
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct ball{
    float x;
    float y;
    float width;
    float height;
} ball;

int initialize_window(void){

    if(SDL_Init(SDL_INIT_EVERYTHING) != FALSE){
        fprintf(stderr, "Error at initialize_window");
        return FALSE;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,         //window in center
        SDL_WINDOWPOS_CENTERED,         //window in center
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if(!window){
        fprintf(stderr, "Error at SDL_CreateWindow");
        return FALSE;
    } //if window dont run return false
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        fprintf(stderr, "Error at SDL_CreateRenderer");
        return FALSE;
    } //if renderer dont run return false

    return TRUE; //if all runs, its true, so we can run the window
}

void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            game_is_running = FALSE;
            break;

        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            if(event.key.keysym.sym == SDLK_d)
                ball.x += 70;
            if(event.key.keysym.sym == SDLK_a)
                ball.x += -70;
            if(event.key.keysym.sym == SDLK_w)
                ball.y += -70;
            if(event.key.keysym.sym == SDLK_s)
                ball.y += 70;
            break;
    }
} //here we call the input, we do a switch to chose what key its pressed



void setup(){
    ball.x = 300;
    ball.y = 250;
    ball.width = 10;
    ball.height = 155;
}

void update(){
    //Time.deltaTime
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));

    float deltaTime = (SDL_GetTicks() - last_frame_time) / 1000.0f; 
    
    last_frame_time = SDL_GetTicks();

    //ball.x += 70 * deltaTime;
}

void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Draw rectangle
    SDL_Rect ball_rect = { 
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height
    };
   
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball_rect);

    SDL_RenderPresent(renderer);
}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void is_outside(int x, int y){
    if(x <= 0 || x >= WINDOW_WIDTH || y <= 0 || y >= WINDOW_HEIGHT){
        game_is_running = FALSE;
    }
} //check if the player its outside of the boundaries

int main(){
    game_is_running = initialize_window();
    
    setup();
    while(game_is_running){
        process_input();
        update();
        render();
        is_outside(ball.x, ball.y);
    }
    destroy_window();

    return TRUE;

}
