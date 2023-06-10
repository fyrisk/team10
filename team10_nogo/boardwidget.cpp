#include "boardwidget.h"
#include <QDateTime>
#include "network/networkdata.h"
#include <QFile>
#include <QTextStream>
#include "gomokuai.h"

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
    trackPos(28, 28),
    isGameWithAi(0)
{
    setWindowTitle("NoGo");
    //设置棋盘大小
    BOARD_WIDTH = boardSize;
    BOARD_HEIGHT = boardSize;
    setFixedSize(WIDGET_SIZE);
    setMouseTracking(true);
    //设置切换人机模式的按钮
    QPushButton *switchModeButton = new QPushButton("AI", this);
    switchModeButton->setGeometry(QRect(340, 310, 90, 30));
    connect(switchModeButton, &QPushButton::clicked, this, &BoardWidget::onSwitchModeButtonClicked);

    QPushButton *stopAIButton = new QPushButton("stop AI", this);
    stopAIButton->setGeometry(QRect(340, 350, 90, 30));
    connect(stopAIButton, &QPushButton::clicked, this, &BoardWidget::stopAIPlayer);

    QPushButton *EVEButton = new QPushButton("EVE", this);
    EVEButton->setGeometry(QRect(340, 390, 90, 30));
    connect(EVEButton, &QPushButton::clicked, this, &BoardWidget::onEVEButtonClicked);
    //修改倒计时时间按钮
    QPushButton *ChangeTimeButton = new QPushButton("Change Time", this);
    ChangeTimeButton -> setGeometry(QRect(340, 50, 90, 30));
    connect(ChangeTimeButton, &QPushButton::clicked, this, &BoardWidget::onChangeTimeButtonClicked);
    //设置投降按钮
    QPushButton *giveUpButton = new QPushButton("Give up", this);
    giveUpButton->setGeometry(QRect(340, 80, 90, 30));
    connect(giveUpButton, &QPushButton::clicked, this, &BoardWidget::onGiveUpButtonClicked);

    //输出行棋记录
    QPushButton *showButton = new QPushButton("all history", this);
    showButton->setGeometry(QRect(340, 270, 90, 30));
    connect(showButton, &QPushButton::clicked, this, &BoardWidget::onShowButtonClicked);

    QPushButton *showLastButton = new QPushButton("last history", this);
    showLastButton->setGeometry(QRect(340, 230, 90, 30));
    connect(showLastButton, &QPushButton::clicked, this, &BoardWidget::onShowLastButtonClicked);

    QPushButton *stopButton = new QPushButton("暂停", this);
    stopButton->setGeometry(QRect(10, 350, 50, 30));
    connect(stopButton, &QPushButton::clicked, this, &BoardWidget::onStopButtonClicked);

    QPushButton *continueButton = new QPushButton("继续", this);
    continueButton->setGeometry(QRect(80, 350, 50, 30));
    connect(continueButton, &QPushButton::clicked, this, &BoardWidget::onContinueButtonClicked);

    QPushButton *lastButton = new QPushButton("上一步", this);
    lastButton->setGeometry(QRect(150, 350, 70, 30));
    connect(lastButton, &QPushButton::clicked, this, &BoardWidget::onLastButtonClicked);

    QPushButton *nextButton = new QPushButton("下一步", this);
    nextButton->setGeometry(QRect(240, 350, 70, 30));
    connect(nextButton, &QPushButton::clicked, this, &BoardWidget::onNextButtonClicked);

    QPushButton *jumpButton = new QPushButton("跳至…", this);
    jumpButton->setGeometry(QRect(10, 390, 90, 30));
    connect(jumpButton, &QPushButton::clicked, this, &BoardWidget::onJumpButtonClicked);


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
    timer->stop();
}

void BoardWidget::onSwitchModeButtonClicked()
{   
    qDebug()<<"into onSwitchModeButtonClicked()";
    if(isPVP==0||(nextPlayer&&PVPColor==1)||(!nextPlayer&&PVPColor==2))
    {
    isGameWithAi=1;
    AIColor=(nextPlayer == WHITE_PLAYER) ? WHITE_PIECE : BLACK_PIECE;
    startAIPlayer(); // 启动AI玩家的决策
    }
}
void BoardWidget::onEVEButtonClicked()
{
  if(isPVP==0||(nextPlayer&&PVPColor==1)||(!nextPlayer&&PVPColor==2))
  {
    isEVE=1;
    isAITurn[nextPlayer]=1;
    isAITurn[!nextPlayer]=1;
    if(!isGameWithAi)
    {
        isGameWithAi=1;
        startAIPlayer();
    }
  }
}
void BoardWidget::startAIPlayer()
{
    qDebug()<<"into startAIPlayer()";
    // 创建AI玩家对象（GomokuAi），并连接相应信号和槽

         qDebug()<<"into if(aiPlayer==nullptr)";
         aiPlayer = new GomokuAi(this);

     qDebug()<<"before connect";
    connect(aiPlayer, &GomokuAi::aiMove, this, &BoardWidget::makeAiMove);
    isplayerturn=1;
    isAITurn[nextPlayer]=1;
     qDebug()<<"after connect and sets";
    emit turnNextPlayer(nextPlayer);//并没有交换玩家，只是告诉AI开始下棋
}

void BoardWidget::stopAIPlayer()
{
    isGameWithAi = 0;
    isAITurn[nextPlayer]=0;
    isAITurn[!nextPlayer]=0;
    // 断开信号和槽连接，并释放AI玩家对象
    if(aiPlayer)
        disconnect(aiPlayer, &GomokuAi::aiMove, this, &BoardWidget::makeAiMove); // 这里断开连接BoardWidget类的makeMove槽
}


void BoardWidget::makeAiMove()
{
    // AI玩家进行落子
    if (aiPlayer&&isAITurn[nextPlayer]==1)
    {

        QPoint pos = aiPlayer->findBestMove();
        aiDropPiece(pos.x(), pos.y());
    }
}

void BoardWidget::aiDropPiece(int x, int y)
{
    downPiece(x,y);
}


int BoardWidget::getBoardWidth() const
{
    // 返回棋盘宽度
    return BOARD_WIDTH;
}

int BoardWidget::getBoardHeight() const
{
    // 返回棋盘高度
    return BOARD_HEIGHT;
}
int BoardWidget::getLiberty(int color)
{
    int score=0;
    for(int i=0;i<BOARD_HEIGHT;i++)
    {
        for(int j=0;j<BOARD_HEIGHT;j++)
        {
            if(board[i][j]==NO_PIECE)
            {
                score+=hasNeighborPiece(i,j,color);
            }
        }
    }
    return score;
}
bool BoardWidget::hasNeighborPiece(int x, int y,int color) const
{
    // 检查指定位置的上下左右四个方向是否有相应颜色棋子
    if (x > 0 && board[x - 1][y] == color)
        return true;
    if (x < BOARD_WIDTH - 1 && board[x + 1][y] == color)
        return true;
    if (y > 0 && board[x][y - 1] == color)
        return true;
    if (y < BOARD_HEIGHT - 1 && board[x][y + 1] == color)
        return true;

    return false;
}

int BoardWidget::getPiece(int x, int y) const
{
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
    {
        return board[x][y];
    }
    else
    {
        // 棋盘越界时返回NO_PIECE
        return NO_PIECE;
    }
}
int BoardWidget::getScore(int color)
{
    //局势得分考虑三点：1占据棋盘有利位置多少，棋盘位置的价值存储在value数组中
    //2 我方棋子气数做负贡献，敌方棋子气数做正贡献
    //3 我方可落子数，减去对方可落子数
    int score=8000;
    for(int i=0;i<BOARD_HEIGHT;i++)
    {
        for(int j=0;j<BOARD_HEIGHT;j++)
        {
            //考虑占据棋盘有利位置的多少
            if(board[i][j]==color) score+=value[i][j];
            if(board[i][j]==3-color) score-=value[i][j];
            //考虑可落子位置，我方越多越好，对方越少越好（对方颜色为3-color）
            if(!board[i][j])
            {
                if(canDown(i,j,color)) {score+=1000;}
                if(canDown(i,j,3-color)) {score-=1000;}
            }
        }
    }
    //考虑气，我方气越少越好，对方越多越好（对方颜色为3-color）
    score-=getLiberty(color)*100;
    score+=getLiberty(3-color)*100;
    return score;
}
bool BoardWidget::canDown(int x,int y,int color)
{
    int flag=0;
    if(board[x][y]!=0) return false;
    board[x][y]=color;
    if(capturesOpponent(x,y)||isSuicidalMove(x,y)) flag=1;
    board[x][y]=NO_PIECE;
    if(flag) return false;
    return true;
}
void BoardWidget::setScores()
{
    int color=2-nextPlayer;
    for(int i=0;i<BOARD_HEIGHT;i++)
    {
        for(int j=0;j<BOARD_HEIGHT;j++)
        {
            if(canDown(i,j,color))
            {
                board[i][j]=color;
                scores[i][j]=getScore(color);
                //if(i==4&&j==4) qDebug()<<scores[i][j]<<" 1 ";
                board[i][j]=NO_PIECE;

                //下面一步是考虑对方落在此处的收益，若对方收益很大我方AI可以提前占据此位置
                if(canDown(i,j,3-color))
                {
                scores[i][j]-=getScore(3-color);
                board[i][j]=3-color;
                scores[i][j]+=getScore(3-color);
                }
                else scores[i][j]-=3000;
                board[i][j]=NO_PIECE;
            }
            else
            {
                //不能落子就设为很小的得分
                canDown1[i][j]=0;
                scores[i][j]=-999999;
            }
        }
    }
}
void BoardWidget::setPlayerName( QString &playerName)
{
    name = playerName;
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
        //qDebug()<<" pvpcolor=  "<<PVPColor<<"nextplayer"<<nextPlayer<<" isAITurn[nextPlayer]=  "<<isAITurn[nextPlayer]<<"isAITurn[!nextPlayer]"<<isAITurn[!nextPlayer];
        if(flag==0)
          //if(((isPVP==0&&isGameWithAi==0)||(nextPlayer&&(PVPColor==1||isAITurn[nextPlayer]))||(!nextPlayer&&(PVPColor==2||isAITurn[!nextPlayer]))))
         if(isPVP==0||(nextPlayer&&PVPColor==1)||(!nextPlayer&&PVPColor==2))
         if(isGameWithAi==0||!isAITurn[nextPlayer])
        {          
                downPiece(pieceX, pieceY);
        }
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
    if (nextPlayer == WHITE_PLAYER)
    {
            whiteStepCount++;
            whiteStepLabel->setText(QString("白方：%1步").arg(whiteStepCount));
            whiteThinkingTime += originTime-remainingTime;
    }
    else
    {
        blackStepCount++;
        blackStepLabel->setText(QString("黑方：%1步").arg(blackStepCount));
        blackThinkingTime += originTime-remainingTime;
    }
    totalStepLabel->setText(QString("总步数：%1步").arg(blackStepCount+whiteStepCount));
    nextPlayer = !nextPlayer;

    if(!isAITurn[!nextPlayer]||isEVE) emit turnNextPlayer(nextPlayer);   //发信号让AI开始落子
}
void BoardWidget::newGame()
{

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            board[i][j] = NO_PIECE;
            canDown1[i][j]=1;
            value[i][j] = qMin(qAbs(i-2),qAbs(i-6))*10+qMin(qAbs(j-2),qAbs(j-6))*10;//设置value值，标准为角落和中间分值高
            if(i+j==0||i+j==8||i+j==16) value[i][j]++;
        }
    }
    dropedPieces.clear();
    nextPlayer = BLACK_PLAYER;
    remainingTime=SET_TIME;//更新时间  // gai为settime
    flag=0;
    if (timer) {
        timer->stop();
    }
    flag=0;
    whiteThinkingTime=0;
    blackThinkingTime=0;
    whiteStepCount=0;
    blackStepCount=0;
    originTime=SET_TIME;
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
    remainingTime = SET_TIME;

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
        flag=1;
        QString map ="T";
        droppedPiecesM.append(map);
        if(isPVP)
        {
            if(nextPlayer!=2-PVPColor )
            {
                emit send(NetworkData(OPCODE::TIMEOUT_END_OP,name,"goodgame"));
                sended=true;
            }
        }
        QMessageBox::information(this, "Time out", "Time is up!");
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
     if(flag==0)
     if(isPVP==0||(nextPlayer&&PVPColor==1)||(!nextPlayer&&PVPColor==2))
     if(isGameWithAi==0||!isAITurn[nextPlayer])
    {
        QString map ="G";
        droppedPiecesM.append(map);
        flag=1;
      if(isPVP==1)
     {
      QString a=name;
      QString b="";
      NetworkData data=NetworkData(OPCODE::GIVEUP_OP,a,b);
      emit send(data);
     }
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

void BoardWidget::downPiece(int x, int y)
{
    //qDebug()<<"downpiece"<<x<<" ispvp=  "<<PVPColor<<"nextplayer"<<nextPlayer;
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT && board[x][y] == NO_PIECE)
    {
        board[x][y] = (nextPlayer == WHITE_PLAYER) ? WHITE_PIECE : BLACK_PIECE;

        if (!isSuicidalMove(x, y))
        {
            lastpiece=QPoint(x,y);
            if (capturesOpponent(x, y))
            {
                // 当落子一方吃掉对方棋子时，判断其为负方

                if(!isGameWithAi) QMessageBox::warning(this, tr("警告"), tr("吃子会判负！"));
                 flag2=1;
                board[x][y] = NO_PIECE;  // 清除棋子
                    update();
                    return;
                //gameOver(nextPlayer);
            }

            else
            {
                update();
                flag2=0;
                QString map = QString(QChar('A' + y)) + QString::number(x + 1);
                dropedPieces.push(QPoint(x, y));
                droppedPiecesM.append(map);
                update();
                isplayerturn=1-isplayerturn;
                if(isPVP==1&&nextPlayer==2-PVPColor)
                {
                    //qDebug() << "into emit sent";
                    QString time = QString::number(QDateTime::currentMSecsSinceEpoch());
                    NetworkData data=NetworkData(OPCODE::MOVE_OP,map,time);
                    emit send(data);
                }
                switchNextPlayer();
                remainingTime=SET_TIME; // 更新时间
                timer->start();
                update();
            }
        }
        else
        {
            // 落子导致己方棋子没气，判负
            flag2=1;
            if(!isGameWithAi) QMessageBox::warning(this, tr("警告"), tr("不允许自杀！"));
            board[x][y] = NO_PIECE;  // 清除棋子
                update();
                return;
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

bool BoardWidget::hasLiberties( Board tempBoard,QVector<QVector<bool>> &visited, int x, int y, int color)//是否有气
{
    //使用深度优先搜索，没有得出有气的结果就判定为无气
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
    {
       return false;
    }
    else if(visited[x][y]) return false;
    visited[x][y] = 1;

    //遇到空格子返回有气的结果，整个搜索都会返回真值
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
    //本次落子是否导致吃子
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
flag=1;
copyLast();
QString filename = "../game_history.txt";
saveLastHistory(lastHistory, filename);         //存储到本地
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


void BoardWidget::onShowButtonClicked()
{
    QString record;
    for (int i = 0; i < droppedPiecesM.size(); ++i)
    {
        record += droppedPiecesM[i];
        if (i != droppedPiecesM.size() - 1) record+=" ";
    }
    QMessageBox::information(this, tr("行棋记录"), record);
}
void BoardWidget::onShowLastButtonClicked()
{
    if (!lastHistory.isEmpty()){
    QString record;
    for (int i = 0; i < lastHistory.size(); ++i)
    {
        record += lastHistory[i];
        if (i != lastHistory.size() - 1) record+=" ";
    }
    QMessageBox::information(this, tr("上一把记录"), record);
    }
}
void BoardWidget::copyLast()
{
    int lastIndex = 0;
    for (int i = droppedPiecesM.size() - 2; i >= 0; --i)
    {
        if (droppedPiecesM[i] == "T" || droppedPiecesM[i] == "G"||i==0)
        {
            lastIndex = i;
            break;
        }
    }
    if(lastIndex ==0) lastIndex--;
    lastHistory = droppedPiecesM.mid(lastIndex+1);
}
void BoardWidget::saveLastHistory(const QVector<QString>& lastHistory, const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (const QString& move : lastHistory)
        {
            out << move << "\n";
        }
        file.close();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Failed to save game history to file."));
    }
}
QVector<QString> BoardWidget::loadLastHistory(const QString& filename)
{
    SET_TIME=999;
    QVector<QString> lastHistory;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString move = in.readLine();
            lastHistory.append(move);
        }
        file.close();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Failed to load game history from file."));
    }
    return lastHistory;
}

void BoardWidget::showLast()
{
    lastHistory=loadLastHistory("../game_history.txt");
    for(i=0;i<=lastHistory.size()-2;++i)
    {
        //判断是否暂停
        if (isStop)
            {
                while (isStop)
                    QCoreApplication::processEvents();
            }
        //每步延时半秒
        QTime delayTime = QTime::currentTime().addMSecs(500);
        while (QTime::currentTime() < delayTime)
            QCoreApplication::processEvents();

        QString move=lastHistory[i];
        //将行棋记录转化为坐标并调用落子函数downPiece
        int x = move.mid(1, move.length() - 1).toInt() - 1;
        int y = move.at(0).toLatin1() - 'A';
        downPiece(x,y);
        timer->stop();
    }
    if(nextPlayer==true)
    {
        if(lastHistory[i]=="G")
        QMessageBox::warning(this, tr("终局成因"), tr("白方认输"));
        else
        QMessageBox::warning(this, tr("终局成因"), tr("白方超时"));

    }
    else
    {
        if(lastHistory[i]=="G")
        QMessageBox::warning(this, tr("终局成因"), tr("黑方认输"));
        else
        QMessageBox::warning(this, tr("终局成因"), tr("黑方超时"));
    }
}

void BoardWidget::onStopButtonClicked()
{
    isStop=true;
}
void BoardWidget::onContinueButtonClicked()
{
    toTheStep(i);//回到当前暂停时的状态，抹去玩家自己的尝试
    isStop=false;
}
void BoardWidget::toTheStep(int x)
{
    //思路是初始化棋盘，重新播放到第x步，期间不设延迟
    newGame();
    SET_TIME=999;
    for(int i=0;i<x;++i)
    {
        QString move=lastHistory[i];
        int x = move.mid(1, move.length() - 1).toInt() - 1;
        int y = move.at(0).toLatin1() - 'A';
        downPiece(x,y);
        timer->stop();
    }
    i=x-1;
}
void BoardWidget::onLastButtonClicked()
{
    toTheStep(blackStepCount+whiteStepCount-1);
}
void BoardWidget::onNextButtonClicked()
{
    toTheStep(blackStepCount+whiteStepCount+1);
}
void BoardWidget::onJumpButtonClicked()
{
    bool yes;
    int newStep = QInputDialog::getInt(
        this,
        "jump to ……",
        "Enter new step :",
        SET_TIME,
        1,
        9999,
        1,
        &yes);

    if (yes)
    {
        toTheStep(newStep);
    }
}
