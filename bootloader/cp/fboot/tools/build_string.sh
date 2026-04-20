echo "#ifndef BUILD_INFO_H" > ../include/build.h
echo "#define BUILD_INFO_H" >> ../include/build.h
echo "#define BUILD_STRING \"g-`git rev-parse --short HEAD`-`whoami`-`date "+%Y-%m-%d--%H:%M:%S"`\"" >> ../include/build.h
echo "#endif /* BUILD_INFO_H */" >> ../include/build.h
