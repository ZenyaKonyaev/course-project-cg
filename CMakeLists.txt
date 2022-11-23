cmake_minimum_required(VERSION 3.19)
project(OpenGlTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenGlTest main.cpp StuffObj/Model/ModelObj.h StuffObj/Model/ModelObj.cpp
        StuffObj/Parser/ParserObj.cpp StuffObj/Parser/ParserObj.h Camera/Camera.cpp Figures/BaseFigure.cpp
        Figures/BaseFigure.h Figures/SquareFigure.cpp Figures/SquareFigure.h Scene/Scene.cpp Scene/Scene.h
        Drawer/Drawer.cpp Drawer/Drawer.h Figures/PyramidFigure.cpp Figures/PyramidFigure.h
        Convertor/ModelObjConvertor.cpp Convertor/ModelObjConvertor.h Figures/GeneralFigure.cpp
        Figures/GeneralFigure.h BmpParser/BmpParser.h BmpParser/BmpParser.cpp MapGenerator/BaseMapGenerator.h
        MapGenerator/BaseMapGenerator.cpp Figures/TerrainFigure.cpp Figures/TerrainFigure.h)
target_link_libraries(OpenGlTest -lOpenGL32 -lfreeGLUT)

