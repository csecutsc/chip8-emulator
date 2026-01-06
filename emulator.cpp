#include <iostream>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include <stack>

int main(int argc, char const *argv[]){
  short program_memory[4096]; // ROM
  bool display[64][32]; // 64 x 32 display
  int pc; // program counter register (PC)
  int ic; // index register (I)
  short registers[16]; // V0 - VF
  std::stack<short> st; // stack
  short delay_timer = 60;
  short sound_timer = 60;


  // open file
  if (argc >= 2){
    const char* filename = argv[1];
    std::cout << filename;

    char buffer[16] = {0};
    // read 16 bytes
    FILE *fptr = fopen(filename, "rb");
    while (fread(buffer, 16, 1, fptr) != 0){
      std::cout << "buffer contents: " << buffer << '\n';
    }
    fclose(fptr);
  }
  else{
    std::cout << "usage: ./emulator <rom_file>";
  }


//  bool window_opened = true;
//  IMGUI_CHECKVERSION();
//  ImGui::CreateContext();
//  ImGuiIO& io = ImGui::GetIO();
//  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//  ImGui::Begin("MY ImGUI App", &window_opened);
//  ImGui::End();
//

  return 0;
}
