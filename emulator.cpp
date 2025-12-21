#include <iostream>
#include "./include/imgui.h"
#include <stack>

int main(){
  short program_memory[4096]; // ROM
  bool display[64][32]; // 64 x 32 display
  int pc; // program counter register (PC)
  int ic; // index register (I)
  short registers[16]; // V0 - VF
  std::stack<short> st; // stack
  short delay_timer = 60;
  short sound_timer = 60;


  return 0;
}
