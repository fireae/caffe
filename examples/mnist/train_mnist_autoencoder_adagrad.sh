#!/bin/bash
<<<<<<< HEAD
set -e

./build/tools/caffe train \
  --solver=examples/mnist/mnist_autoencoder_solver_adagrad.prototxt $@
=======

./build/tools/caffe train \
  --solver=examples/mnist/mnist_autoencoder_solver_adagrad.prototxt
>>>>>>> caffe-yolo/master
