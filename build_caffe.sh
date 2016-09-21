#!/usr/bin/env bash
set -e

PROJECT_ROOT=/home/wencc/workplace/caffe
BUILD_DIR=${PROJECT_ROOT}/build
INSTALL_DIR=/home/wencc/caffe_linux


USE_OPENBLAS=${USE_OPENBLAS:-1}
if [ ${USE_OPENBLAS} -eq 1 ]; then
    BLAS=open
    export OpenBLAS_HOME="${INSTALL_DIR}"
else
    BLAS=eigen
    export EIGEN_HOME="${INSTALL_DIR}/eigen3"
fi

rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}"
cd ${BUILD_DIR}
# set ENV

export HDF5_ROOT=${INSTALL_DIR}
export OpenCV_DIR=${INSTALL_DIR}/share/OpenCV
export LMDB_DIR=${INSTALL_DIR}
cmake -DCMAKE_BUILD_TYPE=Release \
      -DADDITIONAL_FIND_PATH="${INSTALL_DIR}" \
      -DBUILD_python=OFF \
      -DBUILD_docs=OFF \
      -DCPU_ONLY=ON \
      -DUSE_LMDB=ON \
      -DUSE_LEVELDB=OFF \
      -DUSE_HDF5=OFF \
      -DBLAS=${BLAS} \
      -DBOOST_ROOT="${INSTALL_DIR}" \
      -DOpenCV_DIR="${INSTALL_DIR}" \
      -DPROTOBUF_PROTOC_EXECUTABLE="${INSTALL_DIR}/protobuf_host/bin/protoc" \
      -DPROTOBUF_INCLUDE_DIR="${INSTALL_DIR}/include" \
      -DPROTOBUF_LIBRARY="${INSTALL_DIR}/lib/libprotobuf.a" \
      ..

# compile params
make -j4
