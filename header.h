#ifndef HEADER_H
#define HEADER_H

// ============================================================
//  친구 추천 프로그램 - 그래프 자료구조 활용 (Qt GUI)
//
//   - 사람(Person)         = 그래프의 정점(Vertex / Node)
//   - 친구 관계(Friendship) = 그래프의 간선(Edge), 무방향(undirected)
//   - SocialGraph          = 인접 리스트(adjacency list) 기반 그래프
//   - GraphView            = 그래프를 화면에 그리는 위젯 (QWidget 상속)
//   - MainWindow           = 전체 GUI 메인 창 (QMainWindow 상속)
//
//   주요 그래프 알고리즘
//   - 친구 추천      : 친구의 친구(인접 리스트 2단계) 중, 함께 아는 친구가 많은 순
//   - BFS 최단 경로  : 두 사람이 몇 단계 건너 아는 사이인지 계산
// ============================================================

#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QPoint>
#include <QString>

#include <vector>
#include <string>
#include <utility>
#include <functional>

// Qt 이벤트 클래스 전방 선언 (포인터 인자만 쓰므로 선언만으로 충분)
class QPaintEvent;
class QMouseEvent;

// ------------------------------------------------------------
// 1) 정점(Vertex) 데이터 : 사람
// ------------------------------------------------------------
struct Person {
    std::string name;   // 이름
    double nx;          // 화면 표시용 x 좌표 (0.0 ~ 1.0 비율)
    double ny;          // 화면 표시용 y 좌표 (0.0 ~ 1.0 비율)
};

// ------------------------------------------------------------
// 2) 그래프 자료구조 : 인접 리스트(adjacency list)
// ------------------------------------------------------------
class SocialGraph {
public:
    SocialGraph() = default;

    void addPerson(const std::string& name, double nx, double ny);  // 정점 추가
    void addFriendship(int a, int b);                               // 간선 추가(무방향)

    int personCount() const;                            // 정점 개수
    const Person& person(int idx) const;                // 정점 조회
    int findPerson(const std::string& name) const;      // 이름으로 인덱스 찾기
    const std::vector<int>& friendsOf(int idx) const;   // 인접 리스트 조회
    bool areFriends(int a, int b) const;                // 직접 친구인지 확인

    // 친구 추천 : 친구의 친구 중 (아직 친구가 아닌 사람) → 함께 아는 친구 수로 정렬
    //   반환 : (사람 인덱스, 함께 아는 친구 수) 목록
    std::vector<std::pair<int, int>> recommend(int idx) const;

    // BFS 최단 경로 : a → b 까지 최소 단계 경로 (연결이 없으면 빈 벡터)
    std::vector<int> shortestPath(int a, int b) const;

private:
    std::vector<Person> people_;            // 정점 목록
    std::vector<std::vector<int>> adj_;     // 인접 리스트 (핵심 자료구조)
};

// ------------------------------------------------------------
// 3) 그래프 시각화 위젯 (QWidget 상속, 직접 그리기)
// ------------------------------------------------------------
class GraphView : public QWidget {
public:
    explicit GraphView(SocialGraph* graph, QWidget* parent = nullptr);

    // 사람(노드)을 클릭했을 때 호출되는 콜백 (MainWindow 가 등록)
    std::function<void(int)> onPersonClicked;

    void highlightFocus(int idx, const std::vector<int>& directFriends); // 선택한 사람 + 친구 강조
    void highlightPath(int idx, const std::vector<int>& path);           // 두 사람 연결 경로 강조
    void resetSelection();                                               // 선택 초기화

protected:
    void paintEvent(QPaintEvent* event) override;      // 그래프 그리기
    void mousePressEvent(QMouseEvent* event) override; // 클릭 처리

private:
    SocialGraph* graph_;
    int focus_ = -1;             // 선택한 사람
    int target_ = -1;            // 연결 경로의 상대방
    std::vector<int> friends_;   // focus 의 직접 친구 (target 없을 때 강조)
    std::vector<int> path_;      // focus → target 경로 (target 있을 때 강조)

    QPoint personPos(int idx) const;       // 비율좌표 → 실제 픽셀좌표
    int personAt(const QPoint& p) const;   // 클릭 위치 → 사람 인덱스
};

// ------------------------------------------------------------
// 4) 메인 창 (QMainWindow 상속) : 전체 GUI 구성
// ------------------------------------------------------------
class MainWindow : public QMainWindow {
public:
    MainWindow();

private:
    SocialGraph graph_;          // 그래프 자료구조 (데이터 보관)
    GraphView* view_ = nullptr;  // 그래프 화면
    QTextEdit* infoText_ = nullptr;
    QPushButton* resetButton_ = nullptr;

    int focus_ = -1;
    int target_ = -1;

    void setupGraphData();              // 고정 데이터 입력 (서버 대신 코드에 직접 입력)
    void handlePersonClicked(int idx);  // 사람 클릭 처리
    void showFocusInfo();               // 친구 목록 + 친구 추천 표시
    void showPathInfo();                // 두 사람 연결 경로 표시
    void reset();                       // 전체 초기화
};

#endif // HEADER_H
