#include <ctime>
#include <filesystem>
#include <iostream>
#include <stdio.h>

#include "easy_cl.hpp"
#include "structs.h"

using namespace std;

const int MAX_GAMESETS = 13243;

void print_unreachable(bool *reachable, FILE *file) {
  for (int i = 0; i < 900; i++) {
    if (!reachable[i]) {
      fprintf(file, "%d ", i + 100);
    }
  }
  fprintf(file, "\n");
}

int main(int argc, char *argv[]) {

  bool verbose;
  if (argc > 1 && strcmp(argv[1], "1") == 0)
    verbose = true;
  else
    verbose = false;

  EasyCL ecl(verbose);

  string path = filesystem::current_path();
  vector<string> source_files{"kernel.cl"};
  vector<string> kernel_names{"batch_calc_reachable"};

  ecl.load_kernels(source_files, kernel_names,
                   " -I \"" + path + "\" -D MAX_QUEUE_SIZE=400");

  FILE *in_file = fopen("../25_50_75_100.res", "r");
  FILE *out_file = fopen("25_50_75_100_unreachable.res", "w");

  // Setup data
  SynchronisedArray<GameSet_t> gamesets(ecl.context, CL_MEM_READ_ONLY,
                                        {MAX_GAMESETS});
  SynchronisedArray<Reachable_t> reachable_arrs(ecl.context, CL_MEM_WRITE_ONLY,
                                                {MAX_GAMESETS});

  int a, b, c, d, e, f;
  for (int i = 0; i < MAX_GAMESETS; i++) {
    fscanf(in_file, "%d %d %d %d %d %d\n", &a, &b, &c, &d, &e, &f);
    gamesets[i][0] = a;
    gamesets[i][1] = b;
    gamesets[i][2] = c;
    gamesets[i][3] = d;
    gamesets[i][4] = e;
    gamesets[i][5] = f;
    // if (i<3)
    //     cout << a << ", "
    //          << b << ", "
    //          << c << ", "
    //          << d << ", "
    //          << e << ", "
    //          << f << "\n";
  }

  // Run kernel
  ecl.apply_kernel("batch_calc_reachable", gamesets, reachable_arrs);

  // Output result
  for (int i = 0; i < MAX_GAMESETS; i++) {
    print_unreachable(reachable_arrs[i], out_file);
  }

  return 0;
}
