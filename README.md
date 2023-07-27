This repository implements two types of datastructures for the advanced datastructures course at KIT.
One is a y-fast-trie for predecessor queries, the other one a range minimum query datastructure utilising cartesian trees.

To compile simply run the build.sh script (or just the one line contained in it) and an application called "ads_programm" should be created. (But it will throw a warning!)
This application can then be used with "ads_programm [pd|rmq] input_file output_file".
The data format is decribed in https://algo2.iti.kit.edu/download/kurpicz/2023_advanced_data_structures/project.pdf.

For memory measurements malloc_count https://github.com/bingmann/malloc_count is used. The rights lay by the original author.

Requires GCC with C++ 11 or newer!
Tested with Ubuntu 22.04.2 LTS.
