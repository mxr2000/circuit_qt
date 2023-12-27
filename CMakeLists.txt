cmake_minimum_required(VERSION 3.20)
project(circuit2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(circuit2
        main.cpp

        items/CircuitItem.cpp
        items/CircuitItem.h
        items/Capacitor.cpp
        items/Capacitor.h
        items/Resistance.cpp
        items/Resistance.h
        items/Inductor.cpp
        items/Inductor.h
        items/Circuit.cpp
        items/Circuit.h
        items/Line.cpp
        items/Line.h
        items/Source.h
        items/VoltagePoint.h
        items/VoltagePoint.cpp

        views/CircuitView.cpp
        views/CircuitView.h
        views/ItemView.cpp
        views/ItemView.h
        views/LineView.cpp
        views/LineView.h
        views/LineItem.h
        views/VoltagePointView.cpp
        views/VoltagePointView.h

        strategies/Strategy.cpp
        strategies/Strategy.h

        widgets/CanvasWidget.cpp
        widgets/CanvasWidget.h
        widgets/MainWindow.h
        widgets/MainWindow.cpp

        dao/DocumentIO.cpp
        dao/DocumentIO.h

        dialogs/OpenDialog.cpp
        dialogs/OpenDialog.h
        dialogs/SaveDialog.cpp
        dialogs/SaveDialog.h

        utils/PositionUtil.cpp
        utils/PositionUtil.h
        utils/ResultCalculator.cpp
        utils/ResultCalculator.h
        )
target_link_libraries(circuit2
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

