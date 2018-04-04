#TODO check packages are installed using apt search "foo" | grep "foo" | wc -l
executeable="executeable"
if [[ "$1" == "-r" ]]
    then g++ main.cpp -Wall -o $executeable -lglut -lGL -lpthread && ./$executeable
    else g++ main.cpp -Wall -o $executeable -lglut -lGL -lpthread
fi
rm $executeable
