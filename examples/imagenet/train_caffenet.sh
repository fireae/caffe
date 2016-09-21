#!/usr/bin/env sh
<<<<<<< HEAD
set -e

./build/tools/caffe train \
    --solver=models/bvlc_reference_caffenet/solver.prototxt $@
=======

./build/tools/caffe train \
    --solver=models/bvlc_reference_caffenet/solver.prototxt
>>>>>>> caffe-yolo/master
