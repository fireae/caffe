#!/usr/bin/env sh
<<<<<<< HEAD
set -e

TOOLS=./build/tools

$TOOLS/caffe train --solver=examples/siamese/mnist_siamese_solver.prototxt $@
=======

TOOLS=./build/tools

$TOOLS/caffe train --solver=examples/siamese/mnist_siamese_solver.prototxt
>>>>>>> caffe-yolo/master
