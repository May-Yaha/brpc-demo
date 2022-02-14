CUR=`dirname "$0"`
CUR=`cd "$CUR"; pwd`

mkdir -p third_party/lib
mkdir -p third_party/include

pushd ${CUR}
git submodule update --init --recursive
popd

pushd ${CUR}/toft
git checkout master
popd
