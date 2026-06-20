cmake_minimum_required(VERSION 3.16)
project(FriendRecommend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)   # Q_OBJECT 를 쓰지 않아도 켜 두면 안전

# Qt6 우선, 없으면 Qt5 사용
find_package(Qt6 COMPONENTS Widgets QUIET)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Widgets)
endif()

# header.h + main.cpp 분리 버전을 빌드합니다.
add_executable(FriendRecommend main.cpp header.h)

# (단일 파일 버전으로 빌드하려면 위 줄을 지우고 아래 줄의 주석을 푸세요)
# add_executable(FriendRecommend FriendRecommend_single.cpp)

if (Qt6_FOUND)
    target_link_libraries(FriendRecommend PRIVATE Qt6::Widgets)
else()
    target_link_libraries(FriendRecommend PRIVATE Qt5::Widgets)
endif()

# MSVC(비주얼 스튜디오)에서 한글 깨짐 방지
if (MSVC)
    target_compile_options(FriendRecommend PRIVATE /utf-8)
endif()
