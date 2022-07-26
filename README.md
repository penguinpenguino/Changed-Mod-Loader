Changed Mod Loader
=====
This is a DLL injector written for the game Changed ([Steam link](https://store.steampowered.com/app/814540/Changed/)) that loads all DLL files from the folder **mods**.

This also includes an example mod that opens up the console to view all input/output from the game.

Table of Contents
-----
1. [Installing](#isntalling)
2. [Uninstalling](#uninstalling)
3. [Writing Mods](#writing-mods)
4. [A Note About Antiviruses Flagging This](#a-note-about-antiviruses-flagging-this)

Installing
-----
1. Download the [latest release](https://github.com/penguinpenguino/Changed-Mod-Loader/releases/latest).
2. Move **ChangedLoader.exe** into your game directory.
3. Done! To play Changed with mods run **ChangedLoader.exe**, to play without mods run **Game.exe**.

To install other mods, create a folder called **mods** in your games directory, then drag any mod files into it.

Uninstalling
----
1. Delete **ChangedLoader.exe** and the **mods** folder.

Writing Mods
-----
**All mods MUST be 32-bit DLLs**. Changed is a 32-bit game so no 64-bit DLLs will work.
As of now, there is no custom API written for Changed, I am working on that now.

A Note About Antiviruses Flagging This
-----
This is a known issue with this program, and unfortunately, there is nothing I can do about it. I compile these programs using MinGW32 and have the  `--static` flag enabled so the program is portable. For some reason a lot of antivirus programs flag this, as described [here](https://stackoverflow.com/questions/62364507/compiled-c-executable-is-detected-as-a-virus-by-windows-defender), [here](https://stackoverflow.com/questions/64769420/antivirus-detecting-compiled-c-files-as-trojans), and [here](https://security.stackexchange.com/questions/229576/program-compiled-with-mingw32-is-reported-as-infected). Not only is this an issue, but because the program is a DLL injector, it will trigger more antiviruses.

If you want to see the VirusTotal result for version 1.0.1 of ChangedLoader.exe, you can view it [here](https://www.virustotal.com/gui/file/500c4e2af057aeca829751ceebf54d96ae4cdc842f1daef91f86da03978a9293).
