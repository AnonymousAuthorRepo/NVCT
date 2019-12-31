User can read "critcial_data_object.txt" from the result in [S2_select_data_obj](https://github.com/NVMCrashTester/EasyCrash/tree/master/S2_select_data_obj)

User need to modify application to persist critcial data objects in the end of each code region.
>A code region is either a first-level inner loopor a block of code between two adjacent, first-level inner loops.

After application modification, launching another set of crash and restart tests as describe in [S1_crash_and_restart_tests](https://github.com/NVMCrashTester/EasyCrash/tree/master/S1_crash_and_restart_tests) and collecting the recompute result.

Execute `python gether_code_region.py` to collect the code region information from second time crash and restart tests.
Execute `python knapsack.py` to run the algorithm for selecting the code regions. The input of the algoritm is XXX and the output is XXX.
