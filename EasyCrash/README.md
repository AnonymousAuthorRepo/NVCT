# EasyCrash

EasyCrash is a framework to decide how to persist data object in Non-Volatile Main Memory and improve system efficiency. 
The workflow of EasyCrash include four steps: 
1. crash and restart tests
2. select critical data object
3. select code region to persist critical data objects
4. implement EasyCrasb in application.

To implement EasyCrash in an application without recomputation characteristic analysis, user need to trigger a number of crashes by using [NVCT](https://github.com/NVMCrashTester/NVCT). The details of each step can be found in folder :) 
