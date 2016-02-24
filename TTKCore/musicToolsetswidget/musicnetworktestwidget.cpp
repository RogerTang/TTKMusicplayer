#include "musicnetworktestwidget.h"
#include "ui_musicnetworktestwidget.h"
#include "musicbgthememanager.h"
#include "musicuiobject.h"
#include "musicnetworktestthread.h"
#include "musicutils.h"
#include "musicdatadownloadthread.h"
#include "musicmessagebox.h"
#include "musicnetworksuspensionwidget.h"

#include <QActionGroup>

MusicNetworkTestWidget::MusicNetworkTestWidget(QWidget *parent)
    : MusicAbstractMoveDialog(parent),
      ui(new Ui::MusicNetworkTestWidget), m_thread(nullptr), m_testDownload(nullptr)
{
    ui->setupUi(this);

    ui->topTitleCloseButton->setIcon(QIcon(":/share/searchclosed"));
    ui->topTitleCloseButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    m_totalUp = 0;
    m_totalDown = 0;
    m_testAverage = 0;
    ui->speedWidget->setAnimating(false);
    ui->speedWidget->setRatio(50);

    ui->suspensionButton->setStyleSheet(MusicUIObject::MPushButtonStyle06);
    ui->suspensionButton->setCursor(QCursor((Qt::PointingHandCursor)));
    ui->settingButton->setStyleSheet(MusicUIObject::MPushButtonStyle06);
    ui->settingButton->setCursor(QCursor((Qt::PointingHandCursor)));
    ui->testButton->setStyleSheet(MusicUIObject::MPushButtonStyle06);
    ui->testButton->setCursor(QCursor((Qt::PointingHandCursor)));
    connect(ui->suspensionButton, SIGNAL(clicked()), SLOT(suspensionOpen()));
    connect(ui->testButton, SIGNAL(clicked()), SLOT(networkTestStart()));

    m_thread = new MusicNetworkTestThread(this);
    connect(m_thread, SIGNAL(networkData(ulong,ulong)), SLOT(networkData(ulong,ulong)));
    m_thread->start();

    settingButton();

    m_testTimer.setInterval(5*1000);
    connect(&m_testTimer, SIGNAL(timeout()), SLOT(networkTestStop()));
}

MusicNetworkTestWidget::~MusicNetworkTestWidget()
{
    delete m_actionGroup;
    m_testTimer.stop();
    m_thread->stopAndQuitThread();
    delete m_thread;
    delete m_testDownload;
    delete ui;
}

void MusicNetworkTestWidget::settingButton()
{
    m_actionGroup = new QActionGroup(this);
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(MusicUIObject::MMenuStyle02);

    QStringList list = m_thread->getNewtworkNames();
    foreach(QString var, list)
    {
        m_actionGroup->addAction(menu->addAction(var));
    }

    ui->settingButton->setMenu(menu);
    connect(m_actionGroup, SIGNAL(triggered(QAction*)), SLOT(actionTriggered(QAction*)));
}

void MusicNetworkTestWidget::networkData(ulong upload, ulong download)
{
    m_totalUp += upload;
    m_totalDown += download;

    ui->uploadSpeedValue->setText(MusicUtils::speed2Label(upload));
    ui->downloadSpeedValue->setText(MusicUtils::speed2Label(download));
    ui->uploadAllSpeedValue->setText(MusicUtils::speed2Label(m_totalUp));
    ui->downloadAllSpeedValue->setText(MusicUtils::speed2Label(m_totalDown));

    if(m_testTimer.isActive())
    {
        int value = MusicUtils::sizeByte2KByte(download);
        if(value > 100*ui->speedWidget->ratio())
        {
            value = 100*ui->speedWidget->ratio();
        }
        m_testAverage += value;
        ui->speedWidget->setValue(value);
    }
}

void MusicNetworkTestWidget::suspensionOpen()
{
//    (new MusicNetworkSuspensionWidget())->show();
}

void MusicNetworkTestWidget::networkTestStart()
{
    ui->testButton->setEnabled(false);
    m_testTimer.stop();
    delete m_testDownload;
    m_testDownload = new MusicDataDownloadThread(testUrl, testName,
                             MusicDownLoadThreadAbstract::Download_BigBG, this);
    m_testDownload->startToDownload();
    m_testTimer.start();
}

void MusicNetworkTestWidget::actionTriggered(QAction *action)
{
    if(action->icon().isNull())
    {
        action->setIcon(QIcon(":/share/selected"));
    }
    else
    {
        action->setIcon(QIcon());
    }

    QStringList selected;
    QList<QAction*> actions = m_actionGroup->actions();
    foreach(QAction *action, actions)
    {
        if(!action->icon().isNull())
        {
            selected << action->text();
        }
    }
    m_thread->setAvailableNewtworkNames(selected);
}

void MusicNetworkTestWidget::networkTestStop()
{
    delete m_testDownload;
    m_testDownload = NULL;
    m_testTimer.stop();
    ///remove temp file
    QFile::remove(testName);
    ui->testButton->setEnabled(true);

    MusicMessageBox message(this);
    message.setText(tr("Average is %1 kb/s").arg(m_testAverage/5));
    message.exec();
    m_testAverage = 0;
}

int MusicNetworkTestWidget::exec()
{
    QPixmap pix(M_BG_MANAGER->getMBackground());
    ui->background->setPixmap(pix.scaled( size() ));
    return MusicAbstractMoveDialog::exec();
}