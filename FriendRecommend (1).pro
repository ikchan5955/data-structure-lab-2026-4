QT += widgets
CONFIG += c++17

# header.h + main.cpp 분리 버전
SOURCES += main.cpp
HEADERS += header.h

# 단일 파일 버전으로 빌드하려면 위 두 줄 대신 아래 줄을 사용하세요.
# SOURCES += FriendRecommend_single.cpp

TARGET = FriendRecommend
