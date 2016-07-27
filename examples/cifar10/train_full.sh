#!/usr/bin/env sh
<<<<<<< HEAD
set -e
=======
>>>>>>> caffe-yolo/master

TOOLS=./build/tools

$TOOLS/caffe train \
<<<<<<< HEAD
    --solver=examples/cifar10/cifar10_full_solver.prototxt $@
=======
    --solver=examples/cifar10/cifar10_full_solver.prototxt
>>>>>>> caffe-yolo/master

# reduce learning rate by factor of 10
$TOOLS/caffe train \
    --solver=examples/cifar10/cifar10_full_solver_lr1.prototxt \
<<<<<<< HEAD
    --snapshot=examples/cifar10/cifar10_full_iter_60000.solverstate.h5 $@
=======
    --snapshot=examples/cifar10/cifar10_full_iter_60000.solverstate.h5
>>>>>>> caffe-yolo/master

# reduce learning rate by factor of 10
$TOOLS/caffe train \
    --solver=examples/cifar10/cifar10_full_solver_lr2.prototxt \
<<<<<<< HEAD
    --snapshot=examples/cifar10/cifar10_full_iter_65000.solverstate.h5 $@
=======
    --snapshot=examples/cifar10/cifar10_full_iter_65000.solverstate.h5
>>>>>>> caffe-yolo/master
