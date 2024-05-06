
# Program Dependence Graph and Partitioning into SECURE AND NOT SECURE

The program dependence graph consists of 2 parts : Data dependencies and Control Dependencies.

We generate data dependence graph (custom made pass) and control flow graph(llvm pass) for each function and eventually a callgraph(llvm pass).

Finally we build a custom made pass named partition_pass, which creates a map for the callgraph and traverses(BFS) it to find the variables and functions annotated as "secure" and then marks the called functions by them or the functions which use the "secure" annotated variables as "secure" and the rest as "not secure" and prints them to the console.


## DEPENDENCIES

### INSTALLING LLVM

>$ sudo apt-get update

>$ sudo apt-get install clang llvm

Manual annotations for secure variables and functions using:

>$ __attribute__((section("secure_var"))) <type> <varname>;

>$ __attribute__((section("secure"))) <type> <function1>(){}

##  Program Dependence Graph (FUNCTION LEVEL)

We have an input.cpp file as the input which contains different functions. Convert the .cpp file to .ll file using the following command:

> clang -S -emit-llvm enable-new-pm=0 -o input.ll input.cpp

### DATA DEPENDENCY GRAPH GENERATION FROM CUSTOM MADE PASS(.CPP-->.SO-->.LL-->.DOT-->.PNG)

> clang -shared -o PDG.so PDG.cpp `llvm-config --cxxflags --ldflags --libs` -fPIC

> opt --enable-new-pm=0 -load ./PDG.so -pdg <input.ll> PDG.ll 

**note: (PDG - NAME OF PASS) (.so file takes input.ll as input to generate .ll file and the associated .dot files for each function).

> dot -Tpng [NAME OF DOT FILE].dot -o [NAME OF THE OUTPUT FILE].png


### CONTROL FLOW GRAPH GENERATION (Using llvm pass)(.LL--->.DOT--->.PNG)

> opt -dot-cfg -disable-output -enable-new-pm=0 input.ll

**note : It generates 9 .dot files

> dot -Tpng -o cfgN.png ._Z9functionNv.dot

**note: the input.cpp file contains 8 functions and a main function, Hence the cfg for each function has been generated, Replace 'N' by the function number [1-8] to generate the same.

> gimp cfgN.png

**note: instead of gimp, we can also use xdg-open or others to open the image or directly through the gui.


### CALL GRAPH GENERATION (Using llvm pass)(.LL--->.DOT--->.PNG)

> opt -dot-callgraph -disable-output -enable-new-pm=0 input.ll

> dot -Tpng -o callgraph.png input.ll.callgraph.dot

> gimp callgraph.png 

**note: instead of gimp, we can also use xdg-open or others to open the image or directly through the gui.


### OPTIONAL : You can also create a postdominated tree

>opt --enable-new-pm=0 -view-postdom input.ll

**note: This will create all the dot files, save them and convert them to png by methods mentioned above.
## Partitioning

### SECURE/ NOT SECURE PARTITION

>clang++ -shared -o partition_pass.so partition_pass.o `llvm-config --ldflags --libs` -fPIC

>opt -load ./partition_pass.so -call-graph --enable-new-pm=0 <input.ll> /dev/null

//secure and non-secure partitions with function id (numbers) will be printed to console.



## Screenshots

![image](https://github.com/ArcXzost/llvm-secure-partitioning/assets/96982138/242e7dce-426b-4ace-9d70-76681bd9ae5c)


## Authors

- [@Ashutoshpandey](https://github.com/Ashutoshpandey29)
- [@VasuPandey](https://github.com/Ashutoshpandey29)
- [@LohitMajumder](https://github.com/Vasupandey85)


## References

1. Shen Liu, Gang Tan, and Trent Jaeger. 2017. PtrSplit: Supporting General Pointers in Automatic Program Partitioning. In Proceedings of the 2017 ACM SIGSAC Conference on Computer and Communications Security (CCS '17). Association for Computing Machinery, New York, NY, USA, 2359–2371.
- [Refer to the paper](https://doi.org/10.1145/3133956.3134066)
 
2. Jeanne Ferrante, Karl J. Ottenstein, Joe D. Warren. The Program Dependence Graph and Its Use in Optimization, ACM Transactions on Programming Languages and SystemsVolume 9, Issue 3.
- [Refer to the paper](https://dl.acm.org/doi/10.1145/24039.24041)

3. LLVM PASSES(Legacy Version):
- [Refer to the website](https://llvm.org/docs/WritingAnLLVMPass.html)
