#include <raylib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define DARKPINK (Color){145, 65, 100, 255}
#define RAYCREAM (Color){255, 248, 230, 255}                                              #define pink (Color){255, 205, 225, 255}

int main() {
        InitWindow(1920, 1080, "A Proposal letter");
        SetTargetFPS(120);

        Rectangle button1 = {600, 450, 320, 100};
        Rectangle button2 = {1000, 450, 320, 100};

        bool rejection = false;
        bool letter = false;
        bool start = false;

        while(!WindowShouldClose()) {

                Vector2 mouse = GetMousePosition();
                bool hovering_button1 = CheckCollisionPointRec(mouse, button1);
                bool hovering_button2 = CheckCollisionPointRec(mouse, button2);

                bool input_triggered = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsGestu>

                if(input_triggered) {
                        if(!start && hovering_button2) {
                                start = true;
                                rejection = true;
                        }
                        if(!start && hovering_button1) {
                                start = true;
                                letter = true;
                                if(letter) {
                                        if(fork() == 0) {
                                                execlp("firefox", "firefox", "https://m.y>
                                                exit(1);
                                        }
                                }
                                letter = false;
                        }

                }
                BeginDrawing();
                ClearBackground(RAYCREAM);
                if(!start) {
                        DrawText("there is something i want to tell you", 500, 250, 38, D>
                        Color pink2 = hovering_button2 ? (Color){255, 145, 190, 255} : (C>
                        Color pink1 = hovering_button1 ? (Color){255, 145, 190, 255} : (C>
                        DrawRectangleRounded(button2, 0.5f, 12, pink2);
                        DrawRectangleRounded(button1, 0.5f, 12, pink1);
                        DrawText("Yes!", 735, 487, 25, WHITE);
                        DrawText("Nop", 1135, 487, 25, WHITE);
                }
                if (start && rejection) {
                        DrawText("Okay then...... :(", 800, 520, 35, DARKPINK);
                }
                else if (start) {
                        DrawText("Here it is!", 850, 520, 40, DARKPINK);
                }
                EndDrawing();
        }
        CloseWindow();
        return 0;
}
