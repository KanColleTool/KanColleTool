About this Folder
=================

There are three kinds of things in this folder:

1. JSON data straight from the API, like `ship.json`
1. Processed Translation Base files, like `ship-tlbase.json`
1. Translated versions of these files, like `ship-en.json`

Along with these, there's a script to make tlbase files (`maketrans.py`).

Translation of an endpoint is done by capturing a response from the API, removing the "svdata=" prefix from the data, saving it in a JSON file, running it through `maketrans.py`, copying the tlbase file it spits out to a file with a language suffix, and translating the contents.
