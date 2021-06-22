#!/bin/sh
rm -rf build
echo "Building for protium"
west build -b raptor2_protium samples/subsys/shell/shell_module/
#echo "Building for SoCFM"
#west build -b raptor2_socfm samples/subsys/shell/shell_module/
