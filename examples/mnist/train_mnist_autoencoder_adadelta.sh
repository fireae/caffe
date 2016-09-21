#!/bin/bash
<<<<<<< HEAD
set -e

./build/tools/caffe train \
  --solver=examples/mnist/mnist_autoencoder_solver_adadelta.prototxt $@
=======

./build/tools/caffe train \
  --solver=examples/mnist/mnist_autoencoder_solver_adadelta.prototxt
>>>>>>> caffe-yolo/master
