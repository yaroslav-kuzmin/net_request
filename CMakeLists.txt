##############################################################################
#                                                                            #
# ideco : test task                                                          #
#                                                                            #
#  Copyright (C) 2021 Kuzmin Yaroslav <kuzmin.yaroslav@gmail.com>            #
#                                                                            #
# ideco is free software: you can redistribute it and/or modify it           #
# under the terms of the GNU General Public License as published by the      #
# Free Software Foundation, either version 3 of the License, or              #
# (at your option) any later version.                                        #
#                                                                            #
# ideco is distributed in the hope that it will be useful, but               #
# WITHOUT ANY WARRANTY; without even the implied warranty of                 #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       #
# See the GNU General Public License for more details.                       #
#                                                                            #
# You should have received a copy of the GNU General Public License along    #
# with this program.  If not, see <http://www.gnu.org/licenses/>.            #
#                                                                            #
##############################################################################

cmake_minimum_required(VERSION 3.14)

project(ideco VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        window.cpp
        window.h
        netrequest.cpp
        netrequest.h
)

qt_add_executable(ideco
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
)

set_target_properties(ideco PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(ideco PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Widgets
)

qt_finalize_executable(ideco)

