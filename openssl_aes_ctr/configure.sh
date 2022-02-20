cmake \
    -DCMAKE_PREFIX_PATH=/Users/kevin.albertson/code/c-bootstrap/install/mongo-c-driver-master \
    -DCMAKE_BUILD_TYPE="Debug" \
    -DCMAKE_C_COMPILER_LAUNCHER="ccache" \
    -DCMAKE_C_FLAGS="-fsanitize=address" \
    -DOPENSSL_ROOT_DIR=/Users/kevin.albertson/bin/openssl-1.1.1g \
    -S./ \
    -B./cmake-build
