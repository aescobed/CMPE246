#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

const int WIDTH = 40;  // Width of the screen
const int HEIGHT = 20; // Height of the screen
const int FPS = 15;    // Frames per second
const float GRAVITY = 0.5f; // Gravity constant

void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear screen and reset cursor
}

void draw(const std::vector<std::vector<char>>& screen) {
    for (const auto& row : screen) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

int main() {
    // Ball's position and velocity
    float ballX = WIDTH / 2;
    float ballY = HEIGHT / 2;
    float velocityX = 1.0f;
    float velocityY = 0.0f;

    // Screen buffer
    std::vector<std::vector<char>> screen(HEIGHT, std::vector<char>(WIDTH, ' '));

    while (true) {
        // Clear the screen buffer
        for (auto& row : screen) {
            std::fill(row.begin(), row.end(), ' ');
        }

        // Update ball position
        ballX += velocityX;
        ballY += velocityY;

        // Apply gravity
        velocityY += GRAVITY;

        // Check for collisions with walls
        if (ballX <= 0 || ballX >= WIDTH - 1) {
            velocityX *= -1;
        }
        if (ballY >= HEIGHT - 1) {
            ballY = HEIGHT - 1;
            velocityY *= -0.8f; // Reverse and reduce velocity on bounce
        }
        if (ballY <= 0) {
            ballY = 0;
            velocityY *= -1;
        }

        // Place the ball on the screen buffer
        if (ballY >= 0 && ballY < HEIGHT && ballX >= 0 && ballX < WIDTH) {
            screen[static_cast<int>(ballY)][static_cast<int>(ballX)] = 'O';
        }

        // Clear terminal and draw the screen
        clearScreen();
        draw(screen);

        // Pause to control the frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
    }

    return 0;
}
