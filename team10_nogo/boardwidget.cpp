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

BoardWidget::BoardWidget(int boardSize,QWidget *parent) ://获取棋盘大小，创建棋盘界面
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
    QPushButton *changeTimeButton = new QPushButton("Change Time", this);
    changeTimeButton->setGeometry(QRect(340, 70, 90, 30));
    connect(changeTimeButton, &QPushButton::clicked, this, &BoardWidget::onChangeTimeButtonClicked);
    //认输
    QPushButton *giveUp = new QPushButton("Give Up", this);
    giveUp->setGeometry(QRect(340, 110, 90, 30));
    connect(giveUp, &QPushButton::clicked, this, &BoardWidget::giveUp);


    //初始化计时器和棋盘
    initTime();//initBoard用到了initTime初始化的timer指针，二者顺序不可交换
    initBoard();

}

void BoardWidget::paintEvent(QPaintEvent *)//实现棋盘，棋子，标记鼠标位置，上一次落子位置的绘制
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
   //标记当前鼠标位置
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

    //绘制棋盘棋子
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
}

void BoardWidget::mouseReleaseEvent(QMouseEvent *event)//鼠标点击，获取坐标，调用downPiece
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

void BoardWidget::mouseMoveEvent(QMouseEvent *event)//鼠标移动显示即将落子的位置。
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

void BoardWidget::setTrackPos(const QPoint &value)//包含更新棋盘
{
    trackPos = value;
    update();
}

void BoardWidget::initBoard()//初始化棋盘
{
    receivePlayers << WHITE_PLAYER << BLACK_PLAYER;
    newGame();
}

void BoardWidget::downPiece(int x, int y)
{
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT && board[x][y] == NO_PIECE)
    {
        board[x][y] = (nextPlayer == WHITE_PLAYER) ? WHITE_PIECE : BLACK_PIECE;

        if (!isSuicidalMove(x, y))
        {
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
            board[x][y] = NO_PIECE;
            gameOver(nextPlayer);
        }
    }
}

void BoardWidget::switchNextPlayer()//此函数用于实现棋手之间的转换
{
    nextPlayer = !nextPlayer;
    emit turnNextPlayer(nextPlayer);
}

void BoardWidget::newGame()//开始新游戏
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
    remainingTime=SET_TIME;//更新时间
    if (timer) {
        timer->start();
    }

    update();
    update();
    emit turnNextPlayer(nextPlayer);
}

void BoardWidget::initTime()//初始化时间
{
    //初始化计时
    remainingTime=SET_TIME;

        // 初始化 QLabel 控件
        timeLabel = new QLabel(this);
        timeLabel->setGeometry(QRect(340, 20, 100, 30));
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
    if (remainingTime <= 0)
    {
        timer->stop();
        if(nextPlayer)QMessageBox::information(this, "Time out", "White player loses!");
        else QMessageBox::information(this, "Time out", "Black player loses!");
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
        remainingTime=SET_TIME;//更新时间
    }
    timer->start();
}

Board BoardWidget::getBoard()
{
    return board;
}

void BoardWidget::setReceivePlayers(const QSet<int> &value)
{
    receivePlayers = value;
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

bool BoardWidget::isSuicidalMove(int x, int y)//检查落子是否为自杀行为（导致己方棋子没气）
{
    int currentColor = board[x][y];
    initVisited();
    if (!hasLiberties(board,visited, x, y, currentColor)) return true;
    else return false;
}

bool BoardWidget::hasLiberties( Board tempBoard,QVector<QVector<bool>> &visited, int x, int y, int color)
//判断在（x，y）坐标下的color色棋子是否有气，visited用于记录每个位置在递归过程中是否访问过
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

bool BoardWidget::capturesOpponent(int x, int y)//判断是否吃掉对方棋子
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

void BoardWidget::gameOver(int loser)//游戏结束，显示输家信息并开始新游戏
{
timer->stop();
QString loserStr = (loser == WHITE_PLAYER) ? "White" : "Black";
QMessageBox::information(this, "Game Over", loserStr + " player loses!");
newGame();
}
void BoardWidget::giveUp()//认输
{
    gameOver(nextPlayer);
}
