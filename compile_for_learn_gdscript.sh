#!/bin/bash

rm -rf ./bin

echo "Compiling linux editor"

scons p=x11 target=release_debug lto=full tools=yes
strip bin/godot.x11.opt.tools.64
chmod +x bin/godot.x11.opt.tools.64

echo "Compiling headless"

scons p=server target=release_debug lto=full tools=yes
strip bin/godot_server.x11.opt.tools.64
chmod +x bin/godot_server.x11.opt.tools.64

echo "Compiling linux release template"

scons p=x11 target=release optimize=speed disable_3d=true lto=full tools=no
strip bin/godot.x11.opt.64
chmod +x bin/godot.x11.opt.64

echo "Compiling windows release template"

scons p=windows target=release optimize=speed disable_3d=true lto=full tools=no bits=64
strip bin/godot.windows.opt.64.exe

echo "Compiling ARM64 OSX template"

scons p=osx osxcross_sdk=darwin24.4 target=release optimize=speed disable_3d=true tools=no arch=arm64
x86_64-apple-darwin24.4-strip -u -r bin/godot.osx.opt.arm64

echo "Compiling x86_64 OSX template"

scons p=osx osxcross_sdk=darwin24.4 target=release optimize=speed disable_3d=true tools=no arch=x86_64
x86_64-apple-darwin24.4-strip -u -r bin/godot.osx.opt.x86_64

echo "Combining into universal OSX template"

lipo -create bin/godot.osx.opt.arm64 bin/godot.osx.opt.x86_64 -output bin/godot.osx.opt.universal

echo "Building universal bundle"

cp -r misc/dist/osx_template.app bin/osx_template.app
mkdir -p bin/osx_template.app/Contents/MacOS
cp bin/godot.osx.opt.universal bin/osx_template.app/Contents/MacOS/godot_osx_release.64
cp bin/godot.osx.opt.universal bin/osx_template.app/Contents/MacOS/godot_osx_debug.64
chmod +x osx_template.app/Contents/MacOS/godot_osx*
zip -q -9 -r bin/osx_template.zip bin/osx_template.app

echo "Building web export"

scons p=javascript target=release optimize=speed disable_3d=true tools=no

echo "Packing result"

godot_version=$(python -c "import pathlib; ns={}; exec(pathlib.Path('version.py').read_text(), ns); print(f\"{ns['major']}.{ns['minor']}.{ns['patch']}\")")

zip -j /output/godot-learn.${godot_version}.templates.zip bin/osx_template.zip bin/godot.windows.opt.64.exe bin/godot.x11.opt.64 bin/godot.javascript.opt.zip
zip -j /output/godot-learn.${godot_version}.headless.zip bin/godot_server.x11.opt.tools.64
zip -j /output/godot-learn.${godot_version}.editor.zip bin/godot.x11.opt.tools.64

echo "Done compiling. Archived into /output"
