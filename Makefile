all:
	[ -e tool/Makefile ] || qmake -o tool/Makefile tool/KanColleTool.pro
	cd tool && make
	[ -e viewer/Makefile ] || qmake -o viewer/Makefile viewer/KCTViewer.pro
	cd viewer && make
