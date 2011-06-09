echo "[CUBE] Unit testing.";
echo "Please note that you should have compiled the original code successfully to run this script."

echo -n "Compiling distortion unit test ... ";
gcc ../obj/rand.o ../obj/zerog_module.o distortion.c -o dist
echo " [Done] ";
echo -n "Compiling random engine unit test ... ";
gcc ../obj/rand.o random.c -o rand
echo " [Done] ";
echo -n "Compiling hexdump unit test ... "
gcc ../obj/util.o hexdump.c -o hexdump 
echo " [Done] ";
