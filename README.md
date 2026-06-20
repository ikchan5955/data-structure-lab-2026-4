# 친구 추천 프로그램 (Friend Recommendation)

그래프 자료구조를 활용한 클라이언트 사이드(UI) 프로그램입니다.
사람을 **정점(노드)**, 친구 관계를 **간선(엣지)** 으로 표현하여,
**친구 추천**과 **두 사람 사이의 인맥 거리(BFS 최단 경로)** 를 보여줍니다.

> 2026-1 데이터구조 최종 프로젝트 / Qt(C++) + 그래프 자료구조

---

## 1. 필수 조건 충족 여부

| 필수 조건 | 충족 |
|---|---|
| Qt 라이브러리를 활용한 GUI 프로그램 | O (QMainWindow, QWidget, QPainter 등) |
| 다루는 데이터가 그래프 자료구조로 저장 | O (인접 리스트 `adjacency list`) |
| C/C++ 로 구현 | O (C++17) |

서버는 구현하지 않고, 고정된 데이터를 코드에 직접 입력하여 사용합니다.

---

## 2. 데이터(그래프) 설계

- **정점(Vertex)** = 사람 → `struct Person { name, nx, ny }`
- **간선(Edge)** = 친구 관계 (무방향) → 인접 리스트 `std::vector<std::vector<int>> adj_`
- 사람 15명을 3개의 친구 그룹으로 구성하고, 그룹과 그룹은 소수의 "다리(bridge)" 간선으로 연결했습니다.

## 3. 주요 기능 / 그래프 알고리즘

1. **친구 목록 조회** — 인접 리스트 직접 조회 `friendsOf(idx)`
2. **친구 추천 (알 수도 있는 사람)** — 친구의 친구(인접 리스트 2단계) 중 아직 친구가 아닌 사람을, **함께 아는 친구 수**가 많은 순으로 정렬
3. **인맥 거리 찾기** — 두 사람 사이의 **BFS 최단 경로**로 몇 단계 건너 아는 사이인지 계산

## 4. 사용법

1. 왼쪽 그래프에서 **사람(원)을 클릭** → 그 사람의 친구 목록과 추천 친구가 오른쪽에 표시됩니다.
2. **다른 사람을 한 번 더 클릭** → 두 사람이 몇 단계 건너 아는 사이인지(최단 경로)를 보여줍니다.
3. **초기화** 버튼으로 다시 시작합니다.

---

## 5. 빌드 & 실행 방법

### 방법 A. 수업 웹 IDE (가장 간단)
`자료구조 실습실` 웹 페이지에 `main.cpp` 와 `header.h` 를 올리고 실행합니다.
환경이 단일 파일만 받는 경우 `FriendRecommend_single.cpp` 하나만 사용하세요.

### 방법 B. Qt Creator
`FriendRecommend.pro` 를 열고 빌드/실행(▶) 합니다.

### 방법 C. CMake (터미널)
```bash
cmake -S . -B build
cmake --build build
./build/FriendRecommend     # Windows: build\FriendRecommend.exe
```

### 방법 D. Visual Studio
Qt VS Tools 확장에서 `.pro` 또는 CMake 로 열어 빌드합니다.
한글이 깨지면 컴파일 옵션에 `/utf-8` 을 추가하세요. (CMake 에는 이미 포함됨)

> 참고: 노드 이름이 한글이므로 한글 폰트가 필요합니다(대부분의 환경에 기본 설치되어 있음).

---

## 6. 파일 구성

```
FriendRecommend/
├── README.md
├── header.h                    # 클래스 선언 (Person, SocialGraph, GraphView, MainWindow)
├── main.cpp                    # 구현 + main()
├── FriendRecommend_single.cpp  # (대체) 단일 파일 버전
├── CMakeLists.txt              # CMake 빌드 설정
└── FriendRecommend.pro         # qmake 빌드 설정
```
