all : 
	make -j 7 -C gtk/
	make -j 7 -C src/
	make -j 7 -C obj/

PHONY : clean

clean :
	rm obj/*.o obj/*.x *.x

ls :
	echo $(EXE)
