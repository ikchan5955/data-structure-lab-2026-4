// ============================================================
//  친구 추천 프로그램 - 그래프 자료구조 활용 (Qt GUI) [단일 파일 버전]
//
//  ※ 이 파일 하나만으로 빌드/실행이 가능합니다.
//    (header.h + main.cpp 분리 버전과 내용은 동일합니다.)
//
//   - 사람(Person)         = 그래프의 정점(Vertex / Node)
//   - 친구 관계(Friendship) = 그래프의 간선(Edge), 무방향
//   - SocialGraph          = 인접 리스트(adjacency list) 기반 그래프
//   - GraphView            = 그래프를 화면에 그리는 위젯 (QWidget 상속)
//   - MainWindow           = 전체 GUI 메인 창 (QMainWindow 상속)
// ============================================================

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QFont>
#include <QPoint>
#include <QString>

#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <queue>
#include <algorithm>
#include <set>

// ------------------------------------------------------------
// 1) 정점(Vertex) 데이터 : 사람
// ------------------------------------------------------------
struct Person {
    std::string name;
    double nx;
    double ny;
};

// ------------------------------------------------------------
// 2) 그래프 자료구조 : 인접 리스트
// ------------------------------------------------------------
class SocialGraph {
public:
    SocialGraph() = default;

    void addPerson(const std::string& name, double nx, double ny) {
        people_.push_back(Person{name, nx, ny});
        adj_.push_back(std::vector<int>{});
    }

    void addFriendship(int a, int b) {
        adj_[a].push_back(b);
        adj_[b].push_back(a);   // 무방향
    }

    int personCount() const { return static_cast<int>(people_.size()); }
    const Person& person(int idx) const { return people_[idx]; }

    int findPerson(const std::string& name) const {
        for (size_t i = 0; i < people_.size(); ++i)
            if (people_[i].name == name) return static_cast<int>(i);
        return -1;
    }

    const std::vector<int>& friendsOf(int idx) const { return adj_[idx]; }

    bool areFriends(int a, int b) const {
        for (int v : adj_[a]) if (v == b) return true;
        return false;
    }

    // 친구 추천 : 친구의 친구 중 함께 아는 친구 수로 정렬
    std::vector<std::pair<int, int>> recommend(int s) const {
        int n = personCount();
        std::vector<bool> exclude(n, false);
        exclude[s] = true;
        for (int f : adj_[s]) exclude[f] = true;

        std::vector<int> mutual(n, 0);
        for (int f : adj_[s])
            for (int g : adj_[f])
                if (!exclude[g]) mutual[g]++;

        std::vector<std::pair<int, int>> rec;
        for (int v = 0; v < n; ++v)
            if (mutual[v] > 0) rec.push_back(std::make_pair(v, mutual[v]));

        std::sort(rec.begin(), rec.end(),
            [](const std::pair<int, int>& x, const std::pair<int, int>& y) {
                if (x.second != y.second) return x.second > y.second;
                return x.first < y.first;
            });
        return rec;
    }

    // BFS 최단 경로
    std::vector<int> shortestPath(int s, int t) const {
        int n = personCount();
        std::vector<int> prev(n, -1);
        std::vector<bool> visited(n, false);
        std::queue<int> q;

        visited[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;
            for (int v : adj_[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    prev[v] = u;
                    q.push(v);
                }
            }
        }

        std::vector<int> path;
        if (!visited[t]) return path;
        for (int at = t; at != -1; at = prev[at]) path.push_back(at);
        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    std::vector<Person> people_;
    std::vector<std::vector<int>> adj_;   // 인접 리스트 (핵심 자료구조)
};

// ------------------------------------------------------------
// 3) 그래프 시각화 위젯
// ------------------------------------------------------------
class GraphView : public QWidget {
public:
    explicit GraphView(SocialGraph* graph, QWidget* parent = nullptr)
        : QWidget(parent), graph_(graph) {
        setMinimumSize(660, 560);
    }

    std::function<void(int)> onPersonClicked;

    void highlightFocus(int idx, const std::vector<int>& directFriends) {
        focus_ = idx; target_ = -1; friends_ = directFriends; path_.clear(); update();
    }
    void highlightPath(int idx, const std::vector<int>& path) {
        target_ = idx; path_ = path; update();
    }
    void resetSelection() {
        focus_ = -1; target_ = -1; friends_.clear(); path_.clear(); update();
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.fillRect(rect(), QColor("#1e1e2e"));

        std::set<std::pair<int, int>> hiEdges;
        if (target_ != -1) {
            for (size_t i = 0; i + 1 < path_.size(); ++i) {
                int a = path_[i], b = path_[i + 1];
                hiEdges.insert(std::make_pair(std::min(a, b), std::max(a, b)));
            }
        } else if (focus_ != -1) {
            for (int f : friends_)
                hiEdges.insert(std::make_pair(std::min(focus_, f), std::max(focus_, f)));
        }

        // (1) 간선(친구 관계)
        for (int u = 0; u < graph_->personCount(); ++u) {
            for (int v : graph_->friendsOf(u)) {
                if (u < v) {
                    QPoint pa = personPos(u);
                    QPoint pb = personPos(v);
                    std::pair<int, int> key(std::min(u, v), std::max(u, v));
                    if (hiEdges.count(key)) {
                        QPen rp(QColor("#f9e2af")); rp.setWidth(4); p.setPen(rp);
                    } else {
                        QPen ep(QColor("#45475a")); ep.setWidth(2); p.setPen(ep);
                    }
                    p.drawLine(pa, pb);
                }
            }
        }

        std::set<int> hiNodes;
        if (target_ != -1) {
            for (size_t i = 1; i + 1 < path_.size(); ++i) hiNodes.insert(path_[i]);
        } else if (focus_ != -1) {
            for (int f : friends_) hiNodes.insert(f);
        }

        // (2) 정점(사람)
        QFont font = p.font();
        font.setPointSize(9);
        font.setBold(true);
        p.setFont(font);

        for (int i = 0; i < graph_->personCount(); ++i) {
            QPoint c = personPos(i);
            QColor fill("#89b4fa");
            if (i == focus_)            fill = QColor("#a6e3a1");
            else if (i == target_)      fill = QColor("#f38ba8");
            else if (hiNodes.count(i))  fill = QColor("#f9e2af");

            p.setBrush(fill);
            p.setPen(QPen(QColor("#11111b"), 2));
            int r = 20;
            p.drawEllipse(c, r, r);

            p.setPen(QColor("#11111b"));
            p.drawText(QRect(c.x() - r, c.y() - r, 2 * r, 2 * r),
                       Qt::AlignCenter, QString::fromStdString(graph_->person(i).name));
        }
    }

    void mousePressEvent(QMouseEvent* e) override {
        int idx = personAt(e->pos());
        if (idx >= 0 && onPersonClicked) onPersonClicked(idx);
    }

private:
    SocialGraph* graph_;
    int focus_ = -1;
    int target_ = -1;
    std::vector<int> friends_;
    std::vector<int> path_;

    QPoint personPos(int idx) const {
        const Person& p = graph_->person(idx);
        int m = 50;
        int w = width()  - 2 * m;
        int h = height() - 2 * m;
        return QPoint(m + static_cast<int>(p.nx * w),
                      m + static_cast<int>(p.ny * h));
    }

    int personAt(const QPoint& pt) const {
        for (int i = 0; i < graph_->personCount(); ++i) {
            QPoint c = personPos(i);
            int dx = pt.x() - c.x();
            int dy = pt.y() - c.y();
            if (dx * dx + dy * dy <= 22 * 22) return i;
        }
        return -1;
    }
};

// ------------------------------------------------------------
// 4) 메인 창
// ------------------------------------------------------------
class MainWindow : public QMainWindow {
public:
    MainWindow() {
        setWindowTitle("친구 추천 — 그래프 자료구조");
        resize(1040, 640);

        setupGraphData();

        QWidget* central = new QWidget(this);
        setCentralWidget(central);
        QHBoxLayout* root = new QHBoxLayout(central);
        root->setContentsMargins(0, 0, 0, 0);
        root->setSpacing(0);

        view_ = new GraphView(&graph_, this);
        view_->onPersonClicked = [this](int idx) { handlePersonClicked(idx); };
        root->addWidget(view_, 1);

        QWidget* side = new QWidget(this);
        side->setFixedWidth(340);
        QVBoxLayout* sideLayout = new QVBoxLayout(side);
        sideLayout->setContentsMargins(16, 16, 16, 16);

        QLabel* title = new QLabel("친구 추천 & 인맥 찾기");
        title->setStyleSheet("font-size:18px; font-weight:bold; color:#cdd6f4;");
        sideLayout->addWidget(title);

        QLabel* hint = new QLabel(
            "사람(노드)을 클릭하세요.\n"
            "① 한 명 클릭 → 친구 목록 + 친구 추천\n"
            "② 다른 한 명 더 클릭 → 두 사람의 연결 경로");
        hint->setWordWrap(true);
        hint->setStyleSheet("color:#a6adc8; font-size:12px;");
        sideLayout->addWidget(hint);

        infoText_ = new QTextEdit(this);
        infoText_->setReadOnly(true);
        sideLayout->addWidget(infoText_, 1);

        resetButton_ = new QPushButton("초기화", this);
        sideLayout->addWidget(resetButton_);

        root->addWidget(side);

        connect(resetButton_, &QPushButton::clicked, this, [this]() { reset(); });

        setStyleSheet(
            "QMainWindow, QWidget { background:#181825; }"
            "QTextEdit { background:#1e1e2e; color:#cdd6f4; border:1px solid #313244;"
            "            border-radius:8px; padding:8px; font-size:13px; }"
            "QPushButton { background:#89b4fa; color:#11111b; border:none;"
            "              border-radius:8px; padding:10px; font-size:14px; font-weight:bold; }"
            "QPushButton:hover { background:#b4befe; }");

        reset();
    }

private:
    SocialGraph graph_;
    GraphView* view_ = nullptr;
    QTextEdit* infoText_ = nullptr;
    QPushButton* resetButton_ = nullptr;
    int focus_ = -1;
    int target_ = -1;

    void setupGraphData() {
        // 그룹 A
        graph_.addPerson("민준", 0.16, 0.22);
        graph_.addPerson("서연", 0.30, 0.13);
        graph_.addPerson("도윤", 0.10, 0.40);
        graph_.addPerson("지우", 0.27, 0.40);
        graph_.addPerson("하준", 0.40, 0.26);
        // 그룹 B
        graph_.addPerson("서윤", 0.62, 0.18);
        graph_.addPerson("예준", 0.76, 0.13);
        graph_.addPerson("하윤", 0.88, 0.30);
        graph_.addPerson("시우", 0.66, 0.40);
        graph_.addPerson("지유", 0.80, 0.44);
        // 그룹 C
        graph_.addPerson("주원", 0.38, 0.72);
        graph_.addPerson("채원", 0.26, 0.84);
        graph_.addPerson("지호", 0.52, 0.84);
        graph_.addPerson("수아", 0.44, 0.62);
        graph_.addPerson("은우", 0.62, 0.70);

        auto F = [&](const char* a, const char* b) {
            graph_.addFriendship(graph_.findPerson(a), graph_.findPerson(b));
        };
        F("민준", "서연"); F("민준", "도윤"); F("민준", "지우");
        F("서연", "하준"); F("서연", "지우"); F("도윤", "지우"); F("지우", "하준");
        F("서윤", "예준"); F("서윤", "시우"); F("서윤", "지유");
        F("예준", "하윤"); F("예준", "시우"); F("하윤", "지유"); F("시우", "지유");
        F("주원", "수아"); F("주원", "채원"); F("주원", "지호");
        F("수아", "지호"); F("채원", "지호"); F("지호", "은우"); F("수아", "은우");
        F("하준", "서윤");   // A ↔ B
        F("지유", "은우");   // B ↔ C
        F("민준", "주원");   // A ↔ C
    }

    void handlePersonClicked(int idx) {
        if (focus_ == -1) {
            focus_ = idx;
            view_->highlightFocus(idx, graph_.friendsOf(idx));
            showFocusInfo();
        } else if (target_ == -1) {
            if (idx == focus_) return;
            target_ = idx;
            std::vector<int> path = graph_.shortestPath(focus_, target_);
            view_->highlightPath(idx, path);
            showPathInfo();
        } else {
            reset();
            focus_ = idx;
            view_->highlightFocus(idx, graph_.friendsOf(idx));
            showFocusInfo();
        }
    }

    void showFocusInfo() {
        const Person& me = graph_.person(focus_);
        QString html = "<div style='color:#cdd6f4;'>";
        html += QString("<h3 style='color:#a6e3a1;'>%1 님</h3>")
                    .arg(QString::fromStdString(me.name));

        const std::vector<int>& fr = graph_.friendsOf(focus_);
        html += QString("<p><b>친구 %1명 (인접 노드):</b></p><p style='color:#f9e2af;'>")
                    .arg(static_cast<int>(fr.size()));
        for (size_t i = 0; i < fr.size(); ++i) {
            html += QString::fromStdString(graph_.person(fr[i]).name);
            if (i + 1 < fr.size()) html += ", ";
        }
        html += "</p>";

        std::vector<std::pair<int, int>> rec = graph_.recommend(focus_);
        html += "<p><b>알 수도 있는 사람 (친구의 친구):</b></p>";
        if (rec.empty()) {
            html += "<p>추천할 사람이 없습니다.</p>";
        } else {
            html += "<ol>";
            for (const std::pair<int, int>& r : rec) {
                html += QString("<li>%1 — 함께 아는 친구 %2명</li>")
                            .arg(QString::fromStdString(graph_.person(r.first).name))
                            .arg(r.second);
            }
            html += "</ol>";
        }
        html += "<p style='color:#94e2d5;'>다른 사람을 클릭하면 두 사람의 연결 경로를 찾습니다.</p>";
        html += "</div>";
        infoText_->setHtml(html);
    }

    void showPathInfo() {
        const Person& a = graph_.person(focus_);
        const Person& b = graph_.person(target_);
        std::vector<int> path = graph_.shortestPath(focus_, target_);

        QString html = "<div style='color:#cdd6f4;'>";
        html += QString("<h3>%1 ↔ %2</h3>")
                    .arg(QString::fromStdString(a.name))
                    .arg(QString::fromStdString(b.name));

        if (path.empty()) {
            html += "<p style='color:#f38ba8;'>두 사람은 서로 연결되어 있지 않습니다.</p>";
        } else if (graph_.areFriends(focus_, target_)) {
            html += "<p style='color:#a6e3a1;'>두 사람은 <b>이미 친구</b>입니다! (1단계)</p>";
            html += "<p style='color:#f9e2af;'>경로: ";
            for (size_t i = 0; i < path.size(); ++i) {
                html += QString::fromStdString(graph_.person(path[i]).name);
                if (i + 1 < path.size()) html += " → ";
            }
            html += "</p>";
        } else {
            int steps = static_cast<int>(path.size()) - 1;
            html += QString("<p><b>%1단계</b> 건너서 아는 사이입니다.</p>").arg(steps);
            html += "<p style='color:#f9e2af;'>최단 경로 (BFS): ";
            for (size_t i = 0; i < path.size(); ++i) {
                html += QString::fromStdString(graph_.person(path[i]).name);
                if (i + 1 < path.size()) html += " → ";
            }
            html += "</p>";
        }
        html += "<p style='color:#94e2d5;'>'초기화'를 누르거나 다른 사람을 클릭하면 다시 시작합니다.</p>";
        html += "</div>";
        infoText_->setHtml(html);
    }

    void reset() {
        focus_ = -1;
        target_ = -1;
        view_->resetSelection();
        infoText_->setHtml(
            "<div style='color:#a6adc8;'>"
            "<p>사람(노드)을 클릭해서 시작하세요.</p>"
            "<p>① 한 명 클릭 → 친구 목록과 '알 수도 있는 사람' 추천</p>"
            "<p>② 다른 한 명을 더 클릭 → 두 사람이 몇 단계 건너 아는 사이인지 (BFS 최단 경로)</p>"
            "</div>");
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
