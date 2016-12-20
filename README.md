#Delete Duplication Shell Script Maker
A de-duplication program searches through a set of directories, and removes files which are exactly identical to other files. For fear of deleting actual files, the program only prints a shell script which would remove the files if acutally run it.

e.g. ./dedup /usr/share/dict/words > rmShell.sh

It recursively iterates /usr/share/dict/words, detects duplicated files, then prints rm shell script and duplicated infomation into rmShell.sh
