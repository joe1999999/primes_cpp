#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <unistd.h> // for usleep
#include <sstream>  // for std::ostringstream

int current_prime_num;
// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to calculate prime gaps up to a given limit
std::vector<int> calculatePrimeGaps(int limit) {
    std::vector<int> gaps;
    int prevPrime = 2;
    for (int i = 3; i <= limit; i++) {
        if (isPrime(i)) {
            current_prime_num = i;
            gaps.push_back(i - prevPrime);
            prevPrime = i;
        }
    }
    return gaps;
}

// Function to generate a unique RGB color for each gap value
unsigned long getColorForGap(int gap, std::map<int, unsigned long>& gapToColorMap) {
    if (gapToColorMap.find(gap) == gapToColorMap.end()) {
        // Generate a new color for this gap value
        static int colorIndex = 0;
        int r = (colorIndex * 50) % 256;
        int g = (colorIndex * 100) % 256;
        int b = (colorIndex * 150) % 256;
        gapToColorMap[gap] = (r << 16) | (g << 8) | b;
        colorIndex++;
    }
    return gapToColorMap[gap];
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }
    // X11 variables
    Display* display;
    Window window;
    XEvent event;
    GC gc;
    int screen;

    // Open connection to the X server
    display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Unable to open X display" << std::endl;
        return 1;
    }

    screen = DefaultScreen(display);

    // Create a window
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, 800, 600, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    // Set window title
    XStoreName(display, window, "Prime Gap Visualization");

    // Select input events
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Create a graphics context
    gc = XCreateGC(display, window, 0, nullptr);

    // Load a default font (e.g., "fixed")
    Font font = XLoadFont(display, "fixed");
    if (font == None) {
        std::cerr << "Unable to load font 'fixed'. Trying '6x13' instead." << std::endl;
        font = XLoadFont(display, "6x13");
        if (font == None) {
            std::cerr << "Unable to load font '6x13'. Exiting." << std::endl;
            XCloseDisplay(display);
            return 1;
        }
    }
    XSetFont(display, gc, font);

    // Map the window to the screen
    XMapWindow(display, window);

    // Calculate prime gaps
    int limit = atoi(argv[1]); // Upper limit for prime calculation
    std::vector<int> gaps = calculatePrimeGaps(limit);

    // Map to store gap values and their corresponding colors
    std::map<int, unsigned long> gapToColorMap;

    // Event loop
    bool running = true;
    size_t currentGapIndex = 0;
    while (running) {
        // Check for events
        while (XPending(display) > 0) {
            XNextEvent(display, &event);
            if (event.type == KeyPress) {
                running = false; // Exit on any key press
            }
        }

        // Update the background color and display the gap number
        if (currentGapIndex < gaps.size()) {
            int gap = gaps[currentGapIndex];
            // Get the color for this gap value
            unsigned long color = getColorForGap(gap, gapToColorMap);
            // Set the background color
            XSetForeground(display, gc, color);
            XFillRectangle(display, window, gc, 0, 0, 800, 600);

            // Display the gap number as text
            std::ostringstream oss;
            oss << "Gap: " << gap;
            std::string gapText = oss.str();
            // Set text color to black or white based on background brightness
            int brightness = ((color >> 16) & 0xFF) + ((color >> 8) & 0xFF) + (color & 0xFF);
            unsigned long textColor = (brightness > 384) ? BlackPixel(display, screen) : WhitePixel(display, screen);
            XSetForeground(display, gc, textColor);
            // Draw the text
            XDrawString(display, window, gc, 350, 300, gapText.c_str(), gapText.length());

            // Flush the display to ensure the changes are visible
            XFlush(display);
            // Move to the next gap
            currentGapIndex++;
        } else {
            // Reset to the first gap
            currentGapIndex = 0;
        }

        // Add a small delay to make the color changes visible
        usleep(200000); // 500ms delay
    }

    // Clean up
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}