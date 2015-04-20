KanColleTool
============

[![Build Status](https://travis-ci.org/KanColleTool/KanColleTool.png?branch=master)](https://travis-ci.org/KanColleTool/KanColleTool)

KanColleTool is a tool for KanColle players.
That may have been the most redundant sentence I've ever written.

KanColleTool consists of two parts, the Tool (KCT) and the Viewer (KCTV). The Tool displays information gathered from the game, while the viewer is a wrapper around the game to let it and the Tool work more smoothly.

## Downloads

Downloads can be found on the official site: <http://kancolletool.github.io/>.

## Features

* On-the-fly translation of the game, by modifying server response text
* Viewing hidden statistics, such as Condition
* Notifications for quests, repairs and construction
* Optional spoilers for constructions

If you have a suggestion or bug report, please [open an issue](https://github.com/KanColleTool/KanColleTool/issues/new)!  
We're all open for code contributions in the form of Pull Requests as well - we're severely understaffed.

## Build
### On OS X
Install [Qt 5](http://www.qt.io/download/), and make sure the directory to QMake can be found from your `CMAKE_PREFIX_PATH`, i.e. add the following line to your `~/.bash_profile`
```
export CMAKE_PREFIX_PATH=~/<other_stuffs>
``` 
so that `~/<other_stuffs>/bin/qmake` is available. Usually usually you can find it under directory like `<QtInstallDir>/<Version>/clang_64`.

Make sure you have [Ruby Gems](https://rubygems.org/), so that you can install `pod`
```
sudo gem install cocoapods
```

Now find a directory you prefer (like `cd ~/src` or whatever) and 
```
git clone https://github.com/KanColleTool/KanColleTool/
cd KancolleTool
git submodule update --init --recursive
cmake .
make -j8
make install
```
And you should find `KCTViewer.app` and `KanColleTool.app` in `/usr/local`.

## Credits

- **uppfinnarn** - Lead Developer
- **Sauyon** - Developer
- **LynxyssCZ** - Debian Packager
- **Yukariin** - Arch Linux Packager, code contributions

---

This tool is entirely separate from @Grabacr07's [KanColleViewer](https://github.com/Grabacr07/KanColleViewer). I didn't even know of their project when I started mine, and all of my work has been separate from theirs.
