#!/usr/bin/env sh
<<<<<<< HEAD
set -e

./build/tools/caffe train \
  --solver=examples/mnist/lenet_consolidated_solver.prototxt $@
=======

./build/tools/caffe train \
  --solver=examples/mnist/lenet_consolidated_solver.prototxt
>>>>>>> caffe-yolo/master
