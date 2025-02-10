#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cmath>

// Function to draw text in a window
void drawText(Display* display, Window& window, GC& gc, int x, int y, const std::string& text) {
    XDrawString(display, window, gc, x, y, text.c_str(), text.length());
}

int main() {
    // Get user input for the number of numbers to display
    int totalNumbers;
    std::cout << "Enter the number of numbers to display (e.g., 100): ";
    std::cin >> totalNumbers;

    if (totalNumbers <= 0) {
        std::cerr << "Invalid input. Please enter a positive number.\n";
        return 1;
    }

    // Calculate the grid size (rows and columns)
    int gridSize = std::ceil(std::sqrt(totalNumbers));
    if (gridSize * gridSize < totalNumbers) {
        gridSize++; // Ensure the grid can fit all numbers
    }

    // Define square size and padding
    const int minSquareSize = 40; // Minimum size of each square
    const int padding = 15;      // Padding between squares
    int squareSize = minSquareSize;

    // Calculate window size based on grid size and square size
    int windowWidth = gridSize * (squareSize + padding) + padding;
    int windowHeight = gridSize * (squareSize + padding) + padding;

    // Open connection to the X server
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Unable to open X display\n";
        return 1;
    }

    // Get the default screen
    int screen = DefaultScreen(display);

    // Create a window
    Window window = XCreateSimpleWindow(
        display, RootWindow(display, screen),
        100, 100, windowWidth, windowHeight, 1,
        BlackPixel(display, screen), WhitePixel(display, screen)
    );

    // Set the window title
    XStoreName(display, window, "Dynamic Number Grid with X11");

    // Select events to listen to
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Map the window to the screen
    XMapWindow(display, window);

    // Create a graphics context for drawing
    GC gc = XCreateGC(display, window, 0, nullptr);

    // Set the foreground color to black
    XSetForeground(display, gc, BlackPixel(display, screen));

    // Define a color for the specific square (e.g., light blue)
    XColor lightBlue;
    Colormap colormap = DefaultColormap(display, screen);
    XAllocNamedColor(display, colormap, "lightblue", &lightBlue, &lightBlue);

    // Event loop
    XEvent event;
    bool running = true;
    while (running) {
        XNextEvent(display, &event);

        // Handle expose event (window needs to be redrawn)
        if (event.type == Expose) {
            int number = 2;

            for (int row = 0; row < gridSize; ++row) {
                for (int col = 0; col < gridSize; ++col) {
                    if (number > totalNumbers) {
                        break; // Stop drawing if all numbers are displayed
                    }

                    // Calculate the position of the square
                    int x = col * (squareSize + padding) + padding;
                    int y = row * (squareSize + padding) + padding;

                    // Check if this is the square we want to highlight (e.g., number 5)
                    if (number == 5) {
                        // Set the foreground color to light blue
                        XSetForeground(display, gc, lightBlue.pixel);
                        // Fill the square with light blue
                        XFillRectangle(display, window, gc, x, y, squareSize, squareSize);
                        // Reset the foreground color to black for the text
                        XSetForeground(display, gc, BlackPixel(display, screen));
                    } else {
                        // Draw the square outline
                        XDrawRectangle(display, window, gc, x, y, squareSize, squareSize);
                    }

                    // Draw the number inside the square
                    std::stringstream ss;
                    ss << number;
                    std::string numStr = ss.str();
                    int textX = x + (squareSize / 2) - (numStr.length() * 3);
                    int textY = y + (squareSize / 2) + 5;
                    drawText(display, window, gc, textX, textY, numStr);

                    // Increment the number
                    number++;
                }
            }
        }

        // Handle key press event (exit on any key press)
        if (event.type == KeyPress) {
            running = false;
        }
    }

    // Clean up
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}