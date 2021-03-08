read -p "Confirm [Y]? " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]
then
  rm -rf "src/$1.cpp" "src/$1.h" "tests/$1_test.cpp" "tests/$1_test.h"
  echo "Done."
fi

