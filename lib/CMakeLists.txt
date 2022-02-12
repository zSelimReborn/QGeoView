set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

# Set the QT version
set(QT_VERSION 5)

find_package(Qt${QT_VERSION} REQUIRED COMPONENTS
             Core
             Gui
             Widgets
             Network
             Positioning
            )

# External lib for reading shapefiles
ExternalProject_Add(shapelib
        GIT_REPOSITORY https://github.com/OSGeo/shapelib.git
        BUILD_ALWAYS 1
        CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        TIMEOUT 360
        )
set(LIBSHAPELIB ${EXTERNAL_INSTALL_LOCATION}/lib/libshp.so)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIBSHAPELIB ${EXTERNAL_INSTALL_LOCATION}/lib/shp.lib)
    add_custom_command(
            TARGET shapelib
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${EXTERNAL_INSTALL_LOCATION}/bin/shp.dll
            ${CMAKE_BINARY_DIR}
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIBSHAPELIB ${EXTERNAL_INSTALL_LOCATION}/lib/libshp.dylib)
endif()
set(LIBSHAPELIB ${LIBSHAPELIB} PARENT_SCOPE)


qt5_add_resources (RCC_SOURCES resources.qrc)

add_library(qgeoview SHARED
    include/QGeoView/QGVGlobal.h
    include/QGeoView/QGVProjection.h
    include/QGeoView/QGVProjectionEPSG3857.h
    include/QGeoView/QGVCamera.h
    include/QGeoView/QGVMap.h
    include/QGeoView/QGVMapQGItem.h
    include/QGeoView/QGVMapQGView.h
    include/QGeoView/QGVMapRubberBand.h
    include/QGeoView/QGVItem.h
    include/QGeoView/QGVDrawItem.h
    include/QGeoView/QGVLayer.h
    include/QGeoView/QGVImage.h
    include/QGeoView/QGVLayerTiles.h
    include/QGeoView/QGVLayerTilesOnline.h
    include/QGeoView/QGVLayerGoogle.h
    include/QGeoView/QGVLayerBing.h
    include/QGeoView/QGVLayerOSM.h
    include/QGeoView/QGVWidget.h
    include/QGeoView/QGVWidgetCompass.h
    include/QGeoView/QGVWidgetScale.h
    include/QGeoView/QGVWidgetZoom.h
    include/QGeoView/QGVWidgetText.h
    include/QGeoView/QGVUtils.h
    include/QGeoView/QGVIcon.h
    include/QGeoView/QGVBallon.h
    include/QGeoView/QGVLine.h
    include/QGeoView/QGVWidgetMeasure.h
    include/QGeoView/QGVLayerFile.h
    include/QGeoView/QGVLayerGeoJson.h
    include/QGeoView/QGVLayerESRI.h
    include/QGeoView/QGVLayerShape.h
    include/QGeoView/QGVShapeIcon.h
    include/QGeoView/QGVShapePolygon.h
    include/QGeoView/QGVShapeLine.h
    src/QGVGlobal.cpp
    src/QGVProjection.cpp
    src/QGVProjectionEPSG3857.cpp
    src/QGVCamera.cpp
    src/QGVMap.cpp
    src/QGVMapQGItem.cpp
    src/QGVMapQGView.cpp
    src/QGVMapRubberBand.cpp
    src/QGVItem.cpp
    src/QGVDrawItem.cpp
    src/QGVLayer.cpp
    src/QGVImage.cpp
    src/QGVLayerTiles.cpp
    src/QGVLayerTilesOnline.cpp
    src/QGVLayerGoogle.cpp
    src/QGVLayerBing.cpp
    src/QGVLayerOSM.cpp
    src/QGVWidget.cpp
    src/QGVWidgetCompass.cpp
    src/QGVWidgetScale.cpp
    src/QGVWidgetZoom.cpp
    src/QGVWidgetText.cpp
    src/QGVUtils.cpp
    src/QGVIcon.cpp
    src/QGVBallon.cpp
    src/QGVLine.cpp
    src/QGVWidgetMeasure.cpp
    src/QGVLayerFile.cpp
    src/QGVLayerGeoJson.cpp
    src/QGVLayerESRI.cpp
    src/QGVLayerShape.cpp
    src/QGVShapeIcon.cpp
    src/QGVShapePolygon.cpp
    src/QGVShapeLine.cpp
    src/utils/DistanceUnits.cpp include/QGeoView/utils/DistanceUnits.hpp
    ${RCC_SOURCES}
    )

add_dependencies(qgeoview shapelib)

target_include_directories(qgeoview
    PUBLIC
        include
    PRIVATE
        include/QGeoView
)

target_compile_definitions(qgeoview
    PRIVATE
        QGV_EXPORT
)

target_link_libraries(qgeoview
        PRIVATE
        Qt${QT_VERSION}::Core
        Qt${QT_VERSION}::Gui
        Qt${QT_VERSION}::Widgets
        Qt${QT_VERSION}::Network
        Qt${QT_VERSION}::Positioning
        ${LIBSHAPELIB}
        )

add_library(QGeoView ALIAS qgeoview)

install(TARGETS qgeoview LIBRARY
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h*"
)
