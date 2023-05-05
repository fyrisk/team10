#include "boardwidget.h"



/*类静态数据成员定义*/
const QSize BoardWidget::WIDGET_SIZE(430, 430);
const QSize BoardWidget::CELL_SIZE(25, 25);
const QPoint BoardWidget::START_POS(40, 40);
const QPoint BoardWidget::ROW_NUM_START(15, 45);
const QPoint BoardWidget::CLU_NUM_START(39, 25);
const int BoardWidget::NO_PIECE;
const int BoardWidget::WHITE_PIECE;
const int BoardWidget::BLACK_PIECE;
const bool BoardWidget::WHITE_PLAYER;
const bool BoardWidget::BLACK_PLAYER;

BoardWidget::BoardWidget(int boardSize,QWidget *parent) :
    QWidget(parent),
    visited(15, QVector<bool>(15, false)),
    trackPos(28, 28)
{
    setWindowTitle("NoGo");
    //设置棋盘大小
    BOARD_WIDTH = boardSize;
    BOARD_HEIGHT = boardSize;
    setFixedSize(WIDGET_SIZE);
    setMouseTracking(true);

    //修改倒计时时间按钮
    QPushButton *ChangeTimeButton = new QPushButton("Change Time", this);
    ChangeTimeButton -> setGeometry(QRect(340, 50, 90, 30));
    connect(ChangeTimeButton, &QPushButton::clicked, this, &BoardWidget::onChangeTimeButtonClicked);

    //设置投降按钮
    QPushButton *giveUpButton = new QPushButton("Give up", this);
    giveUpButton->setGeometry(QRect(340, 80, 90, 30));
    connect(giveUpButton, &QPushButton::clicked, this, &BoardWidget::onGiveUpButtonClicked);

    // 白方步数
    whiteStepLabel = new QLabel("白方：0步", this);
    whiteStepLabel->setGeometry(QRect(330, 130, 100, 20));
    whiteStepLabel->setAlignment(Qt::AlignHCenter);

    // 黑方步数
    blackStepLabel = new QLabel("黑方：0步", this);
    blackStepLabel->setGeometry(QRect(330, 160, 100, 20));
    blackStepLabel->setAlignment(Qt::AlignHCenter);

    // 总步数
    totalStepLabel = new QLabel("总步数：0步", this);
    totalStepLabel->setGeometry(QRect(330, 190, 100, 20));
    totalStepLabel->setAlignment(Qt::AlignHCenter);

    //初始化计时器和棋盘
    initTime();//initBoard用到了initTime初始化的timer指针，二者顺序不可交换
    initBoard();
}



void BoardWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::lightGray); //背景颜色

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        painter.drawText(CLU_NUM_START + QPoint(i * CELL_SIZE.width(), 0),
                         QString::number(i + 1));
    }
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        painter.drawText(ROW_NUM_START + QPoint(0, i * CELL_SIZE.height()),
                         QString::number(i + 1));
    }

    for (int i = 0; i < BOARD_WIDTH - 1; i++) //绘制棋盘格子
    {
        for (int j = 0; j < BOARD_HEIGHT - 1; j++)
        {
            painter.drawRect(QRect(START_POS + QPoint(i * CELL_SIZE.width(), j * CELL_SIZE.height()),
                                   CELL_SIZE));
        }
    }

    painter.setPen(Qt::red);
    QPoint poses[12] = {
        trackPos + QPoint(0, 8),
        trackPos,
        trackPos + QPoint(8, 0),
        trackPos + QPoint(17, 0),
        trackPos + QPoint(25, 0),
        trackPos + QPoint(25, 8),
        trackPos + QPoint(25, 17),
        trackPos + QPoint(25, 25),
        trackPos + QPoint(17, 25),
        trackPos + QPoint(8, 25),
        trackPos + QPoint(0, 25),
        trackPos + QPoint(0, 17)
    };
    painter.drawPolyline(poses, 3);
    painter.drawPolyline(poses + 3, 3);
    painter.drawPolyline(poses + 6, 3);
    painter.drawPolyline(poses + 9, 3);

    painter.setPen(Qt::NoPen);
    for (int i = 0; i < BOARD_WIDTH; i++) //绘制棋子
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            if (board[i][j] != NO_PIECE)
            {
                QColor color = (board[i][j] == WHITE_PIECE) ? Qt::white : Qt::black;
                painter.setBrush(QBrush(color));
                painter.drawEllipse(START_POS.x() - CELL_SIZE.width()/2 + i*CELL_SIZE.width(),
                                    START_POS.y() - CELL_SIZE.height()/2 + j*CELL_SIZE.height(),
                                    CELL_SIZE.width(), CELL_SIZE.height());
            }
        }
    }

    painter.setPen(Qt::red);
    if (!dropedPieces.isEmpty())
    {
        QPoint lastPos = dropedPieces.top();
        QPoint drawPos = START_POS + QPoint(lastPos.x() * CELL_SIZE.width(), lastPos.y() * CELL_SIZE.height());
        painter.drawLine(drawPos + QPoint(0, 5), drawPos + QPoint(0, -5));
        painter.drawLine(drawPos + QPoint(5, 0), drawPos + QPoint(-5, 0));
    }
    for (int i = 0; i < BOARD_WIDTH; i++){
            for (int j = 0; j < BOARD_HEIGHT; j++)
            {
                // check if the current position is the highlighted position
                if (lastpiece == QPoint(i, j))
                {
                    painter.setBrush(Qt::NoBrush);
                    painter.setPen(QPen(Qt::blue, 1));
                    QRect rectangle(START_POS + QPoint((i-0.5) * CELL_SIZE.width(), (j-0.5) * CELL_SIZE.height()), CELL_SIZE);
                    painter.drawRect(rectangle);
                    painter.setPen(Qt::NoPen);
                }
            }
    }
}

void BoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (receivePlayers.contains(nextPlayer))
    {
        QPoint pos = event->pos() - START_POS;
        int x = pos.x();
        int y = pos.y();
        int pieceX = x / CELL_SIZE.width();
        int pieceY = y / CELL_SIZE.height();
        int offsetX = x % CELL_SIZE.width();
        int offsetY = y % CELL_SIZE.height();
        if (offsetX > CELL_SIZE.width() / 2)
        {
            pieceX++;
        }
        if (offsetY > CELL_SIZE.height() / 2)
        {
            pieceY++;
        }
        downPiece(pieceX, pieceY);
    }
}

void BoardWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos() - START_POS + QPoint(CELL_SIZE.width()/2, CELL_SIZE.height()/2);
    int x = pos.x();
    int y = pos.y();
    //超过范围
    if (x < 0 || x >= CELL_SIZE.width() * BOARD_WIDTH ||
            y < 0 || y >= CELL_SIZE.height() * BOARD_HEIGHT)
    {
        return;
    }
    int offsetX = x % CELL_SIZE.width();
    int offsetY = y % CELL_SIZE.height();
    setTrackPos(QPoint(x - offsetX, y - offsetY) + START_POS - QPoint(CELL_SIZE.width()/2, CELL_SIZE.height()/2));
}


void BoardWidget::initBoard()
{
    receivePlayers << WHITE_PLAYER << BLACK_PLAYER;
    newGame();
}


void BoardWidget::setTrackPos(const QPoint &value)
{
    trackPos = value;
    update();
}

void BoardWidget::setReceivePlayers(const QSet<int> &value)
{
    receivePlayers = value;
}

Board BoardWidget::getBoard()
{
    return board;
}

void BoardWidget::switchNextPlayer()
{
    if (nextPlayer == WHITE_PLAYER) {
            whiteStepCount++;
            whiteStepLabel->setText(QString("白方：%1步").arg(whiteStepCount));
            whiteThinkingTime += originTime-remainingTime;
        } else {
            blackStepCount++;
            blackStepLabel->setText(QString("黑方：%1步").arg(blackStepCount));
            blackThinkingTime += originTime-remainingTime;
        }
    totalStepLabel->setText(QString("总步数：%1步").arg(blackStepCount+whiteStepCount));
    nextPlayer = !nextPlayer;
    emit turnNextPlayer(nextPlayer);
}

void BoardWidget::newGame()
{

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            board[i][j] = NO_PIECE;
        }
    }
    dropedPieces.clear();
    nextPlayer = BLACK_PLAYER;
    remainingTime=60;//更新时间
    if (timer) {
        timer->start();
    }
    flag=0;
    whiteThinkingTime=0;
    blackThinkingTime=0;
    whiteStepCount=0;
    blackStepCount=0;
    originTime=60;
    whiteStepLabel->setText(QString("白方：%1步").arg(whiteStepCount));
    blackStepLabel->setText(QString("黑方：%1步").arg(blackStepCount));
    totalStepLabel->setText(QString("总步数：%1步").arg(blackStepCount+whiteStepCount));
    update();
    update();
    emit turnNextPlayer(nextPlayer);
}
void BoardWidget::initTime()//初始化时间
{
    //初始化计时
    remainingTime = 60;

        // 初始化 QLabel 控件
        timeLabel = new QLabel(this);
        timeLabel->setGeometry(QRect(360, 20, 100, 30));
        timeLabel->setText(QString("Time: %1 s").arg(remainingTime));

        // 初始化 QTimer
        timer = new QTimer(this);
        timer->setInterval(1000); // 设置间隔为 1000 毫秒（1 秒）
        connect(timer, &QTimer::timeout, this, &BoardWidget::onTimerTimeout);

        // 开始计时
        timer->start();
}
void BoardWidget::onTimerTimeout()//不是定时60s后执行，而是每秒执行（设置的间隔是1000ms），修改显示的时间
{
    // 每秒减少剩余时间
    remainingTime--;

    // 更新 QLabel 文本
    timeLabel->setText(QString("Time: %1 s").arg(remainingTime));

    // 检查剩余时间是否已用完
    if (remainingTime <= 0) {
        timer->stop();
        QMessageBox::information(this, "Time out", "Time is up!");
        flag=1;
        if (nextPlayer == WHITE_PLAYER)
        {
            gameOver(WHITE_PLAYER);
        }
        else
        {
            gameOver(BLACK_PLAYER);
        }
    }
}

void BoardWidget::onChangeTimeButtonClicked()//更改时间，点击后可输入新的时间间隔
{
    timer->stop();
    bool yes;
    int newTime = QInputDialog::getInt(
        this,
        "Change Time",
        "Enter new time (in seconds 整数):",
        SET_TIME,
        1,
        9999,
        1,
        &yes);

    if (yes)
    {
        SET_TIME = newTime;
        originTime=SET_TIME;
        remainingTime=SET_TIME;//更新时间
    }
    timer->start();
}

void BoardWidget::onGiveUpButtonClicked()
{
    flag=1;
    if (nextPlayer == WHITE_PLAYER)
    {
        gameOver(WHITE_PLAYER);
    }
    else
    {
        gameOver(BLACK_PLAYER);
    }
}

void BoardWidget::downPiece(int x, int y)
{
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT && board[x][y] == NO_PIECE)
    {
        board[x][y] = (nextPlayer == WHITE_PLAYER) ? WHITE_PIECE : BLACK_PIECE;

        if (!isSuicidalMove(x, y))
        {
            lastpiece=QPoint(x,y);
            if (capturesOpponent(x, y))
            {
                // 当落子一方吃掉对方棋子时，判断其为负方
                gameOver(nextPlayer);
            }

            else
            {
                dropedPieces.push(QPoint(x, y));
                update();
                switchNextPlayer();
                remainingTime=SET_TIME; // 更新时间
                update();
            }
        }
        else
        {
            // 落子导致己方棋子没气，判负
            QMessageBox::warning(this, tr("警告"), tr("不允许自杀！"));
            board[x][y] = NO_PIECE;  // 清除棋子
                update();
                return;
        }
    }
}
// 修改downpiece方法，以便在落子时检查自杀行为和吃子行为。当落子导致吃子时，游戏判定为负方。当落子导致自杀行为时，游戏判定为负方。

bool BoardWidget::isSuicidalMove(int x, int y)//检查落子是否为自杀行为（导致己方棋子没气）
{
    int currentColor = board[x][y];
    initVisited();
    if (!hasLiberties(board,visited, x, y, currentColor)) return true;
    else return false;
}

bool BoardWidget::hasLiberties( Board tempBoard,QVector<QVector<bool>> &visited, int x, int y, int color)
{
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
    {
       return false;
    }
    else if(visited[x][y]) return false;
    visited[x][y] = 1;

    if (tempBoard[x][y] == NO_PIECE)
    {
        initVisited();
        return true;
    }
    if (tempBoard[x][y] != color)
    {
        visited[x][y] = 0;
        return false;
    }

    return hasLiberties(tempBoard, visited, x - 1, y, color) || hasLiberties(tempBoard, visited, x + 1, y, color) ||
           hasLiberties(tempBoard, visited, x, y - 1, color) || hasLiberties(tempBoard, visited, x, y + 1, color);
}




bool BoardWidget::capturesOpponent(int x, int y)
{
    int currentColor = board[x][y];
    int opponentColor = (currentColor == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE;

    QVector<QPoint> neighbors;
    neighbors << QPoint(x - 1, y) << QPoint(x + 1, y) << QPoint(x, y - 1) << QPoint(x, y + 1);
    bool captured = false;

    for (const QPoint &neighbor : neighbors)
    {
        int nx = neighbor.x();
        int ny = neighbor.y();
        if (nx >= 0 && nx < BOARD_WIDTH && ny >= 0 && ny < BOARD_HEIGHT && board[nx][ny] == opponentColor)
        {
            initVisited();
            if (!hasLiberties(board,visited, nx, ny, opponentColor))
            {

                captured = true;
            }
        }
    }
    return captured;
}


void BoardWidget::captureStones(int x, int y)//吃掉对方的棋子
{
int capturedColor = board[x][y];
board[x][y] = NO_PIECE;
QVector<QPoint> neighbors;
neighbors << QPoint(x - 1, y) << QPoint(x + 1, y)
          << QPoint(x, y - 1) << QPoint(x, y + 1);

for (const QPoint &neighbor : neighbors)
{
    int nx = neighbor.x();
    int ny = neighbor.y();
    if (nx >= 0 && nx < BOARD_WIDTH && ny >= 0 && ny < BOARD_HEIGHT && board[nx][ny] == capturedColor)
    {
        captureStones(nx, ny);
    }
}
}
void BoardWidget::initVisited()
{
 for(int i=0;i<15;i++)
 {
     for(int j=0;j<15;j++)
     {
         visited[i][j]=0;
     }
 }
}
void BoardWidget::gameOver(int loser)//游戏结束，显示输家信息并开始新游戏
{
timer->stop();
QString loserStr = (loser == WHITE_PLAYER) ? "白方" : "黑方";
if(loser==WHITE_PLAYER&&flag==0){
    whiteStepCount++;
    whiteStepLabel->setText(QString("白方：%1步").arg(whiteStepCount));
}else if(loser==BLACK_PLAYER&&flag==0){
    blackStepCount++;
    blackStepLabel->setText(QString("黑方：%1步").arg(blackStepCount));
}
whiteAvgThinkingTime = (whiteStepCount > 0) ? ((double) whiteThinkingTime / whiteStepCount) : 0;
blackAvgThinkingTime = (blackStepCount > 0) ? ((double) blackThinkingTime / blackStepCount) : 0;
TotalTime=whiteThinkingTime+blackThinkingTime;
totalStepLabel->setText(QString("总步数：%1步").arg(blackStepCount+whiteStepCount));
    // 显示结算信息
    QMessageBox::information(this, "游戏结束",
                              QString("%1惜败!\n\n"
                                      "总步数: 白方 %2, 黑方 %3\n"
                                      "总时间：%6s\n"
                                      "平均思考时间: 白方 %4s, 黑方 %5s")
                                      .arg(loserStr)
                                      .arg(whiteStepCount)
                                      .arg(blackStepCount)
                                      .arg(whiteAvgThinkingTime,0,'f',2)
                                      .arg(blackAvgThinkingTime,0,'f',2)
                                      .arg(TotalTime,0,'f',2));
}
