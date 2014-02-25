all:
	cd tool && qmake && make
	cd viewer && qmake && make
