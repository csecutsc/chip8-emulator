#include <iostream>
#include <random>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include <stack>


void clear_screen(){

}

int random_range(int lower, int upper){
  return lower + ( std::rand() % ( upper - lower + 1 ) )
}

int main(int argc, char const *argv[]){
  short program_memory[4096]; // ROM
  bool display[64][32]; // 64 x 32 display
  int pc; // program counter register (PC)
  int ic; // index register (I)
  short registers[16]; // V0 - VF
  std::stack<short> st; // stack - stack pointer is handled by this
  short delay_timer = 60;
  short sound_timer = 60;
  std::random_device rd;
  std::mt19937 gen(rd())


  // open file
  if (argc >= 2){
    const char* filename = argv[1];
    std::cout << filename;

    char buffer[4] = {0};
    // read 16 bytes
    FILE *fptr = fopen(filename, "rb");
    // convert the file buffer into a array
    vector<char*> instructions;
    while (fread(buffer, 4, 1, fptr) != 0){
      instructions.push_back(buffer);
    }
    while (pc < instructions.size());
      buffer = instructions[pc];
      // setup the cases
      if (buffer[0] == 0x0 && buffer[1] == 0x0 && buffer[2] == 0xe && buffer[3] == 0x0){
        clear_screen();
      }
      else if (buffer[0] == 0x0 && buffer[1] == 0x0 && buffer[2] == 0xe && buffer[3] == 0xe){
        pc = st.pop();
      }
      else if (buffer[0] == 0x1){
        pc = 256 * buffer[1] + 16 * buffer[2] + buffer[3];
      }
      else if (buffer[0] == 0x2){
        st.push(pc);
        pc = 256 * buffer[1] + 16 * buffer[2] + buffer[3];
      }
      else if (buffer[0] == 0x3){
        if (registers[buffer[1]] == 16*buffer[2]+buffer[3]){
          pc += 2;
        }
      }
      else if (buffer[0] == 0x4){
        if (registers[buffer[1]] != 16*buffer[2]+buffer[3]){
          pc += 2;
        }
      }
      else if (buffer[0] == 0x5 && buffer[3] == 0x0){
        if (registers[buffer[1]] == buffer[2]){
          pc += 2;
        }
      }
      else if (buffer[0] == 0x6){
        registers[buffer[1]] == 16*buffer[2]+buffer[3];
      }
      else if (buffer[0] == 0x7){
        registers[buffer[1]] += 16*buffer[2]+buffer[3];
      }
      else if (buffer[0] == 0x8 && buffer[3] == 0){
        registers[buffer[1]] = registers[buffer[2]];
      }
      else if (buffer[0] == 0x8 && buffer[3] == 1){
        registers[buffer[1]] = registers[buffer[1]] | registers[buffer[2]];
      }
      else if (buffer[0] == 0x8 && buffer[3] == 2){
        registers[buffer[1]] = registers[buffer[1]] & registers[buffer[2]];
      }
      else if (buffer[0] == 0x8 && buffer[3] == 3){
        registers[buffer[1]] = registers[buffer[1]] ^ registers[buffer[2]];
      }
      else if (buffer[0] == 0x8 && buffer[3] == 4){
        registers[buffer[1]] = registers[buffer[1]] + registers[buffer[2]];
        registers[0xf] = (registers[buffer[1]] + registers[buffer[2]] > 255);
      }
      else if (buffer[0] == 0x8 && buffer[3] == 5){
        registers[buffer[1]] = registers[buffer[1]] - registers[buffer[2]];
        registers[0xf] = (registers[buffer[1]] > registers[buffer[2]]);
      }
      else if (buffer[0] == 0x8 && buffer[3] == 6){
        registers[0xf] = (registers[buffer[1]] % 2 == 1);
        registers[buffer[1]] = registers[buffer[1]] >> 2;
      }
      else if (buffer[0] == 0x8 && buffer[3] == 7){
        bool greater = (registers[buffer[2]] > registers[buffer[1]]);
        registers[buffer[1]] = registers[buffer[1]] - registers[buffer[2]];
        registers[buffer[2]] = greater;
      }
      else if (buffer[0] == 0x8 && buffer[3] == 0xe){
        registers[buffer[1]] = registers[buffer[1]] << 1;
        registers[0xf] = (buffer[1] >= 128)
      }
      else if (buffer[0] == 0x9 && buffer[3] == 0x0){
        pc += 2*(registers[buffer[1]] != registers[buffer[2]]);
      }
      pc++;
      else if (buffer[0] == 0xa){
        ic = 256 * buffer[1] + 16 * buffer[2] + buffer[3];
      }
      else if (buffer[0] == 0xb){
        pc = 256 * buffer[1] + 16 * buffer[2] + buffer[3] + registers[0];
      }
      else if (buffer[0] == 0xd){
        int x_cord = buffer[1];
        int y_cord = buffer[2];
        int buffersize = buffer[3];
        for (int i = 0; i < buffersize; i++){
          if (x_cord >= 64){
            x_cord = 0;
            y_cord++;
          }
          if (display[y_cord][x_cord] != 0) registers[0xf] = 1;
          display[y_cord][x_cord] = memory[ic + i];
          x_cord++;
        }
      }
      else if (buffer[0] == 0xe && buffer[2] == 0x9 && buffer[3] == 0xe){
        // check keyboard
      }
      pc++;
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
