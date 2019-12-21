#include <vector>
#include <iostream>
#include "cxxopts.hpp"
#include "OpenAuraSDK.h"

int main(int argc, char *argv[])
{
  const char * desc =
    "Original project https://gitlab.com/CalcProgrammer1/OpenRGB\n\n"
    "  -m, --mode possible values:\n"
    "    0 -  OFF mode                             \n"
    "    1 -  Static color mode                    \n"
    "    2 -  Breathing effect mode                \n"
    "    3 -  Flashing effect mode                 \n"
    "    4 -  Spectrum Cycle mode                  \n"
    "    5 -  Rainbow effect mode                  \n"
    "    6 -  Rainbow Breathing effect mode        \n"
    "    7 -  Chase with Fade effect mode          \n"
    "    8 -  Chase with Fade - Rainbow effect mode\n"
    "    9 -  Chase effect mode                    \n"
    "    10 - Chase with Rainbow effect mode       \n"
    "    11 - Wave effect mode                     \n"
    "    12 - Chase with  Rainbow Pulse effect mode\n"
    "    13 - Random flicker effect mode           \n";

  int mode = 0;
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;

  cxxopts::Options options("openaura-cli", desc);
  options.add_options()
    ("h,help", "Print this help")
    ("l,list", "List controllers")
    ("m,mode", "RGB Effect mode [0-13]", cxxopts::value<int>(mode))
    ("r,red", "Red [0-255]", cxxopts::value<unsigned char>(r))
    ("g,green", "Green [0-255]", cxxopts::value<unsigned char>(g))
    ("b,blue", "Blue [0-255]", cxxopts::value<unsigned char>(b))
    ;

  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    return EXIT_SUCCESS;
  }

  DetectI2CBusses();
  DetectAuraControllers();

  auto controllers = GetControllers();

  for (int i = 0; i < controllers.size(); i += 1)
  {
    auto controller = controllers[i];

    if (result.count("list"))
    {
      std::cout << i << " " << controller->GetDeviceName() << std::endl;
    }

    if (result.count("mode"))
    {
      controller->SetMode(mode);
      controller->SetDirect(false);
    }

    if (result.count("r") || result.count("g") || result.count("b"))
    {
      controller->SetAllColorsEffect(r, g, b);
    }
  }

  return EXIT_SUCCESS;
}
