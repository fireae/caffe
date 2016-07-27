#!/usr/bin/env sh
<<<<<<< HEAD
set -e

./build/tools/caffe train \
    --solver=examples/mnist/lenet_solver_rmsprop.prototxt $@
=======

./build/tools/caffe train --solver=examples/mnist/lenet_solver_rmsprop.prototxt
>>>>>>> caffe-yolo/master
