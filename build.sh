#TODO check packages are installed using apt search "foo" | grep "foo" | wc -l

if [[ "$1" == "-d" ]]
    then cmake CMakeLists.txt && make
    else cmake CMakeLists.txt && make && ./cppSnake
fi

