echo "// Source for $1" > src/"$1.cpp"

echo "// Headers for $1" > src/"$1.h"

echo "// Test source for $1" > tests/"$1_test.cpp"

echo "// Test headers for $1" > tests/"$1_test.h"

echo "#include \"$1_test.h\"" >> ./tests/includes.h
echo "#include \"$1.h\"" >> ./src/includes.h
