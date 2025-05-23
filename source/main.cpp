#include <3ds.h>
#include <print>

int main() {
  gfxInitDefault();

  // Initialize console on top screen. Using NULL as the second argument tells
  // the console library to use the internal console structure as current one
  consoleInit(GFX_TOP, NULL);

  // Move the cursor to row 15 and column 19 and then prints "Hello World!"
  // To move the cursor you have to print "\x1b[r;cH", where r and c are
  // respectively the row and column where you want your cursor to move The top
  // screen has 30 rows and 50 columns The bottom screen has 30 rows and 40
  // columns
  std::println("\x1b[16;20HHello from C++");

  std::println("\x1b[30;16HPress Start to exit.");

  // Main loop
  while (aptMainLoop()) {
    // Scan all the inputs. This should be done once for each frame
    hidScanInput();

    // hidKeysDown returns information about which buttons have been just
    // pressed (and they weren't in the previous frame)
    u32 kDown = hidKeysDown();

    if (kDown & KEY_START)
      break; // break in order to return to hbmenu

    // Flush and swap framebuffers
    gfxFlushBuffers();
    gfxSwapBuffers();

    // Wait for VBlank
    gspWaitForVBlank();
  }

  gfxExit();
  return 0;
}
