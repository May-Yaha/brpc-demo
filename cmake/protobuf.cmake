INCLUDE(ExternalProject)

SET(PROTOBUF_SOURCES_DIR ${THIRD_PARTY_PATH}/protobuf)
SET(PROTOBUF_INSTALL_DIR ${PROTOBUF_SOURCES_DIR}/output)
SET(PROTOBUF_INCLUDE_DIR "${PROTOBUF_INSTALL_DIR}/include" CACHE PATH "gflags include directory." FORCE)

ExternalProject_Add(
        extern_protobuf
        DOWNLOAD_DIR ${THIRD_PARTY_PATH}
        DOWNLOAD_COMMAND cp -r ${PROJECT_SOURCE_DIR}/third_party/protobuf-2.5.0.tar.gz ${THIRD_PARTY_PATH} && tar -zvxf protobuf-2.5.0.tar.gz && mv protobuf-2.5.0 protobuf
        CONFIGURE_COMMAND cd ${PROTOBUF_SOURCES_DIR} && ./autogen.sh && CXXFLAGS=-fPIC ./configure prefix=${PROTOBUF_INSTALL_DIR}
        BUILD_COMMAND cd ${PROTOBUF_SOURCES_DIR} && make -j 12
        INSTALL_COMMAND cd ${PROTOBUF_SOURCES_DIR} && make install && cp -r ${PROTOBUF_INSTALL_DIR}/lib ${THIRD_PARTY_PATH} && cp -r ${PROTOBUF_INSTALL_DIR}/include ${THIRD_PARTY_PATH} && cp ${PROTOBUF_INSTALL_DIR}/bin/protoc ${THIRD_PARTY_PATH}/lib
)
ADD_LIBRARY(protobuf STATIC IMPORTED GLOBAL)
SET_PROPERTY(TARGET protobuf PROPERTY IMPORTED_LOCATION ${PROTOBUF_INSTALL_DIR}/lib/libprotobuf.a)
ADD_DEPENDENCIES(protobuf extern_protobuf)

SET(Protobuf_PROTOC_EXECUTABLE "${PROTOBUF_INSTALL_DIR}/bin/protoc")
LIST(APPEND external_project_dependencies protobuf)
