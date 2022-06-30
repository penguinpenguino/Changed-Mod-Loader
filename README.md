Changed Mod Loader
=====
This is a DLL injector written for the game Changed ([Steam link](https://store.steampowered.com/app/814540/Changed/)) that loads all DLL files from the folder **mods**.

This also includes an example mod that opens up the console to view all input/output from the game.

Table of Contents
-----
1. [Installing](#isntalling)
2. [Uninstalling](#uninstalling)
3. [Writing Mods](#writing-mods)

Installing
-----
1. Install [7-zip](https://www.7-zip.org/).
2. Download the [latest release](https://github.com/penguinpenguino/Changed-Mod-Loader/releases/latest).
3. Open **ChangedLoader.7z** and extract **ChangedLoader.exe** into your game directory.
4. Done! To play Changed with mods run **ChangedLoader.exe**, to play without mods run **Game.exe**.
5. Optional: Extract the **mods** folder from ChangedLoader.7z into your game directory.

To install other mods, create a folder called **mods** in your games directory, then drag any mod files into it.

Uninstalling
----
1. Delete **ChangedLoader.exe** and the **mods** folder.

Writing Mods
-----
**All mods MUST be 32-bit DLLs**. Changed is a 32-bit game so no 64-bit DLLs will work.
As of now, there is no custom API written for Changed, I am working on that now.
